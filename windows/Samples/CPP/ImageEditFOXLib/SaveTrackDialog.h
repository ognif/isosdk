#ifndef _SAVE_TRACK_DIALOG_H_
#define _SAVE_TRACK_DIALOG_H_

#include "fx.h"

class KSaveTrackDialog : public FXDialogBox
{
	FXDECLARE(KSaveTrackDialog)

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
	KSaveTrackDialog();
	KSaveTrackDialog(FXWindow* owner, int16 nTrackNumber, const FXString& strFilePath, unsigned int nFileFormat);
	~KSaveTrackDialog();

	void create();
	long onCancel(FXObject* sender, FXSelector key, void* data);
	long onChoreJobDone(FXObject* sender, FXSelector key, void* data);
	long onChoreBurnDone(FXObject* sender, FXSelector key, void* data);
	long onSetProgress(FXObject* sender, FXSelector key, void* data);
	long onTimer(FXObject* sender, FXSelector key, void* data);
protected:

	static void OnJobDoneEvent(KSaveTrackDialog*);

	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
		double dBytesWritten, double dImageSize, KSaveTrackDialog*);

	static void OnBurnDoneEvent(const TCHAR *pcError, KSaveTrackDialog*);
	
	void RestoreEvents();

	void SetProgress(int nProgress, double nBytesWritten, double nTrackSize);
	void OnJobDone();
	void OnBurnDone(const TCHAR *pcError);
	
	void handleError(int32 errCode);

protected:

	bool			m_bReady;

	FXProgressBar*  m_barProgress;
	FXLabel*		m_lblTrackSize;
	FXLabel*		m_lblBytesWritten;
	FXButton*		m_btnAbort;

	int16 m_nTrackNumber;
	const FXString m_strFilePath;
	unsigned int m_nFileFormat;

	void Done();

	FXLabel*		m_lblElapsed;

	State	m_enState;

	FXMessageChannel guisignal;

	FXString   m_strCallbackError;

	FXString   m_strCurrentFile;
	FXString   m_strLabel;
	FXString   m_strDevice;
	FXTime	   m_nStartTime;

	struct ProgressInfo
	{
		int nProgress;
		double fBytesWritten;
		double fTrackSize;
	} m_cProgressInfo;
};

#endif //  _SAVE_TRACK_DIALOG_H_


