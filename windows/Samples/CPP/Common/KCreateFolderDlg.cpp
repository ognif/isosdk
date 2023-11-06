// KCreateFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KCreateFolderDlg.h"


// KCreateFolderDlg dialog

IMPLEMENT_DYNAMIC(KCreateFolderDlg, CDialog)
KCreateFolderDlg::KCreateFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(KCreateFolderDlg::IDD, pParent)
{
	m_strFolderName = _T("");
}

KCreateFolderDlg::~KCreateFolderDlg()
{
}

void KCreateFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

CString KCreateFolderDlg::GetFolderName()
{
    return m_strFolderName;	
}


BEGIN_MESSAGE_MAP(KCreateFolderDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// KCreateFolderDlg message handlers

void KCreateFolderDlg::OnBnClickedOk()
{
	this->GetDlgItemText(IDC_EDIT_NEW_FOLDER, m_strFolderName);
	
	OnOK();
}
