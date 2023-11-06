// MediumInfo.h : header file
//

#ifndef MEDIUMINFO_H
#define MEDIUMINFO_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMediumInfo dialog

class CMediumInfoDlg : public CDialog
{
// Construction
public:
	CMediumInfoDlg(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_MEDIUMINFO };

	void FillInfo();

	CTreeCtrl	m_ctrlSessions;

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

// Implementation
protected:

	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnBtnTerminate();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnEject();
	afx_msg void OnCbnSelchangeCmbbxDrives();
	afx_msg void OnBnClickedCancel();

	void HandleError(int32);

	DECLARE_MESSAGE_MAP()
};

#endif // MEDIUMINFO_H
