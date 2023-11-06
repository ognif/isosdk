#ifndef _KBOOTIMG_DLG_
#define _KBOOTIMG_DLG_


class KBootImgDlg: public FXDialogBox {
  FXDECLARE(KBootImgDlg)

public:
	enum {
		ID_SELFILE = FXDialogBox::ID_LAST,
		ID_MEDIATYPE,
		ID_PLATFORM,
		ID_RESET,
		ID_ACCEPT,
		ID_LAST
	};

public:
	KBootImgDlg(FXWindow *owner, const FXString &title);
	~KBootImgDlg() {}

	void handleError(int32 errCode);
	
	long onCmdFileSelect(FXObject* sender, FXSelector key, void* data);
	long onCmdMediatype(FXObject* sender, FXSelector key, void* data);
	long onCmdPlatform(FXObject* sender, FXSelector key, void* data);
	long onCmdReset(FXObject* sender, FXSelector key, void* data);
	long onCmdAccept(FXObject* sender, FXSelector key, void* data);

public:
	FXString m_strBootImage;
	FXint m_iMediaType;
	FXint m_iPlatform;
	FXint m_nSectorCount;
	FXint m_nLoadSegment;
	FXString m_strDeveloperID;
	FXint m_bMakeDiskBootable;

private:
	KBootImgDlg() {}

private:
	FXDataTarget tgtBootImage;
	FXDataTarget tgtSectorCount;
	FXDataTarget tgtLoadSegment;
	FXDataTarget tgtDeveloperID;
	FXDataTarget tgtMakeDiskBootable;
};

#endif
