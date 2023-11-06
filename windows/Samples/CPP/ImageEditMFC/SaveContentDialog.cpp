// SaveContentDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "SaveContentDialog.h"
#include <process.h>

#define WM_JOBDONE_CMD  (WM_USER + 1)

// KProcessContentDialog dialog

IMPLEMENT_DYNAMIC(KSaveContentDialog, CDialog)
KSaveContentDialog::KSaveContentDialog(SSaveContentParams params, CWnd* pParent /*= NULL*/)
	:CDialog(KSaveContentDialog::IDD, pParent)	
	,m_enState(ST_NONE)
	,m_cParams(params)
	,m_nTotalFiles(0)
	,m_nTotalSize(0)
	,m_nCurrJobsSize(0)
	,m_nDoneJobsSize(0)
{
}

KSaveContentDialog::~KSaveContentDialog()
{	
}

BOOL KSaveContentDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

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
		SetWindowText(_T("Importing content"));
	}
	else if (AIM_VERIFY == m_cParams.enAim)
	{
		SetWindowText(_T("Verifying content"));
	}
	else
	{
		Done();
		return FALSE;
	}

	SYSTEMTIME timeNow;
	GetSystemTime(&timeNow);
	CTime time(timeNow);
	m_timeStart = CTimeSpan(time.GetTime());
	
	SetTimer(1, 1000, NULL);

	m_iCurrentNode = m_cParams.nodes.begin();
	m_enState = ST_PROCESSING;

	m_nTotalSize = CalculateTotalSize(m_iCurrentNode);

	CString strTmp;
	strTmp.Format(_T("%lli"), m_nTotalSize);
	SetDlgItemText(IDC_TOTAL, strTmp);
	
	//Call OnJobDone to start processing content
	OnJobDone();
	
	return TRUE;
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
		int nCount = node->getChildsCount();

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

void KSaveContentDialog::HandleError(int32 errCode)
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

		AfxMessageBox(strError);
	}
}

void KSaveContentDialog::LogPrint(const CString& strText)
{
	if (ST_PROCESSING == m_enState)
	{
		CListBox *pListBox = (CListBox *)GetDlgItem(IDC_LIST_LOG);

		if (pListBox)
		{
			pListBox->AddString(strText);
			pListBox->SetCurSel(pListBox->GetCount() - 1);
		}
	}
}


void KSaveContentDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KSaveContentDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_MESSAGE(WM_BURNDONE_NOTIFY, OnOnBurnDoneNotify)
END_MESSAGE_MAP()


// KSaveContentDialog message handlers

/*static*/ void KSaveContentDialog::OnProcessEvent(float fPercent, 
				float fDeviceBuffer, float fCache, double dBytesWritten, 
				double dImageSize, KSaveContentDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, (int64)dBytesWritten, (int64)dImageSize);
}

void KSaveContentDialog::SetProgress(int nProgress, int64 nBytesWritten, int64 nTottalSize)
{
	m_nCurrJobsSize = nBytesWritten;

	CString strTmp;
	strTmp.Format(_T("%lli"), m_nDoneJobsSize + m_nCurrJobsSize);
	SetDlgItemText(IDC_BYTES, strTmp);
	
	CProgressCtrl *progress = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS);
	
	if (progress)
	{
		progress->SetPos((m_nDoneJobsSize + m_nCurrJobsSize) * 100 / m_nTotalSize);
	}
}

/*static*/ void KSaveContentDialog::OnBurnFileEvent(const TCHAR* pcFileName, KSaveContentDialog* pDlg)
{
	pDlg->AddCurrentFile(pcFileName);
}

void KSaveContentDialog::AddCurrentFile(const TCHAR *pcFileName)
{
	LogPrint(CString(_T("Importing : ")) + CString(pcFileName));
	m_nTotalFiles++;
}

/*static*/ void KSaveContentDialog::OnBurnDoneEvent(const TCHAR *pcError, KSaveContentDialog *pDlg)
{
	pDlg->SendMessage(WM_BURNDONE_NOTIFY, (WPARAM)pcError);
}

LRESULT KSaveContentDialog::OnOnBurnDoneNotify(WPARAM pcError, LPARAM)
{
	if (pcError && _tcslen((TCHAR *)pcError) > 0)
	{
		AfxMessageBox((TCHAR *)pcError);
	}

	return 0;
}

/*static*/ void KSaveContentDialog::OnJobDoneEvent(KSaveContentDialog *pDlg) 
{
	pDlg->OnJobDone();
}

