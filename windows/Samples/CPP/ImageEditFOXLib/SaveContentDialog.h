#ifndef _SAVE_CONTENT_DIALOG_H_
#define _SAVE_CONTENT_DIALOG_H_

#include "fx.h"
#include "TreeNodes.h"

class KSaveContentDialog : public FXDialogBox
{
	FXDECLARE(KSaveContentDialog)

public:

	enum {
		ID_JOBDONE = FXDialogBox::ID_LAST,
		ID_BURNDONE,
		ID_SETPROGRESS,
		ID_TOTALTIME,
		ID_LOG_BOX,
		ID_LAST
	};


	enum EAim
	{
		AIM_IMPORT,
		AIM_VERIFY,
	};

	typedef std::vector<ITreeNode*> NodeList;

	struct SSaveContentParams
	{
		EAim enAim;
		NodeList nodes;
		FXString strExtractionFolderPath;
		FXString strPassword;
		int32 optType;

		SSaveContentParams() :
		 enAim(AIM_VERIFY),
		 strExtractionFolderPath(_T("")),
		 strPassword(_T("")),
		 optType(0)
		{
		};

		SSaveContentParams(EAim _enAim, const NodeList& _nodes, FXString _strExtractionFolderPath = _T(""), FXString _strPassword = _T(""), int32 _optType = 0) :
		 nodes(_nodes),
		 enAim(_enAim),
		 strExtractionFolderPath(_strExtractionFolderPath),
		 strPassword(_strPassword),
		 optType(_optType)
		{	
		};
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


private:

	KSaveContentDialog();

public:

	KSaveContentDialog(SSaveContentParams params, FXWindow* owner);
	~KSaveContentDialog();

	void create();
	long onCancel(FXObject* sender, FXSelector key, void* data);
	long onChoreJobDone(FXObject* sender, FXSelector key, void* data);	
	long onChoreBurnDone(FXObject* sender, FXSelector key, void* data);
	long onSetProgress(FXObject* sender, FXSelector key, void* data);	
	long onTimer(FXObject* sender, FXSelector key, void* data);

private:
	
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, 
		float fCache, double dBytesWritten, double dImageSize, KSaveContentDialog*);
	static void OnJobDoneEvent(KSaveContentDialog*);
	static void OnBurnDoneEvent(const TCHAR *pcError, KSaveContentDialog*);
	static void OnBurnFileEvent(const TCHAR* pcFileName, KSaveContentDialog*);
	static void OnVerifyFileEvent(const TCHAR* pcFileName, KSaveContentDialog*);
	static void OnVerifyErrorEvent(const TCHAR *pcFileName, const TCHAR *pcError, KSaveContentDialog*);
	static void OnVerifyDoneEvent(int nNumErrors, KSaveContentDialog*);
	
	void RestoreEvents();

	void SetProgress(int nProgress, int64 nBytesWritten, int64 nTottalSize);
	void OnJobDone();
	void OnBurnDone(const TCHAR *pcError);
	void AddCurrentFile(const TCHAR *pcFileName);
	void OnVerifyFile(const TCHAR *pcFileName);
	void OnVerifyError(const TCHAR *pcFileName, const TCHAR *pcError);
	void OnVerifyDone(int nNumErrors);


protected:

	void Done();
	void handleError(int32 errCode);
	void LogPrint(const FXString& strText);
	bool ProcessNextNode();

	int64 CalculateTotalSize(NodeList::iterator iCurrentNode);
	int64 CalculateNodeSize(ITreeNode* node);
	int64 CalculateFileSize(FileNode* filenode);
	

protected:
	

	FXProgressBar*  m_barProgress;
	FXLabel*		m_lblTotalSize;
	FXLabel*		m_lblBytesProcessed;
	FXButton*		m_btnAbort;
	FXText*			m_pLogBox;
	FXList*			m_lbxLog;
	FXProgressBar*  m_barBuffer;
	FXButton*		m_btnCancel;
	FXLabel*		m_lblElapsed;
	FXMessageChannel		guisignal;		
	FXTime			m_nStartTime;
	FXFont*			m_pFont;
	
	
	FXString		m_strCallbackError;
	
	SSaveContentParams m_cParams;
	NodeList::iterator m_iCurrentNode;

	//Total files processed
	int32			m_nTotalFiles;
	//Process state
	State			m_enState;

	int64			m_nTotalSize;
	int64			m_nCurrJobsSize;
	int64			m_nDoneJobsSize;

	struct ProgressInfo
	{
		int nProgress;
		int64 nBytesProcessed;
	} m_cProgressInfo;
};

#endif //  _SAVE_CONTENT_DIALOG_H_
