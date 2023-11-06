#ifndef _AUDIO_GRABBING_DIALOG_H_
#define _AUDIO_GRABBING_DIALOG_H_

#include "fx.h"
#include <vector>

class KAudioGrabbingDialog : public FXDialogBox
{
	FXDECLARE(KAudioGrabbingDialog)

public:

	enum {
		ID_JOBDONE = FXDialogBox::ID_LAST,
		ID_USERACTION,
		ID_BURNDONE,
		ID_SETPROGRESS,
		ID_TOTALTIME,
		ID_ENCODERBOX,
		ID_BITRATE_TYPE_BOX,
		ID_BITRATE_BOX,
		ID_BITRATE_MIN_BOX,
		ID_BITRATE_MAX_BOX,
		ID_BITRATE_QUALITY,
		ID_BROWSE,
		ID_LAST
	};

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
	KAudioGrabbingDialog();
	KAudioGrabbingDialog(FXWindow* owner, std::vector<int32> vTracks);
	~KAudioGrabbingDialog();

	long onUserAction(FXObject* sender, FXSelector key, void* data);
	long onBrowse(FXObject* sender, FXSelector key, void* data);
	long onChoreJobDone(FXObject* sender, FXSelector key, void* data);
	long onChoreBurnDone(FXObject* sender, FXSelector key, void* data);
	long onSetProgress(FXObject* sender, FXSelector key, void* data);
	long onTimer(FXObject* sender, FXSelector key, void* data);
	long onEncoderBox(FXObject* sender, FXSelector key, void* data);
	long onBitrateTypeBox(FXObject* sender, FXSelector key, void* data);
	long onMinBitrateBox(FXObject* sender, FXSelector key, void* data);
	long onMaxBitrateBox(FXObject* sender, FXSelector key, void* data);

protected:

	void StartJob();

	static void OnBurnDoneEvent(const TCHAR *pcError, KAudioGrabbingDialog*);
	static void OnJobDoneEvent(KAudioGrabbingDialog*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, 
		float fCache, double dBytesWritten, double dImageSize, 
		KAudioGrabbingDialog *pDlg);

	void OnCreate();
	void RestoreEvents();

	void SetProgress(int nProgress, double nBytesWritten, double nTrackSize);
	void OnJobDone();
	void OnBurnDone(const TCHAR *pcError);
	
	void handleError(int32 errCode);

protected:

	bool			m_bReady;
	int				m_nCurrentTrack;

	FXProgressBar*  m_barProgress;
	FXLabel*		m_lblTotalSize;
	FXLabel*		m_lblBytesWritten;
	FXLabel*		m_lblElapsed;
	FXLabel*		m_lblTrack;
	FXButton*		m_btnAbort;
	FXButton*		m_btnBrowse;
	FXComboBox*		m_cmbEncoder;
	FXComboBox*		m_cmbBitrateType;
	FXComboBox*		m_cmbBitrate;
	FXComboBox*		m_cmbBitrateMin;
	FXComboBox*		m_cmbBitrateMax;
	FXComboBox*		m_cmbTagChoice;
	FXComboBox*		m_cmbQuality;
	FXTextField*	m_txtSavePath;

	//Numbers of tracks to grab them 
	std::vector<int32> m_vTracks;

	void Done();

	State	m_enState;

	FXMessageChannel guisignal;

	FXString   m_strCallbackError;
	FXString   m_strCurrentFile;
	FXString   m_strLabel;
	FXString   m_strDevice;
	FXTime	   m_nStartTime;


	bool	m_bTrackSizeWasSet;

	struct ProgressInfo
	{
		int nProgress;
		double fBytesWritten;
		double fTrackSize;
	} m_cProgressInfo;
};

#endif //  _AUDIO_GRABBING_DIALOG_H_


