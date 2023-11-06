#pragma once
#ifndef _READ_CD_TEXT_DIALOG_H_
#define _READ_CD_TEXT_DIALOG_H_

class KReadCDTextDlg: public FXDialogBox {
  FXDECLARE(KReadCDTextDlg)

public:
	enum
	{		
		ID_ACCEPT = FXDialogBox::ID_LAST,
		ID_LAST
	};

public:
	KReadCDTextDlg(
					FXApp *app, const FXString &title,
					const FXString& strArranger,
					const FXString& strComposer,
					const FXString& strSongWriter,
					const FXString& strPerformer,
					const FXString& strMessage,
					const FXString& strTitle							);
				
				
	~KReadCDTextDlg() {}

	long onCmdAccept(FXObject* sender, FXSelector key, void* data);

protected:
	KReadCDTextDlg() {}
};




#endif // _READ_CD_TEXT_DIALOG_H_
