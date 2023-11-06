using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Reflection;
using System.Windows.Forms;
using IsoSDK;
using Microsoft.VisualBasic;
using System.IO;
using System.Globalization;

namespace CSharpUtilitiesSample
{
    public partial class UtilitiesSampleForm : Form
    {
        delegate void SetProgressCallback(object sender, ProcessEventArgs e);
        delegate void OnJobDoneEventCallback(object sender, EventArgs e);
        delegate void OnBurnDoneEventCallback(object sender, BurnDoneEventArgs e);
        delegate void OnStartVerifyEventCallback(object sender, EventArgs e);
        delegate void OnVerifyDoneEventCallback(object sender, VerifyDoneEventArgs e);
        delegate void OnVerifySectorEventCallback(object sender, VerifySectorEventArgs e);


        private Burner m_burner;
        private bool m_bBurnDevicesOnly = true;
        private double m_dImgTotalSize;
        private double m_dDscTotalSize;

        public UtilitiesSampleForm()
        {
            InitializeComponent();
            m_burner = new Burner();
            m_burner.Initialize("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7", ASPIInterface.Internal, true);
            CommonNet.Functions.HandleError(m_burner);
            m_burner.Language = "Default";

            Assembly assem = typeof(UtilitiesSampleForm).Assembly;
            AssemblyName assemName = assem.GetName();
            Text = "IsoSDK " + assemName.Version.Major + "." + assemName.Version.Minor + " CSharpUtilitiesSample";
        }


        private void InterfaceInternalMenuItem_Click(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.Internal);
        }

