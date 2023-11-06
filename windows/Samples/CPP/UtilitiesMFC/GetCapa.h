#ifndef GETCAPA_H
#define GETCAPA_H

#pragma once
#include "afxwin.h"
#include <map>

// CGetCapa-Dialogfeld

class CCapabilitiesDlg : public CDialog
{
public:
	CCapabilitiesDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CCapabilitiesDlg();

	enum { IDD = IDD_CAPABILITIES };

	void FillInfos();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	void HandleError(int32 errCode);

	typedef std::map<int64, int> CapsMap;

	CComboBox	m_ctrlDrives;
	CapsMap		m_mCapsMap;
	
	DECLARE_MESSAGE_MAP()
};

#endif