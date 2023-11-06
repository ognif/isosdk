// AudioMFCDlg.h : header file
//

#ifndef AUDIOMFCDLG_H
#define AUDIOMFCDLG_H

#include "afxwin.h"
#include "../Common/SizeRange.h"
#include "IsoSDKExport.h"
#include "../Common/FileTree.h"
#include "TrackList.h"
#include "CDTextDlg.h"
#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAudioMFCDlg dialog

class CAudioMFCDlg : public CDialog
{
// Construction
public:
	CAudioMFCDlg(CWnd* pParent = NULL);	// standard constructor
	~CAudioMFCDlg();

// Dialog Data
	enum { IDD = IDD_AUDIOMFC };

	CTabCtrl		m_tabLists;
	CComboBox		m_cmbDevice;
	CComboBox		m_cmbProjects;
	CFileList		m_lstFiles;
	CTrackList		m_lstTracks;
	CSizeRange		m_cMediumSize;

	BOOL			m_bJoliet;
	BOOL			m_bRockRidge;
	BOOL			m_bFinalize;
	BOOL			m_bEjectAfterBurn;
	BOOL			m_bVerify;
	BOOL			m_bAllowLowercaseNames;
	BOOL			m_bAllowManyDirectories;
	BOOL			m_bWriteCDTextInUnicode;

	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnAudioAddFile();
	afx_msg void OnAudioDeleteFile();
	afx_msg void OnAudioReset();
	afx_msg void OnDataAddFile();
	afx_msg void OnDataAddFolder();
	afx_msg void OnDataCreateFolder();
	afx_msg void OnDataDeleteFile();
	afx_msg void OnDataReset();

	afx_msg void OnBurnDiskDeveloped();
	afx_msg void OnBurnDiskFoxBurner();
	afx_msg void OnEraseDisk();
	afx_msg void OnSetEject();
	afx_msg void OnSetVerify();
	afx_msg void OnSetJoliet();
	afx_msg void OnSetRockRidge();
	afx_msg void OnSetFinalize();
	afx_msg void OnSetWriteUnicode();
	
	afx_msg void OnSetAllowLowercaseNames();
	afx_msg void OnSetAllowManyDirectories();

	afx_msg void OnPlayAudio();
	afx_msg void OnStopAudio();
	afx_msg void OnLoadPlugin();
	afx_msg void OnLoadPluginWMA();
	afx_msg void OnDiskCdText();
	afx_msg void OnTrackCdText();
	afx_msg void OnGetAudioFileSize();
	afx_msg void OnDiskSize();

	afx_msg BOOL OnMountImage();

	afx_msg BOOL OnSetAspi(UINT nAspi);
	afx_msg void OnRescanDevices();
	afx_msg void OnBurningDevices();
	afx_msg void OnDisableImagewriter();

	afx_msg BOOL OnISOLevel(UINT nLevel);

	afx_msg void OnAbout();
	afx_msg void OnWeb();
	afx_msg void OnSaveLog();

	afx_msg void OnDrives();
	afx_msg void OnProjectType();
	afx_msg void OnTabChange(NMHDR*, LRESULT*);
	afx_msg LRESULT OnErrorNotify(WPARAM,LPARAM);

	DECLARE_MESSAGE_MAP()

private:

	void	HandleError(__int32 errCode);
	void	UpdateTime();
	void	SetRuler();
	void	UpdateDeviceCombo();
	int32	UpdateOptions();
	//CString FormatTime(int sec);

	int		m_nPlayTime;

	int32 m_iProjectType;
	bool  m_bMultideviceEnabled;
	bool  m_bBurningDevicesOnly;
	CString m_strStartupDir;

};

#endif
