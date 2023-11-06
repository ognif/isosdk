#include "stdafx.h"
#include "RawFOXLibDlg.h"
#include "../Common/SampleBurnDlg.h"
#include "../Common/AboutDlg.h"
#include "../Common/CommonFoxLib.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <cassert>

#define WEBSITELINK			"http://www.isosdk.com"


inline FXString int2str(int32 i)
{
    char buf[30];
	sprintf(buf,"%d",i);
	return FXString(buf);
}

// See definition later

// Default vertical and horizontal tabs for buttons and other controls.S
const int VERTICAL_TAB = 5;
const int HORIZONTAL_TAB = 10;

inline FXint pointerToInt(void* voidVal)
{
	return *(FXint*)(&voidVal);
}

class KMaskList : public FXGroupBox
{
public:
	KMaskList(FXComposite* owner)
		:FXGroupBox(owner,"", LAYOUT_FILL_X|LIST_SINGLESELECT)
	{
		new FXCheckButton(this, "BS_RDT_SYNC_HEADER", 0, BS_RDT_SYNC_HEADER);
		new FXCheckButton(this, "BS_RDT_SUBHEADERS", 0, BS_RDT_SUBHEADERS);
		new FXCheckButton(this, "BS_RDT_DATA", 0, BS_RDT_DATA);
		new FXCheckButton(this, "BS_RDT_EDC_ECC", 0, BS_RDT_EDC_ECC);
		new FXCheckButton(this, "BS_RDT_SUBCH_PQ", 0, BS_RDT_SUBCH_PQ);
		new FXCheckButton(this, "BS_RDT_SUBCH_PW", 0, BS_RDT_SUBCH_PW);
		new FXCheckButton(this, "BS_RDT_SUBCH_RW", 0, BS_RDT_SUBCH_RW);
	}

	void setMask(int32 mask)
	{
		FXCheckButton* it = dynamic_cast<FXCheckButton*>(this->getFirst());
		while(it)
		{
			it->setCheck(mask & it->getSelector() ? true : false);
			it = dynamic_cast<FXCheckButton*>(it->getNext());
		}
	}

	int32 getMask()
	{
		int32 mask = 0;
		FXCheckButton* it = dynamic_cast<FXCheckButton*>(this->getFirst());
		while(it)
		{
			if (it->getCheck())
			{
				mask |= it->getSelector();
			}
			it = dynamic_cast<FXCheckButton*>(it->getNext());
		}
		return mask;
	}
};




int32 Format2SectorSize(int8 nFormat)
{
	if (nFormat == BS_RTF_MODE1)
	{
		return 2048;
	}

	return 2352;
}

//MESSAGE MAP

FXDEFMAP(KRawFOXLibDlg) KDataFOXLibMap[]= {
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_ADDFILE, KRawFOXLibDlg::onAddFile),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_WRITELOG, KRawFOXLibDlg::onWriteLogFile),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_ANALYZEFILE, KRawFOXLibDlg::onAnalyzeFile),
   	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_ADD_TRACK, KRawFOXLibDlg::onAddTrack),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_DELETE_TRACK, KRawFOXLibDlg::onDeleteTrack),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_RESETLIST, KRawFOXLibDlg::onResetList),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_RESET_FORM, KRawFOXLibDlg::onResetForm),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_BURNDISK_DEVELOPED, KRawFOXLibDlg::onBurnDiskDeveloped),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_BURNDISK_FOXBURNER, KRawFOXLibDlg::onBurnDiskFoxBurner),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_ERASEDISK, KRawFOXLibDlg::onEraseDisk),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_MOUNTIMAGE, KRawFOXLibDlg::onMountImage),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_UNMOUNTIMAGE, KRawFOXLibDlg::onUnmountImage),
	FXMAPFUNCS(SEL_COMMAND,KRawFOXLibDlg::ID_ASPI_INTERNAL, KRawFOXLibDlg::ID_ASPI_FROGASPI, KRawFOXLibDlg::onCmdAspi),
	FXMAPFUNCS(SEL_UPDATE, KRawFOXLibDlg::ID_ASPI_INTERNAL, KRawFOXLibDlg::ID_ASPI_FROGASPI, KRawFOXLibDlg::onUpdAspi),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_RESCANDEVICES, KRawFOXLibDlg::onRescanDevices),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_BURNDEVICES, KRawFOXLibDlg::onBurningDevices),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_DISABLEIMAGE, KRawFOXLibDlg::onDisableImagewriter),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_ABOUT, KRawFOXLibDlg::onAbout),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_WEB, KRawFOXLibDlg::onWeb),
	FXMAPFUNC(SEL_COMMAND, KRawFOXLibDlg::ID_DEVICEBOX, KRawFOXLibDlg::onDeviceBox),
	FXMAPFUNC(KRawFOXLibDlg::SEL_ERRORNOTIFY, 0, KRawFOXLibDlg::onErrorNotify),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KRawFOXLibDlg::onCmdCancel),
	FXMAPFUNC(SEL_CLOSE, 0, KRawFOXLibDlg::onCmdCancel)
};

