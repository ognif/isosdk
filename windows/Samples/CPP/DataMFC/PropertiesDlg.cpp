// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataMFC.h"
#include "PropertiesDlg.h"
#include <strsafe.h>

CTime FileTimeToCTime(const SFileDateTime &fileTime)
{
	return CTime(fileTime.nYear + 1900, fileTime.nMonth, fileTime.nDay, fileTime.nHour, fileTime.nMinute, fileTime.nSecond);
}

void CTimeToFileTime(const CTime &time, SFileDateTime *pFileTime)
{
	ASSERT(pFileTime);
	pFileTime->nYear = time.GetYear() - 1900;
	pFileTime->nMonth = time.GetMonth();
	pFileTime->nDay = time.GetDay();
	pFileTime->nHour = time.GetHour();
	pFileTime->nMinute = time.GetMinute();
	pFileTime->nSecond = time.GetSecond();
}

// PropertiesDlg dialog

IMPLEMENT_DYNAMIC(PropertiesDlg, CDialog)

PropertiesDlg::PropertiesDlg(SFileEntry *pFileEntry) :
	CDialog(PropertiesDlg::IDD),
	m_pFileEntry(pFileEntry)
	, m_strFileName(pFileEntry->lpszFileName)
{
}

PropertiesDlg::~PropertiesDlg()
{
}

void PropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_CREATION_TIME, m_ctlCreationTime);
	DDX_Control(pDX, IDC_MODIFICATION_TIME, m_ctlModificationTime);
	DDX_Control(pDX, IDC_ACCESS_TIME, m_ctlAccessTime);
	DDX_Text(pDX, IDC_NAME, m_strFileName);
	DDX_Control(pDX, IDC_PRIORITY, m_ctlPriority);
}

BEGIN_MESSAGE_MAP(PropertiesDlg, CDialog)
END_MESSAGE_MAP()


// PropertiesDlg message handlers

BOOL PropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Get date format for the current user.
	CString strDateFormat;
	::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, strDateFormat.GetBuffer(100), 100);
	strDateFormat.ReleaseBuffer();

	// Get time format for the current user.
	CString strTimeFormat;
	::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT, strTimeFormat.GetBuffer(100), 100);
	strTimeFormat.ReleaseBuffer();

	CString strDateTimeFormat = strDateFormat + _T(" ") + strTimeFormat;

	m_ctlCreationTime.SetFormat(strDateTimeFormat);
	m_ctlCreationTime.SetTime(&FileTimeToCTime(m_pFileEntry->cCreationTime));

	m_ctlModificationTime.SetFormat(strDateTimeFormat);
	m_ctlModificationTime.SetTime(&FileTimeToCTime(m_pFileEntry->cDateTime));

	m_ctlAccessTime.SetFormat(strDateTimeFormat);
	m_ctlAccessTime.SetTime(&FileTimeToCTime(m_pFileEntry->cAccessTime));

	CheckDlgButton(IDC_GLOBALUSAGE, BST_UNCHECKED);

	CheckDlgButton(IDC_HIDDEN, m_pFileEntry->nAttrib & BS_FA_HIDDEN ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_ADVANCED_HIDDEN, m_pFileEntry->nAttrib & BS_FA_ADVANCED_HIDDEN ? BST_CHECKED : BST_UNCHECKED);

	InitializePriorityComboBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void PropertiesDlg::InitializePriorityComboBox()
{
	m_ctlPriority.AddString(_T("0 - Lowest (Default)"));
	for (int priority = 1; priority < 100; priority++)
	{
		CString strPriority;
		strPriority.Format(_T("%d"), priority);
		m_ctlPriority.AddString(strPriority);
	}
	m_ctlPriority.AddString(_T("100 - Highest"));
	m_ctlPriority.SetCurSel((int)m_pFileEntry->pUserParam);
}

void PropertiesDlg::OnOK()
{
	int result = BS_SDK_ERROR_NO;

	UpdateData(TRUE);

	if (m_strFileName.IsEmpty())
	{
		AfxMessageBox(_T("File name cannot be empty."), MB_OK | MB_ICONERROR);
		return;
	}

	CString strPath = m_pFileEntry->lpszFilePath;
	if (strPath != PATHSEPSTRING)
		strPath += PATHSEPSTRING;
	CString strSourcePath = strPath + m_pFileEntry->lpszFileName;
	CString strDestinationPath = strPath + m_strFileName;

	// Rename the file if the name has been changed.
	if (strSourcePath != strDestinationPath)
	{
		SFileToRename fileToRename;
		fileToRename.lpszSourcePath = strSourcePath;
		fileToRename.lpszDestinationPath = strDestinationPath;
		result = ::RenameFile(fileToRename);
		if (result != BS_SDK_ERROR_NO)
		{
			HandleError(result);
			return;
		}
	}

	CTime time;
	m_ctlCreationTime.GetTime(time);
	SFileDateTime creationTime;
	CTimeToFileTime(time, &creationTime);

	m_ctlModificationTime.GetTime(time);
	SFileDateTime modificationTime;
	CTimeToFileTime(time, &modificationTime);

	m_ctlAccessTime.GetTime(time);
	SFileDateTime accessTime;
	CTimeToFileTime(time, &accessTime);

	if (IsDlgButtonChecked(IDC_GLOBALUSAGE) == BST_CHECKED) {
		SFileTimeEx myTime;
		::GetFileTimeEx(&myTime);

		myTime.CreationDateTime = creationTime;
		myTime.UseCreationDateTime = BS_TRUE;
		myTime.ModificationDateTime = modificationTime;
		myTime.UseModificationDateTime = BS_TRUE;
		myTime.LastAccessDateTime = accessTime;
		myTime.UseLastAccessDateTime = BS_TRUE;
		myTime.UseCustomTimes = BS_TRUE;
		::SetFileTimeEx(myTime);
	}

	// Set creation, modification and last access time.


	result = ::SetFileTimes(strDestinationPath, &creationTime, &modificationTime, &accessTime);
	if (result != BS_SDK_ERROR_NO)
	{
		HandleError(result);
		return;
	}

	// Set file attributes.
	m_pFileEntry->nAttrib &= ~(BS_FA_HIDDEN | BS_FA_ADVANCED_HIDDEN);
	if (IsDlgButtonChecked(IDC_HIDDEN) == BST_CHECKED)
		m_pFileEntry->nAttrib |= BS_FA_HIDDEN;
	if (IsDlgButtonChecked(IDC_ADVANCED_HIDDEN) == BST_CHECKED)
		m_pFileEntry->nAttrib |= BS_FA_ADVANCED_HIDDEN;
	result = ::SetFileAttr(strDestinationPath, m_pFileEntry->nAttrib);
	if (result != BS_SDK_ERROR_NO)
	{
		HandleError(result);
		return;
	}

	// Set file priority as the user param.
	m_pFileEntry->pUserParam = (void*)m_ctlPriority.GetCurSel();
	SetFileUserParam(strDestinationPath, m_pFileEntry->pUserParam);

	CDialog::OnOK();
}

void PropertiesDlg::HandleError(__int32 nError)
{
	if (nError != BS_SDK_ERROR_NO)
		GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, nError);
}
