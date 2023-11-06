// CDTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioMFC.h"
#include "CDTextDlg.h"
#include <algorithm>


CFileAudioProperty::CFileAudioProperty()
	:nPlayTime(0)
{
	UpdateData();
	data.nPause = 2;
	data.bPauseInFrames = BS_FALSE;
}

CFileAudioProperty::CFileAudioProperty(const CFileAudioProperty &prp)
	: strSourceFilePath(prp.strSourceFilePath)
	, strTitle(prp.strTitle)
	, strPerformer(prp.strPerformer)
	, strSongWriter(prp.strSongWriter)
	, strComposer(prp.strComposer)
	, strArranger(prp.strArranger)
	, strMessage(prp.strMessage)
	, strMcnIsrc(prp.strMcnIsrc)
	, nPlayTime(prp.nPlayTime)
	, vIndexes(prp.vIndexes)
{
	UpdateData();
	data.nPause = prp.data.nPause;
	data.bPauseInFrames = prp.data.bPauseInFrames;
}

void CFileAudioProperty::SetTrackNumber(int nTrack)
{
	strSourceFilePath.Format(_T("%02d"), nTrack);
	data.lpszSourceFilePath = strSourceFilePath;
}

CFileAudioProperty::CFileAudioProperty(const CString &filePath)
	:nPlayTime(0)
{
	UpdateData();
	strSourceFilePath = filePath;
	data.nPause = 2;
	data.bPauseInFrames = BS_FALSE;
}

void CFileAudioProperty::UpdateData()
{
	data.lpszSourceFilePath = strSourceFilePath;
	data.lpszTitle = strTitle;
	data.Performer = strPerformer;
	data.SongWriter = strSongWriter;
	data.Composer = strComposer;
	data.Arranger = strArranger;
	data.Message = strMessage;
	data.lpszMCN_ISRC = strMcnIsrc;

	if (vIndexes.empty())
	{
		data.pIndexes = 0;
		data.nIndexesLength = 0;
	}
	else
	{
		data.pIndexes = &vIndexes[0];
		data.nIndexesLength = int32(vIndexes.size());
	}
}

// CCDTextDlg dialog

IMPLEMENT_DYNAMIC(CPropertiesDlg, CDialog)
CPropertiesDlg::CPropertiesDlg(bool bIsDiscText, CWnd* pParent /*=NULL*/)
	: CDialog(CPropertiesDlg::IDD, pParent)
	, m_bIsDiscText(bIsDiscText)
{
}

BOOL CPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CTabCtrl* pTabs = (CTabCtrl*)GetDlgItem(IDC_TAB1);

	pTabs->InsertItem(0, _T("CD Text"));

	if (!m_bIsDiscText)
		pTabs->InsertItem(1, _T("Indexes"));

	CRect rect;
	GetClientRect(&rect);
	pTabs->AdjustRect(FALSE, &rect);

	m_dlgCDText.Create(CCDTextTab::IDD, pTabs);
	m_dlgCDText.SetWindowPos(0, rect.left, rect.top, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	
	m_dlgIndexes.Create(CIndexesTab::IDD, pTabs);
	m_dlgIndexes.SetWindowPos(0, rect.left, rect.top, 0, 0, SWP_NOSIZE|SWP_NOZORDER);

	if (m_bIsDiscText)
	{
		SetWindowText(_T("Disk CD text"));
		m_dlgCDText.SetDlgItemText(IDC_DISCCODE, _T("UPC/EAN:"));
		m_dlgCDText.GetDlgItem(IDC_EDIT_PAUSE)->EnableWindow(FALSE);
		m_dlgCDText.GetDlgItem(IDC_CHECK_PAUSE_IN_FRAMES)->EnableWindow(FALSE);
	}
	else
	{
		SetWindowText(_T("Track CD text"));
		m_dlgCDText.SetDlgItemText(IDC_DISCCODE, _T("ISRC:"));
	}

	SetFileProperty(m_pFileInfo);

	return TRUE;
}

void CPropertiesDlg::SetFileProperty(CFileAudioProperty *pInfo)
{
	m_pFileInfo = pInfo;

	if (pInfo)
	{
		if (IsWindow(m_dlgCDText.m_hWnd))
			m_dlgCDText.SetFileProperty(*pInfo);

		if (IsWindow(m_dlgIndexes.m_hWnd))
			m_dlgIndexes.SetFileProperty(*pInfo);
	}
}

void CPropertiesDlg::OnBnClickedOk()
{
	UpdateData();

	if (m_pFileInfo)
	{
		m_dlgCDText.GetFileProperty(m_pFileInfo);
		m_dlgIndexes.GetFileProperty(m_pFileInfo);

		m_pFileInfo->UpdateData();
	}

	OnOK();
}

void CPropertiesDlg::OnBnClickedReset()
{
	SetFileProperty(m_pFileInfo);

	UpdateData(FALSE);
}

void CPropertiesDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSel = ((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetCurSel();

	m_dlgCDText.ShowWindow(nSel == 0 ? SW_SHOW : SW_HIDE);
	m_dlgIndexes.ShowWindow(nSel == 1 ? SW_SHOW : SW_HIDE);	
}

BEGIN_MESSAGE_MAP(CPropertiesDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CCDTextTab, CDialog)
CCDTextTab::CCDTextTab(CWnd *pParent)
	:CDialog(CCDTextTab::IDD, pParent)
	,m_nPause(2)
	,m_nPauseInFrames(0)
{
}

void CCDTextTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ARRANGER, m_strArranger);
	DDX_Text(pDX, IDC_EDIT_COMPOSER, m_strComposer);
	DDX_Text(pDX, IDC_EDIT_SONGWRITER, m_strSongWriter);
	DDX_Text(pDX, IDC_EDIT_PERFORMER, m_strPerformer);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_DISCCODE, m_strMcnIsrc);
	DDX_Text(pDX, IDC_EDIT_PAUSE, m_nPause);
	DDX_Check(pDX, IDC_CHECK_PAUSE_IN_FRAMES, m_nPauseInFrames);
}

