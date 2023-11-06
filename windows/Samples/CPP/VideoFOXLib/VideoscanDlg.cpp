#include "stdafx.h"
#include "VideoscanDlg.h"


FXDEFMAP(KVideoScanDlg) KVideoScanDlgMap[]= {
	FXMAPFUNC(SEL_CHORE, KVideoScanDlg::ID_SETVIDEOSCANPROGRESS, KVideoScanDlg::onSetVideoScanProgress),
	FXMAPFUNC(SEL_CHORE, KVideoScanDlg::ID_VIDEOSCANCOMPLETE, KVideoScanDlg::onVideoScanComplete),
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KVideoScanDlg::onCmdCancel)	
};

FXIMPLEMENT(KVideoScanDlg, FXDialogBox, KVideoScanDlgMap, ARRAYNUMBER(KVideoScanDlgMap))

KVideoScanDlg::KVideoScanDlg(FXApp *app, const FXString &title)
	: FXDialogBox(app, title, DECOR_TITLE)
	, guisignal(app)
{
	m_lbl = new FXLabel(this, "Scanning Mpeg File...", NULL, LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 200, 30);
	m_barProgress = new FXProgressBar(this, NULL, 0, FRAME_THICK|FRAME_SUNKEN|LAYOUT_FILL_X);
	
	new FXButton(this, "Cancel", NULL, this, FXDialogBox::ID_CANCEL,
		FRAME_RAISED|FRAME_THICK|LAYOUT_SIDE_BOTTOM|LAYOUT_CENTER_X|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,
		0, 0, 80, 30);
}

KVideoScanDlg::KVideoScanDlg()
	: guisignal(NULL)
{
}

KVideoScanDlg::~KVideoScanDlg()
{
}

void KVideoScanDlg::OnVideoScannerEvent(float progress)
{
	m_videoScanProgressInfo.progress = progress;
	//getApp()->addChore(this, KVideoScanDlg::ID_SETVIDEOSCANPROGRESS, &m_videoScanProgressInfo);	
	guisignal.message(this,FXSEL(SEL_CHORE, KVideoScanDlg::ID_SETVIDEOSCANPROGRESS),&m_videoScanProgressInfo,sizeof(m_videoScanProgressInfo));
}

void KVideoScanDlg::OnVideoScanDoneEvent(const FXString &strError, FXint nErrorCode, struct SVideoFormat CurrentFormat)
{	
	m_strPlaytime.format("%i:%i", CurrentFormat.nPlaytime / 60, CurrentFormat.nPlaytime % 60);
	m_strFrameRate.format("%.2lf Frames/sec", CurrentFormat.fFPS);
	m_strBitrate.format("%d bits/s", CurrentFormat.nBitRate);
	m_strAspectRatio.format("%i", CurrentFormat.nAspectRatio);
	m_strDimensions.format("%i X %i", CurrentFormat.nWidth, CurrentFormat.nHeight);

	m_videoScanErrorInfo.nErrorCode = nErrorCode;
	m_videoScanErrorInfo.strErrorString = strError;
	
	//getApp()->addChore(this, KVideoScanDlg::ID_VIDEOSCANCOMPLETE, &m_videoScanErrorInfo);
	guisignal.message(this,FXSEL(SEL_CHORE, KVideoScanDlg::ID_VIDEOSCANCOMPLETE),&m_videoScanErrorInfo,sizeof(m_videoScanErrorInfo));
}

FXuint KVideoScanDlg::execute(FXuint placement)
{
	int32 res = ::AddFile(m_fileToAdd);
	
	m_lbl->setText("Scanning Mpeg File...");

	if (res == BS_SDK_ERROR_NO)
	{
		return FXDialogBox::execute(placement);
	}

	return 0;
}

long KVideoScanDlg::onCmdCancel(FXObject* sender, FXSelector key, void* data)
{
	::StopMpegAction();

	return FXDialogBox::onCmdCancel(sender, key, data);
}

long KVideoScanDlg::onSetVideoScanProgress(FXObject* sender, FXSelector key, void* data)
{
	VIDEOSCANPROGRESSINFO *videoScanProgInfo = (VIDEOSCANPROGRESSINFO*) data;
	
	if (NULL != videoScanProgInfo) 
	{
		m_barProgress->setProgress((FXuint)(videoScanProgInfo->progress));
	}

	return 1;
}

long KVideoScanDlg::onVideoScanComplete(FXObject* sender, FXSelector key, void* data)
{
	VIDEOSCANERRORINFO *videoScanErrorInfo = (VIDEOSCANERRORINFO*) data;
	
	if (0 == videoScanErrorInfo->nErrorCode) {
		FXDialogBox::onCmdAccept(NULL, 0, NULL);
	}
	else {		
		m_lbl->setText(videoScanErrorInfo->strErrorString);
		m_barProgress->setProgress(0);
	}
	
	return 1;
}
