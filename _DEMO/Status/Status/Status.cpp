//
// Demo that illustrates all necessary steps to do except for SignIn to appear for other users as online user.
// Based on call application.
// After running this demo and specifying correct credentials, you should see tons of XML, 
// ending with presense information from all your online-contacts. 
// Check out other client, you should be online from here as well.
//

#include "stdafx.h"
//#include<windows.h> //if we can use c++11, we can make it crossplatform(i hope). Cannot include as we have redefinition in libjingle. stupid lamers

#include "libjingle\talk\xmpp\xmppengine.h"

#include "libjingle\talk\xmpp\presencestatus.h"
#include "libjingle\talk\xmpp\presenceouttask.h"

#include "Utils.h"	//additional utility method(s)
#include "signin.h" //wrapped class from SignIn demo (just to not focus on it here)

static bool volatile isLoggedIn = false;

void log(void*, string msg);
void statusConfigurationMethod(void*, buzz::XmppEngine::State state);

int _tmain(int argc, _TCHAR* argv[])
{
	//
	// input data.
	//
	int loginTimeout = 10000;//we wait 10 sec to connect to server. if not -- we try to reconnect.
	bool logInputOutput = true;

	string hostname;
	int port = 5222;//default
	string jidString;
	string passwordString;
	//Transport Layer Security. Google expects this to be enabled.
	bool useTls = false;

	//
	// Reading connection parameters.
	//
	read_connection_parameters(jidString, hostname, passwordString, useTls);
	
	// Configuring signin class
	SignIn signIn;
	signIn.setLoginListener(&statusConfigurationMethod, &signIn);
	
	if(logInputOutput)
		signIn.setLogListener(&log, nullptr);

	//
	// Trying to log in.
	//
	while(!isLoggedIn)
	{
		signIn.cancelLoginAsync();

		cout<<"Logging in ("<<loginTimeout/1000<<" sec timeout)..."<<endl;
		
		signIn.loginAsync(hostname, port, jidString, passwordString, useTls);
		Sleep(loginTimeout); //TODO: windows dependency.
	}

	signIn.joinLoginThread();
}

void log(void*, string msg)
{
	cout<<msg<<endl;
}

void statusConfigurationMethod(void* signInObj, buzz::XmppEngine::State state)
{
	SignIn* signIn = (SignIn*)signInObj;

	switch (state) 
		{
			case buzz::XmppEngine::STATE_START:
				cout<<"TRYING TO SIGN IN..."<<endl;
			  break;

			case buzz::XmppEngine::STATE_OPENING:
				cout<<"NEGOTIATING WITH SERVER..."<<endl;
				break;

			case buzz::XmppEngine::STATE_OPEN:
				{
					// Connection succeeded. Send your presence information. 
					// --------------- The main part of this demo BEGIN------------------
					isLoggedIn = true;
					cout<<"SIGNED IN."<<endl;
					
					buzz::PresenceStatus status;
					//
					// setting status itself
					//
					status.set_available(true);
					status.set_jid(buzz::Jid(signIn->jid()));
					status.set_show(buzz::PresenceStatus::SHOW_ONLINE);
					status.set_nick("nick");//resource?
					status.set_caps_node("caps node");//WTF?
					status.set_priority(1);
					status.set_status("Status Demo is Working.");
					status.set_sent_time("11:11");//WTF?

					//
					// setting capabilities
					//
					status.set_know_capabilities(true);
					status.set_pmuc_capability(true);
					status.set_voice_capability(false);
					status.set_video_capability(false);
					status.set_camera_capability(false);
					status.set_feedback_probation(false);//WTF?
					
					//
					//sending status message.
					//
					buzz::PresenceOutTask* presenceTask = new buzz::PresenceOutTask(signIn->xmppClient());
					presenceTask->Send(status);
					presenceTask->Start();//memory leak. Do we care? in normal app it will be in same class as sign in and noone will care.

					cout<<endl<<"  -----====SIGNED IN. STATUS/CAPABILITIES SPECIFIED. DEMO SUCCEEDED. NOW YOU SHOULD BE VISIBLE AS ONLINE.====-----"<<endl<<endl;
					// --------------- The main part of this demo END------------------
				}
			  break;
			case buzz::XmppEngine::STATE_CLOSED:
					cout<<"DISCONNECTED."<<endl;
					
					if(!isLoggedIn)
						cout<<"Will retry in few seconds, but consider checking login information."<<endl;

					isLoggedIn = false;
					break;

			default:
				cout<<"UNKNOWN STATE."<<(int)state<<endl;
		}
}

