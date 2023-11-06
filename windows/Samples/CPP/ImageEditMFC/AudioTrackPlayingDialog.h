#pragma once


// KPlayTrackDialog dialog

class KPlayTrackDialog : public CDialog
{
	DECLARE_DYNAMIC(KPlayTrackDialog)

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
	KPlayTrackDialog(CWnd* pParent = NULL);   // standard constructor
	KPlayTrackDialog(int16 nTrackNumber, CWnd* pParent = NULL);
	virtual ~KPlayTrackDialog();

protected:

	static void OnJobDoneEvent(KPlayTrackDialog*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesPlayed, 
		double dImageSize, KPlayTrackDialog*);
	static void OnBurnDoneEvent(const TCHAR *pcError, KPlayTrackDialog*);
	
	void RestoreEvents();

	void SetProgress(int nProgress, double nBytesWritten, double nTrackSize);
	void OnJobDone();
	
	LRESULT OnOnBurnDoneNotify(WPARAM, LPARAM);

	void Done();
	void HandleError(int32 errCode);

protected:

	bool			m_bReady;
	int16			m_nTrackNumber;
	State			m_enState;
	CTimeSpan		m_timeStart;

// Dialog Data
	enum { IDD = IDD_DIALOG_PLAYTRACK };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR);
};
