#include "StdAfx.h"
#include "MessageReceiverTask.h"

#include <iostream>

#include "libjingle\talk\xmpp\constants.h"
using namespace std;

//
// defining consts
//
MessageReceiverTask::MessageReceiverTask(XmppTaskParentInterface* parent, bool printLogs):ReceiveTask(parent),printLogs_(printLogs)
{}

MessageReceiverTask::~MessageReceiverTask()
{
	messageEventHandler_.disconnect_all();
}

bool MessageReceiverTask::WantsStanza(const buzz::XmlElement* stanza)
{
	if(stanza->Name() == buzz::QN_MESSAGE)
	{
		if(printLogs_)
			cout<<"MESSAGE RECEIVER: Accepting Stanza \""<<stanza->Name().Merged()<<"\""<<endl;
		return true;
	}
	else
	{
		if(printLogs_)
			cout<<"MESSAGE RECEIVER: Rejecting Stanza \""<<stanza->Name().Merged()<<"\" != \""<<buzz::QN_MESSAGE.ns<<":"<<buzz::QN_MESSAGE.local<<"\""<<endl;
		return false;
	}
}

void MessageReceiverTask::ReceiveStanza(const buzz::XmlElement* stanza)
{
	if(printLogs_)
	{
		cout<<" ----  RECEIVED MESSAGE! --- "<<endl;
		cout<<"FROM:\t"<<(stanza->HasAttr(buzz::QN_FROM) ? stanza->Attr(buzz::QN_FROM): "N/A")<<endl;
		cout<<"TO:\t"<<(stanza->HasAttr(buzz::QN_TO) ? stanza->Attr(buzz::QN_TO): "N/A")<<endl;
		cout<<"ID:\t"<<(stanza->HasAttr(buzz::QN_ID) ? stanza->Attr(buzz::QN_ID): "N/A")<<endl;
		cout<<"TYPE:\t"<<(stanza->HasAttr(buzz::QN_TYPE)? stanza->Attr(buzz::QN_TYPE): "N/A")<<endl;
		cout<<"ENCODING:\t"<<(stanza->HasAttr(buzz::QN_ENCODING)? stanza->Attr(buzz::QN_ENCODING): "N/A")<<endl;

		const buzz::XmlElement* subjectElement = stanza->FirstNamed(buzz::QN_SUBJECT);
		cout<<"SUBJECT:\t"<<(subjectElement != nullptr ? subjectElement->BodyText() : "N/A")<<endl;

		const buzz::XmlElement* bodyElement = stanza->FirstNamed(buzz::QN_BODY);
		cout<<"BODY:\t"<<(bodyElement != nullptr ? bodyElement->BodyText() : "N/A")<<endl;
	
		cout<<"ELEMENTS:\t"<<endl;printElements(stanza->FirstElement(), 0);
		cout<<"RAW:\""<<stanza->Str()<<"\""<<endl;
		cout<<" ----  END OF MESSAGE --- "<<endl;
	}
	//
	// Creating the message
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
	//sending the message
	//
	messageEventHandler_.emit(msg);
}

//----------------------------------------DEBUGGING STUFF-----------------------------------

void MessageReceiverTask::printAttributes(const buzz::XmlAttr* attr)
{
	if(attr == nullptr)
		return;
	cout<<"[\""<<attr->Name().LocalPart()<<"\" = "<<attr->Value()<<"];";

	printAttributes(attr->NextAttr());
}

void MessageReceiverTask::printChildren(const buzz::XmlChild* child, size_t index)
{
	if(child == nullptr)
		return;
	
	cout<<"CHILD "<<index<<endl<<"  Text: \""<<(child->IsText() ? child->AsText()->Text() : "NOT A TEXT")<<"\"";
	if(!child->IsText())
	{
			cout<<"  Attributes: ";
			printAttributes(child->AsElement()->FirstAttr());
	}
	cout<<endl;
	printChildren(child->NextChild(),index+1);
}

void MessageReceiverTask::printElements(const buzz::XmlElement* element, size_t index)
{
	if(element == nullptr)
		return;
	
	cout<<"ELEMENT "<<index<<endl<<"  Text: \""<<(element->IsText() ? element->AsText()->Text() : "NOT A TEXT")<<"\"";
	if(!element->IsText())
	{
			cout<<"  Attributes: ";
			printAttributes(element->FirstAttr());
			cout<<endl<<"  Name: "<<element->Name().Merged()<<" (Local=\""<<element->Name().LocalPart()<<"\")"<<endl;
			cout<<"  Body text: "<<element->BodyText()<<endl;
	}
	cout<<endl;
	printElements(element->NextElement(), index+1);
}
//bool MessageReceiver::HandleStanza(const buzz::XmlElement* stanza)
//{
//	cout<<"Handling stanza: "<<endl;
//	return true;
//}