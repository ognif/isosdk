#include "stdafx.h"
#include "VideoFOXLibDlg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "../Common/AboutDlg.h"
#include "../Common/SampleBurnDlg.h"
#include "../Common/Rule.h"
#include "../Common/CommonFoxLib.h"
#include <algorithm>

#define WEBSITELINK			"http://www.isosdk.com"

#ifdef min
#undef min
#endif

struct FileItemData
{
	FileItemData(size_t _nSize)
		:nSize(_nSize)
	{
	}

	size_t nSize;
};

void OnVideoScannerEvent(float fPercent,const TCHAR *pcFileName, KVideoScanDlg* pDlg)
{
	pDlg->OnVideoScannerEvent(fPercent);
}

void OnVideoScanDoneEvent(const TCHAR *pcFileName, const TCHAR *pcError, int32 nErrorCode, struct SVideoFormat CurrentFormat, KVideoScanDlg* pDlg)
{
	FXString strError = (const wchar_t*)KString(pcError);

	pDlg->OnVideoScanDoneEvent(strError, nErrorCode, CurrentFormat);
}

FXDEFMAP(KVideoFOXLibDlg) KVideoFOXLibMap[]= {
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_ADDVIDEOFILE, KVideoFOXLibDlg::onAddFile),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_ADDPICTUREFILE, KVideoFOXLibDlg::onAddFile),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_WRITELOG, KVideoFOXLibDlg::onWriteLogFile),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_DELETEITEM, KVideoFOXLibDlg::onDeleteItem),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_RESETLIST, KVideoFOXLibDlg::onResetList),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_BURNDISK_DEVELOPED, KVideoFOXLibDlg::onBurnDiskDeveloped),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_BURNDISK_FOXBURNER, KVideoFOXLibDlg::onBurnDiskFoxBurner),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_ERASEDISK, KVideoFOXLibDlg::onEraseDisk),
	FXMAPFUNCS(SEL_COMMAND,KVideoFOXLibDlg::ID_ASPI_INTERNAL, KVideoFOXLibDlg::ID_ASPI_FROGASPI, KVideoFOXLibDlg::onCmdAspi),
	FXMAPFUNCS(SEL_UPDATE, KVideoFOXLibDlg::ID_ASPI_INTERNAL, KVideoFOXLibDlg::ID_ASPI_FROGASPI, KVideoFOXLibDlg::onUpdAspi),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_RESCANDEVICES, KVideoFOXLibDlg::onRescanDevices),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_BURNDEVICES, KVideoFOXLibDlg::onBurningDevices),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_DISABLEIMAGE, KVideoFOXLibDlg::onDisableImagewriter),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_ABOUT, KVideoFOXLibDlg::onAbout),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_WEB, KVideoFOXLibDlg::onWeb),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_DEVICEBOX, KVideoFOXLibDlg::onDeviceBoxChange),
	FXMAPFUNC(SEL_COMMAND, KVideoFOXLibDlg::ID_PROJECTTYPE, KVideoFOXLibDlg::onProjectTypeChange),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, FXDialogBox::onCmdCancel),
	FXMAPFUNC(SEL_CLOSE, 0, FXDialogBox::onCmdCancel)
};

FXIMPLEMENT(KVideoFOXLibDlg, FXDialogBox, KVideoFOXLibMap, ARRAYNUMBER(KVideoFOXLibMap))

KVideoFOXLibDlg::KVideoFOXLibDlg()
	: m_dlgVideoScan(getApp(), "Video scan progress")
{
}

FXIconList* createIconList(FXComposite* parent, FXObject* tgt, FXSelector sel)
{
	FXIconList* list = new FXIconList(parent, tgt, sel,
		LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_THICK|ICONLIST_DETAILED|ICONLIST_EXTENDEDSELECT);

	list->appendHeader("Name", NULL, 200);
	list->appendHeader("Size", NULL, 60);
	list->appendHeader("Length", NULL, 60);
	list->appendHeader("Modified Date", NULL, 100);
	list->appendHeader("Framerate", NULL, 100);
	list->appendHeader("Bitrate", NULL, 100);
	list->appendHeader("Aspect Ratio", NULL, 100);
	list->appendHeader("Dimensions", NULL, 100);

	return list;
}

