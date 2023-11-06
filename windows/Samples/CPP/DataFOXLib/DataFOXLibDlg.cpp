#include "stdafx.h"
#include "DataFOXLibDlg.h"
#include "HeaderDlg.h"
#include "BootImageDlg.h"
#include "SessionDlg.h"
#include "PropertiesDlg.h"
#include <algorithm>
#include "../Common/SampleBurnDlg.h"
#include "../Common/AboutDlg.h"
#include "../Common/CommonFoxLib.h"

#define WEBSITELINK			"http://www.isosdk.com"


/////////////////////////////////////////////////////////////////////////////
//  message handlers

inline FXint pointerToInt(void* voidVal)
{
	return *(FXint*)(&voidVal);
}

FXDEFMAP(KDataFOXLibDlg) KDataFOXLibMap[]= {
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_ADDFILE, KDataFOXLibDlg::onAddFile),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_ADDFOLDER, KDataFOXLibDlg::onAddFolder),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_RENAMEFILE, KDataFOXLibDlg::onRenameFile),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_DELETEITEM, KDataFOXLibDlg::onDeleteItem),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_RESETLIST, KDataFOXLibDlg::onResetList),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_EDITPROPERTIES, KDataFOXLibDlg::onEditProperties),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_WRITELOG, KDataFOXLibDlg::onWriteLogFile),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_BURNDISK_DEVELOPED, KDataFOXLibDlg::onBurnDiskDeveloped),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_BURNDISK_FOXBURNER, KDataFOXLibDlg::onBurnDiskFoxBurner),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_ERASEDISK, KDataFOXLibDlg::onEraseDisk),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_VERIFY, KDataFOXLibDlg::onVerifySelect),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_EXTHEADER, KDataFOXLibDlg::onExtHeader),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_BOOTDISK, KDataFOXLibDlg::onBootDisk),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_SESSION, KDataFOXLibDlg::onSessionSelect),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_IMPORT_LAST_SESSION, KDataFOXLibDlg::onImportLastSession),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_IMPORT_NO_SESSION, KDataFOXLibDlg::onImportNoSession),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_MOUNTIMAGE, KDataFOXLibDlg::onMountImage),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_UNMOUNTIMAGE, KDataFOXLibDlg::onUnmountImage),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_BURNIMAGE, KDataFOXLibDlg::onBurnImage),
	FXMAPFUNCS(SEL_COMMAND,KDataFOXLibDlg::ID_ASPI_INTERNAL, KDataFOXLibDlg::ID_ASPI_FROGASPI, KDataFOXLibDlg::onCmdAspi),
	FXMAPFUNCS(SEL_UPDATE, KDataFOXLibDlg::ID_ASPI_INTERNAL, KDataFOXLibDlg::ID_ASPI_FROGASPI, KDataFOXLibDlg::onUpdAspi),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_RESCANDEVICES, KDataFOXLibDlg::onRescanDevices),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_BURNDEVICES, KDataFOXLibDlg::onBurningDevices),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_DISABLEIMAGE, KDataFOXLibDlg::onDisableImagewriter),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_IGNOREFILECHECK, KDataFOXLibDlg::onIgnoreFileCheck),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_ABOUT, KDataFOXLibDlg::onAbout),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_WEB, KDataFOXLibDlg::onWeb),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_DEVICEBOX, KDataFOXLibDlg::onDeviceBox),
	FXMAPFUNC(SEL_COMMAND, KDataFOXLibDlg::ID_PROJECTTYPE, KDataFOXLibDlg::onProjectType),
	FXMAPFUNC(KDataFOXLibDlg::SEL_ERRORNOTIFY, 0, KDataFOXLibDlg::onErrorNotify),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KDataFOXLibDlg::onCmdCancel),
	FXMAPFUNC(SEL_CLOSE, 0, KDataFOXLibDlg::onCmdCancel)
};

FXIMPLEMENT(KDataFOXLibDlg, FXDialogBox, KDataFOXLibMap, ARRAYNUMBER(KDataFOXLibMap))

