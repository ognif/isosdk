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

FXString formatSize(int64 size)
{
	if (size == 0)
	{
		return "0";
	}

	FXString res;

	while(size != 0)
	{
		int p = int(size % 1000);

		res = FXString::value("%i ", p) + res;

		size /= 1000;
	}

	return res.trim();
}

FXString formatSize(double size)
{
	return formatSize(int64(size));
}

FXString formatTime(SFileDateTime info)
{
	return FXString::value("%.2d.%.2d.%.4d %.2d:%.2d:%.2d",
		int(info.nDay),
		int(info.nMonth),
		int(info.nYear + 1900),
		int(info.nHour),
		int(info.nMinute),
		int(info.nSecond));
}

FXString formatDate(const SFileEntry& info)
{
	return FXString::value("%.2d.%.2d.%.4d %.2d:%.2d:%.2d", 
		int(info.cDateTime.nDay),
		int(info.cDateTime.nMonth),
		int(info.cDateTime.nYear + 1900),
		int(info.cDateTime.nHour),
		int(info.cDateTime.nMinute),
		int(info.cDateTime.nSecond));
}

GenericInfo::GenericInfo()
	:lba(0)
	,size(0)
	,date("N/A")
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
		info.name = "Empty " + info.name;
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
	props.push_back( make_pair("Medium type", m_info.chMediumType) );
	props.push_back( make_pair("Status", mediumStatusToString(m_info.nMediumStatus)));
	props.push_back( make_pair("Size", formatSize(m_info.dMediumSize)));
	props.push_back( make_pair("Used", formatSize(m_info.dMediumUsedSize)));
	props.push_back( make_pair("Free", formatSize(m_info.dMediumFreeSize)));
	props.push_back( make_pair("Sessions", FXString::value("%u", m_info.nLastSession)));
	props.push_back( make_pair("Tracks", FXString::value("%u", m_info.nLastTrack)));
	props.push_back( make_pair("Last session status", SessionNode::sessionStatusToString(m_info.nLastSessionStatus)));
	props.push_back( make_pair("UCP/EAN code", m_info.chUPCEANCode));

	return props;
}

