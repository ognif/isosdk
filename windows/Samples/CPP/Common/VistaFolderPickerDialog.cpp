#include "StdAfx.h"
#include "VistaFolderPickerDialog.h"

namespace IsoSDK
{

CVistaFolderPickerDialog::CVistaFolderPickerDialog(LPCTSTR title) :
	m_sysFolderPickerDialog(NULL, OFN_ALLOWMULTISELECT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST),
	m_title(title)
{
	m_sysFolderPickerDialog.GetOFN().lpstrTitle = m_title;
}

INT_PTR CVistaFolderPickerDialog::DoModal()
{
	return m_sysFolderPickerDialog.DoModal();
}

POSITION CVistaFolderPickerDialog::GetStartPosition() const
{
	return m_sysFolderPickerDialog.GetStartPosition();
}

CString CVistaFolderPickerDialog::GetNextPathName(POSITION &pos) const
{
	return m_sysFolderPickerDialog.GetNextPathName(pos);
}

} // namespace IsoSDK

