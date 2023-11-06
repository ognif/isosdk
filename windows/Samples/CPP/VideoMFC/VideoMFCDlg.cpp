#include "stdafx.h"
#include "VideoMFC.h"
#include "VideoMFCDlg.h"
#include "IsoSDKExport.h"
#include "SampleBurnDlgMFC.h"
#include "AboutDlgMFC.h"
#include <sys/stat.h>
#include "config.h"

#define WEBSITELINK			"http://www.isosdk.com"

/////////////////////////////////////////////////////////////////////////////
// CVideoMFCDlg dialog

CVideoMFCDlg::CVideoMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoMFCDlg::IDD, pParent)
	, m_iProjectType(BS_BURNER_VCD)
	, m_bBurningDevicesOnly(true)
	, m_nSize(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABS, m_tabLists);
	DDX_Control(pDX, IDC_DEVICES, m_cmbDrives);
	DDX_Control(pDX, IDC_PROJECTTYPE, m_cmbProjects);
	DDX_Control(pDX, IDC_VIDEOFILELIST, m_lstVideoFiles);
	DDX_Control(pDX, IDC_PICTUREFILELIST, m_lstPictureFiles);
}

BEGIN_MESSAGE_MAP(CVideoMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//Menu Commands
	ON_COMMAND(ID_FILE_ADDVIDEOFILE, OnAddVideoFile)
	ON_COMMAND(ID_FILE_ADDPICTUREFILE, OnAddPictureFile)
	ON_COMMAND(ID_FILE_DELETEFILE, OnDeleteSelected)
	ON_COMMAND(ID_FILE_RESET, OnReset)
	ON_COMMAND(ID_FILE_EXIT, OnCancel)

	ON_COMMAND(ID_BURN_BURNWITHDEVELOPEDGUI, OnBurnDiskDeveloped)
	ON_COMMAND(ID_BURN_BURNWITHFOXBURNEREMBEDDEDDIALOG, OnBurnDiskFoxBurner)
	ON_COMMAND(ID_BURN_ERASEDISK, OnEraseDisk)
	ON_COMMAND(ID_OPTIONS_EJECTDISK, OnSetEject)
	ON_COMMAND(ID_OPTIONS_JOLIETFILESYSTEM, OnSetJoliet)

	ON_COMMAND_EX_RANGE(ID_INTERFACE_INTERNAL, ID_INTERFACE_FROGASPI, OnSetAspi)
	ON_COMMAND(ID_ASPI_RESCANDEVICES, OnRescanDevices)
	ON_COMMAND(ID_ASPI_BURNDEVICESONLY, OnBurningDevices)
	ON_COMMAND(ID_ASPI_DISABLEIMAGEWIRTER, OnDisableImagewriter)

	ON_COMMAND(ID_INFORMATION_ABOUT, OnAbout)
	ON_COMMAND(ID_INFORMATION_WEB, OnWeb)
	ON_COMMAND(ID_FILE_WRITELOGFILE, OnSaveLog)

	ON_NOTIFY(TCN_SELCHANGE,IDC_TABS,OnTabChange)

	ON_CBN_SELCHANGE(IDC_DEVICES, OnDrives)
	ON_CBN_SELCHANGE(IDC_PROJECTTYPE, OnProjectType)
	ON_MESSAGE(WM_ERROR_NOTIFY, OnErrorNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoMFCDlg message handlers

void InitFileListCtrl(CListCtrl& list)
{
	list.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
	list.InsertColumn(1, _T("Size"), LVCFMT_LEFT, 60);
	list.InsertColumn(2, _T("Length"), LVCFMT_LEFT, 60);
	list.InsertColumn(3, _T("Modified Date"), LVCFMT_LEFT, 100);
	list.InsertColumn(4, _T("Framerate"), LVCFMT_LEFT, 100);
	list.InsertColumn(5, _T("Bitrate"), LVCFMT_LEFT, 100);
	list.InsertColumn(6, _T("Aspect Ratio"), LVCFMT_LEFT, 100);
	list.InsertColumn(7, _T("Dimensions"), LVCFMT_LEFT, 100);

	list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
}

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Video MFC Sample Application)

BOOL CVideoMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetWindowText(_T(APP_TITLE));

    //--------------------------------------------------
    //Init the SDK
    //--------------------------------------------------
	TCHAR chLicenseKey[35] = _T("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7");
	__int32 res = ::Initialize(chLicenseKey, BS_ASPI_INTERNAL, BS_TRUE);
	if (res != BS_SDK_ERROR_NO) {
		HandleError(res);
		PostQuitMessage(0);
		return FALSE;
	}

	//--------------------------------------------------
    //Set the callbacks to receive infos later
    //--------------------------------------------------
	::SetVideoScannerEventCallback((VideoScannerEvent) CScanDlg::OnVideoScannerEvent, &m_dlgScan);
	::SetVideoScanDoneEventCallback((VideoScanDoneEvent) CScanDlg::OnVideoScanDoneEvent, &m_dlgScan);

    //--------------------------------------------------
    //We need to set a projcet. So we set default project first
    //--------------------------------------------------
	res = ::CreateProject(BS_BURNER_VCD, BS_CONTINUE_NO_SESSION);
	HandleError(res);

    //--------------------------------------------------
    //Set the Options. Remember, not all Options are
	//available on all projects. Read Help
    //--------------------------------------------------

	SOptions opt;
	res = GetOptions(&opt);
	HandleError(res);

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	m_bEject = opt.bEjectAfterBurn;
	m_bFinalize = opt.bFinalize;
	m_bJoliet = opt.bJolietFileSystem;

	res = SetOptions(opt);
	HandleError(res);

	m_cmbProjects.AddString(_T("VCD"));
	m_cmbProjects.AddString(_T("SVCD"));
	m_cmbProjects.SetCurSel(0);

	m_tabLists.InsertItem(0, _T("Video"));
	m_tabLists.InsertItem(1, _T("Pictures"));

	InitFileListCtrl(m_lstVideoFiles);
	InitFileListCtrl(m_lstPictureFiles);

	UpdateData(FALSE);

	//Fill Devicelist and Select
	UpdateDeviceCombo();

	//Some GUI things
	m_cMediumSize.Attach(IDC_RULER, this);


	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISK, m_bEject ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);

	GetMenu()->CheckMenuItem(ID_INTERFACE_INTERNAL, MF_CHECKED);
	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	SetRuler();

	GetCurrentDirectory(_MAX_PATH, m_strStartupDir.GetBuffer(_MAX_PATH));
	m_strStartupDir.ReleaseBuffer();

	return TRUE;
}

