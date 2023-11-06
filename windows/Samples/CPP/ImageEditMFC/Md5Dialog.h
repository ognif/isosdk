#pragma once

#include "md5\KMD5Counter.h"
#include "md5\KMD5FileSource.h"

// KMd5Dialog dialog

class KMd5Dialog : public CDialog
{
	DECLARE_DYNAMIC(KMd5Dialog)

public:
	KMd5Dialog(CWnd* pParent, CString strSourceName);   // standard constructor
	virtual ~KMd5Dialog();

private :		
	KMD5FileSource*	m_pcMD5FileSource;
	KMD5Counter		m_cMD5Counter;
	CStringA		m_strMD5;
	CString			m_strFileName;

	void GenerateMD5();

	KMd5Dialog(CWnd* pParent = NULL);

public :
	CStringA GetMD5String();



// Dialog Data
	enum { IDD = IDD_DIALOG_MD5 };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR);
};