KDataFOXLibDlg::KDataFOXLibDlg(FXApp *app, const FXString &title)
	: FXDialogBox(app, title, DECOR_ALL, 0, 0, 600, 500, 0, 0, 0, 0, 0, 0)
	, m_iSession(BS_CONTINUE_LAST_SESSION)
	, m_iProjectType(BS_BURNER_DATA)
	, m_bBurningDevicesOnly(true)
{

	
	m_bEjectAfterBurn = 1;
	m_bJoliet = 1;
	m_bRockRidge = 1;
	m_bFinalize = 1;
	m_bAllowLowercaseNames = 1;
	m_bAllowManyDirectories = 1;
	m_bAllowLongISO9660Names = 1;
	m_bAllowLongJolietNames = 1;


	// Connect targets and variables

	m_tgtEjectAfterBurn.connect(m_bEjectAfterBurn);
	m_tgtJoliet.connect(m_bJoliet);
	m_tgtRockRidge.connect(m_bRockRidge);
	m_tgtFinalize.connect(m_bFinalize);
	m_tgtAllowLowercaseNames.connect(m_bAllowLowercaseNames);
	m_tgtAllowManyDirectories.connect(m_bAllowManyDirectories);
	m_tgtAllowLongISO9660Names.connect(m_bAllowLongISO9660Names);
	m_tgtAllowLongJolietNames.connect(m_bAllowLongJolietNames);

	// Load icons for menu

	FXIcon *fileAddIcon = new FXICOIcon(getApp(), addfile);
	FXIcon *folderAddIcon = new FXICOIcon(getApp(), addfolder);
	FXIcon *deleteIcon = new FXICOIcon(getApp(), selection);
	FXIcon *resetIcon = new FXICOIcon(getApp(), reset);
	FXIcon *eraseIcon = new FXICOIcon(getApp(), cd_erase);
	FXIcon *burnIcon = new FXICOIcon(getApp(), burn_iso);
	FXIcon *cancelIcon = new FXICOIcon(getApp(), cancel);
	FXIcon *refreshIcon = new FXICOIcon(getApp(), refresh2);
	FXIcon *mountIcon = new FXICOIcon(getApp(), cd_load);
	FXIcon *unmountIcon = new FXICOIcon(getApp(), cd_eject);
	FXIcon *isosdkIconSmall = new FXICOIcon(getApp(), isosdksmall);
	FXIcon *isosdkIconBig = new FXICOIcon(getApp(), isosdkbig);

	///////////////////////////////////////////////////////////////////
	// Create menu bar

	FXMenuBar *menubar = new FXMenuBar(this, LAYOUT_FILL_X);

	FXMenuPane *filemenu = new FXMenuPane(this);
		new FXMenuCommand(filemenu,"&Add file/folder...", fileAddIcon, this, ID_ADDFILE);
		new FXMenuCommand(filemenu,"&Create folder...", folderAddIcon, this, ID_ADDFOLDER);
		new FXMenuCommand(filemenu,"Re&name file...", NULL, this, ID_RENAMEFILE);
		new FXMenuCommand(filemenu,"&Delete selected", deleteIcon, this, ID_DELETEITEM);
		new FXMenuCommand(filemenu,"&Reset", resetIcon, this, ID_RESETLIST);
		new FXMenuCommand(filemenu,"&Properties...", NULL, this, ID_EDITPROPERTIES);
		new FXMenuCommand(filemenu, "&Disable file exists check", NULL, this, ID_IGNOREFILECHECK);
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"Write log", NULL, this, ID_WRITELOG);
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"E&xit", cancelIcon, this, FXDialogBox::ID_CANCEL);
	new FXMenuTitle(menubar, "&File", NULL, filemenu);

	FXMenuPane *burnmenu = new FXMenuPane(this);
		new FXMenuCommand(burnmenu,"&Burn with custom dialog...", burnIcon, this, ID_BURNDISK_DEVELOPED);
		new FXMenuCommand(burnmenu,"Burn with &IsoSDK embedded dialog...", burnIcon, this, ID_BURNDISK_FOXBURNER);
		new FXMenuCommand(burnmenu,"&Erase disk...", eraseIcon, this, ID_ERASEDISK);
		new FXHorizontalSeparator(burnmenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		FXMenuPane *optionsmenu = new FXMenuPane(this);
			new FXMenuCheck(optionsmenu,"&Eject disk", &m_tgtEjectAfterBurn, FXDataTarget::ID_VALUE);
			m_chkVerify = new FXMenuCheck(optionsmenu,"&Verify after burn", this, ID_VERIFY);
			m_chkJoliet = new FXMenuCheck(optionsmenu,"&Joliet file system", &m_tgtJoliet, FXDataTarget::ID_VALUE);
			m_chkRockRidge = new FXMenuCheck(optionsmenu,"&Rock Ridge file system", &m_tgtRockRidge, FXDataTarget::ID_VALUE);
			m_chkFinalize = new FXMenuCheck(optionsmenu,"&Finalize", &m_tgtFinalize, FXDataTarget::ID_VALUE);
			new FXSeparator(optionsmenu);
			m_chkAllowLowercaseNames = new FXMenuCheck(optionsmenu,"Allow &lowercase names", &m_tgtAllowLowercaseNames, FXDataTarget::ID_VALUE);
			m_chkAllowManyDirectories = new FXMenuCheck(optionsmenu,"Allow &many directories", &m_tgtAllowManyDirectories, FXDataTarget::ID_VALUE);
			m_chkAllowLongISO9660Names = new FXMenuCheck(optionsmenu,"Allow long ISO 9660 names", &m_tgtAllowLongISO9660Names, FXDataTarget::ID_VALUE);
			m_chkAllowLongJolietNames = new FXMenuCheck(optionsmenu,"Allow long Joliet names", &m_tgtAllowLongJolietNames, FXDataTarget::ID_VALUE);
			FXHorizontalFrame* ISOLevelFrame = new FXHorizontalFrame(optionsmenu, LAYOUT_FILL_X);
				new FXLabel(ISOLevelFrame, _T("ISO level:"));
				m_lboxISOLevel = new FXListBox(ISOLevelFrame);
				m_lboxISOLevel->appendItem(_T("Level 1"));
				m_lboxISOLevel->appendItem(_T("Level 2"));
				m_lboxISOLevel->appendItem(_T("Level 3"));
				m_lboxISOLevel->appendItem(_T("Romeo"));
				m_lboxISOLevel->setNumVisible(4);
		new FXMenuCascade(burnmenu, "&Options", NULL, optionsmenu);
	new FXMenuTitle(menubar, "&Burn", NULL, burnmenu);

	FXMenuPane* additionalmenu = new FXMenuPane(this);
		new FXMenuCommand(additionalmenu,"&Extended ISO header...", NULL, this, ID_EXTHEADER);
		new FXMenuCommand(additionalmenu,"&BootDisk settings...", NULL, this, ID_BOOTDISK);
		new FXMenuCommand(additionalmenu,"&Import from session...", NULL, this, ID_SESSION);
		new FXMenuCommand(additionalmenu,"Import &last session", NULL, this, ID_IMPORT_LAST_SESSION);
		new FXMenuCommand(additionalmenu,"Import &no session", NULL, this, ID_IMPORT_NO_SESSION);
	new FXMenuTitle(menubar, "&Additional", NULL, additionalmenu);

	FXMenuPane* imagemenu = new FXMenuPane(this);
		new FXMenuCommand(imagemenu, "&Mount image...", mountIcon, this, ID_MOUNTIMAGE);
		new FXMenuCommand(imagemenu, "&Unmount image", unmountIcon, this, ID_UNMOUNTIMAGE);
		new FXHorizontalSeparator(imagemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(imagemenu, "&Burn disk image", burnIcon, this, ID_BURNIMAGE);
	new FXMenuTitle(menubar, "&Images", NULL, imagemenu);

	FXMenuPane* aspimenu = new FXMenuPane(this);
		FXMenuPane* interfacemenu = new FXMenuPane(this);
			new FXMenuRadio(interfacemenu, "&Internal", this, ID_ASPI_INTERNAL);
			new FXMenuRadio(interfacemenu, "&WnAspi", this, ID_ASPI_WNASPI);
			new FXMenuRadio(interfacemenu, "&FrogAspi", this, ID_ASPI_FROGASPI);
		new FXMenuCascade(aspimenu, "&Interface", NULL, interfacemenu);
		new FXMenuCommand(aspimenu,"&Rescan devices", refreshIcon, this, ID_RESCANDEVICES);
		m_burnDevicesOnly = new FXMenuCheck(aspimenu,"&Burn devices only", this, ID_BURNDEVICES);
		new FXMenuCheck(aspimenu,"Disable &imagewriter", this, ID_DISABLEIMAGE);
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

	FXHorizontalFrame* btnframe = new FXHorizontalFrame(this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X);
	m_chPathRule = new FXCheckButton(btnframe, "Do not save the path of the selected file / folder", this, ID_PATHRULE);
	m_chPathRule->setCheck();



	// Capacity rule
	m_rule = new KCDCapacityRule(this, CAPACITYRULE_CD|FRAME_THICK|LAYOUT_BOTTOM|LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|LAYOUT_FIX_HEIGHT, 0, 0, 0, 30);

	


	setMiniIcon(isosdkIconSmall);
	setIcon(isosdkIconBig);


	m_strStartupDir = FXSystem::getCurrentDirectory();
	
}

//--------------------------------------------------------------
// First Load and build Class then load SDK settings to the app
// to make sure that the Fox-Toolkit is initialized the right way.
//--------------------------------------------------------------
void KDataFOXLibDlg::loadOwner()
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

	//----------------------------------------------------------
	//We need to set a project. So we set default project first
	//----------------------------------------------------------
	res = ::CreateProject(m_iProjectType, BS_CONTINUE_NO_SESSION);
	handleError(res);

	//--------------------------------------------------
	//Set the Options. Remember, not all Options are
	//available on all projects. Read Help
	//--------------------------------------------------

	SOptions opt;
	res = GetOptions(&opt);
	handleError(res);

	opt.bTestBurn = BS_FALSE;
	opt.bPerformOPC = BS_FALSE;
	opt.bJolietFileSystem = BS_TRUE;
	opt.bRockRidgeFileSystem = BS_FALSE;
	opt.bEjectAfterBurn = BS_TRUE;
	opt.nCacheSize = 4 * 1024 * 1024;
	opt.bFinalize = BS_FALSE;

	m_bEjectAfterBurn = opt.bEjectAfterBurn;
	m_bJoliet = opt.bJolietFileSystem;
	m_bRockRidge = opt.bRockRidgeFileSystem;
	m_bFinalize = opt.bFinalize;
	m_bVerify = opt.bVerifyAfterBurn;

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	res = ::SetOptions(opt);
	handleError(res);

	SISOInfoEx isoInfo;
	res = ::GetISOInfoEx(&isoInfo);
	handleError(res);

	m_bAllowLowercaseNames = isoInfo.ISOAllowLowercaseNames;
	m_bAllowManyDirectories = isoInfo.ISOAllowManyDirectories;
	m_bAllowLongISO9660Names = isoInfo.ISOAllowLongISO9660Names;
	m_bAllowLongJolietNames = isoInfo.ISOAllowLongJolietNames;

	m_cmbProjectType->appendItem("ISO 9660");
	m_cmbProjectType->appendItem("UDF");
	m_cmbProjectType->appendItem("ISO 9660 / UDF Bridge");
	m_cmbProjectType->appendItem("Video DVD");
	m_cmbProjectType->appendItem("BluRay");
	m_cmbProjectType->setNumVisible(m_cmbProjectType->getNumItems());

	if (m_bVerify)
		m_chkVerify->setCheck();
	if (m_bBurningDevicesOnly)
		m_burnDevicesOnly->setCheck();

	// File tree pane
	FXHorizontalFrame* fileFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X | LAYOUT_FILL_Y);
	m_fileList = new KFileList(fileFrame, this, ID_FILELIST,
		LAYOUT_FILL_X | LAYOUT_FILL_Y | FRAME_THICK | ICONLIST_DETAILED | ICONLIST_EXTENDEDSELECT);

	// Update devices list
	updateDeviceCombo();
}

