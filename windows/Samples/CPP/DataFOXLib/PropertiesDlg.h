#ifndef _PROPERTIES_DLG_H_
#define _PROPERTIES_DLG_H_

#include "DateTime.h"

class KPropertiesDlg : public FXDialogBox
{
	FXDECLARE(KPropertiesDlg)

public:
	enum {
		ID_ACCEPT = FXDialogBox::ID_LAST,
		ID_SYNC_DATES,
		ID_LAST
	};

	KPropertiesDlg(FXWindow *owner, SFileEntry *fileEntry);
	~KPropertiesDlg(void);

	long onSyncDates(FXObject* sender, FXSelector key, void* data);
	long onCmdAccept(FXObject* sender, FXSelector key, void* data);

private:
	KPropertiesDlg() {}
	void handleError(int32 errCode);

	SFileEntry	*m_fileEntry;
	FXString	m_strFileName;
	FXint		m_nHiddenAttribute;
	FXint		m_nAdvancedHiddenAttribute;
	FXint		m_GlobalUsage;

	DECLARE_DATE_TIME_CONTROLS(CreationTime);
	DECLARE_DATE_TIME_CONTROLS(ModificationTime);
	DECLARE_DATE_TIME_CONTROLS(LastAccessTime);

	FXDataTarget tgtFileName;
	FXDataTarget tgtHiddenAttribute;
	FXDataTarget tgtAdvancedHiddenAttribute;
	FXDataTarget tgtGlobalusage;
};

#endif // _PROPERTIES_DLG_H_
