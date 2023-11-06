#include "stdafx.h"
#include "ImageEditFOXLibDlg.h"
#include "../Common/AboutDlg.h"
#include "TreeNodes.h"
#include "PropertiesDlg.h"
#include <utility>
#define WEBSITELINK			"http://www.isosdk.com"

#include "SaveTrackDialog.h"
#include "SaveContentDialog.h"
#include "SectorViewDialog.h"
#include "SaveDiscDialog.h"
#include "md5Dialog.h"
#include "AudioGrabbingDialog.h"
#include "AudioTrackPlayingDialog.h"

#include "ScanSectorsDialog.h"

#include <sys/types.h>
#include <sys/stat.h>

#include "ReadCDTextDlg.h"

#ifdef WIN32
	static const FXString audiofiles_ext[]= {".wav", ".mp3", ".ogg", ".wma", ".vqf", ".aac", ".m4a", ".flac"};
	static const FXint audiofiles_ext_size = 8;
#else
	static const FXString audiofiles_ext[]= {".mp3", ".mp4", ".m4a", ".aac", ".aif", ".aiff", ".aifc", ".wav", ".raw", ".sd2f", ".snd", ".au", ".ac3", ".caf"};	
	static const FXint audiofiles_ext_size = 14;
#endif


#define DLG_IMAGES_PATTERN "All Supported (*.iso,*.bin,*.nrg,*.cdi,*.mdf,*.img,*.gi,*.pdi,*.dmg,*.b5i,*.b6i)"

/////////////////////////////////////////////////////////////////////////////
//  message handlers

inline FXint pointerToInt(void* voidVal)
{
	return *(FXint*)(&voidVal);
}

FXDEFMAP(KImageEditFOXLibDlg) KImageEditFOXLibMap[]= {
	FXMAPFUNCS(SEL_COMMAND,KImageEditFOXLibDlg::ID_ASPI_INTERNAL, KImageEditFOXLibDlg::ID_ASPI_FROGASPI, KImageEditFOXLibDlg::onCmdAspi),
	FXMAPFUNCS(SEL_UPDATE, KImageEditFOXLibDlg::ID_ASPI_INTERNAL, KImageEditFOXLibDlg::ID_ASPI_FROGASPI, KImageEditFOXLibDlg::onUpdAspi),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_RESCANDEVICES, KImageEditFOXLibDlg::onRescanDevices),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_BURNDEVICES, KImageEditFOXLibDlg::onBurningDevices),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_DISABLEIMAGE, KImageEditFOXLibDlg::onDisableImagewriter),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_ABOUT, KImageEditFOXLibDlg::onAbout),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_WEB, KImageEditFOXLibDlg::onWeb),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_DEVICEBOX, KImageEditFOXLibDlg::onDeviceBox),
	FXMAPFUNC(SEL_RIGHTBUTTONPRESS, KImageEditFOXLibDlg::ID_LEFTPANEL, KImageEditFOXLibDlg::onLeftPanelRightClick),
	FXMAPFUNC(SEL_RIGHTBUTTONPRESS, KImageEditFOXLibDlg::ID_RIGHTPANEL, KImageEditFOXLibDlg::onRightPanelRightClick),
	FXMAPFUNC(SEL_DOUBLECLICKED, KImageEditFOXLibDlg::ID_RIGHTPANEL, KImageEditFOXLibDlg::onRightPanelDblClick),
	FXMAPFUNC(SEL_SELECTED, KImageEditFOXLibDlg::ID_LEFTPANEL, KImageEditFOXLibDlg::onLeftPaneSelected),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_SECTOR_VIEW, KImageEditFOXLibDlg::onSectorView),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_SCAN_SECTORS, KImageEditFOXLibDlg::onScanSectors),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_SHOW_PROPERTIES, KImageEditFOXLibDlg::onShowProperties),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_EXTRACT_FILE, KImageEditFOXLibDlg::onExtractFiles),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_EXTRACT_FILE_EX, KImageEditFOXLibDlg::onExtractFilesEx),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_VERIFY_DISCTYPE, KImageEditFOXLibDlg::onVerifyCompressedAndEncrypt),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_EXTRACT_SYS, KImageEditFOXLibDlg::onExtractFiles),

	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_LIST_CONTENT, KImageEditFOXLibDlg::onListContent),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_EXTRACT_TRACK, KImageEditFOXLibDlg::onExtractTrack),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_MD5, KImageEditFOXLibDlg::onMD5),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_MD5_CHECK, KImageEditFOXLibDlg::onMD5Check),
	FXMAPFUNC(KImageEditFOXLibDlg::SEL_ERRORNOTIFY, 0, KImageEditFOXLibDlg::onErrorNotify),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_MOUNTIMAGE, KImageEditFOXLibDlg::onMountImage),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_UNMOUNTIMAGE, KImageEditFOXLibDlg::onUnmountImage),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_SAVEIMAGE,  KImageEditFOXLibDlg::onSaveDisc),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_VERIFYDISC,  KImageEditFOXLibDlg::onVerifyDisc),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_WRITELOG, KImageEditFOXLibDlg::onWriteLogFile),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_PLAY, KImageEditFOXLibDlg::onPlay),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_GRAB, KImageEditFOXLibDlg::onGrab),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_GRABALLTRACKS, KImageEditFOXLibDlg::onGrabAll),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_READ_CDTEXT, KImageEditFOXLibDlg::onReadCDText),	
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_READ_INDEXES, KImageEditFOXLibDlg::onReadIndexes),	
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_READ_ISRC, KImageEditFOXLibDlg::onReadISRC),
	FXMAPFUNC(SEL_COMMAND, KImageEditFOXLibDlg::ID_REFRESH, KImageEditFOXLibDlg::onRefresh),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KImageEditFOXLibDlg::onCmdCancel),	
	FXMAPFUNC(SEL_CLOSE, 0, KImageEditFOXLibDlg::onCmdCancel)
};

