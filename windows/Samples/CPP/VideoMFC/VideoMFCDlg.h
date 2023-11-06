// VideoMFCDlg.h : header file
//

#ifndef VIDEOMFCDLG_H
#define VIDEOMFCDLG_H

#include "afxwin.h"
#include "ScanDlg.h"
#include "afxcmn.h"
#include <vector>
#include "../Common/SizeRange.h"
#include "IsoSDKBurningLib.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScanDlg;
/////////////////////////////////////////////////////////////////////////////
// CVideoMFCDlg dialog

class CVideoMFCDlg : public CDialog
{
// Construction
public:
	CVideoMFCDlg(CWnd* pParent = NULL);	// standard constructor
	~CVideoMFCDlg();

// Dialog Data
	enum { IDD = IDD_VIDEOMFC_DIALOG };

	CComboBox		m_cmbDrives;
	CComboBox		m_cmbProjects;
	CTabCtrl		m_tabLists;
	CListCtrl		m_lstVideoFiles;
	CListCtrl		m_lstPictureFiles;
	CSizeRange		m_cMediumSize;	

	BOOL			m_bJoliet;
	BOOL			m_bFinalize;
	BOOL			m_bEject;

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

	afx_msg void OnAddVideoFile();
	afx_msg void OnAddPictureFile();
	afx_msg void OnDeleteSelected();
	afx_msg void OnReset();

	afx_msg void OnBurnDiskDeveloped();
	afx_msg void OnBurnDiskFoxBurner();
	afx_msg void OnEraseDisk();
	afx_msg void OnSetEject();
	afx_msg void OnSetJoliet();

	afx_msg BOOL OnMountImage(UINT);

	afx_msg BOOL OnSetAspi(UINT nAspi);
	afx_msg void OnRescanDevices();
	afx_msg void OnBurningDevices();
	afx_msg void OnDisableImagewriter();

	afx_msg void OnAbout();
	afx_msg void OnWeb();
	afx_msg void OnSaveLog();

	afx_msg void OnDrives();
	afx_msg void OnProjectType();
	afx_msg void OnTabChange(NMHDR*, LRESULT* pResult);
	afx_msg LRESULT OnErrorNotify(WPARAM,LPARAM);

	DECLARE_MESSAGE_MAP()
private:

	void HandleError(__int32 errCode);
	void Calculator();
	void SetRuler();
	void UpdateDeviceCombo();
	int32 UpdateOptions();
	void DoAddFile(bool bPicture = false);
	void PrepareMenus();

	CScanDlg m_dlgScan;

	int32 m_iProjectType;
	int32 m_nSize;
	bool  m_bMultideviceEnabled;
	bool  m_bBurningDevicesOnly;
	CString m_strStartupDir;

	//void FillTreeView(CString insert,double fFPS, int nBitRate, int nAspectRatio, int nWidth, int nHeight, double fSize);
};

#endif
