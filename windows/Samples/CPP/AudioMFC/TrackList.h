#ifndef TRACKLIST_H
#define TRACKLIST_H

#include "CDTextDlg.h"

class CTrackList : public CListCtrl 
{

public:
	CTrackList();
	~CTrackList();

	void Init(CWinApp& theApp);
	int  AddFile();
	int  DeleteSelectedItems();
	void ResetList();
	void Play();
	double GetAudioFileSizeEx();
	void TrackCDText();
	void DiskCDText();

	void SetRootDirectory(const CString& path);

protected:

	void HandleError(int32 errCode);
	afx_msg void OnDestroy();

	CString				m_strRootDirectory;
	CFileAudioProperty	m_cdText;

	DECLARE_MESSAGE_MAP()
};

#endif