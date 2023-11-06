#include "stdafx.h"
#include "SaveTrackDialog.h"

FXDEFMAP(KSaveTrackDialog) KSampleBurnMap[]= {
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KSaveTrackDialog::onCancel),
	FXMAPFUNC(SEL_CLOSE, 0, KSaveTrackDialog::onCancel),
	FXMAPFUNC(SEL_CHORE, KSaveTrackDialog::ID_JOBDONE, KSaveTrackDialog::onChoreJobDone),
	FXMAPFUNC(SEL_CHORE, KSaveTrackDialog::ID_BURNDONE, KSaveTrackDialog::onChoreBurnDone),
	FXMAPFUNC(SEL_CHORE, KSaveTrackDialog::ID_SETPROGRESS, KSaveTrackDialog::onSetProgress),
	FXMAPFUNC(SEL_TIMEOUT, KSaveTrackDialog::ID_TOTALTIME, KSaveTrackDialog::onTimer),
};

FXIMPLEMENT(KSaveTrackDialog, FXDialogBox, KSampleBurnMap, ARRAYNUMBER(KSampleBurnMap))

KSaveTrackDialog::KSaveTrackDialog()
	:guisignal(NULL)
	,m_bReady(false)
{
}

KSaveTrackDialog::KSaveTrackDialog(FXWindow* owner, int16 nTrackNumber, const FXString& strFilePath, unsigned int nFileFormat)
	:FXDialogBox(owner, "Saving track...", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	,guisignal(owner->getApp())
	,m_enState(ST_NONE)
	,m_nTrackNumber(nTrackNumber)
	,m_strFilePath(strFilePath)
	,m_nFileFormat(nFileFormat)
	,m_bReady(true)
{	
	FXVerticalFrame* mainFrame = new FXVerticalFrame(this, LAYOUT_FILL|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 350, 210);
		new FXLabel(mainFrame, "Total progress:");
		m_barProgress = new FXProgressBar(mainFrame, NULL, 0, PROGRESSBAR_NORMAL|LAYOUT_FILL_X);

		FXHorizontalFrame* bytesWrittenFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(bytesWrittenFrame, "Bytes written: ");
			m_lblBytesWritten = new FXLabel(bytesWrittenFrame, "");

		FXHorizontalFrame* trackSizeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(trackSizeFrame, "Total track size (bytes): ");
			m_lblTrackSize = new FXLabel(trackSizeFrame, "");

		
		FXHorizontalFrame* timeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);			
			m_lblElapsed = new FXLabel(timeFrame, "Total Time: ");

		m_btnAbort = new FXButton(mainFrame, "&Abort", 0, this, KSaveTrackDialog::ID_CANCEL);		
}

void KSaveTrackDialog::create()
{
	FXDialogBox::create();
	if(!m_bReady)
	{
		return;
	}

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KSaveTrackDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KSaveTrackDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KSaveTrackDialog::OnBurnDoneEvent, this);

	m_enState = ST_PROCESSING;
	
	int32 res;
	//You can set yourself the speed here.
	//res = ::SetReadSpeed(BS_READ_DEVICE,2822);
	//handleError(res);
	
	res = ::SaveTrackToFile(BS_READ_DEVICE, m_nTrackNumber, Fox2SDKString(m_strFilePath), m_nFileFormat);
	handleError(res);

	m_nStartTime = FXThread::time()/1000/1000/1000;
	
	getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
}

void KSaveTrackDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

KSaveTrackDialog::~KSaveTrackDialog()
{
}

long KSaveTrackDialog::onCancel(FXObject* sender, FXSelector key, void* data)
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

/*static*/ void KSaveTrackDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesWritten, double dImageSize, KSaveTrackDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, dImageSize);
}

void KSaveTrackDialog::SetProgress(int nProgress, double nBytesWritten, double nTrackSize)
{
	m_cProgressInfo.nProgress = nProgress;
	m_cProgressInfo.fBytesWritten = nBytesWritten;
	m_cProgressInfo.fTrackSize = nTrackSize;

	//getApp()->addChore(this, KSaveTrackDialog::ID_SETPROGRESS, NULL);

	guisignal.message(this,FXSEL(SEL_CHORE,KSaveTrackDialog::ID_SETPROGRESS),NULL,NULL);
}

long KSaveTrackDialog::onSetProgress(FXObject* sender, FXSelector key, void* data)
{
	m_barProgress->setProgress(m_cProgressInfo.nProgress);
	m_lblBytesWritten->setText(FXString::value("%.0f", m_cProgressInfo.fBytesWritten));
	m_lblTrackSize->setText(FXString::value("%.0f", m_cProgressInfo.fTrackSize));
	return 1;
}

/*static*/ void KSaveTrackDialog::OnJobDoneEvent(KSaveTrackDialog *pDlg)
{
	pDlg->OnJobDone();
}

void KSaveTrackDialog::OnJobDone()
{
	//getApp()->addChore(this, KSaveTrackDialog::ID_JOBDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveTrackDialog::ID_JOBDONE),NULL,NULL);
}

long KSaveTrackDialog::onChoreJobDone(FXObject* sender, FXSelector key, void* data)
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

void KSaveTrackDialog::Done()
{
	m_enState = ST_DONE;
	m_btnAbort->enable();
	m_btnAbort->setText("&Close");
	getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
}

/*static*/ void KSaveTrackDialog::OnBurnDoneEvent(const TCHAR *pcError, KSaveTrackDialog* pDlg)
{
	pDlg->OnBurnDone(pcError);
}

void KSaveTrackDialog::OnBurnDone(const TCHAR *pcError)
{
	m_strCallbackError = SDK2FoxString(pcError);

	//getApp()->addChore(this, KSaveTrackDialog::ID_BURNDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveTrackDialog::ID_BURNDONE),NULL,NULL);
}

long KSaveTrackDialog::onChoreBurnDone(FXObject* sender, FXSelector key, void* data)
{
	if (m_strCallbackError.length() != 0)
	{
		FXMessageBox msgBox(this, "Playing track", m_strCallbackError, NULL, MBOX_OK);
		msgBox.execute();
	}

	return 1;
}

long KSaveTrackDialog::onTimer(FXObject* sender, FXSelector key, void* data)
{
	FXTime nNow = FXThread::time()/1000/1000/1000;

	FXint second = (nNow - m_nStartTime) % 60;
	FXint minute = ((nNow - m_nStartTime) / 60) % 60;
	FXint hour   = ((nNow - m_nStartTime) / 3600);

	FXString strElapsed;
	strElapsed.format("Total Time: %.2d:%.2d:%.2d", hour, minute, second);
	m_lblElapsed->setText(strElapsed);

	if (ST_PROCESSING == m_enState)
	{
		getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
	}	
	
	return 1;
}

void KSaveTrackDialog::handleError(int32 errCode)
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
		
		FXMessageBox msgBox(this, "Saving track", SDK2FoxString((const wchar_t*)strError), NULL, MBOX_OK);
		msgBox.execute();
	}
}
