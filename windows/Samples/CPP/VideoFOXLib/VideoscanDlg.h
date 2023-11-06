#ifndef _VIDEOSSCAN_DLG_H
#define _VIDEOSSCAN_DLG_H

class KVideoScanDlg: public FXDialogBox {
  FXDECLARE(KVideoScanDlg)

public:
  enum {
	ID_SETVIDEOSCANPROGRESS = FXDialogBox::ID_LAST,
	ID_VIDEOSCANCOMPLETE,
	ID_LAST
  };

  typedef struct {
	float progress; 
  } VIDEOSCANPROGRESSINFO;
  
  typedef struct {
	FXString strErrorString;
	FXint nErrorCode;
  } VIDEOSCANERRORINFO;  

public:
	KVideoScanDlg(FXApp *app, const FXString &title);
	~KVideoScanDlg();

	void OnVideoScannerEvent(float progress);
	void OnVideoScanDoneEvent(const FXString &strError, FXint nErrorCode, struct SVideoFormat CurrentFormat);	

	long onSetVideoScanProgress(FXObject* sender, FXSelector key, void* data);
	long onVideoScanComplete(FXObject* sender, FXSelector key, void* data);
	long onCmdCancel(FXObject* sender, FXSelector key, void* data);

	// Overrides
	virtual FXuint execute(FXuint placement = PLACEMENT_CURSOR);		

public:
	SFileToAdd m_fileToAdd;

	FXString m_strPlaytime;
	FXString m_strFrameRate;
	FXString m_strBitrate;
	FXString m_strAspectRatio;
	FXString m_strDimensions;

private:
	KVideoScanDlg();

private:
	FXProgressBar *m_barProgress;
	FXLabel *m_lbl;

	FXMessageChannel guisignal;

	VIDEOSCANPROGRESSINFO m_videoScanProgressInfo;
	VIDEOSCANERRORINFO m_videoScanErrorInfo;
};

#endif
