// ChangeRegionDlg.h : header file
//

#ifndef CHANGEREGIONDLG_H
#define CHANGEREGIONDLG_H

#if _MSC_VER > 1000
#	pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChangeRegionDlg dialog

class CChangeRegionDlg : public CDialog
{
	// Construction
public:
	CChangeRegionDlg(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_CHANGEREGION };

	virtual void OnOK();

	// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	void HandleError(int32);

	int m_nRegion;

	DECLARE_MESSAGE_MAP()
};

#endif // CHANGEREGIONDLG_H
