#include "stdafx.h"
#include "FileTreeFoxLib.h"
#include <sys/stat.h>
#include <sys/types.h>

#ifdef LINUX
typedef time_t	__time64_t;
typedef struct stat __stat64;

#define _time64 time
#define _gmtime64 gmtime
#define _localtime64 localtime
#define _fstat64 fstat
#define _stat64 stat
#endif


/* created by reswrap from file bigfolder.gif */
extern const unsigned char bigfolder[]={
  0x47,0x49,0x46,0x38,0x39,0x61,0x20,0x00,0x20,0x00,0xb3,0x00,0x00,0xfc,0xfe,0xfc,
  0x9c,0x9e,0x04,0x04,0x02,0x04,0xfc,0xfe,0xa4,0xcc,0xce,0x64,0xf5,0xd0,0x92,0x34,
  0x32,0x04,0xfc,0xce,0xcc,0xde,0xc7,0x7c,0xd1,0xba,0x78,0xa0,0x57,0x67,0x00,0x00,
  0x00,0x8c,0x00,0x00,0x18,0x11,0x20,0x00,0x00,0x00,0x2d,0x48,0x10,0x21,0xf9,0x04,
  0x01,0x00,0x00,0x00,0x00,0x2c,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x00,0x00,0x04,
  0xca,0x10,0xc8,0x49,0xab,0xbd,0x38,0xeb,0x2d,0x83,0xff,0x9f,0xc0,0x65,0x01,0x30,
  0x9c,0xe8,0x19,0x88,0x63,0x55,0xa6,0xf0,0xb0,0xb6,0xd3,0x1b,0xc3,0x73,0x1b,0x10,
  0x7c,0xef,0xff,0xa0,0x60,0xb0,0x43,0x6b,0x89,0x6c,0xb7,0xe4,0xa9,0xb0,0x44,0x31,
  0x09,0x02,0xa4,0x72,0xc0,0xac,0x3a,0xaf,0x05,0x82,0x41,0x3a,0x8d,0x31,0xa9,0xdf,
  0x81,0x96,0xdb,0xb5,0x36,0x9d,0x63,0x93,0xd2,0x1a,0x86,0xb1,0xd3,0x5d,0x37,0x75,
  0x1e,0x7e,0x6e,0xd5,0xde,0x54,0xfb,0x0a,0xa6,0xc2,0xa7,0x5f,0x66,0x81,0x57,0x7f,
  0x7a,0x65,0x73,0x7d,0x7e,0x77,0x49,0x6c,0x7d,0x6d,0x81,0x76,0x52,0x7b,0x8c,0x8e,
  0x05,0x55,0x85,0x7c,0x74,0x9a,0x88,0x90,0x59,0x8b,0x94,0x86,0x96,0x95,0x73,0x70,
  0x82,0x9c,0x88,0x4e,0x96,0x55,0x07,0x96,0x98,0x72,0x74,0x55,0x75,0xaa,0x8a,0x36,
  0xa6,0x4d,0x83,0x60,0x82,0x9e,0x25,0x7b,0x90,0xb7,0x4b,0x05,0x07,0xb9,0xc1,0x05,
  0x08,0x9f,0x9b,0xbe,0xb1,0xc0,0x4c,0xac,0xad,0x77,0x8d,0x9b,0xc8,0x6c,0xa2,0xbb,
  0x3f,0xd6,0xd7,0x04,0x08,0x3e,0xda,0x04,0x09,0x3c,0x06,0x00,0x06,0xe2,0xe3,0xe4,
  0xe5,0xe6,0xe7,0xe2,0x45,0xea,0xeb,0xec,0xed,0x17,0x11,0x00,0x3b
  };

