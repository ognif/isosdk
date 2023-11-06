#include "stdafx.h"
#include "HeaderDlg.h"
#include "DataFOXLibDlg.h"


FXDEFMAP(KHeaderDlg) KHeaderDlgMap[] = {
	FXMAPFUNC(SEL_COMMAND,  KHeaderDlg::ID_ACCEPT, KHeaderDlg::onCmdAccept),
	FXMAPFUNC(SEL_COMMAND,  KHeaderDlg::ID_RESET, KHeaderDlg::onCmdReset),
	FXMAPFUNC(SEL_COMMAND, KHeaderDlg::ID_SYNC_DATES, KHeaderDlg::onSyncDates)
};

FXIMPLEMENT(KHeaderDlg, FXDialogBox, KHeaderDlgMap, ARRAYNUMBER(KHeaderDlgMap))

KHeaderDlg::KHeaderDlg(FXWindow *owner, const FXString &title)
	: FXDialogBox(owner, title, DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER)
{
	tgtSysIdent.connect(m_strSysIdent);
	tgtVolSet.connect(m_strVolSet);
	tgtPublisher.connect(m_strPublisher);
	tgtDatapreparer.connect(m_strDatapreparer);
	tgtApplication.connect(m_strApplication);
	tgtCopyrightFile.connect(m_strCopyrightFile);
	tgtAbstractFile.connect(m_strAbstractFile);
	tgtBibliographicFile.connect(m_strBibliographicFile);
	tgtAddFileSuffix.connect(m_bAddFileSuffix);

	tgtUseCreation.connect(m_nUseCreation);
	tgtUseModification.connect(m_nUseModification);
	tgtUseExpiration.connect(m_nUseExpiration);
	tgtUseEffective.connect(m_nUseEffective);

	FXMatrix *matrix = new FXMatrix(this, 2, MATRIX_BY_COLUMNS);
	new FXLabel(matrix, "System-Identifier:");
	new FXTextField(matrix, 30, &tgtSysIdent, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Volume set:");
	new FXTextField(matrix, 30, &tgtVolSet, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Publisher:");
	new FXTextField(matrix, 30, &tgtPublisher, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Datapreparer:");
	new FXTextField(matrix, 30, &tgtDatapreparer, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Application:");
	new FXTextField(matrix, 30, &tgtApplication, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Copyright file:");
	new FXTextField(matrix, 30, &tgtCopyrightFile, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Abstract file:");
	new FXTextField(matrix, 30, &tgtAbstractFile, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Bibliographic file:");
	new FXTextField(matrix, 30, &tgtBibliographicFile, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Add version numbers: ");
	new FXCheckButton(matrix, "", &tgtAddFileSuffix, FXDataTarget::ID_VALUE);
	
	new FXLabel(matrix, "Creation date&time: ");
	FXHorizontalFrame * creationFrame = new FXHorizontalFrame(matrix);
		(new FXCheckButton(creationFrame, "", &tgtUseCreation, FXDataTarget::ID_VALUE));
		DEFINE_DATE_TIME_CONTROLS(Creation, creationFrame, KHeaderDlg::ID_SYNC_DATES);

	new FXLabel(matrix, "Modification date&time: ");
	FXHorizontalFrame * modificationFrame = new FXHorizontalFrame(matrix);
		(new FXCheckButton(modificationFrame, "", &tgtUseModification, FXDataTarget::ID_VALUE));
		DEFINE_DATE_TIME_CONTROLS(Modification, modificationFrame, KHeaderDlg::ID_SYNC_DATES);

	new FXLabel(matrix, "Expiration date&time: ");
	FXHorizontalFrame * expirationFrame = new FXHorizontalFrame(matrix);
		(new FXCheckButton(expirationFrame, "", &tgtUseExpiration, FXDataTarget::ID_VALUE));
		DEFINE_DATE_TIME_CONTROLS(Expiration, expirationFrame, KHeaderDlg::ID_SYNC_DATES);

	new FXLabel(matrix, "Effective date&time: ");
	FXHorizontalFrame * effectiveFrame = new FXHorizontalFrame(matrix);
		(new FXCheckButton(effectiveFrame, "", &tgtUseEffective, FXDataTarget::ID_VALUE));
		DEFINE_DATE_TIME_CONTROLS(Effective, effectiveFrame, KHeaderDlg::ID_SYNC_DATES);

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

	onCmdReset(NULL, 0, NULL);
}

long KHeaderDlg::onCmdReset(FXObject* sender, FXSelector key, void* data)
{
	SISOInfoEx info;

	int32 res = ::GetISOInfoEx(&info);
	handleError(res);

	m_strSysIdent = SDK2FoxString(info.ISOSystemIdentifier);
	m_strVolSet = SDK2FoxString(info.ISOSetIdentifier);
	m_strPublisher = SDK2FoxString(info.ISOPublisherIdentifier);
	m_strDatapreparer = SDK2FoxString(info.ISODataPreparerIdentifier);
	m_strApplication = SDK2FoxString(info.ISOApplicationIdentifier);
	m_strCopyrightFile = SDK2FoxString(info.ISOCopyrightFileIdentifier);
	m_strAbstractFile = SDK2FoxString(info.ISOAbstractFileIdentifier);
	m_strBibliographicFile = SDK2FoxString(info.ISOBiblioIdentifier);
	m_bAddFileSuffix = BS_BOOL2bool(info.ISOAddSuffix);

	m_nUseCreation = info.ISOUseCreationDateTime;
	m_nUseModification = info.ISOUseModificationDateTime;
	m_nUseExpiration = info.ISOUseExpirationDateTime;
	m_nUseEffective = info.ISOUseEffectiveDateTime;

	SET_DATE_TIME(Creation, info.ISOCreationDateTime);
	SET_DATE_TIME(Expiration, info.ISOExpirationDateTime);
	SET_DATE_TIME(Modification, info.ISOModificationDateTime);
	SET_DATE_TIME(Effective, info.ISOEffectiveDateTime);
	
	update();

	return 1;
}

long KHeaderDlg::onCmdAccept(FXObject* sender, FXSelector key, void* data)
{
	SISOInfoEx info;
	memset(&info, 0, sizeof(info));

	KString strTmp;

	//strTmp = Fox2SDKString(compose(m_strSysIdent.left(30), DecCanonical));
	strTmp = Fox2SDKString(FXString::compose(m_strSysIdent.left(30), false));
	_tcsncpy(info.ISOSystemIdentifier, strTmp, 31);

	strTmp =  Fox2SDKString(FXString::compose(m_strVolSet.left(127), false));
	_tcsncpy(info.ISOSetIdentifier, strTmp, 128);

	strTmp = Fox2SDKString(FXString::compose(m_strPublisher.left(127), false));
	_tcsncpy(info.ISOPublisherIdentifier, strTmp, 128);

	strTmp = Fox2SDKString(FXString::compose(m_strDatapreparer.left(127), false));
	_tcsncpy(info.ISODataPreparerIdentifier, strTmp, 128);

	strTmp = Fox2SDKString(FXString::compose(m_strApplication.left(127), false));
	_tcsncpy(info.ISOApplicationIdentifier, strTmp, 128);

	strTmp = Fox2SDKString(FXString::compose(m_strCopyrightFile.left(35), false));
	_tcsncpy(info.ISOCopyrightFileIdentifier, strTmp, 36);

	strTmp = Fox2SDKString(FXString::compose(m_strAbstractFile.left(35), false));
	_tcsncpy(info.ISOAbstractFileIdentifier, strTmp, 36);

	strTmp = Fox2SDKString(FXString::compose(m_strBibliographicFile.left(35), false));;
	_tcsncpy(info.ISOBiblioIdentifier, strTmp, 36);

	info.ISOAddSuffix = m_bAddFileSuffix ? BS_TRUE : BS_FALSE;

	info.ISOUseCreationDateTime = m_nUseCreation ? BS_TRUE : BS_FALSE;
	info.ISOUseEffectiveDateTime = m_nUseEffective ? BS_TRUE : BS_FALSE;
	info.ISOUseExpirationDateTime = m_nUseExpiration ? BS_TRUE : BS_FALSE;
	info.ISOUseModificationDateTime = m_nUseModification ? BS_TRUE : BS_FALSE;

	
	COPY_DATE_TIME(Creation, info.ISOCreationDateTime);
	COPY_DATE_TIME(Modification, info.ISOModificationDateTime);
	COPY_DATE_TIME(Expiration, info.ISOExpirationDateTime);
	COPY_DATE_TIME(Effective, info.ISOEffectiveDateTime);

	int32 res = ::SetISOInfoEx(info);
	handleError(res);

	return FXDialogBox::onCmdAccept(sender, key, data);
}

long KHeaderDlg::onSyncDates(FXObject* sender, FXSelector key, void* data)
{
	SYNC_DATE_TIME(Creation);
	SYNC_DATE_TIME(Modification);
	SYNC_DATE_TIME(Expiration);
	SYNC_DATE_TIME(Effective);
	return 1;
}
void KHeaderDlg::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		getOwner()->handle(this, FXSEL(KDataFOXLibDlg::SEL_ERRORNOTIFY, 0), IntToPvoid(errCode));
	}
}
