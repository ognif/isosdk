#include "stdafx.h"
#include "TreeNodes.h"

using namespace std;

template <typename _Ty>
	void freeChilds(std::vector<_Ty*>& childs)
{
	for(size_t i = 0; i < childs.size(); ++i)
	{
		delete childs[i];
	}

	childs.clear();
}

CString formatSize(int64 size)
{
	if (size == 0)
	{
		return _T("0");
	}

	CString res;

	while (size != 0)
	{
		int p = int(size % 1000);

		CString temp = res;
		res.Format(_T("%i "), p);
		res += temp;

		size /= 1000;
	}
	
	return res.Trim();
}

CString formatSize(double size)
{
	return formatSize(int64(size));
}

CString formatTime(SFileDateTime info)
{
	CString temp;
	temp.Format(_T("%.2d.%.2d.%.4d %.2d:%.2d:%.2d"),
		int(info.nDay),
		int(info.nMonth),
		int(info.nYear + 1900),
		int(info.nHour),
		int(info.nMinute),
		int(info.nSecond));

	return temp;
}

CString formatDate(const SFileEntry& info)
{
	CString temp;
	temp.Format(_T("%.2d.%.2d.%.4d %.2d:%.2d:%.2d"), 
		int(info.cDateTime.nDay),
		int(info.cDateTime.nMonth),
		int(info.cDateTime.nYear + 1900),
		int(info.cDateTime.nHour),
		int(info.cDateTime.nMinute),
		int(info.cDateTime.nSecond));

	return temp;
}

CString int2str(int32 N)
{
	CString tmp;
	tmp.Format(_T("%i"), N);
	return tmp;
}

GenericInfo::GenericInfo()
	:lba(0)
	,size(0)
	,date(_T("N/A"))
	,icon(GenericInfo::ICON_FILE)
{
}

MediumNode* MediumNode::create(const SMediumInfo& info)
{
	return new MediumNode(info);
}

MediumNode::MediumNode(const SMediumInfo& info)
	:m_info(info)
{
	// create session nodes

	for(int session = 1; session <= info.nLastSession; ++session)
	{
		SessionNode* sessionNode = SessionNode::create(session);
		m_sessions.push_back(sessionNode);
	}
}

MediumNode::~MediumNode()
{
	freeChilds(m_sessions);
}

GenericInfo MediumNode::getGenericInfo() const
{
	GenericInfo info;
	info.name = m_info.chMediumType;

	if (m_info.nMediumStatus == BS_MS_EMPTY_DISK)
	{
		info.name = _T("Empty ") + info.name;
	}

	info.lba = 0;
	info.size = (int64)(m_info.dMediumSize/2048);
	info.icon = GenericInfo::ICON_MEDIUM;
	return info;
}

Properties MediumNode::getProperties() const
{
	using namespace std;
	Properties props;
	props.push_back( make_pair(_T("Medium type"), m_info.chMediumType) );
	props.push_back( make_pair(_T("Status"), mediumStatusToString(m_info.nMediumStatus)));
	props.push_back( make_pair(_T("Size"), formatSize(m_info.dMediumSize)));
	props.push_back( make_pair(_T("Used"), formatSize(m_info.dMediumUsedSize)));
	props.push_back( make_pair(_T("Free"), formatSize(m_info.dMediumFreeSize)));

	CString temp;
	temp.Format(_T("%u"), m_info.nLastSession);
	props.push_back( make_pair(_T("Sessions"), temp));

	temp.Format(_T("%u"), m_info.nLastTrack);
	props.push_back( make_pair(_T("Tracks"), temp));

	props.push_back( make_pair(_T("Last session status"), 
		SessionNode::sessionStatusToString(m_info.nLastSessionStatus)));
	props.push_back( make_pair(_T("UCP/EAN code"), m_info.chUPCEANCode));

	return props;
}

