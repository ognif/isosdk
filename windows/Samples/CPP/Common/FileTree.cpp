#include "stdafx.h"
#include "FileTree.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "KCreateFolderDlg.h"

IMPLEMENT_DYNAMIC(CFileList, CListCtrl)

BEGIN_MESSAGE_MAP(CFileList, CListCtrl)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDoubleClicked)
END_MESSAGE_MAP()


CFileList::CFileList() :
	m_strRootDirectory(PATHSEPSTRING),
	m_folderPickerDialog(IsoSDK::CFolderPickerDialog::Create(_T("Select folder to add")))
{
}

void CFileList::Init(CWinApp& theApp)
{
	m_ilIcons.Create(16, 16, ILC_MASK|ILC_COLOR32, 3, 0);
	m_nIconClosedFolder = m_ilIcons.Add(theApp.LoadIcon(IDI_CLOSED_FOLDER));
	m_nIconOpenFolder   = m_ilIcons.Add(theApp.LoadIcon(IDI_OPENED_FOLDER));

	SetImageList(&m_ilIcons, LVSIL_SMALL);

	InsertColumn(0, _T("Name"), LVCFMT_LEFT|LVCFMT_IMAGE, 200);
	InsertColumn(1, _T("Size"), LVCFMT_LEFT, 60);
	InsertColumn(2, _T("Modified Date"), LVCFMT_LEFT, 150);
	InsertColumn(3, _T("Origin"), LVCFMT_LEFT, 200);

	SetExtendedStyle(LVS_EX_FULLROWSELECT);

	SelectDirectory(m_strRootDirectory);
}

void CFileList::OnDestroy()
{
	DeleteAllItems();
}

CFileList::~CFileList()
{
	delete m_folderPickerDialog;
}

void CFileList::RefreshList()
{
	SelectDirectory(m_strCurDirectory);
}

void CFileList::SelectDirectory(const CString &strPath)
{
	DeleteAllItems();

	m_strCurDirectory = strPath;	

	HSESSION hSession;
	int32 res = ::OpenDiskSession(BS_CURRENT_DEVICE, 0, &hSession);
	HandleError(res);

	HDIR hDirectory;
	res = ::OpenDirectory(hSession, strPath, &hDirectory);
	HandleError(res);
    
	SFileEntry entry;

	if (m_strRootDirectory != strPath) 
		InsertItem(0, _T(".."), m_nIconOpenFolder);

	int32 nDirSize = 0;
	res = ::GetNumberOfFiles(hDirectory, &nDirSize);
	HandleError(res);

	for(int32 nIndex = 0; nIndex < nDirSize; ++nIndex) 
	{
		::ReadDirectory(hDirectory, nIndex, &entry);

		CString strName = entry.lpszFileName;
	
		CString strSize;		
		int64 size;
		
		if (0 != (BS_FA_DIRECTORY & entry.nAttrib)) {
			CString strDirPath = m_strCurDirectory;
			if (strDirPath != PATHSEPSTRING)
				strDirPath += PATHSEPSTRING;
			strDirPath += strName;
			size = GetDirectorySize(strDirPath);
		} else {
			size = entry.nFileSize;
		}

		if (size > 1024*1024) {
			size = size / (1024*1024);
			strSize.Format(_T("%d MB"), size);
		} else {			
			strSize.Format(_T("%d bytes"), size);
		}

		CString strDate;
		strDate.Format(_T("%02d.%02d.%04d %02d:%02d:%02d"), 
			entry.cDateTime.nDay,
			entry.cDateTime.nMonth,
			entry.cDateTime.nYear + 1900,
			entry.cDateTime.nHour,
			entry.cDateTime.nMinute,
			entry.cDateTime.nSecond);

		CString strOrigin = entry.lpszFileOrigin;
		int nImage = (entry.nAttrib & BS_FA_DIRECTORY) ? m_nIconClosedFolder : -1;

		int nItem = InsertItem(nIndex + 1, strName, nImage);
		SetItemText(nItem, 1, strSize);
		SetItemText(nItem, 2, strDate);
		SetItemText(nItem, 3, strOrigin);

		SFileEntry *userData = new SFileEntry;
		memcpy(userData, &entry, sizeof(SFileEntry));

		SetItemData(nItem, (DWORD_PTR)userData);
	}

	res = ::CloseDirectory(hDirectory);
	HandleError(res);

	res = ::CloseDiskSession(hSession);
	HandleError(res);
}

