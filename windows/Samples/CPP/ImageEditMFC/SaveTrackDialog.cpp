// SaveTrackDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "SaveTrackDialog.h"


// KSaveTrackDialog dialog

IMPLEMENT_DYNAMIC(KSaveTrackDialog, CDialog)
KSaveTrackDialog::KSaveTrackDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KSaveTrackDialog::IDD, pParent)
	,m_bReady(false)
{
}

KSaveTrackDialog::KSaveTrackDialog(CWnd* pParent, int16 nTrackNumber, 
								   const CString& strFilePath, 
								   unsigned int nFileFormat)
	:CDialog(KSaveTrackDialog::IDD, pParent)	
	,m_enState(ST_NONE)
	,m_nTrackNumber(nTrackNumber)
	,m_strFilePath(strFilePath)
	,m_nFileFormat(nFileFormat)
	,m_bReady(true)
{	
}

KSaveTrackDialog::~KSaveTrackDialog()
{
}

void KSaveTrackDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KSaveTrackDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_MESSAGE(WM_BURNDONE_NOTIFY, OnOnBurnDoneNotify)
END_MESSAGE_MAP()


// KSaveTrackDialog message handlers


BOOL KSaveTrackDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_bReady)
	{
		return 0;
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KSaveTrackDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KSaveTrackDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KSaveTrackDialog::OnBurnDoneEvent, this);

	m_enState = ST_PROCESSING;
	//You can set yourself the speed here.
	int32 res = ::SetReadSpeed(BS_READ_DEVICE,2822);
	HandleError(res);
	
	res = ::SaveTrackToFile(BS_READ_DEVICE, m_nTrackNumber, 
		m_strFilePath, m_nFileFormat);

	HandleError(res);

	SYSTEMTIME timeNow;
	GetSystemTime(&timeNow);
	CTime time(timeNow);
	m_timeStart = CTimeSpan(time.GetTime());
	
	SetTimer(1, 1000, NULL);

	return TRUE;
}
void KSaveTrackDialog::OnBnClickedOk()
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

void KSaveTrackDialog::OnTimer(UINT_PTR ID)
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

void KSaveTrackDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

/*static*/ void KSaveTrackDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
					double dBytesWritten, double dImageSize, KSaveTrackDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, dImageSize);	
}

/*static*/ void KSaveTrackDialog::OnJobDoneEvent(KSaveTrackDialog *pDlg) 
{
	pDlg->OnJobDone();
}

void KSaveTrackDialog::SetProgress(int nProgress, double dBytesWritten, double dTrackSize)
{
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(nProgress);

	CString strTmp;
	strTmp.Format(_T("%.0f"), dBytesWritten);
	SetDlgItemText(IDC_BYTES, strTmp);

	
	strTmp.Format(_T("%.0f"), dTrackSize);
	SetDlgItemText(IDC_TOTAL, strTmp);	
}

void KSaveTrackDialog::OnJobDone()
{
	switch (m_enState)
	{
		case ST_PROCESSING :
		case ST_ABORTED :

			m_enState = ST_DONE;
			Done();

		break;

		case ST_CANCELLED :

			this->PostMessage(WM_CLOSE);

		break;
	}
}

void KSaveTrackDialog::Done()
{	
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	SetDlgItemText(IDOK, _T("&Close"));
	KillTimer(1);
}

/*static*/ void KSaveTrackDialog::OnBurnDoneEvent(const TCHAR *pcError, KSaveTrackDialog *pDlg)
{
	pDlg->SendMessage(WM_BURNDONE_NOTIFY, (WPARAM)pcError);
}

LRESULT KSaveTrackDialog::OnOnBurnDoneNotify(WPARAM pcError, LPARAM)
{
	if (pcError && _tcslen((TCHAR *)pcError) > 0)
	{
		AfxMessageBox((TCHAR *)pcError);
	}

	return 0;
}

void KSaveTrackDialog::HandleError(int32 errCode)
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


void KSaveTrackDialog::OnCancel()
{
	m_enState = ST_CANCELLED;
	
	if (::Abort() != BS_SDK_ERROR_NO)
	{
		KillTimer(1);
		RestoreEvents();
		CDialog::OnCancel();
	}
}