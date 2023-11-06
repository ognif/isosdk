#ifndef _DATAFOXLIB_DLG_H
#define _DATAFOXLIB_DLG_H
#include <vector>

#include "../Common/MaskAndMode.h"
using namespace MaskAndMode;

const int32 ABSOLUTE_START_TIME = -150; // First track's start address

class KMaskList;

class KRawFOXLibDlg: public FXDialogBox {
  FXDECLARE(KRawFOXLibDlg)

public:

  enum {
	ID_ADDFILE = FXDialogBox::ID_LAST,
	ID_WRITELOG,
	ID_ANALYZEFILE,

	ID_ADD_TRACK,
	ID_DELETE_TRACK,

	ID_RESETLIST,
	ID_RESET_FORM,

	ID_BURNDISK_DEVELOPED,
	ID_BURNDISK_FOXBURNER,
	ID_ERASEDISK,

	ID_MOUNTIMAGE,
	ID_UNMOUNTIMAGE,
	
	ID_ASPI_INTERNAL,
	ID_ASPI_WNASPI,
	ID_ASPI_FROGASPI,
	ID_RESCANDEVICES,
	ID_BURNDEVICES,
	ID_DISABLEIMAGE,

	ID_ABOUT,
	ID_WEB,

	ID_DEVICEBOX,
	
	ID_ERRORNOTIFY,
	ID_LAST
  };

  enum  DataFOXLibSelType {
	SEL_ERRORNOTIFY = SEL_LAST
  };

public:
	KRawFOXLibDlg(FXApp *app, const FXString &title);
	~KRawFOXLibDlg();

	long onAddFile(FXObject* sender, FXSelector key, void* data);
	long onAnalyzeFile(FXObject* sender, FXSelector key, void* data);
	long onWriteLogFile(FXObject* sender, FXSelector key, void* data);		

	long onAddTrack(FXObject* sender, FXSelector key, void* data);
	long onDeleteTrack(FXObject* sender, FXSelector key, void* data);
	long onResetList(FXObject* sender, FXSelector key, void* data);
	long onResetForm(FXObject* sender, FXSelector key, void* data);

	long onBurnDiskDeveloped(FXObject* sender, FXSelector key, void* data);
	long onBurnDiskFoxBurner(FXObject* sender, FXSelector key, void* data);
	long onEraseDisk(FXObject* sender, FXSelector key, void* data);

	long onMountImage(FXObject* sender, FXSelector key, void* data);
	long onUnmountImage(FXObject* sender, FXSelector key, void* data);
	long onBurnImage(FXObject* sender, FXSelector key, void* data);

	long onCmdAspi(FXObject* sender, FXSelector key, void* data);
	long onUpdAspi(FXObject* sender, FXSelector key, void* data);
	long onRescanDevices(FXObject* sender, FXSelector key, void* data);
	long onBurningDevices(FXObject* sender, FXSelector key, void* data);
	long onDisableImagewriter(FXObject* sender, FXSelector key, void* data);

	long onAbout(FXObject* sender, FXSelector key, void* data);
	long onWeb(FXObject* sender, FXSelector key, void* data);

	long onDeviceBox(FXObject* sender, FXSelector key, void* data);

	long onErrorNotify(FXObject* sender, FXSelector key, void* data);

	void loadOwner();
	
private:
	KRawFOXLibDlg();
	void updateDeviceCombo();
	int32 updateOptions();
	void handleError(int32 errCode);
	int64 AddTrackInfo(int32 nNumber, int32 nIndex, int64 nDiskOffset, int8 nTrackFormat, STrackInfo sTrack);
	
	template <class List>
	FXint insertUnique(List *list, FXString &str);//Insert only one enstance of string to list.
	
	void fillModes(FXComboBox *list); // Fill mode combobox

private:
	FXComboBox *m_cmbDevice;
	
	FXComboBox *m_cmbAddFile;
	FXComboBox *m_cmbTrackMode;

	KMaskList *m_listDatatypeMask;
	KMaskList *m_listIgnoreMask;

	FXSpinner *m_spnrTrackIndex;
	FXSpinner *m_spnrTrackNumber;

	FXTable* m_tblTrack;

	FXTextField *m_txtfieldStartAddress;
	FXTextField *m_txtfieldTrackLength;
	FXTextField *m_txtfieldOffset;

	FXMenuCheck* m_chkFinalize;
	FXMenuCheck* m_chkJoliet;
	FXMenuCheck* m_chkVerify;
	FXMenuCheck* m_chkEjectAfterBurn;

	FXMenuCheck* m_chkBurnDevices;
	FXMenuCheck* m_chkDisableImage;
	
	FXint m_bEjectAfterBurn;
	FXint m_bJoliet;
	FXint m_bFinalize;
	FXint m_bVerify;

	// Data targets to synchronize checkboxes in the menu and m_b* fields.

	FXDataTarget m_tgtEjectAfterBurn;
	FXDataTarget m_tgtVerifyAfterBurn;
	FXDataTarget m_tgtJoliet;
	FXDataTarget m_tgtFinalize;

	bool m_bMultideviceEnabled;
	bool m_bBurningDevicesOnly;

	FXString m_strStartupDir;

	// Vecotr of all tracks user have created.
	std::vector<SRAWTrackToAdd>	m_vTracks;
	// Time to start new track.
	int32 m_nAbsoluteTime;
};

#endif
