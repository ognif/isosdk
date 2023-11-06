#include "stdafx.h"
#include "md5Dialog.h"

#include "fx.h"

FXDEFMAP(KMD5Dialog) KMD5DialogMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______  
	FXMAPFUNC(SEL_TIMEOUT,           KMD5Dialog::ID_TIME_TO_UPDATE_PROGRESS,  KMD5Dialog::onUpdateProgress),
	FXMAPFUNC(SEL_COMMAND,           KMD5Dialog::ID_CANCEL_BUTTON,			  KMD5Dialog::onCancelButton),
};

FXIMPLEMENT(KMD5Dialog,FXDialogBox,KMD5DialogMap,ARRAYNUMBER(KMD5DialogMap))


KMD5Dialog::KMD5Dialog(FXWindow* owner,const FXString& strFileName)
	: FXDialogBox(owner, "MD5 hash code counting...", DECOR_TITLE | DECOR_BORDER,0,0,450)
	, m_bDone(false)	
	, m_bCancelPressed(false)	
	, m_strMD5("")
{
	FXVerticalFrame*	mainFrame = new FXVerticalFrame(this, LAYOUT_FILL);
	/*FXLabel*			lblFileName = */new FXLabel(mainFrame, strFileName);
	/*FXLabel*			lblProgress = */new FXLabel(mainFrame, "Reading file and counting MD5 hash code...");
	m_pProgressBar = new FXProgressBar(mainFrame, 0, 0, PROGRESSBAR_NORMAL | LAYOUT_FILL_X);
	m_pProgressBar->setProgress(0);
	m_pCancelButton = new FXButton(mainFrame, "&Cancel", 0, this, ID_CANCEL_BUTTON, BUTTON_NORMAL | LAYOUT_RIGHT);

	m_pcMD5FileSource = new KMD5FileSource(strFileName);
	m_cMD5Counter.SetDataSource(m_pcMD5FileSource);
}


KMD5Dialog::~KMD5Dialog()
{
	delete m_pcMD5FileSource;
}

void KMD5Dialog::create()
{
	FXDialogBox::create();
	m_cMD5Counter.start();
	this->getApp()->addTimeout(this, ID_TIME_TO_UPDATE_PROGRESS, 20);
}

long KMD5Dialog::onUpdateProgress(FX::FXObject* sen, FX::FXSelector sel, void* ev)
{
	m_bDone = m_cMD5Counter.IsCountingDone();
	m_pProgressBar->setProgress(m_cMD5Counter.GetProgress());

	if (!m_bDone && !m_bCancelPressed)
	{
		this->getApp()->addTimeout(this, ID_TIME_TO_UPDATE_PROGRESS, 20);
	}
	else
	{	
		if (m_bCancelPressed)
		{
			this->onCmdAccept(sen, sel, ev);
			if (m_bDone)
			{
				GenerateMD5();
			}
		}

		m_pProgressBar->setProgress(100);
		m_pCancelButton->setText("&Close");
	}

	return 1;
}

long KMD5Dialog::onCancelButton(FX::FXObject* sen, FX::FXSelector sel, void* ev)
{	
	m_bCancelPressed = true;

	if (!this->getApp()->hasTimeout(this, ID_TIME_TO_UPDATE_PROGRESS))
	{
		this->getApp()->addTimeout(this, ID_TIME_TO_UPDATE_PROGRESS, 1);
	}

	return 1;
}

void KMD5Dialog::GenerateMD5()
{
	unsigned char* pucharMD5 = m_cMD5Counter.GetMD5();
	m_strMD5.clear();

	for (int i = 0 ; i < 16; ++i)
	{		
		m_strMD5 += FXString::value("%02x", int(pucharMD5[i]));
	}	
}

FXString KMD5Dialog::GetMD5String()
{
	return m_strMD5;
}
