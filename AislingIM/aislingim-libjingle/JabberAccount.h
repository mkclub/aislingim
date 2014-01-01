#ifndef AISLINGIM_JABBER_ACCOUNT_H
#define AISLINGIM_JABBER_ACCOUNT_H

#include "definitions.h"
#include "Message.h"
#include <string>
#include <memory>

namespace aislingim_libjingle
{
	struct JabberAccountImp;

	enum AISLINGIMLIBJINGLE_API STATUS_ENUM
	{
		OFFLINE = 0,
		ONLINE,
		FREE_FOR_CHAT,
		AWAY,
		XA,
		DND
	};

	enum AISLINGIMLIBJINGLE_API LOG_MESSAGE_TYPE_ENUM
	{
		INCOMING,
		OUTGOING,
		DEBUG //the message about application execution process.
	};

	typedef AISLINGIMLIBJINGLE_API void (*LogEvent)(void* context, const std::string& message, LOG_MESSAGE_TYPE_ENUM messageType);
	typedef AISLINGIMLIBJINGLE_API void (*MyStatusEvent)(void* context, STATUS_ENUM status);
	typedef AISLINGIMLIBJINGLE_API void (*StatusEvent)(void* context, const std::string& jid, STATUS_ENUM status);
	typedef AISLINGIMLIBJINGLE_API void (*MessageEvent)(void* context, const Message& message);

	class AISLINGIMLIBJINGLE_API JabberAccount
	{
	private:
		std::shared_ptr<JabberAccountImp> pimpl_;//hidden state
		
		JabberAccount(const JabberAccount& that);//not implemented by design;
		JabberAccount& operator=(const JabberAccount& that);//not implemented by design;

		// private methods
		

	public:
		
		// constructors/destructors
		JabberAccount(const std::string& hostname, PORT_TYPE port, const std::string& jid, const std::string& password, bool useTls, const std::string& resourceName);
		~JabberAccount(void);
		
		// methods
		void login();
		void logout();


		// properties
		bool loggedIn();
		STATUS_ENUM status();
		bool setStatus(STATUS_ENUM status, const std::string& statusMessage);//sets status and status message. returns whether operation was successfull.

		//events
		void setLogListener(LogEvent logListener, void* context);
		void setMyStatusListener(MyStatusEvent statusListener, void* context);
		void setContactStatusListener(StatusEvent statusListener, void* context);
		void setMessageListener(MessageEvent messageListener, void* context);
	};
}
#endif