CString MediumNode::mediumStatusToString(int32 status)
{
	switch(status)
	{
		case BS_MS_EMPTY_DISK:
			return _T("Empty");

		case BS_MS_INCOMPLETE_DISK:
			return _T("Incomplete");

		case BS_MS_COMPLETE_DISK:
			return _T("Complete");

		default:
			return _T("Other");
	}
}

SessionNode* SessionNode::create(int session)
{
	return new SessionNode(session);
}

SessionNode::SessionNode(int session)
	:m_session(session)
{
	// get session information
	int32 res = ::GetSessionInformation(BS_READ_DEVICE, session, &m_info);

	if (res != BS_SDK_ERROR_NO)
	{
		// do not process this session
		return;
	}

	// add tracks
	for(int track = m_info.nFirstTrack; track <= m_info.nLastTrack; ++track)
	{
		m_tracks.push_back( TrackNode::create(track) );
	}
}

SessionNode::~SessionNode()
{
	freeChilds(m_tracks);
}

GenericInfo SessionNode::getGenericInfo() const
{
	GenericInfo info;
	info.icon = GenericInfo::ICON_SESSION;

	CString temp;
	temp.Format(_T("Session %i"), m_session);
	info.name = temp;
	info.lba = m_info.dStartLBA;
	info.size = m_info.dSessionSize;
	return info;
}

Properties SessionNode::getProperties() const
{
	CString temp;
	Properties props;

	temp.Format(_T("%u"), m_info.nFirstTrack);
	props.push_back( make_pair(_T("First track"), temp) );

	temp.Format(_T("%u"), m_info.nLastTrack);
	props.push_back( make_pair(_T("Last track"), temp) );

	temp.Format(_T("%u"), m_info.bLastSession);
	props.push_back( make_pair(_T("Last session"), temp) );

	props.push_back( make_pair(_T("Session size"), formatSize(((int64)m_info.dSessionSize)*2048)) );
	return props;
}

CString SessionNode::sessionStatusToString(int32 status)
{
	switch(status)
	{
		case BS_LS_EMPTY_SESSION:
			return _T("Empty");

		case BS_LS_INCOMPLETE_SESSION:
			return _T("Incomplete");

		case BS_LS_COMPLETE_SESSION:
			return _T("Complete");

		default:
			return _T("Damaged");
	}
}

TrackNode* TrackNode::create(int track)
{
	return new TrackNode(track);
}

TrackNode::TrackNode(int track)
{
	// get track information
	int32 res = ::GetTrackInformation(BS_READ_DEVICE, track, &m_info);

	if (res != BS_SDK_ERROR_NO)
	{
		m_info.nTrackNumber = track;
		// skip this track
		return;
	}

	if (m_info.nFormat != BS_TF_AUDIO)
	{
		// data track
		// create file system nodes
		if (m_info.nFileSystem & BS_FS_ISO9660)
		{
			m_fileSystems.push_back( ISO9660Node::create(track, this) );
		}

		if (m_info.nFileSystem & BS_FS_JOLIET)
		{
			m_fileSystems.push_back( ISO9660Node::create(track, this, BS_FS_JOLIET) );
		}

		if (m_info.nFileSystem & BS_FS_ROCKRIDGE)
		{
			m_fileSystems.push_back( ISO9660Node::create(track, this, BS_FS_ROCKRIDGE) );
		}

		if (m_info.nFileSystem & BS_FS_UDF)
		{
			m_fileSystems.push_back( UDFNode::create(track, this) );
		}

		if (m_info.nFileSystem & BS_FS_BOOTABLE)
		{
			m_fileSystems.push_back( BootNode::create(track, this) );
		}
	}
}

TrackNode::~TrackNode()
{
	freeChilds(m_fileSystems);
}

GenericInfo TrackNode::getGenericInfo() const
{
	CString temp;
	GenericInfo info;

	temp.Format(_T("Track %i"), m_info.nTrackNumber);
	info.name = temp;

	info.icon = (m_info.nFormat == BS_TF_AUDIO) 
		? GenericInfo::ICON_TRACK_AUDIO
		: GenericInfo::ICON_TRACK_DATA;

	info.lba = m_info.nStartLBA;
	info.size = m_info.nSize;

	return info;
}

