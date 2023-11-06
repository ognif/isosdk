#include "StdAfx.h"
#include "FolderPickerDialog.h"
#include "LegacyFolderPickerDialog.h"
#if _MSC_VER >= 1600
#include "VistaFolderPickerDialog.h"
#endif

namespace IsoSDK
{

CFolderPickerDialog *CFolderPickerDialog::Create(LPCTSTR title)
{
#if _MSC_VER >= 1600
	if (IsVistaOrNewer())
		return new CVistaFolderPickerDialog(title);
	else
		return new CLegacyFolderPickerDialog(title);
#else
	return new CLegacyFolderPickerDialog(title);
#endif
}

bool CFolderPickerDialog::IsVistaOrNewer()
{
	OSVERSIONINFO versionInfo = { sizeof(OSVERSIONINFO) };
	GetVersionEx(&versionInfo);
	return versionInfo.dwMajorVersion >= 6;
}

} // namespace IsoSDK
