using System;
using System.Collections.Generic;
using System.Text;
using IsoSDK;


namespace CSharpImageEditSample
{
    /// Property list
    public class KProperties : List<KeyValuePair<String, String>>
    {
    }
     
    public class GenericInfo
    {
        /// node icon is used to choose an icon for the node
        public enum Icon
        {
            ICON_MEDIUM = 0,
            ICON_SESSION = 0,
            ICON_TRACK_DATA = 0,
            ICON_TRACK_AUDIO = 1,
            ICON_FILESYS_ISO = 2,
            ICON_FILESYS_JOLIET = 2,
            ICON_FILESYS_ROCKRIDGE = 2,
            ICON_FILESYS_UDF = 2,
            ICON_FILESYS_BOOT = 2,
            ICON_DIRECTORY = 3,
            ICON_FILE = 4,
        };

        /// Node name
        public String name;
        /// Node logical block address
        public int lba = 0;
        /// Node size in bytes
        public Int64 size = 0;
        /// Node modification date
        public String date = "N/A";
        /// Node icon
        public Icon icon = Icon.ICON_FILE;
        /// Node name
        public String path;
    };

    public interface ITreeNode
    {
	    /// Get generic information for this node
	    /// Generic info is displayed at right pane of main window
	    GenericInfo getGenericInfo();
        
	    /// Returns special properties of this node
        KProperties getProperties();

	    /// Returns number of child nodes
        int getChildsCount();        
	    /// Returns child node by its number
        ITreeNode getChild(int i);
    }


    public class Helper
    {
        public static String attribsToString(FileAttributes attr)
        {
            String res = "";
            if ((attr & FileAttributes.Archive) == FileAttributes.Archive)
                res += "A ";
            if ((attr & FileAttributes.Hidden) == FileAttributes.Hidden)
                res += "H ";
            if ((attr & FileAttributes.ReadOnly) == FileAttributes.ReadOnly)
                res += "R ";
            if ((attr & FileAttributes.System) == FileAttributes.System)
                res += "S";
            return res;
        }


        public static KProperties fileEntryToProperties(FileEntry entry)
        {
            KProperties props = new KProperties();
            props.Add(new KeyValuePair<string, string>("Name", entry.Name));
            props.Add(new KeyValuePair<string, string>("Address", entry.Address.ToString()));
            props.Add(new KeyValuePair<string, string>("Size", entry.Size.ToString()));
            props.Add(new KeyValuePair<string, string>("Type", ((entry.Attributes & FileAttributes.Directory) == FileAttributes.Directory) ? "Folder" : "File"));
	        props.Add(new KeyValuePair<string, string>("Path", entry.Path));
	        props.Add(new KeyValuePair<string, string>("Attributes", attribsToString(entry.Attributes)));
	       
	        return props;
        }

        public static String formatSize(double sz)
        {
            Int64 size = Convert.ToInt64(sz);
	        if (size == 0)
            {
		        return "0";
            }

	        String res = "";

	        while(size != 0)
	        {
		        int p = (int)(size % 1000);

		        res = p.ToString() + res;

		        size /= 1000;
	        }

	        return res.Trim();
        }
    }
   

    /// Node representing a track
    public class TrackNode : ITreeNode
    {   
        protected TrackInfo m_info;
        protected List<FileSysNode> m_fileSystems = new List<FileSysNode>();

        protected TrackNode(Burner burner, int track)
        {
            // get track information
            m_info = burner.GetTrackInfo((int)DeviceIndex.Read, track);

            if (CommonNet.Functions.HandleError(burner))
	        {
		        m_info.TrackNumber = track;
		        // skip this track
		        return;
	        }

	        if (m_info.Format != TrackFormat.Audio)
	        {
		        // data track
		        // create file system nodes
                if ((m_info.FileSystem & FileSystems.Iso9660) == FileSystems.Iso9660)
		        {
                    m_fileSystems.Add(ISO9660Node.create(burner, track, this));
		        }

                if ((m_info.FileSystem & FileSystems.Joliet) == FileSystems.Joliet)
		        {
                    m_fileSystems.Add(ISO9660Node.create(burner, track, this, (byte)FileSystems.Joliet));
		        }

                if ((m_info.FileSystem & FileSystems.RockRidge) == FileSystems.RockRidge)
                {
                    m_fileSystems.Add(ISO9660Node.create(burner, track, this, (byte)FileSystems.RockRidge));
                }

                if ((m_info.FileSystem & FileSystems.Udf) == FileSystems.Udf)
		        {
                    m_fileSystems.Add( UDFNode.create(burner, track, this) );
		        }

                if ((m_info.FileSystem & FileSystems.Bootable) == FileSystems.Bootable)
		        {
                    m_fileSystems.Add( BootNode.create(burner, track, this) );
		        }
	        }
        }

