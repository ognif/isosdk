#include "stdafx.h"
#include "SampleBurnDlg.h"

FXDEFMAP(KSampleBurnDlg) KSampleBurnMap[]= {
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KSampleBurnDlg::onCancel),
	FXMAPFUNC(SEL_CLOSE, 0, KSampleBurnDlg::onCancel),
	FXMAPFUNC(SEL_COMMAND, KSampleBurnDlg::ID_SAVELOG, KSampleBurnDlg::onSaveLog),
	FXMAPFUNC(SEL_CHORE, KSampleBurnDlg::ID_ADDLOGLINE, KSampleBurnDlg::onAddLogLine),
	FXMAPFUNC(SEL_CHORE, KSampleBurnDlg::ID_SETPROGRESS, KSampleBurnDlg::onSetProgress),
	FXMAPFUNC(SEL_CHORE, KSampleBurnDlg::ID_JOBDONE, KSampleBurnDlg::onChoreJobDone),
	FXMAPFUNC(SEL_CHORE, KSampleBurnDlg::ID_BURNFILE, KSampleBurnDlg::onBurnFile),
	FXMAPFUNC(SEL_TIMEOUT, KSampleBurnDlg::ID_TOTALTIME, KSampleBurnDlg::onTimer),
};

FXIMPLEMENT(KSampleBurnDlg, FXDialogBox, KSampleBurnMap, ARRAYNUMBER(KSampleBurnMap))

#define TITLE_BURN_FORMAT "%d%% written on %s [%s]"
#define TITLE_VERIFY_FORMAT "%d%% verified on %s [%s]"

void KSampleBurnDlg::OnFinalizeEvent(KSampleBurnDlg* pDlg) 
{
	pDlg->AddLogLine("Finalize...");
	pDlg->m_enState = ST_FINALIZE;
}

void KSampleBurnDlg::OnBurnDoneEvent(const TCHAR* pcError, KSampleBurnDlg* pDlg) 
{
	if ((pcError == NULL) || (0 == _tcslen(pcError))) {
		pDlg->AddLogLine("Burn done");
	} 
	else {
		FXString strError = SDK2FoxString(pcError);
		pDlg->AddLogLine(strError);
		pDlg->AddLogLine("Burn done with errors");
	}

	pDlg->SetProgress(0,0);
}

void KSampleBurnDlg::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesWritten, double dImageSize, KSampleBurnDlg *pDlg) 
{
	pDlg->SetProgress((int)fPercent, (int)fCache);
}

void KSampleBurnDlg::OnStartVerifyEvent(KSampleBurnDlg *pDlg)
{
	pDlg->AddLogLine("Starting verification...");
	pDlg->m_enState = ST_VERIFY;
}

void KSampleBurnDlg::OnVerifyFileEvent(const TCHAR* pcFileName, KSampleBurnDlg *pDlg)
{
	FXString strFileName = SDK2FoxString(pcFileName);
	pDlg->AddLogLine(strFileName);
}

void KSampleBurnDlg::OnVerifyErrorEvent(const TCHAR* pcFileName, const TCHAR* pcError, KSampleBurnDlg *pDlg)
{
	FXString strError = SDK2FoxString(pcError);
	strError += ": ";
	strError += SDK2FoxString(pcFileName);

	pDlg->AddLogLine(strError);
}

void KSampleBurnDlg::OnVerifyDoneEvent(int nNumErrors, KSampleBurnDlg *pDlg)
{
	pDlg->AddLogLine("Verification complete");
	pDlg->SetProgress(0,0);
}

void KSampleBurnDlg::OnJobDoneEvent(KSampleBurnDlg *pDlg)
{
	pDlg->OnJobDone();
}

void KSampleBurnDlg::OnInfoTextEvent(const TCHAR *pcInfoText, int32 nLevel, KSampleBurnDlg *pDlg)
{
	FXString strInfo = SDK2FoxString(pcInfoText);
	pDlg->AddLogLine(strInfo);
}

void KSampleBurnDlg::OnBurnFileEvent(const TCHAR* pcFileName, KSampleBurnDlg* pDlg)
{
	FXString strFileName = SDK2FoxString(pcFileName);
	pDlg->SetCurrentFile(strFileName);
}

KSampleBurnDlg::KSampleBurnDlg()
	:guisignal(NULL)
{
}

