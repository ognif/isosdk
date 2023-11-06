#ifndef _KSESSION_DLG_H_
#define _KSESSION_DLG_H_

class KSessionDlg: public FXDialogBox {
	FXDECLARE(KSessionDlg)

public:
	enum {
		ID_ACCEPT = FXDialogBox::ID_LAST,
		ID_LAST
	};

	KSessionDlg(FXWindow *owner, const FXString &title);
	~KSessionDlg() {}

	long onCmdAccept(FXObject* sender, FXSelector key, void* data);	

public:
	int32 m_nSession;

private:
	KSessionDlg() {}
	void handleError(int32 errCode);

private:
	FXIconList *sessionList;
};

#endif