KDataFOXLibDlg::KDataFOXLibDlg()
{

}

KDataFOXLibDlg::~KDataFOXLibDlg()
{
	::DeInitialize();
}

void KDataFOXLibDlg::updateDeviceCombo()
{
	m_cmbDevice->clearItems();
	m_bMultideviceEnabled = false;

	// Get devices list

	TCHAR chListDevices[26][50];	
	int32 nUsed = 0;
	int32 res = ::GetDevices(chListDevices, &nUsed, m_bBurningDevicesOnly ? BS_TRUE : BS_FALSE);
	handleError(res);

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	handleError(res);


	// Add devices to combo box
	//nUsed ist das ganze Array mit allen Nuller.
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

long KDataFOXLibDlg::onAddFile(FXObject* sender, FXSelector key, void* data)
{
	// Delegate to file tree control
	int32 savePath = BS_DONT_SAVE_PATH;
	if (m_chPathRule->getCheck() == 0) 
	{
		savePath = BS_WHOLE_PATH;
	}

	m_fileList->AddFile(savePath);

	// Update size rule

	//m_rule->SetSizeValue(m_fileList->GetRootDirectorySize());

	return 1;
}

long KDataFOXLibDlg::onWriteLogFile(FXObject* sender, FXSelector key, void* data)

{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(KString(m_strStartupDir.text()) + PATHSEPSTRING + "FoxSampleDataC.log");
	return 1;

}

long KDataFOXLibDlg::onAddFolder(FXObject* sender, FXSelector key, void* data)
{
	// Delegate to file tree control

	m_fileList->CreateFolder();
	return 1;
}

long KDataFOXLibDlg::onDeleteItem(FXObject* sender, FXSelector key, void* data)
{
	// Delegate to file tree control

	m_fileList->DeleteItem();

	// Update size rule

	m_rule->SetSizeValue(m_fileList->GetRootDirectorySize());

	return 1;
}

long KDataFOXLibDlg::onResetList(FXObject* sender, FXSelector key, void* data)
{
	// Clear project

	::ClearAll();

	// Update file tree and size rule

	m_fileList->ResetList();
	m_rule->SetSizeValue(m_fileList->GetRootDirectorySize());

	return 1;
}

long KDataFOXLibDlg::onEditProperties(FXObject* sender, FXSelector key, void* data)
{
	FXint currentIndex = m_fileList->getCurrentItem();
	if (currentIndex >= 0)
	{
		SFileEntry *fileEntry = (SFileEntry *)m_fileList->getItem(currentIndex)->getData();
		if (fileEntry)
		{
			KPropertiesDlg dlg(this, fileEntry);
			if (dlg.execute())
				m_fileList->RefreshList();
		}
	}
	return 1;
}

long KDataFOXLibDlg::onProjectType(FXObject* sender, FXSelector key, void* data)
{
	// Map index to project type

	FXint indx = m_cmbProjectType->getCurrentItem();
	int32 type = BS_BURNER_DATA;
	switch (indx)
	{
	case 0:
		type = BS_BURNER_DATA;
		break;
	case 1:
		type = BS_BURNER_UDFDVD;
		break;
	case 2:
		type = BS_BURNER_ISOUDF;
		break;
	case 3:
		type = BS_BURNER_VIDEODVD;
		break;
	case 4:
		type = BS_BURNER_BLURAY;
		break;
	}

	// Save selected project type

	m_iProjectType = type;

	// Create selected project

	int32 res = ::CreateProject(type, m_iSession);
	handleError(res);

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
			default: FXASSERT(0); break;
		}
		m_cmbProjectType->setCurrentItem(indx);
	}
	else
	{
		// Disable some menu items specific to project type

		if (BS_BURNER_VIDEODVD == m_iProjectType)
			m_chkFinalize->disable();
		else
			m_chkFinalize->enable();

		if (BS_BURNER_DATA == m_iProjectType || BS_BURNER_ISOUDF == m_iProjectType)
		{
			m_chkJoliet->enable();
			m_chkRockRidge->enable();
		}
		else
		{
			m_chkJoliet->disable();
			m_chkRockRidge->disable();
		}
	}

	// Update file list and size rule
	m_fileList->ResetList();
	m_rule->SetSizeValue(m_fileList->GetRootDirectorySize());
	return 1;
}