CVideoMFCDlg::~CVideoMFCDlg()
{
	::DeInitialize();
}

void CVideoMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


HCURSOR CVideoMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVideoMFCDlg::DoAddFile(bool bPicture)
{
	LPCTSTR patterns = _T("MPEG files (*.mpg)|*.mpg||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_EXPLORER, patterns);

	if (dlg.DoModal() == IDOK)
	{
#if _MSC_VER < 1400
		struct _stat statbuf;
#else
		struct _stat64i32 statbuf;
#endif
		int res = _tstat(dlg.GetPathName(), &statbuf);

		if (0 == res)
		{
			m_dlgScan.m_strFileToAdd = dlg.GetPathName();
			m_dlgScan.m_bPictureFile = bPicture;

			if (m_dlgScan.DoModal() == IDOK)
			{
				long size = statbuf.st_size;
				CString strSize;

				if (size > 1024*1024) {
					size = size / (1024*1024);
					strSize.Format(_T("%d MB"), size);
				} else {
					strSize.Format(_T("%d bytes"), size);
				}

				CString strDate;
				struct tm *time = localtime(&statbuf.st_mtime);

				strDate.Format(_T("%02d.%02d.%04d %02d:%02d:%02d"),
					time->tm_mday,
					time->tm_mon+1,
					time->tm_year + 1900,
					time->tm_hour,
					time->tm_min,
					time->tm_sec);

				CListCtrl& list = bPicture
					? m_lstPictureFiles
					: m_lstVideoFiles;

				int nItem = list.InsertItem(list.GetItemCount(), dlg.GetFileName());
				list.SetItemText(nItem, 1, strSize);
				list.SetItemText(nItem, 2, m_dlgScan.m_strPlaytime);
				list.SetItemText(nItem, 3, strDate);
				list.SetItemText(nItem, 4, m_dlgScan.m_strFrameRate);
				list.SetItemText(nItem, 5, m_dlgScan.m_strBitrate);
				list.SetItemText(nItem, 6, m_dlgScan.m_strAspectRatio);
				list.SetItemText(nItem, 7, m_dlgScan.m_strDimensions);
				list.SetItemData(nItem, (DWORD_PTR)new long(statbuf.st_size));

                m_nSize += statbuf.st_size;

				m_tabLists.SetCurSel(bPicture ? 1 : 0);
				Calculator();
			}
		}
	}
}

void CVideoMFCDlg::OnAddVideoFile()
{
	DoAddFile(false);
}

void CVideoMFCDlg::OnAddPictureFile()
{
	DoAddFile(true);
}

void CVideoMFCDlg::OnDeleteSelected()
{
	// Delete video or picture?
	bool bVideo = m_tabLists.GetCurSel() == 0;

	// Get current icon list
	CListCtrl& list = bVideo ? m_lstVideoFiles : m_lstPictureFiles;

	POSITION pos = list.GetFirstSelectedItemPosition();

	if (pos)
	{
		int indx = list.GetNextSelectedItem(pos);

		// Calculate item number to delete
		int32 itemIndex = bVideo 
			? BS_VCD_TRACK_ITEM_0 + indx
			: BS_VCD_SEGMENT_ITEM_0 + indx;

		int32 res = ::EraseMpegByIndex(itemIndex);
		HandleError(res);

		if (BS_SDK_ERROR_NO == res)
		{
			long* size = (long*)list.GetItemData(indx);
			list.DeleteItem(indx);
			m_nSize -= *size;
			Calculator();
			delete size;
		}
	}
}

void CVideoMFCDlg::OnReset()
{
	int32 res = ::ClearAll();
	HandleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		m_lstVideoFiles.DeleteAllItems();
		m_lstPictureFiles.DeleteAllItems();
		m_nSize = 0;
		Calculator();
	}
}

