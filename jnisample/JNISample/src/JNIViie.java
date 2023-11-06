import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JButton;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JPanel;
import javax.swing.JCheckBox;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.JProgressBar;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JSeparator;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.ImageIcon;

import IsoSDKJNIPkg.*;

import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import java.io.*;
import java.net.*;



public class JNIViie {

	
	
	final static boolean RIGHT_TO_LEFT = false;
	private JFrame frmIsosdkJni;
	public static IsoSDKJNI fromIsoSDKObj = new IsoSDKJNI(); 
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				
				try {
					JNIViie window = new JNIViie();
					window.frmIsosdkJni.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
				

			}
		});

	}

	/**
	 * Create the application.
	 */
	public JNIViie() {
		
		
		
		initialize();
		createMenuBar() ;
		
		String mkey;
		
		if(fromIsoSDKObj.osInfo.isWindows()) {
			mkey = "67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7";
		}else {
			mkey = "3GTF75-2UM4AX-18LAHC-BX1FOR-N38Y32";
		}
		
	
		
		fromIsoSDKObj.initializeIsoSDK(mkey);		
		fromIsoSDKObj.rescanDevices();
		
		
		
		String drives = fromIsoSDKObj.drivelist();
		String[] array = drives.split("\\|", -1);
		
	    final DefaultComboBoxModel model = new DefaultComboBoxModel();
	    for (int i = 0, n = array.length; i < n; i++) {
	      model.addElement(array[i]);
	    }
		driveCB.setModel(model);

		
		fromIsoSDKObj.setProject(7);
		fromIsoSDKObj.getProjectType();
		
		
		
		BurnOptions newOptions = fromIsoSDKObj.getOptions();
		
		diskLabelField.setText(newOptions.volumeLabel);
		chckbxOptOPC.setSelected(newOptions.performOPC);
		chckbxOptBurnProof.setSelected(newOptions.underrunProtection);
		chckbxOptEject.setSelected(newOptions.ejectAfterBurn);
		chckbxOptJoliet.setSelected(newOptions.jolietFileSystem);
		chckbxOptAutoErase.setSelected(newOptions.autoErase);
		chckbxOptFinalize.setSelected(newOptions.finalize);
		chckbxOptVerify.setSelected(newOptions.verifyAfterBurn);
		 
		
		/*
		addFile("/home/osboxes/Downloads/FoxSampleQt.zip", "/");
		renameFile("/FoxSampleQt.zip", "FoxSampleQt5.zip");
		removeFile("/", "FoxSampleQt5.zip");
		
		createFolder("JNIFolder", "/");
		createFolder("JNIFolder2", "/JNIFolder/");
		renameFolder("/JNIFolder/JNIFolder2","JNIFolder3");
		removeFolder("/JNIFolder/JNIFolder2");
		removeFolder("/JNIFolder/JNIFolder3");
		
		addFolder("/home/osboxes/Downloads/FoxSampleQt", "/");
		 */

	}
	
    private void createMenuBar() {

    	JMenuBar menuBar = new JMenuBar();

    	JMenu fileMenu = new JMenu("File");
        fileMenu.setMnemonic(KeyEvent.VK_F);
        
        JMenuItem eAddFileItem = new JMenuItem("Add file");
        eAddFileItem.setToolTipText("Select and add file");
        eAddFileItem.addActionListener((event) -> selectAndAddFile());
        fileMenu.add(eAddFileItem);

        JMenuItem eAddFolderItem = new JMenuItem("Add folder");
        eAddFolderItem.setToolTipText("Select and add folder");
        eAddFolderItem.addActionListener((event) -> selectAndAddFolder());
        fileMenu.add(eAddFolderItem);
        
        fileMenu.addSeparator();
        
        JMenuItem eSequenceItem = new JMenuItem("Create Folder Sequence");
        eSequenceItem.setToolTipText("Create Folder, rename and remove as sequence");
        eSequenceItem.addActionListener((event) -> createFolderSequence());
        fileMenu.add(eSequenceItem);
        
        fileMenu.addSeparator();
        
        JMenuItem eLogItem = new JMenuItem("Save log file");
        eLogItem.setToolTipText("Save the log to a text file");
        eLogItem.addActionListener((event) -> savelog());
        fileMenu.add(eLogItem);
        JMenuItem eResetListItem = new JMenuItem("Reset log");
        eResetListItem.setToolTipText("Reset the log list");
        eResetListItem.addActionListener((event) -> clearList());
        fileMenu.add(eResetListItem);
        
        fileMenu.addSeparator();
        
        JMenuItem eMenuItem = new JMenuItem("Exit");
        eMenuItem.setMnemonic(KeyEvent.VK_E);
        eMenuItem.setToolTipText("Exit application");
        eMenuItem.addActionListener((event) -> System.exit(0));
        fileMenu.add(eMenuItem);
        
        
        JMenu helperMenu = new JMenu("Helpers");

        JMenuItem eSettCalbacksItem = new JMenuItem("Activate callbacks");
        eSettCalbacksItem.setToolTipText("Activate the callbacks to get information");
        eSettCalbacksItem.addActionListener((event) -> setCallbacks());
        helperMenu.add(eSettCalbacksItem);
        JMenuItem eResettCalbacksItem = new JMenuItem("Clear callbacks");
        eResettCalbacksItem.setToolTipText("Reset the callbacks");
        eResettCalbacksItem.addActionListener((event) -> resetCallbacks());
        helperMenu.add(eResettCalbacksItem); 

        helperMenu.addSeparator();

        JMenuItem eGetOptionsItem = new JMenuItem("Get options");
        eGetOptionsItem.setToolTipText("Get the options for the current project");
        eGetOptionsItem.addActionListener((event) -> getProjectOptions()); 
        helperMenu.add(eGetOptionsItem);
        JMenuItem eSetOptionsItem = new JMenuItem("Set options");
        eSetOptionsItem.setToolTipText("Set the options for the current projetc");
        eSetOptionsItem.addActionListener((event) -> setProjectOptions()); 
        helperMenu.add(eSetOptionsItem);

        helperMenu.addSeparator();
        
        
        JMenu driveMenu = new JMenu("Drive functions");
        JMenuItem eGetBurnDeviceItem = new JMenuItem("Get burn device");
        eGetBurnDeviceItem.setToolTipText("Get the name of the current burn device");
        eGetBurnDeviceItem.addActionListener((event) -> getCurrentBurnDevice());
        driveMenu.add(eGetBurnDeviceItem);
        JMenuItem eGetReadDeviceItem = new JMenuItem("Get read device");
        eGetReadDeviceItem.setToolTipText("Get the name of the current read device");
        eGetReadDeviceItem.addActionListener((event) -> getCurrentReadDevice()); 
        driveMenu.add(eGetReadDeviceItem);
        JMenuItem eGetDriveInfoItem = new JMenuItem("Get drive info");
        eGetDriveInfoItem.setToolTipText("Get basic infos about the drive");
        eGetDriveInfoItem.addActionListener((event) -> getDriveInfos()); 
        driveMenu.add(eGetDriveInfoItem);
        JMenuItem eOpenDeviceItem = new JMenuItem("Open device");
        eOpenDeviceItem.setToolTipText("Open the tray of a drive");
        eOpenDeviceItem.addActionListener((event) -> fromIsoSDKObj.openDevice(-1));
        driveMenu.add(eOpenDeviceItem);
        JMenuItem eCloseDeviceItem = new JMenuItem("Close device");
        eCloseDeviceItem.setToolTipText("Close the tray of a drive");
        eCloseDeviceItem.addActionListener((event) -> fromIsoSDKObj.closeDevice(-1));
        driveMenu.add(eCloseDeviceItem);
        JMenuItem eDeviceInfoExItem = new JMenuItem("Drive info ex");
        eDeviceInfoExItem.setToolTipText("Extended Drive Info");
        eDeviceInfoExItem.addActionListener((event) -> getDriveInfosEx());
        driveMenu.add(eDeviceInfoExItem);
        JMenuItem eSetReadDeviceItem = new JMenuItem("Set read device");
        eSetReadDeviceItem.setToolTipText("Set the current selected drive as read device");
        eSetReadDeviceItem.addActionListener((event) -> setReadDevice());
        driveMenu.add(eSetReadDeviceItem);
        helperMenu.add(driveMenu); 
        JMenu mediumMenu = new JMenu("Medium functions");
        JMenuItem eGetMediumInfoItem = new JMenuItem("Get medium info");
        eGetMediumInfoItem.setToolTipText("Get basic infos about th medium");
        eGetMediumInfoItem.addActionListener((event) -> getMediumInfos()); 
        mediumMenu.add(eGetMediumInfoItem); 
        JMenuItem eGetSessionInfoItem = new JMenuItem("Get session info");
        eGetSessionInfoItem.setToolTipText("Get information about the given session index");
        eGetSessionInfoItem.addActionListener((event) -> getSessionInformation()); 
        mediumMenu.add(eGetSessionInfoItem); 
        JMenuItem eGetTrackInfoItem = new JMenuItem("Get track info");
        eGetTrackInfoItem.setToolTipText("Get information about the given track index");
        eGetTrackInfoItem.addActionListener((event) -> getTrackInformation()); 
        mediumMenu.add(eGetTrackInfoItem); 
        JMenuItem eWriteTagItem = new JMenuItem("Track to file");
        eWriteTagItem.setToolTipText("Write track to target file format");
        eWriteTagItem.addActionListener((event) -> saveTrackToFile()); 
        mediumMenu.add(eWriteTagItem);
        helperMenu.add(mediumMenu); 
        
        JMenu projectMenu = new JMenu("Project functions");
        JMenuItem eSetISOInfoExItem = new JMenuItem("Set ISOInfoEx");
        eSetISOInfoExItem.setToolTipText("Set ISOInfoEx with pseudo data");
        eSetISOInfoExItem.addActionListener((event) -> setISOEx()); 
        projectMenu.add(eSetISOInfoExItem); 
        JMenuItem eGetISOInfoExItem = new JMenuItem("Get ISOInfoEx");
        eGetISOInfoExItem.setToolTipText("Get ISOInfoEx information");
        eGetISOInfoExItem.addActionListener((event) -> getISOEx()); 
        projectMenu.add(eGetISOInfoExItem); 
        helperMenu.add(projectMenu); 
        
        //Action
        JMenu actionMenu = new JMenu("Action");
        JMenuItem eBurnISOItem = new JMenuItem("Burn to ISO");
        eBurnISOItem.addActionListener((event) -> burnToISO());
        eBurnISOItem.setToolTipText("Burn to ISO file");
        actionMenu.add(eBurnISOItem);

        JMenuItem eBurnFromISOItem = new JMenuItem("Burn from ISO");
        eBurnFromISOItem.addActionListener((event) -> burnISOFile());
        eBurnFromISOItem.setToolTipText("Burn ISO file to disc");
        actionMenu.add(eBurnFromISOItem);
        
        JMenuItem eBurnDiskItem = new JMenuItem("Burn Disk");
        eBurnDiskItem.addActionListener((event) -> burnToDisk());
        eBurnDiskItem.setToolTipText("Burn to Disk");
        actionMenu.add(eBurnDiskItem);
        
        actionMenu.addSeparator();
        
        JMenuItem eEraseItem = new JMenuItem("Erase");
        eEraseItem.addActionListener((event) -> eraseDisk());
        eEraseItem.setToolTipText("Erase RW");
        actionMenu.add(eEraseItem);

        menuBar.add(fileMenu);
        menuBar.add(helperMenu);
        menuBar.add(actionMenu);
        frmIsosdkJni.setJMenuBar(menuBar);

    }
    
    public static void printEraseDone(String nError)
    {
    	logModel.add(logModel.getSize(), "Erase Done: " + nError);
    }
    
	public static void printVerifyStart()
	{
		logModel.add(logModel.getSize(), "Verify Start");
			
	}
	
	public static void printVerifyFile(String nFile)
	{
		
		logModel.add(logModel.getSize(), "Verify file: " + nFile);
			
	}
	
	public static void printVerifyError(String nFile, String nError)
	{
		
		logModel.add(logModel.getSize(), "Error file: " + nFile);
		logModel.add(logModel.getSize(), "Error: " + nError);
			
	}
	
	public static void printVerifyDone(int nCount)
	{
		logModel.add(logModel.getSize(), "Verify done. Errors: " + Integer.toString(nCount));
			
	}

	public static void printBurnFile(String nFile)
	{
		
		logModel.add(logModel.getSize(), "Burn file: " + nFile);
			
	}
	
	public static void printProcess(float nValue)
	{
		progressBar.setValue((int)nValue);
			
	}
	
	public static void printJobDone()
	{
		
		logModel.add(logModel.getSize(), "Job Done");
			
	}
	
	public static void printFinalize()
	{
		
		logModel.add(logModel.getSize(), "Finalize");
			
	}
	
	public static void printBurnDone(String nError)
	{
		
		logModel.add(logModel.getSize(), nError);
			
	}
	
	private void saveTrackToFile() {
		
		int ourTarget = 1; //0=Wave/Audio 1=ISO 2=BIN 3=MPEG
				
		JFileChooser fileChooser = new JFileChooser();
        fileChooser.setAcceptAllFileFilterUsed( false );
        FileNameExtensionFilter filter = null;
        switch ( ourTarget ) {
	        case 0:
	        	filter = new FileNameExtensionFilter( "Audio file", "pcm" );
	        	break;
	        case 1:
	        	filter = new FileNameExtensionFilter( "ISO file", "iso" );
	        	break;
	        case 2:
	        	filter = new FileNameExtensionFilter( "MPEG video", "mpg" );
	        	break;
        }
        
        fileChooser.addChoosableFileFilter( filter );
		fileChooser.setDialogTitle( "Select target file" ); 
		int userSelection = fileChooser.showSaveDialog( frmIsosdkJni );
		
		if ( userSelection == JFileChooser.APPROVE_OPTION ) {
			File fileToSave = fileChooser.getSelectedFile();
			int res = fromIsoSDKObj.writeTrackToFile( fileToSave.getAbsolutePath(), 1, ourTarget );
			logModel.add( logModel.getSize(), "WriteTrack: " + Integer.toString( res ) );
		}
		
	}
	
	private void getSessionInformation() {
		SessionInfo newSessionInfo = fromIsoSDKObj.getSessionInformation(1);
		if(newSessionInfo != null) {
			logModel.add(logModel.getSize(), "Session size: " + Long.toString(newSessionInfo.sessionSize));
			logModel.add(logModel.getSize(), "Last session: " + Boolean.toString(newSessionInfo.lastSession));
			logModel.add(logModel.getSize(), "Start LBA: " + Long.toString(newSessionInfo.startLBA));
			logModel.add(logModel.getSize(), "First track: " + Long.toString(newSessionInfo.firstTrack));
			logModel.add(logModel.getSize(), "Last track: " + Long.toString(newSessionInfo.lastTrack));	
		}

	}
	
	private void getTrackInformation() {
		TrackInfo newTrackInfo = fromIsoSDKObj.getTrackInformation(1);
		if(newTrackInfo != null) {
			logModel.add(logModel.getSize(), "Track number: " + Short.toString(newTrackInfo.trackNumber));
			logModel.add(logModel.getSize(), "Session number: " + Short.toString(newTrackInfo.sessionNumber));
			logModel.add(logModel.getSize(), "Start LBA: " + Integer.toString(newTrackInfo.startLBA));
			logModel.add(logModel.getSize(), "Track size: " + Integer.toString(newTrackInfo.trackSize));
			logModel.add(logModel.getSize(), "Track format: " + Integer.toString(newTrackInfo.trackFormat));	
			
			if((newTrackInfo.trackFS & 0)==0) {
				logModel.add(logModel.getSize(), "Track file system: Unknown");
			}
			if((newTrackInfo.trackFS & 1)==1) {
				logModel.add(logModel.getSize(), "Track file system: ISO9660");
			}
			if((newTrackInfo.trackFS & 2)==2) {
				logModel.add(logModel.getSize(), "Track file system: Joliet");
			}
			if((newTrackInfo.trackFS & 4)==4) {
				logModel.add(logModel.getSize(), "Track file system: UDF");
			}
			if((newTrackInfo.trackFS & 8)==8) {
				logModel.add(logModel.getSize(), "Track file system: Bootable");
			}
			if((newTrackInfo.trackFS & 16)==16) {
				logModel.add(logModel.getSize(), "Track file system: RockRidge");
			}
		}

	}
	
	private void getProjectOptions() {
		BurnOptions newOptions = fromIsoSDKObj.getOptions();
		if(newOptions != null) {
			logModel.add(logModel.getSize(), newOptions.volumeLabel);
			logModel.add(logModel.getSize(), "Bootable: " + Boolean.toString(newOptions.bootable));
			logModel.add(logModel.getSize(), "AutoErase: " + Boolean.toString(newOptions.autoErase));
			logModel.add(logModel.getSize(), "EjectAfterBurn: " + Boolean.toString(newOptions.ejectAfterBurn));
			logModel.add(logModel.getSize(), "Finalize: " + Boolean.toString(newOptions.finalize));
			logModel.add(logModel.getSize(), "Joliet: " + Boolean.toString(newOptions.jolietFileSystem));
			logModel.add(logModel.getSize(), "PadDataTracks: " + Boolean.toString(newOptions.padDataTracks));
			logModel.add(logModel.getSize(), "OPC: " + Boolean.toString(newOptions.performOPC));
			logModel.add(logModel.getSize(), "RockRidge: " + Boolean.toString(newOptions.rockRidgeFileSystem));
			logModel.add(logModel.getSize(), "TestBurn: " + Boolean.toString(newOptions.testBurn));
			logModel.add(logModel.getSize(), "BurnProof: " + Boolean.toString(newOptions.underrunProtection));
			logModel.add(logModel.getSize(), "Verify: " + Boolean.toString(newOptions.verifyAfterBurn));
			logModel.add(logModel.getSize(), "Cache: " + Integer.toString(newOptions.cacheSize));
			logModel.add(logModel.getSize(), "WriteMethod: " + Integer.toString(newOptions.writeMethod));
			logModel.add(logModel.getSize(), "BootImage: " + newOptions.bootImage);
		}

		
	}
	
	private void setProjectOptions() {
		setUiOptions();
	}
	
	private void setISOEx() {
		ISOInfoEx newInfo = fromIsoSDKObj.getISOInfoEx();
		newInfo.iSOUseCreationDateTime = true;
		//%Y/%m/%d %H:%M:%S
		newInfo.iSOCreationDateTime = "2022/3/22 11:11:11";
		fromIsoSDKObj.setISOInfoEx(newInfo);
	}
	
	private void getISOEx() {
		ISOInfoEx newInfo = fromIsoSDKObj.getISOInfoEx();
		if(newInfo != null) {
			logModel.add(logModel.getSize(), "ISOAbstractFileIdentifier: " + newInfo.iSOAbstractFileIdentifier);
			logModel.add(logModel.getSize(), "ISOApplicationIdentifier: " + newInfo.iSOApplicationIdentifier);
			logModel.add(logModel.getSize(), "ISOBiblioIdentifier: " + newInfo.iSOBiblioIdentifier);
			logModel.add(logModel.getSize(), "ISOCopyrightFileIdentifier: " + newInfo.iSOCopyrightFileIdentifier);
			logModel.add(logModel.getSize(), "ISODataPreparerIdentifier: " + newInfo.iSODataPreparerIdentifier);
			logModel.add(logModel.getSize(), "ISOPublisherIdentifier: " + newInfo.iSOPublisherIdentifier);
			logModel.add(logModel.getSize(), "ISOSetIdentifier: " + newInfo.iSOSetIdentifier);
			logModel.add(logModel.getSize(), "ISOSystemIdentifier: " + newInfo.iSOSystemIdentifier);
			logModel.add(logModel.getSize(), "ISOAddSuffix: " + Boolean.toString(newInfo.iSOAddSuffix));
			logModel.add(logModel.getSize(), "ISOLevel: " + Integer.toString(newInfo.iSOLevel));
			logModel.add(logModel.getSize(), "ISOAllowManyDirectories: " + Boolean.toString(newInfo.iSOAllowManyDirectories));
			logModel.add(logModel.getSize(), "ISOAllowLowercaseNames: " + Boolean.toString(newInfo.iSOAllowLowercaseNames));
			logModel.add(logModel.getSize(), "ISOAllowLongISO9660Names: " + Boolean.toString(newInfo.iSOAllowLongISO9660Names));
			logModel.add(logModel.getSize(), "ISOAllowLongJolietNames: " + Boolean.toString(newInfo.iSOAllowLongJolietNames));
			logModel.add(logModel.getSize(), "ISOUseCreationDateTime: " + Boolean.toString(newInfo.iSOUseCreationDateTime));
			logModel.add(logModel.getSize(), "ISOCreationDateTime: " + newInfo.iSOCreationDateTime);
			logModel.add(logModel.getSize(), "ISOUseModificationDateTime: " + Boolean.toString(newInfo.iSOUseModificationDateTime));
			logModel.add(logModel.getSize(), "ISOModificationDateTime: " + newInfo.iSOModificationDateTime);
			logModel.add(logModel.getSize(), "ISOUseExpirationDateTime: " + Boolean.toString(newInfo.iSOUseExpirationDateTime));
			logModel.add(logModel.getSize(), "ISOExpirationDateTime: " + newInfo.iSOExpirationDateTime);
			logModel.add(logModel.getSize(), "ISOUseEffectiveDateTime: " + Boolean.toString(newInfo.iSOUseEffectiveDateTime));
			logModel.add(logModel.getSize(), "ISOEffectiveDateTime: " + newInfo.iSOEffectiveDateTime);			
		}

	}
	
	private void getMediumInfos() {
		
		MediumInformation newInfo = fromIsoSDKObj.getMediumInformation();
		if(newInfo != null) {
			logModel.add(logModel.getSize(), "Medium type: " + newInfo.mediumType);
			logModel.add(logModel.getSize(), "UPCEAN code: " + newInfo.uPCEANCode);
			logModel.add(logModel.getSize(), "Vendor Id: " + newInfo.vendorId);
			logModel.add(logModel.getSize(), "Medium status: " + Integer.toString(newInfo.mediumStatus));
			logModel.add(logModel.getSize(), "First session: " + Integer.toString(newInfo.firstSession));
			logModel.add(logModel.getSize(), "Last session: " + Integer.toString(newInfo.lastSession));
			logModel.add(logModel.getSize(), "First track: " + Integer.toString(newInfo.firstTrack));
			logModel.add(logModel.getSize(), "Last track: " + Integer.toString(newInfo.lastTrack));
			logModel.add(logModel.getSize(), "Last session status: " + Integer.toString(newInfo.lastSessionStatus));
			logModel.add(logModel.getSize(), "Medium size: " + Double.toString(newInfo.mediumSize));
			logModel.add(logModel.getSize(), "Medium used size: " + Double.toString(newInfo.mediumUsedSize));
			logModel.add(logModel.getSize(), "Medium free size: " + Double.toString(newInfo.mediumFreeSize));
			logModel.add(logModel.getSize(), "Medium type code: " + Short.toString(newInfo.mediumTypeCode));
			logModel.add(logModel.getSize(), "Extended medium type: " + Short.toString(newInfo.extendedMediumType));	
		}

	}
	
	private void getDriveInfosEx() {
		ExtendedDeviceInformation newInfo = fromIsoSDKObj.getDeviceInformationEx();
		if(newInfo != null) {
			logModel.add(logModel.getSize(), "Drive name: " + newInfo.strName);
			logModel.add(logModel.getSize(), "Revision: " + newInfo.strRevision);
			logModel.add(logModel.getSize(), "Loader type: " + newInfo.loaderType);
			logModel.add(logModel.getSize(), "Connection interface: " + newInfo.connectionInterface);
			logModel.add(logModel.getSize(), "Physical interface: " + newInfo.physicalInterface);
			logModel.add(logModel.getSize(), "Serial number: " + newInfo.serialNumber);
			logModel.add(logModel.getSize(), "Region code: " + Integer.toString(newInfo.regionCode));
			logModel.add(logModel.getSize(), "Region code changes left: " + Integer.toString(newInfo.regionCodeChangesLeft));
			logModel.add(logModel.getSize(), "Number of volume levels: " + Integer.toString(newInfo.numberOfVolumeLevels));
			logModel.add(logModel.getSize(), "Buffer size: " + Integer.toString(newInfo.bufferSize));
			logModel.add(logModel.getSize(), "Read retry count: " + Integer.toString(newInfo.readRetryCount));
			logModel.add(logModel.getSize(), "Region code vendor reset left: " + Integer.toString(newInfo.regionCodeVendorResetLeft));
			logModel.add(logModel.getSize(), "IDE transfer mode: " + Integer.toString(newInfo.iDETransfermode));
		}
	}
	
	private void getDriveInfos() {

		DriveInfo newInfo = fromIsoSDKObj.getDriveInfo();
		if(newInfo != null) {
			logModel.add(logModel.getSize(), newInfo.vendorId);
			logModel.add(logModel.getSize(), newInfo.productId);
			logModel.add(logModel.getSize(), newInfo.productRevision);
		}

	}
	
	private void getCurrentReadDevice() {
		logModel.add(logModel.getSize(), "Read Device: " + fromIsoSDKObj.getReadDevice());
	}
	
	private void getCurrentBurnDevice() {
		logModel.add(logModel.getSize(), "Burn Device: " + fromIsoSDKObj.getBurnDevice());
	}
	
	private void selectAndAddFile() {
		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setDialogTitle("Add file to burn"); 
		int userSelection = fileChooser.showOpenDialog(frmIsosdkJni);
		
		if (userSelection == JFileChooser.APPROVE_OPTION) {
			File fileToSave = fileChooser.getSelectedFile();
			logModel.add(logModel.getSize(), "Add File: " + fileToSave.getAbsolutePath());
			int res = -1;
			if(fromIsoSDKObj.osInfo.isWindows()) {
				res = fromIsoSDKObj.addFile(fileToSave.getAbsolutePath(), "\\");
			}else {
				res = fromIsoSDKObj.addFile(fileToSave.getAbsolutePath(), "/");
			}
			logModel.add(logModel.getSize(), "Added: " + Integer.toString(res));
		}
		
	}
	
	private void selectAndAddFolder() {
		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setDialogTitle("Add folder to burn"); 
		fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		int userSelection = fileChooser.showOpenDialog(frmIsosdkJni);
		
		if (userSelection == JFileChooser.APPROVE_OPTION) {
			File fileToSave = fileChooser.getSelectedFile();
			logModel.add(logModel.getSize(), "Add File: " + fileToSave.getAbsolutePath());
			int res = -1;
			if(fromIsoSDKObj.osInfo.isWindows()) {
				res = fromIsoSDKObj.addFolder(fileToSave.getAbsolutePath(), "\\");
			}else {
				res = fromIsoSDKObj.addFolder(fileToSave.getAbsolutePath(), "/");
			}
			logModel.add(logModel.getSize(), "Added: " + Integer.toString(res));
		}
		
	}
	
	private void createFolderSequence() {
		logModel.add(logModel.getSize(), "Create Folder: JNIFolder in root");
		int res = -1;
		if(fromIsoSDKObj.osInfo.isWindows()) {
			res = fromIsoSDKObj.createFolder("JNIFolder", "\\");
		}else {
			res = fromIsoSDKObj.createFolder("JNIFolder", "/");
		}
		logModel.add(logModel.getSize(), "Created: " + Integer.toString(res));
		
		logModel.add(logModel.getSize(), "Create Folder: JNIFolder2 in /JNIFolder/");
		if(fromIsoSDKObj.osInfo.isWindows()) {
			res = fromIsoSDKObj.createFolder("JNIFolder2", "\\JNIFolder\\");
		}else {
			res = fromIsoSDKObj.createFolder("JNIFolder2", "/JNIFolder/");
		}
		logModel.add(logModel.getSize(), "Created: " + Integer.toString(res));
		
		logModel.add(logModel.getSize(), "Rename Folder: JNIFolder2 to NIFolder3");
		if(fromIsoSDKObj.osInfo.isWindows()) {
			res = fromIsoSDKObj.renameFolder("\\JNIFolder\\JNIFolder2","JNIFolder3");
		}else {
			res = fromIsoSDKObj.renameFolder("/JNIFolder/JNIFolder2","JNIFolder3");
		}
		logModel.add(logModel.getSize(), "Renamed: " + Integer.toString(res));
		
		logModel.add(logModel.getSize(), "Remove Folder: JNIFolder2");
		if(fromIsoSDKObj.osInfo.isWindows()) {
			res = fromIsoSDKObj.removeFolder("\\JNIFolder\\JNIFolder2");
		}else {
			res = fromIsoSDKObj.removeFolder("/JNIFolder/JNIFolder2");
		}
		logModel.add(logModel.getSize(), "Removed: " + Integer.toString(res));
		
		logModel.add(logModel.getSize(), "Remove Folder: JNIFolder3");
		
		if(fromIsoSDKObj.osInfo.isWindows()) {
			res = fromIsoSDKObj.removeFolder("\\JNIFolder\\JNIFolder3");
		}else {
			res = fromIsoSDKObj.removeFolder("/JNIFolder/JNIFolder3");
		}
		logModel.add(logModel.getSize(), "Removed: " + Integer.toString(res));

	}
	
	private void eraseDisk() {
		
		int res = fromIsoSDKObj.doErase(true,true);
		logModel.add(logModel.getSize(), "Erase RW: " + Integer.toString(res));
	}
	
	private void burnISOFile() {
		//Select the ISO
		JFileChooser fileChooser = new JFileChooser();
        fileChooser.setAcceptAllFileFilterUsed(false);
        FileNameExtensionFilter filter = new FileNameExtensionFilter("ISO Images", "iso");
        fileChooser.addChoosableFileFilter(filter);
		fileChooser.setDialogTitle("Add ISO to burn"); 
		int userSelection = fileChooser.showOpenDialog(frmIsosdkJni);
		
		if (userSelection == JFileChooser.APPROVE_OPTION) {
			File fileToSave = fileChooser.getSelectedFile();
			logModel.add(logModel.getSize(), "ISO file: " + fileToSave.getAbsolutePath());
			int res = fromIsoSDKObj.burnISO(fileToSave.getAbsolutePath());
			logModel.add(logModel.getSize(), "BurnISO: " + Integer.toString(res));
		}
	}
	
	private void burnToISO() {
		setUiOptions();
		if(fromIsoSDKObj.isImageWriterSelected()==1) {
			logModel.add(logModel.getSize(), "ImageWriter selected");
			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setDialogTitle("Specify ISO file");   
			 
			int userSelection = fileChooser.showSaveDialog(frmIsosdkJni);
			 
			if (userSelection == JFileChooser.APPROVE_OPTION) {
			    File fileToSave = fileChooser.getSelectedFile();
			    logModel.add(logModel.getSize(), "SetImageFilePath: " + fileToSave.getAbsolutePath());
			    fromIsoSDKObj.setImageFilePath(fileToSave.getAbsolutePath());
			    int res = fromIsoSDKObj.doPrepare();
			    logModel.add(logModel.getSize(), "Prepare: " + Integer.toString(res));
			    res = fromIsoSDKObj.doBurn();
			    logModel.add(logModel.getSize(), "Burn: " + Integer.toString(res));
			}
			
		}
		
	}
	
	private void savelog() {
		
		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setDialogTitle("Specify log file");   
			 
		int userSelection = fileChooser.showSaveDialog(frmIsosdkJni);
			 
		if (userSelection == JFileChooser.APPROVE_OPTION) {
			File fileToSave = fileChooser.getSelectedFile();
			logModel.add(logModel.getSize(), "SetLogPath: " + fileToSave.getAbsolutePath());
			fromIsoSDKObj.saveLogToFile(fileToSave.getAbsolutePath());
	
		}
			
	
		
	}
	
	
	private void setCallbacks() {
		logModel.add(logModel.getSize(), "Set callbacks");
		fromIsoSDKObj.initializeCallbacks("JNIViie");
	}
	
	private void resetCallbacks() {
		logModel.add(logModel.getSize(), "Clear callbacks");
		fromIsoSDKObj.clearCallbacks();
	}	
	
	private void burnToDisk() {
		logModel.add(logModel.getSize(), "Set Options");
		setUiOptions();
		int res = fromIsoSDKObj.doPrepare();
		logModel.add(logModel.getSize(), "Prepare: " + Integer.toString(res));
		res = fromIsoSDKObj.doBurn();
		logModel.add(logModel.getSize(), "Burn: " + Integer.toString(res));
	}
	
	private void clearList() {
		logModel.clear();
	}
	
	private void setReadDevice() {
        String a = driveCB.getSelectedItem().toString();
        fromIsoSDKObj.setReadDevice(a.trim());
	}
	
	private void setUiOptions() {
		
		BurnOptions newOptions = new BurnOptions();
		newOptions.volumeLabel = diskLabelField.getText();
		newOptions.jolietFileSystem = chckbxOptJoliet.isSelected();
		newOptions.autoErase = chckbxOptAutoErase.isSelected();
		newOptions.performOPC = chckbxOptOPC.isSelected();
		newOptions.underrunProtection = chckbxOptBurnProof.isSelected();
		newOptions.ejectAfterBurn = chckbxOptEject.isSelected();
		newOptions.finalize = chckbxOptFinalize.isSelected();
		newOptions.verifyAfterBurn = chckbxOptVerify.isSelected();
		fromIsoSDKObj.setOptions(newOptions);
		//setOptJoliet(chckbxOptJoliet.isSelected()? 1 : 0);
		 
	}

	private void initialize() {
		

		
		frmIsosdkJni = new JFrame();
		frmIsosdkJni.setTitle("IsoSDK JNI");
		frmIsosdkJni.setBounds(100, 100, 450, 457);
		frmIsosdkJni.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		
		URL iconURL = getClass().getResource("/isosdksample.png");
		ImageIcon icon = new ImageIcon(iconURL);
		frmIsosdkJni.setIconImage(icon.getImage());

		addComponentsToPane(frmIsosdkJni.getContentPane());
	

		

	}
	
	public void addComponentsToPane(Container pane) {
		
        if (RIGHT_TO_LEFT) {
            pane.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
        }
 

        pane.setLayout(new GridBagLayout());
        
        
        lblDriveLabel = new JLabel("Drive: ");
		GridBagConstraints gbc_lblDriveLabel = new GridBagConstraints();
		gbc_lblDriveLabel.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblDriveLabel.anchor = GridBagConstraints.EAST;
		gbc_lblDriveLabel.gridx = 0;
		gbc_lblDriveLabel.gridy = 0;
		gbc_lblDriveLabel.weightx = 1.0;
		gbc_lblDriveLabel.weighty = 0;
		pane.add(lblDriveLabel, gbc_lblDriveLabel);
		
		driveCB = new javax.swing.JComboBox();
		driveCB.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if(e.getStateChange() == ItemEvent.SELECTED) {
	                String a = driveCB.getSelectedItem().toString();
	                fromIsoSDKObj.setBurnDevice(a.trim());
	            }
			}
		});
		GridBagConstraints gbc_comboBox = new GridBagConstraints();
		gbc_comboBox.insets = new Insets(0, 0, 5, 0);
		gbc_comboBox.fill = GridBagConstraints.HORIZONTAL;
		gbc_comboBox.gridx = 1;
		gbc_comboBox.gridy = 0;
		gbc_comboBox.weightx = 1.0;
		gbc_comboBox.weighty = 0;
		gbc_comboBox.gridwidth = 2;
		pane.add(driveCB, gbc_comboBox);
        
        lblDiskNameLabel = new JLabel("Label: ");
		GridBagConstraints gbc_lblDiskNameLabel = new GridBagConstraints();
		gbc_lblDiskNameLabel.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblDiskNameLabel.anchor = GridBagConstraints.EAST;
		gbc_lblDiskNameLabel.gridx = 0;
		gbc_lblDiskNameLabel.gridy = 1;
		gbc_lblDiskNameLabel.weightx = 1.0;
		gbc_lblDiskNameLabel.weighty = 0;
		pane.add(lblDiskNameLabel, gbc_lblDiskNameLabel);
		
		diskLabelField = new JTextField();
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField.gridx = 1;
		gbc_textField.gridy = 1;
		gbc_textField.weightx = 1.0;
		gbc_textField.weighty = 0;
		gbc_textField.gridwidth = 2;
		pane.add(diskLabelField, gbc_textField);
		diskLabelField.setColumns(10);
		
		JSeparator sLine = new JSeparator(); 
		GridBagConstraints gbc_sLine = new GridBagConstraints();
		gbc_sLine.insets = new Insets(10, 0, 10, 0);
		gbc_sLine.fill = GridBagConstraints.HORIZONTAL;
		gbc_sLine.gridx = 0;
		gbc_sLine.gridy = 2;
		gbc_sLine.weightx = 1.0;
		gbc_sLine.gridwidth = 3;
		pane.add(sLine, gbc_sLine);
        sLine.setOrientation(SwingConstants.HORIZONTAL);

        
		chckbxOptFinalize = new JCheckBox("Finalize Disc");
		GridBagConstraints gbc_chckbxOptFinalize = new GridBagConstraints();
		gbc_chckbxOptFinalize.fill = GridBagConstraints.HORIZONTAL;
		gbc_chckbxOptFinalize.gridx = 0;
		gbc_chckbxOptFinalize.gridy = 3;
		gbc_chckbxOptFinalize.weightx = 1.0;
		pane.add(chckbxOptFinalize, gbc_chckbxOptFinalize);
		
		chckbxOptEject = new JCheckBox("Eject After Burn");
		GridBagConstraints gbc_chckbxOptEject = new GridBagConstraints();
		gbc_chckbxOptEject.fill = GridBagConstraints.HORIZONTAL;
		gbc_chckbxOptEject.gridx = 1;
		gbc_chckbxOptEject.gridy = 3;
		gbc_chckbxOptEject.weightx = 1.0;
		pane.add(chckbxOptEject, gbc_chckbxOptEject);
		
		chckbxOptBurnProof = new JCheckBox("Burn Proof");
		GridBagConstraints gbc_chckbxOptBurnProof = new GridBagConstraints();
		gbc_chckbxOptBurnProof.fill = GridBagConstraints.HORIZONTAL;
		gbc_chckbxOptBurnProof.gridx = 2;
		gbc_chckbxOptBurnProof.gridy = 3;
		gbc_chckbxOptBurnProof.weightx = 1.0;
		pane.add(chckbxOptBurnProof, gbc_chckbxOptBurnProof);
		
		chckbxOptOPC = new JCheckBox("OPC");
		GridBagConstraints gbc_chckbxOptOPC = new GridBagConstraints();
		gbc_chckbxOptOPC.fill = GridBagConstraints.HORIZONTAL;
		gbc_chckbxOptOPC.gridx = 0;
		gbc_chckbxOptOPC.gridy = 4;
		gbc_chckbxOptOPC.weightx = 1.0;
		pane.add(chckbxOptOPC, gbc_chckbxOptOPC);
		
		chckbxOptAutoErase = new JCheckBox("Auto Erase");
		GridBagConstraints gbc_chckbxOptAutoErase = new GridBagConstraints();
		gbc_chckbxOptAutoErase.fill = GridBagConstraints.HORIZONTAL;
		gbc_chckbxOptAutoErase.gridx = 1;
		gbc_chckbxOptAutoErase.gridy = 4;
		gbc_chckbxOptAutoErase.weightx = 1.0;
		pane.add(chckbxOptAutoErase, gbc_chckbxOptAutoErase);
		
		chckbxOptJoliet = new JCheckBox("Joliet");
		GridBagConstraints gbc_chckbxOptJoliet = new GridBagConstraints();
		gbc_chckbxOptJoliet.fill = GridBagConstraints.HORIZONTAL;
		gbc_chckbxOptJoliet.gridx = 2;
		gbc_chckbxOptJoliet.gridy = 4;
		gbc_chckbxOptJoliet.weightx = 1.0;
		pane.add(chckbxOptJoliet, gbc_chckbxOptJoliet);
		
		chckbxOptVerify = new JCheckBox("Verify");
		GridBagConstraints gbc_chckbxOptVerify = new GridBagConstraints();
		gbc_chckbxOptVerify.fill = GridBagConstraints.HORIZONTAL;
		gbc_chckbxOptVerify.gridx = 0;
		gbc_chckbxOptVerify.gridy = 5;
		gbc_chckbxOptVerify.weightx = 1.0;
		pane.add(chckbxOptVerify, gbc_chckbxOptVerify);
		
		JSeparator sLine2 = new JSeparator(); 
		GridBagConstraints gbc_sLine2 = new GridBagConstraints();
		gbc_sLine2.insets = new Insets(10, 0, 10, 0);
		gbc_sLine2.fill = GridBagConstraints.HORIZONTAL;
		gbc_sLine2.gridx = 0;
		gbc_sLine2.gridy = 6;
		gbc_sLine2.weightx = 1.0;
		gbc_sLine2.gridwidth = 3;
		pane.add(sLine2, gbc_sLine2);
        sLine2.setOrientation(SwingConstants.HORIZONTAL);
        
        JPanel test = new JPanel();
        test.setBackground(Color.WHITE);
        test.setSize(new Dimension(430, 180));
        test.setPreferredSize(new Dimension(430, 180));
        
        
        logModel = new DefaultListModel();
        logModel.ensureCapacity(300);

        logList = new JList(logModel);
        logList.setPreferredSize(new Dimension(400, 4000));
		logList.setVisibleRowCount(7);
		logList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		
        JScrollPane sp = new JScrollPane(logList);
        sp.setHorizontalScrollBar(null);
        sp.setPreferredSize(new Dimension(logList.getPreferredSize().width, 180));

    
        GridBagConstraints gbc_logList = new GridBagConstraints();
        gbc_logList.anchor = GridBagConstraints.WEST;
        gbc_logList.gridx = 0;
        gbc_logList.gridy = 7;
        gbc_logList.weightx = 1.0;
        gbc_logList.weighty = 1.0;
        gbc_logList.gridwidth = 3;
		pane.add(sp, gbc_logList);
		
        
		
		progressBar = new JProgressBar();
		GridBagConstraints gbc_progressBar = new GridBagConstraints();
		gbc_progressBar.fill = GridBagConstraints.HORIZONTAL;
		gbc_progressBar.gridx = 0;
		gbc_progressBar.gridy = 8;
		gbc_progressBar.weightx = 1.0;
		gbc_progressBar.weighty = 0.5;
		gbc_progressBar.gridwidth = 3;
		progressBar.setMinimum(0);
		progressBar.setMaximum(100);
		pane.add(progressBar, gbc_progressBar);
		
		btnBurn = new JButton("Burn");
		btnBurn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				burnToDisk();
			}
		});
		GridBagConstraints gbc_btnBurn = new GridBagConstraints();
		gbc_btnBurn.gridx = 2;
		gbc_btnBurn.gridy = 9;
		gbc_btnBurn.weightx = 1.0;
		gbc_btnBurn.weighty = 0.5;
		pane.add(btnBurn, gbc_btnBurn);
    }
	
	private static JList logList;
	private static DefaultListModel logModel;
	private static JButton btnBurn;
	private static JProgressBar progressBar;
	private static javax.swing.JComboBox driveCB;
	private static JTextField diskLabelField;
	private static JLabel lblDriveLabel;
	private static JLabel lblDiskNameLabel;
	private static JCheckBox chckbxOptJoliet;
	private static JCheckBox chckbxOptAutoErase;
	private static JCheckBox chckbxOptOPC;
	private static JCheckBox chckbxOptBurnProof;
	private static JCheckBox chckbxOptFinalize;
	private static JCheckBox chckbxOptEject;
	private static JCheckBox chckbxOptVerify;
	
}
