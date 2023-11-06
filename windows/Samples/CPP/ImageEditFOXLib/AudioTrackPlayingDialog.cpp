#include "stdafx.h"
#include "AudioTrackPlayingDialog.h"

FXDEFMAP(KPlayTrackDialog) KSampleBurnMap[]= {
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KPlayTrackDialog::onCancel),
	FXMAPFUNC(SEL_CLOSE, 0, KPlayTrackDialog::onCancel),
	FXMAPFUNC(SEL_CHORE, KPlayTrackDialog::ID_JOBDONE, KPlayTrackDialog::onChoreJobDone),
	FXMAPFUNC(SEL_CHORE, KPlayTrackDialog::ID_BURNDONE, KPlayTrackDialog::onChoreBurnDone),
	FXMAPFUNC(SEL_CHORE, KPlayTrackDialog::ID_SETPROGRESS, KPlayTrackDialog::onSetProgress),
	FXMAPFUNC(SEL_TIMEOUT, KPlayTrackDialog::ID_TOTALTIME, KPlayTrackDialog::onTimer),
};

FXIMPLEMENT(KPlayTrackDialog, FXDialogBox, KSampleBurnMap, ARRAYNUMBER(KSampleBurnMap))

KPlayTrackDialog::KPlayTrackDialog()
	:guisignal(NULL)
	,m_bReady(false)
{
}

KPlayTrackDialog::KPlayTrackDialog(FXWindow* owner, int16 nTrackNumber)
	:FXDialogBox(owner, "Playing track...", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	,guisignal(owner->getApp())
	,m_enState(ST_NONE)
	,m_nTrackNumber(nTrackNumber)
	,m_bReady(true)
{	
	FXVerticalFrame* mainFrame = new FXVerticalFrame(this, LAYOUT_FILL|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 350, 160);
		new FXLabel(mainFrame, "Total progress:");
		m_barProgress = new FXProgressBar(mainFrame, NULL, 0, PROGRESSBAR_NORMAL|LAYOUT_FILL_X);

		FXHorizontalFrame* bytesPlayedFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(bytesPlayedFrame, "Bytes played: ");
			m_lblBytesPlayed = new FXLabel(bytesPlayedFrame, "");

		FXHorizontalFrame* trackSizeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(trackSizeFrame, "Total track size (bytes): ");
			m_lblTrackSize = new FXLabel(trackSizeFrame, "");

		
		FXHorizontalFrame* timeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);			
			m_lblElapsed = new FXLabel(timeFrame, "Total Time: ");

		m_btnAbort = new FXButton(mainFrame, "&Abort", 0, this, KPlayTrackDialog::ID_CANCEL);		
}

void KPlayTrackDialog::create()
{
	FXDialogBox::create();
	if(!m_bReady)
	{
		return;
	}

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KPlayTrackDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KPlayTrackDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KPlayTrackDialog::OnBurnDoneEvent, this);

	m_enState = ST_PROCESSING;
	
	int32 res = ::PlayAudioTrack(/*BS_READ_DEVICE,*/ m_nTrackNumber);	
	handleError(res);

	m_nStartTime = FXThread::time()/1000/1000/1000;
	
	getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
}

void KPlayTrackDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

KPlayTrackDialog::~KPlayTrackDialog()
{
}

long KPlayTrackDialog::onCancel(FXObject* sender, FXSelector key, void* data)
{
	if (FXSELTYPE(key) == SEL_CLOSE)
	{
		m_enState = ST_CANCELLED;
	
		if (::Abort() != BS_SDK_ERROR_NO)
		{
			getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
			RestoreEvents();
			return FXDialogBox::onCmdCancel(sender, key, data);
		}
	}
	else if(FXSELID(key) == FXDialogBox::ID_CANCEL)
	{
		if (m_enState == ST_PROCESSING)
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
		else
		{
			RestoreEvents();
			return FXDialogBox::onCmdCancel(sender, key, data);	
		}
	}

	return 1;
}

/*static*/ void KPlayTrackDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, 
		float fCache, double dBytesWritten, double dImageSize, KPlayTrackDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, dImageSize);
}

void KPlayTrackDialog::SetProgress(int nProgress, double nBytesPlayed, double nTrackSize)
{
	m_cProgressInfo.nProgress = nProgress;
	m_cProgressInfo.fBytesPlayed = nBytesPlayed;
	m_cProgressInfo.fTrackSize = nTrackSize;

	//getApp()->addChore(this, KPlayTrackDialog::ID_SETPROGRESS, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KPlayTrackDialog::ID_SETPROGRESS),NULL,NULL);
}

long KPlayTrackDialog::onSetProgress(FXObject* sender, FXSelector key, void* data)
{
	m_barProgress->setProgress(m_cProgressInfo.nProgress);
	m_lblBytesPlayed->setText(FXString::value("%.0f", m_cProgressInfo.fBytesPlayed));
	m_lblTrackSize->setText(FXString::value("%.0f", m_cProgressInfo.fTrackSize));
	return 1;
}

/*static*/ void KPlayTrackDialog::OnBurnDoneEvent(const TCHAR *pcError, KPlayTrackDialog* pDlg)
{
	pDlg->OnBurnDone(pcError);
}

void KPlayTrackDialog::OnBurnDone(const TCHAR *pcError)
{
	m_strCallbackError = SDK2FoxString(pcError);

	//getApp()->addChore(this, KPlayTrackDialog::ID_BURNDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KPlayTrackDialog::ID_BURNDONE),NULL,NULL);
}

long KPlayTrackDialog::onChoreBurnDone(FXObject* sender, FXSelector key, void* data)
{
	if (m_strCallbackError.length() != 0)
	{
		FXMessageBox msgBox(this, "Playing track", m_strCallbackError, NULL, MBOX_OK);
		msgBox.execute();		
	}
	return 1;
}

/*static*/ void KPlayTrackDialog::OnJobDoneEvent(KPlayTrackDialog *pDlg)
{
	pDlg->OnJobDone();
}


void KPlayTrackDialog::OnJobDone()
{
	//getApp()->addChore(this, KPlayTrackDialog::ID_JOBDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KPlayTrackDialog::ID_JOBDONE),NULL,NULL);
}

long KPlayTrackDialog::onChoreJobDone(FXObject* sender, FXSelector key, void* data)
{
	switch (m_enState)
	{
		case ST_PROCESSING :
		case ST_ABORTED :
			
			Done();
		
		break;

		case ST_CANCELLED :

			getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
			return FXDialogBox::onCmdCancel(sender, key, data);
	}

	return 1;
}

void KPlayTrackDialog::Done()
{
	m_enState = ST_DONE;
	m_btnAbort->enable();
	m_btnAbort->setText("&Close");
	getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
}

long KPlayTrackDialog::onTimer(FXObject* sender, FXSelector key, void* data)
{
	FXTime nNow = FXThread::time()/1000/1000/1000;

	FXint second = (nNow - m_nStartTime) % 60;
	FXint minute = ((nNow - m_nStartTime) / 60) % 60;
	FXint hour   = ((nNow - m_nStartTime) / 3600);

	FXString strElapsed;
	strElapsed.format("Total Time: %.2d:%.2d:%.2d", hour, minute, second);
	m_lblElapsed->setText(strElapsed);

	if (m_enState == ST_PROCESSING)
	{
		getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
	}	
	
	return 1;
}

void KPlayTrackDialog::handleError(int32 errCode)
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
		
		FXMessageBox msgBox(this, "Playing track", SDK2FoxString((const wchar_t*)strError), NULL, MBOX_OK);
		msgBox.execute();
	}
}
