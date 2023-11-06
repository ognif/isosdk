#pragma once

#include "FolderPickerDialog.h"

namespace IsoSDK
{

// CLegacyFolderPickerDialog

class CLegacyFolderPickerDialog : public CFolderPickerDialog
{
public:
	CLegacyFolderPickerDialog(LPCTSTR title);

	INT_PTR DoModal();
	POSITION GetStartPosition() const;
	CString GetNextPathName(POSITION &pos) const;

private:
	CString m_title;
	CString m_selectedPath;

	static int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg, LPARAM lParam, LPARAM lpData);
};

} // namespace IsoSDK
