#include "stdafx.h"
#include "ScanSectorsDialog.h"

class KLogThread : public FXThread
{
private:
	ScanSectorsLogging::ILogGUI* m_pGUI;
	int32 m_nStartLBA;
	int32 m_nRegionSize;
public:
	KLogThread(ScanSectorsLogging::ILogGUI* pGUI, int32 nStartLBA, int32 nRegionSize)
		:m_pGUI(pGUI)
		, m_nStartLBA(nStartLBA)
		, m_nRegionSize(nRegionSize)
	{}
protected:
	FXint run()
	{
		if (m_nRegionSize)
		{
			const int32 nMaxSectorsToRead = 27;

			int32 nCurLba;
			int32 nSectorsToRead = nMaxSectorsToRead;
			int32 nFinLBA = m_nStartLBA + m_nRegionSize;

			ScanSectorsLogging::SReadResults sReadRes;

			for (nCurLba = m_nStartLBA;
				(nCurLba < nFinLBA) && !m_pGUI->Stopped(); /*nCurLba increments in the body*/)
			{
				if (nCurLba + nMaxSectorsToRead >= nFinLBA)
				{
					nSectorsToRead = nFinLBA - nCurLba;
				}

				const int32 buff_length = 2352 * nMaxSectorsToRead;
				uint8 buff[buff_length];
				int32 nRes = ::ReadSectors(BS_READ_DEVICE, nCurLba,
					nSectorsToRead, BS_IMG_BIN, buff, buff_length);

				if (nRes == BS_SDK_ERROR_NO)
				{
					sReadRes.bSuccessive = true;
					sReadRes.nLBA = nCurLba;
					sReadRes.nNumSectors = nSectorsToRead;
					m_pGUI->AddResults(sReadRes);
					nCurLba += nSectorsToRead;
				}
				else
				{
					int32 nErrLba = nCurLba;
					for (; nCurLba < nErrLba + nSectorsToRead; ++nCurLba)
					{
						int32 nRes = ::ReadSectors(BS_READ_DEVICE, nCurLba, 1,
							BS_IMG_BIN, buff, buff_length);

						if (nRes == BS_SDK_ERROR_NO)
						{
							sReadRes.bSuccessive = true;
							sReadRes.nLBA = nCurLba;
							sReadRes.nNumSectors = 1;
							m_pGUI->AddResults(sReadRes);
						}
						else
						{
							sReadRes.bSuccessive = false;
							sReadRes.nLBA = nCurLba;
							sReadRes.nNumSectors = 1;
							m_pGUI->AddResults(sReadRes);
						}
					}
				}
			}

			m_pGUI->Finish();

		}


		return 0;
	}
};



FXDEFMAP(KScanSectorsDialog) KScanSectorsMap[] = {
	FXMAPFUNC(SEL_COMMAND,	KScanSectorsDialog::ID_START, KScanSectorsDialog::onStart),
	FXMAPFUNC(SEL_COMMAND,	KScanSectorsDialog::ID_STOP, KScanSectorsDialog::onStop),
	FXMAPFUNC(SEL_CLOSE, 0, KScanSectorsDialog::onCancel),
	FXMAPFUNC(SEL_CHORE,    KScanSectorsDialog::ID_PROCESS_QUEUE, KScanSectorsDialog::onProcessQueue),
	FXMAPFUNC(SEL_CHORE,    KScanSectorsDialog::ID_FINISH, KScanSectorsDialog::onFinish),

};

FXIMPLEMENT(KScanSectorsDialog, FXDialogBox, KScanSectorsMap, ARRAYNUMBER(KScanSectorsMap))



KScanSectorsDialog::KScanSectorsDialog()
	:m_bCancelled(false)
	, m_pProgressBar(0)
	, m_pText(0)
	, m_nStartLba(0)
	, m_nRegionSizeInSectors(0)
	, m_nBadSectors(0)
	, m_nSectorsRead(0)
	, m_pWorkerThread(0)
	, m_pStartButton(0)
	, m_pStopButton(0)
	, guisignal(NULL)
{}

