/*
 Flat login app that logins with specified login and password to the specified server.
 Used resources: 
  - Login sequence as it is described on https://developers.google.com/talk/libjingle/login
  - "call" project from libjingle source.
*/

#include "stdafx.h"
#include <conio.h>

#include "libjingle\talk\base\ssladapter.h"
#include "libjingle\talk\xmpp\xmppthread.h"
#include "libjingle\talk\base\win32socketserver.h"
#include "libjingle\talk\xmpp\xmppauth.h"

using namespace std;
using namespace buzz;

///
/// Class that is used to react on log in events from server 
///
class StatePrinter : public sigslot::has_slots<>
{
public:
	void PrintState(buzz::XmppEngine::State state)
	{
		switch (state) 
		{
			case buzz::XmppEngine::STATE_START:
			  // Attempting sign in.
				cout<<"STATE PRINTER: TRYING TO SIGN IN."<<endl;
			  break;
			case buzz::XmppEngine::STATE_OPENING:
			  // Negotiating with server.
				cout<<"STATE PRINTER: NEGOTIATING WITH SERVER."<<endl;
			  break;
			case buzz::XmppEngine::STATE_OPEN:
			  // Connection succeeded. Send your presence information.
			  // and sign up to receive presence notifications.
				cout<<endl<<"  -----====STATE PRINTER: SIGNED IN. DEMO SUCCEEDED.====-----"<<endl<<endl;
				
				talk_base::Thread::Current()->Quit(); //in normal apps here we should do all negotiation.

			  break;
			case buzz::XmppEngine::STATE_CLOSED:
			  // Connection ended. 
				cout<<"STATE PRINTER: DISCONNECTED."<<endl;
				talk_base::Thread::Current()->Quit();
			  break;

			default:
				cout<<"STATE PRINTER: UNKNOWN STATE."<<endl;
		}
	}

	void PrintInput(const char * data, int len) 
	{
		string str(data, data+len);
		cout<<"STATE PRINTER: INPUT>> "<<str<<endl;
	}

	void PrintOutput(const char * data, int len)
	{
		string str(data, data+len);
		cout<<"STATE PRINTER: OUTPUT<< "<<str<<endl;
	}
};

void read_connection_parameters(string& jid, string& hostname, string& password, buzz::TlsOptions& tls);

int _tmain(int argc, _TCHAR* argv[])
{
	//
	// input data.
	//
	bool logInputOutput = true;
	string hostname;
	int port = 5222;//default
	string jidString;
	string passwordString;
	buzz::TlsOptions tls = buzz::TLS_DISABLED;//Transport Layer Security. Google expects this to be enabled.
	
	//
	// Reading connection parameters.
	//
	read_connection_parameters(jidString, hostname, passwordString, tls);

	cout<<"Connecting to "<<hostname<<":"<<port<<(tls == buzz::TLS_DISABLED ? " (NO TLS)" : " (TLS)") <<" with login "<<jidString<<endl;

	cout<<"Initializing..."<<endl;

	// ========= 1.  Set up the crypto subsystem. =========
	talk_base::InitializeSSL();

	//
	// ========= 2. Configuring connection =========
	//

	//setting username
	buzz::Jid jid = buzz::Jid(jidString);

	//setting password
	talk_base::InsecureCryptStringImpl pass;
	pass.password() = passwordString;

	// Connection settings
	buzz::XmppClientSettings xcs;
	xcs.set_user(jid.node());
	xcs.set_resource("test");//name of resource we login from
	xcs.set_host(jid.domain());
	xcs.set_allow_plain(false);
	xcs.set_use_tls(tls);
	xcs.set_pass(talk_base::CryptString(pass));
	//xcs.set_auth_token(buzz::AUTH_MECHANISM_OAUTH2, oauth_token); //if we want to use OAuth2, we can setup it here.
	xcs.set_server(talk_base::SocketAddress(hostname, port));

	// ========= 3. Register to receive signals from the XMPP pump to track sign in progress. =========
	XmppPump pump;
	StatePrinter statePrinter; //our class that is used to print login state information to console.
	pump.client()->SignalStateChange.connect(&statePrinter, &StatePrinter::PrintState);

	// logging of input/output
	if(logInputOutput)
	{
		pump.client()->SignalLogInput.connect(&statePrinter, &StatePrinter::PrintInput);
		pump.client()->SignalLogOutput.connect(&statePrinter, &StatePrinter::PrintOutput);
	}

	//
	// LOGGING IN
	//
	
	// ========= 4. Create the signaling thread. =========
	// AutoThread captures the current OS thread and sets it to be
	// ThreadManager::CurrentThread, which will be called and used by SessionManager 
	//talk_base::PhysicalSocketServer ss;
	//talk_base::AutoThread main_thread(&ss);
	talk_base::Win32Thread w32_thread;
	talk_base::ThreadManager::Instance()->SetCurrentThread(&w32_thread);
	talk_base::Thread* main_thread = talk_base::Thread::Current();
	
	// ========= 5. Send the sign in request. =========
	cout<<"Logging in... "<<endl
		<<"(may take some time or even hang at all. If not working -- restart app.)"<<endl;
	
	pump.DoLogin(xcs, new XmppSocket(buzz::TLS_REQUIRED), new XmppAuth());

	// ========= 6. Start the thread and run indefinitely. =========
	main_thread->Run();
	
	//
	// DISCONNECTING
	//

	pump.DoDisconnect();


	cout<<endl<<"Done. Press any key to exit."<<endl;
	_getch();
	return 0;
}

void read_connection_parameters(string& jid, string& hostname, string& password, buzz::TlsOptions& tls)
{
	//login
	cout<<"JID (login@domain): ";
	cin>> jid;

	//server
	string offeredHostname = jid.substr(jid.find("@")+1);
	//ok, there are some known servers...
	if(offeredHostname == "gmail.com" || offeredHostname == "googlemail.com")
		offeredHostname = "talk.google.com";
	
	cout<<"Use "<<offeredHostname<<" as server [Y/n]? ";

	char choise = _getch(); 
	cout<<choise<<endl;
	choise |= 32; //ToLower(). Anyways we care only about Y or N.

	if(choise != 'n')
	{
		hostname = offeredHostname;
	}
	else
	{
		cout<<"SERVER NAME: ";
		cin>>hostname;
	}

	//Setting up TLS
	bool isTlsRecommendedByRST = hostname == "talk.google.com";
	cout<<"USE Transport Layer Security (TLS)"<< (isTlsRecommendedByRST ? "[Y/n]" : "[y/N]") <<"? ";
	choise = _getch();
	cout<<choise<<endl;
	choise |= 32; //ToLower() again.
	if(choise == 'y')
		tls = buzz::TLS_ENABLED;
	else if (choise == 'n')
		tls = buzz::TLS_DISABLED;
	else 
		tls = isTlsRecommendedByRST ? buzz::TLS_ENABLED : buzz::TLS_DISABLED;

	//password
	cout<<"PASSWORD: ";
	cin>>password;
}