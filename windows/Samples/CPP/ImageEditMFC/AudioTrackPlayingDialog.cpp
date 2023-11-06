// SaveTrackDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "AudioTrackPlayingDialog.h"


// KSaveTrackDialog dialog

IMPLEMENT_DYNAMIC(KPlayTrackDialog, CDialog)
KPlayTrackDialog::KPlayTrackDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KPlayTrackDialog::IDD, pParent)
	,m_bReady(false)
{
}

KPlayTrackDialog::KPlayTrackDialog(int16 nTrackNumber, CWnd* pParent /*=NULL*/)
	:CDialog(KPlayTrackDialog::IDD, pParent)	
	,m_enState(ST_NONE)
	,m_nTrackNumber(nTrackNumber)	
	,m_bReady(true)
{	
}

KPlayTrackDialog::~KPlayTrackDialog()
{
}

void KPlayTrackDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KPlayTrackDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_MESSAGE(WM_BURNDONE_NOTIFY, OnOnBurnDoneNotify)
END_MESSAGE_MAP()


// KSaveTrackDialog message handlers


BOOL KPlayTrackDialog::OnInitDialog()
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
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KPlayTrackDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KPlayTrackDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KPlayTrackDialog::OnBurnDoneEvent, this);

	m_enState = ST_PROCESSING;
	
	int32 res = ::PlayAudioTrack(m_nTrackNumber);	
	HandleError(res);

	SYSTEMTIME timeNow;
	GetSystemTime(&timeNow);
	CTime time(timeNow);
	m_timeStart = CTimeSpan(time.GetTime());
	
	SetTimer(1, 1000, NULL);

	return TRUE;
}

void KPlayTrackDialog::OnBnClickedOk()
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

void KPlayTrackDialog::OnTimer(UINT_PTR ID)
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

void KPlayTrackDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

/*static*/ void KPlayTrackDialog::OnProcessEvent(float fPercent, 
				float fDeviceBuffer, float fCache, double dBytesWritten, 
				double dImageSize, KPlayTrackDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, dImageSize);	
}

void KPlayTrackDialog::SetProgress(int nProgress, double dBytesPlayed, 
								   double dTrackSize)
{
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(nProgress);

	CString strTmp;
	strTmp.Format(_T("%.0f"), dBytesPlayed);
	SetDlgItemText(IDC_BYTES, strTmp);

	
	strTmp.Format(_T("%.0f"), dTrackSize);
	SetDlgItemText(IDC_TOTAL, strTmp);	
}


/*static*/ void KPlayTrackDialog::OnJobDoneEvent(KPlayTrackDialog *pDlg) 
{
	pDlg->OnJobDone();
}

void KPlayTrackDialog::OnJobDone()
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

void KPlayTrackDialog::Done()
{	
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	SetDlgItemText(IDOK, _T("&Close"));
	KillTimer(1);
}

/*static*/ void KPlayTrackDialog::OnBurnDoneEvent(const TCHAR *pcError, KPlayTrackDialog *pDlg)
{
	pDlg->SendMessage(WM_BURNDONE_NOTIFY, (WPARAM)pcError);
}

LRESULT KPlayTrackDialog::OnOnBurnDoneNotify(WPARAM pcError, LPARAM)
{
	if (pcError && _tcslen((TCHAR *)pcError) > 0)
	{
		AfxMessageBox((TCHAR *)pcError);
	}

	return 0;
}

void KPlayTrackDialog::HandleError(int32 errCode)
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

void KPlayTrackDialog::OnCancel()
{
	m_enState = ST_CANCELLED;
	
	if (::Abort() != BS_SDK_ERROR_NO)
	{
		KillTimer(1);
		RestoreEvents();
		CDialog::OnCancel();
	}
}