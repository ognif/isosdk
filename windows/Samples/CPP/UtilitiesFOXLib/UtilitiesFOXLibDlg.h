#ifndef _UTILITIESFOXLIB_DLG_H
#define _UTILITIESFOXLIB_DLG_H

#include <map>

class KUtilitiesFOXLibDlg: public FXDialogBox {
  FXDECLARE(KUtilitiesFOXLibDlg)

public:
	enum {
		ID_ISREADY = FXDialogBox::ID_LAST,
		ID_EJECTTRAY,
		ID_CLOSETRAY,
		ID_LOCKDEVICE,
		ID_UNLOCKDEVICE,
		ID_GETDRIVEINFO,
		ID_GETDRIVEINFOEX,
		ID_GETCAPABILITIES,
		ID_SETREGIONCODE,
		ID_WRITELOG,

		ID_GETDISKINFO,
		ID_ERASEDISK,

        ID_ASPI_INTERNAL,
		ID_ASPI_WNASPI,
		ID_ASPI_FROGASPI,
		ID_RESCANDEVICES,
		ID_BURNDEVICES,
		ID_DISABLEIMAGE,

		ID_MOUNTIMAGE,
		ID_UNMOUNTIMAGE,

		ID_ABOUT,
		ID_WEB,

		ID_DEVICEBOX,
		ID_CLOSESESSION,

		ID_BROWSE_TEXT_BOX,
		ID_BROWSEDEST_BTN,
		ID_CHECKFORMAT_BTN,
		ID_EXECUTEIMAGE_BTN,
		ID_DISCCOPY_BTN,
		ID_FORMATBOX_CMB,
		ID_SOURCEDEV_CMB,
		ID_ABORT_IMG_BTN,
		ID_ABORT_DSC_BTN,

		ID_VERIFYSECTOR_IMG,
		ID_VERIFYSTART_IMG,
		ID_VERIFYDONE_IMG,
		ID_VERIFYSECTOR_CPY,
		ID_VERIFYSTART_CPY,
		ID_VERIFYDONE_CPY,
		ID_SETPROGRESS_IMG,
		ID_SETPROGRESS_DSC,
		ID_JOBDONE_IMG,
		ID_JOBDONE_DSC,
		ID_BURNDONE_IMG,
		ID_BURNDONE_DSC,

		ID_SOURCE_DEVICEBOX,

		ID_ADDLOGLINE,
		ID_ERRORNOTIFY,
		ID_LAST
	};

	enum State
	{
		ST_NONE,
		ST_IMAGE_CREATION,
		ST_DISC_COPY,		
	};

protected:
	struct PROGRESSINFO 
	{
		int progress; 
		double size;
		double current;
		int errors;
		double vcurrentsector;
		double sectors;
		bool success;
	};

public:
	KUtilitiesFOXLibDlg(FXApp *app, const FXString &title);
	~KUtilitiesFOXLibDlg();

	long onIsReady(FXObject* sender, FXSelector key, void* data);
	long onEjectTray(FXObject* sender, FXSelector key, void* data);
	long onCloseTray(FXObject* sender, FXSelector key, void* data);
	long onLockDevice(FXObject* sender, FXSelector key, void* data);
	long onUnlockDevice(FXObject* sender, FXSelector key, void* data);
	long onGetDriveInfo(FXObject* sender, FXSelector key, void* data);
	long onGetDriveInfoEx(FXObject* sender, FXSelector key, void* data);
	long onGetCapabilities(FXObject* sender, FXSelector key, void* data);
	long onSetRegionCode(FXObject* sender, FXSelector key, void* data);
	long onWriteLogFile(FXObject* sender, FXSelector key, void* data);

	long onGetDiskInfo(FXObject* sender, FXSelector key, void* data);
	long onEraseDisk(FXObject* sender, FXSelector key, void* data);

