/* Demo app that allows to login and see changing list of contacts with actual statuses.
	Used resources: 
		- "call" project from libjingle source.
		- http://msdn.microsoft.com/en-us/library/windows/desktop/ms686915(v=vs.85).aspx
*/

#include "stdafx.h"
#include <conio.h>

#include "Utils.h"	//additional utility method(s)
#include "MyClient.h"

void log(void*, string msg);
void loginStatusListener(void* , buzz::XmppEngine::State state);
void statusEvent(void* context, string jid, STATUS_ENUM status);

int _tmain(int argc, _TCHAR* argv[])
{
	//
	// input data.
	//
	int loginTimeout = 10000;//we wait 10 sec to connect to server. if not -- we try to reconnect.
	bool logInputOutput = false;

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

	//
	// Configuring client class
	//
	MyClient client(hostname, port, jidString, passwordString, useTls); 
	client.setLoginListener(&loginStatusListener, nullptr);
	client.setOthersStatusListener(&statusEvent, nullptr);
	client.setResourceName("RosterDemo");
	if(logInputOutput)
		client.setLogListener(log, nullptr);

	//
	// Trying to log in.
	//
	while(!client.isLoggedIn())
	{
		//cout<<"Trying to cancel login attempt..."<<endl;
		client.cancelLoginAsync();

		cout<<"Logging in ("<<loginTimeout/1000<<" sec timeout)..."<<endl;
		
		client.loginAsync();
		client.waitLogin(loginTimeout);//can use polling as well (just checking isLoggedIn method)
	}

	cout<<"Setting status...";
	string statusMessage = "Testing roster retrieval.";
	STATUS_ENUM status = ONLINE;
	if(!client.setStatus(status, statusMessage))
		cout<<"failed to set status."<<endl;
	else
		cout<<" done."<<endl;

	cout<<"     ----=== COMPLETE. NOW YOU CAN SEE ACTUAL CONTACTS STATUS. ===----"<<endl
		<<"PRESS ANY KEY TO SHUTDOWN THIS ALL STUFF."<<endl;

	_getch();

	//	client.shutdown();//TODO: because of some unknown to me reason, this does not work (causes access violation).
	return 0;
}

void log(void*, string msg)
{
	cout<<msg<<endl;
}

void loginStatusListener(void* clientObj, buzz::XmppEngine::State state)
{
	MyClient* client = (MyClient*)clientObj;

	switch (state) 
		{
			case buzz::XmppEngine::STATE_START:
				cout<<"TRYING TO SIGN IN..."<<endl;
			  break;

			case buzz::XmppEngine::STATE_OPENING:
				cout<<"NEGOTIATING WITH SERVER..."<<endl;
				break;

			case buzz::XmppEngine::STATE_OPEN:
					cout<<"SIGNED IN."<<endl;
				break;

			case buzz::XmppEngine::STATE_CLOSED:
				cout<<"DISCONNECTED."<<endl;
				break;

			default:
				cout<<"UNKNOWN STATE."<<(int)state<<endl;
		}
}

void statusEvent(void* context, string jid, STATUS_ENUM status)
{
	string statusString = "";
	switch(status)
	{
		case AWAY:
			statusString = "Away";
			break;
		case DND:
			statusString = "Do Not Disturb";
			break;
		case FREE_FOR_CHAT:
			statusString = "Free for chat";
			break;
		case OFFLINE:
			statusString = "Offline";
			break;
		case ONLINE:
			statusString = "Online";
			break;
		case XA:
			statusString = "Not Available";
			break;
		default:
			statusString = "unknown";
	}

	cout<<"ROSTER: "<<jid<<" :\t"<<statusString<<endl;
}