KVideoFOXLibDlg::KVideoFOXLibDlg(FXApp *app, const FXString &title)
	: FXDialogBox(app, title, DECOR_ALL, 0, 0, 600, 500, 0, 0, 0, 0, 0, 0)
	, m_dlgVideoScan(app, "Video scan progress")
	, m_bBurningDevicesOnly(true)
{


	// Load icons for menu
	FXIcon *icoAdd = new FXICOIcon(getApp(), addvideo);
	FXIcon *icoDelete = new FXICOIcon(getApp(), delvideo);
	FXIcon *icoReset = new FXICOIcon(getApp(), reset);
	FXIcon *eraseIcon = new FXICOIcon(getApp(), cd_erase);
	FXIcon *cancelIcon = new FXICOIcon(getApp(), cancel);
	FXIcon *burnIcon = new FXICOIcon(getApp(), burn_iso);
	FXIcon *refreshIcon = new FXICOIcon(getApp(), refresh2);
	FXIcon *isosdkIconSmall = new FXICOIcon(getApp(), isosdksmall);
	FXIcon *isosdkIconBig = new FXICOIcon(getApp(), isosdkbig);

	///////////////////////////////////////////////////////////////////
	// Create menu bar

	FXMenuBar *menubar = new FXMenuBar(this, LAYOUT_FILL_X);
	//new FXHorizontalSeparator(this, LAYOUT_FILL_X|SEPARATOR_GROOVE);

	FXMenuPane *filemenu = new FXMenuPane(this);
		new FXMenuCommand(filemenu,"&Add Video File...", icoAdd, this, ID_ADDVIDEOFILE);
		new FXMenuCommand(filemenu,"Add &Picture File...", icoAdd, this, ID_ADDPICTUREFILE);
		new FXMenuCommand(filemenu,"&Delete selected", icoDelete, this, ID_DELETEITEM);
		new FXMenuCommand(filemenu,"&Reset", icoReset, this, ID_RESETLIST);
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"Write Log", NULL, this, ID_WRITELOG);
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"E&xit", cancelIcon, this, FXDialogBox::ID_CANCEL);
	new FXMenuTitle(menubar, "&File", NULL, filemenu);

	FXMenuPane *burnmenu = new FXMenuPane(this);
		new FXMenuCommand(burnmenu,"&Burn with custom dialog...", burnIcon, this, ID_BURNDISK_DEVELOPED);
		new FXMenuCommand(burnmenu,"Burn with &IsoSDK Embedded Dialog...", burnIcon, this, ID_BURNDISK_FOXBURNER);
		new FXMenuCommand(burnmenu,"&Erase Disk...", eraseIcon, this, ID_ERASEDISK);
		new FXHorizontalSeparator(burnmenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		FXMenuPane *optionsmenu = new FXMenuPane(this);
			new FXMenuCheck(optionsmenu,"&Eject Disk", &m_tgtEjectAfterBurn, FXDataTarget::ID_VALUE);
			new FXMenuCheck(optionsmenu,"&Joliet File System", &m_tgtJoliet, FXDataTarget::ID_VALUE);
		new FXMenuCascade(burnmenu, "&Options", NULL, optionsmenu);
	new FXMenuTitle(menubar, "&Burn", NULL, burnmenu);

	FXMenuPane* aspimenu = new FXMenuPane(this);
		FXMenuPane* interfacemenu = new FXMenuPane(this);
			new FXMenuRadio(interfacemenu, "&Internal", this, ID_ASPI_INTERNAL);
			new FXMenuRadio(interfacemenu, "&WnAspi", this, ID_ASPI_WNASPI);
			new FXMenuRadio(interfacemenu, "&FrogAspi", this, ID_ASPI_FROGASPI);
		new FXMenuCascade(aspimenu, "&Interface", NULL, interfacemenu);
		new FXMenuCommand(aspimenu,"&Rescan Devices", refreshIcon, this, ID_RESCANDEVICES);
		burnDevicesOnly = new FXMenuCheck(aspimenu,"&Burn devices only", this, ID_BURNDEVICES);
		new FXMenuCheck(aspimenu,"Disable &Imagewriter", this, ID_DISABLEIMAGE);
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

	FXHorizontalFrame* projectFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X);
		new FXLabel(projectFrame, "Project type: ", NULL, JUSTIFY_LEFT|LAYOUT_FIX_WIDTH, 0, 0, 70);
		m_cmbProjectType = new FXComboBox(projectFrame, 10, this, ID_PROJECTTYPE, FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
		m_cmbProjectType->appendItem("VCD", (void*)BS_BURNER_VCD);
		m_cmbProjectType->appendItem("SVCD", (void*)BS_BURNER_SVCD);
		m_cmbProjectType->setNumVisible(m_cmbProjectType->getNumItems());

	// Capacity rule
	m_rule = new KCDCapacityRule(this, CAPACITYRULE_CD|FRAME_THICK|LAYOUT_BOTTOM|LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|LAYOUT_FIX_HEIGHT, 0, 0, 0, 30);


		
	// Document icon
	m_miniDoc = new FXGIFIcon(getApp(), minidoc);
	m_miniDoc->create();

	setMiniIcon(isosdkIconSmall);
	setIcon(isosdkIconBig);



	m_strStartupDir = FXSystem::getCurrentDirectory();
}

