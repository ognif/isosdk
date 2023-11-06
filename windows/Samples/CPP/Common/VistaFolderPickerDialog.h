#pragma once

#include "FolderPickerDialog.h"

namespace IsoSDK
{

class CVistaFolderPickerDialog : public CFolderPickerDialog
{
public:
	CVistaFolderPickerDialog(LPCTSTR title);

	INT_PTR DoModal();
	POSITION GetStartPosition() const;
	CString GetNextPathName(POSITION &pos) const;

private:
	CString m_title;
	::CFolderPickerDialog m_sysFolderPickerDialog;
};

} // namespace IsoSDK
