#include "stdafx.h"
#include "DataMFC.h"
#include "DataMFCDlg.h"
#include "ExtInfos.h"
#include "BootOptions.h"
#include "MultiSession.h"
#include "../Common/SampleBurnDlgMFC.h"
#include "../Common/AboutDlgMFC.h"
#include "PropertiesDlg.h"
#include "config.h"

#define WEBSITELINK			"http://www.isosdk.com"

/////////////////////////////////////////////////////////////////////////////
// CDataMFCDlg dialog

CDataMFCDlg::CDataMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataMFCDlg::IDD, pParent)
	, m_iSession(BS_CONTINUE_LAST_SESSION)
	, m_iProjectType(BS_BURNER_DATA)
	, m_bBurningDevicesOnly(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBBX_DRIVES, m_cmbDevice);
	DDX_Control(pDX, IDC_PROJECT_TYPE, m_cmbProjects);
	DDX_Control(pDX, IDC_TREE, m_lstFiles);
}

BEGIN_MESSAGE_MAP(CDataMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//Menu Commands
	ON_COMMAND(ID_FILE_ADDFILE, OnAddFile)
	ON_COMMAND(ID_FILE_ADDFOLDER, OnAddFolder)
	ON_COMMAND(ID_FILE_DELETESELECTED, OnDeleteSelected)
	ON_COMMAND(ID_FILE_RESET, OnReset)
	ON_COMMAND(ID_FILE_EXIT, OnCancel)
	ON_COMMAND(ID_FILE_CREATEFOLDER, OnCreateFolder)
	ON_COMMAND(ID_LANGUAGE_SETGERMAN, OnSetLanguageFileDe)
	ON_COMMAND(ID_LANGUAGE_SETENGLISH, OnSetLanguageFileEn)
	ON_COMMAND(ID_LANGUAGE_FRENCH, OnSetLanguageFileFr)
	ON_COMMAND(ID_LANGUAGE_SPANISH, OnSetLanguageFileEs)
	ON_COMMAND(ID_FILE_DISABLEFILEEXISTSCHECK, OnDisableFileExistCheck)

	ON_COMMAND(ID_BURN_BURNWITHDEVELOPEDGUI, OnBurnDiskDeveloped)
	ON_COMMAND(ID_BURN_BURNWITHFOXBURNEREMBEDDEDDIALOG, OnBurnDiskFoxBurner)
	ON_COMMAND(ID_BURN_ERASEDISK, OnEraseDisk)
	ON_COMMAND(ID_OPTIONS_EJECTDISK, OnSetEject)
	ON_COMMAND(ID_OPTIONS_VERIFY, OnSetVerify)
	ON_COMMAND(ID_OPTIONS_JOLIETFILESYSTEM, OnSetJoliet)
	ON_COMMAND(ID_OPTIONS_ROCKRIDGEFILESYSTEM, OnSetRockRidge)
	ON_COMMAND(ID_OPTIONS_FINALIZE, OnSetFinalize)
	ON_COMMAND(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, OnSetAllowLowercaseNames)
	ON_COMMAND(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, OnSetAllowManyDirectories)
	ON_COMMAND(ID_OPTIONS_ALLOW_LONG_ISO9660_NAMES, OnSetAllowLongISO9660Names)
	ON_COMMAND(ID_OPTIONS_ALLOW_LONG_JOLIET_NAMES, OnSetAllowLongJolietNames)
	ON_COMMAND_EX_RANGE(ID_ISO_LEVEL_1, ID_ISO_LEVEL_ROMEO, OnISOLevel)
	
	ON_COMMAND(ID_ADDITIONAL_EXTENDEDISOHEADER, OnExtHeader)
	ON_COMMAND(ID_ADDITIONAL_BOOTDISKSETTINGS, OnBootOptions)
	ON_COMMAND(ID_ADDITIONAL_IMPORTFROMSESSION, OnImportSession)
	ON_COMMAND(ID_ADDITIONAL_IMPORTLASTSESSION, OnImportLastSession)
	ON_COMMAND(ID_ADDITIONAL_IMPORTNOSESSION, OnImportNoSession)

	ON_COMMAND_EX(ID_IMAGES_MOUNTIMAGE, OnMountImage)
	ON_COMMAND(ID_IMAGES_UNMOUNTIMAGE, OnUnmountImage)
	ON_COMMAND(ID_IMAGES_BURNDISKIMAGE, OnBurnImage)

	ON_COMMAND_EX_RANGE(ID_INTERFACE_INTERNAL, ID_INTERFACE_FROGASPI, OnSetAspi)
	ON_COMMAND(ID_ASPI_RESCANDEVICES, OnRescanDevices)
	ON_COMMAND(ID_ASPI_BURNDEVICESONLY, OnBurningDevices)
	ON_COMMAND(ID_ASPI_DISABLEIMAGEWIRTER, OnDisableImagewriter)

	ON_COMMAND(ID_INFORMATION_SHOW, OnAbout)
	ON_COMMAND(ID_INFORMATION_WEB, OnWeb)
	ON_COMMAND(ID_FILE_WRITELOG, OnSaveLog)

	ON_CBN_SELCHANGE(IDC_CMBBX_DRIVES, OnDrives)
	ON_CBN_SELCHANGE(IDC_PROJECT_TYPE, OnProjectType)
	ON_MESSAGE(WM_ERROR_NOTIFY, OnErrorNotify)
	ON_COMMAND(ID_FILE_PROPERTIES, &CDataMFCDlg::OnFileProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataMFCDlg message handlers

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Data MFC Sample Application)

BOOL CDataMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetWindowText(_T(APP_TITLE));

	

    //--------------------------------------------------
    //Init the SDK
    //--------------------------------------------------

	TCHAR chLicenseKey[35] = _T("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7");
	int32 res = ::Initialize(chLicenseKey, BS_ASPI_INTERNAL, BS_TRUE);
	
	if (res != BS_SDK_ERROR_NO) {
		HandleError(res);
		PostQuitMessage(0);
		return FALSE;
	}
	
	//res = ::SetLanguage(_T("Default"));
	//HandleError(res);

	//----------------------------------------------------------
	//We need to set a project. So we set default project first
	//----------------------------------------------------------
	res = ::CreateProject(m_iProjectType, BS_CONTINUE_NO_SESSION);
	HandleError(res);

    //--------------------------------------------------
    //Set the Options. Remember, not all Options are
	//available on all projects. Read Help
    //--------------------------------------------------

	SOptions opt;
	res = ::GetOptions(&opt);
	HandleError(res);

	opt.bTestBurn = BS_FALSE;
	opt.bPerformOPC = BS_FALSE;
	opt.bJolietFileSystem = BS_TRUE;
	opt.bRockRidgeFileSystem = BS_FALSE;
	opt.bEjectAfterBurn = BS_TRUE;
	opt.nCacheSize = 4*1024*1024;
	opt.bFinalize = BS_FALSE;

	m_bEjectAfterBurn = opt.bEjectAfterBurn;
	m_bJoliet = opt.bJolietFileSystem;
	m_bRockRidge = opt.bRockRidgeFileSystem;
	m_bFinalize = opt.bFinalize;
	m_bVerify = opt.bVerifyAfterBurn;

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	res = ::SetOptions(opt);
	HandleError(res);

	SISOInfoEx isoInfo;
	res = ::GetISOInfoEx(&isoInfo);
	HandleError(res);

	m_bAllowLowercaseNames = isoInfo.ISOAllowLowercaseNames;
	m_bAllowManyDirectories = isoInfo.ISOAllowManyDirectories;
	m_bAllowLongISO9660Names = isoInfo.ISOAllowLongISO9660Names;
	m_bAllowLongJolietNames = isoInfo.ISOAllowLongJolietNames;
	
	m_lstFiles.Init(theApp);

	m_cmbProjects.AddString(_T("ISO 9660"));
	m_cmbProjects.AddString(_T("UDF"));
	m_cmbProjects.AddString(_T("ISO 9660/UDF Bridge"));
	m_cmbProjects.AddString(_T("Video DVD"));
	m_cmbProjects.AddString(_T("BluRay"));
	m_cmbProjects.SetCurSel(0);

	UpdateData(FALSE);

	//Fill Devicelist and Select
	UpdateDeviceCombo();

	//Set the Media Size Ruler.
	m_MediumSize.Attach(IDC_SIZE_DUMMY, this);

	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISK, m_bEjectAfterBurn ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_ROCKRIDGEFILESYSTEM, m_bRockRidge ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_FINALIZE, m_bFinalize ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_VERIFY, m_bVerify ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, m_bAllowLowercaseNames ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, m_bAllowManyDirectories ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LONG_ISO9660_NAMES, m_bAllowLongISO9660Names ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LONG_JOLIET_NAMES, m_bAllowLongJolietNames ? MF_CHECKED : MF_UNCHECKED);

	GetMenu()->CheckMenuItem(ID_INTERFACE_INTERNAL, MF_CHECKED);
	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	GetMenu()->CheckMenuItem(ID_ISO_LEVEL_1, MF_CHECKED);

	SetRuler();

	CheckDlgButton(IDC_CHKNOPATH, TRUE);

	GetCurrentDirectory(_MAX_PATH, m_strStartupDir.GetBuffer(_MAX_PATH));
	m_strStartupDir.ReleaseBuffer();

	SetCompareFilesForArrangementEventCallback(CDataMFCDlg::OnCompareFilesForArrangement, this);

	return TRUE;
}