//--------------------------------------------------------------
// First Load and build Class then load SDK settings to the app
// to make sure that the Fox-Toolkit is initialized the right way.
//--------------------------------------------------------------
void KVideoFOXLibDlg::loadOwner()
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

	// File tree pane
	m_tabBook = new FXTabBook(this, NULL, 0, TABBOOK_NORMAL | LAYOUT_FILL_X | LAYOUT_FILL_Y);
	new FXTabItem(m_tabBook, "Video");
	m_videoFileList = createIconList(m_tabBook, this, ID_VIDEOFILELIST);
	new FXTabItem(m_tabBook, "Pictures");
	m_pictureFileList = createIconList(m_tabBook, this, ID_PICTUREFILELIST);

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------
	SetVideoScannerEventCallback((VideoScannerEvent)OnVideoScannerEvent, &m_dlgVideoScan);
	SetVideoScanDoneEventCallback((VideoScanDoneEvent)OnVideoScanDoneEvent, &m_dlgVideoScan);

	//--------------------------------------------------
	//We need to set a project. So we set default project first
	//--------------------------------------------------

	res = CreateProject(BS_BURNER_VCD, BS_CONTINUE_NO_SESSION);
	handleError(res);

	//--------------------------------------------------
	//Set the Options. Remember, not all Options are
	//aviable on all projects. Read Help
	//--------------------------------------------------

	SOptions opt;

	res = GetOptions(&opt);
	handleError(res);

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));

	m_bEjectAfterBurn = opt.bEjectAfterBurn;
	m_bJoliet = opt.bJolietFileSystem;

	m_tgtEjectAfterBurn.connect(m_bEjectAfterBurn);
	m_tgtJoliet.connect(m_bJoliet);

	res = SetOptions(opt);
	handleError(res);

	//--------------------------------------------------
	//Fill Devicelist and Select
	//--------------------------------------------------

	updateDeviceCombo();
}

KVideoFOXLibDlg::~KVideoFOXLibDlg()
{
	::DeInitialize();
}

long KVideoFOXLibDlg::onWriteLogFile(FXObject* sender, FXSelector key, void* data)
{
	::SaveLogToFile(KString(m_strStartupDir.text()) + PATHSEPSTRING + "FoxSampleVideoC.log");
	return 1;
}


long KVideoFOXLibDlg::onAddFile(FXObject* sender, FXSelector key, void* data)
{
	const FXchar patterns[]= "MPEG files (*.mpg)";

	FXFileDialog dlg(getApp(), "Select MPEG file");
	dlg.setSelectMode(SELECTFILE_EXISTING);
	dlg.setPatternList(patterns);

	const bool bPicture = (FXSELID(key) == ID_ADDPICTUREFILE);

	if (dlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(dlg.getDirectory());
		FXString strPath = FXString::compose(dlg.getFilename(), false);
		KString strTmpPath = Fox2SDKString(strPath);

		struct stat statbuf;
		int res = stat((const char*)strTmpPath, &statbuf);

		if (0 == res)
		{
			FXString strName = FXPath::name(strPath);
			KString strTmpName = Fox2SDKString(strName);

			SFileToAdd file;
				file.lpszFileName = strTmpName;
				file.lpszSourceFilePath = strTmpPath;
				if (bPicture)
					file.lpszDestinationPath = _T(PATHSEPSTRING) _T("SEGMENT");
				else
					file.lpszDestinationPath = _T(PATHSEPSTRING);

				file.bVideoFile = BS_TRUE;
				file.nSavePath = BS_DONT_SAVE_PATH;

			m_dlgVideoScan.m_fileToAdd = file;

			if (res == BS_SDK_ERROR_NO)
			{
				if (m_dlgVideoScan.execute(PLACEMENT_OWNER))
				{
					FXlong size = statbuf.st_size;
					FXString strSize;

					if (size > 1024*1024) {
						size = size / (1024*1024);
						strSize.format("%d MB", size);
					} else {
						strSize.format("%d bytes", size);
					}

					FXString strDate;
					struct tm *time = localtime(&statbuf.st_mtime);

					strDate.format("%02d.%02d.%04d %02d:%02d:%02d",
								time->tm_mday,
								time->tm_mon+1,
								time->tm_year + 1900,
								time->tm_hour,
								time->tm_min,
								time->tm_sec);

					FXString strItem = strName + '\t' +
										strSize + '\t' +
										m_dlgVideoScan.m_strPlaytime + '\t' +
										strDate + '\t' +
										m_dlgVideoScan.m_strFrameRate + '\t' +
										m_dlgVideoScan.m_strBitrate + '\t' +
										m_dlgVideoScan.m_strAspectRatio + '\t' +
										m_dlgVideoScan.m_strDimensions;

					FileItemData* itemData = new FileItemData(statbuf.st_size);
					FXIconList* list = (bPicture ? m_pictureFileList : m_videoFileList);

					list->appendItem(strItem, m_miniDoc, m_miniDoc, itemData);
					m_rule->SetSizeValue(m_rule->GetSizeValue() + statbuf.st_size);

					m_tabBook->setCurrent(bPicture ? 1 : 0);
				}
			}
		}
	}

	return 1;
}

