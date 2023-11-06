#pragma once

#include "Sector2Text.h"

// KSectorViewDialog dialog

class KSectorViewDialog : public CDialog
{
	DECLARE_DYNAMIC(KSectorViewDialog)

public:
	KSectorViewDialog(CWnd* pParent = NULL, int32 nLBA = 0);
	virtual ~KSectorViewDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_VIEWSECTOR };

	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnDeltaposSpinSector(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnEnChangeEditSector();
	afx_msg void OnCheckRaw();
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:
	
	void OnLba();
	std::vector<KString> ReadSector(BOOL bReadRaw, UINT nLBA);

private:
	BOOL m_bRaw;
	UINT m_unCurrentSector;
	CRichEditCtrl	m_cRichEdit;
};
