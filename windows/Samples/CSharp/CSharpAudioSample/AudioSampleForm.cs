using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Reflection;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpAudioSample
{
    public partial class AudioSampleForm : Form
    {

        private Burner m_burner;
        private bool m_bBurnDevicesOnly = true;        
        private TrackListView m_trackListView;
        private FileListView m_fileListView;

        public AudioSampleForm()
        {
            InitializeComponent();
            
                       
            m_burner = new Burner();
            m_burner.Initialize("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7", ASPIInterface.Internal, true);
            m_burner.Language = "Default";

            Assembly assem = typeof(AudioSampleForm).Assembly;
            AssemblyName assemName = assem.GetName();
            Text = "IsoSDK " + assemName.Version.Major + "." + assemName.Version.Minor + " CSharpAudioSample";

            m_trackListView = new TrackListView(listViewAudio, m_burner);
            
            
            comboBoxProjectType.Items.Add("Audio CD");
            comboBoxProjectType.Items.Add("Mixed Mode CD");
            comboBoxProjectType.SelectedIndex = 0;

            m_fileListView = new FileListView(listViewData, m_burner);
            
            
            //set options by default           
            m_burner.Options.VolumeLabel = "ISOSDK";
            updateOptions(true);                                 
            
            UpdateDeviceCombo();
            updateInterfaceMenu(ASPIInterface.Internal);
        }

        private void webToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Functions.GoToPixbytesSite();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Additional.About();
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

        private void rescanDevicesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.RescanDevices();
            UpdateDeviceCombo();
        }

        private void burnDevicesOnlyToolStripMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            m_bBurnDevicesOnly = !m_bBurnDevicesOnly;
            UpdateDeviceCombo();
        }

        private void disableImagewriterToolStripMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            m_burner.ImageDeviceEnabled = !disableImagewriterToolStripMenuItem.Checked;
            m_burner.RescanDevices();
            UpdateDeviceCombo();
        }

        private void burnDevelopedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            updateOptions(true);
            CommonNet.Burning.BurnDeveloped(m_burner, "");
        }

        private void updateOptions(bool save)
        {
            if (save)
            {
                m_burner.Options.EjectAfterBurn = ejectDiskToolStripMenuItem.Checked;
                m_burner.Options.VerifyAfterBurn = verifyAfterBurnToolStripMenuItem.Checked;
                m_burner.Options.Joliet = jolietFileSystemToolStripMenuItem.Checked;
                m_burner.Options.RockRidge = rockRidgeFilesystemToolStripMenuItem.Checked;
                m_burner.Options.FinalizeDisk = finalizeToolStripMenuItem.Checked;
                m_burner.WriteCDTextInUnicode = CDTextInUnicodeToolStripMenuItem.Checked;
                if (comboBoxProjectType.SelectedIndex == 1)
                {
                    m_burner.ISOExOptions.AllowLowercaseNames = AllowLowercaseNamesToolStripMenuItem.Checked;
                    m_burner.ISOExOptions.AllowManyDirectories = AllowManyDirectoriesToolStripMenuItem.Checked;

                    m_burner.ISOExOptions.ISOLevel = (IsoSDK.ISOLevel)(ISOLevel.Level1 + ISOLevelComboBox.SelectedIndex);
                }
                CommonNet.Functions.HandleError(m_burner);                
            }
            else
            {
                ejectDiskToolStripMenuItem.Checked = m_burner.Options.EjectAfterBurn;
                verifyAfterBurnToolStripMenuItem.Checked = m_burner.Options.VerifyAfterBurn;
                jolietFileSystemToolStripMenuItem.Checked = m_burner.Options.Joliet;
                rockRidgeFilesystemToolStripMenuItem.Checked = m_burner.Options.RockRidge; 
                finalizeToolStripMenuItem.Checked = m_burner.Options.FinalizeDisk;
                CDTextInUnicodeToolStripMenuItem.Checked = m_burner.WriteCDTextInUnicode;
                if (comboBoxProjectType.SelectedIndex == 1)
                {
                    AllowLowercaseNamesToolStripMenuItem.Checked = m_burner.ISOExOptions.AllowLowercaseNames;
                    AllowManyDirectoriesToolStripMenuItem.Checked = m_burner.ISOExOptions.AllowManyDirectories;
                    ISOLevelComboBox.SelectedIndex = (int)m_burner.ISOExOptions.ISOLevel - 1;
                }
            }
        }

        private void eraseToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            CommonNet.Erase.EraseDeveloped(m_burner);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void deviceComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int nIndex = deviceComboBox.SelectedIndex;
            if (nIndex == deviceComboBox.Items.Count - 1 && nIndex != 0)
            {
              /*  CSharpDataSample.MultiDeviceDlg dlg = new CSharpDataSample.MultiDeviceDlg(m_burner);
                if (DialogResult.OK != dlg.ShowDialog())
                {
                    deviceComboBox.SelectedIndex = 0;
                }*/

            }
            else
            {
                string str = deviceComboBox.Text;
                m_burner.BurnDevice = str;
            }
        }

        private void deleteSelectedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_trackListView.DeleteSelected();
            RecountSize();
        }

        private void createFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_fileListView.CreateFolder();
            RecountSize();
        }

        private void addFileFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_fileListView.AddFile();
            RecountSize();
        }

        private void SetSizeValue(int sizeInSeconds)
        {
            const int secondsInProgressBar = 90 * 60;
            int value = (100 * sizeInSeconds) / secondsInProgressBar;
            sizeProgressBar.Value = (value > 100) ? 100 : value;
        }

        private void comboBoxProjectType_SelectedIndexChanged(object sender, EventArgs e)
        {
            //TO DO: Select Project Type
            //Show or hide data tab
            //Clear controls
            if (comboBoxProjectType.SelectedIndex == 0)
            {
                m_burner.CreateProject(ProjectType.Audio);

                if (tabControl.TabPages.Count == 2)
                {
                    tabControl.TabPages.Remove(tabPageData);
                }
                
                dataToolStripMenuItem.Enabled = false;

                m_trackListView.SetRootDirectory("\\");

                AllowLowercaseNamesToolStripMenuItem.Enabled = false;                
                AllowManyDirectoriesToolStripMenuItem.Enabled = false;
                ISOLevelComboBox.Enabled = false;                
                jolietFileSystemToolStripMenuItem.Enabled = false;
            }
            else
            {
                m_burner.CreateProject(ProjectType.MixedMode);

                if (tabControl.TabPages.Count == 1)
                {
                    tabControl.TabPages.Add(tabPageData);
                }                
                
                dataToolStripMenuItem.Enabled = true;

                m_trackListView.SetRootDirectory("\\audio");

                AllowLowercaseNamesToolStripMenuItem.Enabled = true;
                AllowManyDirectoriesToolStripMenuItem.Enabled = true;
                ISOLevelComboBox.Enabled = true;
                jolietFileSystemToolStripMenuItem.Enabled = true;
            }

            updateOptions(false);
        }

        private void dataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (dataToolStripMenuItem.Enabled)
            {
                tabControl.SelectedTab = tabPageData;
            }
        }

        private void addAudioFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_trackListView.AddFile();
            RecountSize();
        }

        private void RecountSize()
        {
            int size = m_trackListView.GetSizeInSeconds();
            if (comboBoxProjectType.SelectedIndex == 1)
            {
                size += m_fileListView.GetSizeInSeconds();
            }
            SetSizeValue(size);            
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            m_fileListView.AddFolder();
            RecountSize();
        }

        private void renameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_fileListView.RenameFile();
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            m_fileListView.DeleteItem();
            RecountSize();
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {   
            m_trackListView.ResetList();          
            RecountSize();
        }

        private void audioToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            tabControl.SelectTab(tabPageAudio);
        }

        private void toolStripResetData_Click(object sender, EventArgs e)
        {
            m_fileListView.ResetList();
            RecountSize();
        }

        private void playSelectedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_trackListView.Play();
        }

        private void stopPlaybackToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.AudioFileStop();
            CommonNet.Functions.HandleError(m_burner);
        }

        private void listViewAudio_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void listViewData_DoubleClick(object sender, EventArgs e)
        {
            m_fileListView.OnDoubleClicked();
        }

        private void cDTextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_trackListView.DiskCDText();
        }

        private void trackCDTextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_trackListView.TrackCDText();
        }

        private void internalToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.Internal);
        }

        private void wnApsiToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.WnAspi);
        }

        private void frogAspiToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.FrogAspi);
        }

        private void setISOLevelToolStripMenuItem_Click(object sender, EventArgs e)
        {            
        }

        private void loadBassPluginToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.LoadBassPlugin("bass_ape.dll");
            CommonNet.Functions.HandleError(m_burner);
        }

        private void loadBassWMAPluginToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.LoadBassPlugin("basswma.dll");
            CommonNet.Functions.HandleError(m_burner);
        }
    }
}