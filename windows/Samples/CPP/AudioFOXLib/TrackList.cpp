#include "stdafx.h"
#include "TrackList.h"
#include "CDTextDlg.h"
#include "AudioFOXLibDlg.h"
#include <sys/stat.h>
#include <cmath>

KTrackList::KTrackList(FXComposite *p, FXObject *tgt/* =NULL */, FXSelector sel/* =0 */, FXuint opts/* =ICONLIST_NORMAL */, FXint x/* =0 */, FXint y/* =0 */, FXint w/* =0 */, FXint h/* =0 */)
	:FXIconList(p, tgt, sel, opts, x, y, w, h)
{
	appendHeader("File name", NULL, 300);
	appendHeader("Play time", NULL, 100);

	m_strRootDirectory = _T(PATHSEPSTRING);
}

int KTrackList::AddFile()
{
#ifdef WIN32
	const FXchar patterns[] = "All Supported (*.mp3,*.mp4,*.m4a,*.aac,*.aif,*.aiff,*.aifc,*.wav,*.raw,*.sd2f,*.snd,*.au,*.ac3,*.caf,*.wv,*.ogg,*.oga,*.flac,*.ape,*.opus,*.wma)";
#endif
#ifdef MAC
	const FXchar patterns[]= "All Supported (*.mp3,*.mp4,*.m4a,*.aac,*.aif,*.aiff,*.aifc,*.wav,*.raw,*.sd2f,*.snd,*.au,*.ac3,*.caf,*.wv,*.ogg,*.oga,*.flac,*.ape,*.opus)";
	//const FXchar patterns[]= "All Supported (*.*)";
#endif
#ifdef LINUX
	const FXchar patterns[] = "All Supported (*.mp3,*.mp4,*.m4a,*.aac,*.aif,*.aiff,*.aifc,*.wav,*.raw,*.sd2f,*.snd,*.au,*.ac3,*.caf,*.wv,*.ogg,*.oga,*.flac,*.ape,*.opus)";
#endif

	FXFileDialog dlg(getApp(), "Select audio files");
	dlg.setSelectMode(SELECTFILE_MULTIPLE);
	dlg.setPatternList(patterns);
	

	int total_time = 0;

	if (dlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(dlg.getDirectory());
		FXString *pFilePath = dlg.getFilenames();

		while (pFilePath && !pFilePath->empty())
		{
			KString strTmpPath = Fox2SDKString(FXString::compose(*pFilePath, true)); 

			int32 res;

			SFileToAdd fta;
			fta.lpszSourceFilePath = strTmpPath;
			fta.lpszDestinationPath = m_strRootDirectory;
			fta.nSavePath = BS_DONT_SAVE_PATH;
			fta.bVideoFile = BS_FALSE;

			res = ::AddFile(fta);
  			handleError(res);

			if (BS_SDK_ERROR_NO == res)
			{
				double fSec = 0.0;
				::GetPrecisePlayTime(strTmpPath, &fSec);

				int32 sec = int32(ceil(fSec));

				FXString strTime;
				strTime.format("%02d:%02d:%02d", sec/3600, (sec%3600)/60, sec%60);

				FXString strItem = *pFilePath+ "\t" + strTime;

				FXString strName = FXString::compose(FXPath::name(*pFilePath), false);
				KString strTmpName = Fox2SDKString(strName);
				KFileAudioProperty *pinfo = new KFileAudioProperty(strTmpName);
				pinfo->nPlayTime = sec;

				appendItem(strItem, NULL, NULL, pinfo);

				total_time += sec;
			}

			++pFilePath;
		}
	}

	return total_time;
}

int KTrackList::DeleteItem()
{
	int total_time = 0;

	for (FXint i = getNumItems()-1; i >= 0; --i)
	{
		if (isItemSelected(i))
		{
			FXString strItem = getItemText(i);
			FXint pos = strItem.find('\t');
			if (0 < pos)
			{
				KString strTmpPath = KStringFormat(L"%02d", i+1);

				SFileToRemove file;
				file.lpszFile = strTmpPath;
				file.lpszDestinationPath = m_strRootDirectory;

				int32 res = ::RemoveFile(file);
				handleError(res);

				if (BS_SDK_ERROR_NO == res)
				{
					KFileAudioProperty *pinfo = (KFileAudioProperty*)getItemData(i);
					int32 sec = pinfo->nPlayTime;

					if (pinfo) delete pinfo;

					removeItem(i);

					total_time -= sec;
				}
			}
		}
	}
	return total_time;
}

void KTrackList::ResetList()
{
	for (FXint i=0; i< getNumItems(); ++i) {
		KFileAudioProperty *pinfo = (KFileAudioProperty*)getItemData(i);
		if (pinfo) delete pinfo;
	}

	clearItems();
}

void KTrackList::TrackCDText()
{
	FXint indx = getCurrentItem();

	if (-1 < indx)
	{
		KFileAudioProperty *pinf = (KFileAudioProperty*)getItemData(indx);
		if (pinf)
		{
			KFileAudioProperty prp = *pinf;
			KCDTextDlg dlg(getApp(), "Track Properties", false);
			prp.SetTrackNumber(indx+1);
			dlg.SetFileProperty(&prp);
			if (dlg.execute()) {
				int32 res = ::SetAudioFileProperty(prp.data);
				handleError(res);
				if (res == BS_SDK_ERROR_NO) {
					*pinf = prp;
				}
			}
		}
	}
}

void KTrackList::DiskCDText()
{
	KCDTextDlg dlg(getApp(), "Disk properties", true);
	KFileAudioProperty prp = m_cdText;
	prp.strSourceFilePath = m_strRootDirectory;
	dlg.SetFileProperty(&prp);

	if (dlg.execute()) {
		int32 res = ::SetAudioFileProperty(prp.data);
		handleError(res);
		if (res == BS_SDK_ERROR_NO) {
			m_cdText = prp;
		}
	}
}

void KTrackList::Play()
{
	FXint indx = getCurrentItem();

	if (-1 < indx)
	{
		FXString strItem = getItemText(indx);
		FXint pos = strItem.find('\t');
		if (0 < pos)
		{
			FXString strFilePath = strItem.left(pos);
			KString strTmpFilePath = Fox2SDKString(strFilePath);
			int32 res = ::PlayAudioFile(strTmpFilePath);
			handleError(res);
		}
	}
}

double KTrackList::GetAudioFileSizeEx()
{
	double fSize = 0.0;
	FXint indx = getCurrentItem();
	if (-1 < indx)
	{
		FXString strItem = getItemText(indx);
		FXint pos = strItem.find('\t');
		if (0 < pos)
		{
			FXString strFilePath = strItem.left(pos);
			KString strTmpFilePath = Fox2SDKString(strFilePath);
			int32 res = ::GetAudioFileSize(strTmpFilePath, &fSize);
			handleError(res);
		}
	}

	return fSize;
}

KTrackList::~KTrackList()
{
	ResetList();
}

void KTrackList::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		getTarget()->handle(this, FXSEL(KAudioFOXLibDlg::SEL_ERRORNOTIFY, 0), IntToPvoid(errCode));
	}
}

void KTrackList::SetRootDirectory(const KString& path)
{
    m_strRootDirectory = path;
}
