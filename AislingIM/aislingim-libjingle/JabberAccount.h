#ifndef AISLINGIM_JABBER_ACCOUNT_H
#define AISLINGIM_JABBER_ACCOUNT_H

#include "definitions.h"
#include "Message.h"
#include <string>
#include <memory>

namespace aislingim_libjingle
{
	// forward declaration of internal class that holds state and interface-independent methods)
	struct JabberAccountImp;

	// enumeration that defines possible user state.
	enum AISLINGIMLIBJINGLE_API STATUS_ENUM
	{
		OFFLINE = 0,
		ONLINE,
		FREE_FOR_CHAT,
		AWAY,
		XA,
		DND
	};

	// enumeration that defines possible types of log messages.
	enum AISLINGIMLIBJINGLE_API LOG_MESSAGE_TYPE_ENUM
	{
		INCOMING,
		OUTGOING,
		DEBUG //the message about application execution process.
	};

	// function pointers declarations necessary for event handling
	typedef AISLINGIMLIBJINGLE_API void (*LogEvent)(void* context, const std::string& message, LOG_MESSAGE_TYPE_ENUM messageType);
	typedef AISLINGIMLIBJINGLE_API void (*MyStatusEvent)(void* context, STATUS_ENUM status);
	typedef AISLINGIMLIBJINGLE_API void (*StatusEvent)(void* context, const std::string& jid, STATUS_ENUM status);
	typedef AISLINGIMLIBJINGLE_API void (*MessageEvent)(void* context, const Message& message);

	// Jabber account handling class.
	class AISLINGIMLIBJINGLE_API JabberAccount
	{
	private:
	#pragma warning(push)
	#pragma warning(disable: 4251)
		std::shared_ptr<JabberAccountImp> pimpl_;//hidden state
	#pragma warning(pop)
		JabberAccount(const JabberAccount& that);//not implemented by design;
		JabberAccount& operator=(const JabberAccount& that);//not implemented by design;

	public:
		//
		// ---------------------- CONSTRUCTORS ---------------------------
		//
		JabberAccount(const std::string& hostname, PORT_TYPE port, const std::string& jid, const std::string& password, bool useTls, const std::string& resourceName);
		~JabberAccount(void);
		
		//
		// ---------------------- METHODS ---------------------------
		//

		// establishes connection to the server with specified credentials 
		// and blocks the thread this method was invoked on for communication with the server.
		// As the thread will be blocked during the whole connection interval, this method 
		// should be invoked in the separate thread.
		void run();
		
		// closes connection and releases all resources. After execution of this method, 
		// thread captured by <see cref="start"> method is released. 
		void close();

		//
		// ---------------------- PROPERTIES ---------------------------
		//

		// Specifies whether this account if connected (true) or disconnected (false).
		bool loggedIn();

		// Specifies the user status visible to others.
		STATUS_ENUM status();

		// sets user status to the specified value and allows to specify status message.
		// returns whether operation was successfull.
		bool setStatus(STATUS_ENUM status, const std::string& statusMessage);


		//
		// ---------------------- EVENTS ---------------------------
		//

		// Subscribes provided method to be invoked whenever a log message is generated.
		void setLogListener(LogEvent logListener, void* context);

		// Subscribes provided method to be invoked whenever current user status changes.
		void setMyStatusListener(MyStatusEvent statusListener, void* context);

		// Subscribes provided method to be invoked whenever status of any contact changes.
		void setContactStatusListener(StatusEvent statusListener, void* context);

		// Subscribes provided method to be invoked whenever any message is received.
		void setMessageListener(MessageEvent messageListener, void* context);
	};
}

#endif

