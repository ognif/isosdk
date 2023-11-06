#include "stdafx.h"
#include "SaveDiscDialog.h"

FXDEFMAP(KSaveDiscDialog) KSampleBurnMap[]= {
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KSaveDiscDialog::onCancel),
	FXMAPFUNC(SEL_CLOSE, 0, KSaveDiscDialog::onCancel),
	FXMAPFUNC(SEL_CHORE, KSaveDiscDialog::ID_JOBDONE, KSaveDiscDialog::onChoreJobDone),
	FXMAPFUNC(SEL_CHORE, KSaveDiscDialog::ID_BURNDONE, KSaveDiscDialog::onChoreBurnDone),
	FXMAPFUNC(SEL_TIMEOUT, KSaveDiscDialog::ID_TOTALTIME, KSaveDiscDialog::onTimer),
	FXMAPFUNC(SEL_CHORE, KSaveDiscDialog::ID_SETPROGRESS, KSaveDiscDialog::onSetProgress),
};

FXIMPLEMENT(KSaveDiscDialog, FXDialogBox, KSampleBurnMap, ARRAYNUMBER(KSampleBurnMap))

KSaveDiscDialog::KSaveDiscDialog()
	:guisignal(NULL)
	,m_bReady(false)
{
}

KSaveDiscDialog::KSaveDiscDialog(FXWindow* owner, const FXString& strFilePath, int16 nFileFormat)
	:FXDialogBox(owner, "Saving disc...", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	,guisignal(owner->getApp())
	,m_enState(ST_NONE)	
	,m_strFilePath(strFilePath)
	,m_nFileFormat(nFileFormat)
	,m_bReady(true)
{	
	FXVerticalFrame* mainFrame = new FXVerticalFrame(this, LAYOUT_FILL|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 350, 210);
		new FXLabel(mainFrame, "Total progress:");
		m_barProgress = new FXProgressBar(mainFrame, NULL, 0, PROGRESSBAR_NORMAL|LAYOUT_FILL_X);

		FXHorizontalFrame* bytesWrittenFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(bytesWrittenFrame, "Current Sector: ");
			m_lblCurrentSector = new FXLabel(bytesWrittenFrame, "");

		FXHorizontalFrame* discSizeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(discSizeFrame, "Total Sectors:   ");
			m_lblTotalSectors = new FXLabel(discSizeFrame, "");

		FXHorizontalFrame* discErrorsFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(discErrorsFrame, "Read Errors: ");
			m_lblErrorsCount = new FXLabel(discErrorsFrame, "");
		
		FXHorizontalFrame* timeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);			
			m_lblElapsed = new FXLabel(timeFrame, "Total Time: ");

		m_btnAbort = new FXButton(mainFrame, "&Abort", 0, this, KSaveDiscDialog::ID_CANCEL);		
}

void KSaveDiscDialog::create()
{
	FXDialogBox::create();

	if(!m_bReady)
	{
		return;
	}

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KSaveDiscDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KSaveDiscDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KSaveDiscDialog::OnBurnDoneEvent, this);

	m_enState = ST_PROCESSING;
		
	SCreateImageParams cCreateImageParams;
	
	cCreateImageParams.cErrorParams.bErrorCorrection = BS_TRUE;	
	_tcscpy(cCreateImageParams.lpszImagePath, (const TCHAR*)Fox2SDKString(m_strFilePath));
	cCreateImageParams.nImageType = m_nFileFormat;	
	cCreateImageParams.cErrorParams.nHardwareRetryCount = (uint8)20;
	cCreateImageParams.cErrorParams.nSoftwareRetryCount = (uint8)20;
		
	int32 res = ::CreateImage(cCreateImageParams, BS_IMGTASK_CREATE);
	handleError(res);

	m_nStartTime = FXThread::time()/1000/1000/1000;
	
	getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
}

void KSaveDiscDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

KSaveDiscDialog::~KSaveDiscDialog()
{
}

