// aislingim-libjingle.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "aislingim-libjingle.h"


// This is an example of an exported variable
AISLINGIMLIBJINGLE_API int naislingimlibjingle=0;

// This is an example of an exported function.
AISLINGIMLIBJINGLE_API int fnaislingimlibjingle(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see aislingim-libjingle.h for the class definition
Caislingimlibjingle::Caislingimlibjingle()
{
	return;
}

