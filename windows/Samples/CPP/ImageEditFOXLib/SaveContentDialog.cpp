#include "stdafx.h"
#include "SaveContentDialog.h"

FXDEFMAP(KSaveContentDialog) KSampleBurnMap[]= {
	FXMAPFUNC(SEL_COMMAND, FXDialogBox::ID_CANCEL, KSaveContentDialog::onCancel),
	FXMAPFUNC(SEL_CLOSE, 0, KSaveContentDialog::onCancel),
	FXMAPFUNC(SEL_CHORE, KSaveContentDialog::ID_JOBDONE, KSaveContentDialog::onChoreJobDone),
	FXMAPFUNC(SEL_CHORE, KSaveContentDialog::ID_BURNDONE, KSaveContentDialog::onChoreBurnDone),
	FXMAPFUNC(SEL_CHORE, KSaveContentDialog::ID_SETPROGRESS, KSaveContentDialog::onSetProgress),
	FXMAPFUNC(SEL_TIMEOUT, KSaveContentDialog::ID_TOTALTIME, KSaveContentDialog::onTimer),
};

FXIMPLEMENT(KSaveContentDialog, FXDialogBox, KSampleBurnMap, ARRAYNUMBER(KSampleBurnMap))

KSaveContentDialog::KSaveContentDialog()
	:guisignal(NULL)
{
}

KSaveContentDialog::KSaveContentDialog(SSaveContentParams params, FXWindow* owner)
	:FXDialogBox(owner, "Saving/checking content...", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	,guisignal(owner->getApp())
	,m_enState(ST_NONE)
	,m_cParams(params)
	,m_nTotalFiles(0)	
	,m_nDoneJobsSize(0)
	,m_nCurrJobsSize(0)
	,m_nTotalSize(0)
{
	FXVerticalFrame* mainFrame = new FXVerticalFrame(this, LAYOUT_FILL|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 400, 300);
		new FXLabel(mainFrame, "Total progress:");		
		m_barProgress = new FXProgressBar(mainFrame, NULL, 0, PROGRESSBAR_NORMAL|LAYOUT_FILL_X);

		FXHorizontalFrame* bytesProcessedFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(bytesProcessedFrame, "Current processed (bytes): ");
			m_lblBytesProcessed = new FXLabel(bytesProcessedFrame, "");

		FXHorizontalFrame* totalSizeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);
			new FXLabel(totalSizeFrame, "Total size (bytes): ");
			m_lblTotalSize = new FXLabel(totalSizeFrame, "");

		
		FXHorizontalFrame* timeFrame = new FXHorizontalFrame(mainFrame, LAYOUT_FILL_X);			
			m_lblElapsed = new FXLabel(timeFrame, "Total Time: ");

		FXHorizontalFrame *pTextBoxFrame= new FXHorizontalFrame(mainFrame, FRAME_NORMAL | FRAME_SUNKEN | LAYOUT_FILL);
			m_pLogBox = new FXText(pTextBoxFrame, this, ID_LOG_BOX, TEXT_READONLY | LAYOUT_FILL);

			m_pFont = new FXFont(getApp(), "courier", 12, FXFont::Normal, FXFont::Straight, FONTENCODING_DEFAULT, FXFont::NonExpanded, FXFont::Modern);
			m_pLogBox->setFont(m_pFont);
			

		m_btnAbort = new FXButton(mainFrame, "&Abort", 0, this, KSaveContentDialog::ID_CANCEL);		
}

