#include "stdafx.h"
#include "AudioFOXLibDlg.h"
#include "TrackList.h"
#include "resources.h"
#include "../Common/SampleBurnDlg.h"
#include "../Common/AboutDlg.h"
#include "../Common/FileTreeFoxLib.h"
#include "../Common/CommonFoxLib.h"

#define WEBSITELINK			"http://www.isosdk.com"


FXDEFMAP(KAudioFOXLibDlg) KAudioFOXLibMap[]= {
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_ADDAUDIOFILE, KAudioFOXLibDlg::onAddAudioFile),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_DELETEAUDIOITEM, KAudioFOXLibDlg::onDeleteAudioItem),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_RESETLIST, KAudioFOXLibDlg::onResetList),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_ADDDATAFILE, KAudioFOXLibDlg::onAddDataFile),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_WRITELOG, KAudioFOXLibDlg::onWriteLogFile),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_ADDDATAFOLDER, KAudioFOXLibDlg::onAddFolder),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_RENAMEFILE, KAudioFOXLibDlg::onRenameFile),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_DELETEDATAITEM, KAudioFOXLibDlg::onDeleteDataItem),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_BURNDISK_DEVELOPED, KAudioFOXLibDlg::onBurnDiskDeveloped),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_BURNDISK_FOXBURNER, KAudioFOXLibDlg::onBurnDiskFoxBurner),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_ERASEDISK, KAudioFOXLibDlg::onEraseDisk),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_VERIFY, KAudioFOXLibDlg::onVerifySelect),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_PLAY, KAudioFOXLibDlg::onPlay),
    FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_PLUGIN1, KAudioFOXLibDlg::onLoadPlugin1),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_STOPPLAY, KAudioFOXLibDlg::onStopPlay),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_DISKTEXT, KAudioFOXLibDlg::onDiskText),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_TRACKTEXT, KAudioFOXLibDlg::onTrackText),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_AUDIOFILESIZE, KAudioFOXLibDlg::onAudioFileSize),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_DISKSIZE, KAudioFOXLibDlg::onDiskSize),
	FXMAPFUNCS(SEL_COMMAND, KAudioFOXLibDlg::ID_ASPI_INTERNAL, KAudioFOXLibDlg::ID_ASPI_FROGASPI, KAudioFOXLibDlg::onCmdAspi),
	FXMAPFUNCS(SEL_UPDATE, KAudioFOXLibDlg::ID_ASPI_INTERNAL, KAudioFOXLibDlg::ID_ASPI_FROGASPI, KAudioFOXLibDlg::onUpdAspi),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_RESCANDEVICES, KAudioFOXLibDlg::onRescanDevices),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_BURNDEVICES, KAudioFOXLibDlg::onBurningDevices),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_DISABLEIMAGE, KAudioFOXLibDlg::onDisableImagewriter),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_ABOUT, KAudioFOXLibDlg::onAbout),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_WEB, KAudioFOXLibDlg::onWeb),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_DEVICEBOX, KAudioFOXLibDlg::onDeviceBoxChange),
	FXMAPFUNC(SEL_COMMAND, KAudioFOXLibDlg::ID_PROJECTTYPE, KAudioFOXLibDlg::onProjectTypeChange),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KAudioFOXLibDlg::onCmdCancel),
	FXMAPFUNC(KAudioFOXLibDlg::SEL_ERRORNOTIFY, 0, KAudioFOXLibDlg::onErrorNotify),
	FXMAPFUNC(SEL_CLOSE, 0, FXDialogBox::onCmdCancel)
};

FXIMPLEMENT(KAudioFOXLibDlg, FXDialogBox, KAudioFOXLibMap, ARRAYNUMBER(KAudioFOXLibMap))

KAudioFOXLibDlg::KAudioFOXLibDlg()
{
}

