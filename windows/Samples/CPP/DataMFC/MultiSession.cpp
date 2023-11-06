// MultiSession.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <dbt.h>
#include "DataMFC.h"
#include "MultiSession.h"
#include "DataMFCDlg.h"

#include "IsoSDKExport.h"

// CMultiSession-Dialogfeld

IMPLEMENT_DYNAMIC(CMultiSession, CDialog)
CMultiSession::CMultiSession(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiSession::IDD, pParent)
	, m_nSession(0)
{
}

CMultiSession::~CMultiSession()
{
}

void CMultiSession::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SESSIONS, m_lstSessions);
}


BEGIN_MESSAGE_MAP(CMultiSession, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()


// CMultiSession-Meldungshandler

BOOL CMultiSession::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstSessions.InsertColumn(0, _T("#"), LVCFMT_LEFT, 65);
	m_lstSessions.InsertColumn(1, _T("Startsector"), LVCFMT_LEFT, 155);
	m_lstSessions.InsertColumn(2, _T("Size"), LVCFMT_LEFT, 145);
	m_lstSessions.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	FillInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CMultiSession::HandleError(__int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		TCHAR chErrorDesc[2048];
		__int32 nLength = 2048;

		GetText(errCode, chError, &nLength);
		wsprintf(chErrorDesc, _T("error: %s"), chError);
		AfxMessageBox(chErrorDesc);
	}
}

void CMultiSession::FillInfo()
{
	TCHAR pszDest[256];

	m_lstSessions.DeleteAllItems();

	SMediumInfo mi;
	__int32 nError = GetMediumInformation(BS_CURRENT_DEVICE, &mi);

	if (BS_SDK_ERROR_NO == nError)
	{
		for (int32 i = 0; i < mi.nLastSession; i++)
		{
			SSessionInfo info;
			nError = GetSessionInformation(BS_CURRENT_DEVICE, i + 1, &info);
			HandleError(nError);

			int count = m_lstSessions.GetItemCount();

			_stprintf(pszDest, _T("%d"), i+1);
			m_lstSessions.InsertItem(count, pszDest);
			_stprintf(pszDest, _T("%d"), info.dStartLBA);
			m_lstSessions.SetItemText(count, 1, pszDest);
			_stprintf(pszDest, _T("%d"), info.dSessionSize);
			m_lstSessions.SetItemText(count, 2, pszDest);
		}
	}
}


BOOL CMultiSession::OnDeviceChange(UINT wParam, DWORD_PTR lParam)
{
	if (wParam == DBT_DEVICEARRIVAL || wParam == DBT_DEVICEREMOVECOMPLETE)
	{
		if (wParam == DBT_DEVICEARRIVAL)
			Sleep(3000);

		FillInfo();
	}

	return TRUE;
}

void CMultiSession::OnBnClickedOk()
{
	int nselected = m_lstSessions.GetSelectedCount();
	if (nselected > 0)
	{
		POSITION pos = m_lstSessions.GetFirstSelectedItemPosition();
		m_nSession = m_lstSessions.GetNextSelectedItem(pos) + 1;
	}

	OnOK();
}

void CMultiSession::OnBnClickedCancel()
{
	m_nSession = 0;
	OnCancel();
}
