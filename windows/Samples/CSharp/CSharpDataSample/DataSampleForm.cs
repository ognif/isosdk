using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Reflection;
using System.Windows.Forms;
using System.IO;
using IsoSDK;

namespace CSharpDataSample
{
    public partial class DataSampleForm : Form
    {
        private Burner m_burner;
        private FileListView m_fileListView;
        private ProjectType m_projectType = ProjectType.Data;
        private int m_iSession = 0;
        private bool m_bBurnDevicesOnly = true;

        public DataSampleForm()
        {
            InitializeComponent();
            m_burner = new Burner();
            m_burner.Initialize("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7", ASPIInterface.Internal, true);

            m_fileListView = new FileListView(fileListView, m_burner);

            m_burner.Language = "Default";

            Assembly assem = typeof(DataSampleForm).Assembly;
            AssemblyName assemName = assem.GetName();
            Text = "IsoSDK " + assemName.Version.Major + "." + assemName.Version.Minor + " CSharpDataSample";

            //set default type of project
            m_burner.CreateProject(m_projectType);

            //set options by default
            m_burner.Options.TestBurn = false;
            m_burner.Options.PerformOPC = false;
            m_burner.Options.Joliet = true;
            m_burner.Options.RockRidge = false;
            m_burner.Options.EjectAfterBurn = true;
            m_burner.Options.CacheSize = 2 * 1024 * 1024;
            m_burner.Options.FinalizeDisk = false;
            m_burner.Options.VolumeLabel = "ISOSDK";

            updateInterfaceMenu(ASPIInterface.Internal);

            projectTypeComboBox.Items.Add("ISO 9660");
            projectTypeComboBox.Items.Add("UDF");
            projectTypeComboBox.Items.Add("ISO 9660 / UDF Bridge");
            projectTypeComboBox.Items.Add("Video DVD");
            projectTypeComboBox.Items.Add("BluRay");
            projectTypeComboBox.SelectedIndex = 0;

            updateOptions(false);

            UpdateDeviceCombo();

            EnableControls();
        }

        private void UpdateDeviceCombo()
        {
            deviceComboBox.Items.Clear();
            string[] devices = m_burner.GetDevices(m_bBurnDevicesOnly);
            string[] bDevices = m_burner.GetBurnDevices();

            for (int i = 0; i < devices.Length; ++i)
            {
                deviceComboBox.Items.Add(devices[i]);
                if (bDevices.Length > 0)
                {
                    if (String.Compare(bDevices[0], 0, devices[i], 0, 2) == 0)
                    {
                        deviceComboBox.SelectedIndex = i;
                    }
                }
 
            }
            deviceComboBox.Items.Add("Multiple devices");
            if (bDevices.Length > 1)
            {
                deviceComboBox.SelectedIndex = devices.Length;
            }

        }

        private void addFileButton_Click(object sender, EventArgs e)
        {          
            m_fileListView.AddFile();
            SetSizeValue(m_fileListView.GetDirectorySize("\\"));
        }

        private void createDirButton_Click(object sender, EventArgs e)
        {
            m_fileListView.CreateFolder();
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            m_fileListView.DeleteItem();
            SetSizeValue(m_fileListView.GetDirectorySize("\\"));
        }

        private void resetButton_Click(object sender, EventArgs e)
        {         
            m_burner.ClearAll();
            m_fileListView.ResetList();
            SetSizeValue(m_fileListView.GetDirectorySize("\\"));
        }

        private void renameButton_Click(object sender, EventArgs e)
        {
            m_fileListView.RenameFile();
        }

        private void eraseButton_Click(object sender, EventArgs e)
        {
            CommonNet.Erase.EraseDeveloped(m_burner);
        }

        private void burnButton_Click(object sender, EventArgs e)
        {
            updateOptions(true);

            CommonNet.Burning.BurnDeveloped(m_burner, "");
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void extendedHeaderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            HeaderDlg dlg = new HeaderDlg(m_burner);
            dlg.ShowDialog();
        }

        private void projectTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (projectTypeComboBox.SelectedIndex)
            {
                case 0:
                    m_projectType = ProjectType.Data;
                    break;
                case 1:
                    m_projectType = ProjectType.UdfDvd;
                    break;
                case 2:
                    m_projectType = ProjectType.IsoUdf;
                    break;
                case 3:
                    m_projectType = ProjectType.VideoDvd;
                    break;
                case 4:
                    m_projectType = ProjectType.Bluray;
                    break;
            }