KAudioFOXLibDlg::KAudioFOXLibDlg(FXApp *app, const FXString &title)
	: FXDialogBox(app, title, DECOR_ALL, 0, 0, 600, 500, 0, 0, 0, 0, 0, 0)
	, m_iProjectType(BS_BURNER_AUDIO)
	, m_bEjectAfterBurn(true)
	, m_bJoliet(true)
	, m_bRockRidge(false)
	, m_bVerify(false)
	, m_bFinalize(true)
	, m_bBurningDevicesOnly(true)
	, m_bWriteCDTextInUnicode(false)
	, m_bAllowLowercaseNames(false)
	, m_bAllowManyDirectories(false)
{

	// Load icons for menu
	FXIcon *fileAddIcon = new FXICOIcon(getApp(), addfile);
	FXIcon *folderAddIcon = new FXICOIcon(getApp(), addfolder);
	FXIcon *deleteIcon = new FXICOIcon(getApp(), selection);
	FXIcon *resetIcon = new FXICOIcon(getApp(), reset);
	FXIcon *eraseIcon = new FXICOIcon(getApp(), cd_erase);
	FXIcon *burnIcon = new FXICOIcon(getApp(), burn_iso);
	FXIcon *cancelIcon = new FXICOIcon(getApp(), cancel);
	FXIcon *audioIcon = new FXICOIcon(getApp(), audio);
	FXIcon *isoIcon = new FXICOIcon(getApp(), iso);
	FXIcon *playIcon = new FXICOIcon(getApp(), play);
	FXIcon *stopIcon = new FXICOIcon(getApp(), stop);
	FXIcon *refreshIcon = new FXICOIcon(getApp(), refresh2);
	FXIcon *isosdkIconSmall = new FXICOIcon(getApp(), isosdksmall);
	FXIcon *isosdkIconBig = new FXICOIcon(getApp(), isosdkbig);

	///////////////////////////////////////////////////////////////////
	// Create menu bar

	FXMenuBar *menubar = new FXMenuBar(this, LAYOUT_FILL_X);

	FXMenuPane *filemenu = new FXMenuPane(this);
		FXMenuPane* audiofilemenu = new FXMenuPane(this);
			new FXMenuCommand(audiofilemenu, "Add audio file...", fileAddIcon, this, ID_ADDAUDIOFILE);
			new FXMenuCommand(audiofilemenu, "Delete selected", deleteIcon, this, ID_DELETEAUDIOITEM);
			new FXMenuCommand(audiofilemenu, "Reset", resetIcon, this, ID_RESETLIST);
		new FXMenuCascade(filemenu, "&Audio", audioIcon, audiofilemenu);
		FXMenuPane* datamenu = new FXMenuPane(this);
			new FXMenuCommand(datamenu,"&Add file/folder...", fileAddIcon, this, ID_ADDDATAFILE);
			new FXMenuCommand(datamenu,"&Create folder...", folderAddIcon, this, ID_ADDDATAFOLDER);
			new FXMenuCommand(datamenu,"Re&name file...", NULL, this, ID_RENAMEFILE);
			new FXMenuCommand(datamenu,"&Delete selected", deleteIcon, this, ID_DELETEDATAITEM);
			new FXMenuCommand(datamenu,"&Reset", resetIcon, this, ID_RESETLIST);
		m_dataMenu = new FXMenuCascade(filemenu, "&Data", isoIcon, datamenu);
		new FXMenuCommand(filemenu,"Write log", NULL, this, ID_WRITELOG);	
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"E&xit", cancelIcon, this, FXDialogBox::ID_CANCEL);
	new FXMenuTitle(menubar, "&File", NULL, filemenu);

	FXMenuPane *burnmenu = new FXMenuPane(this);
		new FXMenuCommand(burnmenu,"&Burn with custom dialog...", burnIcon, this, ID_BURNDISK_DEVELOPED);
		new FXMenuCommand(burnmenu,"Burn with &IsoSDK embedded dialog...", burnIcon, this, ID_BURNDISK_FOXBURNER);
		new FXMenuCommand(burnmenu,"&Erase Disk...", eraseIcon, this, ID_ERASEDISK);
		new FXHorizontalSeparator(burnmenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
	FXMenuPane *optionsmenu = new FXMenuPane(this);
		new FXMenuCheck(optionsmenu,"&Eject disk", &m_tgtEjectAfterBurn, FXDataTarget::ID_VALUE);
			m_chkVerify = new FXMenuCheck(optionsmenu,"&Verify after burn", this, ID_VERIFY);
			m_chkJoliet = new FXMenuCheck(optionsmenu,"&Joliet file system", &m_tgtJoliet, FXDataTarget::ID_VALUE);
			m_chkRockRidge = new FXMenuCheck(optionsmenu,"&Rock Ridge file system", &m_tgtRockRidge, FXDataTarget::ID_VALUE);
			m_chkFinalize = new FXMenuCheck(optionsmenu,"&Finalize", &m_tgtFinalize, FXDataTarget::ID_VALUE);
			m_chkAllowLowercaseNames = new FXMenuCheck(optionsmenu,"Allow &lowercase names", &m_tgtAllowLowercaseNames, FXDataTarget::ID_VALUE);
			m_chkAllowManyDirectories = new FXMenuCheck(optionsmenu,"Allow &many directories", &m_tgtAllowManyDirectories, FXDataTarget::ID_VALUE);
			FXHorizontalFrame* ISOLevelFrame = new FXHorizontalFrame(optionsmenu, LAYOUT_FILL_X);
				new FXLabel(ISOLevelFrame, "ISO level:");
				m_lboxISOLevel = new FXListBox(ISOLevelFrame);
				m_lboxISOLevel->appendItem(_T("Level 1"));
				m_lboxISOLevel->appendItem(_T("Level 2"));
				m_lboxISOLevel->appendItem(_T("Level 3"));
				m_lboxISOLevel->appendItem(_T("Romeo"));								
		new FXMenuCascade(burnmenu, "&Options", NULL, optionsmenu);
	new FXMenuTitle(menubar, "&Burn", NULL, burnmenu);

	FXMenuPane* audiomenu = new FXMenuPane(this);
		new FXMenuCommand(audiomenu, "Play selected", playIcon, this, ID_PLAY);
		new FXMenuCommand(audiomenu, "Stop playback", stopIcon, this, ID_STOPPLAY);
        new FXMenuCommand(audiomenu, "Load Bass Ape plugin", NULL, this, ID_PLUGIN1);
		new FXHorizontalSeparator(audiomenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(audiomenu, "CD text", audioIcon, this, ID_DISKTEXT);
		new FXMenuCommand(audiomenu, "Track CD text", audioIcon, this, ID_TRACKTEXT);
		m_chkWriteCDTextInUnicode = new FXMenuCheck(audiomenu, "Write CD text in &unicode", &m_tgtWriteCDTextInUnicode, FXDataTarget::ID_VALUE);
		new FXHorizontalSeparator(audiomenu, LAYOUT_FILL_X | SEPARATOR_GROOVE);
		new FXMenuCommand(audiomenu, "Get audio file size(on disk)", NULL, this, ID_AUDIOFILESIZE);
		new FXMenuCommand(audiomenu, "Get disk size", NULL, this, ID_DISKSIZE);
		new FXMenuTitle(menubar, "&Audio", NULL, audiomenu);

	FXMenuPane* aspimenu = new FXMenuPane(this);
		FXMenuPane* interfacemenu = new FXMenuPane(this);
			new FXMenuRadio(interfacemenu, "&Internal", this, ID_ASPI_INTERNAL);
			new FXMenuRadio(interfacemenu, "&WnAspi", this, ID_ASPI_WNASPI);
			new FXMenuRadio(interfacemenu, "&FrogAspi", this, ID_ASPI_FROGASPI);
		new FXMenuCascade(aspimenu, "&Interface", NULL, interfacemenu);
		new FXMenuCommand(aspimenu,"&Rescan devices", refreshIcon, this, ID_RESCANDEVICES);
		burnDevicesOnly = new FXMenuCheck(aspimenu,"&Burn devices only", this, ID_BURNDEVICES);
		new FXMenuCheck(aspimenu,"&Disable imagewriter", this, ID_DISABLEIMAGE);
	new FXMenuTitle(menubar, "A&SPI/SPTI", NULL, aspimenu);

	FXMenuPane* infomenu = new FXMenuPane(this);
		new FXMenuCommand(infomenu, "&About", NULL, this, ID_ABOUT);
		new FXMenuCommand(infomenu, "&Web", NULL, this, ID_WEB);
	new FXMenuTitle(menubar, "I&nformation", NULL, infomenu);

	// Set checks for some menus



	// Device combo
	FXHorizontalFrame *deviceFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X);
		new FXLabel(deviceFrame, "Device: ", NULL, JUSTIFY_LEFT|LAYOUT_FIX_WIDTH, 0, 0, 70);
		m_cmbDevice = new FXComboBox(deviceFrame, 30, this, ID_DEVICEBOX, LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC, 200);

	// Projects combo
	FXHorizontalFrame* projectFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X);
		new FXLabel(projectFrame, "Project type: ", NULL, JUSTIFY_LEFT|LAYOUT_FIX_WIDTH, 0, 0, 70);
		m_cmbProjectType = new FXComboBox(projectFrame, 10, this, ID_PROJECTTYPE, FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
		m_cmbProjectType->appendItem("Audio CD", (void*)BS_BURNER_AUDIO);
		m_cmbProjectType->appendItem("Mixed Mode CD", (void*)BS_BURNER_MIXEDMODE);
		m_cmbProjectType->setNumVisible(m_cmbProjectType->getNumItems());

	// Time rule
	m_rule = new KCDTimeRule(this, FRAME_THICK|LAYOUT_BOTTOM|LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|LAYOUT_FIX_HEIGHT, 0, 0, 0, 30);



		

	setMiniIcon(isosdkIconSmall);
	setIcon(isosdkIconBig);



	m_bEjectAfterBurn = 1;
	m_bJoliet = 1;
	m_bRockRidge = 1;
	m_bFinalize = 1;
	m_bAllowLowercaseNames = 1;
	m_bAllowManyDirectories = 1;
	m_bAllowLowercaseNames = 1;
	m_bAllowManyDirectories = 1;

	


	m_tgtEjectAfterBurn.connect(m_bEjectAfterBurn);
	m_tgtFinalize.connect(m_bFinalize);
	m_tgtJoliet.connect(m_bJoliet);
	m_tgtRockRidge.connect(m_bRockRidge);
	m_tgtWriteCDTextInUnicode.connect(m_bWriteCDTextInUnicode);
	m_tgtAllowLowercaseNames.connect(m_bAllowLowercaseNames);
	m_tgtAllowManyDirectories.connect(m_bAllowManyDirectories);




	m_strStartupDir = FXSystem::getCurrentDirectory();
}