CDataMFCDlg::~CDataMFCDlg()
{
	::DeInitialize();
}

void CDataMFCDlg::OnPaint()
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


HCURSOR CDataMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDataMFCDlg::OnAddFile()
{

	int32 savePath = BS_DONT_SAVE_PATH;
	if (!this->IsDlgButtonChecked(IDC_CHKNOPATH))
	{
		savePath = BS_WHOLE_PATH;
	}

	m_lstFiles.AddFile(savePath);

	// Update size rule

	Calculator();
}

void CDataMFCDlg::OnAddFolder()
{
	// Delegate to file tree control
	int32 savePath = BS_DONT_SAVE_PATH;
	if (!this->IsDlgButtonChecked(IDC_CHKNOPATH))
	{
		savePath = BS_WHOLE_PATH;
	}

	m_lstFiles.AddFolder(savePath);

	// Update size rule
	Calculator();
}

void CDataMFCDlg::OnCreateFolder()
{	
	m_lstFiles.CreateFolder();

	// Update size rule
	Calculator();
}


void CDataMFCDlg::OnRenameFile()
{
	HandleError(BS_SDK_ERROR_NOT_IMPLEMENTED);
}

void CDataMFCDlg::OnDeleteSelected()
{
	m_lstFiles.DeleteItem();

	// Update size rule
	Calculator();
}

