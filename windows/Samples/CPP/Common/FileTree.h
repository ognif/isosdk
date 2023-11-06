#ifndef FILETREE_H
#define FILETREE_H

#include "IsoSDKBurningLib.h"
#include "FolderPickerDialog.h"

class CFileList : public CListCtrl
{
public:
	CFileList();
	~CFileList();

	void Init(CWinApp& theApp);
	void AddFile(int32 savePath = BS_DONT_SAVE_PATH);
	void AddFolder(int32 savePath = BS_DONT_SAVE_PATH);
	void CreateFolder();
	void DeleteItem();
	void ResetList();
	void RefreshList();
	void RenameFile();
	void SetRootDirectory(const CString& strPath);

	__int64 GetRootDirectorySize();

	void DeleteAllItems();

protected:

	afx_msg void OnDestroy();
	afx_msg void OnDoubleClicked(NMHDR*, LRESULT*);

	__int64 GetDirectorySize(const CString &strPath);
	void SelectDirectory(const CString &strPath);	
	void HandleError(int errCode);

private:
	CImageList m_ilIcons;

	int m_nIconClosedFolder;
	int m_nIconOpenFolder;

	CString m_strRootDirectory;
	CString m_strCurDirectory;

	IsoSDK::CFolderPickerDialog *m_folderPickerDialog;

	DECLARE_DYNAMIC(CFileList)
	DECLARE_MESSAGE_MAP()
};

#endif
