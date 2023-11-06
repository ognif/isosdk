#ifndef ABOUT_DLG_MFC_H
#define ABOUT_DLG_MFC_H

#include "resource.h"

class CAboutDlg : public CDialog
{
public:

	enum { IDD = IDD_ABOUTBOX };

	CAboutDlg(CWnd* pParent)
		:CDialog(CAboutDlg::IDD, pParent)
	{
	}
};


#endif