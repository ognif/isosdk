#pragma once
#ifndef _CD_TEXT_READ_DIALOG_H_
#define _CD_TEXT_READ_DIALOG_H_

#include "Resource.h"

class KCDTextReadDialog : public CDialog
{
	DECLARE_DYNAMIC(KCDTextReadDialog)

public:
	KCDTextReadDialog(CWnd* pParent = NULL);   // standard constructor
	KCDTextReadDialog(CWnd* pParent, 
		const TCHAR* strArranger,
		const TCHAR* strComposer,
		const TCHAR* strSongWriter,
		const TCHAR* strPerformer,
		const TCHAR* strTitle,
		const TCHAR* strMessage
		);
	virtual ~KCDTextReadDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CDTEXT };

private:
		CString m_strArranger;
		CString m_strComposer;
		CString m_strSongWriter;
		CString m_strPerformer;
		CString m_strTitle;
		CString m_strMessage;
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()	
public:	
	//afx_msg void OnBnClickedOk();	
};


#endif // _CD_TEXT_READ_DIALOG_H_