FXIMPLEMENT(KImageEditFOXLibDlg, FXDialogBox, KImageEditFOXLibMap, ARRAYNUMBER(KImageEditFOXLibMap))
KImageEditFOXLibDlg::KImageEditFOXLibDlg(FXApp *app, const FXString &title)
	: FXDialogBox(app, title, DECOR_ALL, 0, 0, 600, 500, 0, 0, 0, 0, 0, 0)
	, m_bBurningDevicesOnly(false)
	, m_medium(0)
	, m_nAspiInterface(BS_ASPI_INTERNAL)	
{


	m_isosdkIconSmall = new FXICOIcon(getApp(), isosdksmall);
	m_isosdkIconBig = new FXICOIcon(getApp(), isosdkbig);
	m_iconAudio = new FXICOIcon(getApp(), audio);
	m_iconDisc = new FXICOIcon(getApp(), burn_iso);
	m_iconOpenDir = new FXICOIcon(getApp(), open_folder);
	m_iconCloseDir = new FXICOIcon(getApp(), closed_folder);
	m_iconFile = new FXGIFIcon(getApp(), minidoc);
	m_iconFileSystem = new FXICOIcon(getApp(), iso);
	m_iconPlay = new FXICOIcon(getApp(), play);
	m_iconStop = new FXICOIcon(getApp(), stop);

	///////////////////////////////////////////////////////////////////
	// Create menu bar

	FXMenuBar *menubar = new FXMenuBar(this, LAYOUT_FILL_X);

	FXMenuPane* discmenu = new FXMenuPane(this);
		new FXMenuCommand(discmenu, "&Verify", NULL, this, ID_VERIFYDISC);
		new FXMenuCommand(discmenu, "&Save in image", NULL, this, ID_SAVEIMAGE);
		new FXHorizontalSeparator(discmenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(discmenu,"Write Log", NULL, this, ID_WRITELOG);
		new FXHorizontalSeparator(discmenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(discmenu,"E&xit", NULL, this, FXDialogBox::ID_CANCEL); //die App hat kein Cancel icon
	new FXMenuTitle(menubar, "&Disc", NULL, discmenu);

	FXMenuPane* imagemenu = new FXMenuPane(this);
		new FXMenuCommand(imagemenu, "&Mount image...", NULL, this, ID_MOUNTIMAGE);
		new FXMenuCommand(imagemenu, "&Unmount image", NULL, this, ID_UNMOUNTIMAGE);		
		new FXMenuSeparator(imagemenu);
		new FXMenuCommand(imagemenu, "&Make MD5 for image", NULL, this, ID_MD5);		
		new FXMenuCommand(imagemenu, "&Check MD5 for image", NULL, this, ID_MD5_CHECK);		
	new FXMenuTitle(menubar, "&Image", NULL, imagemenu);

	FXMenuPane* aspimenu = new FXMenuPane(this);
		FXMenuPane* interfacemenu = new FXMenuPane(this);
			new FXMenuRadio(interfacemenu, "&Internal", this, ID_ASPI_INTERNAL);
			new FXMenuRadio(interfacemenu, "&WnAspi", this, ID_ASPI_WNASPI);
			new FXMenuRadio(interfacemenu, "&FrogAspi", this, ID_ASPI_FROGASPI);
		new FXMenuCascade(aspimenu, "&Interface", NULL, interfacemenu);
		new FXMenuCommand(aspimenu,"&Rescan Devices", NULL, this, ID_RESCANDEVICES);
		burnDevicesOnly = new FXMenuCheck(aspimenu,"&Burn devices only", this, ID_BURNDEVICES);
		m_chkDisableImage = new FXMenuCheck(aspimenu,"Disable &Imagewriter", this, ID_DISABLEIMAGE);
	new FXMenuTitle(menubar, "A&SPI/SPTI", NULL, aspimenu);

	FXMenuPane* audiomenu = new FXMenuPane(this);
		new FXMenuCommand(audiomenu, "Play selected", m_iconPlay, this, ID_PLAY);
		new FXMenuCommand(audiomenu, "Grab all tracks", NULL, this, ID_GRABALLTRACKS);
	new FXMenuTitle(menubar, "&Audio", NULL, audiomenu);

	FXMenuPane* infomenu = new FXMenuPane(this);
		new FXMenuCommand(infomenu, "&About", NULL, this, ID_ABOUT);
		new FXMenuCommand(infomenu, "&Web", NULL, this, ID_WEB);
	new FXMenuTitle(menubar, "I&nformation", NULL, infomenu);

	// Set checks for some menus



	// Device combo
	FXHorizontalFrame *deviceFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X);
		//new FXLabel(deviceFrame, "Device: ", NULL, JUSTIFY_LEFT|LAYOUT_FIX_WIDTH, 0, 0, 70);
		m_cmbDevice = new FXComboBox(deviceFrame, 30, this, ID_DEVICEBOX, LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC, 200);
		new FXButton(deviceFrame, "Refresh", NULL, this, ID_REFRESH);
		new FXButton(deviceFrame, "Open Image...", NULL, this, ID_MOUNTIMAGE);

	FXSplitter* splitter = new FXSplitter(this, LAYOUT_FILL|SPLITTER_NORMAL);

	// create left pane
	m_leftPanel = new FXTreeList(splitter, this, ID_LEFTPANEL, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH|
		TREELIST_SINGLESELECT|TREELIST_SHOWS_LINES|TREELIST_SHOWS_BOXES|TREELIST_ROOT_BOXES, 0, 0, 200, 0);

	// create right pane
	{
		m_rightPanel = new FXIconList(splitter, this, ID_RIGHTPANEL, LAYOUT_FILL|FRAME_SUNKEN);
		m_rightPanel->appendHeader("Name", NULL, 150);
		m_rightPanel->appendHeader("LBA", NULL, 50);
		m_rightPanel->appendHeader("Size", NULL, 50);
		m_rightPanel->appendHeader("Modified", NULL, 120);
	}

	setMiniIcon(m_isosdkIconSmall);
	setIcon(m_isosdkIconBig);


	m_strStartupDir = FXSystem::getCurrentDirectory();
}

void KImageEditFOXLibDlg::loadOwner()
{
	//--------------------------------------------------
	//Init the SDK
	//--------------------------------------------------

		// Set global fxapp to SDK


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

	res = ::SetFXApp(this);
	handleError(res);

	if (m_bBurningDevicesOnly)
		burnDevicesOnly->setCheck();

	// Update devices list
	updateDeviceCombo();
}


void KImageEditFOXLibDlg::create()
{
	FXDialogBox::create();
	m_iconDisc->create();
	m_iconAudio->create();
	m_iconOpenDir->create();
	m_iconCloseDir->create();
	m_iconFile->create();
	m_iconFileSystem->create();
}

KImageEditFOXLibDlg::KImageEditFOXLibDlg()
{
}

KImageEditFOXLibDlg::~KImageEditFOXLibDlg()
{
	delete m_iconDisc;
	delete m_iconAudio;
	delete m_iconOpenDir;
	delete m_iconCloseDir;
	delete m_iconFile;
	delete m_iconFileSystem;
	delete m_medium;
	delete m_iconPlay;
	delete m_iconStop;
	delete m_isosdkIconBig;
	delete m_isosdkIconSmall;

	
	::DeInitialize();
}

void KImageEditFOXLibDlg::updateDeviceCombo()
{
	FXString strOldDevice = m_cmbDevice->getText();

	m_cmbDevice->clearItems();
	m_cmbDevice->setCurrentItem(-1);

	// Get devices list

	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 res = ::GetDevices(chListDevices, &nUsed, m_bBurningDevicesOnly ? BS_TRUE : BS_FALSE);
	handleError(res);

	// Get current device

	TCHAR pchDevice[50];
	int32 nLength = sizeof(pchDevice) / sizeof(TCHAR);
	res = ::GetReadDevice(pchDevice, &nLength);
	handleError(res);

	// Add devices to combo box

	for (int i = 0; i < nUsed; i++)
	{
		FXString strItem;
		strItem = SDK2FoxString(chListDevices[i]);

		m_cmbDevice->appendItem(strItem);

		// Set selection on current device

		if (0 == _tcsncmp(pchDevice, chListDevices[i], 2))
		{
			m_cmbDevice->setCurrentItem(i);
		}
	}

	// Ensure all devices are visible

	m_cmbDevice->setNumVisible(m_cmbDevice->getNumItems());

	if (m_cmbDevice->getText() != strOldDevice)
	{
		onDeviceBox(this, SEL_COMMAND, 0);
	}
}

long KImageEditFOXLibDlg::onDeviceBox(FXObject* sender, FXSelector key, void* data)
{
	FXint indx = m_cmbDevice->getCurrentItem();

	if (-1 < indx)
	{
		FXString strItem = m_cmbDevice->getItemText(indx);
		KString strDevice = Fox2SDKString(strItem);

		// Set current device
		int32 res = ::SetReadDevice(strDevice);
		handleError(res);
	}

	reloadLeftPanel();

	return 1;
}

void KImageEditFOXLibDlg::handleError(int32 errCode)
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

long KImageEditFOXLibDlg::onErrorNotify(FXObject* sender, FXSelector key, void* data)
{
	handleError(pointerToInt(data));
	return 1;
}

long KImageEditFOXLibDlg::onRescanDevices(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::RescanDevices();
	handleError(res);

	// Update devices list

	updateDeviceCombo();
	onDeviceBox(sender, key, data);
	return 1;
}

long KImageEditFOXLibDlg::onCmdAspi(FXObject* sender, FXSelector key, void* data)
{
	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;

	// Set selected interface

	int32 res = ::SetASPI(which);
	handleError(res);
	updateDeviceCombo();

	// Get current interface
	::GetASPI(&m_nAspiInterface);
	return 1;
}

long KImageEditFOXLibDlg::onUpdAspi(FXObject* sender, FXSelector key, void* data)
{
	// Update radio buttons in Interface menu

	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;

	if (m_nAspiInterface == which)
		sender->handle(this,FXSEL(SEL_COMMAND,FXWindow::ID_CHECK),NULL);
	else
		sender->handle(this,FXSEL(SEL_COMMAND,FXWindow::ID_UNCHECK),NULL);

	return 1;
}

long KImageEditFOXLibDlg::onDisableImagewriter(FXObject* sender, FXSelector key, void* data)
{
	// Disable or enable image writer

	::EnableImageDevice(data == 0 ? BS_TRUE : BS_FALSE);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KImageEditFOXLibDlg::onBurningDevices(FXObject* sender, FXSelector key, void* data)
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = data != 0;
	updateDeviceCombo();
	return 1;
}

long KImageEditFOXLibDlg::onAbout(FXObject* sender, FXSelector key, void* data)
{
	KAboutDlg	aboutDlg(this);
	aboutDlg.execute();
	return 1;
}

long KImageEditFOXLibDlg::onWeb(FXObject* sender, FXSelector key, void* data)
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

long KImageEditFOXLibDlg::onLeftPanelRightClick(FXObject* sender, FXSelector key, void* data)
{
	FXEvent* event = (FXEvent*)data;
	FXTreeItem* item = 0;
	item = m_leftPanel->getItemAt(event->win_x, event->win_y);
	
	if (item)
	{
		m_leftPanel->setCurrentItem(item, true);
		m_leftPanel->selectItem(item, true);
	
		if (item->getData())
		{
			NodeList nodes;
			nodes.push_back((ITreeNode*)item->getData());
			// show menu for current nodes
			showPopupForNodes(nodes, event->root_x, event->root_y);
		}
	}
	else
	{
		return 1;
	}

	return 1;
}

long KImageEditFOXLibDlg::onRightPanelRightClick(FXObject* sender, FXSelector key, void* data)
{
	FXEvent* event = (FXEvent*)data;
	FXint item = m_rightPanel->getItemAt(event->win_x, event->win_y);
	if (item != -1)
	{
		m_rightPanel->setCurrentItem(item, true);
		m_rightPanel->selectItem(item, true);
	}

	NodeList nodes;

	for(FXint i = 0; i < m_rightPanel->getNumItems(); ++i)
	{
		if (m_rightPanel->isItemSelected(i))
			nodes.push_back((ITreeNode*)m_rightPanel->getItemData(i));
	}

	// show menu for current nodes
	if (nodes.size() > 0)
		showPopupForNodes(nodes, event->root_x, event->root_y);

	return 1;
}

long KImageEditFOXLibDlg::onRightPanelDblClick(FXObject* sender, FXSelector key, void* data)
{	
	ITreeNode* pTreeNode = (ITreeNode*)m_rightPanel->getItemData( m_rightPanel->getCurrentItem() );

	if (!pTreeNode)
		return 0;

	FXTreeItem* item = m_leftPanel->getCurrentItem();

	if (item == 0)
		return 0;

	// check for ".."
	{
		FXTreeItem* pParent = item->getParent();

		if (pParent)
		{
			ITreeNode* parent = (ITreeNode*)pParent->getData();

			if (parent && parent == pTreeNode)
			{
				m_leftPanel->setCurrentItem(pParent, true);
				m_leftPanel->selectItem(pParent, true);
				return 1;
			}
		}
	}

	m_leftPanel->expandTree(item);

	FXTreeItem* pSubItem = item->getFirst();

	for (; pSubItem; pSubItem = pSubItem->getBelow())
	{
		ITreeNode* pSubNode = (ITreeNode*)pSubItem->getData();

		if (!pSubNode)
			continue;

		if (pSubNode == pTreeNode)
		{
			m_leftPanel->setCurrentItem(pSubItem, true);
			m_leftPanel->selectItem(pSubItem, true);
			return 1;
		}
	}

	return 1;
}

long KImageEditFOXLibDlg::onLeftPaneSelected(FXObject* sender, FXSelector key, void* data)
{
	reloadRightPanel();
	return 1;
}

void KImageEditFOXLibDlg::reloadLeftPanel()
{
	// clear left and right panels
	m_leftPanel->clearItems();
	m_rightPanel->clearItems();

	delete m_medium;
	m_medium = 0;

	SMediumInfo sMediumInfo;
	int32 res = ::GetMediumInformation(BS_READ_DEVICE, &sMediumInfo);

	if (res != BS_SDK_ERROR_NO)
	{
		if (res == BS_SCSI_ERROR_DISK_31)
			m_leftPanel->appendItem(NULL, "No medium");
		else
			handleError(res);
		return;
	}

	m_medium = MediumNode::create(sMediumInfo);

	buildNode(NULL, m_medium);
}

void KImageEditFOXLibDlg::reloadRightPanel()
{
	// get currently selected item on left panel
	FXTreeItem* selected = m_leftPanel->getCurrentItem();
	if (selected == 0)
		return;

	FXTreeItem* pParent = selected->getParent();

	ITreeNode* node = (ITreeNode*)selected->getData();
	ITreeNode* parent = pParent ? (ITreeNode*)pParent->getData() : NULL;

	if (node == 0)
		return;

	// clear right panel
	m_rightPanel->clearItems();

	// if there is parent node, add .. item for it
	if (parent)
	{
		m_rightPanel->appendItem("..", 0, NULL, parent);
	}

	//NodeList fileNodes;

	FXint nLastDir = m_rightPanel->getNumItems();

	for(int i = 0; i < int(node->getChildsCount()); ++i)
	{
		// get child node
		ITreeNode* child = node->getChild(i);

		// get info for child node
		GenericInfo info = child->getGenericInfo();

		// get open/close icons for child node
		std::pair<FXIcon*,FXIcon*> icons = getNodeIcons(info.icon);

		if (dynamic_cast<FileNode*>(child))
		{
			m_rightPanel->appendItem(FXString::value("%s\t%d\t%d\t%s", 
				info.name.text(), info.lba, (int32)info.size, info.date.text()), 
				0, icons.second, child);
		}
		else
		{
			nLastDir = m_rightPanel->insertItem(nLastDir,
				FXString::value("%s\t%d\t%d\t%s", info.name.text(), info.lba, (int32)info.size, info.date.text()), 
				0, icons.second, child) + 1;
		}
	}
}

std::pair<FXIcon*,FXIcon*> KImageEditFOXLibDlg::getNodeIcons(GenericInfo::Icon iconType)
{
	switch(iconType)
	{
	case GenericInfo::ICON_MEDIUM:
	case GenericInfo::ICON_SESSION:
	case GenericInfo::ICON_TRACK_DATA:
		return std::make_pair(m_iconDisc, m_iconDisc);

	case GenericInfo::ICON_TRACK_AUDIO:
		return std::make_pair(m_iconAudio, m_iconAudio);

	case GenericInfo::ICON_FILESYS_ISO:
	case GenericInfo::ICON_FILESYS_JOLIET:
	case GenericInfo::ICON_FILESYS_ROCKRIDGE:
	case GenericInfo::ICON_FILESYS_UDF:
	case GenericInfo::ICON_FILESYS_BOOT:
		return std::make_pair(m_iconFileSystem, m_iconFileSystem);

	case GenericInfo::ICON_DIRECTORY:
		return std::make_pair(m_iconOpenDir, m_iconCloseDir);

	case GenericInfo::ICON_FILE:
		return std::make_pair(m_iconFile, m_iconFile);

	default:
		return std::make_pair((FXIcon*)0, (FXIcon*)0);
	}	
}

void KImageEditFOXLibDlg::buildNode(FXTreeItem* parent, ITreeNode* node)
{
	// skip files
	if (dynamic_cast<FileNode*>(node) != 0)
	{
		return;
	}

	GenericInfo nodeInfo = node->getGenericInfo();

	std::pair<FXIcon*,FXIcon*> icons = getNodeIcons(nodeInfo.icon);

	FXTreeItem* treeItem = m_leftPanel->appendItem(parent, nodeInfo.name, icons.first, icons.second);
	treeItem->setData(node);

	size_t childsCount = node->getChildsCount();

	for (unsigned i = 0; i < childsCount; ++i)
	{
		buildNode(treeItem, node->getChild(i));
	}

	// do not expand directories
	if (dynamic_cast<DirectoryNode*>(node) == 0)
	{
		m_leftPanel->expandTree(treeItem);
	}
}

long KImageEditFOXLibDlg::onShowProperties(FX::FXObject* sender, FX::FXSelector, void*)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();

	KPropertiesDlg dlg(getApp(), nodes[0]->getProperties());
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();

	return 1;
}

