#pragma once

#include <vector>

// KAudioGrabbingDialog dialog

class KAudioGrabbingDialog : public CDialog
{
	DECLARE_DYNAMIC(KAudioGrabbingDialog)

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
	KAudioGrabbingDialog(CWnd* pParent = NULL);   // standard constructor
	KAudioGrabbingDialog(std::vector<int32> vTracks, CWnd* pParent = NULL);
	virtual ~KAudioGrabbingDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_AUDIO_GRABBING };

protected:

	static void OnJobDoneEvent(KAudioGrabbingDialog*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
		double dBytesWritten, double dImageSize, KAudioGrabbingDialog *pDlg);
	static void OnBurnDoneEvent(const TCHAR *pcError, KAudioGrabbingDialog*);
	
	void RestoreEvents();

	void SetProgress(int nProgress, double nBytesWritten, double nTrackSize);
	void OnJobDone();
	
	LRESULT OnOnBurnDoneNotify(WPARAM, LPARAM);
	
	void HandleError(int32 errCode);
	void Done();

protected:

	bool				m_bReady;
	std::vector<int>	m_vTracks;
	State				m_enState;
	int					m_nCurrentTrack;
	CTimeSpan			m_timeStart;


	CComboBox			m_cmbEncoder;
	CComboBox			m_cmbBitrateType;
	CComboBox			m_cmbBitrate;
	CComboBox			m_cmbBitrateMin;
	CComboBox			m_cmbBitrateMax;
	CComboBox			m_cmbBitrateQuality;
	CComboBox			m_cmbTagsChoice;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR);
	
	afx_msg void OnEncoderTypeChanged();
	afx_msg void OnBitrateTypeBox();
	afx_msg void OnMinBitrateBox();
	afx_msg void OnMaxBitrateBox();
};
