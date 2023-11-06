// UtilitiesMFC.h : main header file for the UTILITIESMFC application
//

#if !defined(AFX_UTILITIESMFC_H__7D72B943_68EA_441B_9FD9_6DB280942C83__INCLUDED_)
#define AFX_UTILITIESMFC_H__7D72B943_68EA_441B_9FD9_6DB280942C83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUtilitiesMFCApp:
// See UtilitiesMFC.cpp for the implementation of this class
//

class CUtilitiesMFCApp : public CWinApp
{
public:
	CUtilitiesMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUtilitiesMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUtilitiesMFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UTILITIESMFC_H__7D72B943_68EA_441B_9FD9_6DB280942C83__INCLUDED_)
