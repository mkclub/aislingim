#include "StdAfx.h"

#include "MyClient.h"

#include "libjingle\talk\base\ssladapter.h"
#include "libjingle\talk\xmpp\xmppthread.h"
#include "libjingle\talk\base\win32socketserver.h"
#include "libjingle\talk\xmpp\xmppauth.h"
#include "libjingle\talk\xmpp\presencestatus.h"

MyClient::MyClient(string hostname, int port, string jid, string password, bool useTls):
hostname_(hostname), port_(port), jid_(jid), password_(password), useTls_(useTls_),isLoggedIn_(false),
	asyncThread_(nullptr), logListener_(nullptr), logContext_(nullptr), loginListener_(nullptr), loginCotext_(nullptr),statusListener_(nullptr), statusListenerContext_(nullptr),
	loginSignalObject_(nullptr),presenceOutTask_(nullptr),presencePushTask_(nullptr),main_thread_(nullptr),messageReceiverTask_(nullptr),
	messageListenerContext_(nullptr),messageListener_(nullptr)
{
}

MyClient::~MyClient()
{
	if(isLoggedIn_)
		shutdown();

	if(loginSignalObject_ != nullptr)
	{
		CloseHandle(loginSignalObject_);
		loginSignalObject_ = nullptr;
	}

	//TODO: why we get access violation here? maybe we should not delete them?
	//delete presenceOutTask_;
	//delete presencePushTask_;
	//delete messageReceiverTask_;
}

void MyClient::setLogListener(LogEvent logListener, void* context)
{
	logListener_ = logListener;
	logContext_ = context;
}


void MyClient::setLoginListener(LoginEvent loginListener, void* context)
{
	loginListener_ = loginListener;
	loginCotext_ = context;
}

void MyClient::setOthersStatusListener(StatusEvent statusListener, void* context)
{
	statusListener_ = statusListener;
	statusListenerContext_ = context;
}

void MyClient::setMessageListener(MessageEvent messageListener, void* context)
{
	messageListener_ = messageListener;
	messageListenerContext_ = context;
}

//----------------------------------------LOGIN STUFF-----------------------------------------------------

void MyClient::loginAsync()
{
	if(asyncThread_ != nullptr)
		return;//won't do anything if we're running already.

	//
	// Starting signalling stuff.
	//
	isLoggedIn_ = false;
	if(loginSignalObject_ != nullptr)
		CloseHandle(loginSignalObject_);

	//cout<<"Creating event..."<<" On thread "<<GetCurrentThreadId()<<endl;
	loginSignalObject_ = CreateEvent(NULL, TRUE, FALSE, TEXT("MyLoginEvent")); 

	if(loginSignalObject_ == nullptr)
		cout<<"FAILED TO CREATE EVENT!"<<endl;//who cares about this in demo?
	//else
		//cout<<"Created event "<<(int)loginSignalObject_<<" On thread "<<GetCurrentThreadId()<<endl;

	DWORD ThreadID;																					//TODO: windows dependency.
	asyncThread_ = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)loginAsyncHelper, this,0,&ThreadID);//TODO: windows dependency.
}

///
/// Helper method that runs login synchronously.
///
void MyClient::loginAsyncHelper(PVOID args)
{
	MyClient* _this = (MyClient*)args;
	_this->login();
}


void MyClient::login()
{
	//
	// ========= 1. Configuring connection =========
	//
	buzz::TlsOptions tls =  useTls_ ? buzz::TLS_ENABLED : buzz::TLS_DISABLED;

	//setting username
	buzz::Jid jid = buzz::Jid(jid_);

	//setting password
	talk_base::InsecureCryptStringImpl pass;
	pass.password() = password_;

	// Connection settings
	buzz::XmppClientSettings xcs;
	xcs.set_user(jid.node());
	xcs.set_resource(resourceName_);//name of resource we login from
	xcs.set_host(jid.domain());
	xcs.set_allow_plain(false);
	xcs.set_use_tls(tls);
	xcs.set_pass(talk_base::CryptString(pass));
	//xcs.set_auth_token(buzz::AUTH_MECHANISM_OAUTH2, oauth_token); //if we want to use OAuth2, we can setup it here.
	xcs.set_server(talk_base::SocketAddress(hostname_, port_));

	// ========= 2. Register to receive signals from the XMPP pump to track sign in progress. =========
	XmppPump pump;
	xmppClient_ = pump.client();//we will need this client in future.
	pump.client()->SignalStateChange.connect(this, &MyClient::connectionStateChanged);
	pump.client()->SignalLogInput.connect(this, &MyClient::log);
	pump.client()->SignalLogOutput.connect(this, &MyClient::log);

	
	//
	// LOGGING IN
	//
	// ========= 3. Create the signaling thread. =========
	talk_base::Win32Thread w32_thread;									//TODO: windows dependency.
	talk_base::ThreadManager::Instance()->SetCurrentThread(&w32_thread);//TODO: windows dependency.
	main_thread_ = talk_base::Thread::Current();		//TODO: windows dependency.
	
	// ========= 4. Send the sign in request. =========
	//cout<<"Logging in... "<<endl;
	

	pump.DoLogin(xcs, new XmppSocket(buzz::TLS_REQUIRED), new XmppAuth());

	// ========= 6. Start the thread and run indefinitely. =========
	main_thread_->Run();
	
	//
	// DISCONNECTING
	//
	pump.DoDisconnect();
}