void KSaveContentDialog::create()
{
	FXDialogBox::create();
	
	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KSaveContentDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KSaveContentDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KSaveContentDialog::OnBurnDoneEvent, this);
	SetBurnFileEventCallback((BurnFileEvent)  /*static*/ KSaveContentDialog::OnBurnFileEvent, this);
	SetVerifyFileEventCallback((VerifyFileEvent) /*static*/ KSaveContentDialog::OnVerifyFileEvent, this);
	SetVerifyErrorEventCallback((VerifyErrorEvent) /*static*/ KSaveContentDialog::OnVerifyErrorEvent, this);
	SetVerifyDoneEventCallback((VerifyDoneEvent) /*static*/ KSaveContentDialog::OnVerifyDoneEvent, this);

	if (AIM_IMPORT == m_cParams.enAim)
	{
		this->setTitle("Importing content");
	}
	else if (AIM_VERIFY == m_cParams.enAim)
	{
		this->setTitle("Verifying content");
	}
	else
	{
		Done();
		return;
	}
	
	
	m_enState = ST_PROCESSING;
	m_nStartTime = FXThread::time()/1000/1000/1000;
	getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));

	m_iCurrentNode = m_cParams.nodes.begin();
	m_enState = ST_PROCESSING;

	m_nTotalSize = CalculateTotalSize(m_iCurrentNode);
	m_lblTotalSize->setText(FXString::value("%lli", m_nTotalSize));

	//Call OnJobDone to start processing content
	OnJobDone();
}

int64 KSaveContentDialog::CalculateTotalSize(NodeList::iterator iCurrentNode)
{
	int64 nTotalSize = 0;

	for (; iCurrentNode != m_cParams.nodes.end(); iCurrentNode++)
	{
		nTotalSize += CalculateNodeSize(*iCurrentNode);
	}

	return nTotalSize;
}

int64 KSaveContentDialog::CalculateNodeSize(ITreeNode* node)
{
	if (dynamic_cast<FileNode*>(node))
	{	
		return CalculateFileSize(dynamic_cast<FileNode*>(node));
	}
	else
	{
		int nCount = (int)node->getChildsCount();

		int64 nTotalSize = 0;

		for (int i = 0; i < nCount; i++)
		{
			nTotalSize += CalculateNodeSize(node->getChild(i));
		}

		return nTotalSize;
	}
}

int64 KSaveContentDialog::CalculateFileSize(FileNode* filenode)
{
	if (filenode)
	{
		GenericInfo info = filenode->getGenericInfo();
		return info.size;
	}

	return 0;
}

void KSaveContentDialog::RestoreEvents()
{	
	SetProcessEventCallback(NULL, NULL);
	SetJobDoneEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
	SetBurnFileEventCallback(NULL, NULL);
	SetVerifyFileEventCallback(NULL, NULL);
	SetVerifyErrorEventCallback(NULL, NULL);
	SetVerifyDoneEventCallback(NULL, NULL);
}

KSaveContentDialog::~KSaveContentDialog()
{	
	delete m_pFont;
}

long KSaveContentDialog::onCancel(FXObject* sender, FXSelector key, void* data)
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

/*static*/ void KSaveContentDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
				double dBytesWritten, double dImageSize, KSaveContentDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, (int64)dBytesWritten, (int64)dImageSize);
}

void KSaveContentDialog::SetProgress(int nProgress, int64 nBytesWritten, int64 nTottalSize)
{
	m_cProgressInfo.nProgress = nProgress;
	m_cProgressInfo.nBytesProcessed = nBytesWritten;
	
	//getApp()->addChore(this, KSaveContentDialog::ID_SETPROGRESS, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveContentDialog::ID_SETPROGRESS),NULL,NULL);
}

long KSaveContentDialog::onSetProgress(FXObject* sender, FXSelector key, void* data)
{
	m_nCurrJobsSize = m_cProgressInfo.nBytesProcessed;

	m_lblBytesProcessed->setText(FXString::value("%lli", m_nDoneJobsSize + m_nCurrJobsSize));
	
	m_barProgress->setProgress((FXuint)((m_nDoneJobsSize + m_nCurrJobsSize) * 100 / m_nTotalSize));
	
	return 1;
}

/*static*/ void KSaveContentDialog::OnJobDoneEvent(KSaveContentDialog *pDlg) 
{
	pDlg->OnJobDone();
}

