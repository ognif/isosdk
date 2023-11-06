#ifndef __STDAFX_H__
#define __STDAFX_H__

#ifdef WIN32
#include <windows.h>
#include <limits>
#endif

#include <tchar.h>

#include "fx.h"

// Including IsoSDK
#include "IsoSDKBurningLib.h"

#include "resources.h"
#include "KString.h"

#ifdef WIN32
#	define FXtchar FXnchar
#	define utf2tcs utf2ncs
#elif defined MAC || defined LINUX
#	define FXtchar FXwchar
#	define utf2tcs utf2wcs
#endif

FXString SDK2FoxString(const char* pcText);
FXString SDK2FoxString(const wchar_t* pcText);
KString Fox2SDKString(const FXString &fxStr);

#if _MSC_VER >= 1400
	#if defined _M_IX86
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_IA64
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_X64
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#else
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#endif
#endif

#endif
