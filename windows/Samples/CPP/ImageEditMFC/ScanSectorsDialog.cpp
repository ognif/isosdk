// ScanSectorsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "ScanSectorsDialog.h"


// KScanSectorsDialog dialog

IMPLEMENT_DYNAMIC(KScanSectorsDialog, CDialog)
KScanSectorsDialog::KScanSectorsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KScanSectorsDialog::IDD, pParent)
	, m_pLogger(0)
	, m_pLogCreator(0)
	, m_pThread(NULL)
{
}

KScanSectorsDialog::KScanSectorsDialog(CWnd* pParent, int32 nStartLBA, int32 nRegionSizeInSectors, ILogCreator* pLogCreator)
	: CDialog(KScanSectorsDialog::IDD, pParent)
	, m_pLogger(0)
	, m_pLogCreator(0)
	, m_pThread(NULL)
	
{
	m_pLogCreator = pLogCreator;

	m_pLogger = pLogCreator->CreateLogger();
	m_pLogger->SetStartLba(nStartLBA);
	m_pLogger->SetRegionSize(nRegionSizeInSectors);
}

KScanSectorsDialog::~KScanSectorsDialog()
{
}

void KScanSectorsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KScanSectorsDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START, OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedStop)
END_MESSAGE_MAP()


// KScanSectorsDialog message handlers

BOOL KScanSectorsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_pLogCreator || !m_pLogger)
	{
		return FALSE;
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	CRect rect;
	this->GetClientRect(&rect);
	rect.bottom -= 70;
	rect.top += 10;
	rect.left += 10;
	rect.right -= 10;

	CWnd* pLoggingWidget = m_pLogCreator->CreateLoggingWidget(this, rect);
	m_pLogger->AttachToLoggingWidget(pLoggingWidget);

	OnBnClickedStart();

	return TRUE;
}

void KScanSectorsDialog::EnableStart()
{
	m_pThread = NULL;

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
}

void KScanSectorsDialog::EnableStop()
{	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

void KScanSectorsDialog::OnBnClickedStart()
{
	m_pThread = AfxBeginThread(ScanThreadProc, this);
	EnableStop();
}

void KScanSectorsDialog::OnBnClickedStop()
{
	if (m_pThread)
	{
		if (WaitForSingleObject(m_pThread->m_hThread, 0) != WAIT_OBJECT_0)
		{	
			m_pLogger->Cancel();

			AfxMessageBox(_T("Aborted by user"));

			if (WaitForSingleObject(m_pThread->m_hThread, 2000) != WAIT_OBJECT_0)
			{
				TerminateThread(m_pThread->m_hThread, 0);
			}
		}

		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(0);
		EnableStart();
	}
}

UINT KScanSectorsDialog::ScanThreadProc(LPVOID param)  
{
	KScanSectorsDialog *p = (KScanSectorsDialog *)param;

	p->ScanProc();

	return 1;
}

void KScanSectorsDialog::ScanProc()
{
	if (m_pLogger->GetRegionSize())
	{
		m_pLogger->Reset();		

		const int32 nMaxSectorsToRead = 27;

		int32 nCurLba;
		int32 nSectorsToRead = nMaxSectorsToRead;

		for (nCurLba = m_pLogger->GetStartLba(); 
			(nCurLba < m_pLogger->GetStartLba() + m_pLogger->GetRegionSize()) &&
			!m_pLogger->IsCancelled(); )
		{
			if (nCurLba + nMaxSectorsToRead >= m_pLogger->GetStartLba() + 
				m_pLogger->GetRegionSize())
			{
				nSectorsToRead = m_pLogger->GetStartLba() + 
					m_pLogger->GetRegionSize() - nCurLba;
			}

			const int32 buff_length = 2352 * nMaxSectorsToRead;
			byte buff[buff_length];
			int32 nRes = ::ReadSectors(BS_READ_DEVICE, nCurLba, 
				nSectorsToRead, BS_IMG_BIN, buff, buff_length);

			if (nRes == BS_SDK_ERROR_NO)
			{
				m_pLogger->LogSuccessiveRead(nCurLba, nSectorsToRead);
			}
			else
			{
				int32 nErrLba = nCurLba;
				for (;nCurLba < nErrLba + nSectorsToRead; ++nCurLba)
				{
					int32 nRes = ::ReadSectors(BS_READ_DEVICE, nCurLba, 1, 
						BS_IMG_BIN, buff, buff_length);

					if (nRes == BS_SDK_ERROR_NO)				
					{
						m_pLogger->LogSuccessiveRead(nCurLba, 1);
					}
					else
					{
						m_pLogger->LogFailureRead(nCurLba);
					}
				}
			}

			((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos((100 * 
				(nCurLba + 1 - m_pLogger->GetStartLba())) / 
				m_pLogger->GetRegionSize());
			
			nCurLba += nSectorsToRead;			
		}	

		if(!m_pLogger->IsCancelled())
		{
			m_pLogger->Done();
			((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(100);
			EnableStart();
		}
	}
}

void KScanSectorsDialog::OnCancel()
{
	if (m_pThread)
	{
		if (WaitForSingleObject(m_pThread->m_hThread, 0) != WAIT_OBJECT_0)
		{	
			m_pLogger->Cancel();

			AfxMessageBox(_T("Aborted by user"));
		
			if (WaitForSingleObject(m_pThread->m_hThread, 2000) != WAIT_OBJECT_0)
			{
				TerminateThread(m_pThread->m_hThread, 0);
			}
		}
		
		m_pThread = NULL;
	}

	CDialog::OnCancel();
}