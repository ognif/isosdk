#pragma once

#include "IsoSDKDefinitions.h"
#include <vector>

struct CFileAudioProperty
{
	CFileAudioProperty();
	CFileAudioProperty(const CFileAudioProperty &prp);
	CFileAudioProperty(const CString &filePath);

	void SetTrackNumber(int nTrack);
	void UpdateData();

	SFileAudioProperty data;

	CString strSourceFilePath;
	CString strTitle;
	CString strPerformer;
	CString strSongWriter;
	CString strComposer;
	CString strArranger;
	CString strMessage;	
	CString strMcnIsrc;
	int		nPlayTime;
	std::vector<int32> vIndexes;
};

// CCDTextDlg dialog

class CCDTextTab : public CDialog
{
	DECLARE_DYNAMIC(CCDTextTab)

public:
	CCDTextTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_CDTEXT };

	void SetFileProperty(const CFileAudioProperty& rInfo);
	void GetFileProperty(CFileAudioProperty* pInfo);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CString m_strArranger;
	CString m_strComposer;
	CString m_strSongWriter;
	CString m_strPerformer;
	CString m_strMessage;
	CString m_strTitle;
	CString m_strMcnIsrc;
	int		m_nPause;
	int		m_nPauseInFrames;

	DECLARE_MESSAGE_MAP()
};

class CIndexesTab : public CDialog
{
	DECLARE_DYNAMIC(CIndexesTab)

public:
	CIndexesTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_INDEXES };

	void SetFileProperty(const CFileAudioProperty& rInfo);
	void GetFileProperty(CFileAudioProperty* pInfo);

protected:

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnBnClickedAddIndex();
	afx_msg void OnBnClickedDeleteIndex();

	int m_nPlayTime;
	int m_nMin;
	int m_nSec;
	int m_nFrame;
	CListBox	m_lstIndexes;

	DECLARE_MESSAGE_MAP()
};

class CPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropertiesDlg)

public:
	CPropertiesDlg(bool disc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_PROPERTIES };

	void SetFileProperty(CFileAudioProperty *pInfo);

protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedReset();

	bool m_bIsDiscText;

	CFileAudioProperty* m_pFileInfo;

	CCDTextTab	m_dlgCDText;
	CIndexesTab	m_dlgIndexes;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
