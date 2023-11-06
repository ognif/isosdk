#include "stdafx.h"
#include "AudioMFC.h"
#include "AudioMFCDlg.h"
#include "../Common/SampleBurnDlgMFC.h"
#include "../Common/AboutDlgMFC.h"
#include "config.h"

#define WEBSITELINK			"http://www.isosdk.com"

#import "shdocvw.dll"

class __declspec(uuid("0002DF01-0000-0000-C000-000000000046")) InternetExplorer;
struct __declspec(uuid("D30C1661-CDAF-11D0-8A3E-00C04FC9E26E")) IWebBrowser2;


HRESULT OpenURLWithData( LPCTSTR szURL, LPCTSTR szPostData )
{
    static const LPWSTR POST_HEADER_DATA = L"Content-Type: application/x-www-form-urlencoded\r\n";

    HRESULT hr = S_OK;
    SHDocVw::IWebBrowser2* pWebBrowser = NULL;
    BSTR bstrURL = NULL;
    BSTR bstrHeader = NULL;
    VARIANT vtPostData = {0};
    VARIANT vtEmpty;
    VARIANT vtHeader;
    int nPostDataSize;
    SAFEARRAY* saPostData = NULL;

    if ( !szURL )
        return E_INVALIDARG;

    do
    {
		USES_CONVERSION;

        //
        // Create the web browser instance
        //
        hr = ::CoCreateInstance( __uuidof(InternetExplorer), NULL, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
                               __uuidof(IWebBrowser2), reinterpret_cast<LPVOID *>(&pWebBrowser) );
        if( FAILED(hr) )
		{
			//Can't create instance of IE!
			return hr;
		}

        //
        // Convert URL to BSTR
        //
        bstrURL = SysAllocString( CT2OLE(szURL) );
        if ( !bstrURL )
        {
            hr = E_OUTOFMEMORY;
            break;
        }

        //
        // Create a variant for the header information
        //
        bstrHeader = SysAllocString( POST_HEADER_DATA );
        if ( !bstrHeader )
        {
            hr = E_OUTOFMEMORY;
            break;
        }
        VariantInit( &vtEmpty );
        VariantInit( &vtPostData );
        VariantInit( &vtHeader );

        V_VT( &vtHeader ) = VT_BSTR;
        V_BSTR( &vtHeader ) = bstrHeader;

        if ( szPostData )
        {
            //
            // Convert post data to a variant
            //
            nPostDataSize = (int)_tcslen( szPostData );
			saPostData = SafeArrayCreateVector( VT_UI1, 0, nPostDataSize+1 );
            if( NULL == saPostData )
            {
                hr = E_OUTOFMEMORY;
                break;
            }

			void* pvData = 0;

            hr = SafeArrayAccessData( saPostData, &pvData );
			if( FAILED(hr) )
			{
				break;
			}

			strncpy((char*)pvData, CT2A(szPostData), nPostDataSize+1 );

            hr = SafeArrayUnaccessData( saPostData );
			if( FAILED(hr) )
			{
				break;
			}

            V_VT(&vtPostData) = VT_ARRAY | VT_UI1;
            V_ARRAY(&vtPostData) = saPostData;
        }

        try
        {
            //
            // Show the web browser
            //
            pWebBrowser->put_Visible ( (VARIANT_BOOL) TRUE ); //  Ignore the hr - it's not really important either way

            //
            // Navigate to the requested URL
            //
            hr = pWebBrowser->Navigate( bstrURL, &vtEmpty, &vtEmpty, &vtPostData, &vtHeader );
            if( FAILED(hr) )
			{
				break;
			}
        }
        catch ( ... )
        {
			 // An exception was thrown calling the IE control!
            hr = E_FAIL;
        }

    }
    while ( FALSE );

    if( pWebBrowser )
	{
		pWebBrowser->Release();
	}
	if( bstrURL )
	{
		::SysFreeString(bstrURL);
	}
	if( bstrHeader )
	{
		::SysFreeString(bstrHeader);
	}
    if( saPostData )
    {
        SafeArrayDestroy( saPostData );
        saPostData = NULL;
    }

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// CAudioMFCDlg dialog

CAudioMFCDlg::CAudioMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioMFCDlg::IDD, pParent)
	, m_iProjectType(BS_BURNER_AUDIO)
	, m_bEjectAfterBurn(TRUE)
	, m_bJoliet(TRUE)
	, m_bRockRidge(FALSE)
	, m_bVerify(FALSE)
	, m_bFinalize(TRUE)
	, m_bBurningDevicesOnly(true)
	, m_nPlayTime(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAudioMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TABS, m_tabLists);
	DDX_Control(pDX, IDC_DEVICES, m_cmbDevice);
	DDX_Control(pDX, IDC_PROJECTTYPE, m_cmbProjects);
	DDX_Control(pDX, IDC_FILELIST, m_lstFiles);
	DDX_Control(pDX, IDC_TRACKLIST, m_lstTracks);
}

