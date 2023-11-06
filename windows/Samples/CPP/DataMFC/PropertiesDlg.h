#pragma once

#include <IsoSDKExport.h>
#include "afxdtctl.h"

// PropertiesDlg dialog

class PropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(PropertiesDlg)

public:
	PropertiesDlg(SFileEntry *pFileEntry);   // standard constructor
	virtual ~PropertiesDlg();

// Dialog Data
	enum { IDD = IDD_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

private:
	void HandleError(__int32 nError);
	void InitializePriorityComboBox();

	SFileEntry	*m_pFileEntry;
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CDateTimeCtrl m_ctlCreationTime;
	CDateTimeCtrl m_ctlModificationTime;
	CDateTimeCtrl m_ctlAccessTime;
	CString m_strFileName;
	CComboBox m_ctlPriority;
};