//--------------------------------------------------------------
// First Load and build Class then load SDK settings to the app
// to make sure that the Fox-Toolkit is initialized the right way.
//--------------------------------------------------------------
void KAudioFOXLibDlg::loadOwner()
{

	//--------------------------------------------------
	//Init the SDK
	//--------------------------------------------------

#if defined LINUX
	TCHAR chLicenseKey[35] = _T("3GTF75-2UM4AX-18LAHC-BX1FOR-N38Y32");
#endif

#if defined MAC
	TCHAR chLicenseKey[35] = _T("NPTD4B-WVZ3A7-KZPA9G-B91CYR-2U8TTN");
#endif

#if defined WIN32
	TCHAR chLicenseKey[35] = _T("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7");
#endif

	int32 res = ::Initialize(chLicenseKey, BS_ASPI_INTERNAL, BS_TRUE);
	if (res != BS_SDK_ERROR_NO) {
		handleError(res);
		::exit(1);
	}

	// Set global fxapp to SDK
	res = ::SetFXApp(this);
	handleError(res);

	if (m_bVerify)
		m_chkVerify->setCheck();
	if (m_bBurningDevicesOnly)
		burnDevicesOnly->setCheck();

	//--------------------------------------------------
	//We need to set a project. So we set default project first
	//--------------------------------------------------
	FXTabBook* tabs = new FXTabBook(this, NULL, 0, TABBOOK_NORMAL | LAYOUT_FILL_X | LAYOUT_FILL_Y);
	new FXTabItem(tabs, "Audio content");
	m_trackList = new KTrackList(tabs, this, ID_TRACKLIST, LAYOUT_FILL | FRAME_THICK | ICONLIST_DETAILED | ICONLIST_EXTENDEDSELECT);
	m_dataTab = new FXTabItem(tabs, "Data content");
	m_fileList = new KFileList(tabs, this, ID_FILELIST, LAYOUT_FILL | FRAME_THICK | ICONLIST_DETAILED | ICONLIST_EXTENDEDSELECT);

	onProjectTypeChange(this, 0, 0);

	res = ::CreateProject(m_iProjectType, BS_CONTINUE_NO_SESSION);
	handleError(res);

	//--------------------------------------------------
	 //Set the Options. Remember, not all Options are
	 //available on all projects. Read Help
	 //--------------------------------------------------

	SOptions opt;

	res = GetOptions(&opt);
	handleError(res);

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	m_bEjectAfterBurn = opt.bEjectAfterBurn;
	m_bFinalize = opt.bFinalize;
	m_bJoliet = opt.bJolietFileSystem;
	m_bRockRidge = false;

	if (m_iProjectType != BS_BURNER_AUDIO)
	{
		SISOInfoEx isoInfo;
		res = ::GetISOInfoEx(&isoInfo);
		handleError(res);

		m_bAllowLowercaseNames = isoInfo.ISOAllowLowercaseNames;
		m_bAllowManyDirectories = isoInfo.ISOAllowManyDirectories;
	}

	res = SetOptions(opt);
	handleError(res);


	int8 bWriteCDTextUnicode;
	res = ::GetWriteCDTextInUnicode(&bWriteCDTextUnicode);
	handleError(res);
	m_bWriteCDTextInUnicode = bWriteCDTextUnicode;
	//--------------------------------------------------
	//Fill Devicelist and Select
	//--------------------------------------------------

	updateDeviceCombo();


}