BEGIN_MESSAGE_MAP(CAudioMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_DEVICES, OnDrives)

	//Menu Commands
	ON_COMMAND(ID_AUDIO_ADDAUDIOFILE, OnAudioAddFile)
	ON_COMMAND(ID_AUDIO_DELETESELECTED, OnAudioDeleteFile)
	ON_COMMAND(ID_AUDIO_RESET, OnAudioReset)
	ON_COMMAND(ID_DATA_ADDFILE, OnDataAddFile)
	ON_COMMAND(ID_DATA_ADDFOLDER, OnDataAddFolder)
	ON_COMMAND(ID_DATA_CREATEFOLDER, OnDataCreateFolder)
	ON_COMMAND(ID_DATA_DELETESELECTED, OnDataDeleteFile)
	ON_COMMAND(ID_DATA_RESET, OnDataReset)
	ON_COMMAND(ID_DATA_ADDFOLDER, OnDataAddFolder)
	ON_COMMAND(ID_FILE_EXIT, OnCancel)
	ON_COMMAND_EX_RANGE(ID_ISO_LEVEL_1, ID_ISO_LEVEL_ROMEO, OnISOLevel)

	ON_COMMAND(ID_BURN_BURNWITHDEVELOPEDGUI, OnBurnDiskDeveloped)
	ON_COMMAND(ID_BURN_BURNWITHFOXBURNEREMBEDDEDDIALOG, OnBurnDiskFoxBurner)
	ON_COMMAND(ID_BURN_ERASEDISK, OnEraseDisk)
	ON_COMMAND(ID_OPTIONS_EJECTDISK, OnSetEject)
	ON_COMMAND(ID_OPTIONS_VERIFYAFTERBURN, OnSetVerify)
	ON_COMMAND(ID_WRITE_UNICODE, OnSetWriteUnicode)
	ON_COMMAND(ID_OPTIONS_JOLIETFILESYSTEM, OnSetJoliet)
	ON_COMMAND(ID_OPTIONS_ROCKRIDGEFILESYSTEM, OnSetRockRidge)
	ON_COMMAND(ID_OPTIONS_FINALIZE, OnSetFinalize)
	ON_COMMAND(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, OnSetAllowLowercaseNames)
	ON_COMMAND(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, OnSetAllowManyDirectories)

	ON_COMMAND(ID_AUDIO_PLAYSELECTED, OnPlayAudio)
	ON_COMMAND(ID_AUDIO_STOPPLAYBACK, OnStopAudio)
	ON_COMMAND(ID_AUDIO_LOADBASSPLUGIN, OnLoadPlugin)
	ON_COMMAND(ID_AUDIO_LOADBASSWMAPLUGIN, OnLoadPluginWMA)
	ON_COMMAND(ID_AUDIO_CDTEXT, OnDiskCdText)
	ON_COMMAND(ID_AUDIO_TRACKCDTEXT, OnTrackCdText)

	ON_COMMAND(ID_AUDIO_GETAUDIOFILESIZE, OnGetAudioFileSize)
	ON_COMMAND(ID_AUDIO_GETDISKSIZE, OnDiskSize)

	ON_COMMAND_EX_RANGE(ID_INTERFACE_INTERNAL, ID_INTERFACE_FROGASPI, OnSetAspi)
	ON_COMMAND(ID_ASPI_RESCANDEVICES, OnRescanDevices)
	ON_COMMAND(ID_ASPI_BURNDEVICESONLY, OnBurningDevices)
	ON_COMMAND(ID_ASPI_DISABLEIMAGEWIRTER, OnDisableImagewriter)

	ON_COMMAND(ID_INFORMATION_ABOUT, OnAbout)
	ON_COMMAND(ID_INFORMATION_WEB, OnWeb)
	ON_COMMAND(ID_FILE_LOGFILE, OnSaveLog)

	ON_NOTIFY(TCN_SELCHANGE,IDC_TABS,OnTabChange)

	ON_CBN_SELCHANGE(IDC_PROJECTTYPE, OnProjectType)
	ON_MESSAGE(WM_ERROR_NOTIFY, OnErrorNotify)