	long onCmdAspi(FXObject* sender, FXSelector key, void* data);
	long onUpdAspi(FXObject* sender, FXSelector key, void* data);
	long onRescanDevices(FXObject* sender, FXSelector key, void* data);
	long onBurningDevices(FXObject* sender, FXSelector key, void* data);
	long onDisableImagewriter(FXObject* sender, FXSelector key, void* data);

	long onAbout(FXObject* sender, FXSelector key, void* data);
	long onWeb(FXObject* sender, FXSelector key, void* data);

	long onDeviceBoxChange(FXObject* sender, FXSelector key, void* data);
	long onCloseSession(FXObject* sender, FXSelector key, void* data);
	long onAddLogLine(FXObject* sender, FXSelector key, void* data);
	long onErrorNotify(FXObject* sender, FXSelector key, void* data);

	long onCheckFormat(FXObject* sender, FXSelector key, void* data);
	long onAbortImage(FXObject* sender, FXSelector key, void* data);
	long onBtnImageBrowse(FXObject* sender, FXSelector key, void* data);

	long onAbortDisc(FXObject* sender, FXSelector key, void* data);
	long onSourceDeviceBoxChange(FXObject* sender, FXSelector key, void* data);

	long onExecuteImageCreate(FXObject* sender, FXSelector key, void* data);
	long onExecuteDiscCopy(FXObject* sender, FXSelector key, void* data);

	long onSetVerifyStartImg(FXObject* sender, FXSelector key, void* data);
	long onSetVerifySectorImg(FXObject* sender, FXSelector key, void* data);
	long onSetVerifyDoneImg(FXObject* sender, FXSelector key, void* data);
	long onSetVerifyStartCpy(FXObject* sender, FXSelector key, void* data);
	long onSetVerifySectorCpy(FXObject* sender, FXSelector key, void* data);
	long onSetVerifyDoneCpy(FXObject* sender, FXSelector key, void* data);
	long onSetProgressImg(FXObject* sender, FXSelector key, void* data);
	long onSetProgressDsc(FXObject* sender, FXSelector key, void* data);
	long onJobDoneImg(FXObject* sender, FXSelector key, void* data);
	long onJobDoneDsc(FXObject* sender, FXSelector key, void* data);

	long onBurnDoneImg(FXObject* sender, FXSelector key, void* data);
	long onBurnDoneDsc(FXObject* sender, FXSelector key, void* data);

	long onMountImage(FXObject* sender, FXSelector key, void* data);
	long onUnmountImage(FXObject* sender, FXSelector key, void* data);
	
	void loadOwner();

private:
	KUtilitiesFOXLibDlg();
	void updateDeviceCombo();
	void handleError(int32 errCode,const KString strPrefix = _T("")); 
	void addLogLine(FXString strLogLine);
	void createCapabilitiesPage(FXVerticalFrame* frame);
	void createMediumPage(FXVerticalFrame* frame);
	void createImagePage(FXVerticalFrame* frame);
	void createCopydiscPage(FXVerticalFrame* frame);

protected:
	static void OnJobDoneEvent(KUtilitiesFOXLibDlg*);
	static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesWritten, double dImageSize, KUtilitiesFOXLibDlg *pDlg);
	static void OnBurnDoneEvent(const TCHAR* pcError, KUtilitiesFOXLibDlg*);
	static void OnVerifySectorEvent(double nSector, double tSector, bool nSuccess, KUtilitiesFOXLibDlg *pDlg);
	static void OnStartVerifyEvent(KUtilitiesFOXLibDlg *pDlg);
	static void OnVerifyDoneEvent(int nNumErrors, KUtilitiesFOXLibDlg *pDlg);

	void SetProgress(int progress, double size, double curren, int errors);
	void SetVerifySector(double nSector, double tSector, bool nSuccess);
	void SetVerifyStart();
	void SetVerifyDone(int error);
	void OnJobDone();
	void OnBurnDone(const TCHAR* pcError);
	void CheckFormat();
	void CheckDiscWriteMethod();
	void UpdateSourceDeviceCombo();
	bool UpdateImageReadDevice();
	void UpdateDriveInfo();
	void UpdateDriveInfoEx();
	void UpdateDriveCapabilities();
	void UpdateMediumInfo();