long KVideoFOXLibDlg::onDeleteItem(FXObject* sender, FXSelector key, void* data)
{
	// Delete video or picture?
	bool bVideo = m_tabBook->getCurrent() == 0;

	// Get current icon list
	FXIconList* list = bVideo ? m_videoFileList : m_pictureFileList;

	int32 indx = list->getCurrentItem();

	if (-1 < indx) {
		// Calculate item number to delete
		int32 itemIndex = bVideo 
			? BS_VCD_TRACK_ITEM_0 + indx
			: BS_VCD_SEGMENT_ITEM_0 + indx;

		int32 res = ::EraseMpegByIndex(itemIndex);
		handleError(res);

		if (BS_SDK_ERROR_NO == res)
		{
			FileItemData* itemData = (FileItemData*)list->getItemData(indx);
			list->removeItem(indx);
			m_rule->SetSizeValue(m_rule->GetSizeValue() - itemData->nSize);
			delete itemData;
		}
	}

	return 1;
}

long KVideoFOXLibDlg::onResetList(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::ClearAll();
	handleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		m_videoFileList->clearItems();
		m_pictureFileList->clearItems();
		m_rule->SetSizeValue(0);
	}

	return 1;
}

long KVideoFOXLibDlg::onDeviceBoxChange(FXObject* sender, FXSelector key, void* data)
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

	return 1;
}

long KVideoFOXLibDlg::onEraseDisk(FXObject* sender, FXSelector key, void* data)
{	
	CALL_FXDIALOG_HANDLE_ERROR(::EraseDialog(_T("IsoSDK")));

	updateDeviceCombo();

	return 1;
}

int32 KVideoFOXLibDlg::updateOptions()
{
	SOptions opt;

	int32 res = GetOptions(&opt);
	handleError(res);

	_tcscpy(opt.chVolumeLabel, _T("VideoFOXLib"));

	opt.bEjectAfterBurn = m_bEjectAfterBurn;
	opt.bJolietFileSystem = m_bJoliet;

	res = SetOptions(opt);
	handleError(res);
	return res;
}

void KVideoFOXLibDlg::prepareMenus()
{
	if (m_pictureFileList->getNumItems() > 0)
	{
		// 1st case : we have pictures

		// create key 1..N handlers
		int numPictureHandlers = std::min(m_pictureFileList->getNumItems() - 1, 99);
		int numVideoHandlers = std::min(m_videoFileList->getNumItems(), 99 - numPictureHandlers);

		// set numeric key handler for menu picture
		for(int i = 0; i < numPictureHandlers; ++i)
		{
			::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0, BS_VCD_KEY_0 + i + 1, BS_VCD_SEGMENT_ITEM_0 + i + 1);
		}

		for(int i = 0; i < numVideoHandlers; ++i)
		{
			::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0, BS_VCD_KEY_0 + numPictureHandlers + i + 1, BS_VCD_TRACK_ITEM_0 + i);
		}

		for(int i = 0; i < m_pictureFileList->getNumItems(); ++i)
		{
			// set timeout for all pictures except last picture
			if (i != m_pictureFileList->getNumItems() - 1)
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
		if (m_videoFileList->getNumItems() != 0)
		{
			::SetVCDTimeOutHandler(BS_VCD_SEGMENT_ITEM_0 + m_pictureFileList->getNumItems() - 1, 
								10, BS_VCD_TRACK_ITEM_0);

			::SetVCDKeyHandler(BS_VCD_SEGMENT_ITEM_0 + m_pictureFileList->getNumItems() - 1, 
								BS_VCD_KEY_NEXT, BS_VCD_TRACK_ITEM_0);

			::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0, BS_VCD_KEY_PREVIOUS, 
								BS_VCD_SEGMENT_ITEM_0 + m_pictureFileList->getNumItems() - 1);
		}

		// create prev-next handlers
		for(int i = 0; i < m_videoFileList->getNumItems(); ++i)
		{
			if (i != m_videoFileList->getNumItems() - 1)
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
		for(int i = 0; i < m_videoFileList->getNumItems(); ++i)
		{
			if (i != 0)
				::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0 + i, BS_VCD_KEY_PREVIOUS, BS_VCD_TRACK_ITEM_0 + i - 1);

			if (i != m_videoFileList->getNumItems() -1)
				::SetVCDKeyHandler(BS_VCD_TRACK_ITEM_0 + i, BS_VCD_KEY_NEXT, BS_VCD_TRACK_ITEM_0 + i + 1);
		}
	}
}