/* created by reswrap from file minifolder.gif */
const unsigned char minifolder[]={
  0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x10,0x00,0xa2,0x00,0x00,0xff,0xff,0xff,
  0x9c,0x9c,0x00,0x00,0x00,0x00,0xf7,0xf7,0xf7,0xff,0xff,0xce,0xff,0xff,0x9c,0xce,
  0xce,0x63,0xff,0xce,0x9c,0x21,0xf9,0x04,0x01,0x00,0x00,0x00,0x00,0x2c,0x00,0x00,
  0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x03,0x46,0x08,0xba,0xdc,0x1c,0x10,0x0a,0xb7,
  0xc2,0x20,0xa4,0x94,0x30,0x5d,0x30,0x60,0x68,0x44,0x91,0x12,0x60,0x68,0x8a,0x15,
  0xc6,0x74,0x6a,0x70,0x5c,0x1c,0x2d,0xf0,0xca,0x73,0x5e,0xdf,0xf8,0x31,0xef,0x99,
  0x98,0x6f,0xc8,0x72,0x05,0x85,0x39,0x9a,0x11,0x46,0x1c,0x2a,0x6d,0x84,0x66,0xf2,
  0xf0,0xfc,0x88,0xae,0xa1,0x8e,0x60,0xcb,0xed,0x76,0x29,0xe0,0x30,0x38,0x01,0x00,
  0x3b
  };


/* created by reswrap from file minidoc.gif */
const unsigned char minidoc[]={
  0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x10,0x00,0xa2,0x00,0x00,0xff,0xff,0xff,
  0x80,0x80,0x80,0xff,0xff,0xff,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0xf9,
  0x1a,0x20,0x04,0x08,0x06,0x21,0xf9,0x04,0x01,0x00,0x00,0x00,0x00,0x2c,0x00,0x00,
  0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x03,0x36,0x08,0x10,0xdc,0xae,0x70,0x89,0x49,
  0xe7,0x08,0x51,0x56,0x3a,0x04,0x86,0xc1,0x46,0x11,0x24,0x01,0x8a,0xd5,0x60,0x2a,
  0x21,0x6a,0xad,0x9a,0xab,0x9e,0xae,0x30,0xb3,0xb5,0x0d,0xb7,0xf2,0x9e,0xdf,0x31,
  0x14,0x90,0x27,0xf4,0xd5,0x86,0x83,0xa4,0x72,0x09,0x2c,0x39,0x9f,0xa6,0x04,0x00,
  0x3b
  };

FXDEFMAP(KFileList) KFileListMap[]= {
	FXMAPFUNC(SEL_DOUBLECLICKED, 0, KFileList::onDoubleClicked)
};

FXIMPLEMENT(KFileList, FXIconList, KFileListMap, ARRAYNUMBER(KFileListMap))

KFileList::KFileList(FXComposite *p, FXObject *tgt, FXSelector sel, FXuint opts, FXint x, FXint y, FXint w, FXint h)
	: FXIconList(p, tgt, sel, opts, x, y, w, h)
	, m_strRootDirectory(PATHSEPSTRING)
{
	appendHeader("Name", NULL, 200);
	appendHeader("Size", NULL, 60);
	appendHeader("Modified Date", NULL, 150);
	appendHeader("Origin", NULL, 200);

	mini_folder = new FXGIFIcon(getApp(), minifolder);
	mini_folder->create();

	mini_doc = new FXGIFIcon(getApp(), minidoc);
	mini_doc->create();

	SelectDirectory(m_strRootDirectory);
}

KFileList::~KFileList()
{
	clearItems();
}

void KFileList::RefreshList()
{
	SelectDirectory(m_strCurDirectory);
}

