#pragma once

#include "PropertiesDlg.h"

class KFilePropertiesDlg :
	public KPropertiesDlg
{
public:
	KFilePropertiesDlg(CWnd* pParent, FileNode *fileNode);

protected:
	BOOL OnInitDialog();
	void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	CListCtrl m_ctlAllocationTable;
};