KAudioFOXLibDlg::~KAudioFOXLibDlg()
{
	onResetList(0,0,0);
	::DeInitialize();
}

long KAudioFOXLibDlg::onWriteLogFile(FXObject* sender, FXSelector key, void* data)
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(KString(m_strStartupDir.text()) + PATHSEPSTRING + "FoxSampleAudioC.log");
	return 1;
}

long KAudioFOXLibDlg::onAddDataFile(FXObject* sender, FXSelector key, void* data)
{
	m_fileList->AddFile();
	m_rule->SetDataTimeValue(FXint(m_fileList->GetRootDirectorySize()/(2048*75)));
	return 1;
}

long KAudioFOXLibDlg::onAddAudioFile(FXObject* sender, FXSelector key, void* data)
{
	FXint playtime = m_rule->GetAudioTimeValue();
	playtime += m_trackList->AddFile();
	m_rule->SetAudioTimeValue(playtime);
	return 1;
}

long KAudioFOXLibDlg::onAddFolder(FXObject* sender, FXSelector key, void* data)
{
	// Delegate to file tree control

	m_fileList->CreateFolder();
	return 1;
}

long KAudioFOXLibDlg::onDeleteDataItem(FXObject* sender, FXSelector key, void* data)
{
	m_fileList->DeleteItem();
	m_rule->SetDataTimeValue(FXint(m_fileList->GetRootDirectorySize()/(2048*75)));
	return 1;
}

