// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the AISLINGIMLIBJINGLE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AISLINGIMLIBJINGLE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef AISLINGIMLIBJINGLE_EXPORTS
#define AISLINGIMLIBJINGLE_API __declspec(dllexport)
#else
#define AISLINGIMLIBJINGLE_API __declspec(dllimport)
#endif

// This class is exported from the aislingim-libjingle.dll
class AISLINGIMLIBJINGLE_API Caislingimlibjingle {
public:
	Caislingimlibjingle(void);
	// TODO: add your methods here.
};

extern AISLINGIMLIBJINGLE_API int naislingimlibjingle;

AISLINGIMLIBJINGLE_API int fnaislingimlibjingle(void);
