#ifndef _AUDIOFOXLIB_DLG_H
#define _AUDIOFOXLIB_DLG_H

#include "CDTimeRule.h"

class KTrackList;
class KFileList;

class KAudioFOXLibDlg: public FXDialogBox {
  FXDECLARE(KAudioFOXLibDlg)

public:
	enum {
		ID_ADDAUDIOFILE = FXDialogBox::ID_LAST,
		ID_DELETEAUDIOITEM,
		ID_RESETLIST,

		ID_ADDDATAFILE,
		ID_ADDDATAFOLDER,
		ID_RENAMEFILE,
		ID_DELETEDATAITEM,
		ID_WRITELOG,

		ID_BURNDISK_DEVELOPED,
		ID_BURNDISK_FOXBURNER,
		ID_ERASEDISK,
		ID_VERIFY,

		ID_PLAY,
		ID_STOPPLAY,
        ID_PLUGIN1,
		ID_DISKTEXT,
		ID_TRACKTEXT,
		ID_AUDIOFILESIZE,
		ID_DISKSIZE,

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
		ID_TRACKLIST,
		ID_FILELIST,

		ID_LAST
	};

	enum  AudioFOXLibSelType {
		SEL_ERRORNOTIFY = SEL_LAST
	};

public:
	KAudioFOXLibDlg(FXApp *app, const FXString &title);
	~KAudioFOXLibDlg();

	long onAddAudioFile(FXObject* sender, FXSelector key, void* data);
	long onDeleteAudioItem(FXObject* sender, FXSelector key, void* data);
	long onResetList(FXObject* sender, FXSelector key, void* data);

	long onAddDataFile(FXObject* sender, FXSelector key, void* data);
	long onAddFolder(FXObject* sender, FXSelector key, void* data);
	long onRenameFile(FXObject* sender, FXSelector key, void* data);
	long onDeleteDataItem(FXObject* sender, FXSelector key, void* data);
	long onWriteLogFile(FXObject* sender, FXSelector key, void* data);

	long onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data);
	long onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data);
	long onEraseDisk(FXObject* sender, FXSelector key, void* data);
	long onVerifySelect(FXObject* sender, FXSelector key, void* data);

	long onPlay(FXObject* sender, FXSelector key, void* data);
    long onLoadPlugin1(FXObject* sender, FXSelector key, void* data);
	long onAudioFileSize(FXObject* sender, FXSelector key, void* data);
	long onDiskSize(FXObject* sender, FXSelector key, void* data);
	long onStopPlay(FXObject* sender, FXSelector key, void* data);
	long onDiskText(FXObject* sender, FXSelector key, void* data);
	long onTrackText(FXObject* sender, FXSelector key, void* data);

	long onCmdAspi(FXObject* sender, FXSelector key, void* data);
	long onUpdAspi(FXObject* sender, FXSelector key, void* data);
	long onRescanDevices(FXObject* sender, FXSelector key, void* data);
	long onBurningDevices(FXObject* sender, FXSelector key, void* data);
	long onDisableImagewriter(FXObject* sender, FXSelector key, void* data);

	long onAbout(FXObject* sender, FXSelector key, void* data);
	long onWeb(FXObject* sender, FXSelector key, void* data);

	long onDeviceBoxChange(FXObject* sender, FXSelector key, void* data);
	long onProjectTypeChange(FXObject* sender, FXSelector key, void* data);

	long onErrorNotify(FXObject* sender, FXSelector key, void* data);

	void loadOwner();

private:
	KAudioFOXLibDlg();
	void updateDeviceCombo();
	int32 updateOptions();
	void handleError(int32 errCode);

private:
	FXComboBox *m_cmbDevice;
	KCDTimeRule *m_rule;
	KTrackList* m_trackList;
	KFileList* m_fileList;
	FXComboBox* m_cmbProjectType;
	FXTabItem*  m_dataTab;

	FXMenuCascade* m_dataMenu;
	FXMenuCheck* m_chkVerify;
	FXMenuCheck* m_chkJoliet;
	FXMenuCheck* m_chkRockRidge;
	FXMenuCheck* m_chkFinalize;
	FXMenuCheck* m_chkWriteCDTextInUnicode;
	FXMenuCheck* burnDevicesOnly;

	FXMenuCheck* m_chkAllowLowercaseNames;
	FXMenuCheck* m_chkAllowManyDirectories;

	int32 m_iProjectType;
	FXint m_bEjectAfterBurn;
	FXint m_bJoliet;
	FXint m_bRockRidge;
	FXint m_bVerify;
	FXint m_bFinalize;
	FXint m_bWriteCDTextInUnicode;
	FXint m_bAllowLowercaseNames;
	FXint m_bAllowManyDirectories; // more than 8 one in another.


	FXDataTarget m_tgtEjectAfterBurn;
	FXDataTarget m_tgtJoliet;
	FXDataTarget m_tgtRockRidge;
	FXDataTarget m_tgtFinalize;
	FXDataTarget m_tgtWriteCDTextInUnicode;
	FXDataTarget m_tgtAllowManyDirectories;
	FXDataTarget m_tgtAllowLowercaseNames;

	FXListBox* m_lboxISOLevel;

	bool m_bMultideviceEnabled;
	bool m_bBurningDevicesOnly;

	FXString m_strStartupDir;
};

#endif
