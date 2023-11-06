
#include "stdafx.h"
#include "UtilitiesFOXLibDlg.h"
#include "RegionChangeDlg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "../Common/AboutDlg.h"
#include "../Common/Rule.h"
#include "../Common/CommonFoxLib.h"

#define WEBSITELINK			"http://www.isosdk.com"


FXDEFMAP(KUtilitiesFOXLibDlg) KUtilitiesFOXLibMap[]= {
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_WRITELOG, KUtilitiesFOXLibDlg::onWriteLogFile),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_ISREADY, KUtilitiesFOXLibDlg::onIsReady),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_EJECTTRAY, KUtilitiesFOXLibDlg::onEjectTray),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_CLOSETRAY, KUtilitiesFOXLibDlg::onCloseTray),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_LOCKDEVICE, KUtilitiesFOXLibDlg::onLockDevice),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_UNLOCKDEVICE, KUtilitiesFOXLibDlg::onUnlockDevice),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_GETDRIVEINFO, KUtilitiesFOXLibDlg::onGetDriveInfo),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_GETDRIVEINFOEX, KUtilitiesFOXLibDlg::onGetDriveInfoEx),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_GETCAPABILITIES, KUtilitiesFOXLibDlg::onGetCapabilities),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_SETREGIONCODE, KUtilitiesFOXLibDlg::onSetRegionCode),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_GETDISKINFO, KUtilitiesFOXLibDlg::onGetDiskInfo),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_ERASEDISK, KUtilitiesFOXLibDlg::onEraseDisk),
	FXMAPFUNCS(SEL_COMMAND,KUtilitiesFOXLibDlg::ID_ASPI_INTERNAL, KUtilitiesFOXLibDlg::ID_ASPI_FROGASPI, KUtilitiesFOXLibDlg::onCmdAspi),
	FXMAPFUNCS(SEL_UPDATE, KUtilitiesFOXLibDlg::ID_ASPI_INTERNAL, KUtilitiesFOXLibDlg::ID_ASPI_FROGASPI, KUtilitiesFOXLibDlg::onUpdAspi),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_RESCANDEVICES, KUtilitiesFOXLibDlg::onRescanDevices),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_BURNDEVICES, KUtilitiesFOXLibDlg::onBurningDevices),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_DISABLEIMAGE, KUtilitiesFOXLibDlg::onDisableImagewriter),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_ABOUT, KUtilitiesFOXLibDlg::onAbout),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_WEB, KUtilitiesFOXLibDlg::onWeb),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_DEVICEBOX, KUtilitiesFOXLibDlg::onDeviceBoxChange),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_CLOSESESSION, KUtilitiesFOXLibDlg::onCloseSession),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_ADDLOGLINE, KUtilitiesFOXLibDlg::onAddLogLine),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_ERRORNOTIFY, KUtilitiesFOXLibDlg::onErrorNotify),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, FXDialogBox::onCmdCancel),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_CHECKFORMAT_BTN, KUtilitiesFOXLibDlg::onCheckFormat),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_ABORT_IMG_BTN,  KUtilitiesFOXLibDlg::onAbortImage),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_BROWSEDEST_BTN, KUtilitiesFOXLibDlg::onBtnImageBrowse),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_ABORT_DSC_BTN,  KUtilitiesFOXLibDlg::onAbortDisc),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_SOURCE_DEVICEBOX, KUtilitiesFOXLibDlg::onSourceDeviceBoxChange),	

	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_EXECUTEIMAGE_BTN, KUtilitiesFOXLibDlg::onExecuteImageCreate),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_DISCCOPY_BTN, KUtilitiesFOXLibDlg::onExecuteDiscCopy),

	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSECTOR_IMG, KUtilitiesFOXLibDlg::onSetVerifySectorImg),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSECTOR_CPY, KUtilitiesFOXLibDlg::onSetVerifySectorCpy),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSTART_IMG, KUtilitiesFOXLibDlg::onSetVerifyStartImg),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSTART_CPY, KUtilitiesFOXLibDlg::onSetVerifyStartCpy),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYDONE_IMG, KUtilitiesFOXLibDlg::onSetVerifyDoneImg),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYDONE_CPY, KUtilitiesFOXLibDlg::onSetVerifyDoneCpy),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_SETPROGRESS_IMG, KUtilitiesFOXLibDlg::onSetProgressImg),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_SETPROGRESS_DSC, KUtilitiesFOXLibDlg::onSetProgressDsc),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_JOBDONE_IMG, KUtilitiesFOXLibDlg::onJobDoneImg),	
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_JOBDONE_DSC, KUtilitiesFOXLibDlg::onJobDoneDsc),
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_BURNDONE_IMG, KUtilitiesFOXLibDlg::onBurnDoneImg),	
	FXMAPFUNC(SEL_CHORE, KUtilitiesFOXLibDlg::ID_BURNDONE_DSC, KUtilitiesFOXLibDlg::onBurnDoneDsc),

	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_MOUNTIMAGE, KUtilitiesFOXLibDlg::onMountImage),
	FXMAPFUNC(SEL_COMMAND, KUtilitiesFOXLibDlg::ID_UNMOUNTIMAGE, KUtilitiesFOXLibDlg::onUnmountImage),

	FXMAPFUNC(SEL_CLOSE, 0, FXDialogBox::onCmdCancel)
};

FXIMPLEMENT(KUtilitiesFOXLibDlg, FXDialogBox, KUtilitiesFOXLibMap, ARRAYNUMBER(KUtilitiesFOXLibMap))

KUtilitiesFOXLibDlg::KUtilitiesFOXLibDlg()
:guisignal(NULL)
{
}

KUtilitiesFOXLibDlg::KUtilitiesFOXLibDlg(FXApp *app, const FXString &title)
	: FXDialogBox(app, title, DECOR_ALL, 0, 0, 640, 640, 0, 0, 0, 0, 0, 0)
	, guisignal(app)
	, m_bBurningDevicesOnly(true)
{


	// Load icons for menu
	FXIcon* cancelIcon = new FXICOIcon(getApp(), cancel);
	FXIcon* ejectIcon = new FXICOIcon(getApp(), cd_eject);
	FXIcon* loadIcon = new FXICOIcon(getApp(), cd_load);
	FXIcon* cdinfoIcon = new FXICOIcon(getApp(), cd_info);
	FXIcon* driveinfoIcon = new FXICOIcon(getApp(), drive_info);
	FXIcon* drivescanIcon = new FXICOIcon(getApp(), drive_scan);
	FXIcon* refreshIcon = new FXICOIcon(getApp(), refresh2);
	FXIcon* eraseIcon = new FXICOIcon(getApp(), cd_erase);
	FXIcon *isosdkIconSmall = new FXICOIcon(getApp(), isosdksmall);
	FXIcon *isosdkIconBig = new FXICOIcon(getApp(), isosdkbig);

	///////////////////////////////////////////////////////////////////
	// Create menu bar

	FXMenuBar *menubar = new FXMenuBar(this, LAYOUT_FILL_X);

	FXMenuPane *filemenu = new FXMenuPane(this);
		new FXMenuCommand(filemenu,"Write log", NULL, this, ID_WRITELOG);
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"E&xit", cancelIcon, this, FXDialogBox::ID_CANCEL);
	new FXMenuTitle(menubar, "&File", NULL, filemenu);

	FXMenuPane *devicemenu = new FXMenuPane(this);
		new FXMenuCommand(devicemenu, "Is device &ready", NULL, this, ID_ISREADY);
		new FXMenuCommand(devicemenu, "&Eject tray", ejectIcon, this, ID_EJECTTRAY);
		new FXMenuCommand(devicemenu, "C&lose tray", loadIcon, this, ID_CLOSETRAY);
		new FXMenuCommand(devicemenu, "Lock device", NULL, this, ID_LOCKDEVICE);
		new FXMenuCommand(devicemenu, "Unlock device", NULL, this, ID_UNLOCKDEVICE);
		new FXHorizontalSeparator(devicemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(devicemenu, "Get drive &info", driveinfoIcon, this, ID_GETDRIVEINFO);
		new FXMenuCommand(devicemenu, "Get drive info e&xtended", driveinfoIcon, this, ID_GETDRIVEINFOEX);
		new FXMenuCommand(devicemenu, "Get &capabilities", drivescanIcon, this, ID_GETCAPABILITIES);
		new FXMenuCommand(devicemenu, "Set &region code", NULL, this, ID_SETREGIONCODE);
	new FXMenuTitle(menubar, "&Device", NULL, devicemenu);

	FXMenuPane* imagemenu = new FXMenuPane(this);
		new FXMenuCommand(imagemenu, "&Mount image...", NULL, this, ID_MOUNTIMAGE);
		new FXMenuCommand(imagemenu, "&Unmount image", NULL, this, ID_UNMOUNTIMAGE);		
	new FXMenuTitle(menubar, "&Images", NULL, imagemenu);

	FXMenuPane* mediummenu = new FXMenuPane(this);
		new FXMenuCommand(mediummenu, "Get disk &info", cdinfoIcon, this, ID_GETDISKINFO);
		new FXMenuCommand(mediummenu, "&Erase", eraseIcon, this, ID_ERASEDISK);
	new FXMenuTitle(menubar, "&Medium", NULL, mediummenu);

	FXMenuPane* aspimenu = new FXMenuPane(this);
		FXMenuPane* interfacemenu = new FXMenuPane(this);
			new FXMenuRadio(interfacemenu, "&Internal", this, ID_ASPI_INTERNAL);
			new FXMenuRadio(interfacemenu, "&WnAspi", this, ID_ASPI_WNASPI);
			new FXMenuRadio(interfacemenu, "&FrogAspi", this, ID_ASPI_FROGASPI);
		new FXMenuCascade(aspimenu, "&Interface", NULL, interfacemenu);
		new FXMenuCommand(aspimenu,"&Rescan devices", refreshIcon, this, ID_RESCANDEVICES);
		burnDevicesOnly = new FXMenuCheck(aspimenu,"&Burn devices only", this, ID_BURNDEVICES);
		imagewriter = new FXMenuCheck(aspimenu,"Disable &imagewriter", this, ID_DISABLEIMAGE);
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

	m_tabs = new FXTabBook(this, NULL, 0, TABBOOK_NORMAL|LAYOUT_FILL_X|LAYOUT_FILL_Y);
		new FXTabItem(m_tabs, "Drive info");
			FXHorizontalFrame* driveinfo = new FXHorizontalFrame(m_tabs, FRAME_RAISED);
				FXVerticalFrame* infolabels = new FXVerticalFrame(driveinfo);
					new FXLabel(infolabels, "Disk type:", NULL, LAYOUT_RIGHT);
					new FXLabel(infolabels, "Max. burn speed:", NULL, LAYOUT_RIGHT);
					new FXLabel(infolabels, "Max. read speed:", NULL, LAYOUT_RIGHT);
					new FXLabel(infolabels, "Buffer underrun protection:", NULL, LAYOUT_RIGHT);
					new FXLabel(infolabels, "Test write:", NULL, LAYOUT_RIGHT);
				FXVerticalFrame* infovalues = new FXVerticalFrame(driveinfo);
					m_lblDiskType = new FXLabel(infovalues, "...");
					m_lblMaxBurnSpeed = new FXLabel(infovalues, "...");
					m_lblMaxReadSpeed = new FXLabel(infovalues, "...");
					m_lblUnderrunProtection = new FXLabel(infovalues, "...");
					m_lblTestWrite = new FXLabel(infovalues, "...");



	setMiniIcon(isosdkIconSmall);
	setIcon(isosdkIconBig);

	m_strStartupDir = FXSystem::getCurrentDirectory();
}

