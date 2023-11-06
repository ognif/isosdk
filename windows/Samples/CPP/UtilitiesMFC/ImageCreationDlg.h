#pragma once


// CImageCreationDlg dialog

class CImageCreationDlg : public CDialog
{
	DECLARE_DYNAMIC(CImageCreationDlg)

public:
	CImageCreationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageCreationDlg();

	void HandleError(int32 errCode);
// Dialog Data
	enum { IDD = IDD_IMAGECREATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
			   double dBytesWritten, double dImageSize, CImageCreationDlg*);
	static void OnJobDone(CImageCreationDlg*);

	static void OnStartVerifyEvent(CImageCreationDlg*);
	static void OnVerifySectorEvent(double nSector, double tSector, bool nSuccess, CImageCreationDlg*);
	static void OnVerifyDoneEvent(int nNumErrors, CImageCreationDlg*);

	static void OnBurnDone(const TCHAR* pcError, CImageCreationDlg*);

	DECLARE_MESSAGE_MAP()

protected:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnImageCheck();
	afx_msg void OnBtnImageCreate();
	afx_msg void OnBtnCancelImage();	
	afx_msg void OnBtnImageBrowse();
	afx_msg LRESULT OnUpdateInfo(WPARAM, LPARAM);
	afx_msg void OnDestroy();
	afx_msg void UpdateControls();
	bool UpdateReadDevice();

	CProgressCtrl*	m_pProgress;
	BOOL			m_bExecution;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	void EnableControls(BOOL bEnable);
};