END_MESSAGE_MAP()


#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Audio MFC Sample Application)

BOOL CAudioMFCDlg::OnInitDialog()
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
	

    //--------------------------------------------------
    //We need to set a projet. So we set default project first
    //--------------------------------------------------
	res = ::CreateProject(BS_BURNER_AUDIO, BS_CONTINUE_NO_SESSION);
	HandleError(res);

    //--------------------------------------------------
    //Set the Options. Remember, not all Options are
	//aviable on all projects. Read Help
    //--------------------------------------------------
	SOptions opt;
	HandleError(GetOptions(&opt));

    _tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	m_bEjectAfterBurn = BS_BOOL2bool(opt.bEjectAfterBurn);
	m_bFinalize = BS_BOOL2bool(opt.bFinalize);
	m_bJoliet = BS_BOOL2bool(opt.bJolietFileSystem);
	m_bRockRidge = FALSE;

	HandleError(SetOptions(opt));

	BS_BOOL bWCDTU;
	HandleError(GetWriteCDTextInUnicode(&bWCDTU));
	m_bWriteCDTextInUnicode = BS_BOOL2bool(bWCDTU);
	
	// Init tab control and tabs

	m_tabLists.InsertItem(0, _T("Audio Content"));
	m_tabLists.InsertItem(1, _T("Data Content"));

	m_lstFiles.Init(theApp);
	m_lstTracks.Init(theApp);

	m_cmbProjects.AddString(_T("Audio"));
	m_cmbProjects.AddString(_T("Mixed Mode CD"));
	m_cmbProjects.SetCurSel(0);

	//Set the Media Size Ruler.
	m_cMediumSize.Attach(IDC_SIZE_DUMMY, this);
	SetRuler();

	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISK, m_bEjectAfterBurn ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_ROCKRIDGEFILESYSTEM, m_bRockRidge ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_FINALIZE, m_bFinalize ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_VERIFYAFTERBURN, m_bVerify ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_WRITE_UNICODE, m_bWriteCDTextInUnicode ? MF_CHECKED : MF_UNCHECKED);

	if(m_iProjectType != BS_BURNER_AUDIO)
	{
		SISOInfoEx isoInfo;	
		HandleError(::GetISOInfoEx(&isoInfo));

		m_bAllowLowercaseNames = isoInfo.ISOAllowLowercaseNames;
		m_bAllowManyDirectories = isoInfo.ISOAllowManyDirectories;
	
		GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, m_bAllowLowercaseNames ? MF_CHECKED : MF_UNCHECKED);
		GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, m_bAllowManyDirectories ? MF_CHECKED : MF_UNCHECKED);
	}


	GetMenu()->CheckMenuItem(ID_INTERFACE_INTERNAL, MF_CHECKED);
	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	GetMenu()->CheckMenuItem(ID_ISO_LEVEL_1, MF_CHECKED);

	UpdateDeviceCombo();

	GetCurrentDirectory(_MAX_PATH, m_strStartupDir.GetBuffer(_MAX_PATH));
	m_strStartupDir.ReleaseBuffer();

	OnProjectType();

	return TRUE;
}

CAudioMFCDlg::~CAudioMFCDlg()
{
	::DeInitialize();
}

void CAudioMFCDlg::OnPaint()
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


