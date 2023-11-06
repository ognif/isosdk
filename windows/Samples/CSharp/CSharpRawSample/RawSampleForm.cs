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

namespace CSharpRawSample
{
    public partial class RawSampleForm : Form
    {
        private Burner m_burner;
        private bool m_bBurnDevicesOnly = true;
        private KMaskList m_maskListData;
        private KMaskList m_maskListIgnore;

        private List<RawTrack> m_TrackList = new List<RawTrack>();

        public RawTrackFormat TrackMode
        {
            set
            {
                comboBoxTrackMode.SelectedIndex = (int)value;
            }
            get
            {
                return (RawTrackFormat)comboBoxTrackMode.SelectedIndex;
            }
        }


        public RawSampleForm()
        {
            InitializeComponent();
            m_burner = new Burner();
            m_burner.Initialize("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7", ASPIInterface.Internal, true);
            CommonNet.Functions.HandleError(m_burner);
            m_burner.Language = "Default";

            Assembly assem = typeof(RawSampleForm).Assembly;
            AssemblyName assemName = assem.GetName();
            Text = "IsoSDK " + assemName.Version.Major + "." + assemName.Version.Minor + " CSharpRawSample";


            UpdateDeviceCombo();
            updateInterfaceMenu(ASPIInterface.Internal);

            m_burner.CreateProject(ProjectType.Raw);
            CommonNet.Functions.HandleError(m_burner);

            listViewTracks.Items.Clear();

            updateOptions(true);

            listViewTracks.Columns.Add("No.", 35);
            listViewTracks.Columns.Add("Ind.", 35);
            listViewTracks.Columns.Add("Mode",100);
            listViewTracks.Columns.Add("DataMask",100);
            listViewTracks.Columns.Add("IgnoreMask",100);
            listViewTracks.Columns.Add("Start Address", 100);
            listViewTracks.Columns.Add("Length", 100);
            listViewTracks.Columns.Add("Offset", 100);

            listViewTracks.MultiSelect = false;

            comboBoxTrackMode.Items.Add("Audio");
            comboBoxTrackMode.Items.Add("Mode1");
            comboBoxTrackMode.Items.Add("Mode2 Formless");
            comboBoxTrackMode.Items.Add("Mode2 Form1");
            comboBoxTrackMode.Items.Add("Mode2 Form2");            

            Dictionary<RawDataType, CheckBox> d = new Dictionary<RawDataType,CheckBox>();
            d.Add(RawDataType.Data, checkBoxData);
            d.Add(RawDataType.EdcEcc, checkBoxEdcEcc);
            d.Add(RawDataType.SubchPQ, checkBoxSubchPQ);
            d.Add(RawDataType.SubchPW, checkBoxSubchPW);
            d.Add(RawDataType.SubchRW, checkBoxSubchRW);
            d.Add(RawDataType.SubHeaders, checkBoxSubHeaders);
            d.Add(RawDataType.SyncHeader, checkBoxSyncHeader);
            m_maskListData = new KMaskList(d);

            d = new Dictionary<RawDataType,CheckBox>();
            d.Add(RawDataType.Data, checkBoxIgnoreData);
            d.Add(RawDataType.EdcEcc, checkBoxIgnoreEdcEcc);
            d.Add(RawDataType.SubchPQ, checkBoxIgnoreSubchPQ);
            d.Add(RawDataType.SubchPW, checkBoxIgnoreSubchPW);
            d.Add(RawDataType.SubchRW, checkBoxIgnoreSubchRW);
            d.Add(RawDataType.SubHeaders, checkBoxIgnoreSubHeaders);
            d.Add(RawDataType.SyncHeader, checkBoxIgnoreSyncHeader);
            m_maskListIgnore = new KMaskList(d);

            ResetForm();            
        }