//--------------------------------------------------
//Reset th e TreeView and set the MediaName as RootItem
//--------------------------------------------------
void CDataMFCDlg::OnReset()
{
	// Clear project

	::ClearAll();

	// Update file tree and size rule

	m_lstFiles.ResetList();
	Calculator();
}

//--------------------------------------------------
//Burn the CD or DVD
//--------------------------------------------------
void CDataMFCDlg::OnBurnDiskDeveloped()
{
	// Synchronize options and menu controls

	UpdateOptions();

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
	if (0 == _tcsncmp(_T("#"), chBurnDevices[0], 1))  // Iso writer selected
	{
		OnUnmountImage();
	}
}

void CDataMFCDlg::OnBurnDiskFoxBurner()
{
	// Synchronize options and menu controls

	UpdateOptions();

	// Call IsoSDK burn dialog

	int32 res = ::BurnDialog();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

//--------------------------------------------------
//Call the predefined Erase Dialog
//--------------------------------------------------
void CDataMFCDlg::OnEraseDisk()
{
	__int32 nError = EraseDialog(_T("IsoSDK"));
	HandleError(nError);

	UpdateDeviceCombo();
}


void CDataMFCDlg::OnSetEject()
{
	m_bEjectAfterBurn = !m_bEjectAfterBurn;
	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISK, m_bEjectAfterBurn ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetVerify()
{
	m_bVerify = !m_bVerify;
	GetMenu()->CheckMenuItem(ID_OPTIONS_VERIFY, m_bVerify ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetJoliet()
{
	m_bJoliet = !m_bJoliet;
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetRockRidge()
{
	m_bRockRidge = !m_bRockRidge;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ROCKRIDGEFILESYSTEM, m_bRockRidge ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetFinalize()
{
	m_bFinalize = !m_bFinalize;
	GetMenu()->CheckMenuItem(ID_OPTIONS_FINALIZE, m_bFinalize ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetAllowLowercaseNames()
{
	m_bAllowLowercaseNames = !m_bAllowLowercaseNames;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, m_bAllowLowercaseNames ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetAllowManyDirectories()
{
	m_bAllowManyDirectories = !m_bAllowManyDirectories;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, m_bAllowManyDirectories ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetAllowLongISO9660Names()
{
	m_bAllowLongISO9660Names = !m_bAllowLongISO9660Names;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LONG_ISO9660_NAMES, m_bAllowLongISO9660Names ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnSetAllowLongJolietNames()
{
	m_bAllowLongJolietNames = !m_bAllowLongJolietNames;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LONG_JOLIET_NAMES, m_bAllowLongJolietNames ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnExtHeader()
{
	CExtInfos dlg;
	dlg.DoModal();
}

void CDataMFCDlg::OnBootOptions()
{
	CBootOptions dlg;
	dlg.DoModal();
}

void CDataMFCDlg::OnImportSession()
{
	CMultiSession dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_nSession > 0)
		{
			// For importing session we should recreate project

			int32 res = ::CreateProject(m_iProjectType, dlg.m_nSession);
			HandleError(res);

			if (BS_SDK_ERROR_NO == res)
				m_iSession = dlg.m_nSession;

			// Update files and devices lists

			m_lstFiles.RefreshList();
			Calculator();
		}
	}
}

void CDataMFCDlg::OnImportLastSession()
{
	SMediumInfo infoMedium;
	int32 res = GetMediumInformation(BS_CURRENT_DEVICE, &infoMedium);
	HandleError(res);
	
	int32 session = infoMedium.nLastSession;
	res = ::CreateProject(m_iProjectType, session);
	HandleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		m_iSession = session;
	}	

	// Update files and devices lists

	m_lstFiles.RefreshList();
	Calculator();
}

void CDataMFCDlg::OnImportNoSession()
{
	// Don't import sessions
	m_iSession=BS_CONTINUE_NO_SESSION;

	// Refresh GUI and project.

    OnProjectType();
}

BOOL CDataMFCDlg::OnMountImage(UINT)
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("ISO Files (*.iso)|*.iso||"), this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetImageFilePath(dlg.GetPathName());
		HandleError(res);
		return res == BS_SDK_ERROR_NO ? TRUE : FALSE;
	}

	return FALSE;
}

void CDataMFCDlg::OnUnmountImage()
{
	::SetImageFilePath(NULL);
}

void CDataMFCDlg::OnBurnImage()
{
	// Get image path

	CFileDialog dlg(TRUE, NULL, NULL, 0, _T("Iso Files (*.iso)|*.iso|Cue Sheets (*.cue)|*.cue||"));

    if (IDOK != dlg.DoModal())
		return;

	CString strFileName = dlg.GetPathName().MakeLower();
	
	UpdateOptions();

	int32 res = 0;

	if (strFileName.Right(3) == _T("cue"))
	{
		res = ::CreateProject(BS_BURNER_CUE);
		HandleError(res);

		SFileToAdd fileToAdd;
		fileToAdd.lpszSourceFilePath = strFileName;
		res = ::AddFile(fileToAdd);
		HandleError(res);

		strFileName.Empty();
	}

	// Burn image with IsoSDK dialog

	res = ::BurnDialog(BS_FALSE, BS_FALSE, BS_TRUE, NULL, strFileName);
	HandleError(res);

	int32 nProjectType = 0;
	HandleError (::GetProjectType(&nProjectType));

	if (nProjectType == BS_BURNER_CUE)
	{
		::CreateProject(BS_BURNER_DATA, BS_NDEF);
		OnProjectType();
	}

	// Update devices list

	UpdateDeviceCombo();
}

BOOL CDataMFCDlg::OnSetAspi(UINT nAspi)
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

void CDataMFCDlg::OnRescanDevices()
{
	int32 res = ::RescanDevices();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

void CDataMFCDlg::OnBurningDevices()
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = !m_bBurningDevicesOnly;

	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	UpdateDeviceCombo();
}

void CDataMFCDlg::OnDisableImagewriter()
{
	bool bDisable = GetMenu()->GetMenuState(ID_ASPI_DISABLEIMAGEWIRTER, MF_BYCOMMAND) == MF_UNCHECKED;
	// Disable or enable image writer

	::EnableImageDevice(bDisable ? BS_FALSE : BS_TRUE);

	// Update devices list

	UpdateDeviceCombo();

	GetMenu()->CheckMenuItem(ID_ASPI_DISABLEIMAGEWIRTER, bDisable ? MF_CHECKED : MF_UNCHECKED);
}

void CDataMFCDlg::OnAbout()
{
	CAboutDlg	dlg(this);
	dlg.DoModal();
}

BOOL CDataMFCDlg::OnISOLevel(UINT nLevel)
{
	SISOInfoEx isoInfo;
	HandleError(::GetISOInfoEx(&isoInfo));

	UINT nISOLevel = BS_ISO_LEVEL_1 + nLevel - ID_ISO_LEVEL_1;
	isoInfo.ISOLevel = nISOLevel;

	HandleError(::SetISOInfoEx(isoInfo));

	HandleError(::GetISOInfoEx(&isoInfo));
	
	nISOLevel = isoInfo.ISOLevel;

	GetMenu()->CheckMenuItem(ID_ISO_LEVEL_1, nISOLevel == BS_ISO_LEVEL_1 ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_ISO_LEVEL_2, nISOLevel == BS_ISO_LEVEL_2 ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_ISO_LEVEL_3, nISOLevel == BS_ISO_LEVEL_3 ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_ISO_LEVEL_ROMEO, nISOLevel == BS_ISO_LEVEL_ROMEO ? MF_CHECKED : MF_UNCHECKED );

	return TRUE;	
}

void CDataMFCDlg::OnWeb()
{
	ShellExecute(0, _T("open"), _T(WEBSITELINK), 0, 0, SW_SHOW);
}


//--------------------------------------------------
//A new Drive was selected. Set now to SDK.
//--------------------------------------------------
void CDataMFCDlg::OnDrives()
{
	int index = m_cmbDevice.GetCurSel();

	if (index == m_cmbDevice.GetCount() - 1 && m_bMultideviceEnabled)
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

	m_lstFiles.RefreshList();
}

//--------------------------------------------------
//Calculate new Media size and set the Ruler
//--------------------------------------------------
void CDataMFCDlg::Calculator()
{
	int size = int(m_lstFiles.GetRootDirectorySize() / 1024 / 1024);

	if (size > 950) {

		m_MediumSize.SetValuePos(850);
	} else {
		m_MediumSize.SetValuePos((UINT) size);
	}
	m_MediumSize.RedrawWindow();
}

//--------------------------------------------------
//Handle the Error and put in Listbox
//--------------------------------------------------
void CDataMFCDlg::HandleError(__int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		__int32 nLength = 2048;

		GetText(errCode, chError, &nLength);

		MessageBox(chError, _T("Error"), MB_OK|MB_ICONERROR);
	}
}

//--------------------------------------------------
//Set the Media Ruler to Data CD
//--------------------------------------------------
void CDataMFCDlg::SetRuler()
{
	// Playtime is ax 750 MB.
	m_MediumSize.SetMaxRange(700+50);
	m_MediumSize.SetMarkTick(20);
	m_MediumSize.SetUnitTick(100);
	m_MediumSize.SetUnit("MB");
	m_MediumSize.RemoveAllLines();
	m_MediumSize.ResetValueColorZones();

	m_MediumSize.SetValueColorChange(0,RGB(35,126,216));

	// After 670 min, the is a critical size
	m_MediumSize.AddLine(700-30,RGB(247,200,10),false);
	m_MediumSize.SetValueColorChange(700-30,RGB(247,200,10));

	// After 700 MB most Media are full
	m_MediumSize.AddLine(700,RGB(218,17,5),false);
	m_MediumSize.SetValueColorChange(700,RGB(218,17,5));
}

void CDataMFCDlg::OnProjectType()
{
	// Map index to project type

	int indx = m_cmbProjects.GetCurSel();
	int32 type = BS_BURNER_DATA;

	switch (indx)
	{
	case 0:
		type = BS_BURNER_DATA; break;
	case 1:
		type = BS_BURNER_UDFDVD; break;
	case 2:
		type = BS_BURNER_ISOUDF; break;
	case 3:
		type = BS_BURNER_VIDEODVD; break;
	case 4:
		type = BS_BURNER_BLURAY; break;
	}

	// Save selected project type

	m_iProjectType = type;

	// Create selected project

	int32 res = ::CreateProject(m_iProjectType, m_iSession);
	HandleError(res);

	if (res != BS_SDK_ERROR_NO)
	{
		// Update project type in case of error
		::GetProjectType(&m_iProjectType);
		switch(m_iProjectType)
		{
		case BS_BURNER_DATA:	indx = 0; break;
		case BS_BURNER_UDFDVD:	indx = 1; break;
		case BS_BURNER_ISOUDF:	indx = 2; break;
		case BS_BURNER_VIDEODVD:indx = 3; break;
		case BS_BURNER_BLURAY:  indx = 4; break;
		default: ASSERT(0); break;
		}
		m_cmbProjects.SetCurSel(indx);
	}
	else
	{
		// Disable some menu items specific to project type

		SOptions opt;
		res = ::GetOptions(&opt);
		HandleError(res);

		bool bDisableFinalize = opt.bFinalize == BS_NDEF;
		bool bDisableJoliet = BS_BURNER_DATA == m_iProjectType || BS_BURNER_ISOUDF == m_iProjectType;
		bool bDisableRockRidge = BS_BURNER_DATA == m_iProjectType || BS_BURNER_ISOUDF == m_iProjectType;

		GetMenu()->EnableMenuItem(ID_OPTIONS_FINALIZE, bDisableFinalize ? MF_DISABLED : MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, bDisableJoliet ? MF_DISABLED : MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_ROCKRIDGEFILESYSTEM, bDisableRockRidge ? MF_DISABLED : MF_ENABLED);
	}

	// Update file list and size rule
	m_lstFiles.ResetList();
	Calculator();
}

void CDataMFCDlg::UpdateDeviceCombo()
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

int32 CDataMFCDlg::UpdateOptions()
{
	// Load options from controls

	SOptions opt;

	int32 res = ::GetOptions(&opt);
	HandleError(res);

	_tcscpy(opt.chVolumeLabel, _T("New"));
	opt.bEjectAfterBurn = m_bEjectAfterBurn;
	opt.bFinalize = m_bFinalize;
	opt.bJolietFileSystem = m_bJoliet;
	opt.bRockRidgeFileSystem = m_bRockRidge;
	opt.bVerifyAfterBurn = m_bVerify;
	opt.bPerformOPC = 1;

	// Set option to FoxBruner

	res = ::SetOptions(opt);
	HandleError(res);

	
	if(		(m_iProjectType == BS_BURNER_ISOUDF)
		||	(m_iProjectType == BS_BURNER_MIXEDMODE)
		||	(m_iProjectType == BS_BURNER_DATA)
	   )
	{

		SISOInfoEx isoInfo;
		res = ::GetISOInfoEx(&isoInfo);
		HandleError(res);

		isoInfo.ISOAllowLowercaseNames = m_bAllowLowercaseNames;
		isoInfo.ISOAllowManyDirectories = m_bAllowManyDirectories;
		isoInfo.ISOAllowLongISO9660Names = m_bAllowLongISO9660Names;
		isoInfo.ISOAllowLongJolietNames = m_bAllowLongJolietNames;
		
		res = ::SetISOInfoEx(isoInfo);
		HandleError(res);
	}

	return res;
}

LRESULT CDataMFCDlg::OnErrorNotify(WPARAM,LPARAM errCode)
{
	HandleError(errCode);
	return 0;
}

void CDataMFCDlg::OnFileProperties()
{
	int item = m_lstFiles.GetNextItem(-1, LVNI_FOCUSED);
	if (item >= 0)
	{
		SFileEntry* pFileEntry = (SFileEntry*)m_lstFiles.GetItemData(item);
		if (pFileEntry)
		{
			PropertiesDlg dlg(pFileEntry);
			if (dlg.DoModal())
				m_lstFiles.RefreshList();
		}
	}
}

void CDataMFCDlg::OnSetLanguageFileDe()
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("Language Files (*.ini)|*.ini||"), this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetLanguage(_T("German"),dlg.GetPathName());
		HandleError(res);
		return;
	}

	return;
}

void CDataMFCDlg::OnDisableFileExistCheck()
{
	::SetIgnoreFileExist(BS_TRUE);

	return;
}

void CDataMFCDlg::OnSetLanguageFileEn()
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("Language Files (*.ini)|*.ini||"), this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetLanguage(_T("English"), dlg.GetPathName());
		HandleError(res);
		return;
	}

	return;
}

void CDataMFCDlg::OnSetLanguageFileEs()
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("Language Files (*.ini)|*.ini||"), this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetLanguage(_T("Spanish"),dlg.GetPathName());
		HandleError(res);
		return;
	}

	return;
}

void CDataMFCDlg::OnSetLanguageFileFr()
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("Language Files (*.ini)|*.ini||"), this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetLanguage(_T("French"),dlg.GetPathName());
		HandleError(res);
		return;
	}

	return; 
}

BS_BOOL CDataMFCDlg::OnCompareFilesForArrangement(const SFileEntry *pFile1, const SFileEntry *pFile2, void *pUserData)
{
	// We are using pUserParam of each file to store the file priority marker.
	// Files with higher priority will be placed first in the resulting image.
	return pFile1->pUserParam > pFile2->pUserParam;
}

void CDataMFCDlg::OnSaveLog()
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(m_strStartupDir + _T("\\FoxSampleDataW.log"));
}