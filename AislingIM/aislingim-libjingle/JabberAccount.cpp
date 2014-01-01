#include "StdAfx.h"
#include "JabberAccount.h"
#include "libjingle\talk\base\sigslot.h"
#include "libjingle\talk\xmpp\xmppengine.h"
#include "libjingle\talk\xmpp\xmpppump.h"
#include "libjingle\talk\xmpp\presenceouttask.h"

#include "libjingle\talk\base\ssladapter.h"
#include "libjingle\talk\xmpp\xmppthread.h"
#include "libjingle\talk\base\win32socketserver.h"
#include "libjingle\talk\xmpp\xmppauth.h"
#include "libjingle\talk\xmpp\presencestatus.h"

#include "libjingle\presencepushtask.h"
#include "libjingle\MessageReceiverTask.h"

#include <iostream>

using namespace std;
namespace aislingim_libjingle
{
	template <class EventType>
	struct EventHandler
	{
		EventType handler_;
		void* context_;

		EventHandler(EventType handler, void* context)
			:handler_(handler), context_(context)
		{
		}
	};

	void logEventHandlerStub(void* context, const string& message, LOG_MESSAGE_TYPE_ENUM messageType){}
	void myStatusEventHandlerStub(void* context, STATUS_ENUM status){}
	void contactStatusEventHandlerStub(void* context, const std::string& jid, STATUS_ENUM status){}
	void messageReceivedEventHandlerStub(void* context, const Message& message){}

	struct JabberAccountImp : public sigslot::has_slots<> // otherwise we have issues on connecting to libjingle events.
	{
		string resourceName_;
		string hostname_; 
		PORT_TYPE port_;
		string jid_; 
		string password_;
		bool useTls_;
		bool isLoggedIn_;
		STATUS_ENUM myStatus_;
		
		// libjingle
		buzz::XmppClient* xmppClient_;//we don't manage it, it's in responsibiilty of XmppPump.
		talk_base::Thread* main_thread_;//we don't manage it, it's in responsibiilty of XmppPump.
		buzz::PresenceOutTask* presenceOutTask_; // pump task responsible for receiving and signalling status of other contacts.
		buzz::PresencePushTask* presencePushTask_; // pump task responsible for publishing our status.
		MessageReceiverTask* messageReceiverTask_; // pump tasks responsible for receiving messages.
		buzz::PresenceStatus buzzStatus_;

		// events
		EventHandler<LogEvent> logEventHandler_;
		EventHandler<MyStatusEvent> myStatusEventHandler_;
		EventHandler<StatusEvent> contactStatusEventHandler_;
		EventHandler<MessageEvent> messageReceivedEventHandler_;


		JabberAccountImp(const string& hostname, PORT_TYPE port, const string& jid, const string& password, bool useTls, const string& resourceName):
			hostname_(hostname),port_(port), jid_(jid),password_(password), useTls_(useTls), resourceName_(resourceName),
				myStatus_(STATUS_ENUM::OFFLINE),logEventHandler_(&logEventHandlerStub, nullptr), myStatusEventHandler_(&myStatusEventHandlerStub,nullptr),
				contactStatusEventHandler_(&contactStatusEventHandlerStub, nullptr), messageReceivedEventHandler_(&messageReceivedEventHandlerStub, nullptr),
				xmppClient_(nullptr),main_thread_(nullptr), presenceOutTask_(nullptr), presencePushTask_(nullptr), messageReceiverTask_(nullptr)
		{}

		//property getters/setters
		void updateMyStatus(STATUS_ENUM newStatus);


		// event handlers
		void onLogMessage(const std::string& message, LOG_MESSAGE_TYPE_ENUM messageType);
		void onIncomingLogMessage(const char * data, int len);
		void onOutgoingLogMessage(const char * data, int len);
		void logDebugMessage(const string& message);

