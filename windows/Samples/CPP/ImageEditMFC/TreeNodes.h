#pragma once

#include <vector>
#include <utility>
#include "IsoSDKExport.h"

/// Property is a pair <Name, Value>
typedef std::pair<CString, CString> Property;

/// Property list
typedef std::vector<Property> Properties;

/// Common information for all node types
struct GenericInfo
{
	/// node icon is used to choose an icon for the node
	enum Icon
	{
		ICON_MEDIUM,
		ICON_SESSION,
		ICON_TRACK_DATA,
		ICON_TRACK_AUDIO,
		ICON_FILESYS_ISO,
		ICON_FILESYS_JOLIET,
		ICON_FILESYS_ROCKRIDGE,
		ICON_FILESYS_UDF,
		ICON_FILESYS_BOOT,
		ICON_DIRECTORY,
		ICON_FILE,
	};

	/// Node name
	CString name;
	/// Node logical block address
	int32    lba;
	/// Node size in bytes
	int64    size;
	/// Node modification date
	CString date;
	/// Node icon
	Icon	 icon;
	/// Node name
	CString path;

	GenericInfo();
};

/// Base class for all tree nodes
class ITreeNode
{
public:

	/// Get generic information for this node
	/// Generic info is displayed at right pane of main window
	virtual GenericInfo getGenericInfo() const = 0;

	/// Returns special properties of this node
	virtual Properties getProperties() const = 0;

	/// Returns number of child nodes
	virtual size_t getChildsCount() const = 0;

	/// Returns child node by its number
	virtual ITreeNode* getChild(int i) const = 0;

	virtual ~ITreeNode() = 0 {};
};


class FileSysNode;

class FileNode : public ITreeNode
{
public:
	FileNode(HSESSION hSession, const SFileEntry& entry, FileSysNode* fileSysNode);
	~FileNode();

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual size_t getChildsCount() const { return 0; }

	virtual ITreeNode* getChild(int i) const { return 0; }

	virtual FileSysNode* getFileSystemNode() const { return m_fileSysNode; }

	const SFileAllocationTable *getAllocationTable() const { return m_allocationTable; }

protected:
	SFileEntry m_info;
	FileSysNode* m_fileSysNode;

private:
	SFileAllocationTable *getAllocationTable(HSESSION hSession);

	SFileAllocationTable *m_allocationTable;
};

class DirectoryNode : public ITreeNode
{
public:
	HSESSION m_hSession;

	DirectoryNode(HSESSION hSession, const KString& path, const SFileEntry& entry, FileSysNode* fileSysNode);

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual size_t getChildsCount() const { return m_files.size(); }

	virtual ITreeNode* getChild(int i) const { return m_files.at(i); }

	virtual FileSysNode* getFileSystemNode() const { return m_fileSysNode; }

	~DirectoryNode();

protected:
	SFileEntry m_info;
	std::vector<ITreeNode*> m_files;
	FileSysNode* m_fileSysNode;
};

class TrackNode;

/// Node representing genric file system
class FileSysNode : public ITreeNode
{
public:

	virtual size_t getChildsCount() const { return m_root ? m_root->getChildsCount() : 0; }

	virtual ITreeNode* getChild(int i) const { return m_root->getChild(i); }

	virtual TrackNode* getTrackNode() const { return m_trackNode; }

	virtual int32 getFileSysType() const = 0;

	~FileSysNode();

protected:
	FileSysNode(TrackNode* trackNode):m_root(0), m_trackNode(trackNode) {}

	void init(HSESSION hSession);

	DirectoryNode* m_root;

	TrackNode* m_trackNode;	
};

class ISO9660Node : public FileSysNode
{
public:
	static ISO9660Node* create(int track, TrackNode* trackNode, BYTE fsExtension = 0);

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual int32 getFileSysType() const {return (m_fsExtension ? m_fsExtension : BS_FS_ISO9660);}

protected:
	ISO9660Node(int track, TrackNode* trackNode, BYTE fsExtension);
	BYTE m_fsExtension;
	SISOVolumeInfo m_info;
};

class UDFNode : public FileSysNode
{
public:
	static UDFNode* create(int track, TrackNode* trackNode);

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual int32 getFileSysType() const {return BS_FS_UDF;}

	static CString udfVersionToString(int32 version);
	static CString partitionToString(int32 partition);

protected:
	UDFNode(int track, TrackNode* trackNode);

	SUDFVolumeInfo m_info;
};

class BootNode : public FileSysNode
{
public:
	static BootNode* create(int track, TrackNode* trackNode);

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual int32 getFileSysType() const {return BS_FS_BOOTABLE;}

protected:
	BootNode(int track, TrackNode* trackNode);

	SBootVolumeInfo m_info;
};

/// Node representing a track
class TrackNode : public ITreeNode
{
public:
	static TrackNode* create(int track);

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual size_t getChildsCount() const { return m_fileSystems.size(); }

	virtual FileSysNode* getChild(int i) const { return m_fileSystems.at(i); }

	~TrackNode();

	const STrackInfo getTrackInfo() { return m_info; };
	

protected:
	TrackNode(int track);

	STrackInfo m_info;
	std::vector<FileSysNode*> m_fileSystems;
};

/// Node representing a session
class SessionNode : public ITreeNode
{
public:
	static SessionNode* create(int session);

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual size_t getChildsCount() const { return m_tracks.size(); }

	virtual TrackNode* getChild(int i) const { return m_tracks.at(i); }

	~SessionNode();

	static CString sessionStatusToString(int32 status);

protected:
	SessionNode(int session);

	int m_session;
	SSessionInfo m_info;
	std::vector<TrackNode*> m_tracks;
};

/// Node representing a disc/medium
class MediumNode : public ITreeNode
{
public:
	static MediumNode* create(const SMediumInfo& info);

	virtual GenericInfo getGenericInfo() const;

	virtual Properties getProperties() const;

	virtual size_t getChildsCount() const { return m_sessions.size(); }

	virtual SessionNode* getChild(int i) const { return m_sessions.at(i); }

	~MediumNode();

	static CString mediumStatusToString(int32 status);

protected:
	MediumNode(const SMediumInfo& info);

	SMediumInfo m_info;
	std::vector<SessionNode*> m_sessions;
};