void MyClient::cancelLoginAsync()
{	//TODO: windows dependency. everywhere.
	if(asyncThread_ != nullptr)
	{
		// looks like we need some minimum delay or sync, 
		// because if terminateThread happens at them moment 
		// when we're closing handle... something terrible happens.
		// was fucking hard to detect and I'm still not sure that this is the case...
		// kids, never NEVER terminate threads, windows doesn't like it.
		Sleep(100);
		//cout<<"TERMINATING THREAD..."<<endl;
		if(TerminateThread(asyncThread_, 1) == 0)//TODO: NOT NICE, but who cares? btw, on WinXP leads to resource leak http://msdn.microsoft.com/en-us/library/windows/desktop/ms686717(v=vs.85).aspx
			cout<<"FAILED TO TERMINATE THREAD."<<endl;
		//else
		//	cout<<"TERMINATED THREAD SUCCESSFULLY"<<endl;
		asyncThread_ = nullptr;
	}
}

bool MyClient::waitLogin(int loginTimeout)
{
	if(loginSignalObject_ == nullptr || isLoggedIn_)
		return isLoggedIn_;// either we did not started login yet or already logged in.

	//cout<<"== WAITING ON "<<(int)loginSignalObject_<<" On thread "<<GetCurrentThreadId()<<endl;
	DWORD res = WaitForSingleObject(loginSignalObject_,loginTimeout);//TODO: windows dependency.
	//cout<<"== WAITING FINISHED."<<" On thread "<<GetCurrentThreadId()<<endl;

	return res == WAIT_OBJECT_0;//TODO: windows dependency.
}

//----------------------------------OTHER METHODS ---------------------------------------

bool MyClient::setStatus(STATUS_ENUM status, string statusMessage)
{
	if(!isLoggedIn_)
		return false; //we did not login yet.

	//
	// Creating status object
	//
	buzzStatus_.set_available(true);
	buzzStatus_.set_jid(buzz::Jid(this->jid_));
	switch(status)
	{
		case OFFLINE:
			buzzStatus_.set_show(buzz::PresenceStatus::SHOW_OFFLINE);
			break;
		case ONLINE:
			buzzStatus_.set_show(buzz::PresenceStatus::SHOW_ONLINE);
			break;
		case FREE_FOR_CHAT:
			buzzStatus_.set_show(buzz::PresenceStatus::SHOW_CHAT);
			break;
		case AWAY:
			buzzStatus_.set_show(buzz::PresenceStatus::SHOW_AWAY);
			break;
		case XA:
			buzzStatus_.set_show(buzz::PresenceStatus::SHOW_XA);
			break;
		case DND:
			buzzStatus_.set_show(buzz::PresenceStatus::SHOW_DND);
			break;
	}
	
	//TODO: decide on capabilities.
	buzzStatus_.set_nick("nick");//WTF? noone sets this. (maybe for MUC?)
	buzzStatus_.set_caps_node("capsNode");//WTF?
	buzzStatus_.set_priority(10);
	buzzStatus_.set_status(statusMessage);
	buzzStatus_.set_sent_time("11:11");//WTF?
	buzzStatus_.set_version("1.1");//WTF?
	
	//
	// setting capabilities
	//
	buzzStatus_.set_know_capabilities(true);
	buzzStatus_.set_pmuc_capability(true);
	buzzStatus_.set_voice_capability(false);
	buzzStatus_.set_video_capability(false);
	buzzStatus_.set_camera_capability(false);
	buzzStatus_.set_feedback_probation(false);//WTF?

	if(presenceOutTask_ == nullptr)
		cout<<"PRESENCE TASK IS NULL, what is unexpected."<<endl;
	else
		presenceOutTask_->Send(buzzStatus_);

	return true;
}

void MyClient::shutdown()
{
	if(!isLoggedIn_)
		return;

	if(main_thread_ != nullptr)
	{
		main_thread_->Quit();
		isLoggedIn_ = false;
	}
	else
		cout<<"Failed to shutdown: application is not completely initialized."<<endl;
}