KScanSectorsDialog::KScanSectorsDialog(FXWindow* owner, int32 nStartLBA, int32 nRegionSizeInSectors)
	:FXDialogBox(owner, "Scan Sectors", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	, m_bCancelled(false)
	, m_pProgressBar(0)
	, m_pText(0)
	, m_nStartLba(nStartLBA)
	, m_nRegionSizeInSectors(nRegionSizeInSectors)
	, m_nBadSectors(0)
	, m_nSectorsRead(0)
	, m_pWorkerThread(0)
	, m_pStartButton(0)
	, m_pStopButton(0)
	, guisignal(owner->getApp())
{
	FXVerticalFrame* vFrame = new FXVerticalFrame(this, LAYOUT_FILL|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT, 0, 0, 680, 500);

	FXVerticalFrame* loggingWidgetFrame = new FXVerticalFrame(vFrame, FRAME_NORMAL | LAYOUT_FILL);
	m_pText = new FXText(loggingWidgetFrame, 0, 0, TEXT_READONLY | LAYOUT_FILL);
	m_pText->setScrollStyle(SCROLLERS_TRACK);

	m_pProgressBar = new FXProgressBar(vFrame, 0, 0, PROGRESSBAR_NORMAL | PROGRESSBAR_PERCENTAGE | LAYOUT_FILL_X);

	FXHorizontalFrame* pControlFrame = new FXHorizontalFrame(vFrame, LAYOUT_FILL_X);
	m_pStartButton = new FXButton(pControlFrame, "&Start", 0, this, ID_START, BUTTON_NORMAL, 0, 0, 75);
	m_pStopButton = new FXButton(pControlFrame, "S&top", 0, this, ID_STOP, BUTTON_NORMAL, 0, 0, 75);

	m_pWorkerThread = new KLogThread(this, nStartLBA, nRegionSizeInSectors);
}

KScanSectorsDialog::~KScanSectorsDialog()
{
	if (m_pWorkerThread)
	{
		delete m_pWorkerThread;
	}
}


void KScanSectorsDialog::create()
{
	FXDialogBox::create();
	onStart(0, 0, 0);
}


long KScanSectorsDialog::onStart(FXObject* sender, FXSelector key, void* data)
{
	Reset();
	m_pWorkerThread->start();
	EnableStop();
	return 1;
}

long KScanSectorsDialog::onStop(FXObject* sender, FXSelector key, void* data)
{
	if (m_pWorkerThread->running())
	{
		HandleUserCancellation();

		FXMessageBox msgBox(this, "Scanning sectors", "Aborted by user", NULL, MBOX_OK);
		msgBox.execute();

		if (m_pWorkerThread->running())
		{
			m_pWorkerThread->cancel();
		}
	}

	return 1;
}

void KScanSectorsDialog::EnableStart()
{
	m_pStartButton->enable();
	m_pStopButton->disable();
}

void KScanSectorsDialog::EnableStop()
{
	m_pStartButton->disable();
	m_pStopButton->enable();
}

long KScanSectorsDialog::onCancel(FXObject* sender, FXSelector key, void* data)
{
	if (FXSELTYPE(key) == SEL_CLOSE)
	{
		onStop(0, 0, 0);
		return FXDialogBox::onCmdCancel(sender, key, data);
	}

	return 1;
}

void KScanSectorsDialog::AddResults(const ScanSectorsLogging::SReadResults& sRR)
{
	m_cQueueMutex.lock();
	{
		m_qReadResults.push(sRR);
	}
	m_cQueueMutex.unlock();
	//FXApp::instance()->addChore(this, ID_PROCESS_QUEUE, 0);

	guisignal.message(this, FXSEL(SEL_CHORE, ID_PROCESS_QUEUE), NULL, NULL);

}

void KScanSectorsDialog::Finish()
{
	FXThread::yield();
	//FXApp::instance()->addChore(this, ID_FINISH, 0);
	guisignal.message(this, FXSEL(SEL_CHORE, ID_FINISH), NULL, NULL);
}

bool KScanSectorsDialog::Stopped(void)
{
	return m_bCancelled;
}

long KScanSectorsDialog::onProcessQueue(FXObject* sender, FXSelector key, void* data)
{
	m_cQueueMutex.lock();
	{
		while (!m_qReadResults.empty())
		{
			ScanSectorsLogging::SReadResults sRR = m_qReadResults.front();
			m_qReadResults.pop();
			m_nSectorsRead += sRR.nNumSectors;
			m_pProgressBar->setProgress(100.0 * ((double)m_nSectorsRead) / m_nRegionSizeInSectors);
			if (sRR.bSuccessive)
			{
				LogSuccessiveRead(sRR.nLBA, sRR.nNumSectors);
			}
			else
			{
				LogFailureRead(sRR.nLBA);
			}
		}
	}
	m_cQueueMutex.unlock();

	return 0;
}

long KScanSectorsDialog::onFinish(FXObject* sender, FXSelector key, void* data)
{
	Done();
	m_pProgressBar->setProgress(0);
	EnableStart();
	return 0;
}


void KScanSectorsDialog::LogSuccessiveRead(int32 nSuccessLba, int32 nSectors)
{
	if (!m_bCancelled)
	{
		FXString str;
		str.format("Sectors read successfully at LBA: %d. Quantity: %d.\n", nSuccessLba, nSectors);
		m_pText->appendText(str);

		ScrollToEndOfText();
	}
}

void KScanSectorsDialog::LogFailureRead(int32 nFailLba)
{
	if (!m_bCancelled)
	{
		++m_nBadSectors;

		FXString str;
		str.format("Sector read fail at LBA: %d.\n", nFailLba);
		m_pText->appendText(str);

		ScrollToEndOfText();
	}
}

void KScanSectorsDialog::Reset()
{
	m_pText->setText("Scan log:\n");
	FXString str;
	str.format("Scanning %d sectors from LBA %d...\n", m_nRegionSizeInSectors, m_nStartLba);
	m_pText->appendText(str);
	m_nBadSectors = 0;
	m_nSectorsRead = 0;
	m_bCancelled = false;
	ScrollToEndOfText();
}

void KScanSectorsDialog::Done()
{
	FXString str;
	str.format("Done. Sectors read: %d, from LBA: %d.\nNumber of bad sectors: %d\n", m_nSectorsRead, m_nStartLba, m_nBadSectors);
	m_pText->appendText(str);

	ScrollToEndOfText();
}

void KScanSectorsDialog::HandleUserCancellation()
{
	m_bCancelled = true;
	FXThread::yield();
	FXThread::sleep(500 * 1000 * 1000 /*nanoseconds*/);
	FXString str;
	str.format("User cancelled.\n");
	m_pText->appendText(str);

	ScrollToEndOfText();
}

void KScanSectorsDialog::ScrollToEndOfText()
{
	m_pText->setCursorRow(m_pText->getNumRows());
	m_pText->makePositionVisible(m_pText->getCursorPos());
}
