#include "stdafx.h"
#include "VideoMFC.h"
#include "ScanDlg.h"
#include "VideoMFCDlg.h"
#include "IsoSDKExport.h"

/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog

void CScanDlg::OnVideoScannerEvent(float fPercent, const TCHAR *pcFileName, CScanDlg* pDlg)
{
	pDlg->m_prgScan.SetPos((int) fPercent);
}

void CScanDlg::OnVideoScanDoneEvent(const TCHAR *pcFileName,const TCHAR *pcError,__int32 nErrorCode,struct SVideoFormat CurrentFormat, CScanDlg* pDlg)
{
	pDlg->m_strPlaytime.Format(_T("%i:%i"), CurrentFormat.nPlaytime / 60, CurrentFormat.nPlaytime % 60);
	pDlg->m_strFrameRate.Format(_T("%.2lf Frames/sec"), CurrentFormat.fFPS);
	pDlg->m_strBitrate.Format(_T("%d bits/s"), CurrentFormat.nBitRate);
	pDlg->m_strAspectRatio.Format(_T("%i"), CurrentFormat.nAspectRatio);
	pDlg->m_strDimensions.Format(_T("%i X %i"), CurrentFormat.nWidth, CurrentFormat.nHeight);

	if (0 == nErrorCode)
	{
		pDlg->PostMessage(WM_COMMAND, IDOK, 0);
	}
	else
	{
		if (nErrorCode != BS_SDK_ERROR_ABORTED)
		{
			pDlg->GetDlgItem(IDC_STATIC)->SetWindowText(pcError);
			pDlg->m_prgScan.SetPos(0);
		}
	}
}


CScanDlg::CScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanDlg::IDD, pParent)
	, m_bPictureFile(false)
{
}


void CScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCANPRG, m_prgScan);
}


BEGIN_MESSAGE_MAP(CScanDlg, CDialog)
	ON_BN_CLICKED(IDC_ABORTSCAN, OnBnClickedAbortscan)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanDlg message handlers

BOOL CScanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SFileToAdd file;
	file.lpszSourceFilePath = m_strFileToAdd;
	if (m_bPictureFile) {
#ifdef WIN32
		file.lpszDestinationPath = _T("\\SEGMENT");
#else
		file.lpszDestinationPath = _T("/SEGMENT");
#endif	
	}
	else {
#ifdef WIN32
		file.lpszDestinationPath = _T("\\");
#else
		file.lpszDestinationPath = _T("/");
#endif
	}
		
	file.bVideoFile = BS_TRUE;
	file.nSavePath = BS_DONT_SAVE_PATH;

	int32 res = ::AddFile(file);

	GetDlgItem(IDC_STATIC)->SetWindowText(_T("Scanning Mpeg File..."));

	m_prgScan.SetRange(0,100);
	return FALSE;
}

void CScanDlg::OnBnClickedAbortscan()
{
	::StopMpegAction();
	OnCancel();
}
