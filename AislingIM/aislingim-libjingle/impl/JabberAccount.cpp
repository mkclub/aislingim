#include "StdAfx.h"
#include "..\JabberAccount.h"

#include "JabberAccountImp.h"

#include <iostream>

using namespace std;
namespace aislingim_libjingle
{
	JabberAccount::JabberAccount(const std::string& hostname, PORT_TYPE port, const std::string& jid, const std::string& password, bool useTls, const std::string& resourceName)
		:pimpl_(make_shared<JabberAccountImp>(hostname, port, jid, password, useTls, resourceName))
	{
	}

	JabberAccount::~JabberAccount(void)
	{
		if(loggedIn())
			close();
	}

		// properties
	bool JabberAccount::loggedIn()
	{
		return pimpl_->myStatus_ != OFFLINE;
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
	void JabberAccount::run()
	{
		//
		// ========= 1. Configuring connection =========
		//
		buzz::TlsOptions tls = pimpl_->useTls_ ? buzz::TLS_ENABLED : buzz::TLS_DISABLED;

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
		talk_base::AutoThread* thread = new talk_base::AutoThread(); //TODO: do we need to destroy this object?							
		talk_base::ThreadManager::Instance()->SetCurrentThread(thread);
		pimpl_->main_thread_ = talk_base::Thread::Current();				
	
		// ========= 4. Send the sign in request. =========
		pump.DoLogin(xcs, new buzz::XmppSocket(buzz::TLS_REQUIRED), new XmppAuth());

		// ========= 6. Start the thread and run indefinitely. =========
		pimpl_->main_thread_->Run();
	
		//
		// DISCONNECTING
		//
		pump.DoDisconnect();
	}

	void JabberAccount::close()
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