#include "stdafx.h"
#include "AudioGrabbingDialog.h"
#include "../Common/CommonFoxLib.h"

#ifdef LINUX
	#include <dlfcn.h>
#endif

FXDEFMAP(KAudioGrabbingDialog) KSampleBurnMap[]= {
	FXMAPFUNC(SEL_COMMAND, KAudioGrabbingDialog::ID_USERACTION, KAudioGrabbingDialog::onUserAction),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KAudioGrabbingDialog::onUserAction),
	FXMAPFUNC(SEL_CLOSE, 0, KAudioGrabbingDialog::onUserAction),

	FXMAPFUNC(SEL_COMMAND, KAudioGrabbingDialog::ID_BROWSE, KAudioGrabbingDialog::onBrowse),
	FXMAPFUNC(SEL_CHORE, KAudioGrabbingDialog::ID_JOBDONE, KAudioGrabbingDialog::onChoreJobDone),
	FXMAPFUNC(SEL_CHORE, KAudioGrabbingDialog::ID_BURNDONE, KAudioGrabbingDialog::onChoreBurnDone),
	FXMAPFUNC(SEL_CHORE, KAudioGrabbingDialog::ID_SETPROGRESS, KAudioGrabbingDialog::onSetProgress),
	FXMAPFUNC(SEL_TIMEOUT, KAudioGrabbingDialog::ID_TOTALTIME, KAudioGrabbingDialog::onTimer),
	FXMAPFUNC(SEL_COMMAND, KAudioGrabbingDialog::ID_ENCODERBOX, KAudioGrabbingDialog::onEncoderBox),
	FXMAPFUNC(SEL_COMMAND, KAudioGrabbingDialog::ID_BITRATE_TYPE_BOX, KAudioGrabbingDialog::onBitrateTypeBox),
	FXMAPFUNC(SEL_COMMAND, KAudioGrabbingDialog::ID_BITRATE_MIN_BOX, KAudioGrabbingDialog::onMinBitrateBox),
	FXMAPFUNC(SEL_COMMAND, KAudioGrabbingDialog::ID_BITRATE_MAX_BOX, KAudioGrabbingDialog::onMaxBitrateBox),
};

FXIMPLEMENT(KAudioGrabbingDialog, FXDialogBox, KSampleBurnMap, ARRAYNUMBER(KSampleBurnMap))


FXint ComboIndex2Bitrate(FXint nIndex)
{
	switch (nIndex)
	{
		case 0 :
			return 64;
		case 1 :
			return 96;
		case 2 :
			return 128;
		case 3 :
			return 192;
		case 4 :
			return 256;
		case 5 :
			return 320;
		default:
			return 128;
	}
}

FXint ComboIndex2EncoderIndex(FXint nIndex)
{
	switch (nIndex)
	{
		case 0 :
			return BS_ET_MP3;
		case 1 :
			return BS_ET_AAC;
		case 2 :
			return BS_ET_OGG;
		case 3 :
			return BS_ET_OPUS;
		case 4:
			return BS_ET_FLAC;
		default :
			return BS_ET_MP3;
	}
}

FXString ComboIndex2FileExt(FXint nIndex)
{
	switch (ComboIndex2EncoderIndex(nIndex))
	{
		case BS_ET_MP3:
			return ".mp3";
		case BS_ET_AAC:
			return ".aac";
		case BS_ET_OGG:
			return ".ogg";
		case BS_ET_OPUS:
			return ".opus";
		case BS_ET_FLAC:
			return ".flac";
		default :
			return ".mp3";
	}
}

FXint ComboIndex2TagChoice(FXint nIndex)
{
	switch (nIndex)
	{
		case 0 :
			return BS_TCH_NONE;
		case 1 :
			return BS_TCH_CDTEXT;
		case 2 :
			return BS_TCH_INTERNETDB;
		case 3 :
			return BS_TCH_CDTEXT_INTERNETDB;
		case 4 :
			return BS_TCH_INTERNETDB_CDTEXT;
		default :
			return BS_TCH_NONE;
	}
}