long KDataFOXLibDlg::onDeviceBox(FXObject* sender, FXSelector key, void* data)
{
	FXint indx = m_cmbDevice->getCurrentItem();
	

	if (indx == m_cmbDevice->getNumItems()-1 && m_bMultideviceEnabled)
	{
		// Open multidevice dialog if multidevice is selected
		
		CALL_FXDIALOG(::MultiDeviceDialog());

		// Multidevice dialog set current device, so we
		// should update device combo

		updateDeviceCombo();
	}
	else if (-1 < indx)
	{

		FXString strItem = m_cmbDevice->getItemText(indx);
		KString strDevice = Fox2SDKString(strItem);

		int32 res = ::SetBurnDevice(strDevice);
		handleError(res);


	}

	m_fileList->RefreshList();
	return 1;
}

long KDataFOXLibDlg::onEraseDisk(FXObject* sender, FXSelector key, void* data)
{
	// Call erase dialog
	
	CALL_FXDIALOG_HANDLE_ERROR(::EraseDialog(_T("IsoSDK")));

	// Update device list

	updateDeviceCombo();
	return 1;
}

int32 KDataFOXLibDlg::updateOptions()
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

	if(		(m_iProjectType == BS_BURNER_ISOUDF)
		||	(m_iProjectType == BS_BURNER_MIXEDMODE)
		||	(m_iProjectType == BS_BURNER_DATA)
	   )
	{
		SISOInfoEx isoInfo;
		res = ::GetISOInfoEx(&isoInfo);
		handleError(res);

		isoInfo.ISOAllowLowercaseNames = m_bAllowLowercaseNames;
		isoInfo.ISOAllowManyDirectories = m_bAllowManyDirectories;
		isoInfo.ISOAllowLongISO9660Names = m_bAllowLongISO9660Names;
		isoInfo.ISOAllowLongJolietNames = m_bAllowLongJolietNames;
		isoInfo.ISOLevel = BS_ISO_LEVEL_1 + m_lboxISOLevel->getCurrentItem();

		res = ::SetISOInfoEx(isoInfo);
		handleError(res);
	}

	return res;
}