void CCDTextTab::SetFileProperty(const CFileAudioProperty& rInfo)
{
	m_strArranger = rInfo.strArranger;
	m_strComposer = rInfo.strComposer;
	m_strSongWriter = rInfo.strSongWriter;
	m_strPerformer = rInfo.strPerformer;
	m_strMessage = rInfo.strMessage;
	m_strTitle = rInfo.strTitle;
	m_strMcnIsrc = rInfo.strMcnIsrc;
	m_nPause = rInfo.data.nPause;
	m_nPauseInFrames = rInfo.data.bPauseInFrames == BS_TRUE ? 1 : 0;

	UpdateData(FALSE);
}

void CCDTextTab::GetFileProperty(CFileAudioProperty *pInfo)
{
	UpdateData(TRUE);

	pInfo->strArranger = m_strArranger;
	pInfo->strComposer = m_strComposer;
	pInfo->strSongWriter = m_strSongWriter;
	pInfo->strPerformer = m_strPerformer;
	pInfo->strMessage = m_strMessage;
	pInfo->strTitle = m_strTitle;
	pInfo->strMcnIsrc = m_strMcnIsrc;
	pInfo->data.nPause = m_nPause;
	pInfo->data.bPauseInFrames = m_nPauseInFrames ? BS_TRUE : BS_FALSE;
}

BEGIN_MESSAGE_MAP(CCDTextTab, CDialog)
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CIndexesTab, CDialog)
CIndexesTab::CIndexesTab(CWnd *pParent)
	:CDialog(CIndexesTab::IDD, pParent)
	,m_nPlayTime(0)
	,m_nMin(0)
	,m_nSec(0)
	,m_nFrame(1)
{
}

BOOL CIndexesTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	CSpinButtonCtrl* pMinSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MIN);
	CSpinButtonCtrl* pSecSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SEC);
	CSpinButtonCtrl* pFrameSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_FRAME);

	pMinSpin->SetRange(0, 59);
	pSecSpin->SetRange(0, 59);
	pFrameSpin->SetRange(0, 74);

	return TRUE;
}

void CIndexesTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INDEXES, m_lstIndexes);
	DDX_Text(pDX, IDC_IDX_MIN, m_nMin);
	DDX_Text(pDX, IDC_IDX_SEC, m_nSec);
	DDX_Text(pDX, IDC_IDX_FRAME, m_nFrame);
}

void CIndexesTab::OnBnClickedAddIndex()
{
	UpdateData();

	if (m_nSec < 0 || m_nSec > 59 ||
		m_nFrame < 0 || m_nFrame > 74)
	{
		MessageBox(_T("Time is invalid."), _T("Track properties"), MB_OK|MB_ICONERROR); 
		return;
	}

	int nTime = (m_nMin * 60 + m_nSec) * 75 + m_nFrame;

	if (nTime <= 0 || nTime >=  m_nPlayTime * 75)
	{
		MessageBox(_T("Index is invalid."), _T("Track properties"), MB_OK|MB_ICONERROR);
		return;
	}

	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d"), m_nMin, m_nSec, m_nFrame);

	int nPos = m_lstIndexes.FindString(-1, strTime);

	if (nPos == -1)
	{
		nPos = m_lstIndexes.AddString(strTime);
		m_lstIndexes.SetItemData(nPos, nTime);
	}
}

void CIndexesTab::OnBnClickedDeleteIndex()
{
	int nPos = m_lstIndexes.GetCurSel();

	if (nPos != -1)
		m_lstIndexes.DeleteString(nPos);
}

void CIndexesTab::SetFileProperty(const CFileAudioProperty& rInfo)
{
	m_lstIndexes.ResetContent();
	for(size_t i = 0; i < rInfo.vIndexes.size(); ++i)
	{
		int32 nTime = rInfo.vIndexes[i];
		int nMin = (nTime/75)/60;
		int nSec = (nTime/75)%60;
		int nFrame = nTime % 75;
		CString strTime;

		strTime.Format(_T("%02d:%02d:%02d"), nMin, nSec, nFrame);

		int nPos = m_lstIndexes.AddString(strTime);
		m_lstIndexes.SetItemData(nPos, nTime);
	}
	m_nPlayTime = rInfo.nPlayTime;
}

void CIndexesTab::GetFileProperty(CFileAudioProperty *pInfo)
{
	pInfo->vIndexes.clear();
	for(int i = 0; i < m_lstIndexes.GetCount(); ++i)
		pInfo->vIndexes.push_back(int(m_lstIndexes.GetItemData(i)));

	std::sort(pInfo->vIndexes.begin(), pInfo->vIndexes.end());
}

BEGIN_MESSAGE_MAP(CIndexesTab, CDialog)
	ON_BN_CLICKED(IDC_IDX_ADD, OnBnClickedAddIndex)
	ON_BN_CLICKED(IDC_IDX_DELETE, OnBnClickedDeleteIndex)
END_MESSAGE_MAP()
