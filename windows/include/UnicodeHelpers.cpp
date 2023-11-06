//// Windows-Version
#if _MSC_VER >= 1300

// = 0x400		-> Damit wir kompatibel sind.
#	undef WINVER
#	define WINVER			0x0400

// >= 0x0502	-> Windows Server 2003 family
// >= 0x0501	-> Windows XP
// >= 0x0500	-> Windows 2000
// >= 0x0400	-> Windows NT 4.0
#	undef _WIN32_WINNT
#	define _WIN32_WINNT		0x0500

// = 0x0500		-> Windows NT based
// = 0x0490		-> Windows Me
// >= 0x0410 	-> Windows 98
#	undef _WIN32_WINDOWS
#	define _WIN32_WINDOWS	0x0500
#endif
//// Ende (Windows-Version)

#include <afxwin.h>				// MFC-Kern- und -Standardkomponenten


char WideCharToSingleChar(TCHAR WideChar)
{
	union
	{
		TCHAR w;
		BYTE s[sizeof(TCHAR)];
	} wide;
	wide.w=WideChar;
	return ((wide.s[0]<0)?'_':wide.s[0]);
}

void CStringToAnsi(CString str, char* ANSI)
{
	for(int i=0;i<str.GetLength();++i,++ANSI)
	{
		*ANSI=WideCharToSingleChar(str[i]);
	}
	*ANSI=0;
}

#ifdef UNICODE
CString AnsiToCString(const char* ANSI, int nLength)
{
	CString strResult;
	for(int i=0;i<nLength;++i,++ANSI)
		strResult+=wchar_t((BYTE)(*ANSI));
	return strResult;
}
CString CStringToAnsiCString(CString str)
{
	char *pcTmp = new char[str.GetLength()+1];
	CStringToAnsi(str,pcTmp);
	CString strReturn=AnsiToCString(pcTmp,str.GetLength());
	delete[] pcTmp;
    return strReturn;
}
#else
CString AnsiToCString(const char* ANSI, int nLength)
{
	return CString(ANSI);
}
CString CStringToAnsiCString(CString str)
{
	return str;
}
#endif