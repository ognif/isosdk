#pragma once
#include "afxwin.h"

class CDataMFCDlg;
// CBootOptions-Dialogfeld

class CBootOptions : public CDialog
{
	DECLARE_DYNAMIC(CBootOptions)

public:
	CBootOptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_BOOTOPTIONS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedSelectImageFile();

	void HandleError(__int32 nError);

	CButton		m_btnBoot;
	CComboBox	m_cmbPlatform;
	CComboBox	m_cmbEmulation;

	CString		m_strLoadSegment;
	CString		m_strSectorCount;
	CString		m_strBootImage;
	CString		m_strDeveloperID;

	DECLARE_MESSAGE_MAP()
};