long KImageEditFOXLibDlg::onSectorView(FX::FXObject* sender, FX::FXSelector, void*)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();	
	
	KSectorViewDialog dlg(this,nodes[0]->getGenericInfo().lba);
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();
	return 1;
}

long KImageEditFOXLibDlg::onScanSectors(FX::FXObject* sender, FX::FXSelector, void*)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();	
	GenericInfo cGI = nodes[0]->getGenericInfo();

	KScanSectorsDialog dlg(this, cGI.lba, (int32)(cGI.size));
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();
	return 1;
}

long KImageEditFOXLibDlg::onExtractFiles(FX::FXObject* sender, FX::FXSelector, void*)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();

	FXDirDialog FolderDlg(this, "Choose folder for extraction");

	if(!FolderDlg.execute(PLACEMENT_SCREEN))
	{
		return 0;
	}

	FXString strFolderName = FolderDlg.getDirectory();

	if (strFolderName == "")
	{
		FXMessageBox msgBox(this, "Extract Folders/Files", 
			FXString::value("Extraction path cannot be empty. Nodes: %d", nodes.size()), 
			NULL, MBOX_OK);

		msgBox.execute();
		return 0;
	}

	FX::FXSystem::setCurrentDirectory(strFolderName);
	
	KSaveContentDialog::SSaveContentParams params(KSaveContentDialog::AIM_IMPORT, nodes, strFolderName);
	KSaveContentDialog dlg(params, this);
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();

	return 1;
}