HCURSOR CAudioMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAudioMFCDlg::OnAudioAddFile()
{
	m_nPlayTime += m_lstTracks.AddFile();
	UpdateTime();
}

void CAudioMFCDlg::OnAudioDeleteFile()
{
	m_nPlayTime -= m_lstTracks.DeleteSelectedItems();
	UpdateTime();
}

void CAudioMFCDlg::OnAudioReset()
{
	int32 res = ::ClearAll();
	HandleError(res);

	m_nPlayTime = 0;

	m_lstTracks.ResetList();
	m_lstFiles.ResetList();
	UpdateTime();
}

void CAudioMFCDlg::OnDataAddFile()
{
	m_lstFiles.AddFile();
	UpdateTime();
}

void CAudioMFCDlg::OnDataAddFolder()
{
	m_lstFiles.AddFolder();
	UpdateTime();
}

void CAudioMFCDlg::OnDataCreateFolder()
{
	m_lstFiles.CreateFolder();
	UpdateTime();
}

void CAudioMFCDlg::OnDataDeleteFile()
{
	m_lstFiles.DeleteItem();
	UpdateTime();
}

void CAudioMFCDlg::OnDataReset()
{
	OnAudioReset();
}

void CAudioMFCDlg::OnBurnDiskDeveloped()
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
		if (!OnMountImage())
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