            if (m_projectType == ProjectType.Data || m_projectType == ProjectType.IsoUdf)
            {
                jolietFileSystemToolStripMenuItem.Enabled = true;
                rockRidgeFileSystemToolStripMenuItem.Enabled = true;
            }
            else
            {
                jolietFileSystemToolStripMenuItem.Enabled = false;
                rockRidgeFileSystemToolStripMenuItem.Enabled = false;
            }
            m_burner.CreateProject(m_projectType, m_iSession);
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
            {
                MessageBox.Show("This type of project can't be selected now");
                m_projectType = (ProjectType)m_burner.GetProjectType();
                switch (m_projectType)
                {
                    case ProjectType.Data:
                        projectTypeComboBox.SelectedIndex = 0;
                        break;
                    case ProjectType.UdfDvd:
                        projectTypeComboBox.SelectedIndex = 1;
                        break;
                    case ProjectType.IsoUdf:
                        projectTypeComboBox.SelectedIndex = 2;
                        break;
                    case ProjectType.VideoDvd:
                        projectTypeComboBox.SelectedIndex = 3;
                        break;
                    case ProjectType.Bluray:
                        projectTypeComboBox.SelectedIndex = 4;
                        break;
                }
            }
            m_fileListView.ResetList();
            SetSizeValue(m_fileListView.GetDirectorySize("\\"));
            updateOptions(false);
        }