//-------------------------------------------------PRIVATE FUNCTIONS---------------------------------

void MyClient::log(const char * data, int len)
{
	if(logListener_ != nullptr)
		logListener_(logContext_, string(data,len));//TODO: do we construct string correctly here?
}

void MyClient::connectionStateChanged(buzz::XmppEngine::State state)
{
	//
	// doing some important stuff that needs/can be done on connected state
	//
	if(state == buzz::XmppEngine::STATE_OPEN)
	{
		isLoggedIn_ = true;

		if(presenceOutTask_ != nullptr)
		{
			delete presenceOutTask_;
			presenceOutTask_ = nullptr;
		}

		if(xmppClient_ == nullptr)
			cout<<"XMPP CLIENT IS NULL, while it was expected to be set! Something is wrong!"<<endl;
		else
		{
			//
			// task that publishes our status.
			//
			presenceOutTask_ = new buzz::PresenceOutTask(xmppClient_);
			presenceOutTask_->Start();

			//
			// task to get statuses of others.
			//
			presencePushTask_ = new buzz::PresencePushTask(xmppClient_);
			presencePushTask_->SignalStatusUpdate.connect(this, &MyClient::contactStatusChanged);
			presencePushTask_->Start();

			//
			// Task to receive incoming messages
			//
			bool printReceivedMessageProcess = false; // determines if we print to console how we process messages.
			messageReceiverTask_ = new MessageReceiverTask(xmppClient_, printReceivedMessageProcess);
			messageReceiverTask_->onMessage(this, &MyClient::messageReceived);
			messageReceiverTask_->Start();
		}
	}
	
	//
	// Signalling if we are connected or disconnected
	//
	if(state == buzz::XmppEngine::STATE_OPEN ||
		state == buzz::XmppEngine::STATE_CLOSED)
	{
		//cout<<"SIGNALLING AND CLOSING HANDLE. STATE = " <<state<<endl;
		
		//saving our handle here as we're going to signal on it now and noone knows what will happen to original one...
		HANDLE ourHandle = loginSignalObject_;			//TODO: windows dependency.
		loginSignalObject_ = nullptr;

		if(ourHandle != nullptr)
		{
			//cout<<"SIGNALLING... "<<(int)ourHandle<<" On thread "<<GetCurrentThreadId()<<endl;
			if(!SetEvent(ourHandle))						//TODO: windows dependency.
				cout<<"FAILED TO SET EVENT!";

			//cout<<"DONE. CLOSING..."<<(int)ourHandle<<endl;
			if(!CloseHandle(ourHandle))						//TODO: windows dependency.
				cout<<"FAILED TO CLOSE HANDLE!";

			//cout<<"HANLDE CLOSED."<<endl;
		}
	}

	//
	// Forwarding event.
	//
	if(loginListener_ != nullptr)
		loginListener_(loginCotext_, state);

}

void MyClient::contactStatusChanged(const buzz::PresenceStatus& status)
{
	//cout<<status.jid().node()<<"@"<<status.jid().domain()<<"/"<<status.jid().resource()
	//	<<"(version="<<status.version()<<", priority="<<status.priority()<<")"
	//	<<" is "<<status.ShowStatus()<<endl;

	if(statusListener_ == nullptr)
		return;

	//
	// Preparing arguments
	//
	string jid = status.jid().node() + "@" + status.jid().domain() +"/" +status.jid().resource()+"("+to_string((long long)status.priority())+")";
	STATUS_ENUM statusEnum = OFFLINE;

	// TODO: all these enums... we should decice what to do with them or create some helper methods...
	switch(status.show())
	{
		case buzz::PresenceStatus::SHOW_OFFLINE:
			statusEnum = OFFLINE;
			break;
		case buzz::PresenceStatus::SHOW_ONLINE:
			statusEnum = ONLINE;
			break;
		case buzz::PresenceStatus::SHOW_AWAY:
			statusEnum = AWAY;
			break;
		case buzz::PresenceStatus::SHOW_CHAT:
			statusEnum = FREE_FOR_CHAT;
			break;
		case buzz::PresenceStatus::SHOW_DND:
			statusEnum = DND;
			break;
		case buzz::PresenceStatus::SHOW_XA:
			statusEnum = XA;
			break;
		default:
			cout<<"UNEXPECTED STATUS. Cannot convert:"<<status.show()<<" interpreted as "<<status.status()<<endl;
	}

	//
	// Sending event
	// 
	statusListener_(statusListenerContext_,jid, statusEnum);
}

void MyClient::messageReceived(const Message& message)
{
	if(messageListener_ != nullptr)
		messageListener_(messageListenerContext_, message);
}