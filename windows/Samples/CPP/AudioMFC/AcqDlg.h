#if !defined(AFX_ACQDLG_H__302AF74A_CF5C_40B4_8950_C8CCD4CC4C07__INCLUDED_)
#define AFX_ACQDLG_H__302AF74A_CF5C_40B4_8950_C8CCD4CC4C07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AcqDlg.h : header file
//

class CAudioMFCDlg;
/////////////////////////////////////////////////////////////////////////////
// CAcqDlg dialog

class CAcqDlg : public CDialog
{
// Construction
public:
	CAcqDlg(CWnd* pParent = NULL);   // standard constructor
	void SetSender(CAudioMFCDlg *pCtrl);
	CAudioMFCDlg *m_pControl;
// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_LICACQDLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbortscan();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANDLG_H__302AF74A_CF5C_40B4_8950_C8CCD4CC4C07__INCLUDED_)