long KAudioFOXLibDlg::onDeleteAudioItem(FXObject* sender, FXSelector key, void* data)
{
	FXint playtime = m_rule->GetAudioTimeValue();
	playtime += m_trackList->DeleteItem();
	m_rule->SetAudioTimeValue(playtime);
	return 1;
}

long KAudioFOXLibDlg::onResetList(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::ClearAll();
	handleError(res);

	m_trackList->ResetList();
	m_fileList->ResetList();
	m_rule->Reset();
	return 1;
}

long KAudioFOXLibDlg::onDeviceBoxChange(FXObject* sender, FXSelector key, void* data)
{
	FXint indx = m_cmbDevice->getCurrentItem();

	if (m_bMultideviceEnabled && indx == m_cmbDevice->getNumItems()-1)
	{	
		CALL_FXDIALOG(::MultiDeviceDialog());
	
		updateDeviceCombo();
	} else if (-1 < indx){
		FXString strItem = m_cmbDevice->getItemText(indx);

		KString strDevice = Fox2SDKString(strItem);

		int32 res = ::SetBurnDevice(strDevice);
		handleError(res);

	}

	return 1;
}

long KAudioFOXLibDlg::onEraseDisk(FXObject* sender, FXSelector key, void* data)
{	
	CALL_FXDIALOG_HANDLE_ERROR(::EraseDialog(_T("IsoSDK")));

	updateDeviceCombo();
	return 1;
}

