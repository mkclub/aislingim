#pragma once

#include "libjingle\talk\base\thread.h"
#include "libjingle\talk\xmpp\presenceouttask.h"

class SetStatusMessageHandler : public talk_base::MessageHandler
{
private:
	buzz::PresenceOutTask* presenceTaskToSend_;
	buzz::PresenceStatus* statusToSend_;

public:

	SetStatusMessageHandler(buzz::PresenceOutTask* presenceTaskToSend, buzz::PresenceStatus* statusToSend) {
		presenceTaskToSend_ = presenceTaskToSend;
		statusToSend_ = statusToSend;
	}

	virtual void OnMessage(talk_base::Message*) {
		  presenceTaskToSend_->Send(*statusToSend_);
	}

	virtual ~SetStatusMessageHandler(){}
};

