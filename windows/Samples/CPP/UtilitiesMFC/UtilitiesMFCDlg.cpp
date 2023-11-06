// UtilitiesMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UtilitiesMFC.h"
#include "UtilitiesMFCDlg.h"
#include "ChangeRegionDlg.h"
#include "AboutDlgMFC.h"
#include "config.h"

#define WEBSITELINK			"http://www.isosdk.com"

/////////////////////////////////////////////////////////////////////////////
// CUtilitiesMFCDlg dialog

CUtilitiesMFCDlg::CUtilitiesMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUtilitiesMFCDlg::IDD, pParent)
	, m_bBurningDevicesOnly(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUtilitiesMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICES, m_cmbDevice);
	DDX_Control(pDX, IDC_TABS, m_tabTabs);
}

BEGIN_MESSAGE_MAP(CUtilitiesMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//Menu Commands
	ON_COMMAND(ID_FILE_EXIT, OnCancel)

	ON_COMMAND(ID_DEVICES_ISDRIVEREADY, OnDeviceReady)
	ON_COMMAND(ID_DEVICES_EJECTTRAY, OnEjectTray)
	ON_COMMAND(ID_DEVICES_CLOSETRAY, OnCloseTray)

	ON_COMMAND(ID_DEVICES_LOCKDEVICE, OnLockDevice)
	ON_COMMAND(ID_DEVICES_UNLOCKDEVICE, OnUnlockDevice)

	ON_COMMAND(ID_DEVICES_GETDRIVEINFOS, OnGetDriveInfo)
	ON_COMMAND(ID_DEVICES_GETDRIVEINFOEX, OnGetDriveInfoEx)
	ON_COMMAND(ID_DEVICES_GETCAPABILITIES, OnGetCapabilities)
	ON_COMMAND(ID_DEVICES_SETREGIONCODE, OnSetRegionCode)

	ON_COMMAND(ID_MEDIA_GETDISKINFO, OnGetDiskInfo)
	ON_COMMAND(ID_MEDIA_ERASE, OnErase)

	ON_COMMAND_EX_RANGE(ID_INTERFACE_INTERNAL, ID_INTERFACE_FROGASPI, OnSetAspi)
	ON_COMMAND(ID_ASPI_RESCANDEVICES, OnRescanDevices)
	ON_COMMAND(ID_ASPI_BURNDEVICESONLY, OnBurningDevices)
	ON_COMMAND(ID_ASPI_DISABLEIMAGEWIRTER, OnDisableImagewriter)

	ON_COMMAND(ID_IMAGES_MOUNTIMAGE, OnMountImage)
	ON_COMMAND(ID_IMAGES_UNMOUNTIMAGE, OnUnmountImage)
		
	ON_COMMAND(ID_FILE_WRITELOGFILE, OnWritelog)
	ON_COMMAND(ID_INFORMATION_ABOUT, OnAbout)
	ON_COMMAND(ID_INFORMATION_WEB, OnWeb)

	ON_CBN_SELCHANGE(IDC_DEVICES, OnDrives)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABS, OnTabChange)
	ON_MESSAGE(WM_ERROR_NOTIFY, OnErrorNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUtilitiesMFCDlg message handlers

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Utilitie MFC Sample Application)