void KFileList::SelectDirectory(const FXString &strPath)
{
	
	clearItems();

	m_strCurDirectory = strPath;

	KString strTmp = Fox2SDKString(strPath);

	HSESSION hSession;
	int32 res = ::OpenDiskSession(BS_CURRENT_DEVICE, 0, &hSession);
	handleError(res);

	HDIR hDirectory;
	res = ::OpenDirectory(hSession, strTmp, &hDirectory);
	handleError(res);

	SFileEntry entry;

	if (m_strRootDirectory != strPath) {
		appendItem("..", mini_folder, mini_folder, NULL);
	}

	int32 nDirSize = 0;
	res = ::GetNumberOfFiles(hDirectory, &nDirSize);
	handleError(res);

	for(int32 nIndex = 0; nIndex < nDirSize; ++nIndex)
	{
		::ReadDirectory(hDirectory, nIndex, &entry);

		FXString strName = SDK2FoxString(entry.lpszFileName);

		FXString strSize;
		int64 size;

		if (0 != (BS_FA_DIRECTORY & entry.nAttrib)) {
			FXString strDirPath = m_strCurDirectory;
			if (strDirPath != PATHSEPSTRING)
				strDirPath += PATHSEPSTRING;
			strDirPath += strName;
            size = GetDirectorySize(strDirPath);
		} else {
			size = entry.nFileSize;
		}

		if (size > 1024*1024) {
			size = size / (1024*1024);
			strSize.format("%d MB", size);
		} 
		else if (size > 1024) {
			strSize.format("%d KB", size/1024);
		}
		else {
			strSize.format("%d B", size);
		}

		FXString strDate;
		strDate.format("%02d.%02d.%04d %02d:%02d:%02d",
			entry.cDateTime.nDay,
			entry.cDateTime.nMonth,
			entry.cDateTime.nYear + 1900,
			entry.cDateTime.nHour,
			entry.cDateTime.nMinute,
			entry.cDateTime.nSecond);

		FXString strOrigin = SDK2FoxString(entry.lpszFileOrigin);

		FXString strItem = strName + '\t' + strSize + '\t' + strDate + '\t' + strOrigin;

		SFileEntry *userData = new SFileEntry;
		memcpy(userData, &entry, sizeof(SFileEntry));

		FXIcon *icon = (BS_FA_DIRECTORY & entry.nAttrib) ? mini_folder : mini_doc;

		appendItem(strItem, icon, icon, userData);
	}


	res = ::CloseDirectory(hDirectory);
	handleError(res);

	res = ::CloseDiskSession(hSession);
	handleError(res);
}

void KFileList::AddFile(int32 savePath)
{
	FXFileDialog fileDlg(this->getOwner(), "Add file");
	fileDlg.setSelectMode(SELECTFILE_MULTIPLE_ALL);
	fileDlg.setDirectory(FXSystem::getCurrentDirectory());

	if (fileDlg.execute())
	{
		FX::FXSystem::setCurrentDirectory(fileDlg.getDirectory());

		FXString *aNames = fileDlg.getFilenames();
		if (NULL != aNames)
		{
			for(int i = 0; true != aNames[i].empty(); ++i)
			{
				KString strTmpSourcePath = Fox2SDKString(FXString::compose(aNames[i], false));

#if _MSC_VER < 1400
				__stat64 buf;
				int res = _tstat64(strTmpSourcePath, &buf);
#else
				struct _stat64 buf;
				int res = _tstat64(strTmpSourcePath, &buf);
#endif


				if (0 == res)
				{
					KString strTmpDestPath = Fox2SDKString(m_strCurDirectory);

					if (0 != (buf.st_mode & S_IFDIR))
					{

						SDirToAdd dir;
							dir.lpszSourceDirPath = strTmpSourcePath;
							dir.lpszDestinationPath = strTmpDestPath;
							dir.lpszFileSpecification = _T("*");
							dir.nFileAttributes = BS_FA_ALL;
							dir.nSavePath = savePath; // BS_PARENTDIR_ONLY; // BS_DONT_SAVE_PATH; // BS_PARENTDIR_ONLY;
							dir.bRecursive = BS_TRUE;

						res = ::AddDir(dir);
						handleError(res);
					}
					else
					{
						FXString strName = FXPath::name(FXString::compose(aNames[i], false));
						KString strTmpName = Fox2SDKString(strName);

						SFileToAdd file;
							file.lpszFileName = NULL;
							file.lpszSourceFilePath = strTmpSourcePath;
							file.lpszDestinationPath = strTmpDestPath;
							file.bVideoFile = BS_FALSE;
							file.nSavePath = savePath; //BS_DONT_SAVE_PATH; // BS_WHOLE_PATH;

						res = ::AddFile(file);
						handleError(res);
					}
				}
			}

			SelectDirectory(m_strCurDirectory);
			delete[] aNames;
		}
	}
}