KAudioGrabbingDialog::KAudioGrabbingDialog()
	:guisignal(NULL)
	,m_bReady(false)
{
}

KAudioGrabbingDialog::KAudioGrabbingDialog(FXWindow* owner, std::vector<int32> vTracks)
	:FXDialogBox(owner, "Grabbing audio track...", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	,guisignal(owner->getApp())
	,m_enState(ST_NONE)
	,m_vTracks(vTracks)	
	,m_bReady(true)
	,m_nCurrentTrack(0)
    ,m_bTrackSizeWasSet(false)
{
	FXVerticalFrame* mainFrame = new FXVerticalFrame(this, LAYOUT_FILL);
		new FXLabel(mainFrame, "Total progress:");
		m_barProgress = new FXProgressBar(mainFrame, NULL, 0, PROGRESSBAR_NORMAL|LAYOUT_FILL_X);

		FXHorizontalFrame* bytesWrittenFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(bytesWrittenFrame, "Bytes converted: ");
			m_lblBytesWritten = new FXLabel(bytesWrittenFrame, "");

		FXHorizontalFrame* trackSizeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(trackSizeFrame, "Track size (bytes): ");
			m_lblTotalSize = new FXLabel(trackSizeFrame, "");
		
		FXHorizontalFrame* timeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(timeFrame, "Time left: ");
			m_lblElapsed = new FXLabel(timeFrame, "");	
				FXString strElapsed;
				strElapsed.format("%.2d:%.2d:%.2d", 0, 0, 0);
				m_lblElapsed->setText(strElapsed);

		FXHorizontalFrame* trackFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			m_lblTrack = new FXLabel(trackFrame, "Current track: ");

		FXHorizontalFrame* encoderFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
		
		FXMatrix *pEncoderFrame = new FXMatrix(encoderFrame, 4, MATRIX_BY_ROWS);

			new FXLabel(pEncoderFrame, "Encoder :     ");
			m_cmbEncoder = new FXComboBox(pEncoderFrame, 4, this, ID_ENCODERBOX, 
				LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
			m_cmbEncoder->appendItem("MP3");
			m_cmbEncoder->appendItem("AAC");
			m_cmbEncoder->appendItem("OGG");
			m_cmbEncoder->appendItem("OPUS");
			m_cmbEncoder->appendItem("FLAC");

			m_cmbEncoder->setNumVisible(m_cmbEncoder->getNumItems());
			m_cmbEncoder->setCurrentItem(0);

			new FXLabel(pEncoderFrame, "");
			new FXLabel(pEncoderFrame, "");		

			new FXLabel(pEncoderFrame, "Bitrate type :    ");
			m_cmbBitrateType = new FXComboBox(pEncoderFrame, 8, this, ID_BITRATE_TYPE_BOX, 
				LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
			m_cmbBitrateType->appendItem("Constant");
			m_cmbBitrateType->appendItem("Variable");
			m_cmbBitrateType->appendItem("Average");
			m_cmbBitrateType->setNumVisible(m_cmbBitrateType->getNumItems());
			m_cmbBitrateType->setCurrentItem(0);
			
			new FXLabel(pEncoderFrame, "CBR Bitrate :");
			m_cmbBitrate = new FXComboBox(pEncoderFrame, 6, this, ID_BITRATE_BOX, 
				LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
			m_cmbBitrate->appendItem("64 kBit/s");
			m_cmbBitrate->appendItem("96 kBit/s");
			m_cmbBitrate->appendItem("128 kBit/s");
			m_cmbBitrate->appendItem("192 kBit/s");
			m_cmbBitrate->appendItem("256 kBit/s");
			m_cmbBitrate->appendItem("320 kBit/s");
			m_cmbBitrate->setNumVisible(m_cmbBitrate->getNumItems());
			m_cmbBitrate->setCurrentItem(0);


			new FXLabel(pEncoderFrame, "VBR Min Bitrate :");
			m_cmbBitrateMin = new FXComboBox(pEncoderFrame, 6, this, ID_BITRATE_MIN_BOX, 
				LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
			m_cmbBitrateMin->appendItem("64 kBit/s");
			m_cmbBitrateMin->appendItem("96 kBit/s");
			m_cmbBitrateMin->appendItem("128 kBit/s");
			m_cmbBitrateMin->appendItem("192 kBit/s");
			m_cmbBitrateMin->appendItem("256 kBit/s");
			m_cmbBitrateMin->appendItem("320 kBit/s");
			m_cmbBitrateMin->setNumVisible(m_cmbBitrateMin->getNumItems());
			m_cmbBitrateMin->setCurrentItem(0);
		
			new FXLabel(pEncoderFrame, "VBR Max Bitrate :");
			m_cmbBitrateMax = new FXComboBox(pEncoderFrame, 6, this, ID_BITRATE_MAX_BOX, 
				LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
			m_cmbBitrateMax->appendItem("64 kBit/s");
			m_cmbBitrateMax->appendItem("96 kBit/s");
			m_cmbBitrateMax->appendItem("128 kBit/s");
			m_cmbBitrateMax->appendItem("192 kBit/s");
			m_cmbBitrateMax->appendItem("256 kBit/s");
			m_cmbBitrateMax->appendItem("320 kBit/s");
			m_cmbBitrateMax->setNumVisible(m_cmbBitrateMax->getNumItems());
			m_cmbBitrateMax->setCurrentItem(0);

			new FXLabel(pEncoderFrame, "Quality :");
			m_cmbQuality = new FXComboBox(pEncoderFrame, 6, this, ID_BITRATE_QUALITY, 
				LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC);
			m_cmbQuality->appendItem("1");
			m_cmbQuality->appendItem("2");
			m_cmbQuality->appendItem("3");
			m_cmbQuality->appendItem("4");
			m_cmbQuality->appendItem("5");
			m_cmbQuality->appendItem("6");
			m_cmbQuality->appendItem("7");
			m_cmbQuality->appendItem("8");
			m_cmbQuality->appendItem("9");
			m_cmbQuality->setNumVisible(m_cmbQuality->getNumItems());
			m_cmbQuality->setCurrentItem(0);


		FXHorizontalFrame* tagsFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(tagsFrame, "Add tags :     ");
			m_cmbTagChoice = new FXComboBox(tagsFrame, 6, this, ID_BITRATE_MAX_BOX, 
				LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK|COMBOBOX_STATIC|LAYOUT_FIX_HEIGHT, 0, 0, 0, 20);
			m_cmbTagChoice->appendItem("Don't add");
			m_cmbTagChoice->appendItem("From CD-Text only");
			m_cmbTagChoice->appendItem("From Internet only");
			m_cmbTagChoice->appendItem("CD-Text first, Internet last");
			m_cmbTagChoice->appendItem("Internet first, CD-Text last");
			m_cmbTagChoice->setNumVisible(m_cmbTagChoice->getNumItems());
			m_cmbTagChoice->setCurrentItem(1);

		FXHorizontalFrame* pathFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(pathFrame, "Save path :   ");

			
			m_txtSavePath = new FXTextField(pathFrame, 30, 0, 0, TEXTFIELD_READONLY | FRAME_SUNKEN);

			m_btnBrowse = new FXButton(pathFrame, "&Browse", 0, this, ID_BROWSE);
		
		m_btnAbort = new FXButton(mainFrame, "&Convert", 0, this, KAudioGrabbingDialog::ID_USERACTION,
			BUTTON_NORMAL|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH, 0, 0, 70, 25 );

	OnCreate();


}

void KAudioGrabbingDialog::OnCreate()
{
	if (!m_bReady)
	{
		return;
	}

	if (m_vTracks.size() == 0)
	{
		Done();
	}

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------

	SetProcessEventCallback((ProcessEvent) /*static*/ KAudioGrabbingDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KAudioGrabbingDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KAudioGrabbingDialog::OnBurnDoneEvent, this);

	FXString strTrack;
	strTrack.format("Current track: %d", m_vTracks[m_nCurrentTrack]);
	m_lblTrack->setText(strTrack);
	
	onBitrateTypeBox(this, 0, 0);
}

void KAudioGrabbingDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

KAudioGrabbingDialog::~KAudioGrabbingDialog()
{
}

long KAudioGrabbingDialog::onUserAction(FXObject* sender, FXSelector key, void* data)
{
	if (FXSELTYPE(key) == SEL_CLOSE || FXSELID(key) == FXDialogBox::ID_CANCEL)
	{

	#ifdef MAC
		if (FXSELID(key) == FXDialogBox::ID_CANCEL)
		{
			return 1;
		}
	#endif

		m_enState = ST_CANCELLED;
	
		if (::Abort() != BS_SDK_ERROR_NO)
		{
			getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
			RestoreEvents();
			
			return FXDialogBox::onCmdCancel(sender, key, data);
		}
	
	}
	else if (FXSELID(key) == KAudioGrabbingDialog::ID_USERACTION)
	{
		if (ST_PROCESSING == m_enState)
		{
			m_enState = ST_ABORTED;
		
			if (BS_SDK_ERROR_NO == ::Abort())
			{
				m_btnAbort->disable();
			}
			else
			{
				Done();
			}
		}
		else if (ST_NONE == m_enState)
		{		
			StartJob();
		}
		else
		{
			RestoreEvents();
			return FXDialogBox::onCmdCancel(sender, key, data);	
		}
	}

	return 1;
}

void KAudioGrabbingDialog::StartJob()
{
	FXASSERT(m_nCurrentTrack < (int)m_vTracks.size());
			
	FXString strSavePath;
	
	strSavePath = m_txtSavePath->getText();
	
	if (strSavePath.length() == 0) 
	{
		FXMessageBox::error(this, MBOX_OK, "IsoSDK", "Please, specify the file name.");
		return;
	}

	if (m_nCurrentTrack >= (int)m_vTracks.size())
	{
		FXDialogBox::onCmdCancel(this, 0, 0);
		return;
	}

	int32 res;
	SAudioGrabbingParams params;
	//moved upper 
	//FXString strSavePath;

	switch(m_cmbBitrateType->getCurrentItem()){
		case 0:
			params.nBitrateType = BS_BT_CONSTANT;
			break;
		case 1:
			params.nBitrateType = BS_BT_VARIABLE;
			break;
		case 2:
			params.nBitrateType = BS_BT_AVERAGE;
			break;
	}
	

	params.nBitrate		= ComboIndex2Bitrate(m_cmbBitrate->getCurrentItem());
	params.nMinBitrate	= ComboIndex2Bitrate(m_cmbBitrateMin->getCurrentItem());
	params.nMaxBitrate	= ComboIndex2Bitrate(m_cmbBitrateMax->getCurrentItem());
	params.nQuality		= m_cmbQuality->getCurrentItem();
	params.nEncoderType	= ComboIndex2EncoderIndex(m_cmbEncoder->getCurrentItem());
	params.nTagChoice	= ComboIndex2TagChoice(m_cmbTagChoice->getCurrentItem());

	if (params.nMinBitrate > params.nMaxBitrate)
	{
		FXMessageBox::error(this, MBOX_OK, "IsoSDK", "Bitrates are not correct.");
		return;
	}

	if (params.nTagChoice > 1)
	{
		int32 h = BS_INVALID_TAG_HANDLE;
		CALL_FXDIALOG(::TagsFromNetworkDialog(BS_READ_DEVICE, &h));
		params.nNetworkTagsHandle = h;
	}

	FXString strExt	= ComboIndex2FileExt(m_cmbEncoder->getCurrentItem());

	// Moved to the start of the converting handling.
	// m_txtSavePath->getText(strSavePath);

	FXint pos = strSavePath.find_last_of(".");

	if (pos != -1)
	{
		strSavePath = strSavePath.left(pos) + strExt;
	}
	else
	{
		strSavePath += strExt;
	}

	m_txtSavePath->setText(strSavePath);

	res = ::GrabAudioTrack(params, m_vTracks[m_nCurrentTrack++], Fox2SDKString(strSavePath));
	handleError(res);

	if (res == BS_SDK_ERROR_NO)
	{
		m_nStartTime = FXThread::time()/1000/1000/1000;	
		getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));

		m_enState = ST_PROCESSING;
		m_btnAbort->setText("&Abort");
	}

	m_btnBrowse->disable();
	m_cmbEncoder->disable();
	m_cmbBitrateType->disable();
	m_cmbBitrate->disable();
	m_cmbBitrateMin->disable();
	m_cmbBitrateMax->disable();
	m_cmbTagChoice->disable();
	m_cmbQuality->disable();
	m_txtSavePath->disable();
}

long KAudioGrabbingDialog::onBrowse(FXObject* sender, FXSelector key, void* data)
{
	FXFileDialog FileDialog(this, "Choose file to save please...");

	FXString strPattern;
	FXString strExt = ComboIndex2FileExt(m_cmbEncoder->getCurrentItem());		
	strPattern.format("Supported format (*%s)", strExt.text());

	FileDialog.setPatternList(strPattern);
	FileDialog.setSelectMode(SELECTFILE_ANY);
	if(!FileDialog.execute(PLACEMENT_SCREEN))
	{
		return 1;
	}
	
	FX::FXSystem::setCurrentDirectory(FileDialog.getDirectory());
	FXString strFileName = FXString::compose(FileDialog.getFilename(), false);

	if (strFileName.right(strExt.length()) != strExt)
	{
		strFileName += strExt;
	}

	m_txtSavePath->setText(strFileName);

	return 1;
}

/*static*/ void KAudioGrabbingDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
				double dBytesWritten, double dImageSize, KAudioGrabbingDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, dImageSize);
}

void KAudioGrabbingDialog::SetProgress(int nProgress, double nBytesWritten, double nTrackSize)
{
	m_cProgressInfo.nProgress = nProgress;
	m_cProgressInfo.fBytesWritten = nBytesWritten;
	m_cProgressInfo.fTrackSize = nTrackSize;

	//getApp()->addChore(this, KAudioGrabbingDialog::ID_SETPROGRESS, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KAudioGrabbingDialog::ID_SETPROGRESS),NULL,NULL);
}

long KAudioGrabbingDialog::onSetProgress(FXObject* sender, FXSelector key, void* data)
{
	// Freezing progress after abort fixed.
	if (m_enState == ST_PROCESSING) 
	{
		m_barProgress->setProgress(m_cProgressInfo.nProgress);
		m_lblBytesWritten->setText(FXString::value("%.0f", m_cProgressInfo.fBytesWritten));		
	}
	else // Aborted: reset progress to 0.
	{
		m_barProgress->setProgress(0);
		m_lblBytesWritten->setText("0");		
	}
	
	// Fixed perfomance issue: the same text was printed many times.
	if (!m_bTrackSizeWasSet)
	{
		m_lblTotalSize->setText(FXString::value("%.0f", m_cProgressInfo.fTrackSize));
		m_bTrackSizeWasSet = true;
	}
	
	return 1;
}

/*static*/ void KAudioGrabbingDialog::OnJobDoneEvent(KAudioGrabbingDialog *pDlg)
{
	pDlg->OnJobDone();
}

void KAudioGrabbingDialog::OnJobDone()
{
	//getApp()->addChore(this, KAudioGrabbingDialog::ID_JOBDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KAudioGrabbingDialog::ID_JOBDONE),NULL,NULL);
}

long KAudioGrabbingDialog::onChoreJobDone(FXObject* sender, FXSelector key, void* data)
{
	switch (m_enState)
	{
		case ST_PROCESSING :

			if (m_nCurrentTrack == m_vTracks.size())
			{
				Done();
			}
			else
			{
				m_enState = ST_NONE;

				FXString strTrack;
				strTrack.format("Current track: %d", m_vTracks[m_nCurrentTrack]);
				m_lblTrack->setText(strTrack);

				FXString temp;
				temp.format("Track%d", m_vTracks[m_nCurrentTrack]);
				FXString strSavePath;
				strSavePath = m_txtSavePath->getText();

				strSavePath = strSavePath.left(strSavePath.find_last_of(PATHSEPSTRING) + 1);
				strSavePath += temp;
				strSavePath += ComboIndex2FileExt(m_cmbEncoder->getCurrentItem());
				m_txtSavePath->setText(strSavePath);

				m_enState = ST_NONE;
				m_btnAbort->setText("&Convert");
			}

		break;

		case ST_ABORTED :
			
			Done();

		break;
	}

	return 1;
}

void KAudioGrabbingDialog::Done()
{
	m_enState = ST_DONE;
	m_btnAbort->enable();
	m_btnAbort->setText("&Close");
	getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
}

/*static*/ void KAudioGrabbingDialog::OnBurnDoneEvent(const TCHAR *pcError, KAudioGrabbingDialog* pDlg)
{
	pDlg->OnBurnDone(pcError);
}

void KAudioGrabbingDialog::OnBurnDone(const TCHAR *pcError)
{
	m_strCallbackError = SDK2FoxString(pcError);

	//getApp()->addChore(this, KAudioGrabbingDialog::ID_BURNDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KAudioGrabbingDialog::ID_BURNDONE),NULL,NULL);
}

long KAudioGrabbingDialog::onChoreBurnDone(FXObject* sender, FXSelector key, void* data)
{
	if (m_strCallbackError.length() != 0)
	{
		FXMessageBox msgBox(this, "Saving track", m_strCallbackError, NULL, MBOX_OK);
		msgBox.execute();
	}

	if (ST_CANCELLED == m_enState)
	{
		getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
		return FXDialogBox::onCmdCancel(sender, key, data);
	}
	

	return 1;
}

long KAudioGrabbingDialog::onTimer(FXObject* sender, FXSelector key, void* data)
{
	FXTime nNow = FXThread::time()/1000/1000/1000;

	FXint second = (nNow - m_nStartTime) % 60;
	FXint minute = ((nNow - m_nStartTime) / 60) % 60;
	FXint hour   = ((nNow - m_nStartTime) / 3600);

	FXString strElapsed;
	strElapsed.format("%.2d:%.2d:%.2d", hour, minute, second);
	m_lblElapsed->setText(strElapsed);

	if (ST_PROCESSING == m_enState)
	{
		getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
	}	
	
	return 1;
}

long KAudioGrabbingDialog::onEncoderBox(FXObject* sender, FXSelector key, void* data)
{
	bool bVariablePossible = false;
	bool bAveragePossible = false;

	switch (ComboIndex2EncoderIndex(m_cmbEncoder->getCurrentItem()))
	{
		case BS_ET_MP3:
			bAveragePossible = true;
			bVariablePossible = true;
			break;
		case BS_ET_OGG:
		case BS_ET_AAC:
		case BS_ET_OPUS:
			bVariablePossible = true;
		break;

		
		case BS_ET_FLAC:
			bVariablePossible = false;
		break;
			
	}

	m_cmbBitrateType->clearItems();
	m_cmbBitrateType->appendItem("Constant");
	
	if (bVariablePossible)
	{
		m_cmbBitrateType->appendItem("Variable");
	}
	if (bAveragePossible)
	{
		m_cmbBitrateType->appendItem(_T("Average"));
	}

	m_cmbBitrateType->setCurrentItem(0);
	onBitrateTypeBox(sender, key, data);


	FXString strFileName(_T(""));
	strFileName = m_txtSavePath->getText();

	if (!strFileName.empty())
	{
		FXString strExt = ComboIndex2FileExt(m_cmbEncoder->getCurrentItem());

		int pos = strFileName.rfind(_T('.'));

		if (pos != -1)
		{
			strFileName = strFileName.left(pos) + strExt;
		}
		else
		{
			strFileName += strExt;
		}

		m_txtSavePath->setText(strFileName);
	}

	return 1;
}

long KAudioGrabbingDialog::onBitrateTypeBox(FXObject* sender, FXSelector key, void* data)
{
	FXint item = m_cmbBitrateType->getCurrentItem();

	switch (ComboIndex2EncoderIndex(m_cmbEncoder->getCurrentItem()))
	{
	case BS_ET_MP3:
		switch (item) {
		case 0:
			m_cmbBitrate->enable();
			m_cmbBitrateMin->disable();
			m_cmbBitrateMax->disable();
			m_cmbQuality->disable();
			break;
		case 1:
			m_cmbBitrate->disable();
			m_cmbBitrateMin->enable();
			m_cmbBitrateMax->enable();
			m_cmbQuality->disable();
			break;
		case 2:
			m_cmbBitrate->enable();
			m_cmbBitrateMin->disable();
			m_cmbBitrateMax->disable();
			m_cmbQuality->disable();
			break;
		}
		break;
	case BS_ET_OGG:
		switch (item) {
		case 0:
			m_cmbBitrate->enable();
			m_cmbBitrateMin->disable();
			m_cmbBitrateMax->disable();
			m_cmbQuality->disable();
			break;
		case 1:
			m_cmbBitrate->disable();
			m_cmbBitrateMin->enable();
			m_cmbBitrateMax->enable();
			m_cmbQuality->disable();
			break;
		}
		break;
	
	case BS_ET_AAC:
		switch (item) {
		case 0:
			m_cmbBitrate->enable();
			m_cmbBitrateMin->disable();
			m_cmbBitrateMax->disable();
			m_cmbQuality->disable();
			break;
		case 1:
			m_cmbBitrate->disable();
			m_cmbBitrateMin->disable();
			m_cmbBitrateMax->disable();
			m_cmbQuality->enable();
			break;
		}
		break;
	case BS_ET_OPUS:
		m_cmbBitrate->enable();
		m_cmbBitrateMin->disable();
		m_cmbBitrateMax->disable();
		m_cmbQuality->enable();
		break;
	case BS_ET_FLAC:
		m_cmbBitrate->disable();
		m_cmbBitrateMin->disable();
		m_cmbBitrateMax->disable();
		m_cmbQuality->enable();
		break;
	}

	return 0;
}

long KAudioGrabbingDialog::onMinBitrateBox(FXObject* sender, FXSelector key, void* data)
{
	FXint nMinBitrate	= ComboIndex2Bitrate(m_cmbBitrateMin->getCurrentItem());
	FXint nMaxBitrate	= ComboIndex2Bitrate(m_cmbBitrateMax->getCurrentItem());

	if (nMinBitrate > nMaxBitrate)
	{
		m_cmbBitrateMax->setCurrentItem(m_cmbBitrateMin->getCurrentItem());
	}

	return 0;
}

long KAudioGrabbingDialog::onMaxBitrateBox(FXObject* sender, FXSelector key, void* data)
{
	FXint nMinBitrate	= ComboIndex2Bitrate(m_cmbBitrateMin->getCurrentItem());
	FXint nMaxBitrate	= ComboIndex2Bitrate(m_cmbBitrateMax->getCurrentItem());

	if (nMaxBitrate < nMinBitrate)
	{
		m_cmbBitrateMin->setCurrentItem(m_cmbBitrateMax->getCurrentItem());
	}

	return 0;
}

void KAudioGrabbingDialog::handleError(int32 errCode)
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
		
		FXMessageBox msgBox(this, "Saving track", SDK2FoxString((const TCHAR*)strError), NULL, MBOX_OK);
		msgBox.execute();
	}
}