long KVideoFOXLibDlg::onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data)
{
	updateOptions();
	prepareMenus();

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

			SOptions opt;

			res = ::GetOptions(&opt);
			handleError(res);

			opt.nCopies = 0;
			opt.bTestBurn = BS_FALSE;
			opt.bVerifyAfterBurn = BS_FALSE;

			res = ::SetOptions(opt);
			handleError(res);
		}
		else {
			return 1;
		}
	}

	KSampleBurnDlg	burnDlg(this);
	burnDlg.execute();

	return 1;
}

long KVideoFOXLibDlg::onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data)
{
	updateOptions();
	prepareMenus();
	
	CALL_FXDIALOG_HANDLE_ERROR(::BurnDialog());

	updateDeviceCombo();
	return 1;
}

void KVideoFOXLibDlg::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		int32 nLength = 2048;

		GetText(errCode, chError, &nLength);

#ifdef _UNICODE
		KString strError = KStringFormat(_T("error: %ls"), chError);
#else
		KString strError = KStringFormat(_T("error: %hs"), chError);
#endif

		FXString fxstr = (const wchar_t*)strError;
		FXMessageBox::error(this, MBOX_OK, "IsoSDK", fxstr.text());
	}
}

void KVideoFOXLibDlg::updateDeviceCombo()
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
		m_cmbDevice->setCurrentItem(m_cmbDevice->getNumItems()-1);
	}

	m_cmbDevice->setNumVisible(m_cmbDevice->getNumItems());
}

long KVideoFOXLibDlg::onProjectTypeChange(FXObject* sender, FXSelector key, void* data)
{
	FXint indx = m_cmbProjectType->getCurrentItem();
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
	handleError(res);

	if (res != BS_SDK_ERROR_NO) {
		::GetProjectType(&type);
		switch(type) {
			case BS_BURNER_VCD:	indx = 0; break;
			case BS_BURNER_SVCD:	indx = 1; break;
			default: FXASSERT(0); break;
		}
		m_cmbProjectType->setCurrentItem(indx);
	}
	else {
		m_videoFileList->clearItems();
		m_pictureFileList->clearItems();
	}

	return 1;
}

long KVideoFOXLibDlg::onRescanDevices(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::RescanDevices();
	handleError(res);

	updateDeviceCombo();

	return 1;
}

long KVideoFOXLibDlg::onCmdAspi(FXObject* sender, FXSelector key, void* data)
{
	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;

	// Set selected interface

	int32 res = ::SetASPI(which);
	handleError(res);
	updateDeviceCombo();
	return 1;
}

long KVideoFOXLibDlg::onUpdAspi(FXObject* sender, FXSelector key, void* data)
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

long KVideoFOXLibDlg::onDisableImagewriter(FXObject* sender, FXSelector key, void* data)
{
	// Disable or enable image writer

	::EnableImageDevice(data == 0 ? BS_TRUE : BS_FALSE);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KVideoFOXLibDlg::onBurningDevices(FXObject* sender, FXSelector key, void* data)
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = data != 0;
	updateDeviceCombo();
	return 1;
}

long KVideoFOXLibDlg::onAbout(FXObject* sender, FXSelector key, void* data)
{
	KAboutDlg	aboutDlg(this);
	aboutDlg.execute();
	return 1;
}

long KVideoFOXLibDlg::onWeb(FXObject* sender, FXSelector key, void* data)
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