void KFileList::CreateFolder()
{
	FXIcon *dlgIcon = new FXGIFIcon(getApp(), bigfolder);
	FXInputDialog dlg(getApp(), "Fox Burner", "Create new folder:", dlgIcon, INPUTDIALOG_STRING);

	if (dlg.execute() && !dlg.getText().empty())
	{
		KString strTmpName = Fox2SDKString(FXString::compose(dlg.getText(), false));
		KString strTmpDestPath = Fox2SDKString(m_strCurDirectory);

		SDirToCreate dir;
			dir.lpszDestinationPath = strTmpDestPath;
			dir.lpszDir = strTmpName;

		int32 res = ::CreateDir(dir);
		handleError(res);

		SelectDirectory(m_strCurDirectory);
	}
}

void KFileList::DeleteItem()
{
	FXbool needUpdate = false;

	for (FXint i = getNumItems(); i > 0; i--)
	{
		if (isItemSelected(i-1))
		{
			int32 res;
			SFileEntry *entry = (SFileEntry*)getItemData(i-1);

			if (NULL != entry)
			{
				if (0 != (BS_FA_DIRECTORY & entry->nAttrib))
				{
					KString strDestPath = entry->lpszFilePath;
					if (strDestPath.Right(1) != PATHSEPSTRING) {
						strDestPath += PATHSEP;
					}
					strDestPath += entry->lpszFileName;

					SDirToRemove dir;
						dir.lpszDestinationPath = strDestPath;

					res = ::RemoveDir(dir);
					handleError(res);
				}
				else
				{
					SFileToRemove file;
						file.lpszFile = entry->lpszFileName;
						file.lpszDestinationPath = entry->lpszFilePath;

					res = ::RemoveFile(file);
					handleError(res);
				}

				//delete entry;
				needUpdate = true;
			}
		}
	}

	if (needUpdate)
		SelectDirectory(m_strCurDirectory);
}

void KFileList::ResetList()
{
	SelectDirectory(m_strRootDirectory);
}

int64 KFileList::GetDirectorySize(const FXString &strPath)
{
	int64 size = 0;

	KString strTmp = Fox2SDKString(strPath);

	HSESSION hSession;
	int32 res = ::OpenDiskSession(BS_CURRENT_DEVICE, 0, &hSession);
	handleError(res);

	HDIR hDirectory;
	res = ::OpenDirectory(hSession, strTmp, &hDirectory);
	handleError(res);

	SFileEntry entry;

	for(int32 nIndex = 0; ; ++nIndex)
	{
		if (BS_SDK_ERROR_NO != ::ReadDirectory(hDirectory, nIndex, &entry))
			break;

        if (0 != (BS_FA_DIRECTORY & entry.nAttrib))
		{
			FXString strDirTmp = SDK2FoxString(entry.lpszFilePath);
            //CHANGEDATE: IF-14/2/2019
            //The SDK will give \\users back, so we need to normalize to UNIX path.
            //Special function from foxtoolkit developers.
            //It is also possible to work with the strPath variable to avoid windows paths.
            FXString strDir = FXPath::convert(FXString::compose(strDirTmp, false));
	            
			strDir += PATHSEP;
			strDir += SDK2FoxString(entry.lpszFileName);

			size += GetDirectorySize(strDir);
		}
		else
		{
			size += entry.nFileSize;
		}
	}

	res = ::CloseDirectory(hDirectory);
	handleError(res);

	res = ::CloseDiskSession(hSession);
	handleError(res);

	return size;
}

void KFileList::clearItems(FXbool notify)
{
	for (int i = getNumItems(); i > 0; --i)
	{
		removeItem(i-1);
	}
}

void KFileList::removeItem(FXint index, FXbool notify)
{
	SFileEntry *userData = (SFileEntry*)getItemData(index);
	if (NULL != userData)
		delete userData;

	FXIconList::removeItem(index, notify);
}

