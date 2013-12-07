#pragma once

#include "libjingle\talk\xmpp\receivetask.h"

struct Message
{
public:

	const std::string& getId() const {return id_;}
	const std::string& getEncoding() const {return encoding_;}
	const std::string& getFrom() const {return from_;}
	const std::string& getTo() const {return to_;}
	bool isChatMessage() const {return isChatMessage_;}
	const std::string& getSubject() const {return subject_;}
	const std::string& getBody() const {return body_;}

	void setId(const std::string& id){id_ = id;}
	void setEncoding(const std::string& encoding){encoding_ = encoding;}
	void setChatMessage(bool isChatMessage){isChatMessage_ = isChatMessage;}
	void setFrom(const std::string& from){from_ = from;}
	void setTo(const std::string& to){to_ = to;}
	void setSubject(const std::string& subject){subject_ = subject;}
	void setBody(const std::string& body){body_ = body;}
	
private:
	std::string id_;
	std::string encoding_;
	std::string from_;
	std::string to_;
	bool isChatMessage_;
	std::string subject_;
	std::string body_;
	
};

class MessageReceiverTask : public buzz::ReceiveTask
{
public:
	MessageReceiverTask(XmppTaskParentInterface* parent, bool printLogs);
	
	template<class desttype>
	void onMessage(desttype* clazz, void (desttype::*pmemfun)(const Message&)){messageEventHandler_.connect(clazz, pmemfun);}

	virtual ~MessageReceiverTask();

protected:
	// Return true if the stanza should be received.
  virtual bool WantsStanza(const buzz::XmlElement* stanza);
  // Process the received stanza.
  virtual void ReceiveStanza(const buzz::XmlElement* stanza);

  //virtual bool HandleStanza(const buzz::XmlElement* stanza);

private:
	void printAttributes(const buzz::XmlAttr* attr);
	void printChildren(const buzz::XmlChild* child, size_t index);
	void printElements(const buzz::XmlElement* child, size_t index);

	// fields
	bool printLogs_;
	sigslot::signal1<const Message&> messageEventHandler_;
};
 