        private void InterfaceWnAspiMenuItem_Click(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.WnAspi);
        }
        
        private void InterfaceFrogAspiInternalMenuItem_Click(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.FrogAspi);
        }

        private void UpdateDeviceCombo()
        {
            deviceComboBox.Items.Clear();
            string[] devices = m_burner.GetDevices(m_bBurnDevicesOnly);
            CommonNet.Functions.HandleError(m_burner);
            string[] bDevices = m_burner.GetBurnDevices();
            CommonNet.Functions.HandleError(m_burner);

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

            DscUpdateSourceDeviceCombo();
        }

        private void deviceComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            Application.UseWaitCursor = true;
            try
            {
                Application.DoEvents();

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
                    CommonNet.Functions.HandleError(m_burner);
                }

                DscDestDeviceChanged();

                ImgCheckFormat();
                UpdateDriveInfo();
                UpdateDriveInfoEx();
                UpdateCapabilities();
                UpdateMediumInfo();
            }
            finally
            {
                Application.UseWaitCursor = false;
            }
        }

        private void updateInterfaceMenu(ASPIInterface aspiInterface)
        {
            m_burner.SetASPI(aspiInterface);
            CommonNet.Functions.HandleError(m_burner);

            ASPIInterface actualAspi = m_burner.GetASPI();
            CommonNet.Functions.HandleError(m_burner);

            m_burner.RescanDevices();
            CommonNet.Functions.HandleError(m_burner);

            UpdateDeviceCombo();

            internalToolStripMenuItem.Checked = actualAspi == ASPIInterface.Internal;
            wnApsiToolStripMenuItem.Checked = actualAspi == ASPIInterface.WnAspi;
            frogAspiToolStripMenuItem.Checked = actualAspi == ASPIInterface.FrogAspi;
        }

        private void burnDevicesOnlyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_bBurnDevicesOnly = !m_bBurnDevicesOnly;
            UpdateDeviceCombo();
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

        private void isDeviceReadyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (m_burner.IsDeviceReady())
            {
                MessageBox.Show("Device is ready.");
            }
            else
            {
                CommonNet.Functions.HandleError(m_burner);
                MessageBox.Show("Device is not ready.");
            }
        }

        private void ejectTrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.EjectDevice();
            CommonNet.Functions.HandleError(m_burner);
        }

        private void closeTrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.CloseDevice();
            CommonNet.Functions.HandleError(m_burner);
        }

        private void getDriveInfoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.UseWaitCursor = true;
            try
            {
                Application.DoEvents();
                UpdateDriveInfo();
                TabControl.SelectTab(tabPageDriveInfo);
            }
            finally
            {
                Application.UseWaitCursor = false;
            }
        }

        private void UpdateDriveInfo()
        {
            MediumInfo mi = m_burner.GetMediumInfo();

            lblDIDiskType.Text = (mi == null) ? "No medium" : mi.Type;
            if (mi == null)
                return;

            int tmp = m_burner.GetMaxBurnSpeed();
            CommonNet.Functions.HandleError(m_burner);
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
                return;

            lblDIMaxSpeed.Text = tmp.ToString();

            tmp = m_burner.GetMaxReadSpeed();
            CommonNet.Functions.HandleError(m_burner);
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
                return;

            lblDIMaxReadSpeed.Text = tmp.ToString();

            ExtendedDeviceCapabilities caps = m_burner.GetExtendedDeviceCapabilities();
            CommonNet.Functions.HandleError(m_burner);
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
                return;

            if (caps.AnalyseCapability(Capabilities.WriteTest))
            {
                lblDITestWrite.Text = "Supported";
            }
            else
            {
                lblDITestWrite.Text = "Not supported";
            }

            if (caps.AnalyseCapability(Capabilities.UnderrunProtection))
            {
                lblDIUnderrunProtection.Text = "Supported";
            }
            else
            {
                lblDIUnderrunProtection.Text = "Not supported";
            }
        }

        private void getDriveInfoExToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.UseWaitCursor = true;
            try
            {
                Application.DoEvents();
                UpdateDriveInfoEx();
                TabControl.SelectTab(tabPageDriveInfoEx);
            }
            finally
            {
                Application.UseWaitCursor = false;
            }
        }

        private void UpdateDriveInfoEx()
        {
            dataGridDriveInfoEx.Rows.Clear();

            ExtendedDeviceInformation einf = m_burner.GetDeviceInformationEx();
            CommonNet.Functions.HandleError(m_burner);
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
                return;

            if (einf == null)
            {
                return;
            }

            dataGridDriveInfoEx.Rows.Add("Full name of device", ObjOrNullToStr(einf.Name));
            dataGridDriveInfoEx.Rows.Add("Firmware revision", ObjOrNullToStr(einf.Revision));

            string strFirmwareCreationTime = "Unknown";
            if (einf.FirmwareCreationDate > DateTime.MinValue)
                strFirmwareCreationTime = einf.FirmwareCreationDate.ToLocalTime().ToString();
            dataGridDriveInfoEx.Rows.Add("Firmware Creation Date", strFirmwareCreationTime);

            dataGridDriveInfoEx.Rows.Add("Region code set", ObjOrNullToStr(einf.RegionCode));
            dataGridDriveInfoEx.Rows.Add("Region changes left", ObjOrNullToStr(einf.RegionCodeChangesLeft));
            dataGridDriveInfoEx.Rows.Add("Region vendor resets left", ObjOrNullToStr(einf.RegionCodeVendorResetsLeft));
            dataGridDriveInfoEx.Rows.Add("Loader type", ObjOrNullToStr(einf.LoaderType));
            dataGridDriveInfoEx.Rows.Add("Connection interface", ObjOrNullToStr(einf.ConnectionInterface));
            dataGridDriveInfoEx.Rows.Add("Drive interface", ObjOrNullToStr(einf.PhysicalInterface));
            dataGridDriveInfoEx.Rows.Add("Number of volume levels", ObjOrNullToStr(einf.NumberOfVolumeLevels));
            dataGridDriveInfoEx.Rows.Add("Buffer size", ObjOrNullToStr(einf.BufferSize));
            dataGridDriveInfoEx.Rows.Add("Serial number", ObjOrNullToStr(einf.SerialNumber));
            dataGridDriveInfoEx.Rows.Add("Read Retry Count", ObjOrNullToStr(einf.ReadRetryCount));
        }

        private string ObjOrNullToStr(object o)
        {
            return (o == null) ? "" : o.ToString();
        }

        private void setRegionCodeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RegionSelectDialog dlg = new RegionSelectDialog();
            if (DialogResult.OK == dlg.ShowDialog())
            {
                int nCode = dlg.GetRegionalCode();
                if (!m_burner.SetRegionalCode(nCode))
                {
                    CommonNet.Functions.HandleError(m_burner);
                    MessageBox.Show("Regional code wasn't set.");
                }
            }
        }

        private void getCapabilitiesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.UseWaitCursor = true;
            try
            {
                Application.DoEvents();
                UpdateCapabilities();
                TabControl.SelectTab(tabPageDriveCapabilities);

            }
            finally
            {
                Application.UseWaitCursor = false;
            }
        }

        private void UpdateCapabilities()
        {
            //New method of getting capabilities.
            ExtendedDeviceCapabilities exCaps = m_burner.GetExtendedDeviceCapabilities();
            CommonNet.Functions.HandleError(m_burner);
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
                return;

            checkBoxReadCDR.Checked = exCaps.AnalyseCapability(Capabilities.ReadCdR);
            checkBoxReadCDRW.Checked = exCaps.AnalyseCapability(Capabilities.ReadCdRw);
            checkBoxReadDVD.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvd);
            checkBoxReadDVDR.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdR);
            checkBoxReadDVDRW.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdRw);
            checkBoxReadDVDRAM.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdRam);
            checkBoxReadDVDplusR.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdRPlus);
            checkBoxReadDVDplusRW.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdRwPlus);
            checkBoxReadDVDDL.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdDL);
            checkBoxReadDVDMRDL.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdMrDL);
            checkBoxReadBLURAYROM.Checked = exCaps.AnalyseCapability(Capabilities.ReadBlurayRom);
            checkBoxReadBLURAYR.Checked = exCaps.AnalyseCapability(Capabilities.ReadBlurayR);
            checkBoxReadBLURAYRE.Checked = exCaps.AnalyseCapability(Capabilities.ReadBlurayRe);
            chkReadBDRXL.Checked = exCaps.AnalyseCapability(Capabilities.ReadBlurayRXl);
            chkReadBDREXL.Checked = exCaps.AnalyseCapability(Capabilities.ReadBlurayReXl);
            checkBoxReadHDDVDR.Checked = exCaps.AnalyseCapability(Capabilities.ReadHdDvdR);
            checkBoxReadHDDVDRW.Checked = exCaps.AnalyseCapability(Capabilities.ReadHdDvdRw);
            checkBoxReadHDDVDROM.Checked = exCaps.AnalyseCapability(Capabilities.ReadHdDvdRom);
            checkBoxReadMountRainer.Checked = exCaps.AnalyseCapability(Capabilities.ReadMountRainer);
            checkBoxReadCDRWCav.Checked = exCaps.AnalyseCapability(Capabilities.ReadCdRwCav);
            checkBoxReadDVDplusRDL.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdRDLPlus);
            checkBoxReadDVDplusRWDL.Checked = exCaps.AnalyseCapability(Capabilities.ReadDvdRwDLPlus);


            checkBoxWriteCDR.Checked = exCaps.AnalyseCapability(Capabilities.WriteCdR);
            checkBoxWriteCDRW.Checked = exCaps.AnalyseCapability(Capabilities.WriteCdRw);
            checkBoxWriteDVDR.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdR);
            checkBoxWriteDVDRW.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdRw);
            checkBoxWriteDVDRAM.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdRam);
            checkBoxWriteDVDplusR.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdRPlus);
            checkBoxWriteDVDplusRW.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdRwPlus);
            checkBoxWriteDVDDL.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdDL);
            checkBoxWriteDVDMRDL.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdMrDL);
            checkBoxWriteBLURAYR.Checked = exCaps.AnalyseCapability(Capabilities.WriteBlurayR);
            checkBoxWriteBLURAYRE.Checked = exCaps.AnalyseCapability(Capabilities.WriteBlurayRe);
            chkWriteBDRXL.Checked = exCaps.AnalyseCapability(Capabilities.WriteBlurayRXl);
            chkWriteBDREXL.Checked = exCaps.AnalyseCapability(Capabilities.WriteBlurayReXl);
            checkBoxWriteHDDVDR.Checked = exCaps.AnalyseCapability(Capabilities.WriteHdDvdR);
            checkBoxWriteHDDVDRW.Checked = exCaps.AnalyseCapability(Capabilities.WriteHdDvdRw);
            checkBoxWriteMountRainer.Checked = exCaps.AnalyseCapability(Capabilities.WriteMountRainer);
            checkBoxWriteCDRWCav.Checked = exCaps.AnalyseCapability(Capabilities.WriteCdRwCav);
            checkBoxWriteDVDplusRDL.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdRDLPlus);
            checkBoxWriteDVDplusRWDL.Checked = exCaps.AnalyseCapability(Capabilities.WriteDvdRwDLPlus);

            checkBoxCanSimulateWrite.Checked = exCaps.AnalyseCapability(Capabilities.WriteTest);
            checkBoxBufferUnderrunProtection.Checked = exCaps.AnalyseCapability(Capabilities.UnderrunProtection);
            checkBoxSMART.Checked = exCaps.AnalyseCapability(Capabilities.Smart);
            checkBoxMultisession.Checked = exCaps.AnalyseCapability(Capabilities.Multisession);
            checkBoxCPRMAuth.Checked = exCaps.AnalyseCapability(Capabilities.CprmAuth);
            checkBoxDefectManagement.Checked = exCaps.AnalyseCapability(Capabilities.DefectManagement);
            checkBoxStreaming.Checked = exCaps.AnalyseCapability(Capabilities.Streaming);
            checkBoxLayerJumpRecording.Checked = exCaps.AnalyseCapability(Capabilities.LayerJumpRecording);



            checkBoxAudioPlayback.Checked = exCaps.AnalyseCapability(Capabilities.AnalogAudioPlayback);
            checkBoxCompositeAV.Checked = exCaps.AnalyseCapability(Capabilities.CompositeAudioAndVideo);
            checkBoxDP1.Checked = exCaps.AnalyseCapability(Capabilities.DigitalPort1);
            checkBoxDP2.Checked = exCaps.AnalyseCapability(Capabilities.DigitalPort2);
            checkBoxM2F1.Checked = exCaps.AnalyseCapability(Capabilities.Mode2Form1Read);
            checkBoxM2F2.Checked = exCaps.AnalyseCapability(Capabilities.Mode2Form2Read);
            checkBoxCDDAC.Checked = exCaps.AnalyseCapability(Capabilities.CDDA_Commands);
            checkBoxCCDAAS.Checked = exCaps.AnalyseCapability(Capabilities.CDDA_StreamIsAccurate);
            checkBoxRWSCRead.Checked = exCaps.AnalyseCapability(Capabilities.R_W_SubChannelsRead);
            checkBoxRWSCDeint.Checked = exCaps.AnalyseCapability(Capabilities.R_W_SubChannelsDeint);
            checkBoxC2P.Checked = exCaps.AnalyseCapability(Capabilities.C2_Pointers);
            checkBoxISRCRead.Checked = exCaps.AnalyseCapability(Capabilities.ISRC_Read);
            checkBoxUPCRead.Checked = exCaps.AnalyseCapability(Capabilities.UPC_Read);
            checkBoxBarcodeRead.Checked = exCaps.AnalyseCapability(Capabilities.BarcodeRead);
            checkBoxLockingMedia.Checked = exCaps.AnalyseCapability(Capabilities.LockMedia);
            checkBoxLockState.Checked = exCaps.AnalyseCapability(Capabilities.LockState);
            checkBoxSepVolumeLevels.Checked = exCaps.AnalyseCapability(Capabilities.SeparateVolumeLevels);
            checkBoxPreventLockJumper.Checked = exCaps.AnalyseCapability(Capabilities.PreventJumper);
            checkBoxEject.Checked = exCaps.AnalyseCapability(Capabilities.Eject);
            checkBoxSepMute.Checked = exCaps.AnalyseCapability(Capabilities.SeparateChannelMute);
            checkBoxDiscPresent.Checked = exCaps.AnalyseCapability(Capabilities.ChangerDiscPresent);
            checkBoxSSS.Checked = exCaps.AnalyseCapability(Capabilities.ChangerSoftwareSlotSelection);
            checkBoxSideChange.Checked = exCaps.AnalyseCapability(Capabilities.ChangerSideChangeCapable);
            checkBoxRWSCinLI.Checked = exCaps.AnalyseCapability(Capabilities.R_W_SubChannelsInLeadIn);
            checkBoxMethod2.Checked = exCaps.AnalyseCapability(Capabilities.Method2AddressingFixedPackets);
            checkBoxCDTRead.Checked = exCaps.AnalyseCapability(Capabilities.CD_Text_Read);
            checkBoxCDTWrite.Checked = exCaps.AnalyseCapability(Capabilities.CD_Text_Write);
            checkBoxDAO16.Checked = exCaps.AnalyseCapability(Capabilities.DAO_16);
            checkBoxDAO96Pack.Checked = exCaps.AnalyseCapability(Capabilities.DAO_96_Pack);
            checkBoxDAO96Raw.Checked = exCaps.AnalyseCapability(Capabilities.DAO_96_Raw);
            checkBoxDAORaw.Checked = exCaps.AnalyseCapability(Capabilities.DAO_Raw);
            checkBoxPacketWrite.Checked = exCaps.AnalyseCapability(Capabilities.PacketWrite);
            checkBoxLabelFlash.Checked = exCaps.AnalyseCapability(Capabilities.LabelFlash);
            checkBoxLightScribe.Checked = exCaps.AnalyseCapability(Capabilities.LightScribe);
        }

        private string getStrSpace(double nBytes)
        {
            const double BytesInMegaByte = 1024*1024;
            const string strMB = " MB";
            return (Math.Round((nBytes / BytesInMegaByte) * 100.0) / 100.0).ToString() + strMB;
        }

        private void getDiskInfoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.UseWaitCursor = true;
            try
            {
                Application.DoEvents();
                TabControl.SelectTab(tabPageMediumInfo);
                UpdateMediumInfo();
            }
            finally
            {
                Application.UseWaitCursor = false;
            }
        }

        private void UpdateMediumInfo()
        {
            buttonTerminateLastSession.Enabled = false;

            treeViewMediumInfo.Nodes.Clear();

            labelFreeSpace.Text = "...";
            labelLast.Text = "...";
            labelMedium.Text = "...";
            labelSessions.Text = "...";
            labelSize.Text = "...";
            labelStatus.Text = "...";
            labelTracks.Text = "...";
            labelUpcEanCode.Text = "...";
            labelVendorID.Text = "...";
            labelMaxWriteSpeed.Text = "...";
            labelUsedSpace.Text = "...";

            MediumInfo cMI = m_burner.GetMediumInfo();

            if (cMI == null)
            {
                labelMedium.Text = "No Medium";
                return;
            }

            labelMedium.Text = cMI.Type;
            labelUpcEanCode.Text = cMI.UPCEANCode;
            labelVendorID.Text = cMI.VendorID;
            labelSessions.Text = cMI.LastSession.ToString();
            labelTracks.Text = cMI.LastTrack.ToString();

            MediumStatus cMS = cMI.Status;

            if (cMS != MediumStatus.CompleteDisk)
            {
                labelFreeSpace.Text = getStrSpace(cMI.FreeSize);
            }

            labelUsedSpace.Text = getStrSpace(cMI.UsedSize);
            labelSize.Text = getStrSpace(cMI.Size);

            switch (cMS)
            {
                case MediumStatus.CompleteDisk:
                    labelStatus.Text = "Complete Disk";
                    break;
                case MediumStatus.EmptyDisk:
                    labelStatus.Text = "Empty Disk";
                    break;
                case MediumStatus.IncompleteDisk:
                    labelStatus.Text = "Incomplete Disk";
                    break;
                case MediumStatus.Other:
                    labelStatus.Text = "Unknown";
                    break;
            }

            switch (cMI.LastSesionStatus)
            {
                case SessionStatus.CompleteSession:
                    labelLast.Text = "Complete Session";
                    break;
                case SessionStatus.DamagedSession:
                    labelLast.Text = "Damaged Session";
                    buttonTerminateLastSession.Enabled = true;
                    break;
                case SessionStatus.EmptySession:
                    labelLast.Text = "Empty Session";
                    break;
                case SessionStatus.IncompleteSession:
                    labelLast.Text = "Incomplete Session";
                    buttonTerminateLastSession.Enabled = true;
                    break;
            }

            string strMaxWriteSpeed = "Unknown";
            if (cMI.MaxWriteSpeed > 0)
                strMaxWriteSpeed = String.Format("{0}x", cMI.MaxWriteSpeed.ToString("F1", CultureInfo.InvariantCulture));
            labelMaxWriteSpeed.Text = strMaxWriteSpeed;

            string strExtType = "";

            switch (cMI.ExtendedType)
            {
                case ExtendedMediumType.CdAudio:
                    strExtType = "Audio CD";
                    break;
                case ExtendedMediumType.CdEnhanced:
                    strExtType = "Enhanced CD";
                    break;
                case ExtendedMediumType.CdMixedMode:
                    strExtType = "Mixed Mode CD";
                    break;
                case ExtendedMediumType.CdMultisession:
                    strExtType = "Multisession CD";
                    break;
                case ExtendedMediumType.CdRom:
                    strExtType = "CD-ROM";
                    break;
                case ExtendedMediumType.CdRomXA:
                    strExtType = "CD-ROM XA";
                    break;
                case ExtendedMediumType.Dvd:
                    strExtType = "DVD";
                    break;
                case ExtendedMediumType.Bd:
                    strExtType = "BD";
                    break;
                case ExtendedMediumType.HdDvd:
                    strExtType = "HDDVD";
                    break;
            }

            TreeNode root = treeViewMediumInfo.Nodes.Add(strExtType);

            if (!(cMI.FirstSession > 0 && cMI.LastSession > 0))
            {
                return;
            }

            for (int i = cMI.FirstSession; i <= cMI.LastSession; ++i)
            {
                SessionInfo si;
                si = m_burner.GetSessionInfo(i);
                CommonNet.Functions.HandleError(m_burner);

                string strTmp;
                strTmp = "Session " + i.ToString() + " (" + getStrSpace(si.Size * 2048.0) + ")";

                TreeNode sessNode;
                sessNode = new TreeNode(strTmp);

                for (int j = si.FirstTrack; j <= si.LastTrack; ++j)
                {
                    TrackInfo ti;
                    ti = m_burner.GetTrackInfo(j);
                    CommonNet.Functions.HandleError(m_burner);

                    string strTrack = "";
                    strTrack = "Track " + j.ToString() + " LBA: " + ti.StartLBA.ToString();
                    strTrack = strTrack + " (" + getStrSpace(ti.Size * 2048) + ")";

                    string strTrackFormat = "";
                    switch (ti.Format)
                    {
                        case TrackFormat.Audio:
                            strTrackFormat = "Audio";
                            break;
                        case TrackFormat.DataMode1:
                            strTrackFormat = "mode 1";
                            break;
                        case TrackFormat.DataMode2:
                            strTrackFormat = "mode 2";
                            break;
                    }

                    string strFileSys = "";

                    if (ti.Format != TrackFormat.Audio)
                    {
                        if ((long)(ti.FileSystem & FileSystems.Iso9660) != 0)
                        {
                            strFileSys = "ISO 9660";
                            if ((long)(ti.FileSystem & FileSystems.Joliet) != 0)
                            {
                                strFileSys += "/Joliet";
                            }
                        }
                        if ((long)(ti.FileSystem & FileSystems.Udf) != 0)
                        {
                            strFileSys += (strFileSys.Length == 0 ? "" : "/") + "UDF";
                        }

                        if ((long)(ti.FileSystem & FileSystems.Bootable) != 0)
                        {
                            strFileSys += "/bootable";
                        }
                    }


                    strTrack += " " + strFileSys + " " + strTrackFormat;

                    sessNode.Nodes.Add(strTrack);

                }

                root.Nodes.Add(sessNode);
            }

            root.ExpandAll();
        }

        private void buttonTerminateLastSession_Click(object sender, EventArgs e)
        {
            if (!m_burner.CloseSession())
            {
                CommonNet.Functions.HandleError(m_burner);
                MessageBox.Show("Closing session wasn't done!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void eraseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CommonNet.Erase.EraseDeveloped(m_burner);
        }

        private void rescanDevicesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.RescanDevices();
            CommonNet.Functions.HandleError(m_burner);

            UpdateDeviceCombo();
        }

        private void disableImagewriterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.ImageDeviceEnabled = !disableImagewriterToolStripMenuItem.Checked;
            CommonNet.Functions.HandleError(m_burner);

            UpdateDeviceCombo();
        }

        private void mountImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (disableImagewriterToolStripMenuItem.Checked)
            {
                disableImagewriterToolStripMenuItem.Checked = false;
            }
            deviceComboBox.SelectedIndex = 0;

            OpenFileDialog ofn = new OpenFileDialog();
            ofn.CheckFileExists = true;
            ofn.CheckPathExists = true;
            ofn.Title = "Select image to mount, please...";
            ofn.Multiselect = false;
            string strFilter = "ISO files|*.iso|BIN files|*.bin|NRG files|*.nrg|CDI files|*.cdi|MDF files|*.mdf|CCD files|*.ccd|IMG files|*.img|GI files|*.gi|PDI files|*.pdi|DMG files|*.dmg|B5I files|*.b5i|B6I files|*.b6i)";            
            ofn.Filter =  strFilter;

            if (ofn.ShowDialog() == DialogResult.OK)
            {
                string strFileName = ofn.FileName;
                m_burner.SetImageFilePath(strFileName);
                CommonNet.Functions.HandleError(m_burner);

                ImgCheckFormat();
            }
        }

        private void unmountImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_burner.SetImageFilePath("");
            CommonNet.Functions.HandleError(m_burner);

            ImgCheckFormat();
        }

        private void checkBoxImgBadList_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxImgBadList.Checked)
            {
                textBoxImgBadListPath.Enabled = true;
            }
            else
            {
                textBoxImgBadListPath.Enabled = false;
            }
        }

        private void buttonImgBrowse_Click(object sender, EventArgs e)
        {   
            String strFormat = comboBoxImgFormat.Text;

            String strSaveParam = String.Format("{0:S} files (*.{0:S} )|*.{0:S}", strFormat);

            saveFileDialogImgDest.Filter = strSaveParam;

            if (saveFileDialogImgDest.ShowDialog() == DialogResult.OK)            
            {
                textBoxImgDestPath.Text = saveFileDialogImgDest.FileName;
            }
        }

        private void buttonImgCheckFormat_Click(object sender, EventArgs e)
        {
            ImgCheckFormat();
        }

        private void ImgUpdateReadDevice()
        {
            m_burner.ReadDevice = m_burner.BurnDevice;
            CommonNet.Functions.HandleError(m_burner);
        }

        private void ImgCheckFormat()
        {
            ImgUpdateReadDevice();

            ExtendedDeviceInformation sDeviceInfo = m_burner.GetDeviceInformationEx((int)DeviceIndex.Read); //Read Device
            CommonNet.Functions.HandleError(m_burner);

            numericUpDownImgHardwareCount.Value = Convert.ToDecimal(sDeviceInfo.ReadRetryCount);

            ImageFormat cFormats = m_burner.GetPossibleImageFormats();
            CommonNet.Functions.HandleError(m_burner);

            comboBoxImgFormat.Items.Clear();

            if ((cFormats & ImageFormat.Iso) == ImageFormat.Iso)
	        {
                comboBoxImgFormat.Items.Add("ISO");
	        }

            if ((cFormats & ImageFormat.Bin) == ImageFormat.Bin)
	        {
                comboBoxImgFormat.Items.Add("BIN");
	        }

            if (comboBoxImgFormat.Items.Count == 0)
	        {
                comboBoxImgFormat.Enabled = false;
                buttonImgBrowse.Enabled = false;
                buttonImgExecute.Enabled = false;
	        }
	        else
	        {
                comboBoxImgFormat.Enabled = true;
                buttonImgBrowse.Enabled = true;
                buttonImgExecute.Enabled = true;

                comboBoxImgFormat.SelectedIndex = 0;
	        }
        }

        private void ImgEnableControls(bool bEnable)
        {
            buttonImgCancel.Enabled = !bEnable;
            buttonImgBrowse.Enabled = bEnable;
            comboBoxImgFormat.Enabled = bEnable;
            buttonImgCheckFormat.Enabled = bEnable;
            checkBoxImgCreate.Enabled = bEnable;
            checkBoxImgVerify.Enabled = bEnable;
            buttonImgExecute.Enabled = bEnable;
            textBoxImgDestPath.Enabled = bEnable;
            groupBoxImgCorrectionSettings.Enabled = bEnable;
        }

        private void buttonImgCancel_Click(object sender, EventArgs e)
        {
            bool bRes = m_burner.Abort();

            ImgEnableControls(true);
        }

        private void buttonImgExecute_Click(object sender, EventArgs e)
        {

            //Speed[] aReadSpeeds = m_burner.GetPossibleReadSpeeds();
            //m_burner.SetReadSpeed((int)DeviceIndex.Current, 706);
            //CommonNet.Functions.HandleError(m_burner);


            m_dImgTotalSize = 0;

            String strDest = textBoxImgDestPath.Text;
	        
	        if (strDest == "")
	        {
		        MessageBox.Show("Destination file is not specified.");
		        return;
	        }

	        String strBadSectorsLogPath = textBoxImgBadListPath.Text;	        
	        String strFormat = comboBoxImgFormat.Text;
	        
	        ImageFormat nFormat;
        	
	        if (strFormat == "ISO")
	        {
		        nFormat = ImageFormat.Iso;

                if (strDest.Substring(strDest.Length - 3, 3).ToLower().CompareTo("iso") != 0)
                {
                    strDest += ".iso";
                }
	        }
	        else if (strFormat == "BIN")
	        {
                nFormat = ImageFormat.Bin;

                if (strDest.Substring(strDest.Length - 3, 3).ToLower().CompareTo("bin") != 0)
                {
                    strDest += ".bin";
                }
	        }
	        else
	        {
                return;
	        }

            textBoxImgDestPath.Text = strDest;

            if (checkBoxImgCreate.Checked && File.Exists(strDest))
            {
                if (DialogResult.No == MessageBox.Show("Destination file exists. Do you want to replace it?", "UtilitiesSample", MessageBoxButtons.YesNo))
                    return;
            }

	        CreateImageParams cCreateImageParams = new CreateImageParams();
            cCreateImageParams.ErrorParams = new ReadErrorCorrectionParams();
	        cCreateImageParams.ErrorParams.ErrorCorrection = checkBoxImgReadErrCorrection.Checked;
	        cCreateImageParams.ErrorParams.BlankBadSectors = checkBoxImgBlankBad.Checked;
	        
            cCreateImageParams.BadSectorsFilePath = textBoxImgBadListPath.Text;
	        cCreateImageParams.ImagePath = strDest;
            cCreateImageParams.FullCapacity = true;
            cCreateImageParams.VerifyBufferSectors = 8;
	        cCreateImageParams.ImageType = nFormat;
	        cCreateImageParams.ErrorParams.HardwareRetryCount = Convert.ToInt32(numericUpDownImgHardwareCount.Value);
	        cCreateImageParams.ErrorParams.SoftwareRetryCount = Convert.ToInt32(numericUpDownImgSoftwareCount.Value);

            ImageTask task = 0;

            if (checkBoxImgCreate.Checked)
	        {
		        task = ImageTask.Create;
	        }

	        if (checkBoxImgVerify.Checked)
	        {
		        task |= ImageTask.Verify;
	        }

	        if (task == 0)
            {
		        MessageBox.Show("Operation is not specified.");
		        return;
	        }

	        // Start image creation
            bool bRes = m_burner.CreateImage(cCreateImageParams, task);
            CommonNet.Functions.HandleError(m_burner);

	        if (bRes)
	        {
		        ImgEnableControls(false);
                lblStatus.Text = "Status: Create";
                m_burner.BurnDoneEvent += new Burner.BurnDoneEventHandler(OnImgBurnDoneEvent);
                m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnImgJobDoneEvent);
                m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnImgProcessEvent);
                m_burner.StartVerifyEvent+= new Burner.StartVerifyEventHandler(OnImgVerifyStartEvent);
                m_burner.VerifyDoneEvent += new Burner.VerifyDoneEventHandler(OnImgVerifyDoneEvent);
                m_burner.VerifySectorEvent += new Burner.VerifySectorEventHandler(OnImgVerifySectorEvent);
                
            }
        }

        private void checkBoxImgReadErrCorrection_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxImgReadErrCorrection.Checked)
            {
                numericUpDownImgHardwareCount.Enabled = true;
                numericUpDownImgSoftwareCount.Enabled = true;
            }
            else
            {
                numericUpDownImgHardwareCount.Enabled = false;
                numericUpDownImgSoftwareCount.Enabled = false;
            }
        }

        private void OnImgProcessEvent(object sender, ProcessEventArgs e)
        {
            if (progressBarImg.InvokeRequired)
            {
                SetProgressCallback d = new SetProgressCallback(OnImgProcessEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                ImgSetProgress(e.m_fPercent, e.m_fDeviceBuffer, e.m_dImageSize, e.m_dBytesWritten);
            }
        }

        private void ImgSetProgress(float fBurnPercent, float fBuffer, double dImageSize, double dBytesWritten)
        {  
            progressBarImg.Value = Convert.ToInt32(fBurnPercent);

            labelImgPercentage.Text = String.Format("Percentage : {0:D}%", Convert.ToInt32(fBurnPercent));

            if (m_dImgTotalSize == 0 || m_dImgTotalSize != dImageSize)
            {
                m_dImgTotalSize = dImageSize;
                labelImgTtlSec.Text = String.Format("Total Sectors : {0:D}", Convert.ToInt64(dImageSize));
            }

            labelImgCurSec.Text = String.Format("Current Sector : {0:D}", Convert.ToInt64(dBytesWritten));

            labelImgReadErr.Text = String.Format("Errors : {0:D}", Convert.ToInt32(System.Math.Ceiling(fBuffer * 1000)));
        }

        private void OnImgBurnDoneEvent(object sender, BurnDoneEventArgs e)
        {
            if (e.m_strError.Length > 0)
            {
                if (checkBoxImgCreate.InvokeRequired)
                {
                    OnBurnDoneEventCallback d = new OnBurnDoneEventCallback(OnImgBurnDoneEvent);
                    this.Invoke(d, new object[] { sender, e });
                }
                else
                {
                    MessageBox.Show(e.m_strError);
                }
            }
        }

        private void OnImgVerifyDoneEvent(object sender, VerifyDoneEventArgs e)
        {

            if (lblStatus.InvokeRequired)
            {
                OnVerifyDoneEventCallback d = new OnVerifyDoneEventCallback(OnImgVerifyDoneEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                lblStatus.Text = "Status: Verify done";
                if (e.m_nNumErrors > 0)
                {
                    String strError = String.Format("Verify done with {0:D} errors", e.m_nNumErrors);
                    MessageBox.Show(strError);
                }

            }

        }

        private void OnImgVerifySectorEvent(object sender, VerifySectorEventArgs e)
        {
           
            if (lblVerifySector.InvokeRequired)
            {
                OnVerifySectorEventCallback d = new OnVerifySectorEventCallback(OnImgVerifySectorEvent);
                this.Invoke(d, new object[] { sender, e});
            }
            else
            {
                lblVerifySector.Text = String.Format("Sector : {0:D} / {1:D}", Convert.ToInt64(e.nSector), Convert.ToInt64(e.tSector));
            }
           
        }

        private void OnImgVerifyStartEvent(object sender, EventArgs e)
        {

            if (lblStatus.InvokeRequired)
            {
                OnStartVerifyEventCallback d = new OnStartVerifyEventCallback(OnImgVerifyStartEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                lblStatus.Text = "Status: Verify";
            }

        }

        private void OnImgJobDoneEvent(object sender, EventArgs e)
        {
            if (progressBarImg.InvokeRequired)
            {
                OnJobDoneEventCallback d = new OnJobDoneEventCallback(OnImgJobDoneEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                ImgEnableControls(true);

                progressBarImg.Value = 0;
                labelImgPercentage.Text = "Percentage :";
                labelImgTtlSec.Text = "Total Sectors :";
                labelImgCurSec.Text = "Current Sector :";
                labelImgReadErr.Text = "Errors :";

                m_burner.BurnDoneEvent -= new Burner.BurnDoneEventHandler(OnImgBurnDoneEvent);
                m_burner.JobDoneEvent -= new Burner.JobDoneEventHandler(OnImgJobDoneEvent);
                m_burner.ProcessEvent -= new Burner.ProcessEventHandler(OnImgProcessEvent);
                m_burner.StartVerifyEvent -= new Burner.StartVerifyEventHandler(OnImgVerifyStartEvent);
                m_burner.VerifyDoneEvent -= new Burner.VerifyDoneEventHandler(OnImgVerifyDoneEvent);
                m_burner.VerifySectorEvent -= new Burner.VerifySectorEventHandler(OnImgVerifySectorEvent);
            }
        }

        private void checkBoxDscReadErrCorrection_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxDscReadErrCorrection.Checked)
            {
                numericUpDownDscHardwareCount.Enabled = true;
                numericUpDownDscSoftwareCount.Enabled = true;
            }
            else
            {
                numericUpDownDscHardwareCount.Enabled = false;
                numericUpDownDscSoftwareCount.Enabled = false;
            }
        }

        private void buttonDscCancel_Click(object sender, EventArgs e)
        {
            bool bRes = m_burner.Abort();            
        }

        private void OnDscProcessEvent(object sender, ProcessEventArgs e)
        {
            if (progressBarDsc.InvokeRequired)
            {
                SetProgressCallback d = new SetProgressCallback(OnDscProcessEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                DscSetProgress(e.m_fPercent, e.m_fDeviceBuffer, e.m_dImageSize, e.m_dBytesWritten);
            }
            
        }

        private void DscSetProgress(float fBurnPercent, float fBuffer, double dImageSize, double dBytesWritten)
        {
            progressBarDsc.Value = Convert.ToInt32(fBurnPercent);

            labelDscPercentage.Text = String.Format("Percentage : {0:D}%", Convert.ToInt32(fBurnPercent));

            if (m_dDscTotalSize == 0 || m_dDscTotalSize != dImageSize)
            {
                m_dDscTotalSize = dImageSize;
                labelDscTtlBytes.Text = String.Format("Total Bytes : {0:D}", Convert.ToInt64(dImageSize));
            }

            labelDscBytesWritten.Text = String.Format("Bytes Written : {0:D}", Convert.ToInt64(dBytesWritten));
        }

        private void OnDscBurnDoneEvent(object sender, BurnDoneEventArgs e)
        {
            if (e.m_strError.Length > 0)
            {
                if (checkBoxDscVerify.InvokeRequired)
                {
                    OnBurnDoneEventCallback d = new OnBurnDoneEventCallback(OnDscBurnDoneEvent);
                    this.Invoke(d, new object[] { sender, e });
                }
                else
                {
                    MessageBox.Show(e.m_strError);
                }
            }
        }

        private void OnDscVerifyDoneEvent(object sender, VerifyDoneEventArgs e)
        {

            if (lblDscStatus.InvokeRequired)
            {
                OnVerifyDoneEventCallback d = new OnVerifyDoneEventCallback(OnDscVerifyDoneEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                lblDscStatus.Text = "Status: Verify done";
                if(e.m_nNumErrors>0)
                {
                    String strError= String.Format("Verify done with {0:D} errors", e.m_nNumErrors);
                    MessageBox.Show(strError);
                }
            }

        }

        private void OnDscVerifyStartEvent(object sender, EventArgs e)
        {

            if (lblDscStatus.InvokeRequired)
            {
                OnStartVerifyEventCallback d = new OnStartVerifyEventCallback(OnDscVerifyStartEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                lblDscStatus.Text = "Status: Verify";
            }

        }

        private void OnDscVerifySectorEvent(object sender, VerifySectorEventArgs e)
        {

            if (lblVerifySector.InvokeRequired)
            {
                OnVerifySectorEventCallback d = new OnVerifySectorEventCallback(OnDscVerifySectorEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                lblSectors.Text = String.Format("Sector : {0:D} / {1:D}", Convert.ToInt64(e.nSector), Convert.ToInt64(e.tSector));
            }

        }
        

        private void OnDscJobDoneEvent(object sender, EventArgs e)
        {
            if (progressBarDsc.InvokeRequired)
            {
                OnJobDoneEventCallback d = new OnJobDoneEventCallback(OnDscJobDoneEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                DscEnableControls(true);

                progressBarDsc.Value = 0;
                labelDscPercentage.Text = "Percentage :";
                labelDscTtlBytes.Text = "Total Bytes :";
                labelDscBytesWritten.Text = "Bytes Written :";

                m_burner.BurnDoneEvent -= new Burner.BurnDoneEventHandler(OnDscBurnDoneEvent);
                m_burner.JobDoneEvent -= new Burner.JobDoneEventHandler(OnDscJobDoneEvent);
                m_burner.ProcessEvent -= new Burner.ProcessEventHandler(OnDscProcessEvent);
                m_burner.StartVerifyEvent -= new Burner.StartVerifyEventHandler(OnDscVerifyStartEvent);
                m_burner.VerifyDoneEvent -= new Burner.VerifyDoneEventHandler(OnDscVerifyDoneEvent);
                m_burner.VerifySectorEvent -= new Burner.VerifySectorEventHandler(OnDscVerifySectorEvent);


            }

        }

        private void buttonDscCopy_Click(object sender, EventArgs e)
        {
            m_dDscTotalSize = 0;

	        DiskCopyOptions cDiskCopyOptions = new DiskCopyOptions();
            cDiskCopyOptions.VerifyAfterBurn = checkBoxDscVerify.Checked;
            cDiskCopyOptions.EjectAfterBurn = checkBoxDscEject.Checked;
			cDiskCopyOptions.FullCapacity = true;
            cDiskCopyOptions.VerifyBufferSectors = 8;

            String strMode = comboBoxDscReadMode.Text;

	        if (strMode == "ISO")
	        {
                cDiskCopyOptions.ReadMode = ReadMode.Iso;
	        }
	        else if (strMode == "RAW")
	        {
                cDiskCopyOptions.ReadMode = ReadMode.Raw;
	        }
	        else if (strMode == "RAW+SubCh")
	        {
                cDiskCopyOptions.ReadMode = ReadMode.RawSubchannel;
	        }else
	        {
		        MessageBox.Show("Please, specify read mode.");
		        return;
	        }

            String strWrMethod = comboBoxDscWriteMethod.Text;
	        
	        if (strWrMethod == "DAO")
	        {
                cDiskCopyOptions.WriteMethod = WriteMethod.DiskAtOnce;
	        }
	        else if (strWrMethod == "DAO96")
	        {
                cDiskCopyOptions.WriteMethod = WriteMethod.DiskAtOnce96;
	        }
	        else
	        {
                MessageBox.Show("Please, specify write method.");
		        return;
	        }
        	
	        ReadErrorCorrectionParams cCorrectionParams = new ReadErrorCorrectionParams();            
            cCorrectionParams.ErrorCorrection = checkBoxDscReadErrCorrection.Checked;
            cCorrectionParams.HardwareRetryCount = Convert.ToInt32(numericUpDownDscHardwareCount.Value);
            cCorrectionParams.SoftwareRetryCount = Convert.ToInt32(numericUpDownDscSoftwareCount.Value);
	        cDiskCopyOptions.ErrorParams = cCorrectionParams;

            String strSourceDevice = comboBoxDscSourceDev.Text;

	        String strBurnDevice = m_burner.BurnDevice;
            CommonNet.Functions.HandleError(m_burner);

            if (strBurnDevice == strSourceDevice) 
	        {
		        MessageBox.Show("Source and Destination devices cannot be the same.");
		        return;
	        }

	        m_burner.ReadDevice = strSourceDevice;
            CommonNet.Functions.HandleError(m_burner);

            m_burner.Options.AutoErase = checkBoxDscAutoErase.Checked;
	        
	        bool bRes = m_burner.CopyDisk(cDiskCopyOptions);
            CommonNet.Functions.HandleError(m_burner);

	        if (bRes)
	        {
		        DscEnableControls(false);

                lblDscStatus.Text = "Status: Copy";

                m_burner.BurnDoneEvent += new Burner.BurnDoneEventHandler(OnDscBurnDoneEvent);
                m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnDscJobDoneEvent);
                m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnDscProcessEvent);
                m_burner.StartVerifyEvent += new Burner.StartVerifyEventHandler(OnDscVerifyStartEvent);
                m_burner.VerifyDoneEvent += new Burner.VerifyDoneEventHandler(OnDscVerifyDoneEvent);
                m_burner.VerifySectorEvent += new Burner.VerifySectorEventHandler(OnDscVerifySectorEvent);
            }
        }

        private void DscEnableControls(bool bEnable)
        {
            buttonDscCancel.Enabled = !bEnable;
            comboBoxDscSourceDev.Enabled = bEnable;
            groupBoxDscCorrectionSettings.Enabled = bEnable;
            comboBoxDscWriteMethod.Enabled = bEnable;
            comboBoxDscReadMode.Enabled = bEnable;
            checkBoxDscVerify.Enabled = bEnable;
            checkBoxDscEject.Enabled = bEnable;
            buttonDscCopy.Enabled = bEnable;
        }

        private void comboBoxDscSourceDev_SelectedIndexChanged(object sender, EventArgs e)
        {
            String strSourceDevice = comboBoxDscSourceDev.Text;

	        m_burner.ReadDevice = strSourceDevice;
            CommonNet.Functions.HandleError(m_burner);
	        
            comboBoxDscReadMode.Items.Clear();
            comboBoxDscReadMode.Items.Add("ISO");

            MediumInfo cMediumInfo = m_burner.GetMediumInfo((int)DeviceIndex.Read);
            CommonNet.Functions.HandleError(m_burner);

            if (cMediumInfo.TypeCode == MediumType.CdRom ||
                cMediumInfo.TypeCode == MediumType.CdR ||
                cMediumInfo.TypeCode == MediumType.CdRw)
	        {
		        comboBoxDscReadMode.Items.Add("RAW");
		        comboBoxDscReadMode.Items.Add("RAW+SubCh");
	        }
        	
            comboBoxDscReadMode.SelectedIndex = 0;

            ExtendedDeviceInformation sDeviceInfo = m_burner.GetDeviceInformationEx((int)DeviceIndex.Read);
            CommonNet.Functions.HandleError(m_burner);

            numericUpDownDscHardwareCount.Value = Convert.ToDecimal(sDeviceInfo.ReadRetryCount);
        }

        private void DscDestDeviceChanged()
        {
            comboBoxDscWriteMethod.Items.Clear();
        	
	        comboBoxDscWriteMethod.Items.Add("DAO");

	        MediumInfo cMediumInfo = m_burner.GetMediumInfo();
            if (cMediumInfo == null)
                return;

            if (cMediumInfo.TypeCode == MediumType.CdRom ||
                cMediumInfo.TypeCode == MediumType.CdR ||
                cMediumInfo.TypeCode == MediumType.CdRw)
	        {
                comboBoxDscWriteMethod.Items.Add("DAO96");
	        }

            comboBoxDscWriteMethod.SelectedIndex = 0;
        }

        private void DscUpdateSourceDeviceCombo()
        {
            comboBoxDscSourceDev.Items.Clear();

            string[] devices = m_burner.GetDevices(m_bBurnDevicesOnly);
            CommonNet.Functions.HandleError(m_burner);

            string strCurrentDevice = m_burner.ReadDevice;
            CommonNet.Functions.HandleError(m_burner);

            for (int i = 0; i < devices.Length; ++i)
            {
                comboBoxDscSourceDev.Items.Add(devices[i]);
                if (String.Compare(strCurrentDevice, 0, devices[i], 0, 2) == 0)
                {
                    comboBoxDscSourceDev.SelectedIndex = i;
                }
            }
            
            if (strCurrentDevice.Contains("\t"))
            {
                comboBoxDscSourceDev.SelectedIndex = devices.Length;
            }
        }

        private void UtilitiesSampleForm_Load(object sender, EventArgs e)
        {
            updateInterfaceMenu(ASPIInterface.Internal);
            ImgCheckFormat();
        }

        private void tabPageDiscCopy_Enter(object sender, EventArgs e)
        {
            DscUpdateSourceDeviceCombo();
        }
    }
}