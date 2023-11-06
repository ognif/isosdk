#include "stdafx.h"
#include "BootImageDlg.h"
#include "DataFOXLibDlg.h"


FXDEFMAP(KBootImgDlg) KBootImgDlgMap[]= {
	FXMAPFUNC(SEL_COMMAND, KBootImgDlg::ID_SELFILE, KBootImgDlg::onCmdFileSelect),
	FXMAPFUNC(SEL_COMMAND, KBootImgDlg::ID_MEDIATYPE, KBootImgDlg::onCmdMediatype),
	FXMAPFUNC(SEL_COMMAND, KBootImgDlg::ID_PLATFORM, KBootImgDlg::onCmdPlatform),
	FXMAPFUNC(SEL_COMMAND, KBootImgDlg::ID_RESET, KBootImgDlg::onCmdReset),
	FXMAPFUNC(SEL_COMMAND, KBootImgDlg::ID_ACCEPT, KBootImgDlg::onCmdAccept),
};

FXIMPLEMENT(KBootImgDlg, FXDialogBox, KBootImgDlgMap, ARRAYNUMBER(KBootImgDlgMap))


KBootImgDlg::KBootImgDlg(FXWindow *owner, const FXString &title)
	: FXDialogBox(owner, title, DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER)
{
	onCmdReset(NULL, 0, NULL);

	tgtBootImage.connect(m_strBootImage);
	tgtSectorCount.connect(m_nSectorCount);
	tgtLoadSegment.connect(m_nLoadSegment);
	tgtDeveloperID.connect(m_strDeveloperID);
	tgtMakeDiskBootable.connect(m_bMakeDiskBootable);

	new FXLabel(this, "Boot image:");
	FXHorizontalFrame *horFrame = new FXHorizontalFrame(this);
	new FXTextField(horFrame, 35, &tgtBootImage, FXDataTarget::ID_VALUE);
	new FXButton(horFrame, "...", NULL, this, ID_SELFILE, FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 60, 20);

	FXVerticalFrame *frameOpt = new FXVerticalFrame(this, LAYOUT_FILL_X|FRAME_THICK);

	new FXLabel(frameOpt, "Boot media type (emulation):");
	FXComboBox *cmbMediatype = new FXComboBox(frameOpt, 20, this, ID_MEDIATYPE, FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
	cmbMediatype->appendItem("No emulation");
	cmbMediatype->appendItem("1.2 MB Floppy");
	cmbMediatype->appendItem("1.44 MB Floppy");
	cmbMediatype->appendItem("2.88 MB Floppy");
	cmbMediatype->appendItem("Hard disk");
	cmbMediatype->setNumVisible(cmbMediatype->getNumItems());
	cmbMediatype->setCurrentItem(m_iMediaType);

	new FXLabel(frameOpt, "Platform:");
	FXComboBox *cmbPlatform = new FXComboBox(frameOpt, 20, this, ID_PLATFORM, FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
	cmbPlatform->appendItem("80x86");
	cmbPlatform->appendItem("PowerPC");
	cmbPlatform->appendItem("Mac");
	cmbPlatform->setNumVisible(cmbPlatform->getNumItems());
	cmbPlatform->setCurrentItem(m_iPlatform);

	FXMatrix *matrix = new FXMatrix(frameOpt, 2, MATRIX_BY_COLUMNS);
	new FXLabel(matrix, "Sector count:");
	new FXTextField(matrix, 10, &tgtSectorCount, FXDataTarget::ID_VALUE, TEXTFIELD_NORMAL|TEXTFIELD_INTEGER);

	new FXLabel(matrix, "Load segment:");
	new FXTextField(matrix, 10, &tgtLoadSegment, FXDataTarget::ID_VALUE, TEXTFIELD_NORMAL|TEXTFIELD_INTEGER);

	new FXLabel(matrix, "Developer ID:");
	new FXTextField(matrix, 30, &tgtDeveloperID, FXDataTarget::ID_VALUE);

	new FXCheckButton(frameOpt, "Make disk bootable", &tgtMakeDiskBootable, FXDataTarget::ID_VALUE);

	FXHorizontalFrame *frameButtons = new FXHorizontalFrame(this,  LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);

	new FXButton(frameButtons, "Reset", NULL, this, ID_RESET,
		BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_SIDE_LEFT|LAYOUT_LEFT|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);

	new FXButton(frameButtons, "Cancel", NULL, this, FXDialogBox::ID_CANCEL,
		BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);

	new FXButton(frameButtons, "Ok", NULL, this, ID_ACCEPT,
		BUTTON_DEFAULT|BUTTON_INITIAL|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);
}

long KBootImgDlg::onCmdFileSelect(FXObject* sender, FXSelector key, void* data)
{
	const FXchar patterns[]= "Image files (*.img)";

	FXFileDialog dlg(getApp(), "Select image file");
	dlg.setSelectMode(SELECTFILE_EXISTING);
	dlg.setPatternList(patterns);

	if (dlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(dlg.getDirectory());

		m_strBootImage = dlg.getFilename();
		update();
	}

	return 1;
}

long KBootImgDlg::onCmdMediatype(FXObject* sender, FXSelector key, void* data)
{
	m_iMediaType = ((FXComboBox*)sender)->getCurrentItem();

	return 1;
}

long KBootImgDlg::onCmdPlatform(FXObject* sender, FXSelector key, void* data)
{
	m_iPlatform = ((FXComboBox*)sender)->getCurrentItem();

	return 1;
}

long KBootImgDlg::onCmdReset(FXObject* sender, FXSelector key, void* data)
{
	SOptions opt;
	int32 res = ::GetOptions(&opt);
	handleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		m_strBootImage = SDK2FoxString(opt.chBootImage);
	}

	SBootInfoEx info;
	res = ::GetBootInfoEx(&info);
	handleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		m_bMakeDiskBootable	= info.BootIndicator;
		m_strDeveloperID	= SDK2FoxString(info.DeveloperID);
		m_iMediaType		= info.Emulation;
		m_nLoadSegment		= info.LoadSegment;
		m_iPlatform			= info.PlatformID;
		m_nSectorCount		= info.SectorCount;
	}

	update();
	return 1;
}

long KBootImgDlg::onCmdAccept(FXObject* sender, FXSelector key, void* data)
{
	SOptions opt;
	int32 res = ::GetOptions(&opt);
	handleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		KString strImage = Fox2SDKString(FXString::compose(m_strBootImage.left(_MAX_PATH - 1), false));
		_tcsncpy(opt.chBootImage, (const TCHAR*)strImage, _MAX_PATH);
		opt.bBootable = m_bMakeDiskBootable;

		res = ::SetOptions(opt);
		handleError(res);
	}

	SBootInfoEx info;
	res = ::GetBootInfoEx(&info);
	handleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		memset(&info, 0, sizeof(SBootInfoEx));

		KString strDeveloperID = Fox2SDKString(FXString::compose(m_strDeveloperID.left(23), false));
		_tcsncpy(info.DeveloperID, strDeveloperID, 24*sizeof(TCHAR));

		info.BootIndicator	= m_bMakeDiskBootable;
		info.Emulation		= m_iMediaType;
		info.LoadSegment	= m_nLoadSegment;
		info.PlatformID		= m_iPlatform;
		info.SectorCount	= m_nSectorCount;

		res = ::SetBootInfoEx(info);
		handleError(res);
	}

	return FXDialogBox::onCmdAccept(sender, key, data);
}

void KBootImgDlg::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		getOwner()->handle(this, FXSEL(KDataFOXLibDlg::SEL_ERRORNOTIFY, 0), IntToPvoid(errCode));
	}
}