//--------------------------------------------------------------
// First Load and build Class then load SDK settings to the app
// to make sure that the Fox-Toolkit is initialized the right way.
//--------------------------------------------------------------
void KUtilitiesFOXLibDlg::loadOwner()
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

	if (m_bBurningDevicesOnly)
		burnDevicesOnly->setCheck();
	imagewriter->setCheck();

	new FXTabItem(m_tabs, "Drive info extended");
	FXHorizontalFrame* driveinfoex = new FXHorizontalFrame(m_tabs, FRAME_RAISED);
	m_lstInfoEx = new FXIconList(driveinfoex, NULL, 0, LAYOUT_FILL | FRAME_THICK | ICONLIST_DETAILED | ICONLIST_EXTENDEDSELECT);
	m_lstInfoEx->appendHeader("Parameter", NULL, 150);
	m_lstInfoEx->appendHeader("Value", NULL, 200);

	new FXTabItem(m_tabs, "Drive capabilities");
	FXVerticalFrame* capsframe = new FXVerticalFrame(m_tabs, FRAME_RAISED);
	createCapabilitiesPage(capsframe);

	new FXTabItem(m_tabs, "Medium info");
	FXVerticalFrame* mediumframe = new FXVerticalFrame(m_tabs, FRAME_RAISED);
	createMediumPage(mediumframe);

	new FXTabItem(m_tabs, "Image creation");
	FXVerticalFrame* imageframe = new FXVerticalFrame(m_tabs, FRAME_RAISED);
	createImagePage(imageframe);

	new FXTabItem(m_tabs, "Disc copy");
	FXVerticalFrame* copydiscframe = new FXVerticalFrame(m_tabs, FRAME_RAISED);
	createCopydiscPage(copydiscframe);

	//--------------------------------------------------
	//Fill Devicelist and Select
	//--------------------------------------------------

	updateDeviceCombo();
	UpdateDriveInfo();
	UpdateDriveInfoEx();
	UpdateDriveCapabilities();
	UpdateMediumInfo();

	

	res = ::SetProcessEventCallback((ProcessEvent)KUtilitiesFOXLibDlg::OnProcessEvent, this);
	handleError(res);

	res = ::SetJobDoneEventCallback((JobDoneEvent)KUtilitiesFOXLibDlg::OnJobDoneEvent, this);
	handleError(res);

	res = ::SetBurnDoneEventCallback((BurnDoneEvent)KUtilitiesFOXLibDlg::OnBurnDoneEvent, this);
	handleError(res);

	//Verify Image Creation
	res = ::SetStartVerifyEventCallback((StartVerifyEvent)KUtilitiesFOXLibDlg::OnStartVerifyEvent, this);
	handleError(res);
	res = ::SetVerifySectorEventCallback((VerifySectorEvent)KUtilitiesFOXLibDlg::OnVerifySectorEvent, this);
	handleError(res);
	res = ::SetVerifyDoneEventCallback((VerifyDoneEvent)KUtilitiesFOXLibDlg::OnVerifyDoneEvent, this);
	handleError(res);

	m_EState = ST_NONE;

}