Properties TrackNode::getProperties() const
{
	CString temp;
	Properties props;

	temp.Format(_T("%u"), m_info.nSessionNumber);
	props.push_back( make_pair(_T("Session"), temp) );
	
	CString trackFormat;
	switch(m_info.nFormat)
	{
		case BS_TF_AUDIO:
			trackFormat = _T("Audio"); break;

		case BS_TF_DATA_MODE1:
			trackFormat = _T("Mode 1"); break;

		case BS_TF_DATA_MODE2:
			trackFormat = _T("Mode 2"); break;

		default:
			trackFormat = _T("Unknown"); break;
	}

	props.push_back( make_pair(_T("Format"), trackFormat) );

	CString trackFS;

	if (m_info.nFileSystem == BS_FS_UNKNOWN ||
		m_info.nFileSystem == BS_NDEF)
	{
		trackFS = _T("Unknown");
	}
	else
	{
		if (m_info.nFileSystem & BS_FS_ISO9660)
			trackFS += _T("ISO9660");
		if (m_info.nFileSystem & BS_FS_JOLIET)
			trackFS += _T(" Joliet");
		if (m_info.nFileSystem & BS_FS_UDF)
			trackFS += _T(" UDF");
		if (m_info.nFileSystem & BS_FS_BOOTABLE)
			trackFS += _T(" Bootable");
	}

	props.push_back( make_pair(_T("File system(s)"), trackFS) );

	return props;
}

void FileSysNode::init(HSESSION hSession)
{
	m_root = new DirectoryNode(hSession, PATHSEPSTRING, SFileEntry(), this);
}

FileSysNode::~FileSysNode()
{
	delete m_root;
}

BootNode* BootNode::create(int track, TrackNode* node)
{
	return new BootNode(track, node);
}

BootNode::BootNode(int track, TrackNode* node): FileSysNode(node)
{
	HSESSION hSession = 0;
	int32 res = ::OpenDiskSession(BS_READ_DEVICE, track, &hSession, BS_FS_BOOTABLE);

	if (res != BS_SDK_ERROR_NO)
	{
		// can't read file system
		// skip this
		return;
	}

	init(hSession);

	::GetBootVolumeInformation(hSession, &m_info);
	::CloseDiskSession(hSession);
}

GenericInfo BootNode::getGenericInfo() const
{
	GenericInfo info;
	info.name = _T("Boot");
	info.icon = GenericInfo::ICON_FILESYS_BOOT;
	info.lba = m_info.nVolumeDescriptorAddress;
	info.size = 0;
	return info;
}

Properties BootNode::getProperties() const
{
	CString temp;
	Properties props;

	temp.Format(_T("%i"), m_info.nVolumeDescriptorAddress);
	props.push_back( make_pair(_T("Volume descriptor address"), temp) );

	props.push_back( make_pair(_T("Developer ID"), m_info.sInfoEx.DeveloperID) );

	if (m_info.sInfoEx.BootIndicator)
	{
		props.push_back( make_pair(_T("Boot indicator"), _T("True")) );
	}
	else
	{
		props.push_back( make_pair(_T("Boot indicator"), _T("False")) );
	}

	temp.Format(_T("%i"), m_info.sInfoEx.LoadSegment);
	props.push_back( make_pair(_T("Load segment"), temp) );

	temp.Format(_T("%i"), m_info.sInfoEx.PlatformID);
	props.push_back( make_pair(_T("Platform ID"), temp) );

	temp.Format(_T("%i"), m_info.sInfoEx.Emulation);
	props.push_back( make_pair(_T("Emulation ID"), temp) );

	temp.Format(_T("%i"), m_info.sInfoEx.SectorCount);
	props.push_back( make_pair(_T("Amount of sectors"), temp) );

	return props;
}

ISO9660Node* ISO9660Node::create(int track, TrackNode* trackNode, BYTE fsExtension)
{
	return new ISO9660Node(track, trackNode, fsExtension);
}