int32 KAudioFOXLibDlg::updateOptions()
{
	// Load options from controls

	SOptions opt;

	int32 res = ::GetOptions(&opt);
	handleError(res);

	_tcscpy(opt.chVolumeLabel, _T("New"));
	opt.bEjectAfterBurn = m_bEjectAfterBurn;
	opt.bFinalize = m_bFinalize;
	opt.bJolietFileSystem = m_bJoliet;
	opt.bRockRidgeFileSystem = m_bRockRidge;
	opt.bVerifyAfterBurn = m_bVerify;


	// Set option to FoxBruner

	res = ::SetOptions(opt);
	handleError(res);
	

	FXint indx = m_cmbProjectType->getCurrentItem();
	m_iProjectType = indx == 0 ? BS_BURNER_AUDIO : BS_BURNER_MIXEDMODE;

	if (m_iProjectType != BS_BURNER_AUDIO)
	{
		SISOInfoEx isoInfo;
		res = ::GetISOInfoEx(&isoInfo);
		handleError(res);

		isoInfo.ISOAllowLowercaseNames = m_bAllowLowercaseNames;
		isoInfo.ISOAllowManyDirectories = m_bAllowManyDirectories;
		
		isoInfo.ISOLevel = BS_ISO_LEVEL_1 + m_lboxISOLevel->getCurrentItem();		

		res = ::SetISOInfoEx(isoInfo);	
		handleError(res);
	}

	res = ::SetWriteCDTextInUnicode((int8)m_bWriteCDTextInUnicode);
	handleError(res);

	return res;
}

long KAudioFOXLibDlg::onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data)
{
	// Synchronize options and menu controls

	updateOptions();

	// Get current device
	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	handleError(res);
	
	// Open image selection dialog if image device is selected

	if (0 == _tcsncmp(_T("#"), chBurnDevices[0], 1))  // CUE/BIN writer selected
	{
		const FXchar patterns[]= "CUE/BIN Files (*.bin)";

		FXFileDialog fileDlg(this, "Save As");
		fileDlg.setPatternList(patterns);
		fileDlg.setSelectMode(SELECTFILE_ANY);

		if (fileDlg.execute())
		{
			FX::FXSystem::setCurrentDirectory(fileDlg.getDirectory());
			FXString filename = FXString::compose(fileDlg.getFilename(), false);

			if ("" == FXPath::extension(filename))
				filename += ".bin";

			KString strTmpName = Fox2SDKString(filename);

			res = ::SetImageFilePath(strTmpName);
			handleError(res);

			// Also set special options for image writer

			SOptions opt;

			// Load current options first

			res = ::GetOptions(&opt);
			handleError(res);

			opt.nCopies = 0;	// No need for copies
			opt.bTestBurn = BS_FALSE;	// Test burn not supported
			opt.bVerifyAfterBurn = BS_FALSE;	// Test burn not supported

			// Then save options

			res = ::SetOptions(opt);
			handleError(res);
		}
		else
			return 1;
	}

	KSampleBurnDlg	burnDlg(this);
	burnDlg.execute();

	return 1;
}

long KAudioFOXLibDlg::onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data)
{
	updateOptions();
	
	CALL_FXDIALOG_HANDLE_ERROR(::BurnDialog());

	updateDeviceCombo();
	return 1;
}

void KAudioFOXLibDlg::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		int32 nLength = 2048;

		::GetText(errCode, chError, &nLength);

#ifdef _UNICODE
		KString strError = KStringFormat(_T("error: %ls"), chError);
#else
		KString strError = KStringFormat(_T("error: %hs"), chError);
