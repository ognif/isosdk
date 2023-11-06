#include "stdafx.h"
#include "resource.h"
#include "FilePropertiesDlg.h"

KFilePropertiesDlg::KFilePropertiesDlg(CWnd* pParent, FileNode *fileNode) :
	KPropertiesDlg(pParent, fileNode, IDD_DIALOG_FILE_PROPERTIES)
{
}

void KFilePropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	KPropertiesDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALLOCATION_TABLE, m_ctlAllocationTable);
}

BOOL KFilePropertiesDlg::OnInitDialog()
{
	KPropertiesDlg::OnInitDialog();

	m_ctlAllocationTable.InsertColumn(0, _T("Extent Location"), LVCFMT_LEFT, 130, 0);
	m_ctlAllocationTable.InsertColumn(1, _T("Extent Length (bytes)"), LVCFMT_LEFT, 130, 0);

	const SFileAllocationTable *allocTable = ((FileNode*)m_treeNode)->getAllocationTable();

	CString str;
	for (int i = 0; i < allocTable->NumExtents; i++)
	{
		str.Format(_T("%d"), allocTable->Extents[i].Location);
		m_ctlAllocationTable.InsertItem(i, str);

		str.Format(_T("%d"), allocTable->Extents[i].Length);
		m_ctlAllocationTable.SetItemText(i, 1, str);
	}

	return TRUE;
}