ISO9660Node::ISO9660Node(int track, TrackNode* trackNode, BYTE fsExtension)
	:FileSysNode(trackNode), m_fsExtension(fsExtension)
{
	HSESSION hSession = 0;
	int32 res = ::OpenDiskSession(BS_READ_DEVICE, track, &hSession, fsExtension ? fsExtension : BS_FS_ISO9660);

	if (res != BS_SDK_ERROR_NO)
	{
		// can't read file system
		// skip this
		return;
	}

	init(hSession);

	::GetISOVolumeInformation(hSession, &m_info);
	::CloseDiskSession(hSession);
}

GenericInfo ISO9660Node::getGenericInfo() const
{
	GenericInfo info;

	switch (m_fsExtension)
	{
		case BS_FS_JOLIET:
		{
			info.name = _T("Joliet");
			info.icon = GenericInfo::ICON_FILESYS_JOLIET;		
		}
		break;

		case BS_FS_ROCKRIDGE:
		{
			info.name = _T("Rock Ridge");
			info.icon = GenericInfo::ICON_FILESYS_ROCKRIDGE;		
		}
		break;

		default :			
		{
			info.name = _T("ISO 9660");
			info.icon = GenericInfo::ICON_FILESYS_ISO;		
		}
		break;
	}

	info.lba = m_info.nVolumeDescriptorAddress;
	info.size = m_info.nVolumeSize;
	info.date = formatTime(m_info.tRootDateTime);
	return info;
}

Properties ISO9660Node::getProperties() const
{
	CString temp;
	Properties props;

	props.push_back( make_pair(_T("Volume label"), m_info.chVolumeLabel) );

	temp.Format(_T("%i"), m_info.nVolumeDescriptorAddress);
	props.push_back( make_pair(_T("VD address"), temp) );

	temp.Format(_T("%i"), m_info.nVolumeSize);
	props.push_back( make_pair(_T("Volume size(blocks)"), temp) );

	temp.Format(_T("%i"), m_info.nRootAddress);
	props.push_back( make_pair(_T("Root address"), temp) );

	temp.Format(_T("%i"), m_info.nPathTableAddress);
	props.push_back( make_pair(_T("Path table address"), temp) );

	temp.Format(_T("%i"), m_info.nPathTableSize);
	props.push_back( make_pair(_T("Path table size"), temp) );

	props.push_back( make_pair(_T("Abstract Identifier"), m_info.sInfoEx.ISOAbstractFileIdentifier) );
	props.push_back( make_pair(_T("Application Identifier"), m_info.sInfoEx.ISOApplicationIdentifier) );
	props.push_back( make_pair(_T("Biblio Identifier"), m_info.sInfoEx.ISOBiblioIdentifier) );
	props.push_back( make_pair(_T("Copyright Identifier"), m_info.sInfoEx.ISOCopyrightFileIdentifier) );
	props.push_back( make_pair(_T("Data PreparerIdentifier"), m_info.sInfoEx.ISODataPreparerIdentifier) );
	props.push_back( make_pair(_T("Publisher Identifier"), m_info.sInfoEx.ISOPublisherIdentifier) );
	props.push_back( make_pair(_T("Set Identifier"), m_info.sInfoEx.ISOSetIdentifier) );
	props.push_back( make_pair(_T("System Identifier"), m_info.sInfoEx.ISOSystemIdentifier) );

	props.push_back( make_pair(_T("Creation Date"), formatTime(m_info.sInfoEx.ISOCreationDateTime)) );
	props.push_back(make_pair(_T("Modification Date"), formatTime(m_info.sInfoEx.ISOModificationDateTime)) );
	props.push_back(make_pair(_T("Effective Date"), formatTime(m_info.sInfoEx.ISOEffectiveDateTime)) );
	props.push_back(make_pair(_T("Expiration Date"), formatTime(m_info.sInfoEx.ISOExpirationDateTime)) );

	return props;
}

UDFNode* UDFNode::create(int track, TrackNode* trackNode)
{
	return new UDFNode(track, trackNode);
}

