#ifndef _ImageEditFOXLIB_DLG_H
#define _ImageEditFOXLIB_DLG_H

#include "TreeNodes.h"

class KImageEditFOXLibDlg: public FXDialogBox {
  FXDECLARE(KImageEditFOXLibDlg)

public:
  enum {
	ID_ASPI_INTERNAL = FXDialogBox::ID_LAST,
	ID_ASPI_WNASPI,
	ID_ASPI_FROGASPI,
	ID_RESCANDEVICES,
	ID_BURNDEVICES,
	ID_DISABLEIMAGE,
	ID_WRITELOG,

	ID_ABOUT,
	ID_WEB,

	ID_SAVEIMAGE,
	ID_VERIFYDISC,

	ID_MOUNTIMAGE,
	ID_UNMOUNTIMAGE,	

	ID_DEVICEBOX,
	ID_LEFTPANEL,
	ID_RIGHTPANEL,

	ID_SECTOR_VIEW,
	ID_SCAN_SECTORS,
	ID_SHOW_PROPERTIES,
	ID_EXTRACT_TRACK,
	ID_EXTRACT_FILE,
	ID_EXTRACT_SYS,
	ID_VERIFY_DISCTYPE,
	ID_EXTRACT_FILE_EX,
	ID_LIST_CONTENT,

	ID_ERRORNOTIFY,

	
	ID_PLAY,
	ID_GRAB,
	ID_GRABALLTRACKS,

	ID_MD5,
	ID_MD5_CHECK,

	ID_READ_CDTEXT,
	ID_REFRESH,

	ID_READ_INDEXES,
	ID_READ_ISRC,

	ID_LAST
  };

  enum  ImageEditFOXLibSelType {
	SEL_ERRORNOTIFY = SEL_LAST
  };

public:
	KImageEditFOXLibDlg(FXApp *app, const FXString &title);
	~KImageEditFOXLibDlg();

	long onCmdAspi(FXObject* sender, FXSelector key, void* data);
	long onUpdAspi(FXObject* sender, FXSelector key, void* data);
	long onRescanDevices(FXObject* sender, FXSelector key, void* data);
	long onBurningDevices(FXObject* sender, FXSelector key, void* data);
	long onDisableImagewriter(FXObject* sender, FXSelector key, void* data);

	long onAbout(FXObject* sender, FXSelector key, void* data);
	long onWeb(FXObject* sender, FXSelector key, void* data);

	long onDeviceBox(FXObject* sender, FXSelector key, void* data);

	long onLeftPanelRightClick(FXObject* sender, FXSelector key, void* data);
	long onRightPanelRightClick(FXObject* sender, FXSelector key, void* data);
	long onRightPanelDblClick(FXObject* sender, FXSelector key, void* data);

	long onLeftPaneSelected(FXObject* sender, FXSelector key, void* data);
	long onSectorView(FXObject* sender, FXSelector key, void* data);
	long onScanSectors(FXObject* sender, FXSelector key, void* data);
	long onShowProperties(FXObject* sender, FXSelector key, void* data);
	long onExtractFiles(FXObject* sender, FXSelector key, void* data);
	long onExtractFilesEx(FXObject* sender, FXSelector key, void* data);
	long onVerifyCompressedAndEncrypt(FX::FXObject* sender, FX::FXSelector, void*);
	long onListContent(FXObject* sender, FXSelector key, void* data);
	
	long onExtractTrack(FXObject* sender, FXSelector key, void* data);
	FXuint doExtraction(int16 nTrackNumber, const FXString& strFilePath, unsigned int nFileFormat);

	long onErrorNotify(FXObject* sender, FXSelector key, void* data);

	long onMountImage(FXObject* sender, FXSelector key, void* data);
	long onUnmountImage(FXObject* sender, FXSelector key, void* data);
	
	long onSaveDisc(FXObject* sender, FXSelector key, void* data);
	long onVerifyDisc(FXObject* sender, FXSelector key, void* data);
	long onWriteLogFile(FXObject* sender, FXSelector key, void* data);

	long onPlay(FXObject* sender, FXSelector key, void* data);
	
	long onGrab(FXObject* sender, FXSelector key, void* data);
	long onGrabAll(FXObject* sender, FXSelector key, void* data);

	long onMD5(FXObject* sender, FXSelector key, void* data);
	long onMD5Check(FXObject* sender, FXSelector key, void* data);
	
	long onReadCDText(FXObject* sender, FXSelector key, void* data);
	long onReadIndexes(FXObject* sender, FXSelector key, void* data);
	long onReadISRC(FXObject* sender, FXSelector key, void* data);
	long onRefresh(FXObject* sender, FXSelector key, void* data);

	void create();
	void loadOwner();

private:
	typedef std::vector<ITreeNode*> NodeList;

	KImageEditFOXLibDlg();
	void updateDeviceCombo();
	void handleError(int32 errCode);
	void addLogLine(FXString strLogLine);

	void reloadLeftPanel();
	void reloadRightPanel();
	void buildNode(FXTreeItem* parent, ITreeNode* node);
	std::pair<FXIcon*,FXIcon*> getNodeIcons(GenericInfo::Icon iconType);

	void showPopupForNodes(NodeList& nodes, int x, int y);

	void RecursivePrintContent(FXFile &fContentList, ITreeNode* pcNode, FXString strFolderPath);

	FXString getCurrentImagePath() const;

private:
	FXComboBox *m_cmbDevice;

	FXMenuCheck* m_chkBurnDevices;
	FXMenuCheck* m_chkDisableImage;
	FXMenuCheck* burnDevicesOnly;

	FXTreeList* m_leftPanel;
	FXIconList*	m_rightPanel;
	FXIcon*		m_iconDisc;
	FXIcon*		m_iconAudio;
	FXIcon*		m_iconOpenDir;
	FXIcon*		m_iconCloseDir;
	FXIcon*		m_iconFile;
	FXIcon*     m_iconFileSystem;
	FXIcon*		m_iconPlay;
	FXIcon*		m_iconStop;
	FXIcon*		m_isosdkIconSmall;
	FXIcon*		m_isosdkIconBig;

	MediumNode* m_medium;

	bool m_bBurningDevicesOnly;
	int32 m_nAspiInterface;

	FXString m_strStartupDir;

	int32 ExtractTextFromHandle(int32 handle, int32 nTrackNumber, int32 nCDTCI, KString& rText);
};

#endif
