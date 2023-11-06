#ifndef _KHEADER_DLG_H_
#define _KHEADER_DLG_H_

#include "DateTime.h"

class KHeaderDlg: public FXDialogBox {
  FXDECLARE(KHeaderDlg)

public:
	enum {
		ID_ACCEPT = FXDialogBox::ID_LAST,
		ID_RESET,
		ID_SYNC_DATES,
		ID_LAST
	};

public:
	KHeaderDlg(FXWindow *owner, const FXString &title);
	~KHeaderDlg() {}	

	long onCmdReset(FXObject* sender, FXSelector key, void* data);
	long onCmdAccept(FXObject* sender, FXSelector key, void* data);
	long onSyncDates(FXObject* sender, FXSelector key, void* data);

private:
	KHeaderDlg() {}
	void handleError(int32 errCode);

private:
	FXString m_strSysIdent;
	FXString m_strVolSet;
	FXString m_strPublisher;
	FXString m_strDatapreparer;
	FXString m_strApplication;
	FXString m_strCopyrightFile;
	FXString m_strAbstractFile;
	FXString m_strBibliographicFile;
	FXint	 m_bAddFileSuffix;

	FXint	m_nUseCreation;
	FXint	m_nUseModification;
	FXint	m_nUseExpiration;
	FXint	m_nUseEffective;

	FXDataTarget tgtSysIdent;
	FXDataTarget tgtVolSet;
	FXDataTarget tgtPublisher;
	FXDataTarget tgtDatapreparer;
	FXDataTarget tgtApplication;
	FXDataTarget tgtCopyrightFile;
	FXDataTarget tgtAbstractFile;
	FXDataTarget tgtBibliographicFile;
	FXDataTarget tgtAddFileSuffix;

	FXDataTarget tgtUseCreation;
	FXDataTarget tgtUseModification;
	FXDataTarget tgtUseExpiration;
	FXDataTarget tgtUseEffective;

	DECLARE_DATE_TIME_CONTROLS(Creation);
	DECLARE_DATE_TIME_CONTROLS(Expiration);
	DECLARE_DATE_TIME_CONTROLS(Modification);
	DECLARE_DATE_TIME_CONTROLS(Effective);
};

#endif

