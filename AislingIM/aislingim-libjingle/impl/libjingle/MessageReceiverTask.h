#pragma once

#include "talk\xmpp\receivetask.h"
#include "..\Message.h"

namespace aislingim_libjingle
{
	class MessageReceiverTask : public buzz::ReceiveTask
	{
	public:
		MessageReceiverTask(XmppTaskParentInterface* parent);
	
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
		sigslot::signal1<const Message&> messageEventHandler_;
	};
}
