#ifndef _SCAN_SECTORS_DIALOG_H_
#define _SCAN_SECTORS_DIALOG_H_

#include "fx.h"
#include <queue>
#include "Logging.h"

class KLogThread;

class KScanSectorsDialog : public FXDialogBox, public ScanSectorsLogging::ILogGUI
{
	FXDECLARE(KScanSectorsDialog)
public:
	enum
	{
		ID_START = FXDialogBox::ID_LAST,
		ID_STOP,
		ID_PROCESS_QUEUE,
		ID_FINISH,
		ID_LAST
	};

public:
	KScanSectorsDialog();
	KScanSectorsDialog(FXWindow* owner, int32 nStartLBA, int32 nRegionSizeInSectors);
	~KScanSectorsDialog();

	long onStart(FXObject* sender, FXSelector key, void* data);
	long onStop(FXObject* sender, FXSelector key, void* data);
	long onProcessQueue(FXObject* sender, FXSelector key, void* data);
	long onFinish(FXObject* sender, FXSelector key, void* data);
	void create();
	long onCancel(FXObject* sender, FXSelector key, void* data);

	virtual void AddResults(const ScanSectorsLogging::SReadResults& sRR);
	virtual bool Stopped(void);
	virtual void Finish();

private:
	bool m_bCancelled;

	std::queue<ScanSectorsLogging::SReadResults> m_qReadResults;
	FXMutex m_cQueueMutex;

	FXProgressBar* m_pProgressBar;
	FXText* m_pText;

	int32 m_nStartLba;
	int32 m_nRegionSizeInSectors;
	int32 m_nBadSectors;
	int32 m_nSectorsRead;

	KLogThread* m_pWorkerThread;

	FXButton* m_pStartButton;
	FXButton* m_pStopButton;

	FXMessageChannel		guisignal;

	void Done();
	void HandleUserCancellation();
	void ScrollToEndOfText();
	void Reset();
	void LogFailureRead(int32 nFailLba);
	void LogSuccessiveRead(int32 nSuccessLba, int32 nSectors);


	void EnableStart();
	void EnableStop();
};




#endif //_SCAN_SECTORS_DIALOG_H_