KSampleBurnDlg::KSampleBurnDlg(FXWindow* owner)
	:FXDialogBox(owner, "", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER)
	,guisignal(owner->getApp())
	,m_enState(ST_NONE)
{
	FXVerticalFrame* main = new FXVerticalFrame(this, LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0,0, 450,350);
	
		FXHorizontalFrame* logFr = new FXHorizontalFrame(main,  LAYOUT_FILL | FRAME_SUNKEN);
			m_lbxLog = new FXList(logFr, NULL, 0, LIST_NORMAL | LAYOUT_FILL);
	
		FXHorizontalFrame* infoFrame = new FXHorizontalFrame(main, LAYOUT_FILL_X);
			new FXLabel(infoFrame, "Write file: ");
			m_lblCurrentFile = new FXLabel(infoFrame, "");
			m_lblElapsed = new FXLabel(infoFrame, "Total time: 00:00:00", NULL, LABEL_NORMAL | LAYOUT_RIGHT);
		
		m_lblSpeed = new FXLabel(main, "Current speed:", NULL, LABEL_NORMAL, 5);
		
		new FXHorizontalSeparator(main, SEPARATOR_GROOVE | LAYOUT_FILL_X);
		
		FXVerticalFrame* progressFrame = new FXVerticalFrame(main, LAYOUT_FILL_X);
			new FXLabel(progressFrame, "Current buffer:"); 
			m_barBuffer = new FXProgressBar(progressFrame, NULL, 0, PROGRESSBAR_NORMAL | LAYOUT_FILL_X);
			new FXLabel(progressFrame, "Total progress:");
			m_barProgress = new FXProgressBar(progressFrame, NULL, 0, PROGRESSBAR_NORMAL | LAYOUT_FILL_X);
		
		FXHorizontalFrame* buttonsFrame = new FXHorizontalFrame(main, LAYOUT_FILL_X);
			new FXButton(buttonsFrame, "Save log", NULL, this, KSampleBurnDlg::ID_SAVELOG, 
						BUTTON_NORMAL | LAYOUT_LEFT | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 70, 25);
			
			m_btnCancel = new FXButton(buttonsFrame, "Cancel", NULL, this, KSampleBurnDlg::ID_CANCEL, 
						BUTTON_NORMAL | LAYOUT_RIGHT | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 70, 25);
}

void KSampleBurnDlg::create()
{
	FXDialogBox::create();

	m_nStartTime = FXThread::time()/1000/1000/1000;

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------

	SetFinalizeEventCallback((FinalizeEvent) KSampleBurnDlg::OnFinalizeEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) KSampleBurnDlg::OnBurnDoneEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) KSampleBurnDlg::OnJobDoneEvent, this);
	SetProcessEventCallback((ProcessEvent) KSampleBurnDlg::OnProcessEvent, this);
	SetInfoTextEventCallback((InfoTextEvent) KSampleBurnDlg::OnInfoTextEvent, BS_IL_INFO,  this);
	SetStartVerifyEventCallback((StartVerifyEvent) KSampleBurnDlg::OnStartVerifyEvent, this);
	SetVerifyFileEventCallback((VerifyFileEvent) KSampleBurnDlg::OnVerifyFileEvent, this);
	SetVerifyErrorEventCallback((VerifyErrorEvent) KSampleBurnDlg::OnVerifyErrorEvent, this);
	SetVerifyDoneEventCallback((VerifyDoneEvent) KSampleBurnDlg::OnVerifyDoneEvent, this);
	SetBurnFileEventCallback((BurnFileEvent) KSampleBurnDlg::OnBurnFileEvent, this);


	// Get volume label

	SOptions opt;
	::GetOptions(&opt);

	m_strLabel = opt.chVolumeLabel;

	// Get burning device

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);

	m_strDevice = (const char*)(KString(chBurnDevices[0][0]) + ":");

	// Update window's title

	FXString strTitle;
	strTitle.format(TITLE_BURN_FORMAT, 0, m_strDevice.text(),  m_strLabel.text());
	setTitle(strTitle);

	//--------------------------------------------------
	// Start burning
	//--------------------------------------------------

	// It's mandatory to prepare project before burning

	m_lbxLog->appendItem("Prepare collection");
	res = ::Prepare();
	handleError(res);

	if (BS_SDK_ERROR_NO == res) 
	{
		// Get current burn speed

		int32 nSpeed = 0;
		::GetBurnSpeed(BS_CURRENT_DEVICE, &nSpeed);

		if (nSpeed == BS_MAX_SPEED)
			::GetMaxBurnSpeed(BS_CURRENT_DEVICE, &nSpeed);

		// Update speed label

		FXString strSpeed;

		if (nSpeed == BS_NDEF)
			strSpeed = "n/a";
		else
			strSpeed.format("%d KB/s", nSpeed);

		m_lblSpeed->setText("Current speed: " + strSpeed);

		// Project is successfully prepared - burn it

		m_lbxLog->appendItem("Start burning...");
		res = ::Burn();
		handleError(res);

		if (BS_SDK_ERROR_NO == res) 
		{
			// Burning successfully started
			m_enState = ST_BURN;
			getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
		}
	}
}

void KSampleBurnDlg::RestoreEvents()
{
	SetFinalizeEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetInfoTextEventCallback(NULL, BS_IL_INFO,  NULL);
	SetStartVerifyEventCallback(NULL, NULL);
	SetVerifyFileEventCallback(NULL, NULL);
	SetVerifyErrorEventCallback(NULL, NULL);
	SetVerifyDoneEventCallback(NULL, NULL);
	SetBurnFileEventCallback(NULL, NULL);
}