        public static TrackNode create(Burner burner, int track)
        {
            return new TrackNode(burner, track);
        }

        public virtual GenericInfo getGenericInfo()
        {
            GenericInfo info = new GenericInfo();
            info.name = String.Format("Track {0:D}", m_info.TrackNumber);
	        info.icon = (m_info.Format == TrackFormat.Audio) 
		        ? GenericInfo.Icon.ICON_TRACK_AUDIO
		        : GenericInfo.Icon.ICON_TRACK_DATA;
	        info.lba = m_info.StartLBA;
	        info.size = m_info.Size;

	        return info;
        }

        public virtual KProperties getProperties()
        {
            KProperties props = new KProperties ();            
            props.Add(new KeyValuePair<string, string>("Session", String.Format("{0:D}", m_info.SessionNumber)));

            String trackFormat;
            switch (m_info.Format)
            {
                case TrackFormat.Audio:
                    trackFormat = "Audio"; break;
                case TrackFormat.DataMode1:
                    trackFormat = "Mode 1"; break;
                case TrackFormat.DataMode2:
                    trackFormat = "Mode 2"; break;
                default:
                    trackFormat = "Unknown"; break;
            }

            props.Add(new KeyValuePair<string, string>("Format", trackFormat));

            String trackFS = "";

            if (m_info.FileSystem == FileSystems.Unknown)
                //|| m_info.FileSystem == FileSystems. BS_NDEF)
            {
                trackFS = "Unknown";
            }
            else
            {
                if ((m_info.FileSystem & FileSystems.Iso9660) == FileSystems.Iso9660)
                    trackFS += "ISO9660";
                if ((m_info.FileSystem & FileSystems.Joliet) == FileSystems.Joliet)
                    trackFS += " Joliet";
                if ((m_info.FileSystem & FileSystems.Udf) == FileSystems.Udf)
                    trackFS += " UDF";
                if ((m_info.FileSystem & FileSystems.Bootable) == FileSystems.Bootable)
                    trackFS += " Bootable";
            }

            props.Add(new KeyValuePair<string, string>("File system(s)", trackFS));

            return props;
        }

	    public virtual int getChildsCount() 
        { 
            return m_fileSystems.Count; 
        }

        public virtual ITreeNode getChild(int i)
        { 
            return m_fileSystems[i]; 
        }

	    public TrackInfo getTrackInfo()
        { 
            return m_info; 
        }
    };


    abstract public class FileSysNode : ITreeNode
    {
        public abstract GenericInfo getGenericInfo();

        public abstract KProperties getProperties();

	    public virtual int getChildsCount() 
        { 
            return m_root != null ? m_root.getChildsCount() : 0; 
        }

	    public virtual ITreeNode getChild(int i) 
        { 
            return m_root.getChild(i); 
        }

	    public virtual TrackNode getTrackNode()
        { 
            return m_trackNode; 
        }

        abstract public FileSystems getFileSysType();

        protected FileSysNode(Burner burner, TrackNode trackNode)
        {
            m_trackNode = trackNode;
            m_burner = burner;
        }

        protected void init(DiskSession cSession)
        {
            m_root = new DirectoryNode(m_burner, cSession, "\\", new FileEntry(), this);
        }

	    protected DirectoryNode m_root = null;

        protected TrackNode m_trackNode;

        protected Burner m_burner = null;
    };


