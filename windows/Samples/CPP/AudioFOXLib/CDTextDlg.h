#ifndef _KCDTEXT_DLG_H_
#define _KCDTEXT_DLG_H_

#include <vector>

struct KFileAudioProperty
{
	KFileAudioProperty();
	KFileAudioProperty(const KFileAudioProperty &prp);
	KFileAudioProperty(const KString &filePath);

	void SetTrackNumber(int nTrack);

	void UpdateData();

	SFileAudioProperty data;

	KString strSourceFilePath;
	KString strTitle;
	KString strPerformer;
	KString strSongWriter;
	KString strComposer;
	KString strArranger;
	KString strMessage;	
	KString strMCNISRC;
	int32	nPlayTime;
	std::vector<int32> vIndexes;
};

class KCDTextDlg: public FXDialogBox {
  FXDECLARE(KCDTextDlg)

public:
	enum {
		ID_ACCEPT = FXDialogBox::ID_LAST,
		ID_RESET,
		ID_ADD_INDEX,
		ID_DELETE_INDEX,
		ID_LAST
	};

public:
	KCDTextDlg(FXApp *app, const FXString &title, bool disc);
	~KCDTextDlg() {}

	void SetFileProperty(KFileAudioProperty *pInfo);

	long onCmdReset(FXObject* sender, FXSelector key, void* data);
	long onCmdAccept(FXObject* sender, FXSelector key, void* data);
	long onCmdAddIndex(FXObject* sender, FXSelector key, void* data);
	long onCmdDeleteIndex(FXObject* sender, FXSelector key, void* data);

protected:
	KCDTextDlg() {}
	void CreateCDTextTab();
	void CreateIndexesTab();

private:	
	bool     m_bDiscText;
	FXString m_strArranger;
	FXString m_strComposer;
	FXString m_strSongWriter;
	FXString m_strPerformer;
	FXString m_strMessage;
	FXString m_strTitle;
	FXString m_strMCN_ISRC;
	FXint m_nPause;
	FXint m_nPauseInFrames;


	FXDataTarget tgtArranger;
	FXDataTarget tgtComposer;
	FXDataTarget tgtSongWriter;
	FXDataTarget tgtPerformer;
	FXDataTarget tgtMessage;
	FXDataTarget tgtTitle;
	FXDataTarget tgtMCN_ISRC;
	FXDataTarget tgtPause;
	FXDataTarget tgtPauseInFrames;

	FXDataTarget tgtMinute;
	FXDataTarget tgtSecond;
	FXDataTarget tgtFrame;

	FXint m_nMin;
	FXint m_nSec;
	FXint m_nFrame;

	KFileAudioProperty *m_pFileInfo;

	FXTabBook*	m_tabs;
	FXList*		m_lstIndexes;
};

#endif
