#include "stdafx.h"
#include "CDTextDlg.h"
#include <algorithm>


KFileAudioProperty::KFileAudioProperty()	
	:nPlayTime(0)
{
	UpdateData();
	data.nPause = 2;
	data.bPauseInFrames = BS_FALSE;
}

KFileAudioProperty::KFileAudioProperty(const KFileAudioProperty &prp)
	: strSourceFilePath(prp.strSourceFilePath)
	, strTitle(prp.strTitle)
	, strPerformer(prp.strPerformer)
	, strSongWriter(prp.strSongWriter)
	, strComposer(prp.strComposer)
	, strArranger(prp.strArranger)
	, strMessage(prp.strMessage)
	, strMCNISRC(prp.strMCNISRC)
	, nPlayTime(prp.nPlayTime)
	, vIndexes(prp.vIndexes)
{
	UpdateData();
	data.nPause = prp.data.nPause;
	data.bPauseInFrames = prp.data.bPauseInFrames;
}

void KFileAudioProperty::SetTrackNumber(int nTrack)
{
	strSourceFilePath = KStringFormat("%02d", nTrack);
	data.lpszSourceFilePath = strSourceFilePath;
}

KFileAudioProperty::KFileAudioProperty(const KString &filePath)
	:nPlayTime(0)
{
	UpdateData();
	strSourceFilePath = filePath;
	data.nPause = 2;
	data.bPauseInFrames = BS_FALSE;
}

void KFileAudioProperty::UpdateData()
{
	data.lpszSourceFilePath = strSourceFilePath;
	data.lpszTitle = strTitle;
	data.Performer = strPerformer;
	data.SongWriter = strSongWriter;
	data.Composer = strComposer;
	data.Arranger = strArranger;
	data.Message = strMessage;
	data.lpszMCN_ISRC = strMCNISRC;
	if (vIndexes.empty())
	{
		data.pIndexes = 0;
		data.nIndexesLength = 0;
	}
	else
	{
		data.pIndexes = &vIndexes[0];
		data.nIndexesLength = int32(vIndexes.size());
	}
}

FXDEFMAP(KCDTextDlg) KCDTextDlgMap[] = {
	FXMAPFUNC(SEL_COMMAND,  KCDTextDlg::ID_ACCEPT, KCDTextDlg::onCmdAccept),
	FXMAPFUNC(SEL_COMMAND,  KCDTextDlg::ID_RESET, KCDTextDlg::onCmdReset),
	FXMAPFUNC(SEL_COMMAND,  KCDTextDlg::ID_ADD_INDEX, KCDTextDlg::onCmdAddIndex),
	FXMAPFUNC(SEL_COMMAND,  KCDTextDlg::ID_DELETE_INDEX, KCDTextDlg::onCmdDeleteIndex)
};

FXIMPLEMENT(KCDTextDlg, FXDialogBox, KCDTextDlgMap, ARRAYNUMBER(KCDTextDlgMap))

