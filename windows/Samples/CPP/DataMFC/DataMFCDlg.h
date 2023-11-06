// DataMFCDlg.h : header file
//

#ifndef DATAMFCSLG_H
#define DATAMFCSLG_H

#include "afxwin.h"
#include "../Common/SizeRange.h"
#include "IsoSDKExport.h"
#include "../Common/FileTree.h"
#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDataMFCDlg dialog

class CDataMFCDlg : public CDialog
{
// Construction
public:
	CDataMFCDlg(CWnd* pParent = NULL);	// standard constructor
	~CDataMFCDlg();

// Dialog Data
	enum { IDD = IDD_DATAMFC_DIALOG };

	CComboBox		m_cmbDevice;
	CComboBox		m_cmbProjects;
	CFileList		m_lstFiles;
	CSizeRange		m_MediumSize;

	BOOL			m_bJoliet;
	BOOL			m_bRockRidge;
	BOOL			m_bFinalize;
	BOOL			m_bEjectAfterBurn;
	BOOL			m_bVerify;
	BOOL			m_bAllowLowercaseNames;
	BOOL			m_bAllowManyDirectories;
	BOOL			m_bAllowLongISO9660Names;
	BOOL			m_bAllowLongJolietNames;

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

	afx_msg void OnAddFile();
	afx_msg void OnAddFolder();
	afx_msg void OnCreateFolder();
	afx_msg void OnRenameFile();
	afx_msg void OnDeleteSelected();
	afx_msg void OnReset();
	afx_msg void OnDisableFileExistCheck();

	afx_msg void OnBurnDiskDeveloped();
	afx_msg void OnBurnDiskFoxBurner();
	afx_msg void OnEraseDisk();
	afx_msg void OnSetEject();
	afx_msg void OnSetVerify();
	afx_msg void OnSetJoliet();
	afx_msg void OnSetRockRidge();
	afx_msg void OnSetFinalize();
	afx_msg void OnSetAllowLowercaseNames();
	afx_msg void OnSetAllowManyDirectories();
	afx_msg void OnSetAllowLongISO9660Names();
	afx_msg void OnSetAllowLongJolietNames();

	afx_msg void OnExtHeader();
	afx_msg void OnBootOptions();
	afx_msg void OnImportSession();
	afx_msg void OnImportLastSession();
	afx_msg void OnImportNoSession();

	afx_msg BOOL OnMountImage(UINT);
	afx_msg void OnUnmountImage();
	afx_msg void OnBurnImage();

	afx_msg BOOL OnSetAspi(UINT nAspi);
    afx_msg void OnRescanDevices();
	afx_msg void OnBurningDevices();
	afx_msg void OnDisableImagewriter();

	afx_msg BOOL OnISOLevel(UINT nLevel);


	afx_msg void OnAbout();
	afx_msg void OnWeb();
	afx_msg void OnSaveLog();
	afx_msg void OnSetLanguageFileDe();
	afx_msg void OnSetLanguageFileEn();
	afx_msg void OnSetLanguageFileEs();
	afx_msg void OnSetLanguageFileFr();

	afx_msg void OnDrives();
	afx_msg void OnProjectType();
	afx_msg LRESULT OnErrorNotify(WPARAM,LPARAM);

	DECLARE_MESSAGE_MAP()
private:

	void HandleError(__int32 errCode);
	void Calculator();
	void SetRuler();
	void UpdateDeviceCombo();
	int32 UpdateOptions();
	static BS_BOOL OnCompareFilesForArrangement(const SFileEntry *pFile1, const SFileEntry *pFile2, void *pUserData);

	int32 m_iProjectType;
	int32 m_iSession;
	bool  m_bMultideviceEnabled;
	bool  m_bBurningDevicesOnly;
	CString m_strStartupDir;
public:
	afx_msg void OnFileProperties();
};

#endif // DATAMFCSLG_H