long KSaveDiscDialog::onCancel(FXObject* sender, FXSelector key, void* data)
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

/*static*/ void KSaveDiscDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
			double dBytesWritten, double dImageSize, KSaveDiscDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, (int)dImageSize, (int)fDeviceBuffer * 1000);
}

void KSaveDiscDialog::SetProgress(int nProgress, double dCurrentSector, double dTotalSectors, int nErrorsCount)
{
	m_cProgressInfo.nProgress = nProgress;
	m_cProgressInfo.dCurrentSector = dCurrentSector;
	m_cProgressInfo.dTotalSectors = dTotalSectors;
	m_cProgressInfo.nErrorsCount = nErrorsCount;

	//getApp()->addChore(this, KSaveDiscDialog::ID_SETPROGRESS, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveDiscDialog::ID_SETPROGRESS),NULL,NULL);
}

long KSaveDiscDialog::onSetProgress(FXObject* sender, FXSelector key, void* data)
{
	m_barProgress->setProgress(m_cProgressInfo.nProgress);
	m_lblCurrentSector->setText(FXString::value("%.0f", m_cProgressInfo.dCurrentSector));
	m_lblTotalSectors->setText(FXString::value("%.0f", m_cProgressInfo.dTotalSectors));
	m_lblErrorsCount->setText(FXString::value("%d", m_cProgressInfo.nErrorsCount));
	return 1;
}


/*static*/ void KSaveDiscDialog::OnJobDoneEvent(KSaveDiscDialog *pDlg)
{
	pDlg->OnJobDone();
}

void KSaveDiscDialog::OnJobDone()
{
	//getApp()->addChore(this, KSaveDiscDialog::ID_JOBDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveDiscDialog::ID_JOBDONE),NULL,NULL);
}

long KSaveDiscDialog::onChoreJobDone(FXObject* sender, FXSelector key, void* data)
{
	switch (m_enState)
	{
		case ST_PROCESSING :
		case ST_ABORTED :
			
			Done();
			return 1;

		case ST_CANCELLED :

			getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
			return FXDialogBox::onCmdCancel(sender, key, data);
	}

	return 0;
}

void KSaveDiscDialog::Done()
{
	m_enState = ST_DONE;
	m_btnAbort->enable();
	m_btnAbort->setText("&Close");
	getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
}

/*static*/ void KSaveDiscDialog::OnBurnDoneEvent(const TCHAR *pcError, KSaveDiscDialog* pDlg)
{
	pDlg->OnBurnDone(pcError);
}

void KSaveDiscDialog::OnBurnDone(const TCHAR *pcError)
{
	m_strCallbackError = SDK2FoxString(pcError);

	//getApp()->addChore(this, KSaveDiscDialog::ID_BURNDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveDiscDialog::ID_BURNDONE),NULL,NULL);
}

long KSaveDiscDialog::onChoreBurnDone(FXObject* sender, FXSelector key, void* data)
{
	if (m_strCallbackError.length() != 0)
	{
		FXMessageBox msgBox(this, "Playing track", m_strCallbackError, NULL, MBOX_OK);
		msgBox.execute();
	}

	return 1;
}

long KSaveDiscDialog::onTimer(FXObject* sender, FXSelector key, void* data)
{
	FXTime nNow = FXThread::time()/1000/1000/1000;

	FXint second = (nNow - m_nStartTime) % 60;
	FXint minute = ((nNow - m_nStartTime)/60) % 60;
	FXint hour   = ((nNow - m_nStartTime)/3600);

	FXString strElapsed;
	strElapsed.format("Total Time: %.2d:%.2d:%.2d", hour, minute, second);
	m_lblElapsed->setText(strElapsed);

	if (m_enState == ST_PROCESSING)
	{
		getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
	}
	
	return 1;
}

void KSaveDiscDialog::handleError(int32 errCode)
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

		FXMessageBox msgBox(this, "Saving disc", SDK2FoxString((const wchar_t*)strError), NULL, MBOX_OK);
		msgBox.execute();
	}
}
