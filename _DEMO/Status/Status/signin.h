#include "stdafx.h"
#pragma once
//#include <Windows.h>

#include "libjingle\talk\base\sigslot.h"
#include "libjingle\talk\xmpp\xmppengine.h"
#include "libjingle\talk\xmpp\xmpppump.h"

using namespace buzz;

typedef void (*LogEvent)(void* context, string message);
typedef void (*LoginEvent)(void* context, buzz::XmppEngine::State state);

class SignIn : public sigslot::has_slots<>
{
public:
	SignIn();
	~SignIn();

	void loginAsync(string hostname, int port, string jidString, string password, bool useTls);
	void login(string hostname, int port, string jidString, string password, bool useTls);

	void cancelLoginAsync();

	void setLogListener(LogEvent logListener, void* context);
	void setLoginListener(LoginEvent loginListener, void* context);

	void joinLoginThread();
	void shutdown();

	string jid(){return jid_;}

	buzz::XmppClient* xmppClient(){return pump_.client();}

	friend void loginThreaded(PVOID args);

private:
	SignIn(SignIn&);
	SignIn& operator=(const SignIn&);

	void log(const char * data, int len);
	void connectionStateChanged(buzz::XmppEngine::State state);
		
	XmppPump pump_;

	HANDLE asyncThread_;
	string hostname_; 
	int port_;
	string jid_; 
	string password_;
	bool useTls_;

	LogEvent logListener_;
	void* logContext_;

	LoginEvent loginListener_;
	void* loginCotext_;
};