void KSaveContentDialog::OnJobDone()
{
	//getApp()->addChore(this, KSaveContentDialog::ID_JOBDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveContentDialog::ID_JOBDONE),NULL,NULL);
}

long KSaveContentDialog::onChoreJobDone(FXObject* sender, FXSelector key, void* data)
{
	switch (m_enState)
	{
		case ST_PROCESSING :
		{
			if (m_iCurrentNode != m_cParams.nodes.end())
			{
				if (ProcessNextNode() == false)
				{
					LogPrint(_T("Internal error. Aborted."));
					goto FINISH;
				}
			}
			else
			{
				LogPrint(FXString::value("Done. Tottal files : %i.", m_nTotalFiles));
				goto FINISH;
			}
		}
		break;

		case ST_CANCELLED :

			getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
			return FXDialogBox::onCmdCancel(sender, key, data);

		break;

		case ST_DONE :
		case ST_ABORTED :
		{
FINISH:		
			Done();
		}
		break;
		
		default :
		{
			FXASSERT(0);
		}
		break;
	}

	return 1;
}

void KSaveContentDialog::Done()
{
	m_enState = ST_DONE;
	m_btnAbort->enable();
	m_btnAbort->setText("&Close");
	getApp()->removeTimeout(this, FXSEL(SEL_TIMEOUT, ID_TOTALTIME));
}

bool KSaveContentDialog::ProcessNextNode()
{				
	int32 nFileSysType = -1, nTrackNumber = -1;

	FileSysNode* fsnode = dynamic_cast<FileSysNode*>(*m_iCurrentNode);

	if (!fsnode)
	{
		DirectoryNode* dirnode = dynamic_cast<DirectoryNode*>(*m_iCurrentNode);

		if (dirnode)
		{
			fsnode = dirnode->getFileSystemNode();
		}
		else
		{
			FileNode* filenode = dynamic_cast<FileNode*>(*m_iCurrentNode);

			if (filenode)
			{
				fsnode = filenode->getFileSystemNode();
			}
			else
			{
				return false;
			}
		}
	}

	if (fsnode)
	{
		nFileSysType = fsnode->getFileSysType();

		TrackNode *tracknode = fsnode->getTrackNode();

		if (tracknode)
		{
			STrackInfo info = tracknode->getTrackInfo();
			nTrackNumber = info.nTrackNumber;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	HSESSION hSession;
	int32 nError = ::OpenDiskSession(BS_READ_DEVICE, nTrackNumber, &hSession, nFileSysType);

	if (nError != BS_SDK_ERROR_NO)
	{
		handleError(nError);
		return false;
	}

	m_nDoneJobsSize += m_nCurrJobsSize;
	m_nCurrJobsSize = 0;

	GenericInfo info = (*m_iCurrentNode)->getGenericInfo();

	KString strPath;

	if (dynamic_cast<FileSysNode*>(*m_iCurrentNode))
	{
		strPath = _T("");
	}
	else
	{
		strPath = Fox2SDKString(info.path + PATHSEPSTRING + info.name);
	}

	//What we transfer here? hSession?

	if (AIM_IMPORT == m_cParams.enAim)
	{
		if (m_cParams.optType == BS_IMPOPTS_EX) {
			nError = ::ImportFileEx(hSession, strPath, Fox2SDKString(m_cParams.strExtractionFolderPath), Fox2SDKString(m_cParams.strPassword));
		}
		else {
			nError = ::ImportFile(hSession, strPath, Fox2SDKString(m_cParams.strExtractionFolderPath));
		}
		
	}
	else if (AIM_VERIFY == m_cParams.enAim)
	{
		nError = ::VerifyFile(hSession, strPath);
	}
	else
	{
		return false;
	}

	::CloseDiskSession(hSession);

	if (nError != BS_SDK_ERROR_NO)
	{
		handleError(nError);
		return false;
	}

	m_iCurrentNode++;

	return true;
}

/*static*/ void KSaveContentDialog::OnBurnDoneEvent(const TCHAR *pcError, KSaveContentDialog* pDlg)
{
	pDlg->OnBurnDone(pcError);
}

void KSaveContentDialog::OnBurnDone(const TCHAR *pcError)
{
	m_strCallbackError = SDK2FoxString(pcError);

	//getApp()->addChore(this, KSaveContentDialog::ID_BURNDONE, NULL);
	guisignal.message(this,FXSEL(SEL_CHORE,KSaveContentDialog::ID_BURNDONE),NULL,NULL);
}

long KSaveContentDialog::onChoreBurnDone(FXObject* sender, FXSelector key, void* data)
{
	if (m_strCallbackError.length() != 0)
	{
		FXMessageBox msgBox(this, "Playing track", m_strCallbackError, NULL, MBOX_OK);
		msgBox.execute();
	}

	return 1;
}

long KSaveContentDialog::onTimer(FXObject* sender, FXSelector key, void* data)
{
	FXTime nNow = FXThread::time()/1000/1000/1000;

	FXint second = (nNow - m_nStartTime) % 60;
	FXint minute = ((nNow - m_nStartTime)/60) % 60;
	FXint hour   = ((nNow - m_nStartTime)/3600);

	FXString strElapsed;
	strElapsed.format("Total Time: %.2d:%.2d:%.2d", hour, minute, second);
	m_lblElapsed->setText(strElapsed);

	if (ST_PROCESSING == m_enState)
	{
		getApp()->addTimeout(this, FXSEL(SEL_TIMEOUT,ID_TOTALTIME));
	}	
	
	return 1;
}

void KSaveContentDialog::handleError(int32 errCode)
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

		FXMessageBox msgBox(this, "Content", 
			SDK2FoxString((const wchar_t*)strError), NULL, MBOX_OK);

		msgBox.execute();
	}
}