void KSaveContentDialog::OnJobDone()
{	
	switch (m_enState)
	{
		case ST_PROCESSING :
		{
			if (m_iCurrentNode != m_cParams.nodes.end())
			{
				if (ProcessNextNode() == FALSE)
				{
					LogPrint(_T("Internal error. Aborted."));
					goto FINISH;
				}
			}
			else
			{
				CString logstring;
				logstring.Format(_T("Done. Tottal files : %i."), m_nTotalFiles);

				LogPrint(logstring);

				goto FINISH;
			}
		}
		break;

		case ST_CANCELLED :

			this->PostMessage(WM_CLOSE);

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
			ATLASSERT(0);
		}
		break;
	}
}

void KSaveContentDialog::Done()
{
	m_enState = ST_DONE;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	SetDlgItemText(IDOK, _T("&Close"));
	KillTimer(1);
}

BOOL KSaveContentDialog::ProcessNextNode()
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
				return FALSE;
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
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	HSESSION hSession;
	int32 nError = ::OpenDiskSession(BS_READ_DEVICE, nTrackNumber, &hSession, nFileSysType);

	if (nError != BS_SDK_ERROR_NO)
	{
		HandleError(nError);
		return FALSE;
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
#ifdef WIN32
		strPath = info.path + _T("\\") + info.name;
#else
		strPath = info.path + _T("/") + info.name;
#endif
	}

	if (AIM_IMPORT == m_cParams.enAim)
	{
		if (m_cParams.optType == BS_IMPOPTS_EX) {
			nError = ::ImportFileEx(hSession, strPath, m_cParams.strExtractionFolderPath, m_cParams.strPassword);
		}
		else {
			nError = ::ImportFile(hSession, strPath, m_cParams.strExtractionFolderPath);
		}
	}
	else if (AIM_VERIFY == m_cParams.enAim)
	{
		nError = ::VerifyFile(hSession, strPath);
	}
	else
	{
		return FALSE;
	}

	::CloseDiskSession(hSession);

	if (nError != BS_SDK_ERROR_NO)
	{
		HandleError(nError);
		return FALSE;
	}

	m_iCurrentNode++;

	return TRUE;
}

void KSaveContentDialog::OnTimer(UINT_PTR ID)
{
	SYSTEMTIME timeNow;
	GetSystemTime(&timeNow);
	CTime time(timeNow);
	CTimeSpan timeCurrent = CTimeSpan(time.GetTime());
	timeCurrent -=  m_timeStart;

	CString strElapsed;
	strElapsed.Format(_T("%.2d:%.2d:%.2d"), timeCurrent.GetHours(),
		timeCurrent.GetMinutes(), timeCurrent.GetSeconds());
	
	SetDlgItemText(IDC_TIME, strElapsed);
	
	if (m_enState != ST_PROCESSING)
	{
		KillTimer(1);
	}
}

void KSaveContentDialog::OnBnClickedOk()
{
	if (m_enState == ST_PROCESSING)
	{
		m_enState = ST_ABORTED;
		
		if (BS_SDK_ERROR_NO == ::Abort())
		{
			GetDlgItem(IDOK)->EnableWindow(FALSE);
		}
		else
		{
			Done();
		}
	}		
	else
	{
		RestoreEvents();
		OnOK();
	}
}

void KSaveContentDialog::OnCancel()
{
	m_enState = ST_CANCELLED;
	
	if (::Abort() != BS_SDK_ERROR_NO)
	{
		KillTimer(1);
		RestoreEvents();
		CDialog::OnCancel();
	}
}

/*static*/ void KSaveContentDialog::OnVerifyFileEvent(const TCHAR* pcFileName, KSaveContentDialog *pDlg)
{
	pDlg->OnVerifyFile(pcFileName);
}

void KSaveContentDialog::OnVerifyFile(const TCHAR *pcFileName)
{
	LogPrint(CString(_T("Verifying : ")) + CString(pcFileName));
	m_nTotalFiles++;
}

/*static*/ void KSaveContentDialog::OnVerifyErrorEvent(const TCHAR *pcFileName, const TCHAR *pcError, KSaveContentDialog *pDlg)
{
	pDlg->OnVerifyError(pcFileName, pcError);
}

void KSaveContentDialog::OnVerifyError(const TCHAR *pcFileName, const TCHAR *pcError)
{
	LogPrint(CString(_T("Verification error : ")) + CString(pcFileName) + CString(_T(" : ")) + CString(pcError));	
}

/*static*/ void KSaveContentDialog::OnVerifyDoneEvent(int nNumErrors, KSaveContentDialog *pDlg)
{
	pDlg->OnVerifyDone(nNumErrors);
}

void KSaveContentDialog::OnVerifyDone(int nNumErrors)
{
	CString string;
	string.Format(_T("Verification done : %d error(s)"), nNumErrors);
	LogPrint(string);
}