#pragma once

namespace IsoSDK
{

class CFolderPickerDialog
{
public:
	virtual ~CFolderPickerDialog() {};

	virtual INT_PTR DoModal() = 0;
	virtual POSITION GetStartPosition() const = 0;
	virtual CString GetNextPathName(POSITION &pos) const = 0;

	static CFolderPickerDialog *Create(LPCTSTR title);

protected:
	CFolderPickerDialog() {};

private:
	static bool IsVistaOrNewer();
};

} // namespace IsoSDK