KSampleBurnDlg::~KSampleBurnDlg()
{
}

long KSampleBurnDlg::onCancel(FXObject* sender, FXSelector key, void* data)
{
	if (m_enState != ST_NONE)
	{
		::Abort();
		return 1;
	}
	else
	{
		RestoreEvents();
		return FXDialogBox::onCmdCancel(sender, key, data);
	}
}

long KSampleBurnDlg::onSaveLog(FXObject* sender, FXSelector key, void* data)
{
	FXFileDialog fileDlg(this, "Save log file");
	fileDlg.setPatternList("Log Files (*.log)");
	fileDlg.setSelectMode(SELECTFILE_ANY);

	if (fileDlg.execute())
	{
		::SaveLogToFile(Fox2SDKString(fileDlg.getFilename()));
	}

	return 1;
}

void KSampleBurnDlg::AddLogLine(const FXString& strLogLine)
{
	m_strLogLine = strLogLine;
	//getApp()->addChore(this, KSampleBurnDlg::ID_ADDLOGLINE, &m_strLogLine);
	guisignal.message(this,FXSEL(SEL_CHORE,KSampleBurnDlg::ID_ADDLOGLINE),&m_strLogLine,sizeof(m_strLogLine));
}

long KSampleBurnDlg::onAddLogLine(FXObject* sender, FXSelector key, void* data)
{
	FXString *pstrLogLine = (FXString*)data;	
	if (NULL != pstrLogLine) {
		FXint indx = m_lbxLog->appendItem(*pstrLogLine);
		m_lbxLog->setCurrentItem(indx);
		m_lbxLog->makeItemVisible(indx);
	}

	return 1;
}

void KSampleBurnDlg::SetProgress(int progress, int buffer)
{
	m_progInfo.progress = progress;
	m_progInfo.buffer = buffer;

	//getApp()->addChore(this, KSampleBurnDlg::ID_SETPROGRESS, &m_progInfo);	
	guisignal.message(this,FXSEL(SEL_CHORE,KSampleBurnDlg::ID_SETPROGRESS),&m_progInfo,sizeof(m_progInfo));
}

long KSampleBurnDlg::onSetProgress(FXObject* sender, FXSelector key, void* data)
{
	m_barProgress->setProgress(m_progInfo.progress);
	m_barBuffer->setProgress(m_progInfo.buffer);

	UpdateTitle();
	return 1;
}

long KSampleBurnDlg::onChoreJobDone(FXObject* sender, FXSelector key, void* data)
{
	m_enState = ST_NONE;
	m_btnCancel->setText("Close");
	return 1;
}

void KSampleBurnDlg::OnJobDone()
{
	//getApp()->addChore(this, KSampleBurnDlg::ID_JOBDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSampleBurnDlg::ID_JOBDONE),NULL,NULL);
}

long KSampleBurnDlg::onBurnFile(FXObject* sender, FXSelector key, void* data)
{
	m_lblCurrentFile->setText(m_strCurrentFile);
	return 0;
}

void KSampleBurnDlg::SetCurrentFile(const FXString& strFileName)
{
	m_strCurrentFile = strFileName;
	//getApp()->addChore(this, KSampleBurnDlg::ID_BURNFILE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSampleBurnDlg::ID_BURNFILE),NULL,NULL);
}

long KSampleBurnDlg::onTimer(FXObject* sender, FXSelector key, void* data)
{
	FXTime nNow = FXThread::time()/1000/1000/1000;

	FXint second = (nNow - m_nStartTime) % 60;
	FXint minute = ((nNow - m_nStartTime)/60) % 60;
	FXint hour   = ((nNow - m_nStartTime)/3600);

	FXString strElapsed;
	strElapsed.format("Total time: %.2d:%.2d:%.2d", hour, minute, second);
	m_lblElapsed->setText(strElapsed);

	if (m_enState != ST_NONE)
		getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
	return 1;
}

void KSampleBurnDlg::handleError(int32 errCode)
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

		AddLogLine((const wchar_t*)strError);
	}
}

void KSampleBurnDlg::UpdateTitle()
{
	if (m_enState == ST_BURN || m_enState == ST_FINALIZE)
	{
		int progress = m_enState == ST_BURN ? m_progInfo.progress : 100;
		if (progress != 0)
		{
			FXString strTitle;
			strTitle.format(TITLE_BURN_FORMAT, progress, m_strDevice.text(),  m_strLabel.text());
			setTitle(strTitle);
		}
	}
	else if (m_enState == ST_VERIFY)
	{
		if (m_progInfo.progress != 0)
		{
			FXString strTitle;
			strTitle.format(TITLE_VERIFY_FORMAT, m_progInfo.progress, m_strDevice.text(), m_strLabel.text());
			setTitle(strTitle);
		}
	}
}
