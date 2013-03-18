#include "stdafx.h"
#include <conio.h>

#include "Utils.h"

void read_connection_parameters(string& jid, string& hostname, string& password, bool& tls)
{
	//login
	cout<<"JID (login@domain): ";
	cin>> jid;

	//password
	cout<<"PASSWORD: ";
	cin>>password;

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
		tls = true;
	else if (choise == 'n')
		tls = false;
	else 
		tls = isTlsRecommendedByRST ? true : false;
}