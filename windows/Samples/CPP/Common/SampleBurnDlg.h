#ifndef SAMPLE_BURN_DLG_H
#define SAMPLE_BURN_DLG_H

class KSampleBurnDlg : public FXDialogBox
{
	FXDECLARE(KSampleBurnDlg)

public:

	enum {
		ID_SAVELOG = FXDialogBox::ID_LAST,
		ID_ADDLOGLINE,
		ID_BURNFILE,
		ID_SETPROGRESS,
		ID_JOBDONE,
		ID_TOTALTIME,
		ID_LAST
	};

protected:

	struct PROGRESSINFO 
	{
		int progress; 
		int buffer;
	};

	enum State
	{
		ST_NONE,
		ST_BURN,
		ST_FINALIZE,
		ST_VERIFY
	};

public:
	KSampleBurnDlg();
	KSampleBurnDlg(FXWindow* owner);
	~KSampleBurnDlg();

	void create();
	long onCancel(FXObject* sender, FXSelector key, void* data);
	long onSaveLog(FXObject* sender, FXSelector key, void* data);
	long onAddLogLine(FXObject* sender, FXSelector key, void* data);
	long onSetProgress(FXObject* sender, FXSelector key, void* data);
	long onChoreJobDone(FXObject* sender, FXSelector key, void* data);
	long onBurnFile(FXObject* sender, FXSelector key, void* data);
	long onTimer(FXObject* sender, FXSelector key, void* data);

protected:

	static void OnFinalizeEvent(KSampleBurnDlg*);
	static void OnBurnDoneEvent(const TCHAR* pcError, KSampleBurnDlg*);
	static void OnJobDoneEvent(KSampleBurnDlg*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesWritten, double dImageSize, KSampleBurnDlg *pDlg);

	static void OnInfoTextEvent(const TCHAR *pcInfoText, int32 nLevel, KSampleBurnDlg*);

	static void OnStartVerifyEvent(KSampleBurnDlg*);
	static void OnVerifyFileEvent(const TCHAR *pcFileName, KSampleBurnDlg*);
	static void OnVerifyErrorEvent(const TCHAR *pcFileName, const TCHAR *pcError, KSampleBurnDlg*);
	static void OnVerifyDoneEvent(int32 nNumErrors, KSampleBurnDlg* pUserData);

	static void OnBurnFileEvent(const TCHAR* pcFileName, KSampleBurnDlg* pUserData);

	void RestoreEvents();

	void AddLogLine(const FXString& strLogLine);
	void SetProgress(int progress, int buffer);
	void OnJobDone();
	void SetCurrentFile(const FXString& strFileName);

	void UpdateTitle();

	void handleError(int32 errCode);

protected:
	FXList*			m_lbxLog;
	FXProgressBar*  m_barProgress;
	FXProgressBar*  m_barBuffer;
	FXButton*		m_btnCancel;
	FXLabel*		m_lblCurrentFile;
	FXLabel*		m_lblElapsed;
	FXLabel*		m_lblSpeed;

	State	m_enState;

	FXString m_strLogLine;
	FXMessageChannel guisignal;

	PROGRESSINFO m_progInfo;

	FXString   m_strCurrentFile;
	FXString   m_strLabel;
	FXString   m_strDevice;
	FXTime	   m_nStartTime;
};

#endif
