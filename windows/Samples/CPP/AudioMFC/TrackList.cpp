#include "stdafx.h"
#include "TrackList.h"
#include "CDTextDlg.h"
#include "IsoSDKBurningLib.h"
#include <sys/stat.h>
#include <cmath>


BEGIN_MESSAGE_MAP(CTrackList, CListCtrl)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

CTrackList::CTrackList()
	:m_strRootDirectory(PATHSEPSTRING)
{
}

void CTrackList::Init(CWinApp& theApp)
{
	InsertColumn(0, _T("File name"), LVCFMT_LEFT|LVCFMT_IMAGE, 300);
	InsertColumn(1, _T("Play time"), LVCFMT_LEFT, 100);

	SetExtendedStyle(LVS_EX_FULLROWSELECT);
}

int CTrackList::AddFile()
{
	const TCHAR* patterns = _T("All Supported (*.wav,*.wv,*.ape,*.opus,*.mp3,*.ogg,*.wma,*.vqf,*.aac,*.m4a,*.flac,*.aiff)|*.wav;*.wv;*.ape;*.opus;*.mp3;*.ogg;*.wma;*.vqf;*.aac;*.m4a;*.flac;*.aiff||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER, 
		patterns);

	TCHAR chNameBuffer[256*_MAX_PATH + 1];
	chNameBuffer[0] = 0;

	dlg.GetOFN().lpstrFile = chNameBuffer;
	dlg.GetOFN().nMaxFile  = sizeof(chNameBuffer)/sizeof(TCHAR);

	int total_time = 0;

	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();

		for(; pos ;)
		{
			CString strPath = dlg.GetNextPathName(pos);

			SFileToAdd fta;
			fta.lpszSourceFilePath = strPath;
			fta.lpszDestinationPath = m_strRootDirectory;
			fta.nSavePath = BS_DONT_SAVE_PATH;
			fta.bVideoFile = BS_FALSE;
			
			int32 res = ::AddFile(fta);
			HandleError(res);

			if (BS_SDK_ERROR_NO == res) 
			{
				double fSec = 0.0;
				::GetPrecisePlayTime(strPath, &fSec);

				int32 sec = int32(ceil(fSec));

				CString strTime;
				strTime.Format(_T("%02d:%02d:%02d"), sec/3600, (sec%3600)/60, sec%60);

				CString strName = strPath.Mid(strPath.ReverseFind(_T('\\')) + 1);
				CFileAudioProperty *pinfo = new CFileAudioProperty(strName);
				pinfo->nPlayTime = sec;

				int nItem = InsertItem(GetItemCount(), strPath);
				SetItemText(nItem, 1, strTime);
				SetItemData(nItem, (DWORD_PTR)pinfo);

				total_time += sec;
			}
		}
	}

	return total_time;
}

int CTrackList::DeleteSelectedItems()
{
	int total_time = 0;

	for (int nItem = GetItemCount()-1; nItem >= 0 ; --nItem)
	{
		if (GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
		{
			CString strFilePath = GetItemText(nItem, 0);

			CString strTmpPath;
			strTmpPath.Format(_T("%02d"), nItem+1);

			SFileToRemove file;
			file.lpszFile = strTmpPath;
			file.lpszDestinationPath = m_strRootDirectory;

			int32 res = ::RemoveFile(file);
			HandleError(res);

			if (BS_SDK_ERROR_NO == res) 
			{
				CFileAudioProperty *pinfo = (CFileAudioProperty*)GetItemData(nItem);
				int32 sec = pinfo->nPlayTime;

				if (pinfo) delete pinfo;

				DeleteItem(nItem);

				total_time += sec;
			}
		}
	}

	return total_time;
}

void CTrackList::ResetList()
{
	const int nItemCount = GetItemCount();

	for (int i = 0; i < nItemCount; ++i) 
	{
		CFileAudioProperty *pinfo = (CFileAudioProperty*)GetItemData(i);
		if (pinfo) delete pinfo;
	}

	DeleteAllItems();
}

void CTrackList::TrackCDText()
{
	POSITION pos = GetFirstSelectedItemPosition();

	if (pos)
	{
		int nItem = GetNextSelectedItem(pos);

		CFileAudioProperty *pinf = (CFileAudioProperty*)GetItemData(nItem);
		if (pinf)
		{
			CFileAudioProperty prp = *pinf;
			CPropertiesDlg dlg(false);

			prp.SetTrackNumber(nItem + 1);
			dlg.SetFileProperty(&prp);

			if (dlg.DoModal() == IDOK) 
			{
				int32 res = ::SetAudioFileProperty(prp.data);
				HandleError(res);
				if (res == BS_SDK_ERROR_NO) 
				{
					*pinf = prp;
				}
			}
		}
	}
}

void CTrackList::DiskCDText()
{
	CPropertiesDlg dlg(true);
	CFileAudioProperty prp = m_cdText;

	prp.strSourceFilePath = m_strRootDirectory;
	dlg.SetFileProperty(&prp);

	if (dlg.DoModal() == IDOK) 
	{
		int32 res = ::SetAudioFileProperty(prp.data);
		HandleError(res);
		if (res == BS_SDK_ERROR_NO) 
		{
			m_cdText = prp;
		}
	}
}

void CTrackList::Play()
{
	POSITION pos = GetFirstSelectedItemPosition();

	if (pos)
	{
		int nItem = GetNextSelectedItem(pos);

		CString strPath = GetItemText(nItem, 0);
		int32 res = ::PlayAudioFile(strPath);
		HandleError(res);
	}
}

double CTrackList::GetAudioFileSizeEx()
{
	double fSize = 0.0;
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos)
	{
		int nItem = GetNextSelectedItem(pos);

		CString strPath = GetItemText(nItem, 0);
		int32 res = ::GetAudioFileSize(strPath, &fSize);
		HandleError(res);

		return fSize;
	}

	return fSize;
}

void CTrackList::OnDestroy()
{
	ResetList();
}

CTrackList::~CTrackList()
{
}

void CTrackList::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
		GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}

void CTrackList::SetRootDirectory(const CString& path)
{
	m_strRootDirectory = path;
}