FXString MediumNode::mediumStatusToString(int32 status)
{
	switch(status)
	{
	case BS_MS_EMPTY_DISK:
		return "Empty";
	case BS_MS_INCOMPLETE_DISK:
		return "Incomplete";
	case BS_MS_COMPLETE_DISK:
		return "Complete";
	default:
		return "Other";
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
		//Hier wird der VEctor der TRacks erstellt.
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
	info.name = FXString::value("Session %i", m_session);
	info.lba = m_info.dStartLBA;
	info.size = m_info.dSessionSize;
	return info;
}

Properties SessionNode::getProperties() const
{
	Properties props;
	props.push_back( make_pair("First track", FXString::value("%u", m_info.nFirstTrack)) );
	props.push_back( make_pair("Last track", FXString::value("%u", m_info.nLastTrack)) );
	props.push_back( make_pair("Last session", FXString::value("%u", m_info.bLastSession)) );
	props.push_back( make_pair("Session size", formatSize(((int64)m_info.dSessionSize) * 2048)) );
	return props;
}

FXString SessionNode::sessionStatusToString(int32 status)
{
	switch(status)
	{
	case BS_LS_EMPTY_SESSION:
		return "Empty";
	case BS_LS_INCOMPLETE_SESSION:
		return "Incomplete";
	case BS_LS_COMPLETE_SESSION:
		return "Complete";
	default:
		return "Damaged";
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
	GenericInfo info;
	info.name = FXString::value("Track %i", m_info.nTrackNumber);
	info.icon = (m_info.nFormat == BS_TF_AUDIO) 
		? GenericInfo::ICON_TRACK_AUDIO
		: GenericInfo::ICON_TRACK_DATA;
	info.lba = m_info.nStartLBA;
	info.size = m_info.nSize;
	

	return info;
}

Properties TrackNode::getProperties() const
{
	Properties props;
	props.push_back( make_pair("Session", FXString::value("%u", m_info.nSessionNumber)) );
	
	FXString trackFormat;
	switch(m_info.nFormat)
	{
	case BS_TF_AUDIO:
		trackFormat = "Audio"; break;
	case BS_TF_DATA_MODE1:
		trackFormat = "Mode 1"; break;
	case BS_TF_DATA_MODE2:
		trackFormat = "Mode 2"; break;
	default:
		trackFormat = "Unknown"; break;
	}

	props.push_back( make_pair("Format", trackFormat) );

	FXString trackFS;

	if (m_info.nFileSystem == BS_FS_UNKNOWN ||
		m_info.nFileSystem == BS_NDEF)
	{
		trackFS = "Unknown";
	}
	else
	{
		if (m_info.nFileSystem & BS_FS_ISO9660)
			trackFS += "ISO9660";
		if (m_info.nFileSystem & BS_FS_JOLIET)
			trackFS += " Joliet";
		if (m_info.nFileSystem & BS_FS_UDF)
			trackFS += " UDF";
		if (m_info.nFileSystem & BS_FS_BOOTABLE)
			trackFS += " Bootable";
	}

	props.push_back( make_pair("File system(s)", trackFS) );

	return props;
}

void FileSysNode::init(HSESSION hSession)
{
	m_root = new DirectoryNode(hSession, "", SFileEntry(), this);
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
	info.name = "Boot";
	info.icon = GenericInfo::ICON_FILESYS_BOOT;
	info.lba = m_info.nVolumeDescriptorAddress;
	info.size = 0;
	return info;
}

Properties BootNode::getProperties() const
{
	Properties props;

	props.push_back( make_pair("Volume descriptor address", 
		FXString::value("%i", m_info.nVolumeDescriptorAddress)) );
	props.push_back( make_pair("Developer ID", m_info.sInfoEx.DeveloperID) );

	if (m_info.sInfoEx.BootIndicator)
	{
		props.push_back( make_pair("Boot indicator", "True") );
	}
	else
	{
		props.push_back( make_pair("Boot indicator", "False") );
	}

	props.push_back( make_pair("Load segment", FXString::value("%i", m_info.sInfoEx.LoadSegment)) );
	props.push_back( make_pair("Platform ID", FXString::value("%i", m_info.sInfoEx.PlatformID)) );
	props.push_back( make_pair("Emulation ID", FXString::value("%i", m_info.sInfoEx.Emulation)) );
	props.push_back( make_pair("Amount of sectors", FXString::value("%i", m_info.sInfoEx.SectorCount)) );

	return props;
}

ISO9660Node* ISO9660Node::create(int track, TrackNode* trackNode, int8 fsExtension)
{
	return new ISO9660Node(track, trackNode, fsExtension);
}

ISO9660Node::ISO9660Node(int track, TrackNode* trackNode, int8 fsExtension)
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
			info.name = "Joliet";
			info.icon = GenericInfo::ICON_FILESYS_JOLIET;		
		}
		break;

		case BS_FS_ROCKRIDGE:
		{
			info.name = "Rock Ridge";
			info.icon = GenericInfo::ICON_FILESYS_ROCKRIDGE;		
		}
		break;

		default :			
		{
			info.name = "ISO 9660";
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
	Properties props;

	props.push_back( make_pair("Volume label", m_info.chVolumeLabel) );
	props.push_back( make_pair("VD address", FXString::value("%i", m_info.nVolumeDescriptorAddress)) );
	props.push_back( make_pair("Volume size(blocks)", FXString::value("%i", m_info.nVolumeSize)) );
	props.push_back( make_pair("Root address", FXString::value("%i", m_info.nRootAddress)) );
	props.push_back( make_pair("Path table address", FXString::value("%i", m_info.nPathTableAddress)) );
	props.push_back( make_pair("Path table size", FXString::value("%i", m_info.nPathTableSize)) );

	props.push_back( make_pair("Abstract Identifier", m_info.sInfoEx.ISOAbstractFileIdentifier) );
	props.push_back( make_pair("Application Identifier", m_info.sInfoEx.ISOApplicationIdentifier) );
	props.push_back( make_pair("Biblio Identifier", m_info.sInfoEx.ISOBiblioIdentifier) );
	props.push_back( make_pair("Copyright Identifier", m_info.sInfoEx.ISOCopyrightFileIdentifier) );
	props.push_back( make_pair("Data PreparerIdentifier", m_info.sInfoEx.ISODataPreparerIdentifier) );
	props.push_back( make_pair("Publisher Identifier", m_info.sInfoEx.ISOPublisherIdentifier) );
	props.push_back( make_pair("Set Identifier", m_info.sInfoEx.ISOSetIdentifier) );
	props.push_back( make_pair("System Identifier", m_info.sInfoEx.ISOSystemIdentifier) );

	props.push_back( make_pair("Creation Date", formatTime(m_info.sInfoEx.ISOCreationDateTime)) );
	props.push_back( make_pair("Modification Date", formatTime(m_info.sInfoEx.ISOModificationDateTime)));
	props.push_back( make_pair("Effective Date", formatTime(m_info.sInfoEx.ISOEffectiveDateTime)));
	props.push_back( make_pair("Expiration Date", formatTime(m_info.sInfoEx.ISOExpirationDateTime)));



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
	info.name = "UDF";
	info.icon = GenericInfo::ICON_FILESYS_UDF;
	info.lba = m_info.nMVDSAddress;
	info.size = m_info.nPartitionLength;	
	info.date = formatTime(m_info.tRecordingDateTime);
	return info;
}

Properties UDFNode::getProperties() const
{
	Properties props;
	props.push_back( make_pair("Volume label", m_info.chVolumeLabel) );
	props.push_back( make_pair("Preparer", m_info.chPreparer) );
	props.push_back( make_pair("UDF version", udfVersionToString(m_info.nVersion)) );
	props.push_back( make_pair("Partition type", partitionToString(m_info.nPartitionType)) );
	props.push_back( make_pair("MVDS address", FXString::value("%i", m_info.nMVDSAddress)));
	props.push_back( make_pair("RVDS address", FXString::value("%i", m_info.nRVDSAddress)));
	props.push_back( make_pair("Root address", FXString::value("%i", m_info.nRootAddress)));
	props.push_back( make_pair("Root FE", FXString::value("%i", m_info.nRootFEAddress)));
	props.push_back( make_pair("Partition address", FXString::value("%i", m_info.nPartitionAddress)));
	props.push_back( make_pair("Partition length", FXString::value("%i", m_info.nPartitionLength)));
	props.push_back( make_pair("LVD", FXString::value("%i", m_info.nLVDAddress)));
	props.push_back( make_pair("PVD", FXString::value("%i", m_info.nPVDAddress)));
	props.push_back( make_pair("FSD", FXString::value("%i", m_info.nFSDAddress)));


	if (m_info.nVATAddress != 0)
		props.push_back( make_pair("VAT", FXString::value("%i", m_info.nVATAddress)));
	if (m_info.nMetadataAddress != 0)
		props.push_back( make_pair("Metadata", FXString::value("%i", m_info.nMetadataAddress)));
	if (m_info.nSparingAddress != 0)
		props.push_back( make_pair("Sparing", FXString::value("%i", m_info.nSparingAddress)));
	props.push_back( make_pair("Number of files", FXString::value("%i", m_info.nFileCount)) );
	props.push_back( make_pair("Number of folders", FXString::value("%i", m_info.nDirCount)) );

	props.push_back( make_pair("Recording Date", formatTime(m_info.tRecordingDateTime)) );
	return props;
}

FXString UDFNode::udfVersionToString(int32 version)
{
	return FXString::value("%X.%.2X", (version >> 8), version & 0xFF);
}

FXString UDFNode::partitionToString(int32 partition)
{
	switch(partition)
	{
	case BS_UDF_PARTITION_PHYSICAL:
		return "Physical";
	case BS_UDF_PARTITION_VIRTUAL:
		return "Virtual";
	case BS_UDF_PARTITION_SPARABLE:
		return "Sparable";
	default:
		return "Unknown";
	}
}

FXString attribsToString(int32 attr)
{
	FXString res;
	if (attr & BS_FA_ARCHIVE)
		res += "A ";
	if (attr & BS_FA_HIDDEN)
		res += "H ";
	if (attr & BS_FA_READONLY)
		res += "R ";
	if (attr & BS_FA_SYSTEM)
		res += "S ";
	return res.trim();
}

Properties fileEntryToProperties(const SFileEntry& entry)
{
	Properties props;
	props.push_back( make_pair("Name", SDK2FoxString(entry.lpszFileName)) );
	props.push_back( make_pair("Address", FXString::value("%d", entry.nAddress)) );
	props.push_back( make_pair("Size", FXString::value("%d", entry.nFileSize)) );
	props.push_back( make_pair("Type", (entry.nAttrib & BS_FA_DIRECTORY) ? "Folder" : "File") );
	props.push_back( make_pair("Path", SDK2FoxString(entry.lpszFilePath)) );
	props.push_back( make_pair("Attributes", attribsToString(entry.nAttrib)) );
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
			m_files.push_back(new FileNode(entry, fileSysNode));
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
	info.name = SDK2FoxString(m_info.lpszFileName);
	info.icon = GenericInfo::ICON_DIRECTORY;
	info.lba = m_info.nAddress;
	info.size = m_info.nFileSize;
	info.date = formatDate(m_info);
	info.path = SDK2FoxString(m_info.lpszFilePath);
	return info;
}

Properties DirectoryNode::getProperties() const
{
	return fileEntryToProperties(m_info);
}

FileNode::FileNode(const SFileEntry& entry, FileSysNode* fileSysNode)
	:m_info(entry),
	 m_fileSysNode(fileSysNode)
{
}

GenericInfo FileNode::getGenericInfo() const
{
	GenericInfo info;
	info.name = SDK2FoxString(m_info.lpszFileName);
	info.icon = GenericInfo::ICON_FILE;
	info.lba = m_info.nAddress;
	info.size = m_info.nFileSize;
	info.date = formatDate(m_info);
	info.path = SDK2FoxString(m_info.lpszFilePath);
	return info;
}

Properties FileNode::getProperties() const
{
	return fileEntryToProperties(m_info);
}
