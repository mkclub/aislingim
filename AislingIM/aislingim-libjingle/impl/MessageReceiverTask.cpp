#include "StdAfx.h"
#include "libjingle/MessageReceiverTask.h"

#include <iostream>

#include "libjingle\talk\xmpp\constants.h"
using namespace std;

namespace aislingim_libjingle
{
	//
	// defining consts
	//
	MessageReceiverTask::MessageReceiverTask(XmppTaskParentInterface* parent):ReceiveTask(parent)
	{}

	MessageReceiverTask::~MessageReceiverTask()
	{
		messageEventHandler_.disconnect_all();
	}

	bool MessageReceiverTask::WantsStanza(const buzz::XmlElement* stanza)
	{
		if(stanza->Name() == buzz::QN_MESSAGE)
		{ // we are accepting this stanza
			return true;
		}
		else
		{ // this is some stanza we are not interested in, rejecting.
			return false;
		}
	}

	void MessageReceiverTask::ReceiveStanza(const buzz::XmlElement* stanza)
	{
		//
		// Building the message object
		//
		Message msg;
		msg.setId(stanza->HasAttr(buzz::QN_ID) ? stanza->Attr(buzz::QN_ID): "");
		msg.setEncoding(stanza->HasAttr(buzz::QN_ENCODING)? stanza->Attr(buzz::QN_ENCODING): "");
		msg.setFrom(stanza->HasAttr(buzz::QN_FROM) ? stanza->Attr(buzz::QN_FROM): "");
		msg.setTo(stanza->HasAttr(buzz::QN_TO) ? stanza->Attr(buzz::QN_TO): "");
		msg.setChatMessage(stanza->HasAttr(buzz::QN_TYPE)? stanza->Attr(buzz::QN_TYPE) == "chat" : false);

		const buzz::XmlElement* element = stanza->FirstNamed(buzz::QN_SUBJECT);
		msg.setSubject(element != nullptr ? element->BodyText() : "");
	
		element = stanza->FirstNamed(buzz::QN_BODY);
		msg.setBody(element != nullptr ? element->BodyText() : "");
	
		//
		//invoking event with the message
		//
		messageEventHandler_.emit(msg);
	}
}