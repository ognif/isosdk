#ifndef _MD5_DIALOG_H_
#define _MD5_DIALOG_H_
#include "stdafx.h"

#include "fx.h"
#include "md5/KMD5Counter.h"
#include "md5/kmd5filesource.h"

class KMD5Dialog : public FXDialogBox
{
	  FXDECLARE(KMD5Dialog)
private:
	FXProgressBar*	m_pProgressBar;
	FXButton*		m_pCancelButton;
	bool m_bDone;
	bool m_bCancelPressed;
	KMD5FileSource*  m_pcMD5FileSource;
	KMD5Counter		m_cMD5Counter;

	FXString m_strMD5;
	void GenerateMD5();

protected:
	
	// Default constructor needed.
	KMD5Dialog(){}

public:
	KMD5Dialog(FXWindow* owner,const FXString& strFileName);
	~KMD5Dialog();

	FXString GetMD5String();

public:
  // Messages for class
  enum{
    ID_CANCEL_BUTTON=FXDialogBox::ID_LAST,
    ID_TIME_TO_UPDATE_PROGRESS,
    ID_LAST
    };

  long onUpdateProgress(FXObject*,FXSelector,void*);
  long onCancelButton(FXObject*,FXSelector,void*);
  void create();
};


#endif //_MD5_DIALOG_H_
