#include "stdafx.h"
#include "SampleBurnDlgMFC.h"

#define TITLE_BURN_FORMAT _T("%d%% written on %s [%s]")
#define TITLE_VERIFY_FORMAT _T("%d%% verified on %s [%s]")


void CSampleBurnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BURN_LOG, m_lstLog);
	DDX_Control(pDX, IDC_PROGRESS_BUFFER, m_pbBuffer);
	DDX_Control(pDX, IDC_PROGRESS_TOTAL, m_pbTotal);
	DDX_Control(pDX, IDC_CURRENT_FILE, m_lblCurrentFile);
	DDX_Control(pDX, IDC_TOTAL_TIME, m_lblElapsed);
	DDX_Control(pDX, IDC_CURRENT_SPEED, m_lblSpeed);
}

BEGIN_MESSAGE_MAP(CSampleBurnDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDC_SAVE_LOG, OnSaveLog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CSampleBurnDlg::OnFinalizeEvent(CSampleBurnDlg* pDlg) 
{
	pDlg->AddLogLine(_T("Finalize..."));
	pDlg->m_enState = ST_FINALIZE;
}

void CSampleBurnDlg::OnBurnDoneEvent(const TCHAR* pcError, CSampleBurnDlg* pDlg) 
{
	if ((pcError == NULL) || (0 == _tcslen(pcError))) {
		pDlg->AddLogLine(_T("Burn Done"));
	} 
	else {
		pDlg->AddLogLine(pcError);
		pDlg->AddLogLine(_T("Burn Done With Errors"));
	}

	pDlg->SetProgress(0,0);
}

void CSampleBurnDlg::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesWritten, double dImageSize, CSampleBurnDlg *pDlg) 
{
	pDlg->SetProgress((int)fPercent, (int)fCache);
}

void CSampleBurnDlg::OnStartVerifyEvent(CSampleBurnDlg *pDlg)
{
	pDlg->AddLogLine(_T("Starting verification..."));
	pDlg->m_enState = ST_VERIFY;
}

void CSampleBurnDlg::OnVerifyFileEvent(const TCHAR* pcFileName, CSampleBurnDlg *pDlg)
{
	pDlg->AddLogLine(pcFileName);
}

void CSampleBurnDlg::OnVerifyErrorEvent(const TCHAR* pcFileName, const TCHAR* pcError, CSampleBurnDlg *pDlg)
{
	CString strError = pcError;
	strError += _T(": ");
	strError += pcFileName;

	pDlg->AddLogLine(strError);
}

void CSampleBurnDlg::OnVerifyDoneEvent(int nNumErrors, CSampleBurnDlg *pDlg)
{
	pDlg->AddLogLine(_T("Verification complete"));
	pDlg->SetProgress(0,0);
}

void CSampleBurnDlg::OnJobDoneEvent(CSampleBurnDlg *pDlg)
{
	pDlg->OnJobDone();
}

void CSampleBurnDlg::OnInfoTextEvent(const TCHAR *pcInfoText, int32 nLevel, CSampleBurnDlg *pDlg)
{
	pDlg->AddLogLine(pcInfoText);
}

void CSampleBurnDlg::OnBurnFileEvent(const TCHAR* pcFileName, CSampleBurnDlg* pDlg)
{
	pDlg->SetCurrentFile(pcFileName);
}

CSampleBurnDlg::CSampleBurnDlg(CWnd* pParent)
	:CDialog(CSampleBurnDlg::IDD, pParent)
	,m_enState(ST_NONE)
{
}