void KUtilitiesFOXLibDlg::createCapabilitiesPage(FXVerticalFrame* frame)
{
	new FXLabel(frame, "If you didn't get the expected drive data it is possible that your drive doesn't support the commands sent to the\n"
					"drive. Usually a Firmware update helps to fix this problem.", NULL, JUSTIFY_LEFT);

	FXGroupBox* group = new FXGroupBox(frame, "Info", GROUPBOX_NORMAL|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	FXHorizontalFrame* row1 = new FXHorizontalFrame(group, LAYOUT_FILL_X);

	FXVerticalFrame* row1column1 = new FXVerticalFrame(row1, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH, 0, 0, 160, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
    m_mCaps[BS_READ_CDR] = new FXCheckButton(row1column1, "Read CD-R");
    m_mCaps[BS_READ_CDRW] = new FXCheckButton(row1column1, "Read CD-RW");
    m_mCaps[BS_READ_DVD] = new FXCheckButton(row1column1, "Read DVD");
    m_mCaps[BS_READ_DVDR] = new FXCheckButton(row1column1, "Read DVD-R");
    m_mCaps[BS_READ_DVDRW] = new FXCheckButton(row1column1, "Read DVD-RW");
    m_mCaps[BS_READ_DVDRAM] = new FXCheckButton(row1column1, "Read DVD-RAM");
    m_mCaps[BS_READ_DVDR_PLUS] = new FXCheckButton(row1column1, "Read DVD+R");
    m_mCaps[BS_READ_DVDRW_PLUS] = new FXCheckButton(row1column1, "Read DVD+RW");
    m_mCaps[BS_READ_DVD_DL] = new FXCheckButton(row1column1, "Read DVD DL");
    m_mCaps[BS_READ_DVD_MRDL] = new FXCheckButton(row1column1, "Read DVD-MRDL");
    m_mCaps[BS_READ_BLURAY_R] = new FXCheckButton(row1column1, "Read BLURAY-R");

	FXVerticalFrame* row1column2 = new FXVerticalFrame(row1, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH, 0, 0, 140, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
	m_mCaps[BS_READ_BLURAY_RE] = new FXCheckButton(row1column2, "Read BLURAY-RE");
    m_mCaps[BS_READ_BLURAY_ROM] = new FXCheckButton(row1column2, "Read BLURAY-ROM");
    m_mCaps[BS_READ_HDDVD_R] = new FXCheckButton(row1column2, "Read HDDVD-R");
    m_mCaps[BS_READ_HDDVD_RW] = new FXCheckButton(row1column2, "Read HDDVD-RW");
    m_mCaps[BS_READ_HDDVD_ROM] = new FXCheckButton(row1column2, "Read HDDVD-ROM");
	m_mCaps[BS_READ_DVD_RDL_PLUS] = new FXCheckButton(row1column2, "Read DVD+R DL");
	m_mCaps[BS_READ_DVD_RWDL_PLUS] = new FXCheckButton(row1column2, "Read DVD+RW DL");
	m_mCaps[BS_READ_MOUNT_RAINER] = new FXCheckButton(row1column2, "Read Mount Rainer");
	m_mCaps[BS_READ_CDRW_CAV] = new FXCheckButton(row1column2, "Read CD-RW Cav");

	FXVerticalFrame* row1column3 = new FXVerticalFrame(row1, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH, 0, 0, 140, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
    m_mCaps[BS_WRITE_CDR] = new FXCheckButton(row1column3, "Write CD-R");
    m_mCaps[BS_WRITE_CDRW] = new FXCheckButton(row1column3, "Write CD-RW");
    m_mCaps[BS_WRITE_DVDR] = new FXCheckButton(row1column3, "Write DVD-R");
    m_mCaps[BS_WRITE_DVDRW] = new FXCheckButton(row1column3, "Write DVD-RW");
    m_mCaps[BS_WRITE_DVDRAM] = new FXCheckButton(row1column3, "Write DVD-RAM");
    m_mCaps[BS_WRITE_DVDR_PLUS] = new FXCheckButton(row1column3, "Write DVD+R");
    m_mCaps[BS_WRITE_DVDRW_PLUS] = new FXCheckButton(row1column3, "Write DVD+RW");
    m_mCaps[BS_WRITE_DVD_DL] = new FXCheckButton(row1column3, "Write DVD DL");
    m_mCaps[BS_WRITE_DVD_MRDL] = new FXCheckButton(row1column3, "Write DVD-MRDL");
    m_mCaps[BS_WRITE_BLURAY_R] = new FXCheckButton(row1column3, "Write BLURAY-R");

	FXVerticalFrame* row1column4 = new FXVerticalFrame(row1, LAYOUT_FILL_Y, 0, 0, 0, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
    m_mCaps[BS_WRITE_BLURAY_RE] = new FXCheckButton(row1column4, "Write BLURAY-RE");
    m_mCaps[BS_WRITE_HDDVD_R] = new FXCheckButton(row1column4, "Write HDDVD-R");
    m_mCaps[BS_WRITE_HDDVD_RW] = new FXCheckButton(row1column4, "Write HDDVD-RW");
	m_mCaps[BS_WRITE_DVD_RDL_PLUS] = new FXCheckButton(row1column4, "Write DVD+R DL");
	m_mCaps[BS_WRITE_DVD_RWDL_PLUS] = new FXCheckButton(row1column4, "Write DVD+RW DL");
	m_mCaps[BS_WRITE_MOUNT_RAINER] = new FXCheckButton(row1column4, "Write Mount Rainer");
	m_mCaps[BS_WRITE_CDRW_CAV] = new FXCheckButton(row1column4, "Write CD-RW Cav");

	FXHorizontalFrame* row2 = new FXHorizontalFrame(group, LAYOUT_FILL_X);

	FXVerticalFrame* row2column1 = new FXVerticalFrame(row2, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH, 0, 0, 160, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
	m_mCaps[BS_WRITE_TEST] = new FXCheckButton(row2column1, "Can simulate write");
    m_mCaps[BS_CPRMAUTH] = new FXCheckButton(row2column1, "CPRM Auth");
	m_mCaps[BS_ANALOG_AUDIO_PLAYBACK] = new FXCheckButton(row2column1, "Analog audio playback");
	m_mCaps[BS_COMPOSITE_AUDIO_AND_VIDEO] = new FXCheckButton(row2column1, "Composite audio/video");
	m_mCaps[BS_DIGITAL_PORT_1] = new FXCheckButton(row2column1, "Digital port 1");
	m_mCaps[BS_DIGITAL_PORT_2] = new FXCheckButton(row2column1, "Digital port 2");
	m_mCaps[BS_MODE2_FORM1_READ] = new FXCheckButton(row2column1, "Mode 2 Form 1 Read");
	m_mCaps[BS_MODE2_FORM2_READ] = new FXCheckButton(row2column1, "Mode 2 Form 2 Read");
	m_mCaps[BS_CDDA_COMMANDS] = new FXCheckButton(row2column1, "CDDA Commands");
	m_mCaps[BS_CDDA_STREAM_IS_ACCURATE] = new FXCheckButton(row2column1, "CDDA Accurate Stream");
	m_mCaps[BS_LABELFLASH] = new FXCheckButton(row2column1, "LabelFlash");

	FXVerticalFrame* row2column2 = new FXVerticalFrame(row2, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH, 0, 0, 140, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
	m_mCaps[BS_MULTISESSION] = new FXCheckButton(row2column2, "Multisession");
    m_mCaps[BS_STREAMING] = new FXCheckButton(row2column2, "Streaming");
	m_mCaps[BS_R_W_SUBCHANNELS_READ] = new FXCheckButton(row2column2, "R-W SC read");
	m_mCaps[BS_R_W_SUBCHANNELS_DEINT_AND_CORR] = new FXCheckButton(row2column2, "R-W SC deint.");
	m_mCaps[BS_C2_POINTERS] = new FXCheckButton(row2column2, "C2 Pointers");
	m_mCaps[BS_ISRC_READ] = new FXCheckButton(row2column2, "ISRC Read");
	m_mCaps[BS_UPC_READ] = new FXCheckButton(row2column2, "UPC Read");
	m_mCaps[BS_BARCODE_READ] = new FXCheckButton(row2column2, "Barcode Read");
	m_mCaps[BS_LOCK_MEDIA] = new FXCheckButton(row2column2, "Locking media");
	m_mCaps[BS_LOCK_STATE] = new FXCheckButton(row2column2, "Lock state");
	m_mCaps[BS_LIGHTSCRIBE] = new FXCheckButton(row2column2, "LightScribe");

	FXVerticalFrame* row2column3 = new FXVerticalFrame(row2, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH, 0, 0, 140, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
	m_mCaps[BS_SMART] = new FXCheckButton(row2column3, "S.M.A.R.T.");
	m_mCaps[BS_UNDERRUN_PROTECTION] = new FXCheckButton(row2column3, "Underrun Protection");
	m_mCaps[BS_PREVENT_JUMPER] = new FXCheckButton(row2column3, "Prevent lock jumper");
	m_mCaps[BS_EJECT_INDIVIDUAL_OR_MAGAZINE] = new FXCheckButton(row2column3, "Eject support");
	m_mCaps[BS_SEPARATE_VOLUME_LEVELS] = new FXCheckButton(row2column3, "Sep. volume levels");
	m_mCaps[BS_SEPARATE_CHANNEL_MUTE] = new FXCheckButton(row2column3, "Sep. channel mute");
	m_mCaps[BS_CHANGER_SUPPORTS_DISC_PRESENT] = new FXCheckButton(row2column3, "Disc present");
	m_mCaps[BS_CHANGER_SOFTWARE_SLOT_SELECTION] = new FXCheckButton(row2column3, "SW Slot Selection");
	m_mCaps[BS_CHANGER_SIDE_CHANGE_CAPABLE] = new FXCheckButton(row2column3, "Side change");
	m_mCaps[BS_R_W_SUBCHANNELS_IN_LEAD_IN_READ] = new FXCheckButton(row2column3,"R-W SC in LI Read");

	FXVerticalFrame* row2column4 = new FXVerticalFrame(row2, LAYOUT_FILL_Y, 0, 0, 0, 0,
		DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, DEFAULT_SPACING, 1);
	m_mCaps[BS_DEFECTMANAGEMENT] = new FXCheckButton(row2column4, "Defect management");
	m_mCaps[BS_LAYER_JUMP_RECORDING] = new FXCheckButton(row2column4, "Layer Jump Recording");
	m_mCaps[BS_METHOD_2_ADDRESSING_FIXED_PACKETS] = new FXCheckButton(row2column4, "Method 2 FP Read");
	m_mCaps[BS_CD_TEXT_READ] = new FXCheckButton(row2column4, "CD-Text Read");
	m_mCaps[BS_CD_TEXT_WRITE] = new FXCheckButton(row2column4, "CD-Text Write");
	m_mCaps[BS_DAO_RAW] = new FXCheckButton(row2column4, "DAO Raw");
	m_mCaps[BS_DAO_16] = new FXCheckButton(row2column4,	"DAO 16");
	m_mCaps[BS_DAO_96_PACK] = new FXCheckButton(row2column4, "DAO 96 Pack");
	m_mCaps[BS_DAO_96_RAW] = new FXCheckButton(row2column4,	"DAO 96 Raw");
	m_mCaps[BS_PACKET_WRITE] = new FXCheckButton(row2column4, "Packet Write");
}

long KUtilitiesFOXLibDlg::onWriteLogFile(FXObject* sender, FXSelector key, void* data)
{
	::SaveLogToFile(KString(m_strStartupDir.text()) + PATHSEPSTRING + "FoxSampleUtilitiesC.log");
	return 1;
}

void KUtilitiesFOXLibDlg::createMediumPage(FXVerticalFrame* frame)
{
	FXHorizontalFrame* topFrame = new FXHorizontalFrame(frame, LAYOUT_FILL_X);

	FXMatrix* topColumn1 = new FXMatrix(topFrame, 2, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FIX_WIDTH, 0, 0, 180);
	new FXLabel(topColumn1, "Medium:");
	m_lblMedium = new FXLabel(topColumn1, "...");
	new FXLabel(topColumn1, "Status:");
	m_lblMediumStatus = new FXLabel(topColumn1, "...");
	new FXLabel(topColumn1, "Last:");
	m_lblLastSession = new FXLabel(topColumn1, "...");
	new FXLabel(topColumn1, "Sessions:");
	m_lblMediumSessions = new FXLabel(topColumn1, "...");
	new FXLabel(topColumn1, "Tracks:");
	m_lblMediumTracks = new FXLabel(topColumn1, "...");

	FXMatrix* topColumn2 = new FXMatrix(topFrame, 2, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FIX_WIDTH, 0, 0, 200);
	new FXLabel(topColumn2, "Size:");
	m_lblMediumSize = new FXLabel(topColumn2, "...");
	new FXLabel(topColumn2, "Used space:");
	m_lblMediumUsed = new FXLabel(topColumn2, "...");
	new FXLabel(topColumn2, "Free space:");
	m_lblMediumFree = new FXLabel(topColumn2, "...");
	new FXLabel(topColumn2, "UPC/EAN code:");
	m_lblMediumCatalogCode = new FXLabel(topColumn2, "...");
	new FXLabel(topColumn2, "Vendor ID:");
	m_lblMediumVendorID = new FXLabel(topColumn2, "...");

	FXMatrix* topColumn3 = new FXMatrix(topFrame, 2, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FIX_WIDTH, 0, 0, 200);
	new FXLabel(topColumn3, "Maximum write speed:");
	m_lblMediumMaxWriteSpeed = new FXLabel(topColumn3, "...");

	m_btnCloseSession = new FXButton(frame, "Terminate last session", NULL, this, ID_CLOSESESSION, BUTTON_NORMAL|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 200, 25);
	m_btnCloseSession->disable();

	m_lstSessions = new FXTreeList(frame, NULL, 0, LAYOUT_FILL|FRAME_THICK|TREELIST_SINGLESELECT|TREELIST_SHOWS_LINES|TREELIST_SHOWS_BOXES);

	FXIcon* refreshIcon = new FXICOIcon(getApp(), refresh2);
	FXIcon* ejectIcon = new FXICOIcon(getApp(), cd_eject);

	FXHorizontalFrame* btnframe = new FXHorizontalFrame(frame);
		new FXButton(btnframe, "Refresh", refreshIcon, this, ID_GETDISKINFO, BUTTON_NORMAL|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0,0, 100, 25);
		new FXButton(btnframe, "Eject", ejectIcon, this, ID_EJECTTRAY, BUTTON_NORMAL|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0,0, 100, 25);
}

void KUtilitiesFOXLibDlg::createImagePage(FXVerticalFrame* frame)
{
	FXHorizontalFrame *pTextBoxFrame = new FXHorizontalFrame(frame, FRAME_NONE);

		m_txtBrowseBoxImg = new FXTextField(pTextBoxFrame, 20, this, ID_BROWSE_TEXT_BOX, 
			LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH|TEXTFIELD_NORMAL, 0, 0, 450, 20);

		m_btnBrowseDestImg = new FXButton(pTextBoxFrame, "&Browse", 0, this, ID_BROWSEDEST_BTN, 
			LAYOUT_FIX_X|LAYOUT_FILL_X|BUTTON_NORMAL, 465);

	FXHorizontalFrame *pReadErrorFrame = new FXHorizontalFrame(frame, FRAME_NONE);

		FXGroupBox *pErrorGroup	= new FXGroupBox(pReadErrorFrame, "Read errors correction settings", 
			FRAME_THICK|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH|GROUPBOX_NORMAL, 0, 0, 386, 200);

			m_chbErrorCorrectImg = new FXCheckButton(pErrorGroup, "&Read errors correction enabled");

			FXMatrix *pRetriesFrame = new FXMatrix(pErrorGroup, 2, MATRIX_BY_ROWS, 0, 0, 0, 0, 40);
			
				new FXLabel(pRetriesFrame, "Hardware retries count :", 0, LABEL_NORMAL);
				new FXLabel(pRetriesFrame, "Software retries count :", 0, LABEL_NORMAL);

				m_spnHardwareImg = new FXSpinner(pRetriesFrame, 3, 0, 0, SPIN_NORMAL | FRAME_THICK | FRAME_SUNKEN);
				m_spnHardwareImg->setRange(0, 300);
				m_spnSoftwareImg = new FXSpinner(pRetriesFrame, 3, 0, 0, SPIN_NORMAL | FRAME_THICK | FRAME_SUNKEN);
				m_spnSoftwareImg->setRange(0, 300);

			m_chbBlankBadImg = new FXCheckButton(pErrorGroup, "B&lank bad sectors");
			m_chbBadSectListImg = new FXCheckButton(pErrorGroup, "&Bad sectors list");

			FXHorizontalFrame *pSectorsListFrame= new FXHorizontalFrame(pErrorGroup, FRAME_NONE);
				new FXLabel(pSectorsListFrame, "Path :", 0, LABEL_NORMAL, 0,0,0,0, 40);

				m_txtSetorsListPathImg = new FXTextField(pSectorsListFrame, 20, this, ID_BROWSE_TEXT_BOX, 
					LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH|TEXTFIELD_NORMAL, 0, 0, 250, 20);


		//FXVerticalFrame *pManageFrame = new FXVerticalFrame(pReadErrorFrame, FRAME_NONE);
				FXGroupBox *pManageFrame = new FXGroupBox(pReadErrorFrame, "Format",
					FRAME_THICK | LAYOUT_FIX_HEIGHT | LAYOUT_FIX_WIDTH | GROUPBOX_NORMAL, 0, 0, 179, 200);
		
			FXHorizontalFrame *pFormatFrame = new FXHorizontalFrame(pManageFrame, FRAME_NONE);
					
				m_cmbFormatImg = new FXComboBox(pFormatFrame, 30, this, ID_FORMATBOX_CMB, 
					LAYOUT_FIX_WIDTH|LAYOUT_LEFT|FRAME_NORMAL|COMBOBOX_STATIC, 0, 0, 90);
				m_cmbFormatImg->setNumVisible(2);

			m_btnCheckFormatImg = new FXButton(pManageFrame, "&Check format", 0, this, 
				ID_CHECKFORMAT_BTN, LAYOUT_FIX_WIDTH |BUTTON_NORMAL, 0, 0, 91);


	FXVerticalFrame *pJobFrame = new FXVerticalFrame(frame, FRAME_NONE);
		FXGroupBox *pJobGroup = new FXGroupBox(pJobFrame, "Jobs",
			FRAME_THICK | LAYOUT_FIX_HEIGHT | LAYOUT_FIX_WIDTH | GROUPBOX_NORMAL, 0, 0, 570, 100);

			m_chbCreateImg = new FXCheckButton(pJobGroup, "&Create", 0, 0,
				CHECKBUTTON_NORMAL, 0, 0, 0, 0, DEFAULT_PAD, DEFAULT_PAD, 0);
			m_chbVerifyImg = new FXCheckButton(pJobGroup, "&Verify");

			m_btnExecuteImg = new FXButton(pJobGroup, "&Execute", 0, this, ID_EXECUTEIMAGE_BTN,
				LAYOUT_FILL_X | BUTTON_NORMAL, 0, 0, 107);


	FXVerticalFrame *pProcessFrame = new FXVerticalFrame(frame, FRAME_NONE);

		FXGroupBox *pProcessGroup = new FXGroupBox(pProcessFrame, "Process information", 
			FRAME_THICK|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH|GROUPBOX_NORMAL, 0, 0, 570, 160);

			m_barProgressImg = new FXProgressBar(pProcessGroup, NULL, 0, 
				LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK|PROGRESSBAR_PERCENTAGE);

			//The last value in Matrix is the row number.
			FXMatrix *pProcessMatrixFrame = new FXMatrix(pProcessGroup, 3);			
			
				new FXLabel(pProcessMatrixFrame, "Total sectors : ");
				new FXLabel(pProcessMatrixFrame, "Current sector : ");
				new FXLabel(pProcessMatrixFrame, "Sectors verify : ");

				

				m_lblTtlSectorsImg = new FXLabel(pProcessMatrixFrame, "");
				m_lblCurrentSectorImg = new FXLabel(pProcessMatrixFrame, "");
				m_lblSectorsImg = new FXLabel(pProcessMatrixFrame, "");
				

				new FXLabel(pProcessMatrixFrame, "Read errors : ", 0, LABEL_NORMAL, 0,0,0,0, 100);
				new FXLabel(pProcessMatrixFrame, "Percentage : ", 0, LABEL_NORMAL, 0,0,0,0, 100);
				new FXLabel(pProcessMatrixFrame, "State : ", 0, LABEL_NORMAL, 0, 0, 0, 0, 100);
				
				m_lblReadErrorsImg = new FXLabel(pProcessMatrixFrame, "");
				m_lblPercentageImg = new FXLabel(pProcessMatrixFrame, "");
				m_lbStateImg = new FXLabel(pProcessMatrixFrame, "");
				

				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 100);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 100);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 100);

				m_btnAbortImg = new FXButton(pProcessGroup, "&Abort", 0, this,
					ID_ABORT_IMG_BTN, LAYOUT_FILL_X | BUTTON_NORMAL, 0, 0, 130);

	
	m_chbBlankBadImg->setCheck();
	m_chbErrorCorrectImg->setCheck();
	m_chbCreateImg->setCheck();
	m_btnAbortImg->disable();

	CheckFormat();
}

void KUtilitiesFOXLibDlg::createCopydiscPage(FXVerticalFrame* frame)
{
	FXHorizontalFrame *pSourceDeviceFrame = new FXHorizontalFrame(frame, FRAME_NONE);

		new FXLabel(pSourceDeviceFrame, "Source device : ");

		m_cmbSourceDevDsc = new FXComboBox(pSourceDeviceFrame, 30, this, ID_DEVICEBOX, LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
		
	FXHorizontalFrame *pReadErrorFrame = new FXHorizontalFrame(frame, FRAME_NONE);

		FXGroupBox *pErrorGroup	= new FXGroupBox(pReadErrorFrame, "Read errors correction settings", 
			FRAME_THICK|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH|GROUPBOX_NORMAL, 30, 0, 386, 115);

			m_chbErrorCorrectDsc = new FXCheckButton(pErrorGroup, "&Read errors correction enabled");

			FXMatrix *pRetriesFrame = new FXMatrix(pErrorGroup, 2, MATRIX_BY_ROWS, 0, 0, 0, 0, 40);
			
				new FXLabel(pRetriesFrame, "Hardware retries count :", 0, LABEL_NORMAL);
				new FXLabel(pRetriesFrame, "Software retries count :", 0, LABEL_NORMAL);

				m_spnHardwareDsc = new FXSpinner(pRetriesFrame, 3, 0, 0, SPIN_NORMAL | FRAME_THICK | FRAME_SUNKEN);
				m_spnHardwareDsc->setRange(0, 300);
				m_spnSoftwareDsc = new FXSpinner(pRetriesFrame, 3, 0, 0, SPIN_NORMAL | FRAME_THICK | FRAME_SUNKEN);
				m_spnSoftwareDsc->setRange(0, 300);

		//FXVerticalFrame *pManageFrame= new FXVerticalFrame(pReadErrorFrame, FRAME_NONE);
	
		FXGroupBox *pModeFrame = new FXGroupBox(pReadErrorFrame, "Read & write methods",
			FRAME_THICK | LAYOUT_FIX_HEIGHT | LAYOUT_FIX_WIDTH | GROUPBOX_NORMAL, 0, 0, 179, 115);
		FXMatrix *pModeFrame2 = new FXMatrix(pModeFrame, 2);
			
			new FXLabel(pModeFrame2, "Write : ");
			new FXLabel(pModeFrame2, "Read : ");

			m_cmbWMethodDsc = new FXComboBox(pModeFrame2, 30, this, ID_SOURCEDEV_CMB, 
				LAYOUT_FIX_WIDTH|LAYOUT_LEFT|FRAME_NORMAL|COMBOBOX_STATIC, 0, 0, 70);
			m_cmbWMethodDsc->setNumVisible(2);
			
			m_cmbRModeDsc = new FXComboBox(pModeFrame2, 30, this, ID_SOURCEDEV_CMB, 
				LAYOUT_FIX_WIDTH|LAYOUT_LEFT|FRAME_NORMAL|COMBOBOX_STATIC, 0, 0, 70);
			m_cmbRModeDsc->setNumVisible(3);

		FXVerticalFrame *pCopyJobFrame = new FXVerticalFrame(frame, FRAME_NONE);
		FXGroupBox *pCopyJobGroup = new FXGroupBox(pCopyJobFrame, "Jobs",
				FRAME_THICK | LAYOUT_FIX_HEIGHT | LAYOUT_FIX_WIDTH | GROUPBOX_NORMAL, 0, 0, 570, 125);

			m_chbAutoErase = new FXCheckButton(pCopyJobGroup, "&Auto erase before copy");
			m_chbVerifyDsc = new FXCheckButton(pCopyJobGroup, "&Verify after burn");
			m_chbEjectDsc = new FXCheckButton(pCopyJobGroup, "&Eject after burn");

			m_btnExecuteDsc = new FXButton(pCopyJobGroup, "&Copy", 0, this, ID_DISCCOPY_BTN,
				LAYOUT_FILL_X|BUTTON_NORMAL);

	FXVerticalFrame *pProcessFrame = new FXVerticalFrame(frame, FRAME_NONE);

		FXGroupBox *pProcessGroup = new FXGroupBox(pProcessFrame, "Process information", 
			FRAME_THICK|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH|GROUPBOX_NORMAL, 0, 0, 570, 185);

			m_barProgressDsc = new FXProgressBar(pProcessGroup, NULL, 0, 
				LAYOUT_FILL_X|FRAME_SUNKEN|FRAME_THICK|PROGRESSBAR_PERCENTAGE);

			FXMatrix *pProcessMatrixFrame = new FXMatrix(pProcessGroup, 4);			
			
				new FXLabel(pProcessMatrixFrame, "Total bytes : ");
				new FXLabel(pProcessMatrixFrame, "Bytes written : ");
				new FXLabel(pProcessMatrixFrame, "Job state : ");
				new FXLabel(pProcessMatrixFrame, "Verify sectors : ");

				m_lblTtlBytesDsc = new FXLabel(pProcessMatrixFrame, "");
				m_lblBytesWrittenDsc = new FXLabel(pProcessMatrixFrame, "");
				m_lbljobState = new FXLabel(pProcessMatrixFrame, "");
				m_lblVerifySectors = new FXLabel(pProcessMatrixFrame, "");
				
				new FXLabel(pProcessMatrixFrame, "Percentage : ", 0, LABEL_NORMAL, 0,0,0,0, 100);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 100);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 100);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 100);
								
				m_lblPercentageDsc = new FXLabel(pProcessMatrixFrame, "");
				new FXLabel(pProcessMatrixFrame, " ");
				new FXLabel(pProcessMatrixFrame, " ");
				new FXLabel(pProcessMatrixFrame, " ");

				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 20);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 20);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 20);
				new FXLabel(pProcessMatrixFrame, " ", 0, LABEL_NORMAL, 0, 0, 0, 0, 20);

				m_btnAbortDsc = new FXButton(pProcessGroup, "&Abort", 0, this,
					ID_ABORT_DSC_BTN, LAYOUT_FILL_X |BUTTON_NORMAL, 0, 0, 107);

	m_chbErrorCorrectDsc->setCheck();
	m_btnAbortDsc->disable();

	CheckDiscWriteMethod();
	UpdateSourceDeviceCombo();	
}