void KSaveContentDialog::LogPrint(const FXString& strText)
{
	m_pLogBox->appendText(strText);	
	m_pLogBox->appendText("\n");
	m_pLogBox->makePositionVisible(m_pLogBox->getBottomLine());
}

/*static*/ void KSaveContentDialog::OnBurnFileEvent(const TCHAR* pcFileName, KSaveContentDialog* pDlg)
{
	pDlg->AddCurrentFile(pcFileName);
}

void KSaveContentDialog::AddCurrentFile(const TCHAR *pcFileName)
{
	LogPrint(FXString::value("Importing : %s", (const char *)KString(pcFileName)));
	m_nTotalFiles++;
}

/*static*/ void KSaveContentDialog::OnVerifyFileEvent(const TCHAR* pcFileName, KSaveContentDialog *pDlg)
{
	pDlg->OnVerifyFile(pcFileName);
}

void KSaveContentDialog::OnVerifyFile(const TCHAR *pcFileName)
{
	LogPrint(FXString::value("Verifying : %s", (const char *)KString(pcFileName)));
	m_nTotalFiles++;
}

/*static*/ void KSaveContentDialog::OnVerifyErrorEvent(const TCHAR *pcFileName, const TCHAR *pcError, KSaveContentDialog *pDlg)
{
	pDlg->OnVerifyError(pcFileName, pcError);
}

void KSaveContentDialog::OnVerifyError(const TCHAR *pcFileName, const TCHAR *pcError)
{
	LogPrint(FXString::value("Verification error : %s : %s", (const char *)KString(pcFileName), (const char *)KString(pcError)));
}

/*static*/ void KSaveContentDialog::OnVerifyDoneEvent(int nNumErrors, KSaveContentDialog *pDlg)
{
	pDlg->OnVerifyDone(nNumErrors);
}

void KSaveContentDialog::OnVerifyDone(int nNumErrors)
{
	LogPrint(FXString::value("Verification done : %d error(s)", nNumErrors));
}