		void onConnectionStateChanged(const buzz::XmppEngine::State state);
		void onContactStatusChanged(const buzz::PresenceStatus& status);
		void onMessageReceived(const Message& message);

		
		// service methods
		void performPostLoginSteps(const buzz::XmppEngine::State state); // some steps should be performed only after we successfully login (like creating message listeners)
		bool setStatus(STATUS_ENUM status, const string& statusMessage);
	};

	JabberAccount::JabberAccount(const std::string& hostname, PORT_TYPE port, const std::string& jid, const std::string& password, bool useTls, const std::string& resourceName)
		:pimpl_(make_shared<JabberAccountImp>(hostname, port, jid, password, useTls, resourceName))
	{
	}

	JabberAccount::~JabberAccount(void)
	{
		if(loggedIn())
			logout();
	}

		// properties
	bool JabberAccount::loggedIn()
	{
		return pimpl_->myStatus_ != STATUS_ENUM::OFFLINE;
	}

	STATUS_ENUM JabberAccount::status()
	{
		return pimpl_->myStatus_;
	}

	bool JabberAccount::setStatus(STATUS_ENUM status, const string& statusMessage)
	{
		if(!loggedIn())
		return false; //we did not login yet.

		return pimpl_->setStatus(status, statusMessage);
	}

	bool JabberAccountImp::setStatus(STATUS_ENUM status, const string& statusMessage)
	{
		//
		// Creating status object
		//
		buzzStatus_.set_available(true);
		buzzStatus_.set_jid(buzz::Jid(jid_));
		switch(status)
		{
			case OFFLINE:
				buzzStatus_.set_show(buzz::PresenceStatus::SHOW_OFFLINE);
				break;
			case ONLINE:
				buzzStatus_.set_show(buzz::PresenceStatus::SHOW_ONLINE);
				break;
			case FREE_FOR_CHAT:
				buzzStatus_.set_show(buzz::PresenceStatus::SHOW_CHAT);
				break;
			case AWAY:
				buzzStatus_.set_show(buzz::PresenceStatus::SHOW_AWAY);
				break;
			case XA:
				buzzStatus_.set_show(buzz::PresenceStatus::SHOW_XA);
				break;
			case DND:
				buzzStatus_.set_show(buzz::PresenceStatus::SHOW_DND);
				break;
		}
	
		//TODO: decide on capabilities.

		buzzStatus_.set_priority(10); //TODO: decide who is responsible for priority.
		buzzStatus_.set_status(statusMessage);
	
		//
		// setting capabilities
		//
		buzzStatus_.set_know_capabilities(true);
		buzzStatus_.set_pmuc_capability(true);
		buzzStatus_.set_voice_capability(false);
		buzzStatus_.set_video_capability(false);
		buzzStatus_.set_camera_capability(false);
		buzzStatus_.set_feedback_probation(false);//WTF?

		if(presenceOutTask_ == nullptr)
		{
			logDebugMessage("PRESENCE TASK IS NULL, what is unexpected.");
			return false;
		}
		else
			presenceOutTask_->Send(buzzStatus_);

		return true;
	}
		
	//events
	void JabberAccount::setLogListener(LogEvent logListener, void* context)
	{
		pimpl_->logEventHandler_ = EventHandler<LogEvent>(logListener, context);
	}

	void JabberAccount::setMyStatusListener(MyStatusEvent eventHandler, void* context)
	{
		pimpl_->myStatusEventHandler_ = EventHandler<MyStatusEvent>(eventHandler, context);
	}

	void JabberAccount::setContactStatusListener(StatusEvent statusListener, void* context)
	{
		pimpl_->contactStatusEventHandler_ = EventHandler<StatusEvent>(statusListener, context);
	}
	
	void JabberAccount::setMessageListener(MessageEvent messageListener, void* context)
	{
		pimpl_->messageReceivedEventHandler_ = EventHandler<MessageEvent>(messageListener, context);
	}

	// methods

	void JabberAccountImp::onLogMessage(const string& message, LOG_MESSAGE_TYPE_ENUM messageType)
	{
		logEventHandler_.handler_(logEventHandler_.context_, message, messageType);
	}

