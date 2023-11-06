// SaveDiscDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "SaveDiscDialog.h"


// KSaveDiscDialog dialog

IMPLEMENT_DYNAMIC(KSaveDiscDialog, CDialog)
KSaveDiscDialog::KSaveDiscDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KSaveDiscDialog::IDD, pParent)
	, m_bReady(false)
{	
}

KSaveDiscDialog::KSaveDiscDialog(CWnd* pParent /*=NULL*/,
								 const CString& strFilePath, 
								 int16 nFileFormat)
	: CDialog(KSaveDiscDialog::IDD, pParent)
	,m_bReady(true)
	,m_strFilePath(strFilePath)
	,m_nFileFormat(nFileFormat)
	,m_enState(ST_NONE)	
{	
}

KSaveDiscDialog::~KSaveDiscDialog()
{
}

void KSaveDiscDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KSaveDiscDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_MESSAGE(WM_BURNDONE_NOTIFY, OnOnBurnDoneNotify)
END_MESSAGE_MAP()


// KSaveDiscDialog message handlers

BOOL KSaveDiscDialog::OnInitDialog()
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
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KSaveDiscDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KSaveDiscDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KSaveDiscDialog::OnBurnDoneEvent, this);

	m_enState = ST_PROCESSING;
		
	SCreateImageParams cCreateImageParams;
	
	cCreateImageParams.cErrorParams.bErrorCorrection = BS_TRUE;

	_tcscpy(cCreateImageParams.lpszImagePath, m_strFilePath.GetBuffer());
	m_strFilePath.ReleaseBuffer();

	cCreateImageParams.nImageType = m_nFileFormat;	
	cCreateImageParams.cErrorParams.nHardwareRetryCount = (uint8)20;
	cCreateImageParams.cErrorParams.nSoftwareRetryCount = (uint8)20;
		
	int32 res = ::CreateImage(cCreateImageParams, BS_IMGTASK_CREATE);
	HandleError(res);
	
	SYSTEMTIME timeNow;
	GetSystemTime(&timeNow);
	CTime time(timeNow);
	m_timeStart = CTimeSpan(time.GetTime());
	
	SetTimer(1, 1000, NULL);
	
	return TRUE;
}


/*static*/ void KSaveDiscDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, 
												float fCache, double dBytesWritten, double dImageSize, 
												KSaveDiscDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, (int)dImageSize, (int)fDeviceBuffer * 1000);
}

/*static*/ void KSaveDiscDialog::OnJobDoneEvent(KSaveDiscDialog *pDlg)
{
	pDlg->OnJobDone();
}

void KSaveDiscDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

void KSaveDiscDialog::SetProgress(int nProgress, double dCurrentSector, double dTotalSectors, int nErrorsCount)
{
	CString strTmp;
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(nProgress);
	
	strTmp.Format(_T("%.0f"), dCurrentSector);
	SetDlgItemText(IDC_SECTOR, strTmp);

	strTmp.Format(_T("%.0f"), dTotalSectors);
	SetDlgItemText(IDC_TOTAL, strTmp);

	strTmp.Format(_T("%d"), nErrorsCount);
	SetDlgItemText(IDC_ERRORS, strTmp);
}


void KSaveDiscDialog::OnJobDone()
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

void KSaveDiscDialog::Done()
{	
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	SetDlgItemText(IDOK, _T("&Close"));
	KillTimer(1);
}

/*static*/ void KSaveDiscDialog::OnBurnDoneEvent(const TCHAR *pcError, KSaveDiscDialog *pDlg)
{
	pDlg->SendMessage(WM_BURNDONE_NOTIFY, (WPARAM)pcError);
}

LRESULT KSaveDiscDialog::OnOnBurnDoneNotify(WPARAM pcError, LPARAM)
{
	if (pcError && _tcslen((TCHAR *)pcError) > 0)
	{
		AfxMessageBox((TCHAR *)pcError);
	}

	return 0;
}

void KSaveDiscDialog::OnBnClickedOk()
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

void KSaveDiscDialog::HandleError(int32 errCode)
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


void KSaveDiscDialog::OnTimer(UINT_PTR ID)
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

void KSaveDiscDialog::OnCancel()
{
	m_enState = ST_CANCELLED;
	
	if (::Abort() != BS_SDK_ERROR_NO)
	{
		KillTimer(1);
		RestoreEvents();
		CDialog::OnCancel();
	}
}