void CFileList::AddFile(int32 savePath)
{
	const int nMaxTitle = 0x10000;
	TCHAR	szTitle[nMaxTitle] = {0};

	CFileDialog fileDlg(TRUE, NULL, szTitle, 
		OFN_ALLOWMULTISELECT|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER);

	fileDlg.GetOFN().lpstrFile = szTitle;
	fileDlg.GetOFN().nMaxFile = nMaxTitle;

	if (fileDlg.DoModal() == IDOK)
	{
		CWaitCursor waitCursor;

		POSITION pos = fileDlg.GetStartPosition();

		for(; pos ;)
		{
			CString strTmpSourcePath = fileDlg.GetNextPathName(pos);

			CString strTmpDestPath = m_strCurDirectory;

			SFileToAdd file;
				file.lpszFileName = NULL;
				file.lpszSourceFilePath = strTmpSourcePath;
				file.lpszDestinationPath = strTmpDestPath;
				file.bVideoFile = BS_FALSE;
				file.nSavePath = savePath; // BS_WHOLE_PATH;

			int32 res = ::AddFile(file);
			HandleError(res);
		}

		SelectDirectory(m_strCurDirectory);
	}
}

void CFileList::AddFolder(int32 savePath)
{
	if (m_folderPickerDialog->DoModal() == IDOK)
	{
		CWaitCursor waitCursor;

		POSITION pos = m_folderPickerDialog->GetStartPosition();

		while (pos)
		{
			CString pathName = m_folderPickerDialog->GetNextPathName(pos);

			SDirToAdd dir;
			dir.lpszSourceDirPath = pathName;
			dir.lpszDestinationPath = m_strCurDirectory;
			dir.lpszFileSpecification = _T("*");
			dir.nFileAttributes = BS_FA_ALL;
			dir.nSavePath = savePath; //BS_PARENTDIR_ONLY;
			dir.bRecursive = BS_TRUE;

			int32 res = ::AddDir(dir);
			HandleError(res);
		}
	}

	SelectDirectory(m_strCurDirectory);
}

void CFileList::CreateFolder()
{
	CString strNewDirName;

	KCreateFolderDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		strNewDirName = dlg.GetFolderName();
	}
	else
	{
		return;
	}

	SDirToCreate dir;
	dir.lpszDestinationPath = m_strCurDirectory;
	dir.lpszDir = strNewDirName;

	int32 res = ::CreateDir(dir);
	HandleError(res);

	SelectDirectory(m_strCurDirectory);
}

void CFileList::DeleteItem()
{
	bool needUpdate = false;

	for (int i = GetItemCount(); i > 0; i--)
	{
		if (GetItemState(i-1, LVIS_SELECTED) == LVIS_SELECTED)
		{
			int32 res;
			SFileEntry *entry = (SFileEntry*)GetItemData(i-1);

			if (NULL != entry) 
			{
				if (0 != (BS_FA_DIRECTORY & entry->nAttrib))
				{
					CString strDestPath = entry->lpszFilePath;
					if (strDestPath.Right(1) != PATHSEPSTRING) 
						strDestPath += PATHSEPSTRING;

					strDestPath += entry->lpszFileName;

					SDirToRemove dir;
						dir.lpszDestinationPath = strDestPath;

					res = ::RemoveDir(dir);
					HandleError(res);
				}
				else
				{
					SFileToRemove file;
						file.lpszFile = entry->lpszFileName;
						file.lpszDestinationPath = entry->lpszFilePath;

					res = ::RemoveFile(file);
					HandleError(res);
				}

				needUpdate = true;
			}
		}		
	}

	if (needUpdate) 
		SelectDirectory(m_strCurDirectory);
}

void CFileList::ResetList()
{
	SelectDirectory(m_strRootDirectory);
}

__int64 CFileList::GetDirectorySize(const CString &strPath)
{
	int64 size = 0;	

	HSESSION hSession;
	int32 res = ::OpenDiskSession(BS_CURRENT_DEVICE, 0, &hSession);
	HandleError(res);

	HDIR hDirectory;
	res = ::OpenDirectory(hSession, strPath, &hDirectory);
	HandleError(res);
    
	SFileEntry entry;

	for(int32 nIndex = 0; ; ++nIndex)
	{
		if (BS_SDK_ERROR_NO != ::ReadDirectory(hDirectory, nIndex, &entry))
			break;

        if (0 != (BS_FA_DIRECTORY & entry.nAttrib)) 
		{
			CString strDir = entry.lpszFilePath;
			strDir += PATHSEPSTRING;
			strDir += entry.lpszFileName;

			size += GetDirectorySize(strDir);
		}
		else
		{
			size += entry.nFileSize;
		}
	}

	res = ::CloseDirectory(hDirectory);
	HandleError(res);

	res = ::CloseDiskSession(hSession);
	HandleError(res);

	return size;
}

