#ifndef _DATAFOXLIB_DLG_H
#define _DATAFOXLIB_DLG_H

#include "../Common/FileTreeFoxLib.h"
#include "../Common/Rule.h"


class KDataFOXLibDlg: public FXDialogBox {
  FXDECLARE(KDataFOXLibDlg)

public:
  enum {
	ID_ADDFILE = FXDialogBox::ID_LAST,
	ID_ADDFOLDER,
	ID_RENAMEFILE,
	ID_DELETEITEM,
	ID_RESETLIST,
	ID_EDITPROPERTIES,
	ID_WRITELOG,

	ID_BURNDISK_DEVELOPED,
	ID_BURNDISK_FOXBURNER,
	ID_ERASEDISK,
	ID_VERIFY,

	ID_EXTHEADER,
	ID_BOOTDISK,
	ID_SESSION,
	ID_IMPORT_LAST_SESSION,
	ID_IMPORT_NO_SESSION,

	ID_MOUNTIMAGE,
	ID_UNMOUNTIMAGE,
	ID_BURNIMAGE,

	ID_ASPI_INTERNAL,
	ID_ASPI_WNASPI,
	ID_ASPI_FROGASPI,
	ID_RESCANDEVICES,
	ID_BURNDEVICES,
	ID_DISABLEIMAGE,
	ID_IGNOREFILECHECK,

	ID_ABOUT,
	ID_WEB,

	ID_DEVICEBOX,
	ID_PROJECTTYPE,
	ID_FILELIST,

	ID_ERRORNOTIFY,
	ID_LAST,
	ID_PATHRULE
  };

  enum  DataFOXLibSelType {
	SEL_ERRORNOTIFY = SEL_LAST
  };

public:
	KDataFOXLibDlg(FXApp *app, const FXString &title);
	~KDataFOXLibDlg();

	long onAddFile(FXObject* sender, FXSelector key, void* data);
	long onAddFolder(FXObject* sender, FXSelector key, void* data);
	long onRenameFile(FXObject* sender, FXSelector key, void* data);
	long onDeleteItem(FXObject* sender, FXSelector key, void* data);
	long onResetList(FXObject* sender, FXSelector key, void* data);
	long onEditProperties(FXObject* sender, FXSelector key, void* data);
	long onWriteLogFile(FXObject* sender, FXSelector key, void* data);

	long onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data);
	long onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data);
	long onEraseDisk(FXObject* sender, FXSelector key, void* data);
	long onVerifySelect(FXObject* sender, FXSelector key, void* data);

	long onExtHeader(FXObject* sender, FXSelector key, void* data);
	long onBootDisk(FXObject* sender, FXSelector key, void* data);
	long onSessionSelect(FXObject* sender, FXSelector key, void* data);
	long onImportLastSession(FXObject* sender, FXSelector key, void* data);
	long onImportNoSession(FXObject* sender, FXSelector key, void* data);

	long onMountImage(FXObject* sender, FXSelector key, void* data);
	long onUnmountImage(FXObject* sender, FXSelector key, void* data);
	long onBurnImage(FXObject* sender, FXSelector key, void* data);

	long onCmdAspi(FXObject* sender, FXSelector key, void* data);
	long onUpdAspi(FXObject* sender, FXSelector key, void* data);
	long onRescanDevices(FXObject* sender, FXSelector key, void* data);
	long onBurningDevices(FXObject* sender, FXSelector key, void* data);
	long onDisableImagewriter(FXObject* sender, FXSelector key, void* data);
	long onIgnoreFileCheck(FXObject* sender, FXSelector key, void* data);

	long onAbout(FXObject* sender, FXSelector key, void* data);
	long onWeb(FXObject* sender, FXSelector key, void* data);

	long onDeviceBox(FXObject* sender, FXSelector key, void* data);
	long onProjectType(FXObject* sender, FXSelector key, void* data);

	long onErrorNotify(FXObject* sender, FXSelector key, void* data);

	void loadOwner();
private:
	KDataFOXLibDlg();
	void updateDeviceCombo();
	int32 updateOptions();
	void handleError(int32 errCode);
	
	

private:
	FXComboBox *m_cmbDevice;
	KCDCapacityRule *m_rule;
	KFileList *m_fileList;
	//FXList *m_lbxLog;
	FXComboBox *m_cmbProjectType;
	FXMenuCheck* m_chkFinalize;
	FXMenuCheck* m_chkJoliet;
	FXMenuCheck* m_chkRockRidge;
	FXMenuCheck* m_chkVerify;
	FXMenuCheck* m_burnDevicesOnly;

	FXMenuCheck* m_chkAllowLowercaseNames;
	FXMenuCheck* m_chkAllowManyDirectories;
	FXMenuCheck* m_chkAllowLongISO9660Names;
	FXMenuCheck* m_chkAllowLongJolietNames;

	FXMenuCheck* m_chkBurnDevices;
	FXMenuCheck* m_chkDisableImage;

	FXint m_iSession;
	FXint m_iProjectType;

	FXint m_bEjectAfterBurn;
	FXint m_bJoliet;
	FXint m_bRockRidge;
	FXint m_bFinalize;
	FXint m_bVerify;
	FXint m_bAllowLowercaseNames;
	FXint m_bAllowManyDirectories; // more than 8 one in another.
	FXint m_bAllowLongISO9660Names;
	FXint m_bAllowLongJolietNames;

	FXDataTarget m_tgtEjectAfterBurn;
	FXDataTarget m_tgtJoliet;
	FXDataTarget m_tgtRockRidge;
	FXDataTarget m_tgtFinalize;
	FXDataTarget m_tgtAllowManyDirectories;
	FXDataTarget m_tgtAllowLowercaseNames;
	FXDataTarget m_tgtAllowLongISO9660Names;
	FXDataTarget m_tgtAllowLongJolietNames;

	FXCheckButton* m_chPathRule;
	
	FXListBox* m_lboxISOLevel;

	bool m_bMultideviceEnabled;
	bool m_bBurningDevicesOnly;

	FXString m_strStartupDir;
};

#endif