KUtilitiesFOXLibDlg::~KUtilitiesFOXLibDlg()
{
	int32 nRes = ::SetProcessEventCallback(NULL, NULL);
	handleError(nRes);

	nRes = ::SetJobDoneEventCallback(NULL, NULL);
	handleError(nRes);

	nRes = ::SetBurnDoneEventCallback(NULL, NULL);
	handleError(nRes);

	nRes = ::SetStartVerifyEventCallback(NULL, NULL);
	handleError(nRes);

	nRes = ::SetVerifySectorEventCallback(NULL, NULL);
	handleError(nRes);

	nRes = ::SetVerifyDoneEventCallback(NULL, NULL);
	handleError(nRes);

	::DeInitialize();
}

void KUtilitiesFOXLibDlg::addLogLine(FXString strLogLine)
{
	//m_strLogLine = strLogLine;
	//getApp()->addChore(this, KUtilitiesFOXLibDlg::ID_ADDLOGLINE, &m_strLogLine);
	//guisignal.signal();
}

long KUtilitiesFOXLibDlg::onAddLogLine(FXObject* sender, FXSelector key, void* data)
{
	FXString *pstrLogLine = (FXString*)data;
	if (NULL != pstrLogLine) {
		//FXint indx = m_lbxLog->appendItem(*pstrLogLine);
		//m_lbxLog->setCurrentItem(indx);
		//m_lbxLog->makeItemVisible(indx);
	}

	return 1;
}

long KUtilitiesFOXLibDlg::onDeviceBoxChange(FXObject* sender, FXSelector key, void* data)
{
	FXint indx = m_cmbDevice->getCurrentItem();

	if (m_bMultideviceEnabled && indx == m_cmbDevice->getNumItems()-1)
	{
		CALL_FXDIALOG(::MultiDeviceDialog());

		updateDeviceCombo();
	} else if (-1 < indx) {


		FXString strItem = m_cmbDevice->getItemText(indx);

		KString strDevice = Fox2SDKString(strItem);

		int32 res = ::SetBurnDevice(strDevice);
		handleError(res);


	}

	int32 nCount = 0;
	::GetActiveDevicesCount(&nCount);
	if (nCount > 1) return 0;

	getApp()->beginWaitCursor();

	CheckFormat();
	CheckDiscWriteMethod();

	UpdateDriveInfo();
	UpdateDriveInfoEx();
	UpdateDriveCapabilities();
	UpdateMediumInfo();

	getApp()->endWaitCursor();
	
	return 1;
}

long KUtilitiesFOXLibDlg::onIsReady(FXObject* sender, FXSelector key, void* data)
{
	BS_BOOL	bReady = BS_FALSE;
	int32 nError = ::IsDeviceReady(BS_CURRENT_DEVICE, &bReady);

	if (nError == BS_SDK_ERROR_NO)
	{
		FXString message = bReady ? "Device is ready." : "Device is not ready";
        FXMessageBox msgBox(this, "UtilitiesFOXLib", message, NULL,  MBOX_OK);
		msgBox.execute();
	}

	handleError(nError);
	return 1;
}