void CVideoMFCDlg::PrepareMenus()
{
	if (m_lstPictureFiles.GetItemCount() > 0)
	{
		// 1st case : we have pictures

		// create key 1..N handlers
		int numPictureHandlers = min(m_lstPictureFiles.GetItemCount() - 1, 99);
		int numVideoHandlers = min(m_lstVideoFiles.GetItemCount(), 99 - numPictureHandlers);

		// set numeric key handler for menu picture
		for(int i = 0; i < numPictureHandlers; ++i)
		{
			::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0, BS_VCD_KEY_0 + i + 1, BS_VCD_SEGMENT_ITEM_0 + i + 1);
		}

		for(int i = 0; i < numVideoHandlers; ++i)
		{
			::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0, BS_VCD_KEY_0 + numPictureHandlers + i + 1, BS_VCD_TRACK_ITEM_0 + i);
		}

		for(int i = 0; i < m_lstPictureFiles.GetItemCount(); ++i)
		{
			// set timeout for all pictures except last picture
			if (i != m_lstPictureFiles.GetItemCount() - 1)
			{
				int timeout = (i == 0) ? 120 : 10;
				::SetVCDTimeOutHandler(BS_VCD_SEGMENT_ITEM_0 + i, timeout, BS_VCD_SEGMENT_ITEM_0 + i + 1);
				::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0 + i, BS_VCD_KEY_NEXT, BS_VCD_SEGMENT_ITEM_0 + i + 1);
			}

			if (i != 0)
			{
				::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0 + i, BS_VCD_KEY_PREVIOUS, BS_VCD_SEGMENT_ITEM_0 + i - 1);

				// return from any picture to the menu picture
				::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0 + i, BS_VCD_KEY_RETURN, BS_VCD_SEGMENT_ITEM_0);
			}
		}

		// if there is video files set transition keys pictures<->video
		if (m_lstVideoFiles.GetItemCount() != 0)
		{
			::SetVCDTimeOutHandler(BS_VCD_SEGMENT_ITEM_0 + m_lstPictureFiles.GetItemCount() - 1, 
								10, BS_VCD_TRACK_ITEM_0);

			::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0 + m_lstPictureFiles.GetItemCount() - 1, 
								BS_VCD_KEY_NEXT, BS_VCD_TRACK_ITEM_0);

			::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0, BS_VCD_KEY_PREVIOUS, 
								BS_VCD_SEGMENT_ITEM_0 + m_lstPictureFiles.GetItemCount() - 1);
		}

		// create prev-next handlers
		for(int i = 0; i < m_lstVideoFiles.GetItemCount(); ++i)
		{
			if (i != m_lstVideoFiles.GetItemCount() - 1)
			{
				// jump to next item if user press "Next"
				::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0 + i, BS_VCD_KEY_NEXT, BS_VCD_TRACK_ITEM_0 + i + 1);
				// jump to next item after playing current item
				::SetVCDTimeOutHandler(BS_VCD_TRACK_ITEM_0 + i, 0, BS_VCD_TRACK_ITEM_0 + i + 1);
			}
			else
			{
				// jump to main menu after playing last video item
				::SetVCDTimeOutHandler(BS_VCD_TRACK_ITEM_0 + i, 0, BS_VCD_SEGMENT_ITEM_0);
			}

			if (i != 0)
			{
				// jump previous item if user press "Previous"
				::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0 + i, BS_VCD_KEY_PREVIOUS, BS_VCD_TRACK_ITEM_0 + i - 1);
			}

			// return to the main menu if user press "Return"
			::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0 + i, BS_VCD_KEY_RETURN, BS_VCD_SEGMENT_ITEM_0);
		}
	}
	else
	{
		// 2nd case : we have no pictures in project

		// create "prev-next" key handlers
		for(int i = 0; i < m_lstVideoFiles.GetItemCount(); ++i)
		{
			if (i != 0)
				::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0 + i, BS_VCD_KEY_PREVIOUS, BS_VCD_TRACK_ITEM_0 + i - 1);

			if (i != m_lstVideoFiles.GetItemCount() -1)
				::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0 + i, BS_VCD_KEY_NEXT, BS_VCD_TRACK_ITEM_0 + i + 1);
		}
	}
}

