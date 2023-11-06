#include "stdafx.h"
#include "PropertiesDlg.h"
#include "DataFOXLibDlg.h"

FXDEFMAP(KPropertiesDlg) KPropertiesDlgMap[] = {
	FXMAPFUNC(SEL_COMMAND, KPropertiesDlg::ID_ACCEPT, KPropertiesDlg::onCmdAccept),
	FXMAPFUNC(SEL_COMMAND, KPropertiesDlg::ID_SYNC_DATES, KPropertiesDlg::onSyncDates)
};

FXIMPLEMENT(KPropertiesDlg, FXDialogBox, KPropertiesDlgMap, ARRAYNUMBER(KPropertiesDlgMap))

KPropertiesDlg::KPropertiesDlg(FXWindow *owner, SFileEntry *fileEntry) :
	FXDialogBox(owner, "Properties", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER),
	m_fileEntry(fileEntry)
{
	m_strFileName = fileEntry->lpszFileName;
	m_nHiddenAttribute = fileEntry->nAttrib & BS_FA_HIDDEN ? true : false;
	m_nAdvancedHiddenAttribute = fileEntry->nAttrib & BS_FA_ADVANCED_HIDDEN ? true : false;
	

	SFileTimeEx myTime;
	::GetFileTimeEx(&myTime);
	m_GlobalUsage = myTime.UseCustomTimes == BS_TRUE ? true : false;


	tgtFileName.connect(m_strFileName);
	tgtHiddenAttribute.connect(m_nHiddenAttribute);
	tgtAdvancedHiddenAttribute.connect(m_nAdvancedHiddenAttribute);
	tgtGlobalusage.connect(m_GlobalUsage);

	FXMatrix *nameMatrix = new FXMatrix(this, 2, MATRIX_BY_COLUMNS);
	new FXLabel(nameMatrix, "Name:", 0, LAYOUT_FIX_WIDTH|JUSTIFY_LEFT, 0, 0, 60);
	new FXTextField(nameMatrix, 40, &tgtFileName, FXDataTarget::ID_VALUE);

	new FXHorizontalSeparator(this);

	FXMatrix *timeMatrix = new FXMatrix(this, 2, MATRIX_BY_COLUMNS);
	new FXLabel(timeMatrix, "Created:", 0, LAYOUT_FIX_WIDTH|JUSTIFY_LEFT, 0, 0, 60);
	FXHorizontalFrame *creationFrame = new FXHorizontalFrame(timeMatrix, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	DEFINE_DATE_TIME_CONTROLS(CreationTime, creationFrame, KPropertiesDlg::ID_SYNC_DATES);
	new FXLabel(timeMatrix, "Modified:", 0, LAYOUT_FIX_WIDTH|JUSTIFY_LEFT, 0, 0, 60);
	FXHorizontalFrame *modificationFrame = new FXHorizontalFrame(timeMatrix, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	DEFINE_DATE_TIME_CONTROLS(ModificationTime, modificationFrame, KPropertiesDlg::ID_SYNC_DATES);
	new FXLabel(timeMatrix, "Accessed:", 0, LAYOUT_FIX_WIDTH|JUSTIFY_LEFT, 0, 0, 60);
	FXHorizontalFrame *lastAccessFrame = new FXHorizontalFrame(timeMatrix, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	DEFINE_DATE_TIME_CONTROLS(LastAccessTime, lastAccessFrame, KPropertiesDlg::ID_SYNC_DATES);

	new FXHorizontalSeparator(this);

	FXHorizontalFrame* globalFlag = new FXHorizontalFrame(this, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	new FXCheckButton(this, "Set times for global usage", &tgtGlobalusage, FXDataTarget::ID_VALUE);

	new FXHorizontalSeparator(this);

	FXMatrix *attributesMatrix = new FXMatrix(this, 3, MATRIX_BY_COLUMNS);
	new FXLabel(attributesMatrix, "Attributes:", 0, LAYOUT_FIX_WIDTH|JUSTIFY_LEFT, 0, 0, 60);
	new FXCheckButton(attributesMatrix, "Hidden", &tgtHiddenAttribute, FXDataTarget::ID_VALUE);
	new FXCheckButton(attributesMatrix, "Advanced hidden", &tgtAdvancedHiddenAttribute, FXDataTarget::ID_VALUE);

	FXHorizontalFrame *buttonFrame = new FXHorizontalFrame(this,  LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);
	new FXButton(buttonFrame, "Cancel", NULL, this, FXDialogBox::ID_CANCEL,
		BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);
	new FXButton(buttonFrame, "OK", NULL, this, ID_ACCEPT,
		BUTTON_DEFAULT|BUTTON_INITIAL|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_SIDE_RIGHT|LAYOUT_RIGHT|LAYOUT_FIX_HEIGHT,
		0, 0, 70, 25);

	SET_DATE_TIME(CreationTime, fileEntry->cCreationTime);
	SET_DATE_TIME(ModificationTime, fileEntry->cDateTime);
	SET_DATE_TIME(LastAccessTime, fileEntry->cAccessTime);
}

KPropertiesDlg::~KPropertiesDlg(void)
{
}

long KPropertiesDlg::onSyncDates(FXObject* sender, FXSelector key, void* data)
{
	SYNC_DATE_TIME(CreationTime);
	SYNC_DATE_TIME(ModificationTime);
	SYNC_DATE_TIME(LastAccessTime);
	return 1;
}

long KPropertiesDlg::onCmdAccept(FXObject* sender, FXSelector key, void* data)
{

	SFileTimeEx myTime;
	::GetFileTimeEx(&myTime);

	myTime.UseCustomTimes = m_GlobalUsage == true ? BS_TRUE : BS_FALSE;

	COPY_DATE_TIME(CreationTime, myTime.CreationDateTime);
	myTime.UseCreationDateTime = BS_TRUE;
	COPY_DATE_TIME(ModificationTime, myTime.ModificationDateTime);
	myTime.UseModificationDateTime = BS_TRUE;
	COPY_DATE_TIME(LastAccessTime, myTime.LastAccessDateTime);
	myTime.UseLastAccessDateTime = BS_TRUE;
		
	::SetFileTimeEx(myTime);


	COPY_DATE_TIME(CreationTime, m_fileEntry->cCreationTime);
	COPY_DATE_TIME(ModificationTime, m_fileEntry->cDateTime);
	COPY_DATE_TIME(LastAccessTime, m_fileEntry->cAccessTime);

	int result = BS_SDK_ERROR_NO;

	if (m_strFileName.empty())
	{
		FXMessageBox::error(this, MBOX_OK, "IsoSDK", "File name cannot be empty.");
		return -1;
	}

	KString strPath = m_fileEntry->lpszFilePath;
	if (strPath != PATHSEPSTRING)
		strPath += PATHSEPSTRING;
	KString strSourcePath = strPath + m_fileEntry->lpszFileName;
	KString strDestinationPath = strPath + Fox2SDKString(m_strFileName);

	// Rename the file if the name has been changed.
	if (strSourcePath != strDestinationPath)
	{
		SFileToRename fileToRename;
		fileToRename.lpszSourcePath = strSourcePath;
		fileToRename.lpszDestinationPath = strDestinationPath;
		result = ::RenameFile(fileToRename);
		if (result != BS_SDK_ERROR_NO)
		{
			handleError(result);
			return -1;
		}
	}

	// Set creation, modification and last access time.
	result = ::SetFileTimes(strDestinationPath, &m_fileEntry->cCreationTime, &m_fileEntry->cDateTime, &m_fileEntry->cAccessTime);
	if (result != BS_SDK_ERROR_NO)
	{
		handleError(result);
		return -1;
	}

	// Set file attributes.
	m_fileEntry->nAttrib &= ~(BS_FA_HIDDEN | BS_FA_ADVANCED_HIDDEN);
	if (m_nHiddenAttribute)
		m_fileEntry->nAttrib |= BS_FA_HIDDEN;
	if (m_nAdvancedHiddenAttribute)
		m_fileEntry->nAttrib |= BS_FA_ADVANCED_HIDDEN;
	result = ::SetFileAttr(strDestinationPath, m_fileEntry->nAttrib);
	if (result != BS_SDK_ERROR_NO)
	{
		handleError(result);
		return -1;
	}

	return FXDialogBox::onCmdAccept(sender, key, data);
}

void KPropertiesDlg::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		getOwner()->handle(this, FXSEL(KDataFOXLibDlg::SEL_ERRORNOTIFY, 0), IntToPvoid(errCode));
	}
}
