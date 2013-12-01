#pragma once

#include "libjingle\talk\base\sigslot.h"
#include "libjingle\talk\xmpp\xmppengine.h"
#include "libjingle\talk\xmpp\xmpppump.h"
#include "libjingle\talk\xmpp\presenceouttask.h"
#include "presencepushtask.h"

//-------------- additional classes/enums --------------------
enum STATUS_ENUM
	{
		OFFLINE = 0,
		ONLINE,
		FREE_FOR_CHAT,
		AWAY,
		XA,
		DND
	};

typedef void (*LogEvent)(void* context, string message);
typedef void (*LoginEvent)(void* context, buzz::XmppEngine::State state);
typedef void (*StatusEvent)(void* context, string jid, STATUS_ENUM status);

class MyClient : public sigslot::has_slots<>
{
public:
	

	
	MyClient(string hostname, int port, string jid, string password, bool useTls);
	~MyClient();

	void loginAsync();
	void login();
	
	// waits for login to happen. returns true of we successfully received login event. 
	// In case of timeout or error, returns false.
	bool waitLogin(int loginTimeout);

	bool setStatus(STATUS_ENUM status, string statusMessage);

	string resourceName(){return this->resourceName_;}
	void setResourceName(string resource){this->resourceName_ = resource;}

	void cancelLoginAsync();

	void setLogListener(LogEvent logListener, void* context);
	void setLoginListener(LoginEvent loginListener, void* context);
	void setOthersStatusListener(StatusEvent statusListener, void* context);

	bool isLoggedIn(){return isLoggedIn_;}

	void shutdown();

private:
	MyClient(MyClient&);
	MyClient& operator=(const MyClient&);

	static void loginAsyncHelper(PVOID args);
	void log(const char * data, int len);
	void connectionStateChanged(const buzz::XmppEngine::State state);
	void contactStatusChanged(const buzz::PresenceStatus& status);

	string resourceName_;
	string hostname_; 
	int port_;
	string jid_; 
	string password_;
	bool useTls_;
	volatile bool isLoggedIn_;//still not sure if c++ -volatile is helping to make memory barrier...

	HANDLE asyncThread_;				//TODO: windows dependency.
	volatile HANDLE loginSignalObject_;	//TODO: windows dependency.

	buzz::PresenceOutTask* presenceOutTask_;
	buzz::PresencePushTask* presencePushTask_;
	buzz::XmppClient* xmppClient_;//we don't manage it, it's in responsibiilty of XmppPump.
	buzz::PresenceStatus buzzStatus_;//we need to store status here instead of creating new one all the time as otherwise we have race condition between destructor and status sending...

	LogEvent logListener_;
	void* logContext_;

	LoginEvent loginListener_;
	void* loginCotext_;

	StatusEvent statusListener_;
	void* statusListenerContext_;
};