	void JabberAccountImp::onIncomingLogMessage(const char * data, int len)
	{
		onLogMessage(string(data, len), LOG_MESSAGE_TYPE_ENUM::INCOMING);
	}
	void JabberAccountImp::onOutgoingLogMessage(const char * data, int len)
	{
		onLogMessage(string(data, len), LOG_MESSAGE_TYPE_ENUM::OUTGOING);
	}

	void JabberAccountImp::logDebugMessage(const string& message)
	{
		onLogMessage(message, LOG_MESSAGE_TYPE_ENUM::DEBUG);
	}

	void JabberAccountImp::updateMyStatus(STATUS_ENUM newStatus)
	{
		if(newStatus == myStatus_)
			return;

		myStatus_ = newStatus;
		myStatusEventHandler_.handler_(myStatusEventHandler_.context_, myStatus_);
	}

	string convertStateToString(const buzz::XmppEngine::State state)
	{
		switch(state)
		{
		case buzz::XmppEngine::State::STATE_NONE:        //!< Nonexistent state
			return "NONE";
		case buzz::XmppEngine::State::STATE_START:         //!< Initial state.
			return "START";
		case buzz::XmppEngine::State::STATE_OPENING:         //!< Exchanging stream headers, authenticating and so on.
			return "OPENING";
		case buzz::XmppEngine::State::STATE_OPEN:            //!< Authenticated and bound.
			return "OPEN";
		case buzz::XmppEngine::State::STATE_CLOSED:
			return "CLOSED";
		default:
			return "UNEXPECTED STATE";
		}
	}

	void JabberAccountImp::onConnectionStateChanged(const buzz::XmppEngine::State state)
	{
		logDebugMessage(string("Connection State Updated. Now it is ")+convertStateToString(state));

		if(state == buzz::XmppEngine::State::STATE_OPEN)
		{
			performPostLoginSteps(state);
			updateMyStatus(STATUS_ENUM::ONLINE);//TODO: should we set here some other status (e.g., previously set status)?
		}
		else
			updateMyStatus(STATUS_ENUM::OFFLINE);
	}

	void JabberAccountImp::onContactStatusChanged(const buzz::PresenceStatus& status)
	{
		//
		// Preparing arguments
		//
		string jid = status.jid().node() + "@" + status.jid().domain() +"/" +status.jid().resource()+"("+to_string((long long)status.priority())+")";
		STATUS_ENUM statusEnum = OFFLINE;

		// TODO: all these enums... we should decice what to do with them or create some helper methods...
		switch(status.show())
		{
			case buzz::PresenceStatus::SHOW_OFFLINE:
				statusEnum = OFFLINE;
				break;
			case buzz::PresenceStatus::SHOW_ONLINE:
				statusEnum = ONLINE;
				break;
			case buzz::PresenceStatus::SHOW_AWAY:
				statusEnum = AWAY;
				break;
			case buzz::PresenceStatus::SHOW_CHAT:
				statusEnum = FREE_FOR_CHAT;
				break;
			case buzz::PresenceStatus::SHOW_DND:
				statusEnum = DND;
				break;
			case buzz::PresenceStatus::SHOW_XA:
				statusEnum = XA;
				break;
			default:
				logDebugMessage(string("UNEXPECTED STATUS. Cannot convert status."));// + to_string((unsigned long)status.show()) + " interpreted as " + to_string(status.status()));
		}

		//
		// Sending event
		// 
		contactStatusEventHandler_.handler_(contactStatusEventHandler_.context_, jid, statusEnum);
	}
	
	void JabberAccountImp::onMessageReceived(const Message& message)
	{

	}

