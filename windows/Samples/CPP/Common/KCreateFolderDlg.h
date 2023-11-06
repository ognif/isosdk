#ifndef KCREATE_FOLDER_DLG_H
#define KCREATE_FOLDER_DLG_H

#include "resource.h"
// KCreateFolderDlg dialog

class KCreateFolderDlg : public CDialog
{
	DECLARE_DYNAMIC(KCreateFolderDlg)

public:
	KCreateFolderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~KCreateFolderDlg();

	CString GetFolderName();

// Dialog Data
	enum { IDD = IDD_CREATE_FOLDER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CString m_strFolderName;
public:
	afx_msg void OnBnClickedOk();
};

#endif