void CVideoMFCDlg::OnBurnDiskDeveloped()
{
	// Synchronize options and menu controls

	UpdateOptions();
	PrepareMenus();

	// Get current device

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	HandleError(res);

	// Open image selection dialog if image device is selected

	if (0 == _tcsncmp(_T("#"), chBurnDevices[0], 1))  // Iso writer selected
	{
		if (!OnMountImage(0))
			return;

		// Also set special options for image writer
		SOptions opt;

		// Load current options first

		res = ::GetOptions(&opt);
		HandleError(res);

		opt.nCopies = 0;	// No need for copies
		opt.bTestBurn = BS_FALSE;	// Test burn not supported
		opt.bVerifyAfterBurn = BS_FALSE;	// Test burn not supported

		// Then save options

		res = ::SetOptions(opt);
		HandleError(res);
	}

	CSampleBurnDlg	burnDlg(this);
	burnDlg.DoModal();
}

void CVideoMFCDlg::OnBurnDiskFoxBurner()
{
	// Synchronize options and menu controls

	UpdateOptions();
	PrepareMenus();

	// Call IsoSDK burn dialog

	int32 res = ::BurnDialog();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

void CVideoMFCDlg::OnEraseDisk()
{
	__int32 nError = EraseDialog(_T("IsoSDK"));
	HandleError(nError);

	UpdateDeviceCombo();
}

void CVideoMFCDlg::OnSetEject()
{
	m_bEject = !m_bEject;
	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISK, m_bEject ? MF_CHECKED : MF_UNCHECKED);
}

void CVideoMFCDlg::OnSetJoliet()
{
	m_bJoliet = !m_bJoliet;
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);
}

BOOL CVideoMFCDlg::OnMountImage(UINT)
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("CUE/BIN Files (*.bin)|*.bin||"), this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetImageFilePath(dlg.GetPathName());
		HandleError(res);
		return res == BS_SDK_ERROR_NO ? TRUE : FALSE;
	}

	return FALSE;
}

BOOL CVideoMFCDlg::OnSetAspi(UINT nAspi)
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

void CVideoMFCDlg::OnRescanDevices()
{
	int32 res = ::RescanDevices();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

void CVideoMFCDlg::OnBurningDevices()
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = !m_bBurningDevicesOnly;

	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	UpdateDeviceCombo();
}

void CVideoMFCDlg::OnDisableImagewriter()
{
	bool bDisable = GetMenu()->GetMenuState(ID_ASPI_DISABLEIMAGEWIRTER, MF_BYCOMMAND) == MF_UNCHECKED;
	// Disable or enable image writer

	::EnableImageDevice(bDisable ? BS_FALSE : BS_TRUE);

	// Update devices list

	UpdateDeviceCombo();

	GetMenu()->CheckMenuItem(ID_ASPI_DISABLEIMAGEWIRTER, bDisable ? MF_CHECKED : MF_UNCHECKED);
}

void CVideoMFCDlg::OnAbout()
{
	CAboutDlg	dlg(this);
	dlg.DoModal();
}

void CVideoMFCDlg::OnWeb()
{
	ShellExecute(0, _T("open"), _T(WEBSITELINK), 0, 0, SW_SHOW);
}