#endif

		FXString fxstr = (const wchar_t*)strError;
		FXMessageBox::error(this, MBOX_OK, "IsoSDK", fxstr.text());
	}
}

void KAudioFOXLibDlg::updateDeviceCombo()
{
	m_cmbDevice->clearItems();
	m_bMultideviceEnabled = false;

	// Get devices list

	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 res = ::GetDevices(chListDevices, &nUsed, m_bBurningDevicesOnly ? BS_TRUE : BS_FALSE);
	handleError(res);

	// Get current device

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	handleError(res);

	// Add devices to combo box

	for (int i = 0; i < nUsed; i++)
	{
		FXString strItem;
		strItem = SDK2FoxString(chListDevices[i]);
		if (strItem.length() > 0) {
			FXint itemIndex = m_cmbDevice->appendItem(strItem);

			if (nBurnDevices > 0) {
				FXString strDeviceItem = chBurnDevices[0];
				if (strItem.left(2) == strDeviceItem.left(2))
				{
					m_cmbDevice->setCurrentItem(i);
				}
			}

		}
	}

	// Append multidevice item if more than one device in list

	if (nUsed > 1)
	{
		m_bMultideviceEnabled = true;
		m_cmbDevice->appendItem("Multiple devices");
	}

	// Select multidevice item if more than one device is active

	if (nBurnDevices > 1)
		m_cmbDevice->setCurrentItem(m_cmbDevice->getNumItems()-1);

	// Ensure all devices are visible

	m_cmbDevice->setNumVisible(m_cmbDevice->getNumItems());
}

long KAudioFOXLibDlg::onDiskText(FXObject* sender, FXSelector key, void* data)
{
	m_trackList->DiskCDText();
	return 1;
}

long KAudioFOXLibDlg::onTrackText(FXObject* sender, FXSelector key, void* data)
{
	m_trackList->TrackCDText();
	return 1;
}

long KAudioFOXLibDlg::onPlay(FXObject* sender, FXSelector key, void* data)
{
	m_trackList->Play();
	return 1;
}

long KAudioFOXLibDlg::onStopPlay(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::AudioFileStop();
	handleError(res);
	return 1;
}

long KAudioFOXLibDlg::onAudioFileSize(FXObject* sender, FXSelector key, void* data)
{

	double tSize = m_trackList->GetAudioFileSizeEx();
	if (tSize>0) {
		tSize = tSize / 1024 / 1024;
	}

	KString strError = KStringFormat(_T("Audio file size on disk: %.2f MB"), tSize);
	FXString fxstr = (const wchar_t*)strError;
	FXMessageBox::information(this, MBOX_OK, "Information", fxstr.text());

	return 1;
}

long KAudioFOXLibDlg::onDiskSize(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::Prepare();
	handleError(res);

	double fSize = 0.0;
	res = ::GetImageSize(&fSize);
	handleError(res);

	if (fSize>0) {
		fSize = fSize / 1024 / 1024;
	}

	KString strError = KStringFormat(_T("Disk size: %.2f MB"), fSize);
	FXString fxstr = (const wchar_t*)strError;
	FXMessageBox::information(this, MBOX_OK, "Information", fxstr.text());
	
	return 1;
}

long KAudioFOXLibDlg::onLoadPlugin1(FXObject* sender, FXSelector key, void* data)
{
#if defined LINUX
	int32 res = ::LoadBassPlugin(_T("libbass_ape.so"));
#endif

#if defined MAC
	int32 res = ::LoadBassPlugin(_T("libbass_ape.dylib"));
#endif

#if defined WIN32
#ifdef _UNICODE
	int32 res = ::LoadBassPlugin(_T("bass_ape.dll"));
#else
	int32 res = ::LoadBassPlugin(_T("bass_ape.dll"));
#endif
#endif
    
    handleError(res);
    return 1;
}

long KAudioFOXLibDlg::onRescanDevices(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::RescanDevices();
	handleError(res);

	updateDeviceCombo();
	return 1;
}