FXIMPLEMENT(KRawFOXLibDlg, FXDialogBox, KDataFOXLibMap, ARRAYNUMBER(KDataFOXLibMap))

KRawFOXLibDlg::KRawFOXLibDlg(FXApp *app, const FXString &title)
	: FXDialogBox(app, title, DECOR_ALL, 0, 0, 700, 600, 0, 0, 0, 0, 0, 0)		
	, m_bBurningDevicesOnly(true)
	
{

	//Clear m_vTracks.
	m_vTracks.clear();
	
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

	FXMenuBar *menubar = new FXMenuBar(this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X);

	FXMenuPane *filemenu = new FXMenuPane(this);
		new FXMenuCommand(filemenu,"&Add File...", fileAddIcon, this, ID_ADDFILE);
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"Write Log", NULL, this, ID_WRITELOG);
		new FXHorizontalSeparator(filemenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(filemenu,"E&xit", cancelIcon, this, FXDialogBox::ID_CANCEL);
	new FXMenuTitle(menubar, "&File", NULL, filemenu);

	FXMenuPane *trackmenu = new FXMenuPane(this);
		new FXMenuCommand(trackmenu,"Try to Analyze File",0,this,ID_ANALYZEFILE);
		new FXHorizontalSeparator(trackmenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		new FXMenuCommand(trackmenu,"Add Track",0,this,ID_ADD_TRACK);
		new FXMenuCommand(trackmenu,"Reset Tracklist",0,this,ID_RESETLIST);
	new FXMenuTitle(menubar, "&Tracks", NULL, trackmenu);


	FXMenuPane *burnmenu = new FXMenuPane(this);
		new FXMenuCommand(burnmenu,"&Burn with custom dialog...", burnIcon, this, ID_BURNDISK_DEVELOPED);
		new FXMenuCommand(burnmenu,"Burn with &IsoSDK Embedded Dialog...", burnIcon, this, ID_BURNDISK_FOXBURNER);
		new FXMenuCommand(burnmenu,"&Erase Disc...", eraseIcon, this, ID_ERASEDISK);
		new FXHorizontalSeparator(burnmenu, LAYOUT_FILL_X|SEPARATOR_GROOVE);
		FXMenuPane *optionsmenu = new FXMenuPane(this);
			m_chkEjectAfterBurn = new FXMenuCheck(optionsmenu,"&Eject Disc", &m_tgtEjectAfterBurn, FXDataTarget::ID_VALUE);
			m_chkVerify = new FXMenuCheck(optionsmenu,"&Verify after burn", &m_tgtVerifyAfterBurn, FXDataTarget::ID_VALUE);
			m_chkJoliet = new FXMenuCheck(optionsmenu,"&Joliet File System", &m_tgtJoliet, FXDataTarget::ID_VALUE);
			m_chkFinalize = new FXMenuCheck(optionsmenu,"&Finalize", &m_tgtFinalize, FXDataTarget::ID_VALUE);
		new FXMenuCascade(burnmenu, "&Options", NULL, optionsmenu);
	new FXMenuTitle(menubar, "&Burn", NULL, burnmenu);

	FXMenuPane* aspimenu = new FXMenuPane(this);
		FXMenuPane* interfacemenu = new FXMenuPane(this);
			new FXMenuRadio(interfacemenu, "&Internal", this, ID_ASPI_INTERNAL);
			new FXMenuRadio(interfacemenu, "&WnAspi", this, ID_ASPI_WNASPI);
			new FXMenuRadio(interfacemenu, "&FrogAspi", this, ID_ASPI_FROGASPI);
		new FXMenuCascade(aspimenu, "&Interface", NULL, interfacemenu);
		new FXMenuCommand(aspimenu,"&Rescan Devices", refreshIcon, this, ID_RESCANDEVICES);
		FXMenuCheck* burnDevicesOnly = new FXMenuCheck(aspimenu,"&Burn devices only", this, ID_BURNDEVICES);
		new FXMenuCheck(aspimenu,"Disable &Imagewriter", this, ID_DISABLEIMAGE);
	new FXMenuTitle(menubar, "A&SPI/SPTI", NULL, aspimenu);

	FXMenuPane* infomenu = new FXMenuPane(this);
		new FXMenuCommand(infomenu, "&About", NULL, this, ID_ABOUT);
		new FXMenuCommand(infomenu, "&Web", NULL, this, ID_WEB);
	new FXMenuTitle(menubar, "I&nformation", NULL, infomenu);

	// Device combo
	// Commented to add FXGroupBox instead of frame;
	// FXHorizontalFrame *deviceFrame = new FXHorizontalFrame(this, LAYOUT_FILL_X);
	//	new FXLabel(deviceFrame, "Device: ", NULL, JUSTIFY_LEFT|LAYOUT_FIX_WIDTH, 0, 0, 70);
	
	FXVerticalFrame *contents = new FXVerticalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	FXGroupBox *devicesGroupBox = new FXGroupBox(contents,"Devices",LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_THICK);
		m_cmbDevice = new FXComboBox(devicesGroupBox, 30, this, ID_DEVICEBOX, LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC, 200);

	FXGroupBox *addFileGroupBox = new FXGroupBox(contents,"Add File",LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_THICK);
		FXHorizontalFrame *horizontalFrameInGroupBox = new FXHorizontalFrame(addFileGroupBox,LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
			m_cmbAddFile = new FXComboBox(horizontalFrameInGroupBox,0,0,0,COMBOBOX_NORMAL|LAYOUT_FILL_X|FRAME_NORMAL);
			m_cmbAddFile->setEditable(false);
			m_cmbAddFile->disable();
			FXButton *browseButton = new FXButton(horizontalFrameInGroupBox,"...",0,this,ID_ADDFILE);
			FXButton *tryToAnalyzeButton = new FXButton(horizontalFrameInGroupBox,"Try to Analyze",0,this,ID_ANALYZEFILE,BUTTON_NORMAL,0,0,0,0,HORIZONTAL_TAB,HORIZONTAL_TAB,VERTICAL_TAB,VERTICAL_TAB);
			tryToAnalyzeButton->setHeight(30);

	// TRACK SETTINGS
	
	FXGroupBox *trackSettingsGroupBox = new FXGroupBox(contents,"Track Settings",LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_THICK);
		FXVerticalFrame *trackVerticalFrame=new FXVerticalFrame(trackSettingsGroupBox);
			FXHorizontalFrame *trackHorizontalFrame=new FXHorizontalFrame(trackVerticalFrame);
		
				FXMatrix *leftMatrix = new FXMatrix(trackHorizontalFrame, 2, MATRIX_BY_COLUMNS);
					FXHorizontalFrame *trackNumberFrame=new FXHorizontalFrame(leftMatrix);
						FXLabel *trackNumberLabel=new FXLabel(trackNumberFrame,"Track Number:");	
						m_spnrTrackNumber = new FXSpinner(trackNumberFrame, 1, 0, 0, SPIN_NORMAL | FRAME_SUNKEN|FRAME_THICK, 0, 0, 0, 0,15);
						m_spnrTrackNumber->setRange(1,99);
						//m_listboxTrackNumber = new FXListBox (trackNumberFrame, 0, 0, FRAME_SUNKEN|FRAME_THICK|LISTBOX_NORMAL, 0, 0, 0,0,15);//, FXint h=0, FXint pl=DEFAULT_PAD, FXint pr=DEFAULT_PAD, FXint pt=DEFAULT_PAD, FXint pb=DEFAULT_PAD
					FXHorizontalFrame *trackIndexFrame = new FXHorizontalFrame(leftMatrix);
						FXLabel *trackIndexLabel = new FXLabel(trackIndexFrame,"Track Index (0-pregap,1-track):");	
						m_spnrTrackIndex = new FXSpinner(trackIndexFrame, 1, 0, 0, SPIN_NORMAL | FRAME_SUNKEN|FRAME_THICK, 0, 0, 0, 0,15);//, FXint pr=DEFAULT_PAD, FXint pt=DEFAULT_PAD, FXint pb=DEFAULT_PAD)
						m_spnrTrackIndex->setRange(0,1);
					FXLabel *datatypeMaskLabel=new FXLabel(leftMatrix,"Datatype Mask:");
					FXVerticalFrame* listframe1=new FXVerticalFrame(leftMatrix,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
						m_listDatatypeMask = new KMaskList(listframe1);
					FXLabel *startAdressLabel=new FXLabel(leftMatrix,"Start Adress (sectors):");

					m_txtfieldStartAddress = new FXTextField(leftMatrix,10,0,0,TEXTFIELD_INTEGER|TEXTFIELD_NORMAL);
					FXLabel *trackLengthLabel=new FXLabel(leftMatrix,"Track Length (sectors):");

					m_txtfieldTrackLength = new FXTextField(leftMatrix,10,0,0,TEXTFIELD_INTEGER|TEXTFIELD_NORMAL);
					FXLabel *offsetLabel=new FXLabel(leftMatrix,"Offset (bytes):");		
					m_txtfieldOffset= new FXTextField(leftMatrix,10,0,0,TEXTFIELD_INTEGER|TEXTFIELD_NORMAL);

				FXMatrix *rightMatrix= new FXMatrix(trackHorizontalFrame);
				rightMatrix->setNumColumns(2);
				rightMatrix->setNumRows(3);
					FXLabel *trackModeLabel=new FXLabel(rightMatrix,"Track mode:");
					FXLabel *ignoreMaskLabel=new FXLabel(rightMatrix,"Ignore Mask:");
					FXLabel *rightEmptyLabel=new FXLabel(rightMatrix,"");

					m_cmbTrackMode=new FXComboBox(rightMatrix,30,0,0,COMBOBOX_NORMAL|LAYOUT_FILL_X|FRAME_NORMAL);
					fillModes(m_cmbTrackMode);
					m_cmbTrackMode->setNumVisible(m_cmbTrackMode->getNumItems());
					m_cmbTrackMode->setEditable(false);
					/*FXHorizontalFrame *ignoreMaskFrame=new FXHorizontalFrame(rightMatrix);
						m_cmbIgnoreMask=new FXComboBox(ignoreMaskFrame,20,0,0,COMBOBOX_NORMAL|LAYOUT_FILL_X|FRAME_NORMAL);
						fillMasks(m_cmbIgnoreMask);
						m_cmbIgnoreMask->setEditable(false);
						FXButton *includeIgnoreMaskButton = new FXButton(ignoreMaskFrame,">>",0,this,ID_INCLUDE_IGNOREMASK);*/
					FXVerticalFrame* listframe2=new FXVerticalFrame(rightMatrix,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
						m_listIgnoreMask = new KMaskList(listframe2);
    
					FXHorizontalFrame *horButtonFrame = new FXHorizontalFrame(trackVerticalFrame,LAYOUT_RIGHT|LAYOUT_BOTTOM|LAYOUT_FILL_X);
						FXButton *resetFormButton = new FXButton(horButtonFrame,"Reset form",0,this,ID_RESET_FORM,BUTTON_NORMAL,0,0,0,0,HORIZONTAL_TAB,HORIZONTAL_TAB,VERTICAL_TAB,VERTICAL_TAB);						
						FXButton *addTrackButton = new FXButton(horButtonFrame,"&Add track",0,this,ID_ADD_TRACK,LAYOUT_RIGHT|BUTTON_NORMAL,0,0,0,0,HORIZONTAL_TAB,HORIZONTAL_TAB,VERTICAL_TAB,VERTICAL_TAB);
						FXButton *deleteTrackButton = new FXButton(horButtonFrame,"&Delete track",0,this,ID_DELETE_TRACK,LAYOUT_RIGHT|BUTTON_NORMAL,0,0,0,0,HORIZONTAL_TAB,HORIZONTAL_TAB,VERTICAL_TAB,VERTICAL_TAB);


	//Table of tracks' summary
	m_tblTrack=new FXTable(contents,0,0,LAYOUT_FILL_X|LAYOUT_FILL_Y| TABLE_COL_SIZABLE);
	m_tblTrack->insertColumns(0,8);	
	m_tblTrack->setColumnText(0,"No.");
	m_tblTrack->setColumnText(1,"Ind.");
	m_tblTrack->setColumnText(2,"Mode");
	m_tblTrack->setColumnText(3,"DataMask");
	m_tblTrack->setColumnText(4,"IgnoreMask");
	m_tblTrack->setColumnText(5,"Start Address");
	m_tblTrack->setColumnText(6,"Length");
	m_tblTrack->setColumnText(7,"Offset");
	m_tblTrack->setColumnWidth(0,30);
	m_tblTrack->setColumnWidth(1,30);
	m_tblTrack->setRowHeaderMode(0); 	
	m_tblTrack->showHorzGrid(false);
	m_tblTrack->showHorzGrid(true);	

	//App's Icon.
	setMiniIcon(isosdkIconSmall);
	setIcon(isosdkIconBig);


	//Set startup directory
	m_strStartupDir = FXSystem::getCurrentDirectory();



	//Reset form's state;
	onResetForm(0,0,0);
}

void KRawFOXLibDlg::loadOwner()
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
	res = ::CreateProject(BS_BURNER_RAW, BS_CONTINUE_NO_SESSION);
	handleError(res);

	//--------------------------------------------------
	//Set the Options. Remember, not all Options are
	//available on all projects. Read Help
	//--------------------------------------------------

	SOptions opt;
	res = ::GetOptions(&opt);
	handleError(res);

	opt.bTestBurn = BS_FALSE;
	opt.bPerformOPC = BS_FALSE;
	opt.bJolietFileSystem = BS_TRUE;
	opt.bEjectAfterBurn = BS_TRUE;
	opt.nCacheSize = 4 * 1024 * 1024;
	opt.bFinalize = BS_FALSE;
	opt.bVerifyAfterBurn = BS_FALSE;

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	res = ::SetOptions(opt);
	handleError(res);

	// Update devices list
	updateDeviceCombo();

	// Connect targets and variables
	m_tgtEjectAfterBurn.connect(m_bEjectAfterBurn);
	m_tgtJoliet.connect(m_bJoliet);
	m_tgtFinalize.connect(m_bFinalize);
	m_tgtVerifyAfterBurn.connect(m_bEjectAfterBurn);

	//Sync flags and current state of options.
	m_bEjectAfterBurn = opt.bEjectAfterBurn;
	m_bJoliet = opt.bJolietFileSystem;
	m_bFinalize = opt.bFinalize;
	m_bVerify = opt.bVerifyAfterBurn;
}

//Default constructor
KRawFOXLibDlg::KRawFOXLibDlg()
{
}

//Destructor
KRawFOXLibDlg::~KRawFOXLibDlg()
{
	::DeInitialize();
}

int64 KRawFOXLibDlg::AddTrackInfo(int32 nNumber, int32 nIndex, int64 nDiskOffset, int8 nTrackFormat, STrackInfo sTrack)
{
	int32 nTrackListNumber = m_tblTrack->getNumRows();

	SRAWTrackToAdd rawTrack;
	rawTrack.nNumber = nNumber;
	rawTrack.nIndex = nIndex;
	rawTrack.nOffset = nDiskOffset;
	rawTrack.nStartAddress = sTrack.nStartLBA;
	rawTrack.nFormat = nTrackFormat;
	rawTrack.nDataTypeMask = BS_RDT_DATA;
	rawTrack.nIgnoreDataMask = 0;
	rawTrack.nLength = sTrack.nSize;
	

	switch(nTrackFormat)
	{
		case BS_RTF_MODE2_FORM1:
			rawTrack.nDataTypeMask   |= BS_RDT_SUBHEADERS|BS_RDT_EDC_ECC;
			rawTrack.nIgnoreDataMask |= BS_RDT_EDC_ECC;
			break;

		case BS_RTF_MODE2_FORM2:
			rawTrack.nDataTypeMask   |= BS_RDT_SYNC_HEADER|BS_RDT_SUBHEADERS|BS_RDT_EDC_ECC;
			rawTrack.nIgnoreDataMask |= BS_RDT_SYNC_HEADER|BS_RDT_EDC_ECC;
			break;
	}

	//add to vector
	m_vTracks.push_back(rawTrack);


	FXString itemBuilder;

	m_tblTrack->insertRows(nTrackListNumber, 1);
		
	itemBuilder = "";
	itemBuilder.format("%d", rawTrack.nNumber);
	m_tblTrack->setItemText(nTrackListNumber, 0, itemBuilder);

	itemBuilder = "";
	itemBuilder.format("%d", rawTrack.nIndex);
	m_tblTrack->setItemText(nTrackListNumber, 1, itemBuilder);
	
	m_tblTrack->setItemText(nTrackListNumber, 2, getMode<FXString>(rawTrack.nFormat));
	m_tblTrack->setItemText(nTrackListNumber, 3, getMask<FXString>(rawTrack.nDataTypeMask));
	m_tblTrack->setItemText(nTrackListNumber, 4, getMask<FXString>(rawTrack.nIgnoreDataMask));

	itemBuilder = "";
	itemBuilder.format("%d", rawTrack.nStartAddress);
	m_tblTrack->setItemText(nTrackListNumber, 5, itemBuilder);

	itemBuilder = "";
	itemBuilder.format("%d", rawTrack.nLength);
	m_tblTrack->setItemText(nTrackListNumber, 6, itemBuilder);

	itemBuilder= "";
	itemBuilder.format("%d", rawTrack.nOffset);
	m_tblTrack->setItemText(nTrackListNumber, 7, itemBuilder);
	
	nDiskOffset += (int64)rawTrack.nLength * Format2SectorSize(rawTrack.nFormat);
	
	itemBuilder= "";
	itemBuilder.format("%d", nNumber + 1);
	//edTrackNo.SetWindowText(itemBuilder);

	return nDiskOffset;
}

void KRawFOXLibDlg::updateDeviceCombo()
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

long KRawFOXLibDlg::onWriteLogFile(FXObject* sender, FXSelector key, void* data)
{
	::SaveLogToFile(KString(m_strStartupDir.text()) + PATHSEPSTRING + "FoxSampleRawC.log");	
	return 1;
}

//Add datasource file to project
long KRawFOXLibDlg::onAddFile(FXObject* sender, FXSelector key, void* data)
{
	FXString file= FXFileDialog::getOpenFilename(this,"Add File...","");//, const FXString &path, const FXString &patterns="*", FXint initial=0)
	if(file=="")
	{	
		return 1;
	}
    KString strTmpSourcePath = Fox2SDKString(FXString::compose(file, false));
	SFileToAdd	fileToAdd;
	fileToAdd.lpszSourceFilePath=strTmpSourcePath;

	int32 res = ::ClearAll();
	handleError(res);

	res = ::AddFile(fileToAdd);
	handleError(res);
	if(res==0)
	{
        insertUnique(m_cmbAddFile,file);		
	}
	return 1;
}

//Analyze image file.
long KRawFOXLibDlg::onAnalyzeFile(FXObject* sender, FXSelector key, void* data)
{
	
	if(0 == m_cmbAddFile->getNumItems())
	{
		FXMessageBox::information(this,MBOX_OK,"Information","File not selected.");
		return 1;
	}

    FXString fxstrFileName = m_cmbAddFile->getItem(m_cmbAddFile->getCurrentItem());
	if(true == fxstrFileName.empty())
	{
		FXMessageBox::information(this,MBOX_OK,"Information","File name is empty.");
		return 1;
	}

	onResetForm(0, 0, 0);
	onResetList(0, 0, 0);

	KString kstrFileName = Fox2SDKString(FXString::compose(fxstrFileName, false));
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	SFileToAdd	fileToAdd;			
	fileToAdd.lpszSourceFilePath = (const TCHAR*)(kstrFileName);

	int32 res = ::AddFile(fileToAdd);
	handleError(res);						

    int64 nDiskOffset = 0;
	int32 nCurrentLastSector = 0;

	res = ::SetImageFilePath(fileToAdd.lpszSourceFilePath);
	handleError(res);

	if (res != BS_SDK_ERROR_NO)
	{
		return 0;
	}

	res = ::SetReadDevice(KString(_T('#')));
	handleError(res);

	if (res != BS_SDK_ERROR_NO)
	{
		return 0;
	}
	
	SMediumInfo mi;
	res = ::GetMediumInformation(BS_READ_DEVICE, &mi);
	handleError(res);

	//First pregap (-150) analize

	nDiskOffset = 0;

	if (mi.nFirstSession > 0 && mi.nLastSession > 0)
	{
		for (int32 i = mi.nFirstSession; i <= mi.nLastSession; i++)
		{
			SSessionInfo si;
			res = ::GetSessionInformation(BS_READ_DEVICE, i, &si);
			handleError(res);

			for(int32 j = si.nFirstTrack; j <= si.nLastTrack; ++j)
			{
				STrackInfo cTrackInfo;
				res = ::GetTrackInformation(BS_READ_DEVICE, j, &cTrackInfo);
				handleError(res);

				nDiskOffset += (int64)cTrackInfo.nSize * Format2SectorSize(cTrackInfo.nFormat);
			}
		}
#if _MSC_VER < 1400
		__stat64 devStat;
#else
		struct _stat64 devStat;
#endif
		if (0 != _tstat64(kstrFileName, &devStat))
		{	
			return 0;
		}
		
		if (nDiskOffset < devStat.st_size)
		{
			//need first pregap
			nCurrentLastSector = -150;
		}
	}

	nDiskOffset = 0;

	int nTrackNumber = m_tblTrack->getNumRows() + 1;

	if (mi.nFirstSession > 0 && mi.nLastSession > 0)
	{
		for (int32 i = mi.nFirstSession; i <= mi.nLastSession; i++)
		{
			SSessionInfo si;
			res = ::GetSessionInformation(BS_READ_DEVICE, i, &si);
			handleError(res);

			for(int32 j = si.nFirstTrack; j <= si.nLastTrack; ++j)
			{
				STrackInfo cTrackInfo;
				res = ::GetTrackInformation(BS_READ_DEVICE, j, &cTrackInfo);
				handleError(res);

				int8 nTrackFormat;
				res = ::GetTrackFormatEx(BS_READ_DEVICE, j, &nTrackFormat);
				handleError(res);

				if (nCurrentLastSector != cTrackInfo.nStartLBA)
				{
					STrackInfo cPregapInfo;
					
					cPregapInfo.nFormat = cTrackInfo.nFormat;
					cPregapInfo.nStartLBA = nCurrentLastSector;
					cPregapInfo.nSize = cTrackInfo.nStartLBA - nCurrentLastSector;

					nDiskOffset = AddTrackInfo(nTrackNumber, 0, nDiskOffset, nTrackFormat, cPregapInfo);
				}
		
				nDiskOffset = AddTrackInfo(nTrackNumber, 1, nDiskOffset, nTrackFormat, cTrackInfo);

				nCurrentLastSector = cTrackInfo.nStartLBA + cTrackInfo.nSize;

				++nTrackNumber;
			}
		}
	}

	res = ::SetImageFilePath(_T(""));
	handleError(res);
			
	return 1;
}

//Reset table of tracks.
long KRawFOXLibDlg::onResetList(FXObject* sender, FXSelector key, void* data)
{
	::ClearAll();

	m_cmbAddFile->clearItems();

	m_vTracks.clear();
	
	m_tblTrack->removeRows(0, m_tblTrack->getNumRows());

	onResetForm(0,0,0);

	return 1;
}

long KRawFOXLibDlg::onResetForm(FXObject* sender, FXSelector key, void* data)
{
	m_spnrTrackNumber->setValue(1);
	m_spnrTrackIndex->setValue(0);
	m_cmbTrackMode->setCurrentItem(0);
	m_listDatatypeMask->setMask(0);
	m_listIgnoreMask->setMask(0);
	m_txtfieldOffset->setText("0");
	m_txtfieldStartAddress->setText("0");
	m_txtfieldTrackLength->setText("0");
	return 1;
}

long KRawFOXLibDlg::onDeviceBox(FXObject* sender, FXSelector key, void* data)
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

		// Set current device

		int32 res = ::SetBurnDevice(strDevice);
		handleError(res);
	}
	return 1;
}


long KRawFOXLibDlg::onEraseDisk(FXObject* sender, FXSelector key, void* data)
{
	// Call erase dialog
	CALL_FXDIALOG_HANDLE_ERROR(::EraseDialog(_T("IsoSDK")));

	// Update device list

	updateDeviceCombo();
	return 1;
}
//Synchronize options and controls
int32 KRawFOXLibDlg::updateOptions()
{
	// Load options from controls

	SOptions opt;

	int32 res = ::GetOptions(&opt);
	handleError(res);

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	opt.bEjectAfterBurn = m_bEjectAfterBurn;
	opt.bFinalize = m_bFinalize;
	opt.bJolietFileSystem = m_bJoliet;
	opt.bVerifyAfterBurn = m_bVerify;

	// Set option to FoxBruner

	res = ::SetOptions(opt);
	handleError(res);
	return res;
}

long KRawFOXLibDlg::onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data)
{
	if(m_vTracks.empty())
	{
		FXMessageBox::information(this, MBOX_OK, "Notification", "Please, create at least one track.");
		return 1;
	}
	// Synchronize options and menu controls
	int32 res = ::SetRAWStructure(&m_vTracks.front(), (int32)m_vTracks.size());
	handleError(res);

	updateOptions();

	// Call IsoSDK burn dialog
	CALL_FXDIALOG_HANDLE_ERROR(::BurnDialog());

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KRawFOXLibDlg::onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data)
{

	if(m_vTracks.empty())
	{
		FXMessageBox::information(this, MBOX_OK, "Notification", "Please, create at least one track.");
		return 1;
	}

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
		if (!handle(0, FXSEL(SEL_COMMAND, KRawFOXLibDlg::ID_MOUNTIMAGE), 0))
			return 1;


		// Also set special options for image writer
		SOptions opt;

		// Load current options first

		res = ::GetOptions(&opt);
		handleError(res);

		opt.nCopies = 0;	// No need for copies
		opt.bTestBurn = BS_FALSE;	// Test burn is not supported
		opt.bVerifyAfterBurn = BS_FALSE;	// Test burn is not supported

		// Then save options

		res = ::SetOptions(opt);
		handleError(res);
	}

	res = ::SetRAWStructure(&m_vTracks.front(), (int32)m_vTracks.size());
	handleError(res);

	KSampleBurnDlg	burnDlg(this);	
	burnDlg.execute();

	return 1;
}

