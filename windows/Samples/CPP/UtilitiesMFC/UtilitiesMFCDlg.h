#ifndef UTILITIESDLG_H
#define UTILITIESDLG_H

#include "afxwin.h"
#include "IsoSDKExport.h"
#include "DeviceInfoDlg.h"
#include "DeviceInfoEx.h"
#include "MediumInfo.h"
#include "ImageCreationDlg.h"
#include "DiscCopyDlg.h"
#include "GetCapa.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUtilitiesMFCDlg dialog

class CUtilitiesMFCDlg : public CDialog
{
// Construction
public:
	CUtilitiesMFCDlg(CWnd* pParent = NULL);	// standard constructor
	~CUtilitiesMFCDlg();

	enum { IDD = IDD_UTILITIESMFC };

	CComboBox		m_cmbDevice;
	CTabCtrl		m_tabTabs;

	CDeviceInfoDlg		m_dlgDeviceInfo;
	CDeviceInfoExDlg	m_dlgDeviceInfoEx;
	CMediumInfoDlg		m_dlgMediumInfo;
	CCapabilitiesDlg	m_dlgCapabilities;
	CImageCreationDlg	m_dlgCreateImage;
	CDiscCopyDlg		m_dlgDiscCopy;

	// ClassWizard generated virtual function overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnOK();

// Implementation
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnDeviceReady();
	afx_msg void OnEjectTray();
	afx_msg void OnCloseTray();

	afx_msg void OnLockDevice();
	afx_msg void OnUnlockDevice();

	afx_msg void OnGetDriveInfo();
	afx_msg void OnGetDriveInfoEx();
	afx_msg void OnGetCapabilities();
	afx_msg void OnSetRegionCode();

	afx_msg void OnGetDiskInfo();
	afx_msg void OnErase();

	afx_msg BOOL OnSetAspi(UINT nAspi);
	afx_msg void OnRescanDevices();
	afx_msg void OnBurningDevices();
	afx_msg void OnDisableImagewriter();

	afx_msg void OnMountImage();
	afx_msg void OnUnmountImage();

	afx_msg void OnAbout();
	afx_msg void OnWeb();
	afx_msg void OnWritelog();

	afx_msg void OnDrives();
	afx_msg void OnTabChange(NMHDR*, LRESULT*);
	afx_msg LRESULT OnErrorNotify(WPARAM,LPARAM);

	DECLARE_MESSAGE_MAP()

private:
	void HandleError(__int32);
	void UpdateDeviceCombo();

	CDialog* GetCurrentTab();

	bool m_bBurningDevicesOnly;
	bool m_bMultideviceEnabled;
	CString m_strStartupDir;
};

#endif // UTILITIESDLG_H
