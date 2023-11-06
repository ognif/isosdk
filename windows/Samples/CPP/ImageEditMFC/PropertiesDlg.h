#pragma once

#include "TreeNodes.h"
#include "afxcmn.h"

// KPropertiesDlg dialog

class KPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(KPropertiesDlg)

public:
	KPropertiesDlg(CWnd* pParent, ITreeNode *treeNode, UINT nIDTemplate = IDD_DIALOG_PROPERTIES);
	virtual ~KPropertiesDlg();

private:
	KPropertiesDlg(CWnd* pParent = NULL); // standard constructor

	//const Properties& m_props

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	ITreeNode *m_treeNode;

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_cListProp;
};