UDFNode::UDFNode(int track, TrackNode* trackNode):FileSysNode(trackNode)
{
	HSESSION hSession = 0;
	int32 res = ::OpenDiskSession(BS_READ_DEVICE, track, &hSession, BS_FS_UDF);

	if (res != BS_SDK_ERROR_NO)
	{
		// can't read file system
		// skip this
		return;
	}

	init(hSession);

	::GetUDFVolumeInformation(hSession, &m_info);
	::CloseDiskSession(hSession);
}

GenericInfo UDFNode::getGenericInfo() const
{
	GenericInfo info;
	info.name = _T("UDF");
	info.icon = GenericInfo::ICON_FILESYS_UDF;
	info.lba = m_info.nPartitionAddress;
	info.size = m_info.nPartitionLength;
	info.date = formatTime(m_info.tRecordingDateTime);
	return info;
}

Properties UDFNode::getProperties() const
{
	CString temp;
	Properties props;
	props.push_back( make_pair(_T("Volume label"), m_info.chVolumeLabel) );
	props.push_back( make_pair(_T("Preparer"), m_info.chPreparer) );
	props.push_back( make_pair(_T("UDF version"), udfVersionToString(m_info.nVersion)) );
	props.push_back( make_pair(_T("Partition type"), partitionToString(m_info.nPartitionType)) );
	props.push_back( make_pair(_T("MVDS address"), int2str(m_info.nMVDSAddress)));
	props.push_back( make_pair(_T("RVDS address"), int2str(m_info.nRVDSAddress)));
	props.push_back( make_pair(_T("Root address"), int2str(m_info.nRootAddress)));
	props.push_back( make_pair(_T("Root (E)FE"), int2str(m_info.nRootFEAddress)));
	props.push_back( make_pair(_T("Partition address"), int2str(m_info.nPartitionAddress)));
	props.push_back( make_pair(_T("Partition length"), int2str(m_info.nPartitionLength)));
	props.push_back( make_pair(_T("LVD"), int2str(m_info.nLVDAddress)));
	props.push_back( make_pair(_T("PVD"), int2str(m_info.nPVDAddress)));
	props.push_back( make_pair(_T("FSD"), int2str(m_info.nFSDAddress)));
	if (m_info.nVATAddress != 0)
		props.push_back( make_pair(_T("VAT"), int2str(m_info.nVATAddress)));
	if (m_info.nMetadataAddress != 0)
		props.push_back( make_pair(_T("Metadata"), int2str(m_info.nMetadataAddress)));
	if (m_info.nSparingAddress != 0)
		props.push_back( make_pair(_T("Sparing"), int2str(m_info.nSparingAddress)) );

	temp.Format(_T("%i"), m_info.nFileCount);
	props.push_back( make_pair(_T("Number of files"), temp) );

	temp.Format(_T("%i"), m_info.nDirCount);
	props.push_back( make_pair(_T("Number of folders"), temp) );

	props.push_back( make_pair(_T("Recording Date"), formatTime(m_info.tRecordingDateTime)) );
	return props;
}

CString UDFNode::udfVersionToString(int32 version)
{
	CString temp;
	temp.Format(_T("%X.%.2X"), (version >> 8), version & 0xFF);
	return temp;
}

CString UDFNode::partitionToString(int32 partition)
{
	switch(partition)
	{
		case BS_UDF_PARTITION_PHYSICAL:
			return _T("Physical");

		case BS_UDF_PARTITION_VIRTUAL:
			return _T("Virtual");

		case BS_UDF_PARTITION_SPARABLE:
			return _T("Sparable");

		default:
			return _T("Unknown");
	}
}

CString attribsToString(int32 attr)
{
	CString res;
	if (attr & BS_FA_ARCHIVE)
	{
		res += _T("A ");
	}

	if (attr & BS_FA_HIDDEN)
	{
		res += _T("H ");
	}

	if (attr & BS_FA_READONLY)
	{
		res += _T("R ");
	}

	if (attr & BS_FA_SYSTEM)
	{
		res += _T("S ");
	}

	return res.Trim();
}

