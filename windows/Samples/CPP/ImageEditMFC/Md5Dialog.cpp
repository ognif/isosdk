// Md5Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "Md5Dialog.h"
#include ".\md5dialog.h"


// KMd5Dialog dialog

IMPLEMENT_DYNAMIC(KMd5Dialog, CDialog)
KMd5Dialog::KMd5Dialog(CWnd* pParent, CString strFileName)
	: CDialog(KMd5Dialog::IDD, pParent)	
	, m_strMD5("")
	, m_strFileName(strFileName)
{
	m_pcMD5FileSource = new KMD5FileSource(strFileName.GetBuffer());
	strFileName.ReleaseBuffer();

	m_cMD5Counter.SetDataSource(m_pcMD5FileSource);
}

KMd5Dialog::~KMd5Dialog()
{
	delete m_pcMD5FileSource;
}

void KMd5Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KMd5Dialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// KMd5Dialog message handlers

BOOL KMd5Dialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	SetDlgItemText(IDC_FILE, m_strFileName);

	m_cMD5Counter.start();

	SetTimer(1, 20, NULL);

	return TRUE;
}


void KMd5Dialog::GenerateMD5()
{
	unsigned char* pucharMD5 = m_cMD5Counter.GetMD5();
	m_strMD5.Empty();
	CStringA temp;

	for (int i = 0 ; i < 16; ++i)
	{
		temp.Format("%02x", (int)pucharMD5[i]);
		m_strMD5 += temp;
	}	
}

CStringA KMd5Dialog::GetMD5String()
{
	return m_strMD5;
}

void KMd5Dialog::OnBnClickedOk()
{	
	OnOK();
}

void KMd5Dialog::OnTimer(UINT_PTR ID)
{
	KillTimer(1);

	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(m_cMD5Counter.GetProgress());

	if (m_cMD5Counter.IsCountingDone())
	{
		GenerateMD5();
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(100);
		SetDlgItemText(IDOK, _T("&Close"));
	}
	else
	{
		SetTimer(1, 20, NULL);
	}
}