long KUtilitiesFOXLibDlg::onEjectTray(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::EjectDevice();
	if (res == BS_SCSI_ERROR_109)
	{
		FXuint nID = FXMessageBox::warning(this, MBOX_YES_NO, "UtilitiesFOXLib", "Device is locked.\nWould you like to force ejecting the disk?");
		if (nID == MBOX_CLICKED_YES)
		{
			::LockMedium(BS_CURRENT_DEVICE, BS_FALSE);
			onEjectTray(sender, key, data);
		}
	}
	else
	{
		handleError(res);
	}
	return 1;
}

long KUtilitiesFOXLibDlg::onCloseTray(FXObject* sender, FXSelector key, void* data)
{
	::CloseDevice();
	return 1;
}

long KUtilitiesFOXLibDlg::onLockDevice(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::LockMedium(BS_CURRENT_DEVICE, BS_TRUE);
	handleError(res);
	return 1;
}

long KUtilitiesFOXLibDlg::onUnlockDevice(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::LockMedium(BS_CURRENT_DEVICE, BS_FALSE);
	handleError(res);
	return 1;
}

FXString IntToStr(int value)
{
	FXString text;
	text.format("%d", value);
	return text;
}

FXString RealToStr(double value)
{
	FXString text;
	text.format("%.2f", value);
	return text;
}

long KUtilitiesFOXLibDlg::onGetDriveInfo(FXObject* sender, FXSelector key, void* data)
{
	m_tabs->setCurrent(0);

	getApp()->beginWaitCursor();
	UpdateDriveInfo();
	getApp()->endWaitCursor();

	return 1;
}

long KUtilitiesFOXLibDlg::onGetDriveInfoEx(FXObject* sender, FXSelector key, void* data)
{
	m_tabs->setCurrent(1);

	getApp()->beginWaitCursor();
	UpdateDriveInfoEx();
	getApp()->endWaitCursor();

	return 1;
}

long KUtilitiesFOXLibDlg::onGetCapabilities(FXObject* sender, FXSelector key, void* data)
{
	m_tabs->setCurrent(2);

	getApp()->beginWaitCursor();
	UpdateDriveCapabilities();
	getApp()->endWaitCursor();

	return 1;
}

long KUtilitiesFOXLibDlg::onSetRegionCode(FXObject* sender, FXSelector key, void* data)
{
	KRegionChangeDlg dlg(this);
	dlg.execute();
	return 0;
}

long KUtilitiesFOXLibDlg::onGetDiskInfo(FXObject* sender, FXSelector key, void* data)
{
	m_tabs->setCurrent(3);

	getApp()->beginWaitCursor();
	UpdateMediumInfo();
	getApp()->endWaitCursor();

	return 1;
}

long KUtilitiesFOXLibDlg::onCloseSession(FXObject* sender, FXSelector key, void* data)
{
	int32 nError = ::CloseSession(BS_CURRENT_DEVICE);
	handleError(nError);
	return 1;
}

long KUtilitiesFOXLibDlg::onEraseDisk(FXObject* sender, FXSelector key, void* data)
{	
	CALL_FXDIALOG_HANDLE_ERROR(::EraseDialog(_T("IsoSDK")));

	updateDeviceCombo();
	return 1;
}

void KUtilitiesFOXLibDlg::handleError(int32 errCode,const KString strPrefix) 
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
		if(strPrefix.GetLength())
		{
			strError = strPrefix + KString(_T("\n")) + strError;
		}

		FXString fxstr = (const wchar_t*)strError;
		FXMessageBox::error(this, MBOX_OK, "IsoSDK", fxstr.text());
	}
}

void KUtilitiesFOXLibDlg::updateDeviceCombo()
{
	m_cmbDevice->clearItems();
	m_bMultideviceEnabled = false;



	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 res = ::GetDevices(chListDevices, &nUsed, m_bBurningDevicesOnly ? BS_TRUE : BS_FALSE);
	handleError(res);

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	handleError(res);



	int cbCount = 0;
	for (int i = 0; i < nUsed; i++)
	{
		FXString strItem;
		strItem =(const wchar_t*)KString(chListDevices[i]);
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

	if (nUsed > 1) {
		m_bMultideviceEnabled = true;
		m_cmbDevice->appendItem("Multiple devices");
	}


	if (nBurnDevices > 1) {
		m_cmbDevice->setCurrentItem(m_cmbDevice->getNumItems() - 1);
	}
	


	m_cmbDevice->setNumVisible(m_cmbDevice->getNumItems());
}

long KUtilitiesFOXLibDlg::onRescanDevices(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::RescanDevices();
	handleError(res);

	updateDeviceCombo();

	return 1;
}

long KUtilitiesFOXLibDlg::onCmdAspi(FXObject* sender, FXSelector key, void* data)
{
	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;

	// Set selected interface

	int32 res = ::SetASPI(which);
	handleError(res);
	updateDeviceCombo();
	return 1;
}

long KUtilitiesFOXLibDlg::onUpdAspi(FXObject* sender, FXSelector key, void* data)
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

long KUtilitiesFOXLibDlg::onDisableImagewriter(FXObject* sender, FXSelector key, void* data)
{
	// Disable or enable image writer

	::EnableImageDevice(data == 0 ? BS_TRUE : BS_FALSE);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KUtilitiesFOXLibDlg::onBurningDevices(FXObject* sender, FXSelector key, void* data)
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = data != 0;
	updateDeviceCombo();
	return 1;
}

long KUtilitiesFOXLibDlg::onAbout(FXObject* sender, FXSelector key, void* data)
{
	KAboutDlg	aboutDlg(this);
	aboutDlg.execute();
	return 1;
}

long KUtilitiesFOXLibDlg::onWeb(FXObject* sender, FXSelector key, void* data)
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

long KUtilitiesFOXLibDlg::onErrorNotify(FXObject* sender, FXSelector key, void* data)
{
	int32 *res = (int32 *)data;
	handleError(*res);
	delete res;
	return 1;
}

void KUtilitiesFOXLibDlg::CheckFormat()
{
	UpdateImageReadDevice();

	int16 nImageFormats;
	int32 nRes = ::GetPossibleImageFormats(&nImageFormats);
	handleError(nRes);

	m_cmbFormatImg->clearItems();

	if (nImageFormats & BS_IMG_ISO)
	{
		m_cmbFormatImg->appendItem("ISO");		
	}

	if (nImageFormats & BS_IMG_BIN)
	{
		m_cmbFormatImg->appendItem("BIN");		
	}

	if (m_cmbFormatImg->getNumItems())
	{
		m_cmbFormatImg->enable();
		m_btnBrowseDestImg->enable();
		m_btnExecuteImg->enable();

		m_cmbFormatImg->setCurrentItem(0);
	}
	else
	{
		m_cmbFormatImg->disable();
		m_btnBrowseDestImg->disable();
		m_btnExecuteImg->disable();
	}

	SExtendedDeviceInformation sDeviceInfo;
	nRes = ::GetDeviceInformationEx(BS_CURRENT_DEVICE, &sDeviceInfo);
	handleError(nRes);
	
	m_spnHardwareImg->setValue(sDeviceInfo.nReadRetryCount);	
}

void KUtilitiesFOXLibDlg::CheckDiscWriteMethod()
{
	m_cmbWMethodDsc->clearItems();
	
	SMediumInfo cMediumInfo;
	int32 nRes = ::GetMediumInformation(BS_CURRENT_DEVICE, &cMediumInfo);
	if (nRes)
	{
		return;
	}

	m_cmbWMethodDsc->appendItem("DAO");

	if (cMediumInfo.wMediumTypeCode == BS_CD_ROM ||
		cMediumInfo.wMediumTypeCode == BS_CD_R ||
		cMediumInfo.wMediumTypeCode == BS_CD_RW)
	{
		m_cmbWMethodDsc->appendItem("DAO96");		
	}
	
	m_cmbWMethodDsc->setCurrentItem(0);
}

long KUtilitiesFOXLibDlg::onCheckFormat(FXObject* sender, FXSelector key, void* data)
{
	CheckFormat();
	return 1;
}

long KUtilitiesFOXLibDlg::onAbortImage(FXObject* sender, FXSelector key, void* data)
{
	int32 nRes = ::Abort();
	handleError(nRes);

	if (nRes != 0)
	{
		EnableControlsImg(true);
		m_EState = ST_NONE;
		m_barProgressImg->setProgress(0);
	}
	
	return 1;
}

long KUtilitiesFOXLibDlg::onAbortDisc(FXObject* sender, FXSelector key, void* data)
{
	int32 nRes = ::Abort();
	handleError(nRes);

	if (nRes != 0)
	{
		EnableControlsDsc(true);
		m_EState = ST_NONE;
		m_barProgressDsc->setProgress(0);
	}
	
	return 1;
}


void KUtilitiesFOXLibDlg::OnJobDoneEvent(KUtilitiesFOXLibDlg *pDlg)
{
	pDlg->OnJobDone();
}

void KUtilitiesFOXLibDlg::OnJobDone()
{
	if (m_EState == ST_IMAGE_CREATION)
	{
		//getApp()->addChore(this, KUtilitiesFOXLibDlg::ID_JOBDONE_IMG, NULL);
		guisignal.message(this,FXSEL(SEL_CHORE,KUtilitiesFOXLibDlg::ID_JOBDONE_IMG),NULL,NULL);
	}
	else if (m_EState == ST_DISC_COPY)
	{
		//getApp()->addChore(this, KUtilitiesFOXLibDlg::ID_JOBDONE_DSC, NULL);
		guisignal.message(this,FXSEL(SEL_CHORE,KUtilitiesFOXLibDlg::ID_JOBDONE_DSC),NULL,NULL);
	}

	
}

long KUtilitiesFOXLibDlg::onJobDoneImg(FXObject* sender, FXSelector key, void* data)
{
	EnableControlsImg(true);
	m_EState = ST_NONE;
	m_barProgressImg->setProgress(0);
	m_lblTtlSectorsImg->setText(_T(""));
	m_lblReadErrorsImg->setText(_T(""));
	m_lblCurrentSectorImg->setText(_T(""));
	m_lblPercentageImg->setText(_T(""));
	m_lblSectorsImg->setText(_T(""));
	m_lbStateImg->setText(_T(""));
	return 1;
}

long KUtilitiesFOXLibDlg::onJobDoneDsc(FXObject* sender, FXSelector key, void* data)
{
	EnableControlsDsc(true);
	m_EState = ST_NONE;
	m_barProgressDsc->setProgress(0);
	m_lblTtlBytesDsc->setText(_T(""));
	m_lblBytesWrittenDsc->setText(_T(""));
	m_lblVerifySectors->setText(_T(""));
	m_lbljobState->setText(_T(""));
	m_lblPercentageDsc->setText(_T(""));
	return 1;
}

//Verify Sector
void KUtilitiesFOXLibDlg::OnVerifySectorEvent(double nSector, double tSector, bool nSuccess, KUtilitiesFOXLibDlg *pDlg)
{
	pDlg->SetVerifySector(nSector, tSector, nSuccess);
}

void KUtilitiesFOXLibDlg::SetVerifySector(double nSector, double tSector, bool nSuccess)
{
	m_progInfo.vcurrentsector = nSector;
	m_progInfo.sectors = tSector;
	m_progInfo.success = nSuccess;

	if (m_EState == ST_IMAGE_CREATION)
	{
		guisignal.message(this, FXSEL(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSECTOR_IMG), NULL, NULL);
	}
	else if (m_EState == ST_DISC_COPY)
	{
		guisignal.message(this, FXSEL(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSECTOR_CPY), NULL, NULL);
	}

}

long KUtilitiesFOXLibDlg::onSetVerifySectorImg(FXObject* sender, FXSelector key, void* data)
{
	
	FXString strTemp;
	strTemp.format("%.0f / %.0f", m_progInfo.vcurrentsector, m_progInfo.sectors);
	m_lblSectorsImg->setText(strTemp);
	return 1;
}

long KUtilitiesFOXLibDlg::onSetVerifySectorCpy(FXObject* sender, FXSelector key, void* data)
{

	FXString strTemp;
	strTemp.format("%.0f / %.0f", m_progInfo.vcurrentsector, m_progInfo.sectors);
	m_lblVerifySectors->setText(strTemp);
	return 1;
}
//Start Verify
void KUtilitiesFOXLibDlg::OnStartVerifyEvent(KUtilitiesFOXLibDlg *pDlg)
{
	pDlg->SetVerifyStart();
}

void KUtilitiesFOXLibDlg::SetVerifyStart()
{
	if (m_EState == ST_IMAGE_CREATION)
	{
		guisignal.message(this, FXSEL(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSTART_IMG), NULL, NULL);
	}
	else if (m_EState == ST_DISC_COPY)
	{
		guisignal.message(this, FXSEL(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYSTART_CPY), NULL, NULL);
	}


}

long KUtilitiesFOXLibDlg::onSetVerifyStartImg(FXObject* sender, FXSelector key, void* data)
{
	m_lbStateImg->setText("Verify");
	return 1;
}

long KUtilitiesFOXLibDlg::onSetVerifyStartCpy(FXObject* sender, FXSelector key, void* data)
{
	m_lbljobState->setText("Verify");
	return 1;
}

//Verify Done
void KUtilitiesFOXLibDlg::OnVerifyDoneEvent(int nNumErrors, KUtilitiesFOXLibDlg *pDlg)
{
	pDlg->SetVerifyDone(nNumErrors);
}

void KUtilitiesFOXLibDlg::SetVerifyDone(int error)
{
	m_progInfo.errors  = error;

	if (m_EState == ST_IMAGE_CREATION)
	{
		guisignal.message(this, FXSEL(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYDONE_IMG), NULL, NULL);
	}
	else if (m_EState == ST_DISC_COPY)
	{
		guisignal.message(this, FXSEL(SEL_CHORE, KUtilitiesFOXLibDlg::ID_VERIFYDONE_CPY), NULL, NULL);
	}
}



long KUtilitiesFOXLibDlg::onSetVerifyDoneImg(FXObject* sender, FXSelector key, void* data)
{
	m_lbStateImg->setText("Done");

	if(m_progInfo.errors>0) {
		FXString strTemp;
		strTemp.format("Verify done. %d errors.", m_progInfo.errors);
		FXMessageBox msgBox(this, "Verify disc image", strTemp, NULL, MBOX_OK);
		msgBox.execute();
	}
	return 1;
}

long KUtilitiesFOXLibDlg::onSetVerifyDoneCpy(FXObject* sender, FXSelector key, void* data)
{
	m_lbljobState->setText("Done");

	if (m_progInfo.errors>0) {
		FXString strTemp;
		strTemp.format("Verify done. %d errors.", m_progInfo.errors);
		FXMessageBox msgBox(this, "Verify disc image", strTemp, NULL, MBOX_OK);
		msgBox.execute();
	}
	return 1;
}



void KUtilitiesFOXLibDlg::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dWritten, double dImageSize, KUtilitiesFOXLibDlg *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dImageSize, dWritten, (int)ceil(fDeviceBuffer * 1000));
}