        private void deviceComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int nIndex = deviceComboBox.SelectedIndex;
            if (nIndex == deviceComboBox.Items.Count - 1 && nIndex != 0)
            {
                if (DialogResult.OK != CommonNet.Additional.Multiselection(m_burner))
                {
                    deviceComboBox.SelectedIndex = 0;
                }                

            }
            else
            {
                string str = deviceComboBox.Text;
                m_burner.BurnDevice = str;
            }
        }

        private void importFromSessionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ImportSessionDlg dlg = new ImportSessionDlg(m_burner);
            if (DialogResult.OK == dlg.ShowDialog())
            {
                if (dlg.Session > 0)
                {
                    m_burner.CreateProject(m_projectType, dlg.Session);
                    if (m_burner.GetLastError() == ErrorCode.SdkErrorNo)
                    {
                        this.m_iSession = dlg.Session;
                    }

                    m_fileListView.RefreshList();
                    SetSizeValue(m_fileListView.GetDirectorySize("\\"));
                }                
            }
        }
		
		private void importLastSessionToolStripMenuItem_Click(object sender, EventArgs e)
        {        
            int nLastSession = m_burner.GetMediumInfo().LastSession;
            m_burner.CreateProject(m_projectType, nLastSession);
            if (m_burner.GetLastError() == ErrorCode.SdkErrorNo)
            {
                this.m_iSession = nLastSession;
            }

            m_fileListView.RefreshList();
            SetSizeValue(m_fileListView.GetDirectorySize("\\"));
        }
		
		private void importNoSessionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.CreateProject(m_projectType, -1);
            if (m_burner.GetLastError() == ErrorCode.SdkErrorNo)
            {
                this.m_iSession = -1;
            }            
            m_fileListView.RefreshList();
            SetSizeValue(m_fileListView.GetDirectorySize("\\"));
        }
		

        private void bootToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BootImageDlg dlg = new BootImageDlg(m_burner);
            dlg.ShowDialog();
        }

        private void addFolderButton_Click(object sender, EventArgs e)
        {
            m_fileListView.AddFolder();
            SetSizeValue(m_fileListView.GetDirectorySize("\\"));
        }

        private void fileListView_DoubleClick(object sender, EventArgs e)
        {
            m_fileListView.OnDoubleClicked();
        }
        private void SetSizeValue(Int64 size)
        {
            int value = Convert.ToInt32(size / 1024 / 1024);
            if (value < sizeProgressBar.Maximum)
            {
                sizeProgressBar.Value = value;
            }
            else
            {
                sizeProgressBar.Value = sizeProgressBar.Maximum;
            }
        }

        private void rescanButton_Click(object sender, EventArgs e)
        {
            m_burner.RescanDevices();
            UpdateDeviceCombo();
        }

        private void disableImagewriterToolStripMenuItem_CheckStateChanged(object sender, EventArgs e)
        {
            m_burner.EnableImageDevice(!disableImagewriterToolStripMenuItem.Checked);
            UpdateDeviceCombo();
        }

        private void burnDevicesOnlyToolStripMenuItem_CheckStateChanged(object sender, EventArgs e)
        {
            m_bBurnDevicesOnly = !m_bBurnDevicesOnly;
            UpdateDeviceCombo();
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

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Additional.About();
        }

        private void mountIMageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Image files (*.iso)|*.iso";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                m_burner.SetImageFilePath(dlg.FileName);
            }
        }

        private void unmountImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.SetImageFilePath("");
        }

        private void burnDiskImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Image files (*.iso)|*.iso|Cue Sheets (*.cue)|*.cue";
            if (DialogResult.OK != dlg.ShowDialog())
            {
                return;
            }

            string strFileName = dlg.FileName;

            FileInfo theImageFile = new FileInfo(strFileName);
            
            if (!theImageFile.Exists)
            {
                return;
            }

            if (theImageFile.Extension.ToLower() == ".cue")
            {
                bool b;
                b = m_burner.CreateProject(ProjectType.Cue);
                b = m_burner.AddFile(theImageFile.FullName, "", "", false, SavePathOption.DontSavePath);
                strFileName = "";
            }

            CommonNet.Burning.BurnDeveloped(m_burner, strFileName);
        }

        private void updateOptions(bool save)
        {
            if (save)
            {
                m_burner.Options.TestBurn = true;
                m_burner.Options.EjectAfterBurn = ejectDiskToolStripMenuItem.Checked;
                m_burner.Options.VerifyAfterBurn = verifyAfterBurnToolStripMenuItem.Checked;
                m_burner.Options.Joliet = jolietFileSystemToolStripMenuItem.Checked;
                m_burner.Options.RockRidge = rockRidgeFileSystemToolStripMenuItem.Checked;
                m_burner.Options.FinalizeDisk = finalizeToolStripMenuItem.Checked;
                if (    m_projectType == ProjectType.IsoUdf
                    ||  m_projectType == ProjectType.Data
                    ||  m_projectType == ProjectType.MixedMode
                   )
                {
                    m_burner.ISOExOptions.AllowLowercaseNames = AllowLowercaseNamesToolStripMenuItem.Checked;
                    m_burner.ISOExOptions.AllowManyDirectories = AllowManyDirectoriesToolStripMenuItem.Checked;
                    m_burner.ISOExOptions.AllowLongISO9660Names = AllowLongISO9660NamesToolStripMenuItem.Checked;
                    m_burner.ISOExOptions.AllowLongJolietNames = AllowLongJolietNamesToolStripMenuItem.Checked;
                    m_burner.ISOExOptions.ISOLevel = (IsoSDK.ISOLevel)(ISOLevel.Level1 + ISOLevelComboBox.SelectedIndex);
                }
            }
            else
            {
                ejectDiskToolStripMenuItem.Checked = m_burner.Options.EjectAfterBurn;
                verifyAfterBurnToolStripMenuItem.Checked = m_burner.Options.VerifyAfterBurn;
                jolietFileSystemToolStripMenuItem.Checked = m_burner.Options.Joliet;
                rockRidgeFileSystemToolStripMenuItem.Checked = m_burner.Options.RockRidge;
                finalizeToolStripMenuItem.Checked = m_burner.Options.FinalizeDisk;
                if (m_projectType == ProjectType.IsoUdf
                  || m_projectType == ProjectType.Data
                  || m_projectType == ProjectType.MixedMode
                 )
                {
                    AllowLowercaseNamesToolStripMenuItem.Checked = m_burner.ISOExOptions.AllowLowercaseNames;
                    AllowManyDirectoriesToolStripMenuItem.Checked = m_burner.ISOExOptions.AllowManyDirectories;
                    AllowLongISO9660NamesToolStripMenuItem.Checked = m_burner.ISOExOptions.AllowLongISO9660Names;
                    AllowLongJolietNamesToolStripMenuItem.Checked = m_burner.ISOExOptions.AllowLongJolietNames;
                    ISOLevelComboBox.SelectedIndex = (int)m_burner.ISOExOptions.ISOLevel - 1;
                }
            }
        }


        private void webToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Functions.GoToPixbytesSite();
        }

        private void rescanDevicesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            rescanButton_Click(sender, e);
        }

        private void ISOLevelToolStripMenuItem_Click(object sender, EventArgs e)
        {            
        }

        private void EnableControls()
        {
            propertiesToolStripMenuItem.Enabled = fileListView.FocusedItem != null && fileListView.FocusedItem.Tag != null;
        }

        private void propertiesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PropertiesDlg dlg = new PropertiesDlg(m_burner, (FileEntry)fileListView.FocusedItem.Tag);
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                m_fileListView.Refresh();
            }
        }

        private void fileListView_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            EnableControls();
        }
    }
}