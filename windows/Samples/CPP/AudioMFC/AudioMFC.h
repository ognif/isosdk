// AudioMFC.h : main header file for the AudioMFC application
//

#ifndef AUDIOMFC_H
#define AUDIOMFC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"		// main symbols

class CAudioMFCApp : public CWinApp
{
public:
	CAudioMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAudioMFCApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CAudioMFCApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // AUDIOMFC_H