	void JabberAccount::login()
	{
		//
		// ========= 1. Configuring connection =========
		//
		buzz::TlsOptions tls =  pimpl_->useTls_ ? buzz::TLS_ENABLED : buzz::TLS_DISABLED;

		//setting username
		buzz::Jid jid = buzz::Jid(pimpl_->jid_);

		//setting password
		talk_base::InsecureCryptStringImpl pass;
		pass.password() = pimpl_->password_;

		// Connection settings
		buzz::XmppClientSettings xcs;
		xcs.set_user(jid.node());
		xcs.set_resource(pimpl_->resourceName_);//name of resource we login from
		xcs.set_host(jid.domain());
		xcs.set_allow_plain(false);
		xcs.set_use_tls(tls);
		xcs.set_pass(talk_base::CryptString(pass));
		//xcs.set_auth_token(buzz::AUTH_MECHANISM_OAUTH2, oauth_token); //if we want to use OAuth2, we can setup it here.
		xcs.set_server(talk_base::SocketAddress(pimpl_->hostname_, pimpl_->port_));

		// ========= 2. Register to receive signals from the XMPP pump to track sign in progress. =========
		buzz::XmppPump pump;
		pimpl_->xmppClient_ = pump.client();//we will need this client in future.
		pump.client()->SignalStateChange.connect(pimpl_.get(), &JabberAccountImp::onConnectionStateChanged);
		pump.client()->SignalLogInput.connect(pimpl_.get(), &JabberAccountImp::onIncomingLogMessage);
		pump.client()->SignalLogOutput.connect(pimpl_.get(), &JabberAccountImp::onOutgoingLogMessage);

	
		//
		// LOGGING IN
		//
		// ========= 3. Create the signaling thread. =========
		talk_base::Win32Thread w32_thread;									//TODO: windows dependency.
		talk_base::ThreadManager::Instance()->SetCurrentThread(&w32_thread);//TODO: windows dependency.
		pimpl_->main_thread_ = talk_base::Thread::Current();		//TODO: windows dependency.
	
		// ========= 4. Send the sign in request. =========
		//cout<<"Logging in... "<<endl;
	

		pump.DoLogin(xcs, new buzz::XmppSocket(buzz::TLS_REQUIRED), new XmppAuth());

		// ========= 6. Start the thread and run indefinitely. =========
		pimpl_->main_thread_->Run();
	
		//
		// DISCONNECTING
		//
		pump.DoDisconnect();
	}

	void JabberAccountImp::performPostLoginSteps(const buzz::XmppEngine::State state)
	{
		//
		// doing some important stuff that needs/can be done on connected state
		//
		if(state == buzz::XmppEngine::STATE_OPEN)
		{
			isLoggedIn_ = true;

			if(presenceOutTask_ != nullptr)
			{
				delete presenceOutTask_;
				presenceOutTask_ = nullptr;
			}

			if(xmppClient_ == nullptr)
				logDebugMessage("XMPP CLIENT IS NULL, while it was expected to be set! Something is wrong!");
			else
			{
				//
				// task that publishes our status.
				//
				presenceOutTask_ = new buzz::PresenceOutTask(xmppClient_);
				presenceOutTask_->Start();

				setStatus(STATUS_ENUM::ONLINE, "Demo status");//TODO: get rid of this and make it work properly.

				//
				// task to get statuses of others.
				//
				presencePushTask_ = new buzz::PresencePushTask(xmppClient_);
				presencePushTask_->SignalStatusUpdate.connect(this, &JabberAccountImp::onContactStatusChanged);
				presencePushTask_->Start();

				//
				// Task to receive incoming messages
				//
				bool printReceivedMessageProcess = false; // determines if we print to console how we process messages.
				messageReceiverTask_ = new MessageReceiverTask(xmppClient_, printReceivedMessageProcess);
				messageReceiverTask_->onMessage(this, &JabberAccountImp::onMessageReceived);
				messageReceiverTask_->Start();
			}
		}
	}

	void JabberAccount::logout()
	{
		if(!loggedIn())
		return;

		if(pimpl_->main_thread_ != nullptr)
		{
			pimpl_->main_thread_->Quit();
			//isLoggedIn_ = false; //TODO: check that status changes automatically.
		}
		else
			pimpl_->logDebugMessage("Failed to shutdown: application is not completely initialized.");
	}
}