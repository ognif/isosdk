#ifndef TRACKLIST_H
#define TRACKLIST_H

//#include "KString.h"
#include "CDTextDlg.h"

class KTrackList : public FXIconList {

public:
	KTrackList(FXComposite *p, FXObject *tgt=NULL, FXSelector sel=0, FXuint opts=ICONLIST_NORMAL, FXint x=0, FXint y=0, FXint w=0, FXint h=0);
	~KTrackList();

	int  AddFile();
	int  DeleteItem();
	void ResetList();
	void Play();
	double GetAudioFileSizeEx();
	void TrackCDText();
	void DiskCDText();

	void SetRootDirectory(const KString& path);

protected:
	KTrackList() {}

	void handleError(int32 errCode);
private:
	KString				m_strRootDirectory;
	KFileAudioProperty	m_cdText;
};

#endif
