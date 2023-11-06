#ifndef SCANDLG_H
#define SCANDLG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog

class CScanDlg : public CDialog
{
public:
	CScanDlg(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_SCANDLG };

	CString	m_strFileToAdd;

	CString m_strPlaytime;
	CString m_strFrameRate;
	CString m_strBitrate;
	CString m_strAspectRatio;
	CString	m_strDimensions;
	bool	m_bPictureFile;

	static void OnVideoScannerEvent(float fPercent, const TCHAR *pcFileName, CScanDlg* pDlg);
	static void OnVideoScanDoneEvent(const TCHAR *pcFileName, const TCHAR *pcError, __int32 nErrorCode, struct SVideoFormat CurrentFormat, CScanDlg* pDlg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedAbortscan();

	CProgressCtrl	m_prgScan;

	DECLARE_MESSAGE_MAP()
};

#endif
