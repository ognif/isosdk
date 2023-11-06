using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Reflection;
using System.IO;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpVideoSample
{
    struct AddFileTask
    {
        public bool bPicture;
        public string strFileName;
    };

    public partial class VideoSampleDlg : Form
    {
        private Burner m_burner;
        private ProjectType m_projectType = ProjectType.Vcd;
        private bool m_bBurnDevicesOnly = true;
        private string m_strCurFile = "";
        private Queue<AddFileTask> m_taskQueue = new Queue<AddFileTask>();

        delegate void ScannerDelegate(object sender, VideoScannerEventArgs e);
        delegate void ScanDoneDelegate(object sender, VideoScanDoneEventArgs e);

        delegate void ProcessTasksDelegate();

        private void ProcessNextTask()
        {
            lock (m_taskQueue)
            {
                if (m_taskQueue.Count > 0)
                {
                    AddFileTask t = m_taskQueue.Peek();

                    string strDestDir = t.bPicture ? "\\SEGMENT" : "\\";
                    string str = t.strFileName;
                    m_burner.AddFile(str, strDestDir, str.Substring(str.LastIndexOf(@"\") + 1),
                        true, SavePathOption.DontSavePath);
                }
            }
        }

        public VideoSampleDlg()
        {
            InitializeComponent();
            m_burner = new Burner();
            m_burner.Initialize("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7", ASPIInterface.Internal, true);

            m_burner.Language = "Default";

            Assembly assem = typeof(VideoSampleDlg).Assembly;
            AssemblyName assemName = assem.GetName();
            Text = "IsoSDK " + assemName.Version.Major + "." + assemName.Version.Minor + " CSharpVideoSample";

            m_burner.CreateProject(m_projectType);

            projectTypeComboBox.SelectedIndex = 0;

            m_burner.VideoScannerEvent += new Burner.VideoScannerEventHandler(this.OnScanner);
            m_burner.VideoScanDoneEvent += new Burner.VideoScanDoneEventHandler(this.OnScanDone);

            updateInterfaceMenu(ASPIInterface.Internal);

            tuneListViewForFiles(videoListView);
            tuneListViewForFiles(pictureListView);
        }

        private void OnScanner(object sender, VideoScannerEventArgs e)
        {
            if (statusStrip1.InvokeRequired)
            {
                ScannerDelegate d = new ScannerDelegate(OnScanner);
                this.Invoke(d, new object[] { sender, e });
                return;
            }

       
            if (m_strCurFile != e.m_strFileName)
            {
                m_strCurFile = e.m_strFileName;
                statusLabel.Text = m_strCurFile;
                statusProgress.Visible = true;
            }

            statusProgress.Value = System.Convert.ToInt32(e.m_fPercent);

          
        }

        private void OnScanDone(object sender, VideoScanDoneEventArgs e)
        {
            if (this.InvokeRequired)
            {
                ScanDoneDelegate d = new ScanDoneDelegate(OnScanDone);
                this.Invoke(d, new object[] {sender, e});
                return;
            }

            AddFileTask t = m_taskQueue.Dequeue();
            bool bPicture = t.bPicture;

            statusProgress.Visible = false;
            m_strCurFile = "";
            statusLabel.Text = "";

            if (e.m_nErrorCode == 0)
            {
                statusLabel.Text = e.m_strFileName + " was added.";
            }
            else
            {
                statusLabel.Text = e.m_strFileName + " was not added. " +
                    e.m_strError;
                MessageBox.Show(statusLabel.Text);
                ProcessTasksDelegate ntd = new ProcessTasksDelegate(ProcessNextTask);
                this.Invoke(ntd);
                return;
            }

            ListView lv = bPicture ? pictureListView : videoListView;

            FileInfo theFile = new FileInfo(e.m_strFileName);

            string AspRatio = "Unknown";

            switch (e.m_nAspectRatio)
            {
                case AspectRatio.SquarePixels:
                    AspRatio = "Square";
                    break;

                case AspectRatio.Display16To9:
                    AspRatio = "16x9";
                    break;

                case AspectRatio.Display221To2:
                    AspRatio = "2.21x1";
                    break;

                case AspectRatio.Display4To3:
                    AspRatio = "4x3";
                    break;
            }

            string.Format("2d:2d:2d", (e.m_nPlayTime / 3600), (e.m_nPlayTime / 60), (e.m_nPlayTime % 60));

            lv.Items.Add(new ListViewItem(new string[] 
{
            theFile.Name,

            ((Math.Round(100.0 * (theFile.Length / 1024.0) /1024.0))/100.0).ToString() + " MB", 

            string.Format("{0:d2}:{1:d2}:{2:d2}", (e.m_nPlayTime / 3600), (e.m_nPlayTime / 60), (e.m_nPlayTime % 60)),

            (theFile.LastWriteTime.ToString()),

            (Math.Round(e.m_nFPS * 100) / 100).ToString() + " fps",
            
            (e.m_nBitRate/1000).ToString() + " Kbps",
            
            AspRatio,

            e.m_nWidth.ToString() + "x" + e.m_nHeight.ToString(),            
}
            ));

            UpdateSize();

            ProcessTasksDelegate ntd2 = new ProcessTasksDelegate(ProcessNextTask);
            this.Invoke(ntd2);           
        }

        public Int64 GetDirectorySize(string strDirPath)
        {
            Int64 size = 0;

            using (DiskSession session = m_burner.OpenDiskSession(0, FileSystems.Unknown))
            {
                using (DiskDirectory directory = session.OpenDirectory(strDirPath))
                {
                    int nFileCount = directory.FilesCount;
                    for (Int32 nIndex = 0; nIndex < nFileCount; ++nIndex)
                    {
                        FileEntry entry = directory.get_Files(nIndex);

                        if ((entry.Attributes & IsoSDK.FileAttributes.Directory) == IsoSDK.FileAttributes.Directory)
                        {
                            string strDir = entry.Path;
                            strDir += @"\";
                            strDir += entry.Name;

                            size += GetDirectorySize(strDir);
                        }
                        else
                        {
                            size += entry.Size;
                        }
                    }
                }
            }

            return size;
        }

        private void UpdateSize()
        {
            int size = System.Convert.ToInt32(Math.Round(GetDirectorySize("\\") / 1000.0 / 1000.0));
            sizeProgressBar.Value = size > sizeProgressBar.Maximum ? sizeProgressBar.Maximum : size;
        }

        private void tuneListViewForFiles(ListView lv)
        {
            lv.Columns.Add("Name", 150);
            lv.Columns.Add("Size", 80);
            lv.Columns.Add("Length", 80);
            lv.Columns.Add("Modified", 80);
            lv.Columns.Add("Frame rate", 80);
            lv.Columns.Add("Bit rate", 80);
            lv.Columns.Add("Aspect ratio", 80);
            lv.Columns.Add("Dimensions", 80);
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

        private void updateOptions(bool save)
        {
            if (save)
            {
                m_burner.Options.EjectAfterBurn = ejectDiskToolStripMenuItem.Checked;
                m_burner.Options.Joliet = jolietFileSystemToolStripMenuItem.Checked;
            }
            else
            {
                ejectDiskToolStripMenuItem.Checked = m_burner.Options.EjectAfterBurn;
                jolietFileSystemToolStripMenuItem.Checked = m_burner.Options.Joliet;
            }
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Additional.About();
        }

        private void webToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Functions.GoToPixbytesSite();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void AddFile(object sender, EventArgs e)
        {
            bool bPicture = sender.Equals(addPictureToolStripMenuItem);

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.CheckFileExists = true;
            dlg.Multiselect = true;
            dlg.Filter = "MPEG files (*.*)|*.mpg";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                foreach (string str in dlg.FileNames)
                {
                    lock (m_taskQueue)
                    {
                        AddFileTask t;
                        t.bPicture = bPicture;
                        t.strFileName = str;
                        m_taskQueue.Enqueue(t);
                    }
                }
                ProcessTasksDelegate d = new ProcessTasksDelegate(ProcessNextTask);
                this.Invoke(d);
            }            
        }

        private void deleteSelectedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bPicture = tabControl1.SelectedTab == tabPagePictures;

            ListView lv = bPicture ? pictureListView : videoListView;

            int startIndex = bPicture ? m_burner.FirstSegmentIndex : m_burner.FirstTrackIndex;

            while (lv.SelectedItems.Count > 0)
            {
                int item = lv.SelectedItems[0].Index;
                m_burner.EraseMpegByIndex(startIndex + item);
                lv.Items.RemoveAt(item);
                UpdateSize();
            }
        }

        private void resetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.ClearAll();
            ClearSizeAndFiles();          
        }

        private void ClearSizeAndFiles()
        {
            pictureListView.Items.Clear();
            videoListView.Items.Clear();
            UpdateSize();            
        }

        private void projectTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            IsoSDK.ProjectType pt = projectTypeComboBox.SelectedIndex == 0 ? ProjectType.Vcd : ProjectType.Svcd;
            resetToolStripMenuItem_Click(sender, e);
            m_burner.CreateProject(pt);
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

        private void burnWithCustomDialogToolStripMenuItem_Click(object sender, EventArgs e)
        {
            updateOptions(true);
            prepareMenus();

            CommonNet.Burning.BurnDeveloped(m_burner, "");
        }

        private void prepareMenus()
        {
            
            if (pictureListView.Items.Count > 0)
	        {
		        // 1st case : we have pictures

		        // create key 1..N handlers
		        int numPictureHandlers = Math.Min(pictureListView.Items.Count, 99);
		        int numVideoHandlers = Math.Min(videoListView.Items.Count,  99 - numPictureHandlers);

		        // set numeric key handler for menu picture
		        for(int i = 0; i < numPictureHandlers; ++i)
		        {
m_burner.SetVCDKeyHandler(m_burner.FirstSegmentIndex, m_burner.VCDKey0 + i + 1, m_burner.FirstSegmentIndex + i + 1);
		        }

		        for(int i = 0; i < numVideoHandlers; ++i)
		        {
m_burner.SetVCDKeyHandler(m_burner.FirstSegmentIndex, m_burner.VCDKey0 + numPictureHandlers + i + 1,
    m_burner.FirstTrackIndex + i);
		        }

		        for(int i = 0; i < pictureListView.Items.Count; ++i)
		        {
			        // set timeout for all pictures except last picture
			        if (i != pictureListView.Items.Count - 1)
			        {
				        int timeout = (i == 0) ? 120 : 10;
m_burner.SetVCDTimeOutHandler(m_burner.FirstSegmentIndex + i, timeout, m_burner.FirstSegmentIndex + i + 1);
m_burner.SetVCDKeyHandler(m_burner.FirstSegmentIndex + i, m_burner.VCDKeyNext,
    m_burner.FirstSegmentIndex + i + 1);
			        }

			        if (i != 0)
			        {
m_burner.SetVCDKeyHandler(m_burner.FirstSegmentIndex + i, m_burner.VCDKeyPrevious,
    m_burner.FirstSegmentIndex + i - 1);
				        // return from any picture to the menu picture
m_burner.SetVCDKeyHandler(m_burner.FirstSegmentIndex + i, m_burner.VCDKeyReturn,
    m_burner.FirstSegmentIndex);
			        }
		        }

		        // if there is video files set transition keys pictures<->video
		        if (videoListView.Items.Count != 0)
		        {
m_burner.SetVCDTimeOutHandler(m_burner.FirstSegmentIndex + pictureListView.Items.Count - 1,
    10, m_burner.FirstTrackIndex);

m_burner.SetVCDKeyHandler(m_burner.FirstSegmentIndex + pictureListView.Items.Count -1 ,
    m_burner.VCDKeyNext, m_burner.FirstTrackIndex);

m_burner.SetVCDKeyHandler(m_burner.FirstTrackIndex,
    m_burner.VCDKeyPrevious, m_burner.FirstSegmentIndex + pictureListView.Items.Count -1 );
		        }

		        // create prev-next handlers
		        for(int i = 0; i < videoListView.Items.Count; ++i)
		        {
			        if (i != videoListView.Items.Count - 1)
			        {
				        // jump to next item if user press "Next"
				        m_burner.SetVCDKeyHandler(m_burner.FirstTrackIndex + i, m_burner.VCDKeyNext, m_burner.FirstTrackIndex + i + 1);
				        // jump to next item after playing current item
				        m_burner.SetVCDTimeOutHandler(m_burner.FirstTrackIndex + i, 0, m_burner.FirstTrackIndex + i + 1);
			        }
			        else
			        {
				        // jump to main menu after playing last video item
				        m_burner.SetVCDTimeOutHandler(m_burner.FirstTrackIndex + i, 0, m_burner.FirstSegmentIndex);
			        }

			        if (i != 0)
			        {
				        // jump previous item if user press "Previous"
				        m_burner.SetVCDKeyHandler(m_burner.FirstTrackIndex + i, m_burner.VCDKeyPrevious, m_burner.FirstTrackIndex + i - 1);
			        }

			        // return to the main menu if user press "Return"
			        m_burner.SetVCDKeyHandler(m_burner.FirstTrackIndex + i, m_burner.VCDKeyReturn, m_burner.FirstSegmentIndex);
		        }
	        }
	        else
	        {
		        // 2nd case : we have no pictures in project

		        // create "prev-next" key handlers
		        for(int i = 0; i < videoListView.Items.Count; ++i)
		        {
			        if (i != 0)
				        m_burner.SetVCDKeyHandler(m_burner.FirstTrackIndex + i, m_burner.VCDKeyPrevious, m_burner.FirstTrackIndex + i - 1);

			        if (i != videoListView.Items.Count -1)
				        m_burner.SetVCDKeyHandler(m_burner.FirstTrackIndex + i, m_burner.VCDKeyNext, m_burner.FirstTrackIndex + i + 1);
		        }
	        }
        }

        private void eraseDiskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Erase.EraseDeveloped(m_burner);
        }

        private void AspiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            updateInterfaceMenu(
                sender == internalToolStripMenuItem 
                    ? ASPIInterface.Internal 
                    : 
                    (sender == frogAspiToolStripMenuItem ? 
                         ASPIInterface.FrogAspi 
                            : ASPIInterface.WnAspi));
        }

        private void rescanDevicesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.RescanDevices();
            UpdateDeviceCombo();
        }

        private void burnDevicesOnlyToolStripMenuItem_CheckStateChanged(object sender, EventArgs e)
        {
            m_bBurnDevicesOnly = burnDevicesOnlyToolStripMenuItem.Checked;
            UpdateDeviceCombo();
        }

        private void disableImagewriterToolStripMenuItem_CheckStateChanged(object sender, EventArgs e)
        {
            m_burner.EnableImageDevice(!disableImagewriterToolStripMenuItem.Checked);
            UpdateDeviceCombo();
        }

   
    }
}