void KUtilitiesFOXLibDlg::SetProgress(int progress, double size, double current, int errors)
{
	m_progInfo.progress = progress;
	m_progInfo.current = current;
	m_progInfo.size = size;
	m_progInfo.errors = errors;

	if (m_EState == ST_IMAGE_CREATION)
	{
		//getApp()->addChore(this, KUtilitiesFOXLibDlg::ID_SETPROGRESS_IMG, &m_progInfo);	
		guisignal.message(this,FXSEL(SEL_CHORE,KUtilitiesFOXLibDlg::ID_SETPROGRESS_IMG),NULL,NULL);
	}
	else if (m_EState == ST_DISC_COPY)
	{
		//getApp()->addChore(this, KUtilitiesFOXLibDlg::ID_SETPROGRESS_DSC, &m_progInfo);	
		guisignal.message(this,FXSEL(SEL_CHORE,KUtilitiesFOXLibDlg::ID_SETPROGRESS_DSC),NULL,NULL);
	}


}

long KUtilitiesFOXLibDlg::onSetProgressImg(FXObject* sender, FXSelector key, void* data)
{
	m_barProgressImg->setProgress(m_progInfo.progress);

	FXString strTemp;

	strTemp.format("%.0f", m_progInfo.size);
	m_lblTtlSectorsImg->setText(strTemp);

	strTemp.format("%d", m_progInfo.errors);
	m_lblReadErrorsImg->setText(strTemp);

	strTemp.format("%.0f", m_progInfo.current);
	m_lblCurrentSectorImg->setText(strTemp);

	strTemp.format("%d%%", m_progInfo.progress);
	m_lblPercentageImg->setText(strTemp);

	return 1;
}

long KUtilitiesFOXLibDlg::onSetProgressDsc(FXObject* sender, FXSelector key, void* data)
{
	m_barProgressDsc->setProgress(m_progInfo.progress);	

	FXString strTemp;

	strTemp.format("%.0f", m_progInfo.size);
	m_lblTtlBytesDsc->setText(strTemp);

	strTemp.format("%.0f", m_progInfo.current);
	m_lblBytesWrittenDsc->setText(strTemp);

	strTemp.format("%d%%", m_progInfo.progress);
	m_lblPercentageDsc->setText(strTemp);

	return 1;
}

long KUtilitiesFOXLibDlg::onSourceDeviceBoxChange(FXObject* sender, FXSelector key, void* data)
{
	m_cmbRModeDsc->clearItems();

	SMediumInfo cMediumInfo;
	int32 nRes = ::GetMediumInformation(m_cmbSourceDevDsc->getCurrentItem(), &cMediumInfo);
	handleError(nRes);

	if (nRes)
	{
		return 0;
	}

	m_cmbRModeDsc->appendItem("ISO");

	if (cMediumInfo.wMediumTypeCode == BS_CD_ROM ||
		cMediumInfo.wMediumTypeCode == BS_CD_R ||
		cMediumInfo.wMediumTypeCode == BS_CD_RW)
	{
		m_cmbRModeDsc->appendItem("RAW");
		m_cmbRModeDsc->appendItem("RAW+SubCh");		
	}
	
	m_cmbRModeDsc->setCurrentItem(0);

	SExtendedDeviceInformation sDeviceInfo;
	nRes = ::GetDeviceInformationEx(m_cmbSourceDevDsc->getCurrentItem(), &sDeviceInfo);
	handleError(nRes);

	m_spnHardwareDsc->setValue(sDeviceInfo.nReadRetryCount);

	return 1;
}

void KUtilitiesFOXLibDlg::UpdateSourceDeviceCombo()
{
	m_cmbSourceDevDsc->clearItems();

	// Get devices list

	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 nRes = ::GetDevices(chListDevices, &nUsed, BS_FALSE);
	handleError(nRes);

	// Get current device

	TCHAR pchDevice[50];
	int32 nLength = sizeof(pchDevice) / sizeof(TCHAR);
	int32 res = ::GetReadDevice(pchDevice, &nLength);
	handleError(res);



	// Add devices to combo box
	int cbCount = 0;
	for (int i = 0; i < nUsed; i++)
	{
		FXString strItem;
		strItem =(const wchar_t*)KString(chListDevices[i]);

		FXint itemIndex = m_cmbSourceDevDsc->appendItem(strItem);
	
		if (0 == _tcsncmp(pchDevice, chListDevices[i], 2))
		{
			m_cmbSourceDevDsc->setCurrentItem(i);
		}


		cbCount++;
	}

	m_cmbSourceDevDsc->setNumVisible(nUsed);

	onSourceDeviceBoxChange(this, 0, 0);
}

long KUtilitiesFOXLibDlg::onBtnImageBrowse(FXObject* sender, FXSelector key, void* data)
{
	FXString strFormat = m_cmbFormatImg->getText();
	
	FXString strPattern;
	strPattern.format("%s files (*.%s)", strFormat.text(), strFormat.text());

	FXFileDialog dlg(getApp(), "Select destination file");
	dlg.setSelectMode(SELECTFILE_ANY);
	dlg.setPatternList(strPattern);

	if (dlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(dlg.getDirectory());

		FXString strPath = FXString::compose(dlg.getFilename(), false);
		
		if (strPath.find(".") == -1)
		{
			strPath += "." + strFormat;
		}

		m_txtBrowseBoxImg->setText(strPath);		
	}

	return 1;
}

long KUtilitiesFOXLibDlg::onExecuteImageCreate(FXObject* sender, FXSelector key, void* data)
{
	m_EState = ST_IMAGE_CREATION;

	FXString strDest = m_txtBrowseBoxImg->getText();

	if (strDest == "")
	{
		FXMessageBox::error(this, MBOX_OK, "UtilitiesFOXLib", "Destination file is not specified.");
		return 0;
	}

	FXString strBadSectorsLogPath = m_txtSetorsListPathImg->getText();
	FXString strFormat = m_cmbFormatImg->getText();
	
	int16 nFormat;
	
	if (strFormat == _T("ISO"))
	{
		nFormat = BS_IMG_ISO;
		
		if (comparecase(strDest.right(3), _T("iso")))
		{
			strDest += _T(".iso");
		}
	}
	else if (strFormat == _T("BIN"))
	{
		nFormat = BS_IMG_BIN;
		if (comparecase(strDest.right(3), _T("bin")))
		{
			strDest += _T(".bin");
		}
	}
	else
	{
		return 0;
	}

	m_txtBrowseBoxImg->setText(strDest);
	

	FXFile file;

	if (file.open(strDest) && m_chbCreateImg->getCheck())
	{
		if (MBOX_CLICKED_NO == FXMessageBox::error(this, MBOX_YES_NO, "UtilitiesFOXLib", 
			"Destination file exists. Do you want to replace it?"))
			return 0;
	}

	SCreateImageParams cCreateImageParams;
	cCreateImageParams.cErrorParams.bErrorCorrection = m_chbErrorCorrectImg->getCheck();
	cCreateImageParams.cErrorParams.bBlankBadSectors = m_chbBlankBadImg->getCheck();
	_tcscpy(cCreateImageParams.lpszBadSectorsFilePath, Fox2SDKString(strBadSectorsLogPath));
	_tcscpy(cCreateImageParams.lpszImagePath, Fox2SDKString(strDest));
	cCreateImageParams.nImageType = nFormat;	
	cCreateImageParams.nVerifyBufferSectors = 8;
	cCreateImageParams.bFullCapacity = BS_TRUE;
	cCreateImageParams.cErrorParams.nHardwareRetryCount = m_spnHardwareImg->getValue();
	cCreateImageParams.cErrorParams.nSoftwareRetryCount = m_spnSoftwareImg->getValue();

	int8 dwOperation = 0;

	if (m_chbCreateImg->getCheck())
	{
		dwOperation = BS_IMGTASK_CREATE;
	}
	
	if (m_chbVerifyImg->getCheck())
	{
		dwOperation |= BS_IMGTASK_VERIFY;
	}
	
	if (!dwOperation)
	{
		FXMessageBox::error(this, MBOX_OK, "UtilitiesFOXLib", "Operation is not specified.");
		return 0;
	}

	if (!UpdateImageReadDevice())
	{
		return 1;
	}

	// Start image creation
	
	int32 nRes = ::CreateImage(cCreateImageParams, dwOperation);
	handleError(nRes);

	if (nRes == BS_SDK_ERROR_NO)
	{
		EnableControlsImg(false);
		m_lbStateImg->setText("Create");
	}

	return 1;
}

