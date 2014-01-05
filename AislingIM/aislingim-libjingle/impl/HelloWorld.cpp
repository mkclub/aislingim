#include "stdafx.h"
#include "..\HelloWorld.h"
#include "libjingle\talk\base\ssladapter.h"
#include "libjingle\talk\xmpp\xmppthread.h"
#include "libjingle\talk\base\win32socketserver.h"
#include "libjingle\talk\xmpp\xmppauth.h"

using namespace std;
using namespace buzz;

std::string hello(std::string name)
{
	return string("HELLo, ")+name;
}