#ifndef _SAVE_DISC_DIALOG_H_
#define _SAVE_DISC_DIALOG_H_

#include "fx.h"

class KSaveDiscDialog : public FXDialogBox
{
	FXDECLARE(KSaveDiscDialog)

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
	KSaveDiscDialog();
	KSaveDiscDialog(FXWindow* owner, const FXString& strFilePath, int16 nFileFormat);
	~KSaveDiscDialog();

	void create();
	long onCancel(FXObject* sender, FXSelector key, void* data);
	long onChoreJobDone(FXObject* sender, FXSelector key, void* data);
	long onChoreBurnDone(FXObject* sender, FXSelector key, void* data);
	long onSetProgress(FXObject* sender, FXSelector key, void* data);
	long onTimer(FXObject* sender, FXSelector key, void* data);
protected:

	static void OnJobDoneEvent(KSaveDiscDialog*);

	static void OnProcessEvent(float fPercent, float fDeviceBuffer, 
		float fCache, double dBytesWritten, double dImageSize, KSaveDiscDialog*);

	static void OnBurnDoneEvent(const TCHAR *pcError, KSaveDiscDialog*);
	
	void RestoreEvents();

	void SetProgress(int nProgress, double dBytesWritten, double dTrackSize, int nErrorsCount);
	void OnJobDone();
	void OnBurnDone(const TCHAR *pcError);
	
	void handleError(int32 errCode);

protected:

	bool			m_bReady;

	FXProgressBar*  m_barProgress;
	FXLabel*		m_lblTotalSectors;
	FXLabel*		m_lblCurrentSector;
	FXLabel*		m_lblErrorsCount;
	FXButton*		m_btnAbort;
	
	const FXString m_strFilePath;
	int16 m_nFileFormat;

	void Done();

	FXList*			m_lbxLog;
	
	FXProgressBar*  m_barBuffer;
	FXButton*		m_btnCancel;
	FXLabel*		m_lblCurrentFile;
	FXLabel*		m_lblElapsed;
	FXLabel*		m_lblSpeed;

	State	m_enState;

	FXString m_strLogLine;
	FXMessageChannel guisignal;

	FXString   m_strCallbackError;

	FXString   m_strCurrentFile;
	FXString   m_strLabel;
	FXString   m_strDevice;
	FXTime	   m_nStartTime;


	struct ProgressInfo
	{
		int nProgress;
		double dCurrentSector;
		double dTotalSectors;
		int nErrorsCount;
	} m_cProgressInfo;
};

#endif //  _SAVE_DISC_DIALOG_H_
