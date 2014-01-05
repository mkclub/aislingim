#include "StdAfx.h"
#include "JabberAccountImp.h"

#include "EnumUtils.h"
#include "libjingle\SetStatusMessageHandler.h"

using namespace std;

namespace aislingim_libjingle
{
	// definition of stub functions for event handlers.
	void logEventHandlerStub(void* context, const std::string& message, LOG_MESSAGE_TYPE_ENUM messageType){}
	void myStatusEventHandlerStub(void* context, STATUS_ENUM status){}
	void contactStatusEventHandlerStub(void* context, const std::string& jid, STATUS_ENUM status){}
	void messageReceivedEventHandlerStub(void* context, const Message& message){}

	bool JabberAccountImp::setStatus(STATUS_ENUM status, const string& statusMessage)
	{
		//
		// Creating status object
		//
		buzzStatus_.set_available(true);
		buzzStatus_.set_jid(buzz::Jid(jid_));
		buzzStatus_.set_show(EnumUtils::convert(status));
	
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
		{
			SetStatusMessageHandler handler = SetStatusMessageHandler(presenceOutTask_, &buzzStatus_);
			main_thread_->Send(&handler);
		}

		updateMyStatus(status);

		return true;
	}

	void JabberAccountImp::onLogMessage(const string& message, LOG_MESSAGE_TYPE_ENUM messageType)
	{
		logEventHandler_.handler_(logEventHandler_.context_, message, messageType);
	}

	void JabberAccountImp::onIncomingLogMessage(const char * data, int len)
	{
		onLogMessage(string(data, len), INCOMING);
	}
	void JabberAccountImp::onOutgoingLogMessage(const char * data, int len)
	{
		onLogMessage(string(data, len), OUTGOING);
	}

	void JabberAccountImp::logDebugMessage(const string& message)
	{
		onLogMessage(message, DEBUG);
	}

	void JabberAccountImp::updateMyStatus(STATUS_ENUM newStatus)
	{
		if(newStatus == myStatus_)
			return;

		myStatus_ = newStatus;
		myStatusEventHandler_.handler_(myStatusEventHandler_.context_, myStatus_);
	}

	void JabberAccountImp::onConnectionStateChanged(const buzz::XmppEngine::State state)
	{
		logDebugMessage(string("Connection State Updated. Now it is ")+EnumUtils::to_string(state));

		if(state == buzz::XmppEngine::STATE_OPEN)
		{
			performPostLoginSteps(state);
			updateMyStatus(ONLINE);//TODO: should we set here some other status (e.g., previously set status)?
		}
		else
			updateMyStatus(OFFLINE);
	}

	void JabberAccountImp::onContactStatusChanged(const buzz::PresenceStatus& status)
	{
		//
		// Preparing arguments
		//
		string jid = status.jid().node() + "@" + status.jid().domain() +"/" +status.jid().resource()+"("+to_string((long long)status.priority())+")";
		STATUS_ENUM statusEnum = OFFLINE;

		statusEnum = EnumUtils::convert(status.show());

		//
		// Sending event
		// 
		contactStatusEventHandler_.handler_(contactStatusEventHandler_.context_, jid, statusEnum);
	}
	
	void JabberAccountImp::onMessageReceived(const Message& message)
	{
		messageReceivedEventHandler_.handler_(messageReceivedEventHandler_.context_, message);
	}

	
	void JabberAccountImp::performPostLoginSteps(const buzz::XmppEngine::State state)
	{
		//
		// doing some important stuff that needs/can be done on connected state
		//
		if(state == buzz::XmppEngine::STATE_OPEN)
		{
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
				// task to get statuses of others.
				//
				presencePushTask_ = new buzz::PresencePushTask(xmppClient_);
				presencePushTask_->SignalStatusUpdate.connect(this, &JabberAccountImp::onContactStatusChanged);
				presencePushTask_->Start();

				//
				// task that publishes our status.
				//
				presenceOutTask_ = new buzz::PresenceOutTask(xmppClient_);
				presenceOutTask_->Start();

				//
				// Task to receive incoming messages
				//
				messageReceiverTask_ = new MessageReceiverTask(xmppClient_);
				messageReceiverTask_->onMessage(this, &JabberAccountImp::onMessageReceived);
				messageReceiverTask_->Start();
			}
		}
	}
}