BOOL CUtilitiesMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetWindowText(_T(APP_TITLE));

	TCHAR chLicenseKey[35] = _T("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7");
	__int32 res = ::Initialize(chLicenseKey, BS_ASPI_INTERNAL, BS_TRUE);
	if (res != BS_SDK_ERROR_NO) {
		HandleError(res);
		PostQuitMessage(0);
		return FALSE;
	}

	m_tabTabs.InsertItem(0, _T("Drive info"));
	m_tabTabs.InsertItem(1, _T("Drive info ex"));
	m_tabTabs.InsertItem(2, _T("Drive capabilities"));
	m_tabTabs.InsertItem(3, _T("Medium info"));
	m_tabTabs.InsertItem(4, _T("Image creation"));
	m_tabTabs.InsertItem(5, _T("Disc copy"));

	CRect rect;
	m_tabTabs.GetClientRect(&rect);
	m_tabTabs.AdjustRect(FALSE, &rect);

	m_dlgDeviceInfo.Create(IDD_DRIVEINFO, &m_tabTabs);
	m_dlgDeviceInfo.MoveWindow(&rect);
	m_dlgDeviceInfo.FillInfo();

	m_dlgDeviceInfoEx.Create(IDD_DRIVEINFOEX, &m_tabTabs);
	m_dlgDeviceInfoEx.MoveWindow(&rect);
	m_dlgDeviceInfoEx.FillInfo();

	m_dlgCapabilities.Create(IDD_CAPABILITIES, &m_tabTabs);
	m_dlgCapabilities.MoveWindow(&rect);
	m_dlgCapabilities.FillInfos();

	m_dlgMediumInfo.Create(IDD_MEDIUMINFO, &m_tabTabs);
	m_dlgMediumInfo.MoveWindow(&rect);
	m_dlgMediumInfo.FillInfo();

	m_dlgCreateImage.Create(IDD_IMAGECREATION, &m_tabTabs);
	m_dlgCreateImage.MoveWindow(&rect);

	m_dlgDiscCopy.Create(IDD_DISCCOPY, &m_tabTabs);
	m_dlgDiscCopy.MoveWindow(&rect);

	GetMenu()->CheckMenuItem(ID_INTERFACE_INTERNAL, MF_CHECKED);
	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	UpdateDeviceCombo();

	GetCurrentDirectory(_MAX_PATH, m_strStartupDir.GetBuffer(_MAX_PATH));
	m_strStartupDir.ReleaseBuffer();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

CUtilitiesMFCDlg::~CUtilitiesMFCDlg()
{
	::DeInitialize();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUtilitiesMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUtilitiesMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUtilitiesMFCDlg::OnErase()
{
	EnableWindow(FALSE);

	int32 nError = ::EraseDialog(_T("IsoSDK"));
	HandleError(nError);

	EnableWindow();
}

void CUtilitiesMFCDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		__int32 nLength = 2048;

		GetText(errCode, chError, &nLength);

		MessageBox(chError, _T("Error"), MB_OK | MB_ICONERROR);
	}
}

void CUtilitiesMFCDlg::OnDeviceReady()
{
	BS_BOOL	bReady = BS_FALSE;
	int32 nError = ::IsDeviceReady(BS_CURRENT_DEVICE, &bReady);

	if (nError == BS_SDK_ERROR_NO)
	{
		CString message = bReady ? _T("Device is ready.") : _T("Device is not ready");
		MessageBox(message, _T("UtilitiesMFC"), MB_OK| MB_ICONERROR);
	}

	HandleError(nError);
}

void CUtilitiesMFCDlg::OnEjectTray()
{
	int32 nError = ::EjectDevice(BS_CURRENT_DEVICE);
	if (nError == BS_SCSI_ERROR_109)
	{
		int nID = MessageBox(_T("Device is locked.\nWould you like to force ejecting the disk?"), _T(""), MB_YESNO|MB_ICONEXCLAMATION);
		if (nID == IDYES)
		{
			::LockMedium(BS_CURRENT_DEVICE, BS_FALSE);
			OnEjectTray();
		}
	}
	else
	{
		HandleError(nError);
	}
}

void CUtilitiesMFCDlg::OnCloseTray()
{
	int32 nError = ::CloseDevice(BS_CURRENT_DEVICE);
	HandleError(nError);
}

void CUtilitiesMFCDlg::OnLockDevice()
{	
	int32 nError = ::LockMedium(BS_CURRENT_DEVICE, BS_TRUE);
	HandleError(nError);
}

void CUtilitiesMFCDlg::OnUnlockDevice()
{
	int32 nError = ::LockMedium(BS_CURRENT_DEVICE, BS_FALSE);
	HandleError(nError);
}

void CUtilitiesMFCDlg::OnGetDriveInfo()
{
	m_dlgDeviceInfo.FillInfo();

	m_tabTabs.SetCurSel(0);
	OnTabChange(NULL, NULL);
}

void CUtilitiesMFCDlg::OnGetDriveInfoEx()
{
	m_dlgDeviceInfoEx.FillInfo();

	m_tabTabs.SetCurSel(1);
	OnTabChange(NULL, NULL);
}

void CUtilitiesMFCDlg::OnGetCapabilities()
{
	m_dlgCapabilities.FillInfos();

	m_tabTabs.SetCurSel(2);
	OnTabChange(NULL, NULL);
}

void CUtilitiesMFCDlg::OnSetRegionCode()
{
	CChangeRegionDlg dlg(this);
	dlg.DoModal();
}