public:
	void EnableControlsImg(bool bEnable);
	void EnableControlsDsc(bool bEnable);

private:
	FXComboBox*			m_cmbDevice;
	FXTabBook*			m_tabs;

	// Device Info tab
	FXLabel*		m_lblDiskType;
	FXLabel*		m_lblMaxBurnSpeed;
	FXLabel*		m_lblMaxReadSpeed;
	FXLabel*		m_lblUnderrunProtection;
	FXLabel*		m_lblTestWrite;
	FXLabel*		m_lbljobState;
	FXLabel*		m_lblVerifySectors;

	FXMenuCheck* burnDevicesOnly;
	FXMenuCheck* imagewriter;

	// Device InfoEx tab
	FXIconList*		m_lstInfoEx;

	// Capabilities tab
	typedef std::map<int64, FXCheckButton*> CapsMap;
	CapsMap		m_mCaps;

	// Medium tab
	FXLabel*	m_lblMedium;
	FXLabel*	m_lblMediumStatus;
	FXLabel*	m_lblLastSession;
	FXLabel*	m_lblMediumSize;
	FXLabel*	m_lblMediumUsed;
	FXLabel*	m_lblMediumFree;
	FXLabel*	m_lblMediumSessions;
	FXLabel*	m_lblMediumTracks;
	FXLabel*	m_lblMediumVendorID;
	FXLabel*	m_lblMediumMaxWriteSpeed;
	FXLabel*	m_lblMediumCatalogCode;
	FXButton*	m_btnCloseSession;
	FXTreeList* m_lstSessions;

	FXTextField*	m_txtBrowseBoxImg;
	FXTextField*	m_txtSetorsListPathImg;
	FXButton*		m_btnBrowseDestImg;
	FXButton*		m_btnCheckFormatImg;
	FXButton*		m_btnExecuteImg;
	FXButton*		m_btnAbortImg;
	FXComboBox*		m_cmbFormatImg;
	FXCheckButton*	m_chbCreateImg;
	FXCheckButton*	m_chbVerifyImg;
	FXCheckButton*	m_chbErrorCorrectImg;	
	FXCheckButton*	m_chbBadSectListImg;
	FXCheckButton*	m_chbBlankBadImg;
	FXSpinner*		m_spnHardwareImg;
	FXSpinner*		m_spnSoftwareImg;
	FXLabel*		m_lblTtlSectorsImg;
	FXLabel*		m_lblReadErrorsImg;
	FXLabel*		m_lblSectorsImg;
	FXLabel*		m_lbStateImg;
	FXLabel*		m_lblCurrentSectorImg;
	FXLabel*		m_lblPercentageImg;
	FXProgressBar*	m_barProgressImg;

	FXCheckButton*	m_chbErrorCorrectDsc;
	FXComboBox*		m_cmbSourceDevDsc;
	FXSpinner*		m_spnHardwareDsc;
	FXSpinner*		m_spnSoftwareDsc;	
	FXComboBox*		m_cmbWMethodDsc;
	FXComboBox*		m_cmbRModeDsc;
	FXCheckButton*	m_chbAutoErase;
	FXCheckButton*	m_chbVerifyDsc;
	FXCheckButton*	m_chbEjectDsc;
	FXButton*		m_btnExecuteDsc;
	FXButton*		m_btnAbortDsc;
	FXLabel*		m_lblTtlBytesDsc;	
	FXLabel*		m_lblBytesWrittenDsc;
	FXLabel*		m_lblPercentageDsc;
	FXProgressBar*	m_barProgressDsc;
		

	bool m_bMultideviceEnabled;
	bool m_bBurningDevicesOnly;

	FXString m_strStartupDir;

	PROGRESSINFO m_progInfo;
	FXMessageChannel guisignal;

	FXString m_strBurnError;

	State m_EState;
	
};

#endif