        private void webToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Functions.GoToPixbytesSite();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Additional.About();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void updateOptions(bool save)
        {
            if (save)
            {
                m_burner.Options.EjectAfterBurn = ejectDiskToolStripMenuItem.Checked;
                m_burner.Options.VerifyAfterBurn = verifyAfterBurnToolStripMenuItem.Checked;
                m_burner.Options.Joliet = jolietFileSystemToolStripMenuItem.Checked;
                m_burner.Options.FinalizeDisk = finalizeToolStripMenuItem.Checked;
            }
            else
            {
                ejectDiskToolStripMenuItem.Checked = m_burner.Options.EjectAfterBurn;
                verifyAfterBurnToolStripMenuItem.Checked = m_burner.Options.VerifyAfterBurn;
                jolietFileSystemToolStripMenuItem.Checked = m_burner.Options.Joliet;
                finalizeToolStripMenuItem.Checked = m_burner.Options.FinalizeDisk;
            }
        }

        private void burnDevelopedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            updateOptions(true);

            m_burner.SetRawStructure(m_TrackList.ToArray());
            CommonNet.Functions.HandleError(m_burner);

            CommonNet.Burning.BurnDeveloped(m_burner, "");
        }

        private void eraseToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            CommonNet.Erase.EraseDeveloped(m_burner);
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

        private void burnDevicesOnlyToolStripMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            m_bBurnDevicesOnly = !m_bBurnDevicesOnly;
            UpdateDeviceCombo();
        }

        private void disableImagewriterToolStripMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            m_burner.ImageDeviceEnabled = !disableImagewriterToolStripMenuItem.Checked;
            UpdateDeviceCombo();
        }

        private void rescanDevicesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.RescanDevices();
            UpdateDeviceCombo();
        }

        private void buttonResetForm_Click(object sender, EventArgs e)
        {
            ResetForm();
        }

        private void ResetForm()
        {
            numericUpDownTrackNumber.Value = 1;
            numericUpDownTrackIndex.Value = 0;
            comboBoxTrackMode.SelectedIndex = 0;

            m_maskListData.Mask = RawDataType.No;
            m_maskListIgnore.Mask = RawDataType.No;           

            textBoxStartAddress.Text = textBoxOffset.Text = 
                textBoxTrackLength.Text = "0";

            TrackMode = RawTrackFormat.Mode1;

            m_TrackList.Clear();
            listViewTracks.Items.Clear();
        }

        private void addFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddFile();
        }

        public void AddFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.CheckFileExists = true;
            ofd.Multiselect = false;
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                m_burner.ClearAll();
                if (CommonNet.Functions.HandleError(m_burner))
                {
                    return;
                }

                m_burner.AddFile(ofd.FileName, "", "", false, SavePathOption.DontSavePath);
                if (CommonNet.Functions.HandleError(m_burner))
                {
                    return;
                }
                
                if (!comboBoxAddFile.Items.Contains(ofd.FileName))
                {
                    comboBoxAddFile.Items.Add(ofd.FileName);
                }

                comboBoxAddFile.SelectedItem = ofd.FileName;                
            }
        }

        private void buttonBrowse_Click(object sender, EventArgs e)
        {
            AddFile();
        }

        private void buttonAnalyze_Click(object sender, EventArgs e)
        {
            AnalyzeFile();
        }

        private int format2SectorSize(RawTrackFormat Format)
        {
	        if (Format == RawTrackFormat.Mode1)
            {
                return 2048;
            }
		     
		    return 2352;
        }

        private int format2SectorSize(TrackFormat Format)
        {
            if (Format == TrackFormat.DataMode1)
            {
                return 2048;
            }

            return 2352;
        }

        String format2Text(RawTrackFormat Format)
        {
            switch (Format)
	        {
                case RawTrackFormat.Audio:
                    return "Audio";

                case RawTrackFormat.Mode1:
                    return "Mode1";

                case RawTrackFormat.Mode2Formless:
                    return "Mode2 Formless";

                case RawTrackFormat.Mode2Form1:
                    return "Mode2 Form1";

                case RawTrackFormat.Mode2Form2:
                    return "Mode2 Form2";
        		
		        default:
                    return "Unknown";
	        }
        }

        private void addMaskText(ref String to, String what)
	    {
		    if(to != "") to += " | ";
		    to += what;
	    }

        private String datamask2Text(RawDataType DataType)
        {
            String strRes = "";
            if ((DataType & RawDataType.SyncHeader) == RawDataType.SyncHeader)
                addMaskText(ref strRes, "BS_RDT_SYNC_HEADER");
            if ((DataType & RawDataType.SubHeaders) == RawDataType.SubHeaders)
                addMaskText(ref strRes, "BS_RDT_SUBHEADERS");
            if ((DataType & RawDataType.Data) == RawDataType.Data)
                addMaskText(ref strRes, "BS_RDT_DATA");
            if ((DataType & RawDataType.EdcEcc) == RawDataType.EdcEcc)
                addMaskText(ref strRes, "BS_RDT_EDC_ECC");
            if ((DataType & RawDataType.SubchPQ) == RawDataType.SubchPQ)
                addMaskText(ref strRes, "BS_RDT_SUBCH_PQ");
            if ((DataType & RawDataType.SubchPW) == RawDataType.SubchPW)
                addMaskText(ref strRes, "BS_RDT_SUBCH_PW");
            if ((DataType & RawDataType.SubchRW) == RawDataType.SubchRW)
                addMaskText(ref strRes, "BS_RDT_SUBCH_RW");
            return strRes;
        }

        private Int64 AddTrackInfo(int nNumber, int nIndex, Int64 nDiskOffset, RawTrackFormat RawFormat, TrackInfo sTrack)
        {
	        int nTrackListNumber = listViewTracks.Items.Count;

	        RawTrack rawTrack = new RawTrack();
	        rawTrack.Number = nNumber;
	        rawTrack.Index = nIndex;
	        rawTrack.Offset = nDiskOffset;
            rawTrack.StartAddress = sTrack.StartLBA;
            rawTrack.Format = RawFormat;
	        rawTrack.DataTypeMask = RawDataType.Data;
	        rawTrack.IgnoreDataMask = RawDataType.No;
	        rawTrack.Length = sTrack.Size;
        	

	        switch(RawFormat)
	        {
                case RawTrackFormat.Mode2Form1:
			        rawTrack.DataTypeMask   |= RawDataType.SubHeaders | RawDataType.EdcEcc;
			        rawTrack.IgnoreDataMask |= RawDataType.EdcEcc;
			        break;

		        case RawTrackFormat.Mode2Form2:
			        rawTrack.DataTypeMask   |= RawDataType.SyncHeader|RawDataType.SubHeaders | RawDataType.EdcEcc;
			        rawTrack.IgnoreDataMask |= RawDataType.SyncHeader | RawDataType.EdcEcc;
			        break;
	        }

	        //add to vector
            m_TrackList.Add(rawTrack);

            listViewTracks.Items.Add(rawTrack.Number.ToString());
            listViewTracks.Items[nTrackListNumber].SubItems.Add(rawTrack.Index.ToString());
            listViewTracks.Items[nTrackListNumber].SubItems.Add(format2Text(rawTrack.Format));
            listViewTracks.Items[nTrackListNumber].SubItems.Add(datamask2Text(rawTrack.DataTypeMask));
            listViewTracks.Items[nTrackListNumber].SubItems.Add(datamask2Text(rawTrack.IgnoreDataMask));
            listViewTracks.Items[nTrackListNumber].SubItems.Add(rawTrack.StartAddress.ToString());
            listViewTracks.Items[nTrackListNumber].SubItems.Add(rawTrack.Length.ToString());
            listViewTracks.Items[nTrackListNumber].SubItems.Add(rawTrack.Offset.ToString());

            numericUpDownTrackNumber.Value = Convert.ToDecimal(nNumber + 1);

            nDiskOffset += (long)rawTrack.Length * format2SectorSize(rawTrack.Format);

	        return nDiskOffset;
        }

        private void AnalyzeFile()
        {
            if (comboBoxAddFile.SelectedItem == null)
            {
                MessageBox.Show("Add file to analyze, please.", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            ResetForm();

            string fileName = comboBoxAddFile.SelectedItem.ToString();

	        m_burner.AddFile(fileName, "", "", false, new SavePathOption());
            CommonNet.Functions.HandleError(m_burner);

	        Int64 nDiskOffset = 0;
	        int nCurrentLastSector = 0;

            m_burner.SetImageFilePath(fileName);
            if (CommonNet.Functions.HandleError(m_burner))
	        {
		        return;
	        }

	        m_burner.ReadDevice = "#";
	        if (CommonNet.Functions.HandleError(m_burner))
	        {
		        return;
	        }

            MediumInfo mi = m_burner.GetMediumInfo((int)DeviceIndex.Read);
	        CommonNet.Functions.HandleError(m_burner);

            //First pregap (-150) analize

	        if (mi != null && mi.FirstSession > 0 && mi.LastSession > 0)
	        {
		        for (int i = mi.FirstSession; i <= mi.LastSession; i++)
		        {
			        SessionInfo si = m_burner.GetSessionInfo((int)DeviceIndex.Read, i);
			        CommonNet.Functions.HandleError(m_burner);

			        for(int j = si.FirstTrack; j <= si.LastTrack; ++j)
			        {
				        TrackInfo cTrackInfo = m_burner.GetTrackInfo((int)DeviceIndex.Read, j);
				        CommonNet.Functions.HandleError(m_burner);

				        nDiskOffset += (long)cTrackInfo.Size * format2SectorSize(cTrackInfo.Format);
			        }
		        }

                FileInfo fileInfo =  new FileInfo(fileName);

                if (nDiskOffset < fileInfo.Length)
		        {
			        //need first pregap
			        nCurrentLastSector = -150;
		        }
	        }

	        nDiskOffset = 0;

	        int nTrackNumber = listViewTracks.Items.Count + 1;

	        if (mi.FirstSession > 0 && mi.LastSession > 0)
	        {
		        for (int i = mi.FirstSession; i <= mi.LastSession; i++)
		        {
			        SessionInfo si = m_burner.GetSessionInfo((int)DeviceIndex.Read, i);
			        CommonNet.Functions.HandleError(m_burner);

			        for(int j = si.FirstTrack; j <= si.LastTrack; ++j)
			        {
                        TrackInfo cTrackInfo = m_burner.GetTrackInfo((int)DeviceIndex.Read, j);
				        CommonNet.Functions.HandleError(m_burner);

                        RawTrackFormat rawFormat = m_burner.GetTrackFormatEx((int)DeviceIndex.Read, j);

				        if (nCurrentLastSector != cTrackInfo.StartLBA)
				        {
					        TrackInfo cPregapInfo = new TrackInfo();

					        cPregapInfo.Format = cTrackInfo.Format;
					        cPregapInfo.StartLBA = nCurrentLastSector;
					        cPregapInfo.Size = cTrackInfo.StartLBA - nCurrentLastSector;

					        nDiskOffset = AddTrackInfo(nTrackNumber, 0, nDiskOffset, rawFormat, cPregapInfo);
				        }
        		
				        nDiskOffset = AddTrackInfo(nTrackNumber, 1, nDiskOffset, rawFormat, cTrackInfo);

				        nCurrentLastSector = cTrackInfo.StartLBA + cTrackInfo.Size;

				        ++nTrackNumber;
			        }
		        }
	        }

            m_burner.SetImageFilePath("");
            CommonNet.Functions.HandleError(m_burner);
        }

        private void tryToToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AnalyzeFile();
        }

        private void AddTrack()
        {
            RawTrack track = new RawTrack();

	        int nNumb = 1;
	        int nInd = -1;

	        if (m_TrackList.Count > 0)
	        {
		        nNumb = m_TrackList[m_TrackList.Count - 1].Number + 1;
                nInd = m_TrackList[m_TrackList.Count - 1].Index;
	        }
        	
	        int nItemPos = listViewTracks.Items.Count;
	        int nTrackNumber = Convert.ToInt32(numericUpDownTrackNumber.Value);
            int nTrackIndex = Convert.ToInt32(numericUpDownTrackIndex.Value);

	        if (nNumb == nTrackNumber || 
		        (nNumb - 1 == nTrackNumber && nTrackIndex > nInd &&
		        (nItemPos - 2 < 0 || m_TrackList[nItemPos - 2].Number != nTrackNumber )))
	        {
		        track.Number = nTrackNumber;
                track.Index = nTrackIndex;
                track.Format = TrackMode;
                track.DataTypeMask = m_maskListData.Mask;
                track.IgnoreDataMask = m_maskListIgnore.Mask;
                track.StartAddress = Convert.ToInt32(textBoxStartAddress.Text);
                track.Length = Convert.ToInt32(textBoxTrackLength.Text);
                track.Offset = Convert.ToInt32(textBoxOffset.Text);

                if (track.Length <= 0)
                {
                    MessageBox.Show("The length of the track should be more than '0'");
                    return;
                }

                listViewTracks.Items.Add(nTrackNumber.ToString());
                listViewTracks.Items[nItemPos].SubItems.Add(nTrackIndex.ToString());
                listViewTracks.Items[nItemPos].SubItems.Add(comboBoxTrackMode.Text);
                listViewTracks.Items[nItemPos].SubItems.Add(datamask2Text(m_maskListData.Mask));
                listViewTracks.Items[nItemPos].SubItems.Add(datamask2Text(m_maskListIgnore.Mask));
                listViewTracks.Items[nItemPos].SubItems.Add(textBoxStartAddress.Text);
                listViewTracks.Items[nItemPos].SubItems.Add(textBoxTrackLength.Text);
                listViewTracks.Items[nItemPos].SubItems.Add(textBoxOffset.Text);
               	
                m_TrackList.Add(track);
	        }
	        else
	        {
		        MessageBox.Show("Track number or Index is not correct.");
	        }
        }

        private void buttonAddTrack_Click(object sender, EventArgs e)
        {
            AddTrack();
        }

        private void buttonDeleteTrack_Click(object sender, EventArgs e)
        {
            ListView.SelectedIndexCollection selectedIndexes = listViewTracks.SelectedIndices;
            
            for (int i = 0; i < selectedIndexes.Count; ++i)
            {
                int nIndex = selectedIndexes[i];
                listViewTracks.Items.RemoveAt(nIndex);
                m_TrackList.RemoveAt(nIndex);
            }
        }

        private void resetTrackListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ResetForm();
        }

        private void addTrackToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddTrack();
        }

        private void listViewTracks_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listViewTracks.SelectedIndices.Count == 0)
            {
                return;
            }

            int nSelected = listViewTracks.SelectedIndices[0];

            if (nSelected >= m_TrackList.Count)
            {
                return;
            }

            numericUpDownTrackNumber.Value = Convert.ToDecimal(m_TrackList[nSelected].Number);
            numericUpDownTrackIndex.Value = Convert.ToDecimal(m_TrackList[nSelected].Index);
            comboBoxTrackMode.Text = format2Text(m_TrackList[nSelected].Format);

            m_maskListData.Mask = m_TrackList[nSelected].DataTypeMask;
            m_maskListIgnore.Mask = m_TrackList[nSelected].IgnoreDataMask;

            textBoxStartAddress.Text = m_TrackList[nSelected].StartAddress.ToString();
            textBoxTrackLength.Text = m_TrackList[nSelected].Length.ToString();
            textBoxOffset.Text = m_TrackList[nSelected].Offset.ToString();
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
    }

    public class KMaskList
    {
        private Dictionary<RawDataType, CheckBox> m_checkBoxDict;

        public KMaskList(Dictionary<RawDataType, CheckBox> dict)
        {
            m_checkBoxDict = dict;
        }

        
        public RawDataType Mask
        {
            get
            {
                RawDataType res = RawDataType.No;
                foreach (KeyValuePair<RawDataType, CheckBox> pair in m_checkBoxDict)
                {
                    res |= (pair.Value.Checked ? pair.Key : RawDataType.No);
                }
                return res;                                
            }
            set
            {
                foreach (KeyValuePair<RawDataType, CheckBox> pair in m_checkBoxDict)
                {
                    pair.Value.Checked = (value & pair.Key) == pair.Key;
                }
            }
        }
    }
}