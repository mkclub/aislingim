#include "StdAfx.h"

#include "libjingle\talk\base\ssladapter.h"
#include "libjingle\talk\xmpp\xmppthread.h"
#include "libjingle\talk\base\win32socketserver.h"
#include "libjingle\talk\xmpp\xmppauth.h"

#include "signin.h"


SignIn::SignIn():asyncThread_(nullptr),hostname_(""),port_(0),jid_(""),password_(""),useTls_(false)
{
	talk_base::InitializeSSL();//TODO: don't know if we can do this every time or we have to do it once...
}


SignIn::~SignIn()
{
	shutdown();
	cancelLoginAsync();
}


void SignIn::loginAsync(string hostname, int port, string jidString, string password, bool useTls)
{
	if(asyncThread_ != nullptr)
		return;//won't do anything if we're running already.

	hostname_ = hostname;
	port_ = port;
	jid_ = jidString;
	password_ = password;
	useTls_ = useTls;

	DWORD ThreadID;
	asyncThread_ = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)loginThreaded, this,0,&ThreadID);//TODO: windows dependency.
}

///
/// Helper method that runs login synchronously.
///
void loginThreaded(PVOID args)
{
	SignIn* _this = (SignIn*)args;
	_this->login(_this->hostname_, _this->port_, _this->jid_, _this->password_, _this->useTls_);
}


void SignIn::login(string hostname, int port, string jidString, string password, bool useTls)
{
	//if someone calls us async, this will cause stupid work, but for the sake of consistency...
	hostname_ = hostname;
	port_ = port;
	jid_ = jidString;
	password_ = password;
	useTls_ = useTls;

	//
	// ========= 2. Configuring connection =========
	//
	buzz::TlsOptions tls =  useTls ? buzz::TLS_ENABLED : buzz::TLS_DISABLED;

	//setting username
	buzz::Jid jid = buzz::Jid(jid_);

	//setting password
	talk_base::InsecureCryptStringImpl pass;
	pass.password() = password_;

	// Connection settings
	buzz::XmppClientSettings xcs;
	xcs.set_user(jid.node());
	xcs.set_resource("status");//name of resource we login from
	xcs.set_host(jid.domain());
	xcs.set_allow_plain(false);
	xcs.set_use_tls(tls);
	xcs.set_pass(talk_base::CryptString(pass));
	//xcs.set_auth_token(buzz::AUTH_MECHANISM_OAUTH2, oauth_token); //if we want to use OAuth2, we can setup it here.
	xcs.set_server(talk_base::SocketAddress(hostname, port));

	// ========= 3. Register to receive signals from the XMPP pump to track sign in progress. =========
	pump_.client()->SignalStateChange.connect(this, &SignIn::connectionStateChanged);
	pump_.client()->SignalLogInput.connect(this, &SignIn::log);
	pump_.client()->SignalLogOutput.connect(this, &SignIn::log);

	//
	// LOGGING IN
	//
	
	// ========= 4. Create the signaling thread. =========
	talk_base::Win32Thread w32_thread;									//TODO: windows dependency.
	talk_base::ThreadManager::Instance()->SetCurrentThread(&w32_thread);//TODO: windows dependency.
	talk_base::Thread* main_thread = talk_base::Thread::Current();		//TODO: windows dependency.
	
	// ========= 5. Send the sign in request. =========
	//cout<<"Logging in... "<<endl;
			
	pump_.DoLogin(xcs, new XmppSocket(buzz::TLS_REQUIRED), new XmppAuth());

	// ========= 6. Start the thread and run indefinitely. =========
	main_thread->Run();
	
	//
	// DISCONNECTING
	//
	pump_.DoDisconnect();
}


void SignIn::cancelLoginAsync()
{
	if(asyncThread_ != nullptr)
	{
		if(TerminateThread(asyncThread_, 1) == 0)//TODO: NOT NICE, but who cares? btw, on WinXP leads to resource leak http://msdn.microsoft.com/en-us/library/windows/desktop/ms686717(v=vs.85).aspx
			cout<<"FAILED TO TERMINATE THREAD."<<endl;

		asyncThread_ = nullptr;
	}
}


void SignIn::shutdown()
{
	talk_base::Thread::Current()->Quit();
}


void SignIn::joinLoginThread()
{
	if(asyncThread_ == nullptr)
		return;

	WaitForSingleObject(asyncThread_, INFINITE);//TODO: windows dependency.
}


void SignIn::log(const char * data, int len)
{
	if(logListener_ != nullptr)
		logListener_(logContext_, string(data,len));//TODO: do we construct string correctly here?
}


void SignIn::connectionStateChanged(buzz::XmppEngine::State state)
{
	if(loginListener_ != nullptr)
		loginListener_(loginCotext_, state);
}


void SignIn::setLogListener(LogEvent logListener, void* context)
{
	logListener_ = logListener;
	logContext_ = context;
}


void SignIn::setLoginListener(LoginEvent loginListener, void* context)
{
	loginListener_ = loginListener;
	loginCotext_ = context;
}
