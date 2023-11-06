// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "PropertiesDlg.h"


// KPropertiesDlg dialog

IMPLEMENT_DYNAMIC(KPropertiesDlg, CDialog)
KPropertiesDlg::KPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_PROPERTIES, pParent)
{
}

KPropertiesDlg::KPropertiesDlg(CWnd* pParent, ITreeNode *treeNode, UINT nIDTemplate)
	: CDialog(nIDTemplate, pParent),
	m_treeNode(treeNode)
{
}

KPropertiesDlg::~KPropertiesDlg()
{
}

void KPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROPERTIES, m_cListProp);
}


BEGIN_MESSAGE_MAP(KPropertiesDlg, CDialog)
END_MESSAGE_MAP()


// KPropertiesDlg message handlers

BOOL KPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	m_cListProp.InsertColumn(0, _T("Parameter"), LVCFMT_LEFT, 130, 0);
	m_cListProp.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 130, 0);

	Properties props = m_treeNode->getProperties();
	Properties::const_iterator iter = props.begin();
	
	for (int i = 0; iter != props.end(); iter++, i++)
	{
		m_cListProp.InsertItem(i, iter->first);
		m_cListProp.SetItemText(i, 1, iter->second);
	}

	return TRUE;
}