void CVideoMFCDlg::OnDrives()
{
	int index = m_cmbDrives.GetCurSel();

	if (index == m_cmbDrives.GetCount()-1 && m_bMultideviceEnabled)
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
		m_cmbDrives.GetLBText(index, strDevice);

		// Set current device

		int32 res = ::SetBurnDevice(strDevice);
		HandleError(res);
	}
}

void CVideoMFCDlg::OnProjectType()
{
	int indx = m_cmbProjects.GetCurSel();
	int32 type = BS_BURNER_VCD;

	switch (indx) {
	case 0:
		type = BS_BURNER_VCD;
		break;
	case 1:
		type = BS_BURNER_SVCD;
		break;
	}

	int32 res = ::CreateProject(type);
	HandleError(res);

	if (res != BS_SDK_ERROR_NO)
	{
		::GetProjectType(&type);
		switch(type) {
			case BS_BURNER_VCD:		indx = 0; break;
			case BS_BURNER_SVCD:	indx = 1; break;
			default: ASSERT(0); break;
		}
		m_cmbProjects.SetCurSel(indx);
	}
	else
	{
		OnReset();
	}
}

void CVideoMFCDlg::HandleError(__int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		__int32 nLength = 2048;

		GetText(errCode, chError, &nLength);

		MessageBox(chError, _T("Error"), MB_OK|MB_ICONERROR);
	}
}

void CVideoMFCDlg::Calculator()
{
	m_cMediumSize.SetValuePos(m_nSize/(1024*1024));
	m_cMediumSize.Invalidate();
}

void CVideoMFCDlg::SetRuler()
{
	// Playtime is ax 750 MB.
	m_cMediumSize.SetMaxRange(750);
	m_cMediumSize.SetMarkTick(20);
	m_cMediumSize.SetUnitTick(100);
	m_cMediumSize.SetUnit("MB");
	m_cMediumSize.RemoveAllLines();
	m_cMediumSize.ResetValueColorZones();

	m_cMediumSize.SetValueColorChange(0,RGB(35,126,216));

	// After 670 min, the is a critical size
	m_cMediumSize.AddLine(700-30,RGB(247,200,10),false);
	m_cMediumSize.SetValueColorChange(700-30,RGB(247,200,10));

	// After 700 MB most Media are full
	m_cMediumSize.AddLine(700,RGB(218,17,5),false);
	m_cMediumSize.SetValueColorChange(700,RGB(218,17,5));
}

void CVideoMFCDlg::UpdateDeviceCombo()
{
	m_cmbDrives.ResetContent();
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
	;

	// Add devices to combo box

	for (int i = 0; i < nUsed; i++)
	{
		m_cmbDrives.AddString(chListDevices[i]);

		// Set selection on current device

		if (nBurnDevices > 0) {
			if (0 == _tcsncmp(chBurnDevices[0], chListDevices[i], 2)) {
				m_cmbDrives.SetCurSel(i);
			}
		}
	}

	// Append multidevice item if more than one device in list

	if (nUsed > 1)
	{
		m_bMultideviceEnabled = true;
		m_cmbDrives.AddString(_T("Multiple devices"));
	}

	// Select multidevice item if more than one device is active

	if (nBurnDevices > 1)
		m_cmbDrives.SetCurSel(m_cmbDrives.GetCount()-1);
}

int32 CVideoMFCDlg::UpdateOptions()
{
	// Load options from controls
	SOptions opt;

	int32 res = ::GetOptions(&opt);
	HandleError(res);

	_tcscpy(opt.chVolumeLabel, _T("New"));
	opt.bEjectAfterBurn = m_bEject;
	opt.bFinalize = m_bFinalize;
	opt.bJolietFileSystem = m_bJoliet;

	// Set option to FoxBruner

	res = ::SetOptions(opt);
	HandleError(res);
	return res;
}

void CVideoMFCDlg::OnTabChange(NMHDR*, LRESULT* pResult)
{
	int nTab = m_tabLists.GetCurSel();

	m_lstVideoFiles.ShowWindow(nTab == 0 ? SW_SHOW : SW_HIDE);
	m_lstPictureFiles.ShowWindow(nTab == 1 ? SW_SHOW : SW_HIDE);

	*pResult = TRUE;
}

LRESULT CVideoMFCDlg::OnErrorNotify(WPARAM,LPARAM errCode)
{
	HandleError(errCode);
	return 0;
}

void CVideoMFCDlg::OnSaveLog()
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(m_strStartupDir + _T("\\FoxSampleVideoW.log"));
}