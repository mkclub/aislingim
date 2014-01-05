#pragma once

#include "..\JabberAccount.h"

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

	void logEventHandlerStub(void* context, const std::string& message, LOG_MESSAGE_TYPE_ENUM messageType);
	void myStatusEventHandlerStub(void* context, STATUS_ENUM status);
	void contactStatusEventHandlerStub(void* context, const std::string& jid, STATUS_ENUM status);
	void messageReceivedEventHandlerStub(void* context, const Message& message);

	struct JabberAccountImp : public sigslot::has_slots<> // otherwise we have issues on connecting to libjingle events.
	{
		std::string resourceName_;
		std::string hostname_; 
		PORT_TYPE port_;
		std::string jid_; 
		std::string password_;
		bool useTls_;
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

		JabberAccountImp(const std::string& hostname, PORT_TYPE port, const std::string& jid, const std::string& password, bool useTls, const std::string& resourceName):
			hostname_(hostname),port_(port), jid_(jid),password_(password), useTls_(useTls), resourceName_(resourceName),
				myStatus_(OFFLINE),logEventHandler_(&logEventHandlerStub, nullptr), myStatusEventHandler_(&myStatusEventHandlerStub,nullptr),
				contactStatusEventHandler_(&contactStatusEventHandlerStub, nullptr), messageReceivedEventHandler_(&messageReceivedEventHandlerStub, nullptr),
				xmppClient_(nullptr),main_thread_(nullptr), presenceOutTask_(nullptr), presencePushTask_(nullptr), messageReceiverTask_(nullptr)
		{}

		//property getters/setters
		void updateMyStatus(STATUS_ENUM newStatus);


		// event handlers
		void onLogMessage(const std::string& message, LOG_MESSAGE_TYPE_ENUM messageType);
		void onIncomingLogMessage(const char * data, int len);
		void onOutgoingLogMessage(const char * data, int len);
		void logDebugMessage(const std::string& message);

		void onConnectionStateChanged(const buzz::XmppEngine::State state);
		void onContactStatusChanged(const buzz::PresenceStatus& status);
		void onMessageReceived(const Message& message);

		
		// service methods
		void performPostLoginSteps(const buzz::XmppEngine::State state); // some steps should be performed only after we successfully login (like creating message listeners)
		bool setStatus(STATUS_ENUM status, const std::string& statusMessage);
	};
}