void KRawFOXLibDlg::handleError(int32 errCode)
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

long KRawFOXLibDlg::onErrorNotify(FXObject* sender, FXSelector key, void* data)
{
	handleError(pointerToInt(data));
	return 1;
}

long KRawFOXLibDlg::onRescanDevices(FXObject* sender, FXSelector key, void* data)
{
	int32 res = ::RescanDevices();
	handleError(res);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KRawFOXLibDlg::onMountImage(FXObject* sender, FXSelector key, void* data)
{
	const FXchar patterns[]= "ISO Files (*.iso)";

	FXFileDialog fileDlg(this, "Select Image File");
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

long KRawFOXLibDlg::onUnmountImage(FXObject* sender, FXSelector key, void* data)
{
	::SetImageFilePath(NULL);
	return 1;
}


long KRawFOXLibDlg::onCmdAspi(FXObject* sender, FXSelector key, void* data)
{
	FXint which = FXSELID(key) - ID_ASPI_INTERNAL;

	// Set selected interface

	int32 res = ::SetASPI(which);
	handleError(res);
	updateDeviceCombo();
	return 1;
}

long KRawFOXLibDlg::onUpdAspi(FXObject* sender, FXSelector key, void* data)
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

long KRawFOXLibDlg::onDisableImagewriter(FXObject* sender, FXSelector key, void* data)
{
	// Disable or enable image writer

	::EnableImageDevice(data == 0 ? BS_TRUE : BS_FALSE);

	// Update devices list

	updateDeviceCombo();
	return 1;
}

long KRawFOXLibDlg::onBurningDevices(FXObject* sender, FXSelector key, void* data)
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = data != 0;
	updateDeviceCombo();
	return 1;
}

long KRawFOXLibDlg::onAbout(FXObject* sender, FXSelector key, void* data)
{
	KAboutDlg	aboutDlg(this);
	aboutDlg.execute();
	return 1;
}

long KRawFOXLibDlg::onWeb(FXObject* sender, FXSelector key, void* data)
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

template <class List>
FXint KRawFOXLibDlg::insertUnique(List *list, FXString &str)
{
	FXint ind = list->findItem(str);
	if (ind != -1)
	{
        list->setCurrentItem(ind);
		return 1;
	}
	list->appendItem(str);
	list->setCurrentItem(list->getNumItems()-1);
	return 1;
}

void KRawFOXLibDlg::fillModes(FXComboBox *combo)
{
	combo->insertItem(0,IDS_MODE_AUDIO);
	combo->insertItem(1,IDS_MODE_1);
	combo->insertItem(2,IDS_MODE_2_FORMLESS);
	combo->insertItem(3,IDS_MODE_2_FORM_1);
	combo->insertItem(4,IDS_MODE_2_FORM_2);
}

long KRawFOXLibDlg::onDeleteTrack(FXObject* sender, FXSelector key, void* data)
{
	int nSelected = m_tblTrack->getSelStartRow();

	if(-1 == nSelected || m_tblTrack->getSelEndRow()!=nSelected )
	{
		FXMessageBox::information(this,MBOX_OK,"Information","You should select exactly one track to delete in the table below.");
        return 0;
	}

	m_tblTrack->removeRows(nSelected);
	m_vTracks.erase(m_vTracks.begin() + nSelected);		
	return 1;

}
long KRawFOXLibDlg::onAddTrack(FXObject* sender, FXSelector key, void* data)
{
	SRAWTrackToAdd track;

	int nNumb = 1;
	int nInd = -1;

	if (m_vTracks.size() > 0)
	{
		nNumb = m_vTracks.back().nNumber + 1;
		nInd = m_vTracks.back().nIndex;
	}

	int nItemPos = m_tblTrack->getNumRows();
	
	int nTrackNumber, nTrackIndex;
	nTrackNumber = m_spnrTrackNumber->getValue();
	nTrackIndex = m_spnrTrackIndex->getValue();

	// Check wheter the combination of Number and Index doesn't conflict with other tracks.
	if (nNumb == nTrackNumber || 
		(nNumb - 1 == nTrackNumber && nTrackIndex > nInd &&
		(nItemPos - 2 < 0 || m_vTracks[nItemPos - 2].nNumber != nTrackNumber )))
	{ // Check passed
		track.nNumber = nTrackNumber;
		track.nIndex = nTrackIndex;
		track.nFormat = str2format(m_cmbTrackMode->getText());
		
		track.nDataTypeMask = m_listDatatypeMask->getMask();

		track.nIgnoreDataMask = m_listIgnoreMask->getMask();

		track.nStartAddress = m_txtfieldStartAddress->getText().toInt();
		track.nLength = m_txtfieldTrackLength->getText().toInt();
		if (track.nLength <= 0) {
			FXMessageBox::information(this, MBOX_OK, "Information", "Track length, offset or start address should be legal numbers. Length, for example, should be posistive. Please, correct them and try again.");
			return 0;
		}
		track.nOffset = m_txtfieldOffset->getText().toInt();

		/*
		catch(EmptyStringErrorIn_str2int)
		{
			FXMessageBox::information(this,MBOX_OK,"Information","Track length, offset and start address should not be empty. Please, correct them and try again.");
			return 0;            
		}
		*/
        
		m_vTracks.push_back(track);
		
		m_tblTrack->insertRows(nItemPos,1);
		
		FXString str;
		
		str= "";
		str.format("%d",track.nNumber);
		m_tblTrack->setItemText(nItemPos,0,str);

		str= "";
		str.format("%d",track.nIndex);
		m_tblTrack->setItemText(nItemPos,1,str);
		
		m_tblTrack->setItemText(nItemPos,2,getFormat<FXString>(track));
		m_tblTrack->setItemText(nItemPos,3,getMask<FXString>(track.nDataTypeMask));
		m_tblTrack->setItemText(nItemPos,4,getMask<FXString>(track.nIgnoreDataMask));

		str= "";
		str.format("%d",track.nStartAddress);
		m_tblTrack->setItemText(nItemPos,5,str);

		str= "";
		str.format("%d",track.nLength);
		m_tblTrack->setItemText(nItemPos,6,str);

		str= "";
		str.format("%d",track.nOffset);
		m_tblTrack->setItemText(nItemPos,7,str);
	}
	else // conflict
	{
		FXMessageBox::information(this,MBOX_OK,"Information","Track number or index conflicts with existing tracks. Please, correct it and try again.");
	}	
	return 1;
}
