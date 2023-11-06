#pragma once

#include <vector>
#include "TreeNodes.h"

// KSaveContentDialog dialog

class KSaveContentDialog : public CDialog
{
public:

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
		CString strExtractionFolderPath;
		CString strPassword;
		int32 optType;

		SSaveContentParams() :
		 enAim(AIM_VERIFY),
		 strExtractionFolderPath(_T("")),
		 strPassword(_T("")),
		 optType(0)
		{
		};

		SSaveContentParams(EAim _enAim, const NodeList& _nodes, CString _strExtractionFolderPath = _T(""), CString _strPassword = _T(""), int32 _optType = 0) :
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

	
	DECLARE_DYNAMIC(KSaveContentDialog)

private:
	KSaveContentDialog(CWnd* pParent = NULL);   // standard constructor

public:	
	KSaveContentDialog(SSaveContentParams params, CWnd* pParent = NULL);
	virtual ~KSaveContentDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTENT };

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
	void AddCurrentFile(const TCHAR *pcFileName);
	void OnVerifyFile(const TCHAR *pcFileName);
	void OnVerifyError(const TCHAR *pcFileName, const TCHAR *pcError);
	void OnVerifyDone(int nNumErrors);

	LRESULT OnOnBurnDoneNotify(WPARAM, LPARAM);
		
protected :

	int64 CalculateTotalSize(NodeList::iterator iCurrentNode);
	int64 CalculateNodeSize(ITreeNode* node);
	int64 CalculateFileSize(FileNode* filenode);

	BOOL ProcessNextNode();
	void HandleError(int32 errCode);
	void LogPrint(const CString& strText);
	void Done();


protected:

	SSaveContentParams m_cParams;
	NodeList::iterator m_iCurrentNode;

	//Total files processed
	int32			m_nTotalFiles;

	int64			m_nTotalSize;
	int64			m_nCurrJobsSize;
	int64			m_nDoneJobsSize;
	
	//Process state
	State			m_enState;
	//Start time for calculate processing time
	CTimeSpan		m_timeStart;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR);
	
	virtual void OnCancel();
};
