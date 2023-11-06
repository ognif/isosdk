// PasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "PasswordDlg.h"


// CPasswordDlg dialog

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialog)
CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
{
}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PWD, m_strPassword);
}

BOOL CPasswordDlg::OnInitDialog()
{
	SetWindowText(_T("Please enter your password"));
	return TRUE;
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
END_MESSAGE_MAP()


// CPasswordDlg message handlers
