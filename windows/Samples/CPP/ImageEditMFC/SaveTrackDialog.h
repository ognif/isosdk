#pragma once


// KSaveTrackDialog dialog

class KSaveTrackDialog : public CDialog
{
	DECLARE_DYNAMIC(KSaveTrackDialog)

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
	KSaveTrackDialog(CWnd* pParent = NULL);   // standard constructor

	KSaveTrackDialog(CWnd* pParent, int16 nTrackNumber, 
		const CString& strFilePath, unsigned int nFileFormat);

	virtual ~KSaveTrackDialog();

protected:

	static void OnJobDoneEvent(KSaveTrackDialog*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
		double dBytesWritten, double dImageSize, KSaveTrackDialog*);
	static void OnBurnDoneEvent(const TCHAR *pcError, KSaveTrackDialog*);
	
	void RestoreEvents();

	void SetProgress(int nProgress, double nBytesWritten, double nTrackSize);
	void OnJobDone();
	
	LRESULT OnOnBurnDoneNotify(WPARAM, LPARAM);
	
	void HandleError(int32 errCode);
	void Done();

protected:

	bool			m_bReady;
	int16			m_nTrackNumber;
	const CString	m_strFilePath;
	unsigned int	m_nFileFormat;
	State			m_enState;
	CTimeSpan		m_timeStart;

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVETRACK };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR);
};