long KImageEditFOXLibDlg::onVerifyCompressedAndEncrypt(FX::FXObject* sender, FX::FXSelector, void*)
{
	int nRes = ::CheckSignature();
	FXString sourceType = "";
	switch (nRes) {
	case BS_SDK_COMPENC_ENCRYPTED:
		sourceType = "Disc or Image is encrypted!";
		break;
	case BS_SDK_COMPENC_COMPRESSED:
		sourceType = "Disc or Image is compressed!";
		break;
	case BS_SDK_COMPENC_BOTH:
		sourceType = "Disc or Image is compressed and encrypted!";
		break;
	default:
		sourceType = "Disc or Image is not compressed and encrypted!";
	}
	FXMessageBox msgBox(this, "Is disc/image encrypted or compressed?",
		sourceType,
		NULL, MBOX_OK);
	msgBox.execute();
	return 0;
}

long KImageEditFOXLibDlg::onExtractFilesEx(FX::FXObject* sender, FX::FXSelector, void*)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();

	FXDirDialog FolderDlg(this, "Choose folder for extraction");

	if (!FolderDlg.execute(PLACEMENT_SCREEN))
	{
		return 0;
	}

	FXString strFolderName = FolderDlg.getDirectory();

	if (strFolderName == "")
	{
		FXMessageBox msgBox(this, "Extract Folders/Files",
			FXString::value("Extraction path cannot be empty. Nodes: %d", nodes.size()),
			NULL, MBOX_OK);

		msgBox.execute();
		return 0;
	}

	//TamTam...is it a IsoSDK signed disc/image?
	//It is encrypted, so show the password dialog
	FXString  strTmpName = "";
	int nRes = ::CheckSignature();
	if (nRes == BS_SDK_COMPENC_ENCRYPTED || nRes == BS_SDK_COMPENC_BOTH) {

		FXInputDialog dlgPwd(getApp(), "IsoSDK Decrypt", "Password", NULL, INPUTDIALOG_STRING);
		
		if (dlgPwd.execute() && !dlgPwd.getText().empty())
		{
			strTmpName = FXString::compose(dlgPwd.getText(), false);

		}
		else {
			FXMessageBox msgBox(this, "Extract encrypted files",
				FXString::value("For encrypted files a password is needed."),
				NULL, MBOX_OK);

			msgBox.execute();
			return 0;
		}

	}

	FX::FXSystem::setCurrentDirectory(strFolderName);

	KSaveContentDialog::SSaveContentParams params(KSaveContentDialog::AIM_IMPORT, nodes, strFolderName, strTmpName, BS_IMPOPTS_EX);
	KSaveContentDialog dlg(params, this);
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();

	return 1;
}