long KDataFOXLibDlg::onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data)
{
	// Synchronize options and menu controls

	updateOptions();

	// Call IsoSDK burn dialog
	//int32 res = ::BurnDialog();
	//handleError(res);

	CALL_FXDIALOG_HANDLE_ERROR(::BurnDialog());

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KDataFOXLibDlg::onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data)
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
		if (!handle(0, FXSEL(SEL_COMMAND, KDataFOXLibDlg::ID_MOUNTIMAGE), 0))
			return 1;


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

	KSampleBurnDlg	burnDlg(this);
	burnDlg.execute();

	if (0 == _tcsncmp(_T("#"), chBurnDevices[0], 1))  // Iso writer selected
	{
		handle(0, FXSEL(SEL_COMMAND, KDataFOXLibDlg::ID_UNMOUNTIMAGE),0);
	}


	return 1;
}

long KDataFOXLibDlg::onBurnImage(FXObject* sender, FXSelector key, void* data)
{
	// Get image path

	FXFileDialog fileDlg(this, "Select image file");
	fileDlg.setPatternList("Iso Files (*.iso)\nCue Sheets (*.cue)");
	fileDlg.setSelectMode(SELECTFILE_EXISTING);

	if (!fileDlg.execute())
		return 1;

    FX::FXSystem::setCurrentDirectory(fileDlg.getDirectory());

	FXString strFileName = fileDlg.getFilename().lower();
	KString strTmpSourcePath = Fox2SDKString(strFileName);

	updateOptions();

	int32 res = 0;

	if (strTmpSourcePath.Right(3) == _T("cue"))
	{
		res = ::CreateProject(BS_BURNER_CUE);
		handleError(res);

		SFileToAdd fileToAdd;
		fileToAdd.lpszSourceFilePath = strTmpSourcePath;
		res = ::AddFile(fileToAdd);
		handleError(res);

		strTmpSourcePath.Empty();
	}

	// Burn image with IsoSDK dialog
	res = ::BurnDialog(BS_FALSE, BS_FALSE, BS_TRUE, NULL, strTmpSourcePath);
	handleError(res);

	onProjectType(this, ID_PROJECTTYPE, 0);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KDataFOXLibDlg::onExtHeader(FXObject* sender, FXSelector key, void* data)
{
	KHeaderDlg dlg(this, "Extended ISO header infos");
	dlg.execute();
	return 1;
}

long KDataFOXLibDlg::onBootDisk(FXObject* sender, FXSelector key, void* data)
{
	KBootImgDlg dlg(this, "Boot image options");
	dlg.execute();
	return 1;
}


long KDataFOXLibDlg::onSessionSelect(FXObject* sender, FXSelector key, void* data)
{
	KSessionDlg dlg(this, "Select session");
	if (dlg.execute())
	{
		if(0 < dlg.m_nSession)
		{
			FXint session = dlg.m_nSession;

			// For importing session we should recreate project

			int32 res = ::CreateProject(m_iProjectType, session);
			handleError(res);

			if (BS_SDK_ERROR_NO == res)
			{
				m_iSession = session;
			}

			// Update files and devices lists

			m_fileList->RefreshList();
			m_rule->SetSizeValue(m_fileList->GetRootDirectorySize());
		}
	}

	return 1;
}

void KDataFOXLibDlg::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		int32 nLength = 2048;

		// Get error description

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

long KDataFOXLibDlg::onVerifySelect(FXObject* sender, FXSelector key, void* data)
{
	m_bVerify = (data == 0 ? 0 : 1);

	// For verification flag call special function

	::SetVerify(m_bVerify != 0);
	return 1;
}

long KDataFOXLibDlg::onRenameFile(FXObject* sender, FXSelector key, void* data)
{
	// Delegate to file list control

	m_fileList->RenameFile();
	return 1;
}

long KDataFOXLibDlg::onErrorNotify(FXObject* sender, FXSelector key, void* data)
{
	handleError(pointerToInt(data));
	return 1;
}

long KDataFOXLibDlg::onRescanDevices(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::RescanDevices();
	handleError(res);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KDataFOXLibDlg::onMountImage(FXObject* sender, FXSelector key, void* data)
{
	const FXchar patterns[]= "ISO Files (*.iso)";

	FXFileDialog fileDlg(this, "Select image file");
	fileDlg.setPatternList(patterns);
	fileDlg.setSelectMode(SELECTFILE_ANY);

	if (fileDlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(fileDlg.getDirectory());
		FXString filename = FXString::compose(fileDlg.getFilename(), false);

		if ("" == FXPath::extension(filename))
			filename += ".iso";

		KString strTmpName = Fox2SDKString(filename);

		int32 res = ::SetImageFilePath(strTmpName);
		handleError(res);
		return (res == BS_SDK_ERROR_NO) ? 1 : 0;
	}
	else
	{
		return 0;
	}
}

long KDataFOXLibDlg::onUnmountImage(FXObject* sender, FXSelector key, void* data)
{
	::SetImageFilePath(NULL);
	return 1;
}

long KDataFOXLibDlg::onCmdAspi(FXObject* sender, FXSelector key, void* data)
{
	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;

	// Set selected interface

	int32 res = ::SetASPI(which);
	handleError(res);
	updateDeviceCombo();
	return 1;
}

long KDataFOXLibDlg::onUpdAspi(FXObject* sender, FXSelector key, void* data)
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
long KDataFOXLibDlg::onIgnoreFileCheck(FXObject* sender, FXSelector key, void* data)
{
	::SetIgnoreFileExist(BS_TRUE);
	return 1;
}


long KDataFOXLibDlg::onDisableImagewriter(FXObject* sender, FXSelector key, void* data)
{
	// Disable or enable image writer

	::EnableImageDevice(data == 0 ? BS_TRUE : BS_FALSE);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KDataFOXLibDlg::onBurningDevices(FXObject* sender, FXSelector key, void* data)
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = data != 0;
	updateDeviceCombo();
	return 1;
}

long KDataFOXLibDlg::onAbout(FXObject* sender, FXSelector key, void* data)
{
	KAboutDlg	aboutDlg(this);
	aboutDlg.execute();
	return 1;
}

long KDataFOXLibDlg::onWeb(FXObject* sender, FXSelector key, void* data)
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

long KDataFOXLibDlg::onImportLastSession(FXObject* sender, FXSelector key, void* data)
{
	SMediumInfo infoMedium;
	int32 res = GetMediumInformation(BS_CURRENT_DEVICE, &infoMedium);
	handleError(res);

	int32 session = infoMedium.nLastSession;

	res = ::CreateProject(m_iProjectType, session);
	handleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		m_iSession = session;
	}

	// Update files and devices lists

	m_fileList->RefreshList();
	m_rule->SetSizeValue(m_fileList->GetRootDirectorySize());


	return 1;
};

long KDataFOXLibDlg::onImportNoSession(FXObject* sender, FXSelector key, void* data)
{
	// Don't import sessions
	m_iSession=BS_CONTINUE_NO_SESSION;
	
	// Refresh GUI and project.
    return onProjectType(0,0,0);
}
