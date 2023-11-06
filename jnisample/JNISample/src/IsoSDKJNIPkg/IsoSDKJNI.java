package IsoSDKJNIPkg;

public class IsoSDKJNI {
	
	public static ProgramDirectoryUtilities runFrom;
	public static OperatingSystem osInfo;
	
    public static String getFullPAthOS()
    {
    	String ownPath = "";
    	String libPath = "";
    	ownPath = ProgramDirectoryUtilities.getProgramDirectory();
    	
    	boolean is64 = OperatingSystem.is64bit();
    	if(is64==true) {
    		if(OperatingSystem.isWindows()) {
    			libPath = ownPath.concat("\\jar\\jni\\win64\\IsoSDKJNI.dll");
    		}
        	if(OperatingSystem.isUnix()) {
        		libPath = ownPath.concat("/jar/jni/linux64/libIsoSDKJNI.so");
        	}
        	if(OperatingSystem.isMac()) {
        		libPath = ownPath.concat("/jar/jni/mac64/libIsoSDKJNI.dynlib");
        	}
    	}else {
    		if(OperatingSystem.isWindows()) {
    			libPath = ownPath.concat("\\jar\\jni\\win32\\IsoSDKJNI.dll");
    		}
        	if(OperatingSystem.isUnix()) {
        		libPath = ownPath.concat("/jar/jni/linux32/libIsoSDKJNI.so");
        	}
    	}
    	
    	return libPath;
    }
	
    static {
    	try {
        	System.load(getFullPAthOS());
        } catch (UnsatisfiedLinkError e) {
          System.err.println("Native code library failed to load.\n" + e);
          System.exit(1);
        }
    }
    
    public native String initializeIsoSDK(String mkey);
	public native String drivelist();
	public native int openDevice(int mDevice);
	public native int closeDevice(int mDevice);
	public native int setBurnDevice(String mDrive);
	public native int setReadDevice(String mDrive);
	public native String getBurnDevice();
	public native String getReadDevice();
	public native int addBurnDevice(String mDrive);
	public native int doErase(boolean fast, boolean eject);
	public native int saveLogToFile(String mFile);
	public native int setProject(int mProjectType);
	public native int addFile(String mFilePath, String mDiscPath);
	public native int addFolder(String mFolderPath, String mDiscPath);
	public native int createFolder(String mFolderName, String mDiscPath);
	public native int renameFile(String mFilePath, String mNewFileName);
	public native int removeFile(String mFilePath, String mFileName);
	public native int renameFolder(String mFolderPath, String mNewFolderName);
	public native int removeFolder(String mDiscPath);
	public native int abort();
	public native int deleteProject();
	public native int rescanDevices();
	public native int getProjectType();
	public native int getActiveDevices();
	public native int getLastError();
	public native int doBurn();
	public native int doPrepare();
	public native int isDeviceReady(int mDevice);
	public native int setOptAutoErase(int mValue);
	public native int setImageFilePath(String mPath);
	public native int isImageWriterSelected();
	public native void initializeCallbacks(String dlgClass);
	public native void clearCallbacks();
	public native DriveInfo getDriveInfo();
	public native BurnOptions getOptions();
	public native int setOptions(BurnOptions mOptions);
	public native BootInfo getBootInfo();
	public native int setBootInfo(BootInfo mOptions);
	public native UDFOptions getUDFOptions();
	public native int getUDFOptions(UDFOptions mOptions);
	public native UDFOptionsEx getUDFOptionsEx();
	public native int setUDFOptionsEx(UDFOptionsEx mOptions);
	public native MediumInformation getMediumInformation();
	public native int setISOInfoEx(ISOInfoEx mOptions);
	public native ISOInfoEx getISOInfoEx();
	public native int burnISO(String mPath);
	public native SessionInfo getSessionInformation(int nSession);
	public native TrackInfo getTrackInformation(int nTrack);
	public native ExtendedDeviceInformation getDeviceInformationEx();
	public native int writeTrackToFile(String ltargetPath, int nTrack, int nFormat);
	public native int setFileAttributes(String mFilePath, FileAttributesTimes mAttributes);
	public native int clearAll();	
	public native String getImageFilePath();
	public native String getTrackISRC();
	public native int isValidVideoTsFolder(String mDVDPath);
	public native int analyzeDeviceCapabilitie(long nCapability);
	public native int releaseDeviceCapabilitiesHandle();
	public native int createDeviceCapabilitiesHandle();
	public native int createImage(CreateImageParams mParams, int nType);
	public native int checkFormat(int nType);
	public native int createCDTextReader();
	public native int releaseCDTextReader();
	public native String getCDTextTrackString(int nTrack, int nCDTid);
	public native String getCDTextDiscString(int nCDTid);
	public native int getMaxBurnSpeed(int nDevice);
	public native int getMaxReadSpeed(int nDevice);
	public native int getReadSpeed(int nDevice);
	public native int getBurnSpeed(int nDevice);
	public native int setReadSpeed(int nDevice, int nSpeed);
	public native int setBurnSpeed(int nDevice, int nSpeed);
	public native int playAudioTrack(int nTrack);
}

