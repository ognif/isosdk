#ifndef SAMPLE_BURN_DLG_MFC_H
#define SAMPLE_BURN_DLG_MFC_H

#include "resource.h"
#include "IsoSDKBurningLib.h"

class CSampleBurnDlg : public CDialog
{
public:

	enum { IDD = IDD_SAMPLE_BURN_DIALOG };

	CSampleBurnDlg(CWnd* pParent);
	~CSampleBurnDlg();

	/*
	enum {
		ID_SAVELOG = FXDialogBox::ID_LAST,
		ID_ADDLOGLINE,
		ID_BURNFILE,
		ID_SETPROGRESS,
		ID_JOBDONE,
		ID_TOTALTIME,
		ID_LAST
	};
	*/

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);

	// Generated message map functions
	virtual BOOL OnInitDialog();

	enum State
	{
		ST_NONE,
		ST_BURN,
		ST_FINALIZE,
		ST_VERIFY
	};

	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnCancel();
	afx_msg void OnSaveLog();
	afx_msg void OnTimer(UINT_PTR);


protected:

	static void OnFinalizeEvent(CSampleBurnDlg*);
	static void OnBurnDoneEvent(const TCHAR* pcError, CSampleBurnDlg*);
	static void OnJobDoneEvent(CSampleBurnDlg*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesWritten, double dImageSize, CSampleBurnDlg *pDlg);
	static void OnInfoTextEvent(const TCHAR *pcInfoText, int32 nLevel, CSampleBurnDlg*);
	static void OnStartVerifyEvent(CSampleBurnDlg*);
	static void OnVerifyFileEvent(const TCHAR *pcFileName, CSampleBurnDlg*);
	static void OnVerifyErrorEvent(const TCHAR *pcFileName, const TCHAR *pcError, CSampleBurnDlg*);
	static void OnVerifyDoneEvent(int32 nNumErrors, CSampleBurnDlg* pUserData);
	static void OnBurnFileEvent(const TCHAR* pcFileName, CSampleBurnDlg* pUserData);

	void RestoreEvents();

	void AddLogLine(const CString& strLogLine);
	void SetProgress(int progress, int buffer);
	void OnJobDone();
	void SetCurrentFile(const CString& strFileName);

	void UpdateTitle(int progress);

	void HandleError(int32 errCode);

protected:
	CListBox		m_lstLog;
	CProgressCtrl   m_pbBuffer;
	CProgressCtrl   m_pbTotal;
	CStatic			m_lblCurrentFile;
	CStatic			m_lblElapsed;
	CStatic			m_lblSpeed;

	State	m_enState;

	CString   m_strLabel;
	CString   m_strDevice;
	CTime	  m_nStartTime;
};

#endif