void CUtilitiesMFCDlg::OnGetDiskInfo()
{
	m_dlgMediumInfo.FillInfo();

	m_tabTabs.SetCurSel(3);
	OnTabChange(NULL, NULL);
}

BOOL CUtilitiesMFCDlg::OnSetAspi(UINT nAspi)
{
	::SetASPI(nAspi - ID_INTERFACE_INTERNAL);

	int32 nActualAspi = 0;
	::GetASPI(&nActualAspi);

	GetMenu()->CheckMenuItem(ID_INTERFACE_INTERNAL, nActualAspi == BS_ASPI_INTERNAL ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_INTERFACE_WINASPI, nActualAspi == BS_ASPI_WNASPI ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_INTERFACE_FROGASPI, nActualAspi == BS_ASPI_FROGASPI ? MF_CHECKED : MF_UNCHECKED );

	UpdateDeviceCombo();
	return TRUE;
}

void CUtilitiesMFCDlg::OnRescanDevices()
{
	int32 res = ::RescanDevices();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

void CUtilitiesMFCDlg::OnBurningDevices()
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = !m_bBurningDevicesOnly;

	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	UpdateDeviceCombo();
}

void CUtilitiesMFCDlg::OnDisableImagewriter()
{
	bool bDisable = GetMenu()->GetMenuState(ID_ASPI_DISABLEIMAGEWIRTER, MF_BYCOMMAND) == MF_UNCHECKED;
	// Disable or enable image writer

	::EnableImageDevice(bDisable ? BS_FALSE : BS_TRUE);

	// Update devices list

	UpdateDeviceCombo();

	GetMenu()->CheckMenuItem(ID_ASPI_DISABLEIMAGEWIRTER, bDisable ? MF_CHECKED : MF_UNCHECKED);
}

void CUtilitiesMFCDlg::OnWritelog()
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(m_strStartupDir + _T("\\FoxSampleUtilitiesW.log"));
}

void CUtilitiesMFCDlg::OnAbout()
{
	CAboutDlg	dlg(this);
	dlg.DoModal();
}

void CUtilitiesMFCDlg::OnWeb()
{
	ShellExecute(0, _T("open"), _T(WEBSITELINK), 0, 0, SW_SHOW);
}

void CUtilitiesMFCDlg::OnDrives()
{
	CWaitCursor wait;

	int index = m_cmbDevice.GetCurSel();

	if (index == m_cmbDevice.GetCount()-1 && m_bMultideviceEnabled)
	{
		// Open multidevice dialog if multidevice is selected

		::MultiDeviceDialog();

		// Multidevice dialog set current device, so we
		// should update device combo

		UpdateDeviceCombo();
	}
	else if (CB_ERR < index)
	{
		CString strDevice;
		m_cmbDevice.GetLBText(index, strDevice);

		// Set current device

		int32 res = ::SetBurnDevice(strDevice);
		HandleError(res);
	}

	GetCurrentTab()->SendMessage(WM_CURRENT_DEVICE_CHANGE);

	m_dlgDeviceInfo.FillInfo();
	m_dlgDeviceInfoEx.FillInfo();
	m_dlgCapabilities.FillInfos();
	m_dlgMediumInfo.FillInfo();
}

CDialog* CUtilitiesMFCDlg::GetCurrentTab()
{
	switch(m_tabTabs.GetCurSel())
	{
		case 1: return &m_dlgDeviceInfoEx;
		case 2: return &m_dlgCapabilities;
		case 3: return &m_dlgMediumInfo;
		case 4: return &m_dlgCreateImage;
		case 5: return &m_dlgDiscCopy;
		default: return &m_dlgDeviceInfo;
	}
}

void CUtilitiesMFCDlg::UpdateDeviceCombo()
{
	m_cmbDevice.ResetContent();
	m_bMultideviceEnabled = false;

	// Get devices list

	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 res = ::GetDevices(chListDevices, &nUsed, m_bBurningDevicesOnly ? BS_TRUE : BS_FALSE);
	HandleError(res);

	// Get current device

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	HandleError(res);

	// Add devices to combo box

	for (int i = 0; i < nUsed; i++)
	{
		m_cmbDevice.AddString(chListDevices[i]);

		// Set selection on current device

		if (nBurnDevices > 0) {
			if (0 == _tcsncmp(chBurnDevices[0], chListDevices[i], 2)) {
				m_cmbDevice.SetCurSel(i);
			}
		}
	}

	// Append multidevice item if more than one device in list

	if (nUsed > 1)
	{
		m_bMultideviceEnabled = true;
		m_cmbDevice.AddString(_T("Multiple devices"));
	}

	// Select multidevice item if more than one device is active

	if (nBurnDevices > 1)
		m_cmbDevice.SetCurSel(m_cmbDevice.GetCount()-1);
}

