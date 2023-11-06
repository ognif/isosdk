using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Reflection;
using System.Drawing;
using System.Text;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpImageEditSample
{

    public partial class ImageEditForm : Form
    {
        private Burner m_burner;

        private bool m_bBurningDevicesOnly = false;

        private MediumNode m_medium = null;

        private const int audiofiles_ext_size = 8;
        private String[] audiofiles_ext = {".wav", ".mp3", ".ogg", ".wma", ".vqf", ".aac", ".m4a", ".flac"};

        private const int SECTOR_SIZE = 2352;
        private const int BYTES_TO_PLAY = SECTOR_SIZE * 64;

        public ImageEditForm()
        {
            InitializeComponent();

            m_burner = new Burner();
            m_burner.Initialize("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7", ASPIInterface.Internal, true);
            m_burner.Language = "Default";

            Assembly assem = typeof(ImageEditForm).Assembly;
            AssemblyName assemName = assem.GetName();
            Text = "IsoSDK " + assemName.Version.Major + "." + assemName.Version.Minor + " CSharpImageEditSample";

            listViewRightPanel.Columns[0].Width = 150;
            listViewRightPanel.Columns[1].Width = 50;
            listViewRightPanel.Columns[2].Width = 50;
            listViewRightPanel.Columns[3].Width = 120;

            // Update devices list
            UpdateDeviceCombo();
        }

        private void UpdateDeviceCombo()
        {
            string strOldDevice = comboBoxDevices.SelectedItem as string;
            comboBoxDevices.Items.Clear();

	        // Get devices list

            string[] devices = m_burner.GetDevices(m_bBurningDevicesOnly);
            //CommonNet.Functions.HandleError(m_burner);

            string strCurrentDevice = m_burner.ReadDevice;
            
            for (int i = 0; i < devices.Length; ++i)
            {
                comboBoxDevices.Items.Add(devices[i]);
                if (String.Compare(strCurrentDevice, 0, devices[i], 0, 2) == 0)
                {
                    comboBoxDevices.SelectedIndex = i;
                }
            }

            // Check if any device is selected
            if (comboBoxDevices.SelectedIndex == -1)
            {
                // No device is selected, so select first
                comboBoxDevices.SelectedIndex = 0;
            }
            else
            {
                // Check if device is changed
                string strCurDevice = comboBoxDevices.SelectedItem as string;

                // If device is changed reload all information
                if (strCurDevice != strOldDevice)
                    ReloadLeftPanel();
            }
        }

        private void ReloadLeftPanel()
        {
            // clear left and right panels
	        treeViewLeftPanel.Nodes.Clear();
	        listViewRightPanel.Items.Clear();
	        
            MediumInfo cMediumInfo = m_burner.GetMediumInfo((int)DeviceIndex.Read);
            
	        if (CommonNet.Functions.HandleError(m_burner))
	        {
		        /*if (res == BS_SCSI_ERROR_DISK_31)
			        m_leftPanel->appendItem(NULL, "No medium");
		        else
			        handleError(res);*/
		        return;
	        }

	        m_medium = MediumNode.create(m_burner, cMediumInfo);

	        buildNode(null, m_medium);
        }

        private void ReloadRightPanel()
        {
	        // get currently selected item on left panel
	        TreeNode selected = treeViewLeftPanel.SelectedNode;

            if (selected == null)
            {
                return;
            }
            TreeNode parent = selected.Parent;

	        ITreeNode node = (ITreeNode)selected.Tag;
            ITreeNode parentNode = parent != null ? (ITreeNode)parent.Tag : null;

	        if (node == null)
            {
		        return;
            }

	        // clear right panel
	        listViewRightPanel.Items.Clear();

            // if there is parent node, add .. item for it
            if (parentNode != null)
            {
                ListViewItem item = listViewRightPanel.Items.Add("..");
                item.Tag = parentNode;
            }

            int lastDir = listViewRightPanel.Items.Count;

	        for(int i = 0; i < (int)node.getChildsCount(); ++i)
	        {
		        // get child node
		        ITreeNode child = node.getChild(i);

                // get info for child node
                GenericInfo info = child.getGenericInfo();

                String[] subItems = {info.name, info.lba.ToString(), 
                    info.size.ToString(), info.date};

                ListViewItem item = new ListViewItem(subItems, (int)info.icon * 2);
                item.Tag = child;

                if (child is FileNode)
                {
                    listViewRightPanel.Items.Add(item);
                }
                else
                {
                    listViewRightPanel.Items.Insert(lastDir, item);
                    lastDir = item.Index + 1;
                }
	        }
        }

        void buildNode(TreeNode parent, ITreeNode node)
        {
	        // skip files
            if ((node is FileNode))
            {
                return;
            }

	        GenericInfo nodeInfo = node.getGenericInfo();

            TreeNode treeNode = new TreeNode(nodeInfo.name, 
                (int)nodeInfo.icon * 2, (int)nodeInfo.icon * 2 + 1);

            if (parent == null)
            {
                treeViewLeftPanel.Nodes.Add(treeNode);
            }
            else
            {
                parent.Nodes.Add(treeNode);
            }

            treeNode.Tag = node;

	        int childsCount = node.getChildsCount();

            for (int i = 0; i < childsCount; ++i)
	        {
		        buildNode(treeNode, node.getChild(i));
	        }

	        // do not expand directories
            if (!(node is DirectoryNode))
            {
                treeNode.Expand();
            }
        }
              
        private void comboBoxDevices_SelectedIndexChanged(object sender, EventArgs e)
        {
            int indx = comboBoxDevices.SelectedIndex;

	        if (-1 < indx)
	        {
		        String strItem = comboBoxDevices.Items[indx].ToString();
		        
                m_burner.ReadDevice = strItem;
                CommonNet.Functions.HandleError(m_burner);
	        }

            ReloadLeftPanel();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Additional.About();
        }

        private void webToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Functions.GoToPixbytesSite();
        }

        private void internalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.Internal);
        }

        private void wnApsiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.WnAspi);
        }

        private void frogAspiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.FrogAspi);
        }

        private void updateInterfaceMenu(ASPIInterface aspiInterface)
        {
            m_burner.SetASPI(aspiInterface);

            ASPIInterface actualAspi = m_burner.GetASPI();
            m_burner.RescanDevices();
            UpdateDeviceCombo();

            internalToolStripMenuItem.Checked = actualAspi == ASPIInterface.Internal;
            wnApsiToolStripMenuItem.Checked = actualAspi == ASPIInterface.WnAspi;
            frogAspiToolStripMenuItem.Checked = actualAspi == ASPIInterface.FrogAspi;
        }

        private void rescanDevicesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.RescanDevices();
            UpdateDeviceCombo();
        }

        private void burnDevicesOnlyToolStripMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            m_bBurningDevicesOnly = !m_bBurningDevicesOnly;
            UpdateDeviceCombo();
        }

        private void disableImagewriterToolStripMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            m_burner.ImageDeviceEnabled = !disableImagewriterToolStripMenuItem.Checked;
            m_burner.RescanDevices();
            UpdateDeviceCombo();
        }

        private void treeViewLeftPanel_AfterSelect(object sender, TreeViewEventArgs e)
        {
            ReloadRightPanel();
        }

        private void treeViewLeftPanel_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                TreeNode node = treeViewLeftPanel.GetNodeAt(e.X, e.Y);

                if (node != null)
	            {
		            treeViewLeftPanel.SelectedNode = node;

                    if (node.Tag != null)
		            {
			            List<ITreeNode> nodes = new List<ITreeNode> ();
                        nodes.Add((ITreeNode)node.Tag);
			            
                        // show menu for current nodes
                        ShowPopupForNodes(nodes, MousePosition.X, MousePosition.Y);
		            }
	            }	            
            }
        }

        private void OnCheckSignature(object sender, EventArgs e)
        {
            DiscSignature Res = (DiscSignature)m_burner.CheckSignature();
            String sourceType = "";
            switch (Res)
            {
                case DiscSignature.Encrypted:
                    sourceType = "Disc or Image is encrypted!";
                    break;
                case DiscSignature.Compressed:
                    sourceType = "Disc or Image is compressed!";
                    break;
                case DiscSignature.EncryptedCompressed:
                    sourceType = "Disc or Image is compressed and encrypted!";
                    break;
                default:
                    sourceType = "Disc or Image is not compressed and encrypted!";
                    break;
            }

            MessageBox.Show(sourceType, "Is disc/image encrypted or compressed?");

        }

        private void OnExtractFileEx(object sender, EventArgs e)
        {
            List<ITreeNode> nodes = (List<ITreeNode>)((ToolStripItem)sender).GetCurrentParent().Tag;

            FolderBrowserDialog FolderDlg = new FolderBrowserDialog();
            FolderDlg.ShowNewFolderButton = true;
            FolderDlg.Description = "Choose folder for extraction";

            if (FolderDlg.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            String strFolderName = FolderDlg.SelectedPath;

            if (strFolderName == "")
            {
                MessageBox.Show("Extract Folders/Files",
                    "Extraction path cannot be empty.");

                return;
            }

            String strPassword = "";
            DiscSignature Res = (DiscSignature)m_burner.CheckSignature();
            if (Res == DiscSignature.Encrypted || Res == DiscSignature.EncryptedCompressed)
            {
                PasswordBox inputDlg = new PasswordBox();
                strPassword = inputDlg.Show("Enter password", "IsoSDK");
                if (strPassword == "")
                {
                    MessageBox.Show("Extract Folders/Files",
                        "Password is required for encrypted files.");
                    return;
                }
            }

            KSaveContentDialog.SaveContentParams parmas =
                new KSaveContentDialog.SaveContentParams(KSaveContentDialog.EAim.AIM_IMPORT, nodes, strFolderName, strPassword, KSaveContentDialog.Extract.IMP_EX);

            KSaveContentDialog dlg = new KSaveContentDialog(m_burner, parmas);
            dlg.ShowDialog();
        }

        private void OnExtractFiles(object sender, EventArgs e)
        {
            List<ITreeNode> nodes = (List<ITreeNode>)((ToolStripItem)sender).GetCurrentParent().Tag;

            FolderBrowserDialog FolderDlg = new FolderBrowserDialog();
            FolderDlg.ShowNewFolderButton = true;
            FolderDlg.Description = "Choose folder for extraction";

            if (FolderDlg.ShowDialog() != DialogResult.OK)
	        {
		        return;
	        }

            String strFolderName = FolderDlg.SelectedPath;

	        if (strFolderName == "")
	        {
		        MessageBox.Show("Extract Folders/Files", 
			        "Extraction path cannot be empty.");

		        return;
	        }

            KSaveContentDialog.SaveContentParams parmas = 
                new KSaveContentDialog.SaveContentParams(KSaveContentDialog.EAim.AIM_IMPORT, nodes, strFolderName,"", KSaveContentDialog.Extract.IMP_COMMON);

            KSaveContentDialog dlg = new KSaveContentDialog(m_burner, parmas);
	        dlg.ShowDialog();
        }

        private void OnExtractTrack(object sender, EventArgs e)
        {
            List<ITreeNode> nodes = (List<ITreeNode>)((ToolStripItem)sender).GetCurrentParent().Tag;
            	
            for (int i = 0; i < nodes.Count; ++i)
            {
	            TrackNode pcTrackNode = (nodes[i] as TrackNode);
        		
	            String strPatternList;
                SaveTrackFileFormat FileFormat;
	                    		
	            if (pcTrackNode != null)
	            {
		            TrackInfo cTrackInfo = pcTrackNode.getTrackInfo();
        			
		            switch (cTrackInfo.Format)
		            {
			            case TrackFormat.Audio:
			            {
                            FileFormat = SaveTrackFileFormat.Wave;				            
				            strPatternList = 
					            "WAVE files (*.wav)|*.wav|BIN files (RAW FORMAT) (*.bin)|*.bin";
			            }
			            break;

			            case TrackFormat.DataMode1:
			            {
                            FileFormat = SaveTrackFileFormat.Iso;				            
				            strPatternList = "ISO files (*.iso)|*.iso";
        					
				            //Check Disk
				            MediumInfo cMediumInfo =
                                m_burner.GetMediumInfo((int)DeviceIndex.Read);

				            if (cMediumInfo.ExtendedType != ExtendedMediumType.Dvd)
				            {
                                strPatternList += "|BIN files (RAW FORMAT) (*.bin)|*.bin";
				            }
			            }
			            break;

			            case TrackFormat.DataMode2:
			            {
                            FileFormat = SaveTrackFileFormat.Mpeg;				            
				            strPatternList =
                                "MPEG files (*.mpg)|*.mpg|BIN files (RAW FORMAT) (*.bin)|*.bin";
			            }
			            break;

		                default:
			            {
				            //handleError(BS_SDK_ERROR_NOT_IMPLEMENTED);
				            return;
			            }
		            }

		            SaveFileDialog dlg = new SaveFileDialog();

                    dlg.Title = "Choose file to save track # " + cTrackInfo.TrackNumber.ToString();
                    dlg.Filter = strPatternList;
                    dlg.RestoreDirectory = false;
		            
		            if (dlg.ShowDialog() != DialogResult.OK)
		            {
			            continue;
		            }
        			
		            String strFileName = dlg.FileName;

		            if (dlg.FilterIndex == 1)
		            {
                        FileFormat = SaveTrackFileFormat.Bin;			            
		            }

		            DoExtraction(cTrackInfo.TrackNumber, strFileName, FileFormat);					
	            }// if(pcTrackNode)
	            else
	            {
		            continue;
	            }
            }
        	
            // end
        }

        void DoExtraction(int TrackNumber, String strFilePath, SaveTrackFileFormat FileFormat)
        {
	        KSaveTrackDialog dlgSave = new KSaveTrackDialog(m_burner, 
                TrackNumber, strFilePath, FileFormat);

	        dlgSave.ShowDialog();
        }

        private void OnListContent(object sender, EventArgs e)
        {
            List<ITreeNode> nodes = (List<ITreeNode>)((ToolStripItem)sender).GetCurrentParent().Tag;

            SaveFileDialog dlg = new SaveFileDialog();

            dlg.Title = "Choose file to list content";
            dlg.Filter = "Text files (*.txt )|*.txt";

	        String strFileName = "";

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                strFileName = dlg.FileName;

                File.CreateText(strFileName).Close();

                FileStream stream = File.OpenWrite(strFileName);

                RecursivePrintContent(stream, nodes[0], "\\");
            }
        }

        private void RecursivePrintContent(FileStream stream, ITreeNode pcNode, String strFolderPath)
        {	
	        FileSysNode pcFSysNode = (pcNode as FileSysNode);

	        if (pcFSysNode != null)
	        {
		        int nChildCount = pcFSysNode.getChildsCount();

		        for (int i = 0; i < nChildCount; i++)
		        {
                    RecursivePrintContent(stream, pcFSysNode.getChild(i), strFolderPath);
		        }
	        }
	        else
	        {
		        DirectoryNode pcDirNode = (pcNode as DirectoryNode);

		        if (pcDirNode != null)
		        {
			        GenericInfo info = pcDirNode.getGenericInfo();

			        strFolderPath += info.name;
			        strFolderPath += "\\";

			        String strWrite = strFolderPath;
			        strWrite += "\r\n";

                    byte[] bytes = new UTF8Encoding(true).GetBytes(strWrite);
                    stream.Write(bytes, 0, bytes.Length);
                    
			        int nChildCount = pcDirNode.getChildsCount();

			        for (int i = 0; i < nChildCount; i++)
			        {
                        RecursivePrintContent(stream, 
                            pcDirNode.getChild(i), strFolderPath);
			        }
		        }
		        else
		        {
			        FileNode pcFileNode = (pcNode as FileNode);

			        if (pcFileNode != null)
			        {
				        GenericInfo info = pcFileNode.getGenericInfo();
        				
				        String strWrite = strFolderPath;
				        strWrite += info.name;
				        strWrite += "\r\n";

                        byte[] bytes = new UTF8Encoding(true).GetBytes(strWrite);
                        stream.Write(bytes, 0, bytes.Length);
			        }
		        }
	        }
        }

        private void OnSectorView(object sender, EventArgs e)
        {
            List<ITreeNode> nodes =
                (List<ITreeNode>)((ToolStripItem)sender).GetCurrentParent().Tag;
	
	        KSectorViewDialog dlg = new KSectorViewDialog(m_burner, nodes[0].getGenericInfo().lba);
	        dlg.ShowDialog();
        }

        private void OnScanSectors(object sender, EventArgs e)
        {
            List<ITreeNode> nodes =
                (List<ITreeNode>)((ToolStripItem)sender).GetCurrentParent().Tag;

            GenericInfo cGI = nodes[0].getGenericInfo();
	        
	        KScanSectorsDialog dlg = new KScanSectorsDialog(m_burner, cGI.lba, (int)(cGI.size));
            dlg.ShowDialog();
        }

        private void OnShowProperties(object sender, EventArgs e)
        {
            List<ITreeNode> nodes = 
                (List<ITreeNode>)((ToolStripItem)sender).GetCurrentParent().Tag;

	        KPropertiesDialog dlg = new KPropertiesDialog(nodes[0]);
	        dlg.ShowDialog();
        }

        private void ShowPopupForNodes(List<ITreeNode> nodes, int x, int y)
        {
            if (nodes == null || nodes.Count == 0)
            {
                return;
            }

            ContextMenuStrip popupMenu = new ContextMenuStrip();
            
            // set nodes as user data to menu to get it in command handler
            popupMenu.Tag = nodes;
	        

	        // create menu commands
	        if (nodes[0] is FileSysNode)
	        {
                popupMenu.Items.Add("Extract File System", null, OnExtractFiles);		        
	        }

            if (nodes[0] is TrackNode)
	        {
                popupMenu.Items.Add("Extract Track(s)", null, OnExtractTrack);
	        }

            if (nodes[0] is FileNode || nodes[0] is DirectoryNode)
	        {
                popupMenu.Items.Add("Extract Content", null, OnExtractFiles);
	        }

            if (nodes[0] is FileNode)
            {
                popupMenu.Items.Add("Extract Dcrypted / Compressed", null, OnExtractFileEx);
            }

            if (nodes[0] is FileNode)
            {
                popupMenu.Items.Add("Check if source is compressed and/or encrypted", null, OnCheckSignature);
            }

            if (nodes[0] is DirectoryNode || nodes[0] is FileSysNode)
	        {
                popupMenu.Items.Add("List Content", null, OnListContent);
	        }

	        if (nodes.Count == 1)
	        {
                popupMenu.Items.Add("Sector View", null, OnSectorView);

                popupMenu.Items.Add("Scan Sectors", null, OnScanSectors);
                
		        // property command is available for all nodes
                popupMenu.Items.Add("Properties", null, OnShowProperties);


                if (nodes[0] is TrackNode && (nodes[0] as TrackNode).getGenericInfo().icon ==
                    GenericInfo.Icon.ICON_TRACK_AUDIO)
		        {
                    popupMenu.Items.Add("Play", null, OnPlay);
                    popupMenu.Items.Add("Grab audio track", null, OnGrab);
                    popupMenu.Items.Add("Read CD-Text", null, OnReadCDText);
                    popupMenu.Items.Add("Read Indexes", null, OnReadIndexes);
                    popupMenu.Items.Add("Read ISRC", null, OnReadISRC);                    
		        }
	        }

	        // if menu is not empty - show it
            if (popupMenu.Items != null)
	        {
		        // create menu and show
                popupMenu.Show(x, y);		        
	        }
        }

        private void listViewRightPanel_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                ListViewItem item = listViewRightPanel.GetItemAt(e.X, e.Y);
                if (item != null)
	            {
                    listViewRightPanel.SelectedIndices.Add(item.Index);
	            }

	            List<ITreeNode> nodes = new List<ITreeNode> ();

	            for(int i = 0; i < listViewRightPanel.SelectedItems.Count; ++i)
	            {
                    nodes.Add((ITreeNode)listViewRightPanel.SelectedItems[i].Tag);
	            }

	            // show menu for current nodes
                if (nodes.Count > 0)
                {
                    ShowPopupForNodes(nodes, MousePosition.X, MousePosition.Y);
                }
            }
        }

        private void mountToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (disableImagewriterToolStripMenuItem.Checked)
            {
                disableImagewriterToolStripMenuItem.Checked = false;
            }

            OpenFileDialog ofn = new OpenFileDialog();
            ofn.CheckFileExists = true;
            ofn.CheckPathExists = true;
            ofn.Title = "Select image to mount, please...";
            ofn.Multiselect = false;
            string strFilter = "All supported |*.iso;*.bin;*.nrg;*.cdi;*.mdf;*.img;*.gi;*.pdi;*.dmg;*.b5i;*.b6i|ISO files|*.iso|BIN files|*.bin|NRG files|*.nrg|CDI files|*.cdi|MDF files|*.mdf|IMG files|*.img|GI files|*.gi|PDI files|*.pdi|DMG files|*.dmg|B5I files|*.b5i|B6I files|*.b6i)";
            ofn.Filter = strFilter;


            if (ofn.ShowDialog() == DialogResult.OK)
            {
                string strFileName = ofn.FileName;
                m_burner.SetImageFilePath(strFileName);
                CommonNet.Functions.HandleError(m_burner);
            }

            if (comboBoxDevices.SelectedIndex == 0)
            {
                comboBoxDevices_SelectedIndexChanged(sender, e);
            }
            else
            {
                comboBoxDevices.SelectedIndex = 0;
            }
        }

        private void unmountToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.SetImageFilePath("");
            CommonNet.Functions.HandleError(m_burner);
        }

        private void listViewRightPanel_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            ListViewItem item = listViewRightPanel.GetItemAt(e.X, e.Y);

            if (item == null)
                return;

            ITreeNode node = item.Tag as ITreeNode;

            TreeNode leftNode = treeViewLeftPanel.SelectedNode;

            if (leftNode == null)
                return;

            // check for ".."
            {
                TreeNode parent = leftNode.Parent;
                if (parent != null)
                {
                    ITreeNode parentNode = parent.Tag as ITreeNode;

                    if (parentNode != null && parentNode == node)
                    {
                        treeViewLeftPanel.SelectedNode = parent;
                        return;
                    }
                }
            }

            leftNode.Expand();

            for (int i = 0; i < leftNode.Nodes.Count; ++i)
            {
                ITreeNode subNode = leftNode.Nodes[i].Tag as ITreeNode;

                if (subNode == node)
                {
                    treeViewLeftPanel.SelectedNode = leftNode.Nodes[i];
                    return;
                }
            }            
        }

        private void makeMd5ToolStripMenuItem_Click(object sender, EventArgs e)
        {   
            OpenFileDialog OpenDlg = new OpenFileDialog();
            OpenDlg.Title = "Choose file please...";
            OpenDlg.Filter = "ISO files (*.iso)|*.iso|BIN files (RAW FORMAT) (*.bin)|*.bin";
            OpenDlg.Multiselect = false;

	        if (OpenDlg.ShowDialog() != DialogResult.OK)
	        {
		        return;
	        }
        	
	        String strFileName = OpenDlg.FileName;

	        KMD5Dialog md5Dlg = new KMD5Dialog(strFileName);
	        
            DialogResult Res = md5Dlg.ShowDialog();

	        String strMD5 = md5Dlg.GetMD5String();

	        if (strMD5.Length == 0)
	        {
		        return;
	        }

	        String strMD5FileName = strFileName.Substring(0, strFileName.LastIndexOf('.')) + ".md5";
        	
            File.WriteAllText(strMD5FileName, strMD5);

            MessageBox.Show("MD5 hash \" " + strMD5 + "\" was written in this file:\n" + strMD5FileName + ".", "Done");
        }

        private void checkMd5ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog OpenDlg = new OpenFileDialog();
            OpenDlg.Title = "Choose file please...";
            OpenDlg.Filter = "ISO files (*.iso)|*.iso|BIN files (RAW FORMAT) (*.bin)|*.bin";
            OpenDlg.Multiselect = false;

            if (OpenDlg.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            String strFileName = OpenDlg.FileName;

            KMD5Dialog md5Dlg = new KMD5Dialog(strFileName);

            DialogResult Res = md5Dlg.ShowDialog();

            String strMD5 = md5Dlg.GetMD5String();

            String strMD5FileName = strFileName.Substring(0, strFileName.LastIndexOf('.')) + ".md5";

            String strMD5FromFile = File.ReadAllText(strMD5FileName);

            if (strMD5 == strMD5FromFile)
	        {
		        MessageBox.Show("MD5 hash \" " + strMD5 + "\" is equal to those in .md5 file.", "MD5 is Ok.");
	        }
	        else
	        {
		        MessageBox.Show("MD5 hash \" " + strMD5 + "\" differs from those in .md5 file: \" " + strMD5FromFile + "\".", "MD5 hash DIFFERS!");
	        }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ImageFormat Format = ImageFormat.Bin;

	        String strPatternList = "BIN files (*.bin)|*.bin";
        	
	        ImageFormat ImageFormats = m_burner.GetPossibleImageFormats();

            if (CommonNet.Functions.HandleError(m_burner) || ImageFormats == 0)
	        {
		        MessageBox.Show("Disc is incorrect or no disc is inserted.", "Saving image");		        
		        return;
	        }
        	
	        if ((ImageFormats & ImageFormat.Iso) == ImageFormat.Iso)
	        {	
		        strPatternList += "|ISO files (*.iso)|*.iso";
	        }

            SaveFileDialog fileDialog = new SaveFileDialog();
            fileDialog.Title =  "Choose file to save disk image";
            fileDialog.Filter = strPatternList;
        	
	        if (fileDialog.ShowDialog() != DialogResult.OK)
	        {
		        return;
	        }
        	
	        String strFileName = fileDialog.FileName;

	        if (fileDialog.FilterIndex == 2)
	        {		        
		        Format = ImageFormat.Iso;
	        }

            KSaveDiscDialog dlg = new KSaveDiscDialog(m_burner, strFileName, Format);
            dlg.ShowDialog();
        }

        private void verifyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            List<ITreeNode> nodes = new List<ITreeNode>();

	        TreeNode rootItem = treeViewLeftPanel.Nodes[0];
        	
	        TreeNode sessionItem = rootItem.FirstNode;

	        while (sessionItem != null)
	        {
		        TreeNode trackItem = sessionItem.FirstNode;
                

		        while (trackItem != null)
		        {
			        TreeNode fsysItem = trackItem.FirstNode;

			        while (fsysItem != null)
			        {
				        nodes.Add((ITreeNode)fsysItem.Tag);

				        fsysItem = fsysItem.NextNode;
			        }

			        trackItem = trackItem.NextNode;
		        }

		        sessionItem = sessionItem.NextNode;
	        }

            KSaveContentDialog.SaveContentParams parmas =
                new KSaveContentDialog.SaveContentParams(KSaveContentDialog.EAim.AIM_VERIFY, nodes, "", "", KSaveContentDialog.Extract.IMP_COMMON);

            KSaveContentDialog dlgSave = new KSaveContentDialog(m_burner, parmas);
            dlgSave.ShowDialog();
        }

        private void OnReadISRC(object sender, EventArgs e)
        {
            TreeNode item = treeViewLeftPanel.SelectedNode;

            if (item == null)
            {
                return;
            }

            ITreeNode node = (ITreeNode)item.Tag;
            if (node == null)
            {
                return;
            }

            TrackNode pcTrackNode = node as TrackNode;

            if (pcTrackNode == null)
            {
                return;
            }

            int nTrackNumber = pcTrackNode.getTrackInfo().TrackNumber;

            
            string strISRC = m_burner.GetTrackISRC((int)IsoSDK.DeviceIndex.Read, nTrackNumber);

            if (CommonNet.Functions.HandleError(m_burner))
            {
                return;
            }

            if (strISRC == null)
            {
                return;
            }

            MessageBox.Show(strISRC, "Track ISRC");

        }
        private void OnReadIndexes(object sender, EventArgs e)
        {
            TreeNode item = treeViewLeftPanel.SelectedNode;

            if (item == null)
            {
                return;
            }

            ITreeNode node = (ITreeNode)item.Tag;
            if (node == null)
            {
                return;
            }

            TrackNode pcTrackNode = node as TrackNode;

            if (pcTrackNode == null)
            {
                return;
            }

            int nTrackNumber = pcTrackNode.getTrackInfo().TrackNumber;
            int [] Indexes = m_burner.GetTrackIndexes((int)IsoSDK.DeviceIndex.Read, nTrackNumber);

            if (CommonNet.Functions.HandleError(m_burner))
            {
                return;
            }

            if (Indexes == null)
            {
                return;
            }

            if (Indexes.Length == 0)
            {
                return;
            }

            string s = "";

            for(int i = 0; i<Indexes.Length; ++i)
            {
                s += "Index " + i.ToString() + " : " + Indexes[i].ToString() + "\n";
            }

            s += "\n";

            if (Indexes.Length > 1)
            {
                s += "Pause length: " + (Indexes[1] - Indexes[0]).ToString();
            }

            MessageBox.Show(s, "Track indexes");
        }

        private void OnReadCDText(object sender, EventArgs e)
        {
            TreeNode item = treeViewLeftPanel.SelectedNode;

            if (item == null)
            {
                return;
            }

            ITreeNode node = (ITreeNode)item.Tag;
            if (node == null)
            {
                return;
            }

            TrackNode pcTrackNode = node as TrackNode;

            if (pcTrackNode == null)
            {
                return;
            }

            int nTrackNumber = pcTrackNode.getTrackInfo().TrackNumber;

            CDText cdText = m_burner.ReadCDText((int)IsoSDK.DeviceIndex.Read);
            if (cdText == null)
            {
                return;
            }

            String message = "Performer: ";
            message += cdText.GetTrackTagString(nTrackNumber, CDTextContentItem.Performer) + "\n";

            message += "Title: ";
            message += cdText.GetTrackTagString(nTrackNumber, CDTextContentItem.Title) + "\n";

            message += "Song Writer: ";
            message += cdText.GetTrackTagString(nTrackNumber, CDTextContentItem.SongWriter) + "\n";
            
            message += "Composer: ";
            message += cdText.GetTrackTagString(nTrackNumber, CDTextContentItem.Composer) + "\n";
            
            message += "Arranger: ";
            message += cdText.GetTrackTagString(nTrackNumber, CDTextContentItem.Arrager) + "\n";
            
            message += "Message: ";
            message += cdText.GetTrackTagString(nTrackNumber, CDTextContentItem.Message) + "\n";

            MessageBox.Show(message, "CD-Text", MessageBoxButtons.OK);
        }

        private void OnPlay(object sender, EventArgs e)
        {
            TreeNode item = treeViewLeftPanel.SelectedNode;

	        if (item != null)
	        {
		        ITreeNode node = (ITreeNode)item.Tag;
		        
                if (node == null)
                {
			        return;
                }

                TrackNode pcTrackNode = node as TrackNode;

                TrackInfo cTrackInfo = null;

                if (pcTrackNode != null)
                {
                    cTrackInfo = pcTrackNode.getTrackInfo();
                }
                else
                {
                    if (listViewRightPanel.SelectedItems.Count == 1)
                    {
                        ListViewItem listItem = listViewRightPanel.SelectedItems[0];

                        item = treeViewLeftPanel.SelectedNode.Nodes[listItem.Index];

                        if (item != null)
                        {
                            node = (ITreeNode)item.Tag;

                            if (node == null)
                            {
                                return;
                            }

                            pcTrackNode = node as TrackNode;

                            if (pcTrackNode != null)
                            {
                                cTrackInfo = pcTrackNode.getTrackInfo();
                            }
                        }
                    }
                }

                if (cTrackInfo == null)
                {
                    return;
                }

                KTrackPlayDialog dlgPlay = new KTrackPlayDialog(m_burner, cTrackInfo.TrackNumber);
                dlgPlay.ShowDialog();
            }
        }


        private void ImageEditForm_FormClosing(object sender, FormClosingEventArgs e)
        {   
        }

        private void OnGrab(object sender, EventArgs e)
        {
            TreeNode item = treeViewLeftPanel.SelectedNode;

            if (item != null)
            {
                ITreeNode node = (ITreeNode)item.Tag;

                if (node == null)
                {
                    return;
                }

                TrackNode pcTrackNode = node as TrackNode;

                TrackInfo cTrackInfo = null;

                if (pcTrackNode != null)
                {
                    cTrackInfo = pcTrackNode.getTrackInfo();
                }
                else
                {
                    if (listViewRightPanel.SelectedItems.Count == 1)
                    {
                        ListViewItem listItem = listViewRightPanel.SelectedItems[0];

                        item = treeViewLeftPanel.SelectedNode.Nodes[listItem.Index];

                        if (item != null)
                        {
                            node = (ITreeNode)item.Tag;

                            if (node == null)
                            {
                                return;
                            }

                            pcTrackNode = node as TrackNode;

                            if (pcTrackNode != null)
                            {
                                cTrackInfo = pcTrackNode.getTrackInfo();
                            }
                        }
                    }
                }

                if (cTrackInfo == null)
                {
                    return;
                }

                List<uint> vTracks = new List<uint>();
			    vTracks.Add((uint)cTrackInfo.TrackNumber);

                KAudioGrabbingDialog dlg = new KAudioGrabbingDialog(m_burner, vTracks);
                dlg.ShowDialog();
            }
        }

        private void grabAllTracksToolStripMenuItem_Click(object sender, EventArgs e)
        {
            List<uint> vTracks = new List<uint> ();
            ITreeNode node;
            TrackNode pcTrackNode;
            TrackInfo cTrackInfo = null;

            TreeNode rootItem = treeViewLeftPanel.Nodes[0];

            TreeNode sessionItem = rootItem.FirstNode;

            while (sessionItem != null)
            {
                TreeNode trackItem = sessionItem.FirstNode;

                while (trackItem != null)
                {
                    
                    node = (ITreeNode)trackItem.Tag;

                    if (node == null)
                    {
                        continue;
                    }
                    
                    pcTrackNode = node as TrackNode;

                    if (pcTrackNode != null)
                    {
                        cTrackInfo = pcTrackNode.getTrackInfo();
                    }

                    if (cTrackInfo == null)
                    {
                        continue;
                    }

			        vTracks.Add((uint)cTrackInfo.TrackNumber);

                    trackItem = trackItem.NextNode;
                }

                sessionItem = sessionItem.NextNode;
            }

            if (vTracks.Count > 0)
            {
                KAudioGrabbingDialog dlg = new KAudioGrabbingDialog(m_burner, vTracks);
                dlg.ShowDialog();
            }
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            ReloadLeftPanel();
        }
    }

    public class PasswordBox
    {
        private Form frm;
        public string Show(string prompt, string title)
        {
            frm = new Form();
            FlowLayoutPanel FL = new FlowLayoutPanel();
            Label lbl = new Label();
            TextBox txt = new TextBox();
            Button ok = new Button();
            Button cancel = new Button();

            frm.Font = new Font("Calibri", 9, FontStyle.Bold);
            frm.FormBorderStyle = FormBorderStyle.FixedToolWindow;
            frm.StartPosition = FormStartPosition.CenterScreen;
            frm.Width = 200;
            frm.Height = 150;

            frm.Text = title;
            lbl.Text = prompt;
            ok.Text = "Ok";
            cancel.Text = "Cancel";
            txt.PasswordChar = '*';

            ok.FlatStyle = FlatStyle.Flat;
            ok.BackColor = SystemColors.ButtonShadow;
            ok.ForeColor = SystemColors.ButtonHighlight;
            ok.Cursor = Cursors.Hand;

            cancel.FlatStyle = FlatStyle.Flat;
            cancel.BackColor = SystemColors.ButtonShadow;
            cancel.ForeColor = SystemColors.ButtonHighlight;
            cancel.Cursor = Cursors.Hand;

            FL.Left = 0;
            FL.Top = 0;
            FL.Width = frm.Width;
            FL.Height = frm.Height;
            FL.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right | AnchorStyles.Top;
            FL.Padding = new Padding(10);
            FL.FlowDirection = FlowDirection.TopDown;

            ok.Width = FL.Width - 35;
            txt.Width = ok.Width;
            cancel.Width = ok.Width;
            lbl.Width = ok.Width;

            ok.Click += new System.EventHandler(OkClick);
            cancel.Click += new System.EventHandler(CancelClick);
            txt.KeyPress += new KeyPressEventHandler(TxtEnter);

            FL.Controls.Add(lbl);
            FL.Controls.Add(txt);
            FL.Controls.Add(ok);
            FL.Controls.Add(cancel);
            frm.Controls.Add(FL);

            frm.ShowDialog();
            DialogResult DR = frm.DialogResult;
            frm.Dispose();
            frm = null;
            if (DR == DialogResult.OK)
            {
                return txt.Text;
            }
            else
            {
                return "";
            }
        }
        private void OkClick(object sender, System.EventArgs e)
        {
            frm.DialogResult = DialogResult.OK;
            frm.Close();
        }
        private void CancelClick(object sender, System.EventArgs e)
        {
            frm.DialogResult = DialogResult.Cancel;
            frm.Close();
        }
        private void TxtEnter(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13) { OkClick(null, null); }
        }
    }
}