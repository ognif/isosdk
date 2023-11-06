// ChangeRegionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UtilitiesMFC.h"
#include "IsoSDKExport.h"
#include "ChangeRegionDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CChangeRegionDlg dialog

CChangeRegionDlg::CChangeRegionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeRegionDlg::IDD, pParent)
	, m_nRegion(0)
{
}

BEGIN_MESSAGE_MAP(CChangeRegionDlg, CDialog)
END_MESSAGE_MAP()

void CChangeRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_REGION1, m_nRegion);
}

/*BOOL CChangeRegionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}*/

void CChangeRegionDlg::OnOK()
{
	UpdateData(TRUE);

	int32 res = ::SetRegionalCode(BS_CURRENT_DEVICE, m_nRegion + 1);
	HandleError(res);

	CDialog::OnOK();
}

void CChangeRegionDlg::HandleError(int32 errCode)
{
	GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}
