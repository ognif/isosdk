// ScanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioMFC.h"
#include "AcqDlg.h"
#include "AudioMFCDlg.h"
#include "IsoSDKExport.h"

/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog


CAcqDlg::CAcqDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAcqDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAcqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAcqDlg, CDialog)
	//{{AFX_MSG_MAP(CAcqDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, OnBnClickedAbortscan)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanDlg message handlers

BOOL CAcqDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAcqDlg::SetSender(CAudioMFCDlg *pCtrl)
{
	m_pControl = pCtrl;
}

void CAcqDlg::OnBnClickedAbortscan()
{
	ShowWindow(false);
}