long KImageEditFOXLibDlg::onListContent(FXObject* sender, FXSelector, void*)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();

	FXString strFileName = FXFileDialog::getSaveFilename(this, "Choose file to list content", "", "Text files (*.txt)");

	if (strFileName.empty())
		return 1;

	if ("" == FXPath::extension(strFileName))
		strFileName += ".txt";
	
	FXFile fContentList;
	fContentList.create(strFileName);
	fContentList.open(strFileName, FXIO::WriteOnly);

	RecursivePrintContent(fContentList, nodes[0], PATHSEPSTRING);

	return 1;
}

void KImageEditFOXLibDlg::RecursivePrintContent(FXFile &fContentList, ITreeNode* pcNode, FXString strFolderPath)
{		
	FileSysNode *pcFSysNode = 0;
	pcFSysNode = dynamic_cast<FileSysNode*>(pcNode);

	if (pcFSysNode)
	{
		int32 nChildCount = (int32)pcFSysNode->getChildsCount();

		for (int32 i = 0; i < nChildCount; i++)
		{
			RecursivePrintContent(fContentList, pcFSysNode->getChild(i), strFolderPath);
		}
	}
	else
	{
		DirectoryNode* pcDirNode = 0;
		pcDirNode = dynamic_cast<DirectoryNode*>(pcNode);

		if (pcDirNode)
		{
			GenericInfo info = pcDirNode->getGenericInfo();

			strFolderPath += info.name;
			strFolderPath += PATHSEPSTRING;

			FXString strWrite(strFolderPath);
			strWrite += "\r\n";
			fContentList.writeBlock(strWrite.text(), strWrite.length());

			int32 nChildCount = (int32)pcDirNode->getChildsCount();

			for (int32 i = 0; i < nChildCount; i++)
			{
				RecursivePrintContent(fContentList, pcDirNode->getChild(i), strFolderPath);
			}
		}
		else
		{
			FileNode* pcFileNode = 0;
			pcFileNode = dynamic_cast<FileNode*>(pcNode);

			if(pcFileNode)
			{
				GenericInfo info = pcFileNode->getGenericInfo();
				
				FXString strWrite(strFolderPath);
				strWrite += info.name;
				strWrite += "\r\n";
				fContentList.writeBlock(strWrite.text(), strWrite.length());
			}
		}
	}
}

long KImageEditFOXLibDlg::onMD5(FX::FXObject* sender, FX::FXSelector, void*)
{	
	FXString strImagePath = getCurrentImagePath();

	if (strImagePath.empty())
	{
		FXFileDialog fileDialog(this, "Choose file please...");
		fileDialog.setPatternList(DLG_IMAGES_PATTERN);
		fileDialog.setSelectMode(SELECTFILE_EXISTING);
		if (fileDialog.execute(PLACEMENT_SCREEN))
		{
			FX::FXSystem::setCurrentDirectory(fileDialog.getDirectory());
			strImagePath = FXString::compose(fileDialog.getFilename(), false);
		}
	}

	if (!strImagePath.empty())
	{
		KMD5Dialog dlg(this, strImagePath);
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
		dlg.execute();

		FXString strMD5 = dlg.GetMD5String();

		if (strMD5.empty())
		{
			return 0;
		}

		FXString strMD5FileName = strImagePath.left(strImagePath.find('.')) + ".md5";

		FXFile cFile(strMD5FileName, FXFile::Writing);
		cFile.writeBlock(strMD5.text(), strMD5.length());

		FXMessageBox::information(this, MBOX_OK, "Done!", ("MD5 hash \" " + strMD5 + "\" has been written to this file:\n" +strMD5FileName +".").text());
	}

	return 1;
}

long KImageEditFOXLibDlg::onMD5Check(FX::FXObject* sender, FX::FXSelector, void*)
{	
	FXString strImagePath = getCurrentImagePath();

	if (strImagePath.empty())
	{
		FXFileDialog fileDialog(this,"Choose file please...");
		fileDialog.setPatternList(DLG_IMAGES_PATTERN);
		fileDialog.setSelectMode(SELECTFILE_EXISTING);
		if (fileDialog.execute(PLACEMENT_SCREEN))
		{
			FX::FXSystem::setCurrentDirectory(fileDialog.getDirectory());
			strImagePath = FXString::compose(fileDialog.getFilename(), false);
		}
	}

	if (!strImagePath.empty())
	{
		FXString strMD5FileName = strImagePath.left(strImagePath.find('.')) + ".md5";

		FXFile cFile(strMD5FileName, FXFile::Reading);

		if (!cFile.isOpen())
		{
			FXMessageBox::error(this, MBOX_OK, "ImageEditFOXLib", ("Can't open MD5 file \"" + strMD5FileName + "\".").text());
			return 0;
		}

		char szBuffer[32 + 1] = {0};
		cFile.readBlock(szBuffer, 32);

		FXString strMD5FromFile = szBuffer;

		KMD5Dialog dlg(this, strImagePath);
		dlg.setIcon(m_isosdkIconBig);
		dlg.setMiniIcon(m_isosdkIconSmall);
		dlg.execute();

		FXString strMD5 = dlg.GetMD5String();

		if (strMD5.empty())
		{
			return 0;
		}

		if (strMD5 == strMD5FromFile)
		{
			FXMessageBox::information(this, MBOX_OK, "MD5 is Ok.", ("MD5 hash \" " + strMD5 + "\" is equal to those in .md5 file.").text());
		}
		else
		{
			FXMessageBox::information(this, MBOX_OK, "MD5 hash DIFFERS!", ("MD5 hash \" " + strMD5 + "\" differs from those in .md5 file: \" " + strMD5FromFile + "\".").text());
		}
	}

	return 0;
}

