// VideoMFC.h : main header file for the VideoMFC application
//

#if !defined(AFX_VIDEOMFC_H__E7BE1EE6_4B75_4CDE_85D7_3E022CFEC7B0__INCLUDED_)
#define AFX_VIDEOMFC_H__E7BE1EE6_4B75_4CDE_85D7_3E022CFEC7B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVideoMFCApp:
// See VideoMFC.cpp for the implementation of this class
//

class CVideoMFCApp : public CWinApp
{
public:
	CVideoMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVideoMFCApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOMFC_H__E7BE1EE6_4B75_4CDE_85D7_3E022CFEC7B0__INCLUDED_)
