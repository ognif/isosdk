#pragma once


// KSaveDiscDialog dialog

class KSaveDiscDialog : public CDialog
{
	DECLARE_DYNAMIC(KSaveDiscDialog)

protected:

	enum State
	{
		ST_NONE,
		ST_PROCESSING,
		ST_ABORTED,
		ST_CANCELLED,
		ST_DONE,
	};

public:
	KSaveDiscDialog(CWnd* pParent = NULL);   // standard constructor
	KSaveDiscDialog(CWnd* pParent, const CString& strFilePath, int16 nFileFormat);
	virtual ~KSaveDiscDialog();
	

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVE_DISC };

protected:

	static void OnJobDoneEvent(KSaveDiscDialog*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, 
		float fCache, double dBytesWritten, double dImageSize, KSaveDiscDialog*);
	static void OnBurnDoneEvent(const TCHAR *pcError, KSaveDiscDialog*);
	
	void RestoreEvents();

	void SetProgress(int nProgress, double dBytesWritten, double dTrackSize, int nErrorsCount);
	void OnJobDone();
	
	LRESULT OnOnBurnDoneNotify(WPARAM, LPARAM);
	
	void HandleError(int32 errCode);

	void Done();

protected:

	bool  m_bReady;
	CString m_strFilePath;
	int16 m_nFileFormat;
	State m_enState;
	CTimeSpan m_timeStart;
	
	

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR);
};