long KImageEditFOXLibDlg::onExtractTrack(FX::FXObject* sender, FX::FXSelector, void*)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();
	
	for(size_t i = 0; i < nodes.size(); ++i)
	{
		TrackNode* pcTrackNode = 0;
		pcTrackNode = dynamic_cast<TrackNode*>(nodes[i]);
		
		FXString strPatternList;
		unsigned nFileFormat;
		FXString strExtension;
		
		if(pcTrackNode)
		{
			const STrackInfo& cSTrackInfo = pcTrackNode->getTrackInfo();
			
			switch(cSTrackInfo.nFormat)
			{
				case BS_TF_AUDIO:
				{
					nFileFormat = BS_FF_WAVE;
					strExtension = ".wav";
					strPatternList = 
						"WAVE files (*.wav)\nBIN files (RAW FORMAT) (*.bin)";
				}
				break;

				case BS_TF_DATA_MODE1:
				{
					nFileFormat = BS_FF_ISO;
					strExtension = ".iso";

					strPatternList = "ISO files (*.iso)";
					
					//Check Disk
					SMediumInfo cMediumInfo;
					::GetMediumInformation(BS_READ_DEVICE, &cMediumInfo);

					if (cMediumInfo.wMediumTypeCode >= BS_CD_ROM &&
						cMediumInfo.wMediumTypeCode <= BS_CD_RW)
					{
						strPatternList += "\nBIN files (RAW FORMAT) (*.bin)";
					}
				}
				break;

				case BS_TF_DATA_MODE2:
				{
					nFileFormat = BS_FF_MPEG;
					strExtension = ".mpg";
					strPatternList = 
						"MPEG files (*.mpg)\nBIN files (RAW FORMAT) (*.bin)";
				}
				break;

			default:
				{
					handleError(BS_SDK_ERROR_NOT_IMPLEMENTED);
					return 0;
				}
			}

			FXFileDialog FileDialog(this, FXString::value("Choose file to save track # %d", 
				cSTrackInfo.nTrackNumber));

			FileDialog.setFilename(FXString::value("Track %d", cSTrackInfo.nTrackNumber));
			FileDialog.setPatternList(strPatternList);
			FileDialog.setSelectMode(SELECTFILE_ANY);
			
			if(!FileDialog.execute(PLACEMENT_SCREEN))
			{
				continue;
			}
			
			FX::FXSystem::setCurrentDirectory(FileDialog.getDirectory());

			FXString strFileName = FXString::compose(FileDialog.getFilename(), false);

			if (FileDialog.getCurrentPattern() == 1)
			{
				nFileFormat = BS_FF_BIN;
				strExtension = ".bin";
			}

			if ("" == FXPath::extension(strFileName))
			{
				strFileName += strExtension;
			}

			doExtraction(cSTrackInfo.nTrackNumber, strFileName, nFileFormat);
			
		}// if(pcTrackNode)
		else
		{
			continue;
		}
	}
	
	// end

	return 1;
}

void KImageEditFOXLibDlg::showPopupForNodes(std::vector<ITreeNode*>& nodes, int x, int y)
{
	FXASSERT(!nodes.empty());

	FXMenuPane popupMenu(this);
	
	// set nodes as user data to menu to get it in command handler
	popupMenu.setUserData(&nodes);

	// create menu commands
	if (dynamic_cast<FileSysNode*>(nodes[0]))
	{
		new FXMenuCommand(&popupMenu, "Extract File System", NULL, this, ID_EXTRACT_SYS);
	}

	if (dynamic_cast<TrackNode*>(nodes[0]))
	{
		new FXMenuCommand(&popupMenu, "Extract Track(s)", NULL, this, ID_EXTRACT_TRACK);
	}
	
	if (dynamic_cast<FileNode*>(nodes[0]) ||
		dynamic_cast<DirectoryNode*>(nodes[0]))
	{
		new FXMenuCommand(&popupMenu, "Extract Content", NULL, this, ID_EXTRACT_FILE);
	}

	if (dynamic_cast<FileNode*>(nodes[0]))
	{
		new FXMenuCommand(&popupMenu, "Extract Files Ex (Compress / Encrypted)", NULL, this, ID_EXTRACT_FILE_EX);
	}

	if (dynamic_cast<FileNode*>(nodes[0]))
	{
		new FXMenuCommand(&popupMenu, "Check if source is compressed and/or encrypted", NULL, this, ID_VERIFY_DISCTYPE);
	}

	

	if (dynamic_cast<DirectoryNode*>(nodes[0]) ||
		dynamic_cast<FileSysNode*>(nodes[0]))
	{
		new FXMenuCommand(&popupMenu, "List Content", NULL, this, ID_LIST_CONTENT);
	}

	if (nodes.size() == 1)
	{
		new FXMenuCommand(&popupMenu, "Sector View", NULL, this, ID_SECTOR_VIEW);
		new FXMenuCommand(&popupMenu, "Scan Sectors", NULL, this, ID_SCAN_SECTORS);
		// property command is available for all nodes
		new FXMenuCommand(&popupMenu, "Properties", NULL, this, ID_SHOW_PROPERTIES);

		if (dynamic_cast<TrackNode*>(nodes[0]) && 
			dynamic_cast<TrackNode*>(nodes[0])->getGenericInfo().icon == 
			GenericInfo::ICON_TRACK_AUDIO)
		{
			new FXMenuCommand(&popupMenu, "Play", NULL, this, ID_PLAY);
			new FXMenuCommand(&popupMenu, "Grab Audio", NULL, this, ID_GRAB);
			new FXMenuCommand(&popupMenu, "Read CD-Text", NULL, this, ID_READ_CDTEXT);
			new FXMenuCommand(&popupMenu, "Read Indexes", NULL, this, ID_READ_INDEXES);
			new FXMenuCommand(&popupMenu, "Read ISRC", NULL, this, ID_READ_ISRC);
		}		
	}

	// if menu is not empty - show it
	if (popupMenu.getFirst())
	{
		// create menu and show
		popupMenu.create();
		popupMenu.popup(NULL, x, y);
		getApp()->runModalWhileShown(&popupMenu);
	}
}

FXuint KImageEditFOXLibDlg::doExtraction(int16 nTrackNumber, const FXString& strFilePath, unsigned int nFileFormat)
{
	KSaveTrackDialog dlg(this, nTrackNumber, strFilePath, nFileFormat);
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	return dlg.execute();	
}

long KImageEditFOXLibDlg::onMountImage(FXObject* sender, FXSelector key, void* data)
{
	FXFileDialog fileDlg(this, "Select Image File");
	fileDlg.setPatternList(DLG_IMAGES_PATTERN);
	fileDlg.setSelectMode(SELECTFILE_ANY);


	if (fileDlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(fileDlg.getDirectory());
		FXString filename = FXString::compose(fileDlg.getFilename(), false);
		
		KString strTmpName = Fox2SDKString(filename);

		int32 res = ::SetImageFilePath(strTmpName);
		handleError(res);

		if (m_chkDisableImage->getCheck() == false)
		{
			m_cmbDevice->setCurrentItem(0);
			onDeviceBox(sender, key, data);
		}
		else
		{	
			FXint ind = m_cmbDevice->findItem(">", -1, SEARCH_FORWARD|SEARCH_PREFIX);
			if (ind != -1)	m_cmbDevice->removeItem(ind);
			m_cmbDevice->appendItem("> " + filename);
			m_cmbDevice->setNumVisible(m_cmbDevice->getNumItems());
			m_cmbDevice->setCurrentItem(m_cmbDevice->getNumItems() - 1, true);
		}

		return (res == BS_SDK_ERROR_NO) ? 1 : 0;
	}
	else
	{
		return 0;
	}
}