BOOL CSampleBurnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_nStartTime = CTime::GetCurrentTime();

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------

	SetFinalizeEventCallback((FinalizeEvent) CSampleBurnDlg::OnFinalizeEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) CSampleBurnDlg::OnBurnDoneEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) CSampleBurnDlg::OnJobDoneEvent, this);
	SetProcessEventCallback((ProcessEvent) CSampleBurnDlg::OnProcessEvent, this);
	SetInfoTextEventCallback((InfoTextEvent) CSampleBurnDlg::OnInfoTextEvent, BS_IL_INFO,  this);
	SetStartVerifyEventCallback((StartVerifyEvent) CSampleBurnDlg::OnStartVerifyEvent, this);
	SetVerifyFileEventCallback((VerifyFileEvent) CSampleBurnDlg::OnVerifyFileEvent, this);
	SetVerifyErrorEventCallback((VerifyErrorEvent) CSampleBurnDlg::OnVerifyErrorEvent, this);
	SetVerifyDoneEventCallback((VerifyDoneEvent) CSampleBurnDlg::OnVerifyDoneEvent, this);
	SetBurnFileEventCallback((BurnFileEvent) CSampleBurnDlg::OnBurnFileEvent, this);

	// Get volume label

	SOptions opt;
	::GetOptions(&opt);

	m_strLabel = opt.chVolumeLabel;

	// Get burning device
	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);

	m_strDevice = CString(chBurnDevices[0][0]) + _T(":");

	// Update window's title

	CString strTitle;
	strTitle.Format(TITLE_BURN_FORMAT, 0, (const TCHAR*)m_strDevice, (const TCHAR*)m_strLabel);
	SetWindowText(strTitle);

	//--------------------------------------------------
	// Start burning
	//--------------------------------------------------

	// It's mandatory to prepare project before burning

	m_lstLog.AddString(_T("Prepare Collection"));
	res = ::Prepare();
	HandleError(res);

	if (BS_SDK_ERROR_NO == res) 
	{
		// Get current burn speed

		int32 nSpeed = 0;
		::GetBurnSpeed(BS_CURRENT_DEVICE, &nSpeed);

		if (nSpeed == BS_MAX_SPEED)
			::GetMaxBurnSpeed(BS_CURRENT_DEVICE, &nSpeed);

		// Update speed label

		CString strSpeed;
		if (nSpeed == BS_NDEF)
			strSpeed = _T("n/a");
		else
			strSpeed.Format(_T("%d KB/s"), nSpeed);

		m_lblSpeed.SetWindowText(_T("Current Speed: ") + strSpeed);

		// Project is successfully prepared - burn it

		m_lstLog.AddString(_T("Start Burning..."));
		res = ::Burn();
		HandleError(res);

		if (BS_SDK_ERROR_NO == res) 
		{
			// Burning successfully started
			m_enState = ST_BURN;
			SetTimer(1, 1000, NULL);
		}
	}

	return TRUE;
}

void CSampleBurnDlg::RestoreEvents()
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

CSampleBurnDlg::~CSampleBurnDlg()
{
}

void CSampleBurnDlg::OnCancel()
{
	if (m_enState != ST_NONE)
	{
		::Abort();
	}
	else
	{
		RestoreEvents();
		CDialog::OnCancel();
	}
}

void CSampleBurnDlg::OnSaveLog()
{
	CFileDialog fileDlg(FALSE, NULL, NULL, 0, _T("Log Files (*.log)"), this);

	if (fileDlg.DoModal() == IDOK)
		::SaveLogToFile(fileDlg.GetPathName());
}

void CSampleBurnDlg::AddLogLine(const CString& strLogLine)
{
	int n = m_lstLog.AddString(strLogLine);
}

void CSampleBurnDlg::SetProgress(int progress, int buffer)
{
	m_pbTotal.SetPos(progress);
	m_pbBuffer.SetPos(buffer);

	UpdateTitle(progress);
}

void CSampleBurnDlg::OnJobDone()
{
	m_enState = ST_NONE;
	GetDlgItem(IDCANCEL)->SetWindowText(_T("Close"));
}

void CSampleBurnDlg::SetCurrentFile(const CString& strFileName)
{
	m_lblCurrentFile.SetWindowText(strFileName);
}

void CSampleBurnDlg::OnTimer(UINT_PTR nID)
{
	CTimeSpan nDiff = CTime::GetCurrentTime() - m_nStartTime;

	CString strElapsed;
	strElapsed.Format(_T("Total Time: %.2d:%.2d:%.2d"), nDiff.GetHours(), nDiff.GetMinutes(), nDiff.GetSeconds());
	m_lblElapsed.SetWindowText(strElapsed);

	if (m_enState == ST_NONE)
		KillTimer(nID);
}

void CSampleBurnDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		int32 nLength = 2048;

		// Get error description

		::GetText(errCode, chError, &nLength);

		CString strError;
		strError.Format(_T("error: %s"), chError);
		AddLogLine(strError);
	}
}

void CSampleBurnDlg::UpdateTitle(int progress)
{
	if (m_enState == ST_BURN || m_enState == ST_FINALIZE)
	{
		int titleProgress = m_enState == ST_BURN ? progress : 100;
		if (titleProgress != 0)
		{
			CString strTitle;
			strTitle.Format(TITLE_BURN_FORMAT, titleProgress, m_strDevice,  m_strLabel);
			SetWindowText(strTitle);
		}
	}
	else if (m_enState == ST_VERIFY)
	{
		if (progress != 0)
		{
			CString strTitle;
			strTitle.Format(TITLE_VERIFY_FORMAT, progress, m_strDevice, m_strLabel);
			SetWindowText(strTitle);
		}
	}
}