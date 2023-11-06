#pragma once
#include "afxwin.h"

// CExtInfos Dialog

class CExtInfos : public CDialog
{
	DECLARE_DYNAMIC(CExtInfos)

public:
	CExtInfos(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CExtInfos();

// Dialogfelddaten
	enum { IDD = IDD_EXTINFOS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedReset();

	void HandleError(__int32 nError);

	CString m_strSystemIdent;
	CString m_strVolumeSet;
	CString m_strPublisher;
	CString m_strDataPreparer;
	CString m_strApplication;
	CString m_strCopyright;
	CString m_strAbstact;
	CString m_strBiblio;
	BOOL    m_bAddFileSuffix;
	BOOL	m_bUseCreationDateTime;
	BOOL	m_bUseModificationDateTime;
	BOOL	m_bUseExpirationDateTime;
	BOOL	m_bUseEffectiveDateTime;
	CTime	m_cCreationDateTime;
	CTime	m_cModificationDateTime;
	CTime	m_cExpirationDateTime;
	CTime	m_cEffectiveDateTime;

	DECLARE_MESSAGE_MAP()
};