long KAudioFOXLibDlg::onProjectTypeChange(FXObject* sender, FXSelector key, void* data)
{
	FXint indx = m_cmbProjectType->getCurrentItem();
	m_iProjectType = indx == 0 ? BS_BURNER_AUDIO : BS_BURNER_MIXEDMODE;

	int32 res = ::CreateProject(m_iProjectType, BS_CONTINUE_NO_SESSION);
	handleError(res);

	if (m_iProjectType == BS_BURNER_AUDIO)
	{
		m_dataTab->disable();
		m_dataMenu->disable();
		m_chkJoliet->disable();
		m_chkRockRidge->disable();
		m_chkVerify->disable();
		m_chkFinalize->disable();
		m_chkAllowLowercaseNames->disable();
		m_chkAllowManyDirectories->disable();
		m_lboxISOLevel->disable();
		m_trackList->SetRootDirectory(PATHSEPSTRING);
		m_fileList->SetRootDirectory(PATHSEPSTRING);
	}
	else
	{
		m_dataTab->enable();
		m_dataMenu->enable();
		m_chkJoliet->enable();
		m_chkRockRidge->enable();
		m_chkVerify->enable();
		m_chkFinalize->enable();
		m_chkAllowLowercaseNames->enable();
		m_chkAllowManyDirectories->enable();
		m_lboxISOLevel->enable();
		m_trackList->SetRootDirectory(PATHSEPSTRING + KString("audio"));
		m_fileList->SetRootDirectory(SDK2FoxString((const TCHAR*)(PATHSEPSTRING + KString("data"))));
	}

	m_trackList->ResetList();
	m_fileList->ResetList();
	m_rule->Reset();

	updateOptions();

	return 1;
}

long KAudioFOXLibDlg::onVerifySelect(FXObject* sender, FXSelector key, void* data)
{
	m_bVerify = (data == 0 ? 0 : 1);

	// For verification flag call special function

	::SetVerify(m_bVerify != 0);
	return 1;
}

long KAudioFOXLibDlg::onRenameFile(FXObject* sender, FXSelector key, void* data)
{
	// Delegate to file list control

	m_fileList->RenameFile();
	return 1;
}

long KAudioFOXLibDlg::onErrorNotify(FXObject* sender, FXSelector key, void* data)
{
	handleError(int32(size_t(data)));
	return 1;
}

long KAudioFOXLibDlg::onCmdAspi(FXObject* sender, FXSelector key, void* data)
{
	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;

	// Set selected interface

	int32 res = ::SetASPI(which);
	handleError(res);
	updateDeviceCombo();
	return 1;
}

long KAudioFOXLibDlg::onUpdAspi(FXObject* sender, FXSelector key, void* data)
{
	// Update radio buttons in Interface menu

	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;
	int32 nInterface = BS_ASPI_INTERNAL;

	// Get current interface

	::GetASPI(&nInterface);

	if (nInterface == which)
		sender->handle(this,FXSEL(SEL_COMMAND,FXWindow::ID_CHECK),NULL);
	else
		sender->handle(this,FXSEL(SEL_COMMAND,FXWindow::ID_UNCHECK),NULL);

	return 1;
}

long KAudioFOXLibDlg::onDisableImagewriter(FXObject* sender, FXSelector key, void* data)
{
	// Disable or enable image writer

	::EnableImageDevice(data == 0 ? BS_TRUE : BS_FALSE);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KAudioFOXLibDlg::onBurningDevices(FXObject* sender, FXSelector key, void* data)
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = data != 0;
	updateDeviceCombo();
	return 1;
}

long KAudioFOXLibDlg::onAbout(FXObject* sender, FXSelector key, void* data)
{
	KAboutDlg	aboutDlg(this);
	aboutDlg.execute();
	return 1;
}

long KAudioFOXLibDlg::onWeb(FXObject* sender, FXSelector key, void* data)
{
	#if defined LINUX
		system("xdg-open http://www.isosdk.com/");
	#endif

	#if defined MAC
		FXString link ="open http://www.isosdk.com/";
		system(link.text());
	#endif

	#if defined WIN32
		ShellExecute(0, _T("open"), _T(WEBSITELINK), 0, 0, SW_SHOW);
	#endif
	return 1;
}
