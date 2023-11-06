#ifndef _AUDIO_TRACK_PLAYING_DIALOG_H_
#define _AUDIO_TRACK_PLAYING_DIALOG_H_

#include "fx.h"

class KPlayTrackDialog : public FXDialogBox
{
	FXDECLARE(KPlayTrackDialog)

public:

	enum {
		ID_JOBDONE = FXDialogBox::ID_LAST,		
		ID_BURNDONE,
		ID_SETPROGRESS,
		ID_TOTALTIME,
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
	KPlayTrackDialog();
	KPlayTrackDialog(FXWindow* owner, int16 nTrackNumber);
	~KPlayTrackDialog();

	void create();
	long onCancel(FXObject* sender, FXSelector key, void* data);
	long onChoreJobDone(FXObject* sender, FXSelector key, void* data);
	long onChoreBurnDone(FXObject* sender, FXSelector key, void* data);
	long onSetProgress(FXObject* sender, FXSelector key, void* data);
	long onTimer(FXObject* sender, FXSelector key, void* data);
protected:

	static void OnJobDoneEvent(KPlayTrackDialog*);
	static void OnBurnDoneEvent(const TCHAR *pcError, KPlayTrackDialog*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
		double dBytesWritten, double dImageSize, KPlayTrackDialog *pDlg);
	
	void RestoreEvents();

	void SetProgress(int nProgress, double nBytesPlayed, double nTrackSize);
	void OnJobDone();
	void OnBurnDone(const TCHAR *pcError);
	
	void handleError(int32 errCode);

protected:

	void Done();

	bool			m_bReady;

	FXProgressBar*  m_barProgress;
	FXLabel*		m_lblTrackSize;
	FXLabel*		m_lblBytesPlayed;
	FXButton*		m_btnAbort;
	FXLabel*		m_lblElapsed;
	FXString		m_strLabel;
	FXString		m_strDevice;
	FXTime			m_nStartTime;
	FXMessageChannel	guisignal;

	int16			m_nTrackNumber;
	State			m_enState;

	FXString   m_strCallbackError;

	struct ProgressInfo
	{
		int nProgress;
		double fBytesPlayed;
		double fTrackSize;
	} m_cProgressInfo;
};

#endif //  _AUDIO_TRACK_PLAYING_DIALOG_H_