long KUtilitiesFOXLibDlg::onExecuteDiscCopy(FXObject* sender, FXSelector key, void* data)
{
	m_EState = ST_DISC_COPY;

	SDiskCopyOptions cDiskCopyOptions;
	cDiskCopyOptions.bVerifyAfterBurn = m_chbVerifyDsc->getCheck();
	cDiskCopyOptions.bEjectAfterBurn = m_chbEjectDsc->getCheck();
	
	FXString strMode = m_cmbRModeDsc->getText();

	if (strMode == "ISO")
	{
		cDiskCopyOptions.nReadMode = BS_RM_USERDATA;
	}
	else if (strMode == "RAW")
	{
		cDiskCopyOptions.nReadMode = BS_RM_RAW;
	}
	else if (strMode == "RAW+SubCh")
	{
		cDiskCopyOptions.nReadMode = BS_RM_RAW_SUBCHANNEL;
	}
	else
	{
		FXMessageBox::error(this, MBOX_OK,  "UtilitiesFOXLib", "Please, specify read mode.");
		return 0;
	}

	
	FXString strWrMethod = m_cmbWMethodDsc->getText();
	
	if (strWrMethod == "DAO")
	{
		cDiskCopyOptions.nWriteMethod = BS_WM_DAO;
	}
	else if (strWrMethod == "DAO96")
	{
		cDiskCopyOptions.nWriteMethod = BS_WM_DAO96;
	}
	else
	{
		
		FXMessageBox::error(this, MBOX_OK, "UtilitiesFOXLib", "Please, specify write method.");
		return 0;
	}
	
	SReadErrorCorrectionParams cCorrectionParams;
	cCorrectionParams.bErrorCorrection = m_chbErrorCorrectDsc->getCheck();
	cCorrectionParams.nHardwareRetryCount = m_spnHardwareDsc->getValue();
	cCorrectionParams.nSoftwareRetryCount = m_spnSoftwareDsc->getValue();

	cDiskCopyOptions.cErrorParams = cCorrectionParams;
	cDiskCopyOptions.bFullCapacity = BS_TRUE;
	cDiskCopyOptions.nVerifyBufferSectors = 8;

	FXString strSourceDevice = m_cmbSourceDevDsc->getText();

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 nRes = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	handleError(nRes);

	FXString strDeviceItem = chBurnDevices[0];
	if (strSourceDevice.left(2) == strDeviceItem.left(2))
	{
		FXMessageBox::error(this, MBOX_OK, "UtilitiesFOXLib", "Source and Destination devices cannot be the same.");
		return 0;
	}
	   
	SOptions opt;
	::GetOptions(&opt);
	opt.bAutoErase = m_chbAutoErase->getCheck();
	::SetOptions(opt);

	KString strDevice = Fox2SDKString(strSourceDevice);

	nRes = ::SetReadDevice(strDevice);
	handleError(nRes);




	

	if (nRes == BS_SDK_ERROR_NO)
	{
		nRes = ::CopyDisk(cDiskCopyOptions);
		handleError(nRes);

		m_lbljobState->setText("Copy");
	}

	if (nRes == BS_SDK_ERROR_NO)
	{
		EnableControlsDsc(false);
	}

	return 1;
}

void KUtilitiesFOXLibDlg::OnBurnDoneEvent(const TCHAR* pcError, KUtilitiesFOXLibDlg *pDlg) 
{
	pDlg->OnBurnDone(pcError);
}

void KUtilitiesFOXLibDlg::OnBurnDone(const TCHAR* pcError)
{
	m_strBurnError = pcError;

	if (m_EState == ST_IMAGE_CREATION)
	{
		//getApp()->addChore(this, KUtilitiesFOXLibDlg::ID_BURNDONE_IMG, 0);	
		guisignal.message(this,FXSEL(SEL_CHORE,KUtilitiesFOXLibDlg::ID_BURNDONE_IMG),NULL,NULL);
	}
	else if (m_EState == ST_DISC_COPY)
	{
		//getApp()->addChore(this, KUtilitiesFOXLibDlg::ID_BURNDONE_DSC, 0);	
		guisignal.message(this,FXSEL(SEL_CHORE,KUtilitiesFOXLibDlg::ID_BURNDONE_DSC),NULL,NULL);
	}


}

long KUtilitiesFOXLibDlg::onBurnDoneImg(FXObject* sender, FXSelector key, void* data)
{
	if (!m_strBurnError.empty()) 
	{
		FXMessageBox::error(this, MBOX_OK, "UtilitiesFOXLib", m_strBurnError.text());
	}

	return 1;
}

long KUtilitiesFOXLibDlg::onBurnDoneDsc(FXObject* sender, FXSelector key, void* data)
{
	if (!m_strBurnError.empty()) 
	{
		FXMessageBox::error(this, MBOX_OK, "UtilitiesFOXLib", m_strBurnError.text(), NULL,  MBOX_OK);
	}

	return 1;
}

bool KUtilitiesFOXLibDlg::UpdateImageReadDevice()
{
	// Get current burn device

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);

	if (res != BS_SDK_ERROR_NO)
	{
		handleError(res);
		return false;
	}
	if (nBurnDevices > 1)
	{
		handleError(BS_SDK_ERROR_NOT_ALLOWED);
		return false;
	}
	res = ::SetReadDevice(chBurnDevices[0]);
	if (res != BS_SDK_ERROR_NO)
	{
		handleError(res);
		return false;
	}






	// Multidevice is not allowed



	// Set current read device to current burn device

	return true;
}


void KUtilitiesFOXLibDlg::EnableControlsImg(bool bEnable)
{
	if (bEnable)
	{
		m_btnAbortImg->disable();
		m_btnExecuteImg->enable();
		m_txtBrowseBoxImg->enable();
		m_btnBrowseDestImg->enable();
		m_chbErrorCorrectImg->enable();
		m_spnHardwareImg->enable();
		m_spnSoftwareImg->enable();
		m_chbBlankBadImg->enable();
		m_chbBadSectListImg->enable();
		m_txtSetorsListPathImg->enable();
		m_cmbFormatImg->enable();
		m_btnCheckFormatImg->enable();
		m_chbCreateImg->enable();
		m_chbVerifyImg->enable();
	}
	else
	{
		m_btnAbortImg->enable();
		m_btnExecuteImg->disable();
		m_txtBrowseBoxImg->disable();
		m_btnBrowseDestImg->disable();
		m_chbErrorCorrectImg->disable();
		m_spnHardwareImg->disable();
		m_spnSoftwareImg->disable();
		m_chbBlankBadImg->disable();
		m_chbBadSectListImg->disable();
		m_txtSetorsListPathImg->disable();
		m_cmbFormatImg->disable();
		m_btnCheckFormatImg->disable();
		m_chbCreateImg->disable();
		m_chbVerifyImg->disable();
	}
}

void KUtilitiesFOXLibDlg::EnableControlsDsc(bool bEnable)
{
	if (bEnable)
	{
		m_btnAbortDsc->disable();
		m_btnExecuteDsc->enable();
		m_cmbSourceDevDsc->enable();
		m_cmbWMethodDsc->enable();
		m_cmbRModeDsc->enable();
		m_chbVerifyDsc->enable();
		m_chbAutoErase->enable();
		m_chbEjectDsc->enable();
		m_chbErrorCorrectDsc->enable();
		m_spnHardwareDsc->enable();
		m_spnSoftwareDsc->enable();
	}
	else
	{
		m_btnAbortDsc->enable();
		m_btnExecuteDsc->disable();
		m_cmbSourceDevDsc->disable();
		m_cmbWMethodDsc->disable();
		m_cmbRModeDsc->disable();
		m_chbVerifyDsc->disable();
		m_chbAutoErase->disable();
		m_chbEjectDsc->disable();
		m_chbErrorCorrectDsc->disable();
		m_spnHardwareDsc->disable();
		m_spnSoftwareDsc->disable();
	}
}

long KUtilitiesFOXLibDlg::onMountImage(FXObject* sender, FXSelector key, void* data)
{
	const FXchar patterns[]= "All Supported (*.iso,*.bin,*.nrg,*.cdi,*.mdf,*.ccd,*.img,*.gi, *.pdi, *.dmg, *.b5i, *.b6i)";

	FXFileDialog fileDlg(this, "Select Image File");
	fileDlg.setPatternList(patterns);
	fileDlg.setSelectMode(SELECTFILE_ANY);

	if (fileDlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(fileDlg.getDirectory());
		FXString filename = FXString::compose(fileDlg.getFilename(), false);
		
		KString strTmpName = Fox2SDKString(filename);

		int32 res = ::SetImageFilePath(strTmpName);
		handleError(res);

		FXint indx = m_cmbDevice->getCurrentItem();

		if (-1 < indx)
		{
			FXString strItem = m_cmbDevice->getItemText(indx);
			KString strDevice = Fox2SDKString(strItem.left(1));

			if (strDevice == '#')
			{
				onDeviceBoxChange(sender, key, data);
			}
		}

		return (res == BS_SDK_ERROR_NO) ? 1 : 0;
	}
	else
	{
		return 0;
	}
}

long KUtilitiesFOXLibDlg::onUnmountImage(FXObject* sender, FXSelector key, void* data)
{
	::SetImageFilePath(NULL);

	FXint indx = m_cmbDevice->getCurrentItem();

	if (-1 < indx)
	{
		FXString strItem = m_cmbDevice->getItemText(indx);
		KString strDevice = Fox2SDKString(strItem.left(1));

		if (strDevice == '#')
		{
			onDeviceBoxChange(sender, key, data);
		}
	}

	return 1;
}