void CFileList::DeleteAllItems()
{
	for (int i = GetItemCount(); i > 0; --i)
	{
		SFileEntry *userData = (SFileEntry*)GetItemData(i-1);
		if (NULL != userData) 
			delete userData;
	}

	CListCtrl::DeleteAllItems();
}

void CFileList::OnDoubleClicked(NMHDR* lpnmItem, LRESULT* pResult)
{
	LPNMITEMACTIVATE pItem = (LPNMITEMACTIVATE)lpnmItem;

	if (pItem->iItem == -1)
		return;

	if (_T("..") == GetItemText(pItem->iItem, 0))
	{
		int pos = m_strCurDirectory.ReverseFind(PATHSEPSTRING[0]);
		if (0 == pos)
			m_strCurDirectory = PATHSEPSTRING;
		else
			m_strCurDirectory = m_strCurDirectory.Left(pos);

		SelectDirectory(m_strCurDirectory);
	}
	else 
	{
		SFileEntry* data = (SFileEntry*)GetItemData(pItem->iItem);
		if ((NULL != data) && (0 != (BS_FA_DIRECTORY & data->nAttrib)))
		{
			if (PATHSEPSTRING != m_strCurDirectory)
				m_strCurDirectory += PATHSEPSTRING;

			CString strName = data->lpszFileName;
			m_strCurDirectory += strName;

			SelectDirectory(m_strCurDirectory);
		}
	}

	*pResult = 0;
}

void CFileList::RenameFile()
{
	/*
	FXint indx = getCurrentItem();
	if (indx == -1)
		return;

	SFileEntry *entry = (SFileEntry*)getItemData(indx);
	
	if (NULL == entry) 
		return;

	bool isFolder = (0 != (BS_FA_Directory & entry->nAttrib));

	FXString strFileName = SDK2FoxString(entry->lpszFileName);
	FXString strCaption = "Rename \"";
	strCaption += strFileName + "\" to:";

	FXIcon *dlgIcon;
	
	if (isFolder) 
	{
		dlgIcon = new FXGIFIcon(getApp(), minifolder);
	}
	else
	{
		dlgIcon = new FXGIFIcon(getApp(), minidoc);
	}

	FXInputDialog dlg(getApp(), "Fox Burner", strCaption, dlgIcon, INPUTDIALOG_STRING);

	if (dlg.execute() && !dlg.getText().empty())
	{
        KString strTmpName = Fox2SDKString(compose(dlg.getText(), DecCanonical));
		
		KString strTmpSrcPath = entry->lpszFilePath;
		if (strTmpSrcPath != _T(PATHSEPSTRING))
			strTmpSrcPath += _T(PATHSEPSTRING);		
		strTmpSrcPath += entry->lpszFileName;
		
		//KString strTmpDestPath = entry->lpszFilePath;
		//if (strTmpDestPath != _T(PATHSEPSTRING)) 
		//	strTmpDestPath += _T(PATHSEPSTRING);		
		//strTmpDestPath += strTmpName;
		KString& strTmpDestPath = strTmpName;

		if (isFolder)
		{
			SDirToRename dir;
				dir.lpszSourcePath = strTmpSrcPath;
				dir.lpszDestinationPath = strTmpDestPath;

			int32 res = ::RenameDir(dir);
			handleError(res);
		}
		else
		{
			SFileToRename file;
				file.lpszSourcePath = strTmpSrcPath;
				file.lpszDestinationPath = strTmpDestPath;

			int32 res = ::RenameFile(file);
			handleError(res);
		}

		SelectDirectory(m_strCurDirectory);
	}
	*/
}

void CFileList::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
		GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}

void CFileList::SetRootDirectory(const CString& strPath)
{
	m_strRootDirectory = strPath;
	SelectDirectory(m_strRootDirectory);
}

int64 CFileList::GetRootDirectorySize()
{
    return GetDirectorySize(m_strRootDirectory);
}
