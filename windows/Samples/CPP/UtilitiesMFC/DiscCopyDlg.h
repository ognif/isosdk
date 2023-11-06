#pragma once


// CDiscCopyDlg dialog

class CDiscCopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CDiscCopyDlg)

public:
	CDiscCopyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiscCopyDlg();

	void HandleError(int32 errCode);

// Dialog Data
	enum { IDD = IDD_DISCCOPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
			   double dBytesWritten, double dImageSize, CDiscCopyDlg *pDicsCopyDlg);
	static void OnJobDone(CDiscCopyDlg *pDicsCopyDlg);

	static void OnBurnDone(const TCHAR* pcError, CDiscCopyDlg*);

	static void OnStartVerifyEvent(CDiscCopyDlg*);
	static void OnVerifySectorEvent(double nSector, double tSector, bool nSuccess, CDiscCopyDlg*);
	static void OnVerifyDoneEvent(int nNumErrors, CDiscCopyDlg*);
	static void OnInfoTextEvent(const TCHAR* pcInfoText, int32 nLevel, CDiscCopyDlg*);

	DECLARE_MESSAGE_MAP()


protected:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void UpdateControls();
	void UpdateDeviceCombo();
	afx_msg LRESULT OnUpdateInfo(WPARAM, LPARAM);

	CProgressCtrl*	m_pProgress;
	CComboBox		m_cmbSourceDevice;
	BOOL			m_bExecution;

public:
	afx_msg void OnBnClickedDisccopyCancel();
	afx_msg void OnBnClickedDisccopyCopy();
	afx_msg void OnCbnSelchangeDisccopySourcedevice();

	void EnableControls(BOOL bEnable);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
