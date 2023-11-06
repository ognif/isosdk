#include "stdafx.h"
#include "LegacyFolderPickerDialog.h"

namespace IsoSDK
{

// CLegacyFolderPickerDialog

CLegacyFolderPickerDialog::CLegacyFolderPickerDialog(LPCTSTR title) :
	m_title(title)
{
}

INT_PTR CLegacyFolderPickerDialog::DoModal()
{
	BROWSEINFO info = { 0 };
	info.lpszTitle = m_title;
	info.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	info.lpfn = BrowseCallbackProc;
	info.lParam = (LPARAM)(LPCTSTR)m_selectedPath;

	LPITEMIDLIST selectedFolder = SHBrowseForFolder(&info);

	if (selectedFolder != NULL) 
	{
		TCHAR *selectedPath = m_selectedPath.GetBuffer(MAX_PATH);
		SHGetPathFromIDList(selectedFolder, selectedPath);
		m_selectedPath.ReleaseBuffer();
		CoTaskMemFree(selectedFolder);

		return IDOK;
	}

	return IDCANCEL;
}

int CALLBACK CLegacyFolderPickerDialog::BrowseCallbackProc(HWND hwnd,UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	return 0;
}

POSITION CLegacyFolderPickerDialog::GetStartPosition() const
{
	return (POSITION)(LPCTSTR)m_selectedPath;;
}

CString CLegacyFolderPickerDialog::GetNextPathName(POSITION &pos) const
{
	pos = NULL;
	return m_selectedPath;
}

} // namespace IsoSDK
