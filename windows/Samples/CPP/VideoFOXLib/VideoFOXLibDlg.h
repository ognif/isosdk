#ifndef _VIDEOFOXLIB_DLG_H
#define _VIDEOFOXLIB_DLG_H

#include "VideoFOXLibDlg.h"
#include "VideoscanDlg.h"

class KCDCapacityRule;

class KVideoFOXLibDlg: public FXDialogBox {
  FXDECLARE(KVideoFOXLibDlg)

public:
	enum {
		ID_ADDVIDEOFILE = FXDialogBox::ID_LAST,
		ID_ADDPICTUREFILE,
		ID_DELETEITEM,
		ID_RESETLIST,
		ID_WRITELOG,

		ID_BURNDISK_DEVELOPED,
		ID_BURNDISK_FOXBURNER,
		ID_ERASEDISK,

		ID_ASPI_INTERNAL,
		ID_ASPI_WNASPI,
		ID_ASPI_FROGASPI,
		ID_RESCANDEVICES,
		ID_BURNDEVICES,
		ID_DISABLEIMAGE,

		ID_ABOUT,
		ID_WEB,

		ID_DEVICEBOX,
		ID_PROJECTTYPE,
		ID_VIDEOFILELIST,
		ID_PICTUREFILELIST,

		ID_ADDLOGLINE,
		ID_LAST
	};

public:
	KVideoFOXLibDlg(FXApp *app, const FXString &title);
	~KVideoFOXLibDlg();

	long onAddFile(FXObject* sender, FXSelector key, void* data);
	long onDeleteItem(FXObject* sender, FXSelector key, void* data);
	long onResetList(FXObject* sender, FXSelector key, void* data);
	long onWriteLogFile(FXObject* sender, FXSelector key, void* data);

	long onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data);
	long onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data);
	long onEraseDisk(FXObject* sender, FXSelector key, void* data);

	long onCmdAspi(FXObject* sender, FXSelector key, void* data);
	long onUpdAspi(FXObject* sender, FXSelector key, void* data);
	long onRescanDevices(FXObject* sender, FXSelector key, void* data);
	long onBurningDevices(FXObject* sender, FXSelector key, void* data);
	long onDisableImagewriter(FXObject* sender, FXSelector key, void* data);

	long onAbout(FXObject* sender, FXSelector key, void* data);
	long onWeb(FXObject* sender, FXSelector key, void* data);

	long onDeviceBoxChange(FXObject* sender, FXSelector key, void* data);
	long onProjectTypeChange(FXObject* sender, FXSelector key, void* data);

	void loadOwner();

private:
	KVideoFOXLibDlg();
	void updateDeviceCombo();
	int32 updateOptions();
	void handleError(int32 errCode);
	void prepareMenus();

private:
	FXTabBook*			m_tabBook;
	FXComboBox*			m_cmbDevice;
	FXIconList*			m_videoFileList;
	FXIconList*			m_pictureFileList;
	FXComboBox*			m_cmbProjectType;
	KVideoScanDlg		m_dlgVideoScan;
	FXButton*			m_btnBurn;
	KCDCapacityRule*	m_rule;
	FXMenuCheck*		burnDevicesOnly;

	FXint		 m_bEjectAfterBurn;
	FXint		 m_bJoliet;
	FXDataTarget m_tgtEjectAfterBurn;
	FXDataTarget m_tgtJoliet;

	FXIcon *m_miniDoc;

	bool m_bMultideviceEnabled;
	bool m_bBurningDevicesOnly;

	FXString m_strStartupDir;
};

#endif
