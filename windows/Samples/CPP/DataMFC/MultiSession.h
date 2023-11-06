#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CDataMFCDlg;

// CMultiSession-Dialogfeld

class CMultiSession : public CDialog
{
	DECLARE_DYNAMIC(CMultiSession)

public:
	CMultiSession(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CMultiSession();

// Dialogfelddaten
	enum { IDD = IDD_MULTISESSION };

	int		m_nSession;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	afx_msg BOOL OnDeviceChange(UINT, DWORD_PTR);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	void HandleError(__int32 errCode);
	void FillInfo();

	CListCtrl		m_lstSessions;

	DECLARE_MESSAGE_MAP()
};