long KImageEditFOXLibDlg::onUnmountImage(FXObject* sender, FXSelector key, void* data)
{
	::SetImageFilePath(NULL);

	FXint indx = m_cmbDevice->getCurrentItem();

	if (-1 < indx)
	{
		FXString strItem = m_cmbDevice->getItemText(indx);
		KString strDevice = Fox2SDKString(strItem.left(1));

		if (strDevice == '#' || strDevice == '>')
		{
			onDeviceBox(sender, key, data);
		}
	}

	return 1;
}

long KImageEditFOXLibDlg::onSaveDisc(FXObject* sender, FXSelector key, void* data)
{
	int16 nFormat = BS_IMG_BIN;
	FXString strExtension = ".bin";
	FXString strPatternList = "BIN files (*.bin)";
	
	int16 nImageFormats;
	::GetPossibleImageFormats(&nImageFormats);

	if (!nImageFormats)
	{
		FXMessageBox::error(this, MBOX_OK, "Saving image", "Disc is incorrect or no disc is inserted.");
		return 1;
	}
	
	if (nImageFormats & BS_IMG_ISO)
	{	
		strPatternList += "\nISO files (*.iso)";
	}

	FXFileDialog FileDialog(this, "Choose file to save disk image");
	FileDialog.setPatternList(strPatternList);
	FileDialog.setSelectMode(SELECTFILE_ANY);
	
	if(!FileDialog.execute(PLACEMENT_SCREEN))
	{
		return 1;
	}
	
	FX::FXSystem::setCurrentDirectory(FileDialog.getDirectory());

	FXString strFileName = FXString::compose(FileDialog.getFilename(), false);

	if (FileDialog.getCurrentPattern() == 1)
	{
		strExtension = ".iso";
		nFormat = BS_IMG_ISO;
	}

	if ("" == FXPath::extension(strFileName))
	{
		strFileName += strExtension;
	}

	KSaveDiscDialog dlg(this, strFileName, nFormat);
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();
	return 1;
}

long KImageEditFOXLibDlg::onWriteLogFile(FXObject* sender, FXSelector key, void* data)
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(KString(m_strStartupDir.text()) + PATHSEPSTRING + "FoxSampleImageEditW.log");
	return 1;
}

long KImageEditFOXLibDlg::onVerifyDisc(FXObject* sender, FXSelector key, void* data)
{
	NodeList nodes;

	FXTreeItem *rootItem = m_leftPanel->getFirstItem();
	
	
	FXTreeItem *sessionItem = rootItem->getFirst();

	while (sessionItem)
	{
		FXTreeItem *trackItem = sessionItem->getFirst();

		while (trackItem)
		{
			FXTreeItem *fsysItem = trackItem->getFirst();

			while (fsysItem)
			{
				nodes.push_back((ITreeNode*)fsysItem->getData());

				fsysItem = fsysItem->getNext();
			}

			trackItem = trackItem->getNext();
		}

		sessionItem = sessionItem->getNext();
	}

	KSaveContentDialog::SSaveContentParams params(KSaveContentDialog::AIM_VERIFY, nodes);
	KSaveContentDialog dlg(params, this);
	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();

	return 1;
}

long KImageEditFOXLibDlg::onPlay(FXObject* sender, FXSelector key, void* data)
{
	TrackNode *pcTrackNode = 0;

	// First, try the right panel
	FXint indx_r = m_rightPanel->getCurrentItem();

	if(indx_r != -1)
	{
		// If item is selected
		if (m_rightPanel->isItemSelected(indx_r))
		{
			ITreeNode* node = (ITreeNode*)m_rightPanel->getItemData(indx_r);
			// Check if it is TrackNode
			pcTrackNode = dynamic_cast<TrackNode*>(node);
		}
	}

	// No track nodes are selected at right panel, so try left
	if (!pcTrackNode)
	{
		// Get selected item at the left panel
		FXTreeItem* item = m_leftPanel->getCurrentItem();
		if (item != NULL)
		{
			ITreeNode* node = (ITreeNode*)item->getData();
			// Check if it is TrackItem
			pcTrackNode = dynamic_cast<TrackNode*>(node);
		}		
	}

	// If audio trac track is selected
	if (pcTrackNode && pcTrackNode->getTrackInfo().nFormat == BS_TF_AUDIO)
	{
		const STrackInfo& cSTrackInfo = pcTrackNode->getTrackInfo();

		// Start playing selected track
		KPlayTrackDialog dlg(this, cSTrackInfo.nTrackNumber);
		dlg.setIcon(m_isosdkIconBig);
		dlg.setMiniIcon(m_isosdkIconSmall);
		dlg.execute();
	}
	
	return 1;
}

long KImageEditFOXLibDlg::onGrab(FXObject* sender, FXSelector key, void* data)
{
	TrackNode *pcTrackNode = 0;

	// First, try the right panel
	FXint indx_r = m_rightPanel->getCurrentItem();

	// If item is selected
	if (m_rightPanel->isItemSelected(indx_r))
	{
		ITreeNode* node = (ITreeNode*)m_rightPanel->getItemData(indx_r);
		// Check if it is TrackNode
		pcTrackNode = dynamic_cast<TrackNode*>(node);
	}

	// No track nodes are selected at right panel, so try left
	if (!pcTrackNode)
	{
		// Get selected item at the left panel
		FXTreeItem* item = m_leftPanel->getCurrentItem();
		if (item != NULL)
		{
			ITreeNode* node = (ITreeNode*)item->getData();
			// Check if it is TrackItem
			pcTrackNode = dynamic_cast<TrackNode*>(node);
		}		
	}

	// If audio trac track is selected
	if (pcTrackNode && pcTrackNode->getTrackInfo().nFormat == BS_TF_AUDIO)
	{
		// Start playing selected track
		const STrackInfo& cSTrackInfo = pcTrackNode->getTrackInfo();

		// Make the vector of tracks to grab
		std::vector<int32> vTracks;
		vTracks.push_back(cSTrackInfo.nTrackNumber);

		// Invoke audio grabbing dialog
		KAudioGrabbingDialog dlgGrab(this, vTracks);
		dlgGrab.setIcon(m_isosdkIconBig);
		dlgGrab.setMiniIcon(m_isosdkIconSmall);
		dlgGrab.execute();		
	}

	return 1;
}