void CAudioMFCDlg::OnBurnDiskFoxBurner()
{
	// Synchronize options and menu controls

	UpdateOptions();

	// Call IsoSDK burn dialog

	int32 res = ::BurnDialog();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

void CAudioMFCDlg::OnEraseDisk()
{
	__int32 nError = EraseDialog(_T("IsoSDK SDK"));
	HandleError(nError);

	UpdateDeviceCombo();
}

void CAudioMFCDlg::OnSetEject()
{
	m_bEjectAfterBurn = !m_bEjectAfterBurn;
	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISK, m_bEjectAfterBurn ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnSetVerify()
{
	m_bVerify = !m_bVerify;
	GetMenu()->CheckMenuItem(ID_OPTIONS_VERIFYAFTERBURN, m_bVerify ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnSetJoliet()
{
	m_bJoliet = !m_bJoliet;
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnSetRockRidge()
{
	m_bRockRidge = !m_bRockRidge;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ROCKRIDGEFILESYSTEM, m_bRockRidge ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnSetFinalize()
{
	m_bFinalize = !m_bFinalize;
	GetMenu()->CheckMenuItem(ID_OPTIONS_FINALIZE, m_bFinalize ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnSetWriteUnicode()
{
	m_bWriteCDTextInUnicode = !m_bWriteCDTextInUnicode;
	GetMenu()->CheckMenuItem(ID_WRITE_UNICODE, m_bWriteCDTextInUnicode ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnSetAllowLowercaseNames()
{
	m_bAllowLowercaseNames = !m_bAllowLowercaseNames;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, m_bAllowLowercaseNames ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnSetAllowManyDirectories()
{
	m_bAllowManyDirectories = !m_bAllowManyDirectories;
	GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, m_bAllowManyDirectories ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnPlayAudio()
{
	m_lstTracks.Play();
}

void CAudioMFCDlg::OnStopAudio()
{
	int32 res = ::AudioFileStop();
	HandleError(res);
}

void CAudioMFCDlg::OnLoadPlugin()
{
#ifdef _UNICODE
	int32 res = ::LoadBassPlugin(L"bass_ape.dll");
#else
	int32 res = ::LoadBassPlugin("bass_ape.dll");
#endif
    HandleError(res);
}

void CAudioMFCDlg::OnLoadPluginWMA()
{
#ifdef _UNICODE
	int32 res = ::LoadBassPlugin(L"basswma.dll");
#else
	int32 res = ::LoadBassPlugin("basswma.dll");
#endif
	
    HandleError(res);
}

void CAudioMFCDlg::OnDiskCdText()
{
	m_lstTracks.DiskCDText();
}

void CAudioMFCDlg::OnGetAudioFileSize()
{
	CString strSectors;
	double tSize = m_lstTracks.GetAudioFileSizeEx();
	if(tSize>0) {
		tSize = tSize / 1024 / 1024;
	}
	strSectors.Format(_T("Audio file size on disk: %.2f MB"), tSize);
	MessageBox(strSectors, _T("Information"));
}

void CAudioMFCDlg::OnDiskSize()
{
	int32 res = ::Prepare();
	HandleError(res);

	double fSize = 0.0;
	res = ::GetImageSize(&fSize);
	HandleError(res);

	if (fSize>0) {
		fSize = fSize / 1024 / 1024;
	}

	CString strDiskSize;
	strDiskSize.Format(_T("Disk size: %.2f MB"), fSize);

	MessageBox(strDiskSize, _T("Information"));
}


void CAudioMFCDlg::OnTrackCdText()
{
	m_lstTracks.TrackCDText();
}

BOOL CAudioMFCDlg::OnSetAspi(UINT nAspi)
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

void CAudioMFCDlg::OnRescanDevices()
{
	int32 res = ::RescanDevices();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

void CAudioMFCDlg::OnBurningDevices()
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = !m_bBurningDevicesOnly;

	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	UpdateDeviceCombo();
}

void CAudioMFCDlg::OnDisableImagewriter()
{
	bool bDisable = GetMenu()->GetMenuState(ID_ASPI_DISABLEIMAGEWIRTER, MF_BYCOMMAND) == MF_UNCHECKED;
	// Disable or enable image writer

	::EnableImageDevice(bDisable ? BS_FALSE : BS_TRUE);

	// Update devices list

	UpdateDeviceCombo();

	GetMenu()->CheckMenuItem(ID_ASPI_DISABLEIMAGEWIRTER, bDisable ? MF_CHECKED : MF_UNCHECKED);
}

void CAudioMFCDlg::OnAbout()
{
	CAboutDlg	dlg(this);
	dlg.DoModal();
}

BOOL CAudioMFCDlg::OnISOLevel(UINT nLevel)
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

void CAudioMFCDlg::OnWeb()
{
	ShellExecute(0, _T("open"), _T(WEBSITELINK), 0, 0, SW_SHOW);
}

void CAudioMFCDlg::OnDrives()
{
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

	m_lstFiles.RefreshList();
}

void CAudioMFCDlg::OnProjectType()
{
	int indx = m_cmbProjects.GetCurSel();
	m_iProjectType = indx == 0 ? BS_BURNER_AUDIO : BS_BURNER_MIXEDMODE;

	int32 res = ::CreateProject(m_iProjectType, BS_CONTINUE_NO_SESSION);
	HandleError(res);

	if (m_iProjectType == BS_BURNER_AUDIO)
	{
		GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_GRAYED|MF_BYPOSITION);
		GetMenu()->EnableMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_ROCKRIDGEFILESYSTEM, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_VERIFYAFTERBURN, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_FINALIZE, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, MF_GRAYED);

		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_1, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_2, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_3, MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_ROMEO, MF_GRAYED);
			
		m_lstTracks.SetRootDirectory(PATHSEPSTRING);
		m_lstFiles.SetRootDirectory(PATHSEPSTRING);
	}
	else
	{
		GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_ENABLED|MF_BYPOSITION);
		GetMenu()->EnableMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_ROCKRIDGEFILESYSTEM, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_VERIFYAFTERBURN, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_FINALIZE, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, MF_ENABLED);
		
		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_1, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_2, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_3, MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_ISO_LEVEL_ROMEO, MF_ENABLED);

		SISOInfoEx isoInfo;	
		HandleError(::GetISOInfoEx(&isoInfo));

		m_bAllowLowercaseNames = isoInfo.ISOAllowLowercaseNames;
		m_bAllowManyDirectories = isoInfo.ISOAllowManyDirectories;
	
		GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_LOWERCASE_NAMES, m_bAllowLowercaseNames ? MF_CHECKED : MF_UNCHECKED);
		GetMenu()->CheckMenuItem(ID_OPTIONS_ALLOW_MANY_DIRECTORIES, m_bAllowManyDirectories ? MF_CHECKED : MF_UNCHECKED);
		

		m_lstTracks.SetRootDirectory(_T("\\audio"));
		m_lstFiles.SetRootDirectory(_T("\\data"));
	}

	m_nPlayTime = 0;
	m_lstTracks.ResetList();
	m_lstFiles.ResetList();
	m_cMediumSize.SetValuePos(0);
}

BOOL CAudioMFCDlg::OnMountImage()
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("CUE/BIN Files (*.bin)|*.bin||"), this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPath = dlg.GetPathName();
		if (dlg.GetFileExt().MakeLower() != _T("bin"))
			strPath += ".bin";

		int32 res = ::SetImageFilePath(strPath);
		HandleError(res);
		return res == BS_SDK_ERROR_NO ? TRUE : FALSE;
	}

	return FALSE;
}


//--------------------------------------------------
//Handle the Error and put in Listbox
//--------------------------------------------------
void CAudioMFCDlg::HandleError(__int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		__int32 nLength = 2048;

		GetText(errCode, chError, &nLength);

		MessageBox(chError, _T("Error"), MB_OK | MB_ICONERROR);
	}
}

//--------------------------------------------------
//Update the Media Ruler.
//--------------------------------------------------
void CAudioMFCDlg::UpdateTime()
{
	int sectors = m_nPlayTime*75;

	if (m_iProjectType == BS_BURNER_MIXEDMODE)
		sectors += int(m_lstFiles.GetRootDirectorySize() / 2048);

	m_cMediumSize.SetValuePos(sectors/(75*60));
	m_cMediumSize.Invalidate();
}

//--------------------------------------------------
//Set the Media Ruler to AudioCD
//--------------------------------------------------
void CAudioMFCDlg::SetRuler()
{
		//Playtime is ax 90 min.
		m_cMediumSize.SetMaxRange(90);
		m_cMediumSize.SetMarkTick(5);
		m_cMediumSize.SetUnitTick(10);
		m_cMediumSize.SetUnit("Min");
		m_cMediumSize.RemoveAllLines();
		m_cMediumSize.ResetValueColorZones();

		m_cMediumSize.SetValueColorChange(0,RGB(35,126,216));

		//Affter 74 most Media are full
		m_cMediumSize.AddLine(74,RGB(247,200,10),false);
		m_cMediumSize.SetValueColorChange(74,RGB(247,200,10));

		//After 80 min, the is a critical size
		m_cMediumSize.AddLine(80,RGB(218,17,5),false);
		m_cMediumSize.SetValueColorChange(80,RGB(218,17,5));
}

void CAudioMFCDlg::UpdateDeviceCombo()
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

int32 CAudioMFCDlg::UpdateOptions()
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

	// Set option to FoxBruner

	res = ::SetOptions(opt);
	HandleError(res);

	HandleError(::SetWriteCDTextInUnicode(m_bWriteCDTextInUnicode));

	
	if (m_iProjectType != BS_BURNER_AUDIO)
	{
		SISOInfoEx isoInfo;
		res = ::GetISOInfoEx(&isoInfo);
		HandleError(res);

		isoInfo.ISOAllowLowercaseNames = m_bAllowLowercaseNames;
		isoInfo.ISOAllowManyDirectories = m_bAllowManyDirectories;
		

		res = ::SetISOInfoEx(isoInfo);
		HandleError(res);
	}

	return res;
}

void CAudioMFCDlg::OnTabChange(NMHDR*, LRESULT* pResult)
{
	int nTab = m_tabLists.GetCurSel();

	if (nTab == 0)
	{
		m_lstTracks.ShowWindow(SW_SHOW);
		m_lstFiles.ShowWindow(SW_HIDE);
	}
	else
	{
		m_lstFiles.ShowWindow(SW_SHOW);
		m_lstTracks.ShowWindow(SW_HIDE);
	}

	*pResult = TRUE;
}

LRESULT CAudioMFCDlg::OnErrorNotify(WPARAM, LPARAM errCode)
{
	HandleError((int)errCode);
	return 0;
}

void CAudioMFCDlg::OnSaveLog()
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(m_strStartupDir + _T("\\FoxSampleAudioW.log"));
}