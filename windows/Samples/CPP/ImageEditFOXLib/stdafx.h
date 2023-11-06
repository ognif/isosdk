#ifndef __STDAFX_H__
#define __STDAFX_H__

#ifdef WIN32
	#pragma warning(push)
	#pragma warning(disable:4005)
	#include <windows.h>
	#include <limits>
	#pragma warning(pop)
#endif

#include <tchar.h>

#include "fx.h"

#include "IsoSDKBurningLib.h"

#include "resources.h"
#include "KString.h"

FXString SDK2FoxString(const char* pcText);
FXString SDK2FoxString(const wchar_t* pcText);
KString Fox2SDKString(const FXString &fxStr);

#ifdef WIN32
#	define FXtchar FXnchar
#	define utf2tcs utf2ncs
#elif defined MAC || defined LINUX
#	define FXtchar FXwchar
#	define utf2tcs utf2wcs
#endif

#ifndef _MSC_VER
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <time.h>

	typedef time_t	__time64_t;
	typedef struct stat __stat64;

	#define _time64 time
	#define _gmtime64 gmtime
	#define _localtime64 localtime
	#define _fstat64 fstat
	#define _stat64 stat
#endif

/*	inline void* IntToPvoid(int32 val)
	{
		return (void*)val;
	}*/

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