long KImageEditFOXLibDlg::onGrabAll(FXObject* sender, FXSelector key, void* data)
{
	TrackNode *pcTrackNode = 0;
	std::vector<int32> vTracks;

	FXTreeItem *rootItem = m_leftPanel->getFirstItem();	
	FXTreeItem *sessionItem = rootItem->getBelow();

	while (sessionItem)
	{
		FXTreeItem *trackItem = sessionItem->getBelow();

		while (trackItem)
		{
			ITreeNode* node = (ITreeNode*)trackItem->getData();

			trackItem = trackItem->getNext();
		
			if (node == 0)
			{
				continue;
			}

			pcTrackNode = dynamic_cast<TrackNode*>(node);

			if (pcTrackNode)
			{
				if (dynamic_cast<TrackNode*>(node)->getGenericInfo().icon == 
					GenericInfo::ICON_TRACK_AUDIO)
				{
					const STrackInfo& cSTrackInfo = pcTrackNode->getTrackInfo();
					vTracks.push_back(cSTrackInfo.nTrackNumber);
				}
			}
		}

		sessionItem = sessionItem->getNext();
	}
			

	if (vTracks.size() > 0)
	{
		KAudioGrabbingDialog dlg(this, vTracks);
		dlg.setIcon(m_isosdkIconBig);
		dlg.setMiniIcon(m_isosdkIconSmall);
		dlg.execute();			
	}

	return 1;
}

FXString KImageEditFOXLibDlg::getCurrentImagePath() const
{
	int32 nLength = 0;
	::GetImageFilePath(NULL, &nLength);

	KString strPath;
	::GetImageFilePath(strPath.GetBuffer(nLength), &nLength);
	strPath.ReleaseBuffer();

	return SDK2FoxString((const TCHAR*)strPath);
}


int32 KImageEditFOXLibDlg::ExtractTextFromHandle(int32 handle, int32 nTrackNumber, int32 nCDTCI, KString& rText)
{
	int32 nLen = 0;
	int32 res;

	handleError(res = ::GetCDTextTrackTagString(handle, nTrackNumber, nCDTCI, 0, &nLen));
	if(res != BS_SDK_ERROR_NO)
	{
		return res;
	}

	if(!nLen || nLen == 1)
	{
		rText = L"";
		return BS_SDK_ERROR_NO;
	}

	TCHAR *pBuf = new TCHAR[nLen];
	handleError(res = ::GetCDTextTrackTagString(handle, nTrackNumber, nCDTCI, pBuf, &nLen));
	if(res != BS_SDK_ERROR_NO)
	{
		delete pBuf;
		return res;
	}

	pBuf[nLen-1] = _T('\0');
	rText = KString(pBuf);
	delete pBuf;
	return BS_SDK_ERROR_NO;
}

long KImageEditFOXLibDlg::onReadISRC(FXObject* sender, FXSelector key, void* data)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();

	if(nodes.empty())
	{
		return 0;
	}
	
	TrackNode* pcTrackNode = 0;
	pcTrackNode = dynamic_cast<TrackNode*>(nodes[0]);

	if(!pcTrackNode)
	{
		return 0;
	}

	int32 nTrackNumber = (int32) pcTrackNode->getTrackInfo().nTrackNumber;

	int32 res;
	TCHAR strISRC[13];
	handleError(res = ::GetTrackISRC(BS_READ_DEVICE, nTrackNumber, strISRC));
	if(res != BS_SDK_ERROR_NO)
	{
		return 0;
	}
	
	strISRC[12] = TCHAR(0);

	FXMessageBox mb(this, "Track ISRC", FXString(strISRC), m_isosdkIconSmall, MBOX_OK);
	mb.execute();

	return 0;
}

long KImageEditFOXLibDlg::onReadIndexes(FXObject* sender, FXSelector key, void* data)
{
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();

	if(nodes.empty())
	{
		return 0;
	}
	
	TrackNode* pcTrackNode = 0;
	pcTrackNode = dynamic_cast<TrackNode*>(nodes[0]);

	if(!pcTrackNode)
	{
		return 0;
	}

	int32 nTrackNumber = (int32) pcTrackNode->getTrackInfo().nTrackNumber;

	const int32 max = 100;
	std::vector<int32> Indexes(max);
	int32 nInd  = max;
	int32 res;
	handleError(res = ::GetTrackIndexes(BS_READ_DEVICE, nTrackNumber, &(Indexes[0]), &nInd));
	if(res != BS_SDK_ERROR_NO)
	{
		return 0;
	}

	if(nInd <= 1)
	{
		return 0;
	}

	FXString text, tmp;
	text = "";
	for(int i = 0; (i < nInd) && (i < 10); ++i)
	{
		tmp.format("Index %d : %d\n", i, Indexes[i]);
		text += tmp;
	}

	if(nInd >= 10)
	{
		text += "...\nToo many indexes";
	}

	tmp.format("\nPause length: %d", Indexes[1] - Indexes[0]);
	text += tmp;
	FXMessageBox mb(this, "Track indexes", text, m_isosdkIconSmall, MBOX_OK);
	mb.execute();

	return 0;
}

long KImageEditFOXLibDlg::onReadCDText(FXObject* sender, FXSelector key, void* data)
{	
	NodeList& nodes = *(NodeList*)((FXMenuCommand*)sender)->getParent()->getUserData();

	if(nodes.empty())
	{
		return 0;
	}
	
	TrackNode* pcTrackNode = 0;
	pcTrackNode = dynamic_cast<TrackNode*>(nodes[0]);

	if(!pcTrackNode)
	{
		return 0;
	}

	int32 nTrackNumber = (int32) pcTrackNode->getTrackInfo().nTrackNumber;

	KString strArranger,
			strComposer,
			strSongWriter,
			strPerformer,
			strMessage,
			strTitle;

	int32 hCdText;
	
	int32 res;

	handleError(res = ::ReadCDText(BS_READ_DEVICE, &hCdText));
	if(res != BS_SDK_ERROR_NO)
	{
		return 0;
	}

	handleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_ARRANGER, strArranger));
	handleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_COMPOSER, strComposer));
	handleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_MESSAGE, strMessage));
	handleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_PERFORMER, strPerformer));
	handleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_SONG_WRITER, strSongWriter));
	handleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_TITLE, strTitle));

	handleError(res = ::CloseCDTextHandle(hCdText));
	if(res != BS_SDK_ERROR_NO)
	{
		return 0;
	}


	KReadCDTextDlg dlg(getApp(), "CD Text",
		SDK2FoxString((const wchar_t*)strArranger),
		SDK2FoxString((const wchar_t*)strComposer),
		SDK2FoxString((const wchar_t*)strSongWriter),
		SDK2FoxString((const wchar_t*)strPerformer),
		SDK2FoxString((const wchar_t*)strMessage),
		SDK2FoxString((const wchar_t*)strTitle)		
		);

	dlg.setIcon(m_isosdkIconBig);
	dlg.setMiniIcon(m_isosdkIconSmall);
	dlg.execute();
	
	return 1;
}

long KImageEditFOXLibDlg::onRefresh(FXObject* sender, FXSelector key, void* data)
{
	reloadLeftPanel();
	return 1;
}
