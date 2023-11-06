// RawWriterDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"



// CRawWriterDlg dialog
class CRawWriterDlg : public CDialog
{
// Construction
public:
	CRawWriterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_RAWWRITER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CComboBox m_cmbDevice;
	CComboBox cbTrackMode;
	CListCtrl lstDataMask;
	CListCtrl lstIgnoreMask;
	CListCtrl reportTrackItems;
	CEdit edTrackNo;
	CEdit AddFileEdit;
	bool  m_bBurningDevicesOnly;

	afx_msg void OnBnClickedAddtrack();
	afx_msg void OnBnClickedResettrack();
	afx_msg void OnBnClickedDeletetrack();
	afx_msg void OnBnClickedSelfile();
    afx_msg void OnBnClickedAnalyzebutton();
	afx_msg BOOL OnMountImage(UINT);
	afx_msg void OnUnmountImage();	
	afx_msg void OnBurnWithFoxBurnerEmbeddedDialog();
	afx_msg void OnBurnDiscWithDevelopedGUI();
	afx_msg BOOL OnSetAspi(UINT nAspi);    
	afx_msg void OnBurningDevices();
	afx_msg void OnDisableImagewriter();
	afx_msg void OnDrives();
	afx_msg void OnBurnErasedisk();
	afx_msg void OnLvnItemchangedTrackitems(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinIndex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinTrack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetEject();
	afx_msg void OnSetVerify();
	afx_msg void OnSetJoliet();
	afx_msg void OnSetFinalize();
	afx_msg void OnSaveLog();

	void InitMaskList(CListCtrl& cList);

private:

	void OnExit();
	void OnReset();
	void OnAboutBox();
	void OnVisitWeb();

	void UpdateDeviceCombo();
	void HandleError(__int32 errCode);
	int32 UpdateOptions();
	CString m_strStartupDir;

	int64 AddTrackInfo(int32 nNumber, int32 nIndex, int64 nDiskOffset, int8 nTrackFormat, STrackInfo sTrack);
	

	CString m_strModeAudio;
	CString m_strMode1;
	CString m_strMode2Formless;
	CString m_strMode2Form1;
	CString m_strMode2Form2;
	CString m_strModeCDG;
	CString m_strModeUnknown;

	CString m_strRdtSyncHeader;
	CString m_strRdtSubHeaders;
	CString m_strRdtData;
	CString m_strRdtEdcEcc;
	CString m_strRdtSubChPq;
	CString m_strRdtSubChPw;
	CString m_strRdtSubChRw;

	std::vector<SRAWTrackToAdd>	m_vTracks;
	
	BOOL m_bJoliet;
	BOOL m_bFinalize;
	BOOL m_bEjectAfterBurn;
	BOOL m_bVerify;

	BOOL m_bMultideviceEnabled;	
};