void CUtilitiesMFCDlg::OnTabChange(NMHDR*, LRESULT* pResult)
{
	int nTab = m_tabTabs.GetCurSel();

	switch(nTab)
	{
	case 0:
		m_dlgDeviceInfo.ShowWindow(SW_SHOW);
		m_dlgDeviceInfoEx.ShowWindow(SW_HIDE);
		m_dlgMediumInfo.ShowWindow(SW_HIDE);
		m_dlgCapabilities.ShowWindow(SW_HIDE);
		m_dlgCreateImage.ShowWindow(SW_HIDE);
		m_dlgDiscCopy.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlgDeviceInfoEx.ShowWindow(SW_SHOW);
		m_dlgDeviceInfo.ShowWindow(SW_HIDE);
		m_dlgMediumInfo.ShowWindow(SW_HIDE);
		m_dlgCapabilities.ShowWindow(SW_HIDE);
		m_dlgCreateImage.ShowWindow(SW_HIDE);
		m_dlgDiscCopy.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_dlgCapabilities.ShowWindow(SW_SHOW);
		m_dlgDeviceInfoEx.ShowWindow(SW_HIDE);
		m_dlgDeviceInfo.ShowWindow(SW_HIDE);
		m_dlgMediumInfo.ShowWindow(SW_HIDE);
		m_dlgCreateImage.ShowWindow(SW_HIDE);
		m_dlgDiscCopy.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_dlgMediumInfo.ShowWindow(SW_SHOW);
		m_dlgDeviceInfoEx.ShowWindow(SW_HIDE);
		m_dlgDeviceInfo.ShowWindow(SW_HIDE);
		m_dlgCapabilities.ShowWindow(SW_HIDE);
		m_dlgCreateImage.ShowWindow(SW_HIDE);
		m_dlgDiscCopy.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_dlgCreateImage.ShowWindow(SW_SHOW);
		m_dlgMediumInfo.ShowWindow(SW_HIDE);
		m_dlgDeviceInfoEx.ShowWindow(SW_HIDE);
		m_dlgDeviceInfo.ShowWindow(SW_HIDE);
		m_dlgCapabilities.ShowWindow(SW_HIDE);
		m_dlgDiscCopy.ShowWindow(SW_HIDE);
		break;
	case 5:
		m_dlgDiscCopy.ShowWindow(SW_SHOW);
		m_dlgCreateImage.ShowWindow(SW_HIDE);
		m_dlgMediumInfo.ShowWindow(SW_HIDE);
		m_dlgDeviceInfoEx.ShowWindow(SW_HIDE);
		m_dlgDeviceInfo.ShowWindow(SW_HIDE);
		m_dlgCapabilities.ShowWindow(SW_HIDE);		
		break;
	}

	if (pResult)
		*pResult = TRUE;
}

LRESULT CUtilitiesMFCDlg::OnErrorNotify(WPARAM,LPARAM errCode)
{
	HandleError(errCode);
	return 0;
}

void CUtilitiesMFCDlg::OnMountImage()
{	
	CFileDialog  dlg(FALSE, NULL, NULL, 0, _T("All Supported|*.iso;*.bin;*.nrg;*.cdi;*.mdf;*.ccd;*.img;*.gi;*.pdi;*.dmg;*.b5i;*.b6i| iso files|*.iso| bin files|*.bin| nrg files|*.nrg| cdi files|*.cdi| mdf files|*.mdf| ccd files|*.ccd| img files|*.img| gi files|*.gi| pdi files|*.pdi| dmg files|*.dmg| b5i files|*.b5i| b6i files|*.b6i||"), this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetImageFilePath(dlg.GetPathName());
		HandleError(res);	

		GetCurrentTab()->SendMessage(WM_CURRENT_DEVICE_CHANGE);
	}
}

void CUtilitiesMFCDlg::OnUnmountImage()
{
	int32 res = ::SetImageFilePath(NULL);
	HandleError(res);

	GetCurrentTab()->SendMessage(WM_CURRENT_DEVICE_CHANGE);
}

void CUtilitiesMFCDlg::OnOK()
{
}