long KFileList::onDoubleClicked(FXObject* sender, FXSelector key, void* data)
{
	FXIconList::onDoubleClicked(sender, key, data);

	FXint indx = getCurrentItem();

	if (-1 == indx)
		return 1;

	if (".." == getItemText(indx))
	{
		FXint pos = m_strCurDirectory.find_last_of(PATHSEP, m_strCurDirectory.length());
		if (0 == pos)
			m_strCurDirectory = PATHSEPSTRING;
		else
			m_strCurDirectory = m_strCurDirectory.left(pos);

		SelectDirectory(m_strCurDirectory);
	}
	else
	{
		SFileEntry *data = (SFileEntry*)getItemData(indx);
		if ((NULL != data) && (0 != (BS_FA_DIRECTORY & data->nAttrib)))
		{
			if (PATHSEPSTRING != m_strCurDirectory)
				m_strCurDirectory += PATHSEPSTRING;

			FXString strName = SDK2FoxString(data->lpszFileName);
			m_strCurDirectory += strName;

			SelectDirectory(m_strCurDirectory);
		}
	}

	return 1;
}

void KFileList::RenameFile()
{
	FXint indx = getCurrentItem();
	if (indx == -1)
		return;

	SFileEntry *entry = (SFileEntry*)getItemData(indx);

	if (NULL == entry)
		return;

	bool isFolder = (0 != (BS_FA_DIRECTORY & entry->nAttrib));

	FXString strFileName = SDK2FoxString(entry->lpszFileName);
	FXString strCaption = "Rename \"";
	strCaption += strFileName + "\" to:";

	FXIcon *dlgIcon;

	if (isFolder)
	{
		dlgIcon = new FXGIFIcon(getApp(), minifolder);
	}
	else
	{
		dlgIcon = new FXGIFIcon(getApp(), minidoc);
	}

	FXInputDialog dlg(getApp(), "Fox Burner", strCaption, dlgIcon, INPUTDIALOG_STRING);

	if (dlg.execute() && !dlg.getText().empty())
	{
        KString strTmpName = Fox2SDKString(FXString::compose(dlg.getText(), false));

		KString strTmpSrcPath = entry->lpszFilePath;
		if (strTmpSrcPath != _T(PATHSEPSTRING))
			strTmpSrcPath += _T(PATHSEPSTRING);
		strTmpSrcPath += entry->lpszFileName;

		//KString strTmpDestPath = entry->lpszFilePath;
		//if (strTmpDestPath != _T(PATHSEPSTRING))
		//	strTmpDestPath += _T(PATHSEPSTRING);
		//strTmpDestPath += strTmpName;
		KString& strTmpDestPath = strTmpName;

		if (isFolder)
		{
			SDirToRename dir;
				dir.lpszSourcePath = strTmpSrcPath;
				dir.lpszDestinationPath = strTmpDestPath;

			int32 res = ::RenameDir(dir);
			handleError(res);
		}
		else
		{
			SFileToRename file;
				file.lpszSourcePath = strTmpSrcPath;
				file.lpszDestinationPath = strTmpDestPath;

			int32 res = ::RenameFile(file);
			handleError(res);
		}

		SelectDirectory(m_strCurDirectory);
	}
}

void KFileList::handleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		int32 nLength = 2048;

		// Get error description

		::GetText(errCode, chError, &nLength);

#ifdef _UNICODE
		KString strError = KStringFormat(_T("error: %ls"), chError);
#else
		KString strError = KStringFormat(_T("error: %hs"), chError);
#endif

		FXString fxstr = (const wchar_t*)strError;
		FXMessageBox::error(this, MBOX_OK, "IsoSDK", fxstr.text());		
	}
}

void KFileList::SetRootDirectory(const FXString& strPath)
{
	m_strRootDirectory = strPath;
	SelectDirectory(m_strRootDirectory);
}

int64 KFileList::GetRootDirectorySize()
{
    return GetDirectorySize(m_strRootDirectory);
}