void KUtilitiesFOXLibDlg::UpdateDriveInfo()
{
	int32 nError = 0;

	// Get disk type

	SMediumInfo mi;
	nError = ::GetMediumInformation(BS_CURRENT_DEVICE, &mi);

	if (_tcscmp(mi.chMediumType, _T("BS_NDEF")) == 0)
		m_lblDiskType->setText("No Medium");
	else
		m_lblDiskType->setText(mi.chMediumType);

	// Get max. burn speed

	int32 nSpeed = 0;
	nError = ::GetMaxBurnSpeed(BS_CURRENT_DEVICE, &nSpeed);
	handleError(nError);
	m_lblMaxBurnSpeed->setText(IntToStr(nSpeed));

	// Get max. read speed

	nError = ::GetMaxReadSpeed(BS_CURRENT_DEVICE, &nSpeed);
	handleError(nError);
	m_lblMaxReadSpeed->setText(IntToStr(nSpeed));

	// Get capabilities
	/**/

	//Create a handle
	int32 nCapsHandle;
 
	//Set the handle
	nError = GetDeviceCapabilitiesHandle(BS_CURRENT_DEVICE, &nCapsHandle);
	handleError(nError);

	if(nError != BS_SDK_ERROR_NO)
		return;

	BS_BOOL bRes = false;
	nError = AnalyseDeviceCapability(nCapsHandle, BS_WRITE_TEST, &bRes);
	handleError(nError);

	if (bRes == BS_TRUE)
		m_lblTestWrite->setText("Supported");
	else
		m_lblTestWrite->setText("Not supported");

	bRes = BS_FALSE;
	nError = AnalyseDeviceCapability(nCapsHandle, BS_UNDERRUN_PROTECTION, &bRes);
	handleError(nError);

	if (bRes == BS_TRUE)
		m_lblUnderrunProtection->setText("Supported");
	else
		m_lblUnderrunProtection->setText("Not supported");

	nError = ReleaseDeviceCapabilities(nCapsHandle);
	handleError(nError);
}

void KUtilitiesFOXLibDlg::UpdateDriveInfoEx()
{
	m_lstInfoEx->clearItems();

	SExtendedDeviceInformation	infoEx;
	if (::GetDeviceInformationEx(BS_CURRENT_DEVICE, &infoEx) == BS_SDK_ERROR_NO)
	{
		m_lstInfoEx->appendItem("Full name of device\t" + FXString(infoEx.lpszName));
		m_lstInfoEx->appendItem("Firmware revision\t" + FXString(infoEx.lpszRevision));

		FXString strFirmwareCreationDate = "Unknown";
		if (infoEx.FirmwareCreationDate != 0)
		{
			tm *tmFirmwareCreationDate = localtime(&infoEx.FirmwareCreationDate);
			char szFirmwareCreationDate[20];
			strftime(szFirmwareCreationDate, sizeof(szFirmwareCreationDate), "%c", tmFirmwareCreationDate);
			strFirmwareCreationDate = szFirmwareCreationDate;
		}
		m_lstInfoEx->appendItem("Firmware creation date\t" + strFirmwareCreationDate);

		m_lstInfoEx->appendItem("Region code set\t" + IntToStr(infoEx.nRegionCode));
		m_lstInfoEx->appendItem("Region code changes left\t" + IntToStr(infoEx.nRegionCodeChangesLeft));
		m_lstInfoEx->appendItem("Region code vendor resets left\t" + IntToStr(infoEx.nRegionCodeVendorResetsLeft));
		m_lstInfoEx->appendItem("Loader type\t" + FXString(infoEx.lpszLoaderType));
		m_lstInfoEx->appendItem("Connection interface\t" + FXString(infoEx.lpszConnectionInterface));
		m_lstInfoEx->appendItem("Drive interface\t" + FXString(infoEx.lpszPhysicalInterface));
		m_lstInfoEx->appendItem("Number of volume levels\t" + IntToStr(infoEx.nNumberOfVolumeLevels));
		m_lstInfoEx->appendItem("Buffer size\t" + IntToStr(infoEx.nBufferSize));
		m_lstInfoEx->appendItem("Serial number\t" + FXString(infoEx.lpszSerialNumber));
		m_lstInfoEx->appendItem("Read retry count\t" + IntToStr(infoEx.nReadRetryCount));
	}
}

void KUtilitiesFOXLibDlg::UpdateDriveCapabilities()
{
	int32 nCapsHandle;

	int32 nErr = ::GetDeviceCapabilitiesHandle(BS_CURRENT_DEVICE, &nCapsHandle);
	handleError(nErr);

	if (nErr != BS_SDK_ERROR_NO)
		return;

	CapsMap::iterator it = m_mCaps.begin(), itEnd = m_mCaps.end();

	for(; it != itEnd ; ++it)
	{
		BS_BOOL bRes;
		
		nErr = ::AnalyseDeviceCapability(nCapsHandle, it->first, &bRes);
		
		handleError(nErr);
		if (nErr != BS_SDK_ERROR_NO)
			return;

		it->second->setCheck(bRes ? true : false);
	}

	nErr = ::ReleaseDeviceCapabilities(nCapsHandle);
	handleError(nErr);
}

void KUtilitiesFOXLibDlg::UpdateMediumInfo()
{
	// Clear all controls

	m_btnCloseSession->disable();
	m_lstSessions->clearItems();

	m_lblMedium->setText("...");
	m_lblMediumStatus->setText("...");
	m_lblLastSession->setText("...");
	m_lblMediumSize->setText("...");
	m_lblMediumUsed->setText("...");
	m_lblMediumFree->setText("...");
	m_lblMediumCatalogCode->setText("...");
	m_lblMediumSessions->setText("...");
	m_lblMediumTracks->setText("...");
	m_lblMediumVendorID->setText("...");
	m_lblMediumMaxWriteSpeed->setText("...");

	// Get medium information

	SMediumInfo mi;
	int32 nError = ::GetMediumInformation(BS_CURRENT_DEVICE, &mi);

	if (_tcscmp(mi.chMediumType, _T("BS_NDEF")) == 0)
	{
		m_lblMedium->setText("No medium");
		return;
	}

	m_lblMedium->setText(mi.chMediumType);
	m_lblMediumCatalogCode->setText(mi.chUPCEANCode);
	m_lblMediumSessions->setText(IntToStr(mi.nLastSession));
	m_lblMediumTracks->setText(IntToStr(mi.nLastTrack));
	m_lblMediumVendorID->setText(mi.chVendorID);

	const double MEGABYTE = 1024.0 * 1024.0;

	switch (mi.nMediumStatus) {

		case BS_MS_EMPTY_DISK:
			m_lblMediumUsed->setText(RealToStr(mi.dMediumUsedSize / MEGABYTE) + " MB");
			m_lblMediumFree->setText(RealToStr(mi.dMediumFreeSize / MEGABYTE) + " MB");
			m_lblMediumSize->setText(RealToStr(mi.dMediumSize / MEGABYTE) + " MB");
			m_lblMediumStatus->setText("Empty disk");
			break;

		case BS_MS_INCOMPLETE_DISK:
			m_lblMediumUsed->setText(RealToStr(mi.dMediumUsedSize / MEGABYTE) + " MB");
			m_lblMediumFree->setText(RealToStr(mi.dMediumFreeSize / MEGABYTE) + " MB");
			m_lblMediumSize->setText(RealToStr(mi.dMediumSize / MEGABYTE) + " MB");
			m_lblMediumStatus->setText("Incomplete disk");
			break;
		case BS_MS_COMPLETE_DISK:
			m_lblMediumSize->setText(RealToStr(mi.dMediumSize / MEGABYTE) + " MB");
			m_lblMediumUsed->setText(RealToStr(mi.dMediumUsedSize / MEGABYTE) + " MB");
			m_lblMediumStatus->setText("Complete disk");
	}

	switch (mi.nLastSessionStatus)
	{
		case BS_LS_EMPTY_SESSION:
			m_lblLastSession->setText("Empty session");
			break;

		case BS_LS_INCOMPLETE_SESSION:
			m_lblLastSession->setText("Incomplete session");
			m_btnCloseSession->enable();
			break;

		case BS_LS_DAMAGED_SESSION:
			m_lblLastSession->setText("Damaged session");
			m_btnCloseSession->enable();
			break;

		case BS_LS_COMPLETE_SESSION:
			m_lblLastSession->setText("Complete session");
			break;
	}

	FXString strMaxWriteSpeed = "Unknown";
	if (mi.fMaxWriteSpeed > 0)
		strMaxWriteSpeed.format("%.1fx", mi.fMaxWriteSpeed);
	m_lblMediumMaxWriteSpeed->setText(strMaxWriteSpeed);

	FXString strExtDiskType;
	switch(mi.nExtendedMediumType)
	{
	case BS_EMT_CD_ROM:		strExtDiskType = "CD-ROM"; break;
	case BS_EMT_CD_ROM_XA:	strExtDiskType = "CD-ROM XA"; break;
	case BS_EMT_CD_AUDIO:   strExtDiskType = "Audio CD"; break;
	case BS_EMT_CD_MIXED_MODE: strExtDiskType = "Mixed Mode CD"; break;
	case BS_EMT_CD_ENHANCED: strExtDiskType = "Enhanced CD"; break;
	case BS_EMT_CD_MULTISESSION: strExtDiskType = "Multisession CD"; break;
	case BS_EMT_DVD: strExtDiskType = "DVD"; break;
	case BS_EMT_BD: strExtDiskType = "BD"; break;
	case BS_EMT_HDDVD: strExtDiskType = "HDDVD"; break;
	default: break;
	}

	if (mi.nFirstSession > 0 && mi.nLastSession > 0)
	{
		FXTreeItem* diskItem = m_lstSessions->appendItem(NULL, strExtDiskType);

		for (int32 i = mi.nFirstSession; i <= mi.nLastSession; i++)
		{
			SSessionInfo si;
			nError = ::GetSessionInformation(BS_CURRENT_DEVICE, i, &si);
			handleError(nError);

			double dSessionSizeInMB = (si.dSessionSize * 2048.0)/MEGABYTE;

			FXString strSession = "Session " + IntToStr(i) + " (" + RealToStr(dSessionSizeInMB) + " MB)";
			FXTreeItem* sessionItem = m_lstSessions->appendItem(diskItem, strSession);

			for(int32 j = si.nFirstTrack; j <= si.nLastTrack; ++j)
			{
				STrackInfo ti;
				nError = ::GetTrackInformation(BS_CURRENT_DEVICE, j, &ti);
				handleError(nError);

				FXString strTrackFormat;
				switch(ti.nFormat)
				{
				case BS_TF_AUDIO: strTrackFormat = "Audio"; break;
				case BS_TF_DATA_MODE1: strTrackFormat = "mode 1"; break;
				case BS_TF_DATA_MODE2: strTrackFormat = "mode 2"; break;
				}

				FXString strFileSys;

				if (ti.nFormat != BS_TF_AUDIO)
				{
					if (ti.nFileSystem & BS_FS_ISO9660)
					{
						strFileSys += "ISO 9660";
						if (ti.nFileSystem & BS_FS_JOLIET)
							strFileSys += "/Joliet";
					}

					if (ti.nFileSystem & BS_FS_UDF)
					{
						if (strFileSys.length())
							strFileSys += "/";
						strFileSys += "UDF";
					}

					if (ti.nFileSystem & BS_FS_BOOTABLE)
						strFileSys += "/bootable";
				}

				FXString strTrack = "Track " + IntToStr(j) + "  " + IntToStr(ti.nStartLBA) +
					"  (" + RealToStr((ti.nSize*2048.0)/MEGABYTE) + "MB) " + strFileSys + " " + strTrackFormat;
				m_lstSessions->appendItem(sessionItem, strTrack);
			}

			m_lstSessions->expandTree(sessionItem);
		}

		m_lstSessions->expandTree(diskItem);
	}
}