    public class DirectoryNode : ITreeNode
    {
	    public DirectoryNode(Burner burner, DiskSession cSession, String path, FileEntry entry, FileSysNode fileSysNode)                
        {
            m_info = entry;
	        m_fileSysNode = fileSysNode;

	        DiskDirectory diskDirectory = cSession.OpenDirectory(path);

	        if (CommonNet.Functions.HandleError(burner))
	        {
		        return;
	        }

            using (diskDirectory)
            {

                int nCount = diskDirectory.FilesCount;
                for (int i = 0; i < nCount; ++i)
                {
                    FileEntry file_entry = diskDirectory.get_Files(i);

                    if (CommonNet.Functions.HandleError(burner))
                    {
                        break;
                    }

                    if ((file_entry.Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                    {
                        m_files.Add(new DirectoryNode(burner, cSession,
                            path + "\\" + file_entry.Name, file_entry, fileSysNode));
                    }
                    else
                    {
                        m_files.Add(new FileNode(cSession, file_entry, fileSysNode));
                    }
                }
            }
        }

	    public virtual GenericInfo getGenericInfo()
        {
            GenericInfo info =  new GenericInfo();
	        info.name = m_info.Name;
	        info.icon = GenericInfo.Icon.ICON_DIRECTORY;
	        info.lba = m_info.Address;
            info.size = m_info.Size;
	        info.date = CommonNet.Functions.formatDate(m_info);
	        info.path = m_info.Path;
	        return info;
        }

	    public virtual KProperties getProperties()
        {
            return Helper.fileEntryToProperties(m_info);
        }

	    public virtual int getChildsCount() 
        { 
            return m_files.Count; 
        }

	    public virtual ITreeNode getChild(int i) 
        { 
            return m_files[i];
        }

	    public virtual FileSysNode getFileSystemNode() 
        { 
            return m_fileSysNode; 
        }

    
	    protected FileEntry m_info;
	    protected List<ITreeNode> m_files = new List<ITreeNode>();
	    protected FileSysNode m_fileSysNode;
    };


    public class FileNode : ITreeNode
    {

        public FileNode(DiskSession cSession, FileEntry entry, FileSysNode fileSysNode)
        {
            m_info = entry;
            m_fileSysNode = fileSysNode;

            string filePath = string.Format("{0}\\{1}", entry.Path, entry.Name);
            m_allocationTable = cSession.GetFileAllocationTable(filePath);
        }

        public virtual GenericInfo getGenericInfo()
        {
            GenericInfo info = new GenericInfo();
	        info.name = m_info.Name;
	        info.icon = GenericInfo.Icon.ICON_FILE;
	        info.lba = m_info.Address;
	        info.size = m_info.Size;
	        info.date = CommonNet.Functions.formatDate(m_info);
	        info.path = m_info.Path;
	        return info;
        }

	    public virtual KProperties getProperties()
        {
            return Helper.fileEntryToProperties(m_info);
        }

	    public virtual int getChildsCount()
        { 
            return 0; 
        }

	    public virtual ITreeNode getChild(int i)
        { 
            return null; 
        }

	    public virtual FileSysNode getFileSystemNode()
        { 
            return m_fileSysNode; 
        }

        public FileAllocationTable AllocationTable
        {
            get { return m_allocationTable; }
        }


	    protected FileEntry m_info;
	    protected FileSysNode m_fileSysNode;
        protected FileAllocationTable m_allocationTable;
};


    public class ISO9660Node : FileSysNode
    {
        public static ISO9660Node create(Burner burner, int track, TrackNode trackNode, byte fsExtension)
        {
            return new ISO9660Node(burner, track, trackNode, fsExtension);
        }

        public static ISO9660Node create(Burner burner, int track, TrackNode trackNode)
        {
            return create(burner, track, trackNode, (byte)FileSystems.Iso9660);
        }

	    public override GenericInfo getGenericInfo()
        {
            GenericInfo info = new GenericInfo();

            switch ((FileSystems)m_fsExtension)
            {
                case FileSystems.Iso9660:
                {
                    info.name = "ISO 9660";
                    info.icon = GenericInfo.Icon.ICON_FILESYS_ISO;
                    break;
                }

                case FileSystems.Joliet:
                {
                    info.name = "Joliet";
                    info.icon = GenericInfo.Icon.ICON_FILESYS_JOLIET;
                    break;
                }

                case FileSystems.RockRidge:
                {
                    info.name = "Rock Ridge";
                    info.icon = GenericInfo.Icon.ICON_FILESYS_ROCKRIDGE;
                    break;
                }
            }

	        info.lba = m_info.VolumeDescriptorAddress;
	        info.size = m_info.VolumeSize;
            info.date = CommonNet.Functions.formatTime(m_info.RootDateTime);
	        return info;
        }

        public override KProperties getProperties()
        {
            KProperties props = new KProperties();

            props.Add(new KeyValuePair<string, string>("Volume label", m_info.VolumeLabel));
            props.Add(new KeyValuePair<string, string>("VD address", m_info.VolumeDescriptorAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("Volume size(blocks)", m_info.VolumeSize.ToString()));
            props.Add(new KeyValuePair<string, string>("Root address", m_info.RootAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("Path table address", m_info.PathTableAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("Path table size", m_info.PathTableSize.ToString()));
            props.Add(new KeyValuePair<string, string>("Abstract Identifier", m_info.AbstractFileIdentifier));
            props.Add(new KeyValuePair<string, string>("Application Identifier", m_info.ApplicationIdentifier));
            props.Add(new KeyValuePair<string, string>("Biblio Identifier", m_info.BiblioIdentifier));
            props.Add(new KeyValuePair<string, string>("Copyright Identifier", m_info.CopyrightFileIdentifier));
            props.Add(new KeyValuePair<string, string>("Data PreparerIdentifier", m_info.DataPreparerIdentifier));
            props.Add(new KeyValuePair<string, string>("Publisher Identifier", m_info.PublisherIdentifier));
            props.Add(new KeyValuePair<string, string>("Set Identifier", m_info.SetIdentifier));
            props.Add(new KeyValuePair<string, string>("System Identifier", m_info.SystemIdentifier));

            props.Add(new KeyValuePair<string, string>("Creation Date", CommonNet.Functions.formatTime(m_info.CreationDateTime)));
            props.Add(new KeyValuePair<string, string>("Modification Date", CommonNet.Functions.formatTime(m_info.ModificationDateTime)));
            props.Add(new KeyValuePair<string, string>("Effective Date", CommonNet.Functions.formatTime(m_info.EffectiveDateTime)));
            props.Add(new KeyValuePair<string, string>("Expiration Date", CommonNet.Functions.formatTime(m_info.ExpirationDateTime)));

            return props;
        }

        public override FileSystems getFileSysType()
        {
            return (FileSystems)m_fsExtension;
        }

        protected ISO9660Node(Burner burner, int track, TrackNode trackNode, byte fsExtension) 
            : base(burner, trackNode)
        {
            m_fsExtension = fsExtension;

            if (CommonNet.Functions.HandleError(burner))
            {
		        // can't read file system
		        // skip this
		        return;
	        }

            using (DiskSession cSession = burner.OpenDiskSession((int)DeviceIndex.Read, track, (FileSystems)m_fsExtension))
            {
                init(cSession);
                m_info = cSession.GetISOVolumeInformation();
            }
        }

        protected byte m_fsExtension;
	    protected ISOVolumeInfo m_info;
    }

    class UDFNode : FileSysNode
    {
        public static UDFNode create(Burner burner, int track, TrackNode trackNode)
        {
            return new UDFNode(burner, track, trackNode);
        }

	    public override GenericInfo getGenericInfo()
        {
            GenericInfo info = new GenericInfo();
	        info.name = "UDF";
	        info.icon = GenericInfo.Icon.ICON_FILESYS_UDF;
	        info.lba = m_info.MVDSAddress;
	        info.size = m_info.PartitionLength;
            info.date = CommonNet.Functions.formatTime(m_info.RecordingDateTime);
            return info;
        }

        String udfVersionToString(UDFVersion version)
        {   
            return String.Format("{0:D}.{0,2:D}", ((int)version >> 8), (int)version & 0xFF);
        }

        String partitionToString(UDFPartitionType partition)
        {
	        switch(partition)
	        {
                case UDFPartitionType.Physical:
		            return "Physical";
                case UDFPartitionType.Virtual:
		            return "Virtual";
                case UDFPartitionType.Sparable:
		            return "Sparable";
	            default:
		            return "Unknown";
	        }
        }

        public override KProperties getProperties()
        {
            KProperties props = new KProperties();
            props.Add(new KeyValuePair<string, string>("Volume label", m_info.VolumeLabel));

            props.Add(new KeyValuePair<string, string>("Preparer", m_info.Preparer));
            props.Add(new KeyValuePair<string, string>("UDF version", udfVersionToString(m_info.Version)));
            props.Add(new KeyValuePair<string, string>("Partition type", partitionToString(m_info.PartitionType)));
            props.Add(new KeyValuePair<string, string>("MVDS address", m_info.MVDSAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("RVDS address", m_info.RVDSAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("Root address", m_info.RootAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("Root (E)FE", m_info.RootFEAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("Partition address", m_info.PartitionAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("Partition length", m_info.PartitionLength.ToString()));
            props.Add(new KeyValuePair<string, string>("LVD", m_info.LVDAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("PVD", m_info.PVDAddress.ToString()));
            props.Add(new KeyValuePair<string, string>("FSD", m_info.FSDAddress.ToString()));
            
            if (m_info.VATAddress != 0)
                props.Add(new KeyValuePair<string, string>("VAT", m_info.VATAddress.ToString()));
            if (m_info.MetadataAddress != 0)
                props.Add(new KeyValuePair<string, string>("Metadata", m_info.MetadataAddress.ToString()));
            if (m_info.SparingAddress != 0)
                props.Add(new KeyValuePair<string, string>("Sparing", m_info.SparingAddress.ToString()));

            props.Add(new KeyValuePair<string, string>("Number of files", m_info.FileCount.ToString()));
            props.Add(new KeyValuePair<string, string>("Number of folders", m_info.DirCount.ToString()));

            props.Add(new KeyValuePair<string, string>("Recording Date", CommonNet.Functions.formatTime(m_info.RecordingDateTime)));
            return props;
        }

        public override FileSystems getFileSysType()
        {
            return FileSystems.Udf;
        }

        protected UDFNode(Burner burner, int track, TrackNode trackNode)
            : base(burner, trackNode)
        {   
	        if (CommonNet.Functions.HandleError(burner))
	        {
		        // can't read file system
		        // skip this
		        return;
	        }

            using (DiskSession cSession = burner.OpenDiskSession((int)DeviceIndex.Read, track, FileSystems.Udf))
            {
                init(cSession);
                m_info = cSession.GetUDFVolumeInformation();
            }
        }

	    protected UDFVolumeInfo m_info;
    };

    class BootNode : FileSysNode
    {
        public static BootNode create(Burner burner, int track, TrackNode trackNode)
        {
            return new BootNode(burner, track, trackNode);
        }

        public override GenericInfo getGenericInfo()
        {
            GenericInfo info = new GenericInfo();
	        info.name = "Boot";
	        info.icon = GenericInfo.Icon.ICON_FILESYS_BOOT;
	        info.lba = m_info.VolumeDescriptorAddress;
	        info.size = 0;
	        return info;
        }

        public override KProperties getProperties()
        {
            KProperties props = new KProperties();

            props.Add(new KeyValuePair<string, string>("Volume descriptor address",
                m_info.VolumeDescriptorAddress.ToString()));

            props.Add(new KeyValuePair<string, string>("Developer ID", m_info.DeveloperID));

            if (m_info.BootIndicator)
            {
                props.Add(new KeyValuePair<string, string>("Boot indicator", "True"));
            }
            else
            {
                props.Add(new KeyValuePair<string, string>("Boot indicator", "False"));
            }

            props.Add(new KeyValuePair<string, string>("Load segment", m_info.LoadSegment.ToString()));
            props.Add(new KeyValuePair<string, string>("Platform ID", m_info.PlatformID.ToString()));
            props.Add(new KeyValuePair<string, string>("Emulation ID", m_info.Emulation.ToString()));
            props.Add(new KeyValuePair<string, string>("Amount of sectors", m_info.SectorCount.ToString()));

            return props;
        }

        public override FileSystems getFileSysType()
        {
            return FileSystems.Bootable;
        }


        protected BootNode(Burner burner, int track, TrackNode trackNode)
            : base(burner, trackNode)
        {
	        if (CommonNet.Functions.HandleError(burner))
	        {
		        // can't read file system
		        // skip this
		        return;
	        }

            using (DiskSession cSession = burner.OpenDiskSession((int)DeviceIndex.Read, track, FileSystems.Bootable))
            {
                init(cSession);
                m_info = cSession.GetBootVolumeInformation();
            }
        }

	    protected BootVolumeInfo m_info;
    }


    class SessionNode : ITreeNode
    {
        public static SessionNode create(Burner burner, int session)
        {
            return new SessionNode(burner, session);
        }

	    public virtual GenericInfo getGenericInfo()
        {
            GenericInfo info = new GenericInfo();
	        info.icon = GenericInfo.Icon.ICON_SESSION;
            info.name = String.Format("Session {0:D}", m_session);
	        info.lba = m_info.StartLBA;
	        info.size = m_info.Size;
	        return info;
        }

	    public virtual KProperties getProperties()
        {
            KProperties props = new KProperties();
            props.Add(new KeyValuePair<string, string>("First track", m_info.FirstTrack.ToString()));
            props.Add(new KeyValuePair<string, string>("Last track", m_info.LastTrack.ToString()));
            props.Add(new KeyValuePair<string, string>("Last session", m_info.LastSession.ToString()));
            Int64 size = ((Int64)m_info.Size) * 2048;
            props.Add(new KeyValuePair<string, string>("Session size", size.ToString()));
            return props;
        }

        public virtual int getChildsCount()
        { 
            return m_tracks.Count;
        }

        public virtual ITreeNode getChild(int i)
        { 
            return m_tracks[i]; 
        }

	    public static String sessionStatusToString(SessionStatus status)
        {
            switch (status)
            {
                case SessionStatus.EmptySession:
                    return "Empty";
                case SessionStatus.IncompleteSession:
                    return "Incomplete";
                case SessionStatus.CompleteSession:
                    return "Complete";
                default:
                    return "Damaged";
            }
        }

        protected SessionNode(Burner burner, int session)
        {
            m_session = session;

            // get session information
	        m_info = burner.GetSessionInfo((int)DeviceIndex.Read, session);
            
            if (CommonNet.Functions.HandleError(burner))
	        {
		        // do not process this session
		        return;
	        }

	        // add tracks
	        for(int track = m_info.FirstTrack; track <= m_info.LastTrack; ++track)
	        {
                m_tracks.Add(TrackNode.create(burner, track));
	        }
        }

	    int m_session;
	    SessionInfo m_info;
	    List<TrackNode> m_tracks = new List<TrackNode> ();
    };

    /// Node representing a disc/medium
    class MediumNode : ITreeNode
    {
        public static MediumNode create(Burner burner, MediumInfo info)
        {
            return new MediumNode(burner, info);
        }

	    public virtual GenericInfo getGenericInfo()
        {
            GenericInfo info = new GenericInfo();
	        info.name = m_info.Type;
            if (m_info.Status == MediumStatus.EmptyDisk)
		        info.name = "Empty " + info.name;

	        info.lba = 0;
	        info.size = (Int64)m_info.Size;
	        info.icon = GenericInfo.Icon.ICON_MEDIUM;
	        return info;
        }

	    public virtual KProperties getProperties()
        {
            KProperties props = new KProperties();
	        props.Add( new KeyValuePair<string, string>("Medium type", m_info.Type) );
	        props.Add( new KeyValuePair<string, string>("Status", mediumStatusToString(m_info.Status)));
            props.Add(new KeyValuePair<string, string>("Size", Helper.formatSize(m_info.Size)));
            props.Add(new KeyValuePair<string, string>("Used", Helper.formatSize(m_info.UsedSize)));
            props.Add(new KeyValuePair<string, string>("Free", Helper.formatSize(m_info.FreeSize)));
	        props.Add( new KeyValuePair<string, string>("Sessions", m_info.LastSession.ToString()));
	        props.Add( new KeyValuePair<string, string>("Tracks", m_info.LastTrack.ToString()));
	        props.Add( new KeyValuePair<string, string>("Last session status", SessionNode.sessionStatusToString(m_info.LastSesionStatus)));
	        props.Add( new KeyValuePair<string, string>("UCP/EAN code", m_info.UPCEANCode));

	        return props;
        }

	    public virtual int getChildsCount()
        { 
            return m_sessions.Count;
        }

        public virtual ITreeNode getChild(int i)
        { 
            return m_sessions[i];
        }

	    public static String mediumStatusToString(MediumStatus status)
        {
            switch (status)
            {
                case MediumStatus.EmptyDisk:
                    return "Empty";
                case MediumStatus.IncompleteDisk:
                    return "Incomplete";
                case MediumStatus.CompleteDisk:
                    return "Complete";
                default:
                    return "Other";
            }
        }

        protected MediumNode(Burner burner, MediumInfo info)
        {
            m_info = info;

	        // create session nodes

	        for(int session = 1; session <= info.LastSession; ++session)
	        {
                SessionNode sessionNode = SessionNode.create(burner, session);
		        m_sessions.Add(sessionNode);
	        }
        }

	    MediumInfo m_info;
	    List<SessionNode> m_sessions = new List<SessionNode>();
    };


}
