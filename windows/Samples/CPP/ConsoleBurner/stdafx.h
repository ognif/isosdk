// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#include <iostream>
#include <tchar.h>
#include <string>
#include <vector>

#ifdef WIN32
	#include <windows.h>
	#include <atlbase.h>
#endif

#include "IsoSDKBurningLib.h"
#include "synclib.h"

#ifdef _UNICODE
#	define _tcout std::wcout
#	define tstring std::wstring
#else
#	define _tcout std::cout
#	define tstring std::string
#endif

// TODO: reference additional headers your program requires here