Properties fileEntryToProperties(const SFileEntry& entry)
{
	CString temp;
	Properties props;
	props.push_back( make_pair(_T("Name"), entry.lpszFileName) );

	temp.Format(_T("%d"), entry.nAddress);
	props.push_back( make_pair(_T("Address"), temp) );

	temp.Format(_T("%d"), entry.nFileSize);
	props.push_back( make_pair(_T("Size"), temp) );

	props.push_back( make_pair(_T("Type"), (entry.nAttrib & BS_FA_DIRECTORY) ?
		_T("Folder") : _T("File")) );

	props.push_back( make_pair(_T("Path"), entry.lpszFilePath) );
	props.push_back( make_pair(_T("Attributes"), attribsToString(entry.nAttrib)) );
	return props;
}

DirectoryNode::DirectoryNode(HSESSION hSession, const KString &path, 
							 const SFileEntry& entry, FileSysNode* fileSysNode)
	:m_info(entry),
	 m_fileSysNode(fileSysNode)
{
	HDIR hDir = 0;
	int32 res = ::OpenDirectory(hSession, path, &hDir);

	if (res != BS_SDK_ERROR_NO)
	{
		return;
	}

	for(int i = 0; ; ++i)
	{
		SFileEntry entry;
		res = ::ReadDirectory(hDir, i, &entry);
		if (res != BS_SDK_ERROR_NO)
			break;

		if (entry.nAttrib & BS_FA_DIRECTORY)
		{
			m_files.push_back(new DirectoryNode(hSession, path + PATHSEPSTRING + entry.lpszFileName, entry, fileSysNode));
		}
		else
		{
			m_files.push_back(new FileNode(hSession, entry, fileSysNode));
		}
	}

	::CloseDirectory(hDir);
}

DirectoryNode::~DirectoryNode()
{
	freeChilds(m_files);
}

GenericInfo DirectoryNode::getGenericInfo() const
{
	GenericInfo info;
	info.name = m_info.lpszFileName;
	info.icon = GenericInfo::ICON_DIRECTORY;
	info.lba = m_info.nAddress;
	info.size = m_info.nFileSize;
	info.date = formatDate(m_info);
	info.path = m_info.lpszFilePath;
	return info;
}

Properties DirectoryNode::getProperties() const
{
	return fileEntryToProperties(m_info);
}

FileNode::FileNode(HSESSION hSession, const SFileEntry& entry, FileSysNode* fileSysNode)
	:m_info(entry),
	 m_fileSysNode(fileSysNode),
	 m_allocationTable(getAllocationTable(hSession))
{
}

FileNode::~FileNode()
{
	if (m_allocationTable)
		free(m_allocationTable);
}

GenericInfo FileNode::getGenericInfo() const
{
	GenericInfo info;
	info.name = m_info.lpszFileName;
	info.icon = GenericInfo::ICON_FILE;
	info.lba = m_info.nAddress;
	info.size = m_info.nFileSize;
	info.date = formatDate(m_info);
	info.path = m_info.lpszFilePath;
	return info;
}

Properties FileNode::getProperties() const
{
	return fileEntryToProperties(m_info);
}

SFileAllocationTable *FileNode::getAllocationTable(HSESSION hSession)
{
	CString pathName;
	pathName.Format(_T("%s\\%s"), m_info.lpszFilePath, m_info.lpszFileName);

	int32 tableSize = 0;
	int32 errCode = GetFileAllocationTable(hSession, pathName, NULL, &tableSize);
	if (errCode != BS_SDK_ERROR_MORE_SPACE_NEEDED)
		return NULL;

	SFileAllocationTable *allocTable = (SFileAllocationTable*)malloc(tableSize);
	errCode = GetFileAllocationTable(hSession, pathName, allocTable, &tableSize);

	if (errCode != BS_SDK_ERROR_NO)
	{
		free(allocTable);
		return NULL;
	}


	return allocTable;
}