KCDTextDlg::KCDTextDlg(FXApp *app, const FXString &title, bool disc)
	: FXDialogBox(app, title, DECOR_TITLE|DECOR_CLOSE|DECOR_MENU, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	, m_pFileInfo(NULL)
	, m_bDiscText(disc)
	, m_nMin(0)
	, m_nSec(0)
	, m_nFrame(1)
{
	m_tabs = new FXTabBook(this, NULL, 0, TABBOOK_NORMAL|LAYOUT_FILL_X);

	CreateCDTextTab();
	CreateIndexesTab();

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

void KCDTextDlg::CreateCDTextTab()
{
	tgtArranger.connect(m_strArranger);
	tgtComposer.connect(m_strComposer);
	tgtSongWriter.connect(m_strSongWriter);
	tgtPerformer.connect(m_strPerformer);
	tgtMessage.connect(m_strMessage);
	tgtTitle.connect(m_strTitle);
	tgtMCN_ISRC.connect(m_strMCN_ISRC);
	tgtPause.connect(m_nPause);
	tgtPauseInFrames.connect(m_nPauseInFrames);

	new FXTabItem(m_tabs, "CD Text");

	FXMatrix *matrix = new FXMatrix(m_tabs, 2, MATRIX_BY_COLUMNS|FRAME_RAISED);
	new FXLabel(matrix, "Arranger:");
	new FXTextField(matrix, 30, &tgtArranger, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Composer:");
	new FXTextField(matrix, 30, &tgtComposer, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Song writer:");
	new FXTextField(matrix, 30, &tgtSongWriter, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Performer:");
	new FXTextField(matrix, 30, &tgtPerformer, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Message:");
	new FXTextField(matrix, 30, &tgtMessage, FXDataTarget::ID_VALUE);
	new FXLabel(matrix, "Title:");
	new FXTextField(matrix, 30, &tgtTitle, FXDataTarget::ID_VALUE);

	new FXLabel(matrix, m_bDiscText ? "UPC/EAN:" : "ISRC:");
	new FXTextField(matrix, 30, &tgtMCN_ISRC, FXDataTarget::ID_VALUE);

	new FXLabel(matrix, "Pause:");
	FXTextField* txtPause = new FXTextField(matrix, 5, &tgtPause, FXDataTarget::ID_VALUE, TEXTFIELD_NORMAL|TEXTFIELD_INTEGER);
	
	new FXLabel(matrix, "Pause in frames:");
	FXCheckButton* chkPauseInFrames = new FXCheckButton(matrix, "", &tgtPauseInFrames, FXDataTarget::ID_VALUE);

	if (m_bDiscText)
	{
		txtPause->disable();
		chkPauseInFrames->disable();
	}
}

void KCDTextDlg::CreateIndexesTab()
{
	tgtMinute.connect(m_nMin);
	tgtSecond.connect(m_nSec);
	tgtFrame.connect(m_nFrame);

	FXTabItem* tabIndexes = new FXTabItem(m_tabs, "Indexes");

	FXHorizontalFrame* horFrame = new FXHorizontalFrame(m_tabs, FRAME_RAISED|LAYOUT_FILL);
		FXVerticalFrame * listFrame = new FXVerticalFrame(horFrame, FRAME_SUNKEN|LAYOUT_FILL);
		m_lstIndexes = new FXList(listFrame, 0, 0, LIST_NORMAL|LAYOUT_FILL);
		FXVerticalFrame* vertFrame = new FXVerticalFrame(horFrame, LAYOUT_FILL_Y);
			FXHorizontalFrame* timeFrame = new FXHorizontalFrame(vertFrame, LAYOUT_FILL_X);
				new FXLabel(timeFrame, "M: ");
				new FXTextField(timeFrame, 3, &tgtMinute, FXDataTarget::ID_VALUE);
				new FXLabel(timeFrame, "S: ");
				new FXTextField(timeFrame, 3, &tgtSecond, FXDataTarget::ID_VALUE);
				new FXLabel(timeFrame, "F: ");
				new FXTextField(timeFrame, 3, &tgtFrame, FXDataTarget::ID_VALUE);
			FXHorizontalFrame* btnFrame = new FXHorizontalFrame(vertFrame, LAYOUT_FILL_X);
				new FXButton(btnFrame, "Delete", NULL, this, ID_DELETE_INDEX, BUTTON_NORMAL|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0, 0, 70, 25);
				new FXButton(btnFrame, "Add", NULL, this, ID_ADD_INDEX, BUTTON_NORMAL|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0, 0, 70, 25);

	if (m_bDiscText)
		tabIndexes->disable();
}

void KCDTextDlg::SetFileProperty(KFileAudioProperty *pInfo)
{
	m_pFileInfo = pInfo;
	if (pInfo) {
		m_strArranger = (const wchar_t*)pInfo->strArranger;
		m_strComposer = (const wchar_t*)pInfo->strComposer;
		m_strSongWriter = (const wchar_t*)pInfo->strSongWriter;
		m_strPerformer = (const wchar_t*)pInfo->strPerformer;
		m_strMessage = (const wchar_t*)pInfo->strMessage;
		m_strTitle = (const wchar_t*)pInfo->strTitle;
		m_strMCN_ISRC = (const wchar_t*)pInfo->strMCNISRC;
		m_nPause = pInfo->data.nPause;
		m_nPauseInFrames = pInfo->data.bPauseInFrames ? 1 : 0;

		m_lstIndexes->clearItems();
		for(size_t i = 0; i < pInfo->vIndexes.size(); ++i)
		{
			int32 nTime = pInfo->vIndexes[i];
			int nFrame = nTime % 75;
			int nSec = ((nTime - nFrame)/75) % 60;
			int nMin = nTime/(60*75);

			FXString strTime = FXString::value("%02d:%02d:%02d", nMin, nSec, nFrame);
			m_lstIndexes->appendItem(strTime, 0, (void*)size_t(pInfo->vIndexes[i]));
		}
	}
}

long KCDTextDlg::onCmdReset(FXObject* sender, FXSelector key, void* data)
{
	SetFileProperty(m_pFileInfo);
	update();

	return 1;
}

long KCDTextDlg::onCmdAccept(FXObject* sender, FXSelector key, void* data)
{
	if (m_pFileInfo)
	{		
		m_pFileInfo->strArranger = Fox2SDKString(FXString::compose(m_strArranger, false));
		m_pFileInfo->strComposer = Fox2SDKString(FXString::compose(m_strComposer, false));
		m_pFileInfo->strSongWriter = Fox2SDKString(FXString::compose(m_strSongWriter, false));
		m_pFileInfo->strPerformer = Fox2SDKString(FXString::compose(m_strPerformer, false));
		m_pFileInfo->strMessage = Fox2SDKString(FXString::compose(m_strMessage, false));
		m_pFileInfo->strTitle = Fox2SDKString(FXString::compose(m_strTitle, false));
		m_pFileInfo->strMCNISRC = Fox2SDKString(FXString::compose(m_strMCN_ISRC, false));
		m_pFileInfo->data.nPause = m_nPause;
		m_pFileInfo->data.bPauseInFrames = m_nPauseInFrames ? BS_TRUE : BS_FALSE;

		m_pFileInfo->vIndexes.clear();

		for(FXint i = 0; i < m_lstIndexes->getNumItems(); ++i)
			m_pFileInfo->vIndexes.push_back((int32)size_t(m_lstIndexes->getItemData(i)));

		std::sort(m_pFileInfo->vIndexes.begin(), m_pFileInfo->vIndexes.end());

		m_pFileInfo->UpdateData();
	}

	return FXDialogBox::onCmdAccept(sender, key, data);
}

long KCDTextDlg::onCmdAddIndex(FX::FXObject *sender, FX::FXSelector key, void *data)
{
	if (m_nSec < 0 || m_nSec > 59 ||
		m_nFrame < 0 || m_nFrame > 74)
	{
		FXMessageBox::error(this, MBOX_OK, "Track properties", "Time is invalid");
		return 0;
	}

	size_t nIndex = (m_nMin*60 + m_nSec)*75 + m_nFrame;

	FXint item = m_lstIndexes->findItemByData((void*)nIndex);

	if (item == -1)
	{
		if (nIndex > 0 && nIndex < size_t(m_pFileInfo->nPlayTime*75))
			m_lstIndexes->appendItem(FXString::value("%02d:%02d:%02d", m_nMin, m_nSec, m_nFrame), 0, (void*)nIndex);
		else
			FXMessageBox::error(this, MBOX_OK, "Track properties", "Index is invalid");
	}
	return 0;
}

long KCDTextDlg::onCmdDeleteIndex(FX::FXObject *sender, FX::FXSelector key, void *data)
{
	FXint currItem = m_lstIndexes->getCurrentItem();

	if (currItem != -1)
		m_lstIndexes->removeItem(currItem);
	return 0;
}
