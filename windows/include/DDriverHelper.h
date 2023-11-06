#if !defined(AFX_DDRIVERHELPER_H__88811D46_4F68_4AE9_B0AC_B0D33BD7B269__INCLUDED_)
#define AFX_DDRIVERHELPER_H__88811D46_4F68_4AE9_B0AC_B0D33BD7B269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned __int64 uint64;
typedef unsigned int uint32;

#include <windows.h>
#include "..\include\CompressEncryptConfig.h"

class DDriverHelper  
{
public:

	typedef void (*EncryptedDiskCallback)(TCHAR chDrive);

	static DDriverHelper& GetInstance();

	bool StartDriver();

	bool InstallDriver(const TCHAR *tszImagePath);
	bool UninstallDriver(const TCHAR *tszImagePath);

	bool SetPassword(const TCHAR* tszDrive, const char* tszPasswd);
	bool SetEncryptedDiskCallback(EncryptedDiskCallback pCallback);
	bool IsLoaded();

private:
	DDriverHelper();
	DDriverHelper(const DDriverHelper&);
	DDriverHelper& operator=(const DDriverHelper&);
	~DDriverHelper();

	static DWORD WINAPI CallbackThreadProc(LPVOID);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM lParam, LPARAM wParam);

	bool RegisterCallbackWndClass();
	bool CreateCallbackWnd();
	bool CreateCallbackThread();
	bool TerminateCallbackThread();

	bool					m_bLoaded;
	HWND					m_hCallbackWnd;
	HANDLE					m_hCallbackThread;
	EncryptedDiskCallback	m_pCallbackProc;
};

#endif
