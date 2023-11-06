namespace CSharpUtilitiesSample
{
    partial class UtilitiesSampleForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UtilitiesSampleForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deviceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.isDeviceReadyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ejectTrayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeTrayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.getDriveInfoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getDriveInfoExToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getCapabilitiesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.setRegionCodeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imagesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mountImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.unmountImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mediumToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getDiskInfoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eraseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aSPISPTIToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.interfaceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.internalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.wnApsiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.frogAspiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rescanDevicesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.burnDevicesOnlyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.disableImagewriterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.informationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.webToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.deviceComboBox = new System.Windows.Forms.ComboBox();
            this.TabControl = new System.Windows.Forms.TabControl();
            this.tabPageDriveInfo = new System.Windows.Forms.TabPage();
            this.lblDITestWrite = new System.Windows.Forms.Label();
            this.lblDIUnderrunProtection = new System.Windows.Forms.Label();
            this.lblDIMaxReadSpeed = new System.Windows.Forms.Label();
            this.lblDIMaxSpeed = new System.Windows.Forms.Label();
            this.lblDIDiskType = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tabPageDriveInfoEx = new System.Windows.Forms.TabPage();
            this.dataGridDriveInfoEx = new System.Windows.Forms.DataGridView();
            this.ColumnParameter = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tabPageDriveCapabilities = new System.Windows.Forms.TabPage();
            this.groupBoxDriveCaps = new System.Windows.Forms.GroupBox();
            this.checkBoxCCDAAS = new System.Windows.Forms.CheckBox();
            this.chkWriteBDREXL = new System.Windows.Forms.CheckBox();
            this.chkWriteBDRXL = new System.Windows.Forms.CheckBox();
            this.chkReadBDREXL = new System.Windows.Forms.CheckBox();
            this.chkReadBDRXL = new System.Windows.Forms.CheckBox();
            this.checkBoxLightScribe = new System.Windows.Forms.CheckBox();
            this.checkBoxLabelFlash = new System.Windows.Forms.CheckBox();
            this.checkBoxPacketWrite = new System.Windows.Forms.CheckBox();
            this.checkBoxDAO96Raw = new System.Windows.Forms.CheckBox();
            this.checkBoxDAO96Pack = new System.Windows.Forms.CheckBox();
            this.checkBoxDAO16 = new System.Windows.Forms.CheckBox();
            this.checkBoxDAORaw = new System.Windows.Forms.CheckBox();
            this.checkBoxCDTWrite = new System.Windows.Forms.CheckBox();
            this.checkBoxCDTRead = new System.Windows.Forms.CheckBox();
            this.checkBoxMethod2 = new System.Windows.Forms.CheckBox();
            this.checkBoxRWSCinLI = new System.Windows.Forms.CheckBox();
            this.checkBoxSideChange = new System.Windows.Forms.CheckBox();
            this.checkBoxSSS = new System.Windows.Forms.CheckBox();
            this.checkBoxDiscPresent = new System.Windows.Forms.CheckBox();
            this.checkBoxSepMute = new System.Windows.Forms.CheckBox();
            this.checkBoxEject = new System.Windows.Forms.CheckBox();
            this.checkBoxPreventLockJumper = new System.Windows.Forms.CheckBox();
            this.checkBoxSepVolumeLevels = new System.Windows.Forms.CheckBox();
            this.checkBoxLockState = new System.Windows.Forms.CheckBox();
            this.checkBoxLockingMedia = new System.Windows.Forms.CheckBox();
            this.checkBoxBarcodeRead = new System.Windows.Forms.CheckBox();
            this.checkBoxUPCRead = new System.Windows.Forms.CheckBox();
            this.checkBoxISRCRead = new System.Windows.Forms.CheckBox();
            this.checkBoxC2P = new System.Windows.Forms.CheckBox();
            this.checkBoxRWSCDeint = new System.Windows.Forms.CheckBox();
            this.checkBoxRWSCRead = new System.Windows.Forms.CheckBox();
            this.checkBoxCDDAC = new System.Windows.Forms.CheckBox();
            this.checkBoxM2F2 = new System.Windows.Forms.CheckBox();
            this.checkBoxM2F1 = new System.Windows.Forms.CheckBox();
            this.checkBoxDP2 = new System.Windows.Forms.CheckBox();
            this.checkBoxDP1 = new System.Windows.Forms.CheckBox();
            this.checkBoxCompositeAV = new System.Windows.Forms.CheckBox();
            this.checkBoxAudioPlayback = new System.Windows.Forms.CheckBox();
            this.checkBoxLayerJumpRecording = new System.Windows.Forms.CheckBox();
            this.checkBoxDefectManagement = new System.Windows.Forms.CheckBox();
            this.checkBoxBufferUnderrunProtection = new System.Windows.Forms.CheckBox();
            this.checkBoxSMART = new System.Windows.Forms.CheckBox();
            this.checkBoxStreaming = new System.Windows.Forms.CheckBox();
            this.checkBoxMultisession = new System.Windows.Forms.CheckBox();
            this.checkBoxCPRMAuth = new System.Windows.Forms.CheckBox();
            this.checkBoxCanSimulateWrite = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteCDRWCav = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteMountRainer = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDplusRWDL = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDplusRDL = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteHDDVDRW = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteHDDVDR = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteBLURAYRE = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteBLURAYR = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDMRDL = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDDL = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDplusRW = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDplusR = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDRAM = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDRW = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteDVDR = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteCDRW = new System.Windows.Forms.CheckBox();
            this.checkBoxWriteCDR = new System.Windows.Forms.CheckBox();
            this.checkBoxReadCDRWCav = new System.Windows.Forms.CheckBox();
            this.checkBoxReadMountRainer = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDplusRWDL = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDplusRDL = new System.Windows.Forms.CheckBox();
            this.checkBoxReadHDDVDROM = new System.Windows.Forms.CheckBox();
            this.checkBoxReadHDDVDRW = new System.Windows.Forms.CheckBox();
            this.checkBoxReadHDDVDR = new System.Windows.Forms.CheckBox();
            this.checkBoxReadBLURAYROM = new System.Windows.Forms.CheckBox();
            this.checkBoxReadBLURAYRE = new System.Windows.Forms.CheckBox();
            this.checkBoxReadBLURAYR = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDMRDL = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDDL = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDplusRW = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDplusR = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDRAM = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDRW = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVDR = new System.Windows.Forms.CheckBox();
            this.checkBoxReadDVD = new System.Windows.Forms.CheckBox();
            this.checkBoxReadCDRW = new System.Windows.Forms.CheckBox();
            this.checkBoxReadCDR = new System.Windows.Forms.CheckBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.tabPageMediumInfo = new System.Windows.Forms.TabPage();
            this.labelMaxWriteSpeed = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.labelVendorID = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.treeViewMediumInfo = new System.Windows.Forms.TreeView();
            this.buttonEject = new System.Windows.Forms.Button();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.buttonTerminateLastSession = new System.Windows.Forms.Button();
            this.labelUpcEanCode = new System.Windows.Forms.Label();
            this.labelFreeSpace = new System.Windows.Forms.Label();
            this.labelUsedSpace = new System.Windows.Forms.Label();
            this.labelSize = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.labelTracks = new System.Windows.Forms.Label();
            this.labelSessions = new System.Windows.Forms.Label();
            this.labelLast = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.labelMedium = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.tabPageImgCreation = new System.Windows.Forms.TabPage();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonImgCheckFormat = new System.Windows.Forms.Button();
            this.comboBoxImgFormat = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonImgExecute = new System.Windows.Forms.Button();
            this.checkBoxImgCreate = new System.Windows.Forms.CheckBox();
            this.checkBoxImgVerify = new System.Windows.Forms.CheckBox();
            this.groupBoxProcessInfo = new System.Windows.Forms.GroupBox();
            this.lblVerifySector = new System.Windows.Forms.Label();
            this.lblStatus = new System.Windows.Forms.Label();
            this.progressBarImg = new System.Windows.Forms.ProgressBar();
            this.buttonImgCancel = new System.Windows.Forms.Button();
            this.labelImgPercentage = new System.Windows.Forms.Label();
            this.labelImgReadErr = new System.Windows.Forms.Label();
            this.labelImgCurSec = new System.Windows.Forms.Label();
            this.labelImgTtlSec = new System.Windows.Forms.Label();
            this.groupBoxImgCorrectionSettings = new System.Windows.Forms.GroupBox();
            this.textBoxImgBadListPath = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.checkBoxImgBadList = new System.Windows.Forms.CheckBox();
            this.checkBoxImgBlankBad = new System.Windows.Forms.CheckBox();
            this.numericUpDownImgSoftwareCount = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownImgHardwareCount = new System.Windows.Forms.NumericUpDown();
            this.label18 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.checkBoxImgReadErrCorrection = new System.Windows.Forms.CheckBox();
            this.buttonImgBrowse = new System.Windows.Forms.Button();
            this.textBoxImgDestPath = new System.Windows.Forms.TextBox();
            this.tabPageDiscCopy = new System.Windows.Forms.TabPage();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label26 = new System.Windows.Forms.Label();
            this.comboBoxDscWriteMethod = new System.Windows.Forms.ComboBox();
            this.comboBoxDscReadMode = new System.Windows.Forms.ComboBox();
            this.label27 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.checkBoxDscAutoErase = new System.Windows.Forms.CheckBox();
            this.checkBoxDscEject = new System.Windows.Forms.CheckBox();
            this.checkBoxDscVerify = new System.Windows.Forms.CheckBox();
            this.buttonDscCopy = new System.Windows.Forms.Button();
            this.groupBoxDscProcessInfo = new System.Windows.Forms.GroupBox();
            this.lblSectors = new System.Windows.Forms.Label();
            this.lblDscStatus = new System.Windows.Forms.Label();
            this.progressBarDsc = new System.Windows.Forms.ProgressBar();
            this.buttonDscCancel = new System.Windows.Forms.Button();
            this.labelDscPercentage = new System.Windows.Forms.Label();
            this.labelDscBytesWritten = new System.Windows.Forms.Label();
            this.labelDscTtlBytes = new System.Windows.Forms.Label();
            this.groupBoxDscCorrectionSettings = new System.Windows.Forms.GroupBox();
            this.numericUpDownDscSoftwareCount = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownDscHardwareCount = new System.Windows.Forms.NumericUpDown();
            this.label31 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.checkBoxDscReadErrCorrection = new System.Windows.Forms.CheckBox();
            this.comboBoxDscSourceDev = new System.Windows.Forms.ComboBox();
            this.label25 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.saveFileDialogImgDest = new System.Windows.Forms.SaveFileDialog();
            this.menuStrip1.SuspendLayout();
            this.TabControl.SuspendLayout();
            this.tabPageDriveInfo.SuspendLayout();
            this.tabPageDriveInfoEx.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridDriveInfoEx)).BeginInit();
            this.tabPageDriveCapabilities.SuspendLayout();
            this.groupBoxDriveCaps.SuspendLayout();
            this.tabPageMediumInfo.SuspendLayout();
            this.tabPageImgCreation.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBoxProcessInfo.SuspendLayout();
            this.groupBoxImgCorrectionSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownImgSoftwareCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownImgHardwareCount)).BeginInit();
            this.tabPageDiscCopy.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBoxDscProcessInfo.SuspendLayout();
            this.groupBoxDscCorrectionSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDscSoftwareCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDscHardwareCount)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.deviceToolStripMenuItem,
            this.imagesToolStripMenuItem,
            this.mediumToolStripMenuItem,
            this.aSPISPTIToolStripMenuItem,
            this.informationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(630, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.cancel;
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(93, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // deviceToolStripMenuItem
            // 
            this.deviceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.isDeviceReadyToolStripMenuItem,
            this.ejectTrayToolStripMenuItem,
            this.closeTrayToolStripMenuItem,
            this.toolStripSeparator1,
            this.getDriveInfoToolStripMenuItem,
            this.getDriveInfoExToolStripMenuItem,
            this.getCapabilitiesToolStripMenuItem,
            this.setRegionCodeToolStripMenuItem});
            this.deviceToolStripMenuItem.Name = "deviceToolStripMenuItem";
            this.deviceToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.deviceToolStripMenuItem.Text = "&Device";
            // 
            // isDeviceReadyToolStripMenuItem
            // 
            this.isDeviceReadyToolStripMenuItem.Name = "isDeviceReadyToolStripMenuItem";
            this.isDeviceReadyToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.isDeviceReadyToolStripMenuItem.Text = "Is Device &Ready";
            this.isDeviceReadyToolStripMenuItem.Click += new System.EventHandler(this.isDeviceReadyToolStripMenuItem_Click);
            // 
            // ejectTrayToolStripMenuItem
            // 
            this.ejectTrayToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.cd_eject;
            this.ejectTrayToolStripMenuItem.Name = "ejectTrayToolStripMenuItem";
            this.ejectTrayToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.ejectTrayToolStripMenuItem.Text = "&Eject Tray";
            this.ejectTrayToolStripMenuItem.Click += new System.EventHandler(this.ejectTrayToolStripMenuItem_Click);
            // 
            // closeTrayToolStripMenuItem
            // 
            this.closeTrayToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.cd_load;
            this.closeTrayToolStripMenuItem.Name = "closeTrayToolStripMenuItem";
            this.closeTrayToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.closeTrayToolStripMenuItem.Text = "C&lose Tray";
            this.closeTrayToolStripMenuItem.Click += new System.EventHandler(this.closeTrayToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(158, 6);
            // 
            // getDriveInfoToolStripMenuItem
            // 
            this.getDriveInfoToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.drive_info;
            this.getDriveInfoToolStripMenuItem.Name = "getDriveInfoToolStripMenuItem";
            this.getDriveInfoToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.getDriveInfoToolStripMenuItem.Text = "Get Drive &Info";
            this.getDriveInfoToolStripMenuItem.Click += new System.EventHandler(this.getDriveInfoToolStripMenuItem_Click);
            // 
            // getDriveInfoExToolStripMenuItem
            // 
            this.getDriveInfoExToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.drive_info;
            this.getDriveInfoExToolStripMenuItem.Name = "getDriveInfoExToolStripMenuItem";
            this.getDriveInfoExToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.getDriveInfoExToolStripMenuItem.Text = "Get Drive InfoE&x";
            this.getDriveInfoExToolStripMenuItem.Click += new System.EventHandler(this.getDriveInfoExToolStripMenuItem_Click);
            // 
            // getCapabilitiesToolStripMenuItem
            // 
            this.getCapabilitiesToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.drive_scan;
            this.getCapabilitiesToolStripMenuItem.Name = "getCapabilitiesToolStripMenuItem";
            this.getCapabilitiesToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.getCapabilitiesToolStripMenuItem.Text = "Get &Capabilities";
            this.getCapabilitiesToolStripMenuItem.Click += new System.EventHandler(this.getCapabilitiesToolStripMenuItem_Click);
            // 
            // setRegionCodeToolStripMenuItem
            // 
            this.setRegionCodeToolStripMenuItem.Name = "setRegionCodeToolStripMenuItem";
            this.setRegionCodeToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.setRegionCodeToolStripMenuItem.Text = "Set &Region Code";
            this.setRegionCodeToolStripMenuItem.Click += new System.EventHandler(this.setRegionCodeToolStripMenuItem_Click);
            // 
            // imagesToolStripMenuItem
            // 
            this.imagesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mountImageToolStripMenuItem,
            this.unmountImageToolStripMenuItem});
            this.imagesToolStripMenuItem.Name = "imagesToolStripMenuItem";
            this.imagesToolStripMenuItem.Size = new System.Drawing.Size(57, 20);
            this.imagesToolStripMenuItem.Text = "&Images";
            // 
            // mountImageToolStripMenuItem
            // 
            this.mountImageToolStripMenuItem.Name = "mountImageToolStripMenuItem";
            this.mountImageToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.mountImageToolStripMenuItem.Text = "&Mount image...";
            this.mountImageToolStripMenuItem.Click += new System.EventHandler(this.mountImageToolStripMenuItem_Click);
            // 
            // unmountImageToolStripMenuItem
            // 
            this.unmountImageToolStripMenuItem.Name = "unmountImageToolStripMenuItem";
            this.unmountImageToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.unmountImageToolStripMenuItem.Text = "&Unmount image";
            this.unmountImageToolStripMenuItem.Click += new System.EventHandler(this.unmountImageToolStripMenuItem_Click);
            // 
            // mediumToolStripMenuItem
            // 
            this.mediumToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getDiskInfoToolStripMenuItem,
            this.eraseToolStripMenuItem});
            this.mediumToolStripMenuItem.Name = "mediumToolStripMenuItem";
            this.mediumToolStripMenuItem.Size = new System.Drawing.Size(64, 20);
            this.mediumToolStripMenuItem.Text = "&Medium";
            // 
            // getDiskInfoToolStripMenuItem
            // 
            this.getDiskInfoToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.cd_info;
            this.getDiskInfoToolStripMenuItem.Name = "getDiskInfoToolStripMenuItem";
            this.getDiskInfoToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.getDiskInfoToolStripMenuItem.Text = "Get Disk &Info";
            this.getDiskInfoToolStripMenuItem.Click += new System.EventHandler(this.getDiskInfoToolStripMenuItem_Click);
            // 
            // eraseToolStripMenuItem
            // 
            this.eraseToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.cd_erase;
            this.eraseToolStripMenuItem.Name = "eraseToolStripMenuItem";
            this.eraseToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.eraseToolStripMenuItem.Text = "&Erase";
            this.eraseToolStripMenuItem.Click += new System.EventHandler(this.eraseToolStripMenuItem_Click);
            // 
            // aSPISPTIToolStripMenuItem
            // 
            this.aSPISPTIToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.interfaceToolStripMenuItem,
            this.rescanDevicesToolStripMenuItem,
            this.burnDevicesOnlyToolStripMenuItem,
            this.disableImagewriterToolStripMenuItem});
            this.aSPISPTIToolStripMenuItem.Name = "aSPISPTIToolStripMenuItem";
            this.aSPISPTIToolStripMenuItem.Size = new System.Drawing.Size(70, 20);
            this.aSPISPTIToolStripMenuItem.Text = "A&SPI/SPTI";
            // 
            // interfaceToolStripMenuItem
            // 
            this.interfaceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.internalToolStripMenuItem,
            this.wnApsiToolStripMenuItem,
            this.frogAspiToolStripMenuItem});
            this.interfaceToolStripMenuItem.Name = "interfaceToolStripMenuItem";
            this.interfaceToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.interfaceToolStripMenuItem.Text = "I&nterface";
            // 
            // internalToolStripMenuItem
            // 
            this.internalToolStripMenuItem.Checked = true;
            this.internalToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.internalToolStripMenuItem.Name = "internalToolStripMenuItem";
            this.internalToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.internalToolStripMenuItem.Text = "&Internal";
            this.internalToolStripMenuItem.Click += new System.EventHandler(this.InterfaceInternalMenuItem_Click);
            // 
            // wnApsiToolStripMenuItem
            // 
            this.wnApsiToolStripMenuItem.Name = "wnApsiToolStripMenuItem";
            this.wnApsiToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.wnApsiToolStripMenuItem.Text = "&WnAspi";
            this.wnApsiToolStripMenuItem.Click += new System.EventHandler(this.InterfaceWnAspiMenuItem_Click);
            // 
            // frogAspiToolStripMenuItem
            // 
            this.frogAspiToolStripMenuItem.Name = "frogAspiToolStripMenuItem";
            this.frogAspiToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.frogAspiToolStripMenuItem.Text = "&FrogAspi";
            this.frogAspiToolStripMenuItem.Click += new System.EventHandler(this.InterfaceFrogAspiInternalMenuItem_Click);
            // 
            // rescanDevicesToolStripMenuItem
            // 
            this.rescanDevicesToolStripMenuItem.Image = global::CSharpUtilitiesSample.Properties.Resources.refresh2;
            this.rescanDevicesToolStripMenuItem.Name = "rescanDevicesToolStripMenuItem";
            this.rescanDevicesToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.rescanDevicesToolStripMenuItem.Text = "&Rescan Devices";
            this.rescanDevicesToolStripMenuItem.Click += new System.EventHandler(this.rescanDevicesToolStripMenuItem_Click);
            // 
            // burnDevicesOnlyToolStripMenuItem
            // 
            this.burnDevicesOnlyToolStripMenuItem.Checked = true;
            this.burnDevicesOnlyToolStripMenuItem.CheckOnClick = true;
            this.burnDevicesOnlyToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.burnDevicesOnlyToolStripMenuItem.Name = "burnDevicesOnlyToolStripMenuItem";
            this.burnDevicesOnlyToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.burnDevicesOnlyToolStripMenuItem.Text = "&Burn devices only";
            this.burnDevicesOnlyToolStripMenuItem.CheckedChanged += new System.EventHandler(this.burnDevicesOnlyToolStripMenuItem_Click);
            // 
            // disableImagewriterToolStripMenuItem
            // 
            this.disableImagewriterToolStripMenuItem.CheckOnClick = true;
            this.disableImagewriterToolStripMenuItem.Name = "disableImagewriterToolStripMenuItem";
            this.disableImagewriterToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.disableImagewriterToolStripMenuItem.Text = "Disable &Imagewriter";
            this.disableImagewriterToolStripMenuItem.CheckedChanged += new System.EventHandler(this.disableImagewriterToolStripMenuItem_Click);
            // 
            // informationToolStripMenuItem
            // 
            this.informationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.webToolStripMenuItem});
            this.informationToolStripMenuItem.Name = "informationToolStripMenuItem";
            this.informationToolStripMenuItem.Size = new System.Drawing.Size(82, 20);
            this.informationToolStripMenuItem.Text = "I&nformation";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.aboutToolStripMenuItem.Text = "&About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // webToolStripMenuItem
            // 
            this.webToolStripMenuItem.Name = "webToolStripMenuItem";
            this.webToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.webToolStripMenuItem.Text = "&Web";
            this.webToolStripMenuItem.Click += new System.EventHandler(this.webToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Device:";
            // 
            // deviceComboBox
            // 
            this.deviceComboBox.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.deviceComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.deviceComboBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.deviceComboBox.FormattingEnabled = true;
            this.deviceComboBox.Location = new System.Drawing.Point(79, 30);
            this.deviceComboBox.Name = "deviceComboBox";
            this.deviceComboBox.Size = new System.Drawing.Size(402, 21);
            this.deviceComboBox.TabIndex = 2;
            this.deviceComboBox.SelectedIndexChanged += new System.EventHandler(this.deviceComboBox_SelectedIndexChanged);
            // 
            // TabControl
            // 
            this.TabControl.Controls.Add(this.tabPageDriveInfo);
            this.TabControl.Controls.Add(this.tabPageDriveInfoEx);
            this.TabControl.Controls.Add(this.tabPageDriveCapabilities);
            this.TabControl.Controls.Add(this.tabPageMediumInfo);
            this.TabControl.Controls.Add(this.tabPageImgCreation);
            this.TabControl.Controls.Add(this.tabPageDiscCopy);
            this.TabControl.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.TabControl.Location = new System.Drawing.Point(0, 59);
            this.TabControl.Name = "TabControl";
            this.TabControl.SelectedIndex = 0;
            this.TabControl.Size = new System.Drawing.Size(630, 532);
            this.TabControl.TabIndex = 3;
            // 
            // tabPageDriveInfo
            // 
            this.tabPageDriveInfo.Controls.Add(this.lblDITestWrite);
            this.tabPageDriveInfo.Controls.Add(this.lblDIUnderrunProtection);
            this.tabPageDriveInfo.Controls.Add(this.lblDIMaxReadSpeed);
            this.tabPageDriveInfo.Controls.Add(this.lblDIMaxSpeed);
            this.tabPageDriveInfo.Controls.Add(this.lblDIDiskType);
            this.tabPageDriveInfo.Controls.Add(this.label6);
            this.tabPageDriveInfo.Controls.Add(this.label5);
            this.tabPageDriveInfo.Controls.Add(this.label4);
            this.tabPageDriveInfo.Controls.Add(this.label3);
            this.tabPageDriveInfo.Controls.Add(this.label2);
            this.tabPageDriveInfo.Location = new System.Drawing.Point(4, 22);
            this.tabPageDriveInfo.Name = "tabPageDriveInfo";
            this.tabPageDriveInfo.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPageDriveInfo.Size = new System.Drawing.Size(622, 506);
            this.tabPageDriveInfo.TabIndex = 0;
            this.tabPageDriveInfo.Text = "Drive Info";
            this.tabPageDriveInfo.UseVisualStyleBackColor = true;
            // 
            // lblDITestWrite
            // 
            this.lblDITestWrite.AutoSize = true;
            this.lblDITestWrite.Location = new System.Drawing.Point(167, 125);
            this.lblDITestWrite.Name = "lblDITestWrite";
            this.lblDITestWrite.Size = new System.Drawing.Size(16, 13);
            this.lblDITestWrite.TabIndex = 9;
            this.lblDITestWrite.Text = "...";
            // 
            // lblDIUnderrunProtection
            // 
            this.lblDIUnderrunProtection.AutoSize = true;
            this.lblDIUnderrunProtection.Location = new System.Drawing.Point(167, 97);
            this.lblDIUnderrunProtection.Name = "lblDIUnderrunProtection";
            this.lblDIUnderrunProtection.Size = new System.Drawing.Size(16, 13);
            this.lblDIUnderrunProtection.TabIndex = 8;
            this.lblDIUnderrunProtection.Text = "...";
            // 
            // lblDIMaxReadSpeed
            // 
            this.lblDIMaxReadSpeed.AutoSize = true;
            this.lblDIMaxReadSpeed.Location = new System.Drawing.Point(167, 71);
            this.lblDIMaxReadSpeed.Name = "lblDIMaxReadSpeed";
            this.lblDIMaxReadSpeed.Size = new System.Drawing.Size(16, 13);
            this.lblDIMaxReadSpeed.TabIndex = 7;
            this.lblDIMaxReadSpeed.Text = "...";
            // 
            // lblDIMaxSpeed
            // 
            this.lblDIMaxSpeed.AutoSize = true;
            this.lblDIMaxSpeed.Location = new System.Drawing.Point(167, 47);
            this.lblDIMaxSpeed.Name = "lblDIMaxSpeed";
            this.lblDIMaxSpeed.Size = new System.Drawing.Size(16, 13);
            this.lblDIMaxSpeed.TabIndex = 6;
            this.lblDIMaxSpeed.Text = "...";
            // 
            // lblDIDiskType
            // 
            this.lblDIDiskType.AutoSize = true;
            this.lblDIDiskType.Location = new System.Drawing.Point(167, 24);
            this.lblDIDiskType.Name = "lblDIDiskType";
            this.lblDIDiskType.Size = new System.Drawing.Size(16, 13);
            this.lblDIDiskType.TabIndex = 5;
            this.lblDIDiskType.Text = "...";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(102, 125);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 13);
            this.label6.TabIndex = 4;
            this.label6.Text = "Test Write:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 97);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(139, 13);
            this.label5.TabIndex = 3;
            this.label5.Text = "Buffer Underrun Protection: ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(65, 71);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(96, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Max. Read Speed:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(69, 47);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(92, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Max. Burn Speed:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(103, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Disk Type:";
            // 
            // tabPageDriveInfoEx
            // 
            this.tabPageDriveInfoEx.Controls.Add(this.dataGridDriveInfoEx);
            this.tabPageDriveInfoEx.Location = new System.Drawing.Point(4, 22);
            this.tabPageDriveInfoEx.Name = "tabPageDriveInfoEx";
            this.tabPageDriveInfoEx.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPageDriveInfoEx.Size = new System.Drawing.Size(622, 506);
            this.tabPageDriveInfoEx.TabIndex = 1;
            this.tabPageDriveInfoEx.Text = "Drive Info EX";
            this.tabPageDriveInfoEx.UseVisualStyleBackColor = true;
            // 
            // dataGridDriveInfoEx
            // 
            this.dataGridDriveInfoEx.AllowUserToAddRows = false;
            this.dataGridDriveInfoEx.AllowUserToDeleteRows = false;
            this.dataGridDriveInfoEx.AllowUserToOrderColumns = true;
            this.dataGridDriveInfoEx.AllowUserToResizeRows = false;
            this.dataGridDriveInfoEx.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridDriveInfoEx.BackgroundColor = System.Drawing.SystemColors.ControlLightLight;
            this.dataGridDriveInfoEx.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.dataGridDriveInfoEx.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridDriveInfoEx.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnParameter,
            this.ColumnValue});
            this.dataGridDriveInfoEx.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridDriveInfoEx.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnKeystroke;
            this.dataGridDriveInfoEx.Location = new System.Drawing.Point(3, 3);
            this.dataGridDriveInfoEx.MultiSelect = false;
            this.dataGridDriveInfoEx.Name = "dataGridDriveInfoEx";
            this.dataGridDriveInfoEx.ReadOnly = true;
            this.dataGridDriveInfoEx.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dataGridDriveInfoEx.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.dataGridDriveInfoEx.ShowCellErrors = false;
            this.dataGridDriveInfoEx.ShowCellToolTips = false;
            this.dataGridDriveInfoEx.ShowEditingIcon = false;
            this.dataGridDriveInfoEx.ShowRowErrors = false;
            this.dataGridDriveInfoEx.Size = new System.Drawing.Size(616, 500);
            this.dataGridDriveInfoEx.StandardTab = true;
            this.dataGridDriveInfoEx.TabIndex = 0;
            this.dataGridDriveInfoEx.TabStop = false;
            // 
            // ColumnParameter
            // 
            this.ColumnParameter.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.DisplayedCells;
            this.ColumnParameter.FillWeight = 40F;
            this.ColumnParameter.HeaderText = "Parameter";
            this.ColumnParameter.Name = "ColumnParameter";
            this.ColumnParameter.ReadOnly = true;
            this.ColumnParameter.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.ColumnParameter.Width = 80;
            // 
            // ColumnValue
            // 
            this.ColumnValue.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ColumnValue.FillWeight = 60F;
            this.ColumnValue.HeaderText = "Value";
            this.ColumnValue.Name = "ColumnValue";
            this.ColumnValue.ReadOnly = true;
            // 
            // tabPageDriveCapabilities
            // 
            this.tabPageDriveCapabilities.Controls.Add(this.groupBoxDriveCaps);
            this.tabPageDriveCapabilities.Controls.Add(this.textBox1);
            this.tabPageDriveCapabilities.Location = new System.Drawing.Point(4, 22);
            this.tabPageDriveCapabilities.Name = "tabPageDriveCapabilities";
            this.tabPageDriveCapabilities.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPageDriveCapabilities.Size = new System.Drawing.Size(622, 506);
            this.tabPageDriveCapabilities.TabIndex = 2;
            this.tabPageDriveCapabilities.Text = "Drive Capabilities";
            this.tabPageDriveCapabilities.UseVisualStyleBackColor = true;
            // 
            // groupBoxDriveCaps
            // 
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxCCDAAS);
            this.groupBoxDriveCaps.Controls.Add(this.chkWriteBDREXL);
            this.groupBoxDriveCaps.Controls.Add(this.chkWriteBDRXL);
            this.groupBoxDriveCaps.Controls.Add(this.chkReadBDREXL);
            this.groupBoxDriveCaps.Controls.Add(this.chkReadBDRXL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxLightScribe);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxLabelFlash);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxPacketWrite);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDAO96Raw);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDAO96Pack);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDAO16);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDAORaw);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxCDTWrite);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxCDTRead);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxMethod2);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxRWSCinLI);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxSideChange);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxSSS);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDiscPresent);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxSepMute);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxEject);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxPreventLockJumper);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxSepVolumeLevels);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxLockState);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxLockingMedia);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxBarcodeRead);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxUPCRead);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxISRCRead);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxC2P);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxRWSCDeint);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxRWSCRead);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxCDDAC);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxM2F2);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxM2F1);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDP2);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDP1);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxCompositeAV);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxAudioPlayback);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxLayerJumpRecording);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxDefectManagement);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxBufferUnderrunProtection);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxSMART);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxStreaming);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxMultisession);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxCPRMAuth);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxCanSimulateWrite);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteCDRWCav);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteMountRainer);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDplusRWDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDplusRDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteHDDVDRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteHDDVDR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteBLURAYRE);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteBLURAYR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDMRDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDplusRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDplusR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDRAM);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteDVDR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteCDRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxWriteCDR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadCDRWCav);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadMountRainer);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDplusRWDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDplusRDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadHDDVDROM);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadHDDVDRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadHDDVDR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadBLURAYROM);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadBLURAYRE);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadBLURAYR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDMRDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDDL);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDplusRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDplusR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDRAM);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVDR);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadDVD);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadCDRW);
            this.groupBoxDriveCaps.Controls.Add(this.checkBoxReadCDR);
            this.groupBoxDriveCaps.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBoxDriveCaps.Location = new System.Drawing.Point(3, 36);
            this.groupBoxDriveCaps.Name = "groupBoxDriveCaps";
            this.groupBoxDriveCaps.Size = new System.Drawing.Size(616, 467);
            this.groupBoxDriveCaps.TabIndex = 2;
            this.groupBoxDriveCaps.TabStop = false;
            this.groupBoxDriveCaps.Text = "Info";
            // 
            // checkBoxCCDAAS
            // 
            this.checkBoxCCDAAS.AutoCheck = false;
            this.checkBoxCCDAAS.AutoSize = true;
            this.checkBoxCCDAAS.Location = new System.Drawing.Point(6, 409);
            this.checkBoxCCDAAS.Name = "checkBoxCCDAAS";
            this.checkBoxCCDAAS.Size = new System.Drawing.Size(120, 17);
            this.checkBoxCCDAAS.TabIndex = 55;
            this.checkBoxCCDAAS.Text = "CDDA Accu Stream";
            this.checkBoxCCDAAS.UseVisualStyleBackColor = true;
            // 
            // chkWriteBDREXL
            // 
            this.chkWriteBDREXL.AutoCheck = false;
            this.chkWriteBDREXL.AutoSize = true;
            this.chkWriteBDREXL.Location = new System.Drawing.Point(435, 92);
            this.chkWriteBDREXL.Name = "chkWriteBDREXL";
            this.chkWriteBDREXL.Size = new System.Drawing.Size(103, 17);
            this.chkWriteBDREXL.TabIndex = 84;
            this.chkWriteBDREXL.Text = "Write BD-RE XL";
            this.chkWriteBDREXL.UseVisualStyleBackColor = true;
            // 
            // chkWriteBDRXL
            // 
            this.chkWriteBDRXL.AutoCheck = false;
            this.chkWriteBDRXL.AutoSize = true;
            this.chkWriteBDRXL.Location = new System.Drawing.Point(435, 74);
            this.chkWriteBDRXL.Name = "chkWriteBDRXL";
            this.chkWriteBDRXL.Size = new System.Drawing.Size(96, 17);
            this.chkWriteBDRXL.TabIndex = 83;
            this.chkWriteBDRXL.Text = "Write BD-R XL";
            this.chkWriteBDRXL.UseVisualStyleBackColor = true;
            // 
            // chkReadBDREXL
            // 
            this.chkReadBDREXL.AutoCheck = false;
            this.chkReadBDREXL.AutoSize = true;
            this.chkReadBDREXL.Location = new System.Drawing.Point(128, 128);
            this.chkReadBDREXL.Name = "chkReadBDREXL";
            this.chkReadBDREXL.Size = new System.Drawing.Size(104, 17);
            this.chkReadBDREXL.TabIndex = 82;
            this.chkReadBDREXL.Text = "Read BD-RE XL";
            this.chkReadBDREXL.UseVisualStyleBackColor = true;
            // 
            // chkReadBDRXL
            // 
            this.chkReadBDRXL.AutoCheck = false;
            this.chkReadBDRXL.AutoSize = true;
            this.chkReadBDRXL.Location = new System.Drawing.Point(128, 110);
            this.chkReadBDRXL.Name = "chkReadBDRXL";
            this.chkReadBDRXL.Size = new System.Drawing.Size(97, 17);
            this.chkReadBDRXL.TabIndex = 81;
            this.chkReadBDRXL.Text = "Read BD-R XL";
            this.chkReadBDRXL.UseVisualStyleBackColor = true;
            // 
            // checkBoxLightScribe
            // 
            this.checkBoxLightScribe.AutoCheck = false;
            this.checkBoxLightScribe.AutoSize = true;
            this.checkBoxLightScribe.Location = new System.Drawing.Point(128, 427);
            this.checkBoxLightScribe.Name = "checkBoxLightScribe";
            this.checkBoxLightScribe.Size = new System.Drawing.Size(79, 17);
            this.checkBoxLightScribe.TabIndex = 80;
            this.checkBoxLightScribe.Text = "LightScribe";
            this.checkBoxLightScribe.UseVisualStyleBackColor = true;
            // 
            // checkBoxLabelFlash
            // 
            this.checkBoxLabelFlash.AutoCheck = false;
            this.checkBoxLabelFlash.AutoSize = true;
            this.checkBoxLabelFlash.Location = new System.Drawing.Point(6, 427);
            this.checkBoxLabelFlash.Name = "checkBoxLabelFlash";
            this.checkBoxLabelFlash.Size = new System.Drawing.Size(77, 17);
            this.checkBoxLabelFlash.TabIndex = 79;
            this.checkBoxLabelFlash.Text = "LabelFlash";
            this.checkBoxLabelFlash.UseVisualStyleBackColor = true;
            // 
            // checkBoxPacketWrite
            // 
            this.checkBoxPacketWrite.AutoCheck = false;
            this.checkBoxPacketWrite.AutoSize = true;
            this.checkBoxPacketWrite.Location = new System.Drawing.Point(435, 409);
            this.checkBoxPacketWrite.Name = "checkBoxPacketWrite";
            this.checkBoxPacketWrite.Size = new System.Drawing.Size(88, 17);
            this.checkBoxPacketWrite.TabIndex = 78;
            this.checkBoxPacketWrite.Text = "Packet Write";
            this.checkBoxPacketWrite.UseVisualStyleBackColor = true;
            // 
            // checkBoxDAO96Raw
            // 
            this.checkBoxDAO96Raw.AutoCheck = false;
            this.checkBoxDAO96Raw.AutoSize = true;
            this.checkBoxDAO96Raw.Location = new System.Drawing.Point(435, 391);
            this.checkBoxDAO96Raw.Name = "checkBoxDAO96Raw";
            this.checkBoxDAO96Raw.Size = new System.Drawing.Size(89, 17);
            this.checkBoxDAO96Raw.TabIndex = 77;
            this.checkBoxDAO96Raw.Text = "DAO 96 Raw";
            this.checkBoxDAO96Raw.UseVisualStyleBackColor = true;
            // 
            // checkBoxDAO96Pack
            // 
            this.checkBoxDAO96Pack.AutoCheck = false;
            this.checkBoxDAO96Pack.AutoSize = true;
            this.checkBoxDAO96Pack.Location = new System.Drawing.Point(435, 373);
            this.checkBoxDAO96Pack.Name = "checkBoxDAO96Pack";
            this.checkBoxDAO96Pack.Size = new System.Drawing.Size(92, 17);
            this.checkBoxDAO96Pack.TabIndex = 76;
            this.checkBoxDAO96Pack.Text = "DAO 96 Pack";
            this.checkBoxDAO96Pack.UseVisualStyleBackColor = true;
            // 
            // checkBoxDAO16
            // 
            this.checkBoxDAO16.AutoCheck = false;
            this.checkBoxDAO16.AutoSize = true;
            this.checkBoxDAO16.Location = new System.Drawing.Point(435, 355);
            this.checkBoxDAO16.Name = "checkBoxDAO16";
            this.checkBoxDAO16.Size = new System.Drawing.Size(64, 17);
            this.checkBoxDAO16.TabIndex = 75;
            this.checkBoxDAO16.Text = "DAO 16";
            this.checkBoxDAO16.UseVisualStyleBackColor = true;
            // 
            // checkBoxDAORaw
            // 
            this.checkBoxDAORaw.AutoCheck = false;
            this.checkBoxDAORaw.AutoSize = true;
            this.checkBoxDAORaw.Location = new System.Drawing.Point(435, 337);
            this.checkBoxDAORaw.Name = "checkBoxDAORaw";
            this.checkBoxDAORaw.Size = new System.Drawing.Size(74, 17);
            this.checkBoxDAORaw.TabIndex = 74;
            this.checkBoxDAORaw.Text = "DAO Raw";
            this.checkBoxDAORaw.UseVisualStyleBackColor = true;
            // 
            // checkBoxCDTWrite
            // 
            this.checkBoxCDTWrite.AutoCheck = false;
            this.checkBoxCDTWrite.AutoSize = true;
            this.checkBoxCDTWrite.Location = new System.Drawing.Point(435, 319);
            this.checkBoxCDTWrite.Name = "checkBoxCDTWrite";
            this.checkBoxCDTWrite.Size = new System.Drawing.Size(93, 17);
            this.checkBoxCDTWrite.TabIndex = 73;
            this.checkBoxCDTWrite.Text = "CD-Text Write";
            this.checkBoxCDTWrite.UseVisualStyleBackColor = true;
            // 
            // checkBoxCDTRead
            // 
            this.checkBoxCDTRead.AutoCheck = false;
            this.checkBoxCDTRead.AutoSize = true;
            this.checkBoxCDTRead.Location = new System.Drawing.Point(435, 301);
            this.checkBoxCDTRead.Name = "checkBoxCDTRead";
            this.checkBoxCDTRead.Size = new System.Drawing.Size(94, 17);
            this.checkBoxCDTRead.TabIndex = 72;
            this.checkBoxCDTRead.Text = "CD-Text Read";
            this.checkBoxCDTRead.UseVisualStyleBackColor = true;
            // 
            // checkBoxMethod2
            // 
            this.checkBoxMethod2.AutoCheck = false;
            this.checkBoxMethod2.AutoSize = true;
            this.checkBoxMethod2.Location = new System.Drawing.Point(435, 284);
            this.checkBoxMethod2.Name = "checkBoxMethod2";
            this.checkBoxMethod2.Size = new System.Drawing.Size(116, 17);
            this.checkBoxMethod2.TabIndex = 71;
            this.checkBoxMethod2.Text = "Method 2 FP Read";
            this.checkBoxMethod2.UseVisualStyleBackColor = true;
            // 
            // checkBoxRWSCinLI
            // 
            this.checkBoxRWSCinLI.AutoCheck = false;
            this.checkBoxRWSCinLI.AutoSize = true;
            this.checkBoxRWSCinLI.Location = new System.Drawing.Point(281, 409);
            this.checkBoxRWSCinLI.Name = "checkBoxRWSCinLI";
            this.checkBoxRWSCinLI.Size = new System.Drawing.Size(117, 17);
            this.checkBoxRWSCinLI.TabIndex = 70;
            this.checkBoxRWSCinLI.Text = "R-W SC in LI Read";
            this.checkBoxRWSCinLI.UseVisualStyleBackColor = true;
            // 
            // checkBoxSideChange
            // 
            this.checkBoxSideChange.AutoCheck = false;
            this.checkBoxSideChange.AutoSize = true;
            this.checkBoxSideChange.Location = new System.Drawing.Point(281, 391);
            this.checkBoxSideChange.Name = "checkBoxSideChange";
            this.checkBoxSideChange.Size = new System.Drawing.Size(86, 17);
            this.checkBoxSideChange.TabIndex = 69;
            this.checkBoxSideChange.Text = "Side change";
            this.checkBoxSideChange.UseVisualStyleBackColor = true;
            // 
            // checkBoxSSS
            // 
            this.checkBoxSSS.AutoCheck = false;
            this.checkBoxSSS.AutoSize = true;
            this.checkBoxSSS.Location = new System.Drawing.Point(281, 373);
            this.checkBoxSSS.Name = "checkBoxSSS";
            this.checkBoxSSS.Size = new System.Drawing.Size(112, 17);
            this.checkBoxSSS.TabIndex = 68;
            this.checkBoxSSS.Text = "SW Slot Selection";
            this.checkBoxSSS.UseVisualStyleBackColor = true;
            // 
            // checkBoxDiscPresent
            // 
            this.checkBoxDiscPresent.AutoCheck = false;
            this.checkBoxDiscPresent.AutoSize = true;
            this.checkBoxDiscPresent.Location = new System.Drawing.Point(281, 355);
            this.checkBoxDiscPresent.Name = "checkBoxDiscPresent";
            this.checkBoxDiscPresent.Size = new System.Drawing.Size(85, 17);
            this.checkBoxDiscPresent.TabIndex = 67;
            this.checkBoxDiscPresent.Text = "Disc present";
            this.checkBoxDiscPresent.UseVisualStyleBackColor = true;
            // 
            // checkBoxSepMute
            // 
            this.checkBoxSepMute.AutoCheck = false;
            this.checkBoxSepMute.AutoSize = true;
            this.checkBoxSepMute.Location = new System.Drawing.Point(281, 337);
            this.checkBoxSepMute.Name = "checkBoxSepMute";
            this.checkBoxSepMute.Size = new System.Drawing.Size(115, 17);
            this.checkBoxSepMute.TabIndex = 66;
            this.checkBoxSepMute.Text = "Sep. channel mute";
            this.checkBoxSepMute.UseVisualStyleBackColor = true;
            // 
            // checkBoxEject
            // 
            this.checkBoxEject.AutoCheck = false;
            this.checkBoxEject.AutoSize = true;
            this.checkBoxEject.Location = new System.Drawing.Point(281, 301);
            this.checkBoxEject.Name = "checkBoxEject";
            this.checkBoxEject.Size = new System.Drawing.Size(88, 17);
            this.checkBoxEject.TabIndex = 65;
            this.checkBoxEject.Text = "Eject support";
            this.checkBoxEject.UseVisualStyleBackColor = true;
            // 
            // checkBoxPreventLockJumper
            // 
            this.checkBoxPreventLockJumper.AutoCheck = false;
            this.checkBoxPreventLockJumper.AutoSize = true;
            this.checkBoxPreventLockJumper.Location = new System.Drawing.Point(281, 284);
            this.checkBoxPreventLockJumper.Name = "checkBoxPreventLockJumper";
            this.checkBoxPreventLockJumper.Size = new System.Drawing.Size(120, 17);
            this.checkBoxPreventLockJumper.TabIndex = 64;
            this.checkBoxPreventLockJumper.Text = "Prevent lock jumper";
            this.checkBoxPreventLockJumper.UseVisualStyleBackColor = true;
            // 
            // checkBoxSepVolumeLevels
            // 
            this.checkBoxSepVolumeLevels.AutoCheck = false;
            this.checkBoxSepVolumeLevels.AutoSize = true;
            this.checkBoxSepVolumeLevels.Location = new System.Drawing.Point(281, 319);
            this.checkBoxSepVolumeLevels.Name = "checkBoxSepVolumeLevels";
            this.checkBoxSepVolumeLevels.Size = new System.Drawing.Size(115, 17);
            this.checkBoxSepVolumeLevels.TabIndex = 63;
            this.checkBoxSepVolumeLevels.Text = "Sep. volume levels";
            this.checkBoxSepVolumeLevels.UseVisualStyleBackColor = true;
            // 
            // checkBoxLockState
            // 
            this.checkBoxLockState.AutoCheck = false;
            this.checkBoxLockState.AutoSize = true;
            this.checkBoxLockState.Location = new System.Drawing.Point(128, 409);
            this.checkBoxLockState.Name = "checkBoxLockState";
            this.checkBoxLockState.Size = new System.Drawing.Size(76, 17);
            this.checkBoxLockState.TabIndex = 62;
            this.checkBoxLockState.Text = "Lock state";
            this.checkBoxLockState.UseVisualStyleBackColor = true;
            // 
            // checkBoxLockingMedia
            // 
            this.checkBoxLockingMedia.AutoCheck = false;
            this.checkBoxLockingMedia.AutoSize = true;
            this.checkBoxLockingMedia.Location = new System.Drawing.Point(128, 391);
            this.checkBoxLockingMedia.Name = "checkBoxLockingMedia";
            this.checkBoxLockingMedia.Size = new System.Drawing.Size(95, 17);
            this.checkBoxLockingMedia.TabIndex = 61;
            this.checkBoxLockingMedia.Text = "Locking media";
            this.checkBoxLockingMedia.UseVisualStyleBackColor = true;
            // 
            // checkBoxBarcodeRead
            // 
            this.checkBoxBarcodeRead.AutoCheck = false;
            this.checkBoxBarcodeRead.AutoSize = true;
            this.checkBoxBarcodeRead.Location = new System.Drawing.Point(128, 373);
            this.checkBoxBarcodeRead.Name = "checkBoxBarcodeRead";
            this.checkBoxBarcodeRead.Size = new System.Drawing.Size(95, 17);
            this.checkBoxBarcodeRead.TabIndex = 60;
            this.checkBoxBarcodeRead.Text = "Barcode Read";
            this.checkBoxBarcodeRead.UseVisualStyleBackColor = true;
            // 
            // checkBoxUPCRead
            // 
            this.checkBoxUPCRead.AutoCheck = false;
            this.checkBoxUPCRead.AutoSize = true;
            this.checkBoxUPCRead.Location = new System.Drawing.Point(128, 355);
            this.checkBoxUPCRead.Name = "checkBoxUPCRead";
            this.checkBoxUPCRead.Size = new System.Drawing.Size(77, 17);
            this.checkBoxUPCRead.TabIndex = 59;
            this.checkBoxUPCRead.Text = "UPC Read";
            this.checkBoxUPCRead.UseVisualStyleBackColor = true;
            // 
            // checkBoxISRCRead
            // 
            this.checkBoxISRCRead.AutoCheck = false;
            this.checkBoxISRCRead.AutoSize = true;
            this.checkBoxISRCRead.Location = new System.Drawing.Point(128, 337);
            this.checkBoxISRCRead.Name = "checkBoxISRCRead";
            this.checkBoxISRCRead.Size = new System.Drawing.Size(80, 17);
            this.checkBoxISRCRead.TabIndex = 58;
            this.checkBoxISRCRead.Text = "ISRC Read";
            this.checkBoxISRCRead.UseVisualStyleBackColor = true;
            // 
            // checkBoxC2P
            // 
            this.checkBoxC2P.AutoCheck = false;
            this.checkBoxC2P.AutoSize = true;
            this.checkBoxC2P.Location = new System.Drawing.Point(128, 319);
            this.checkBoxC2P.Name = "checkBoxC2P";
            this.checkBoxC2P.Size = new System.Drawing.Size(80, 17);
            this.checkBoxC2P.TabIndex = 57;
            this.checkBoxC2P.Text = "C2 Pointers";
            this.checkBoxC2P.UseVisualStyleBackColor = true;
            // 
            // checkBoxRWSCDeint
            // 
            this.checkBoxRWSCDeint.AutoCheck = false;
            this.checkBoxRWSCDeint.AutoSize = true;
            this.checkBoxRWSCDeint.Location = new System.Drawing.Point(128, 301);
            this.checkBoxRWSCDeint.Name = "checkBoxRWSCDeint";
            this.checkBoxRWSCDeint.Size = new System.Drawing.Size(94, 17);
            this.checkBoxRWSCDeint.TabIndex = 56;
            this.checkBoxRWSCDeint.Text = "R-W SC deint.";
            this.checkBoxRWSCDeint.UseVisualStyleBackColor = true;
            // 
            // checkBoxRWSCRead
            // 
            this.checkBoxRWSCRead.AutoCheck = false;
            this.checkBoxRWSCRead.AutoSize = true;
            this.checkBoxRWSCRead.Location = new System.Drawing.Point(128, 283);
            this.checkBoxRWSCRead.Name = "checkBoxRWSCRead";
            this.checkBoxRWSCRead.Size = new System.Drawing.Size(89, 17);
            this.checkBoxRWSCRead.TabIndex = 55;
            this.checkBoxRWSCRead.Text = "R-W SC read";
            this.checkBoxRWSCRead.UseVisualStyleBackColor = true;
            // 
            // checkBoxCDDAC
            // 
            this.checkBoxCDDAC.AutoCheck = false;
            this.checkBoxCDDAC.AutoSize = true;
            this.checkBoxCDDAC.Location = new System.Drawing.Point(6, 391);
            this.checkBoxCDDAC.Name = "checkBoxCDDAC";
            this.checkBoxCDDAC.Size = new System.Drawing.Size(111, 17);
            this.checkBoxCDDAC.TabIndex = 54;
            this.checkBoxCDDAC.Text = "CDDA Commands";
            this.checkBoxCDDAC.UseVisualStyleBackColor = true;
            // 
            // checkBoxM2F2
            // 
            this.checkBoxM2F2.AutoCheck = false;
            this.checkBoxM2F2.AutoSize = true;
            this.checkBoxM2F2.Location = new System.Drawing.Point(6, 373);
            this.checkBoxM2F2.Name = "checkBoxM2F2";
            this.checkBoxM2F2.Size = new System.Drawing.Size(97, 17);
            this.checkBoxM2F2.TabIndex = 53;
            this.checkBoxM2F2.Text = "Mode 2 Form 2";
            this.checkBoxM2F2.UseVisualStyleBackColor = true;
            // 
            // checkBoxM2F1
            // 
            this.checkBoxM2F1.AutoCheck = false;
            this.checkBoxM2F1.AutoSize = true;
            this.checkBoxM2F1.Location = new System.Drawing.Point(6, 355);
            this.checkBoxM2F1.Name = "checkBoxM2F1";
            this.checkBoxM2F1.Size = new System.Drawing.Size(97, 17);
            this.checkBoxM2F1.TabIndex = 52;
            this.checkBoxM2F1.Text = "Mode 2 Form 1";
            this.checkBoxM2F1.UseVisualStyleBackColor = true;
            // 
            // checkBoxDP2
            // 
            this.checkBoxDP2.AutoCheck = false;
            this.checkBoxDP2.AutoSize = true;
            this.checkBoxDP2.Location = new System.Drawing.Point(6, 337);
            this.checkBoxDP2.Name = "checkBoxDP2";
            this.checkBoxDP2.Size = new System.Drawing.Size(86, 17);
            this.checkBoxDP2.TabIndex = 51;
            this.checkBoxDP2.Text = "Digital Port 2";
            this.checkBoxDP2.UseVisualStyleBackColor = true;
            // 
            // checkBoxDP1
            // 
            this.checkBoxDP1.AutoCheck = false;
            this.checkBoxDP1.AutoSize = true;
            this.checkBoxDP1.Location = new System.Drawing.Point(6, 319);
            this.checkBoxDP1.Name = "checkBoxDP1";
            this.checkBoxDP1.Size = new System.Drawing.Size(86, 17);
            this.checkBoxDP1.TabIndex = 50;
            this.checkBoxDP1.Text = "Digital Port 1";
            this.checkBoxDP1.UseVisualStyleBackColor = true;
            // 
            // checkBoxCompositeAV
            // 
            this.checkBoxCompositeAV.AutoCheck = false;
            this.checkBoxCompositeAV.AutoSize = true;
            this.checkBoxCompositeAV.Location = new System.Drawing.Point(6, 301);
            this.checkBoxCompositeAV.Name = "checkBoxCompositeAV";
            this.checkBoxCompositeAV.Size = new System.Drawing.Size(97, 17);
            this.checkBoxCompositeAV.TabIndex = 49;
            this.checkBoxCompositeAV.Text = "Composite A/V";
            this.checkBoxCompositeAV.UseVisualStyleBackColor = true;
            // 
            // checkBoxAudioPlayback
            // 
            this.checkBoxAudioPlayback.AutoCheck = false;
            this.checkBoxAudioPlayback.AutoSize = true;
            this.checkBoxAudioPlayback.Location = new System.Drawing.Point(6, 283);
            this.checkBoxAudioPlayback.Name = "checkBoxAudioPlayback";
            this.checkBoxAudioPlayback.Size = new System.Drawing.Size(110, 17);
            this.checkBoxAudioPlayback.TabIndex = 48;
            this.checkBoxAudioPlayback.Text = "Analog audio play";
            this.checkBoxAudioPlayback.UseVisualStyleBackColor = true;
            // 
            // checkBoxLayerJumpRecording
            // 
            this.checkBoxLayerJumpRecording.AutoCheck = false;
            this.checkBoxLayerJumpRecording.AutoSize = true;
            this.checkBoxLayerJumpRecording.Location = new System.Drawing.Point(435, 265);
            this.checkBoxLayerJumpRecording.Name = "checkBoxLayerJumpRecording";
            this.checkBoxLayerJumpRecording.Size = new System.Drawing.Size(132, 17);
            this.checkBoxLayerJumpRecording.TabIndex = 47;
            this.checkBoxLayerJumpRecording.Text = "Layer Jump Recording";
            this.checkBoxLayerJumpRecording.UseVisualStyleBackColor = true;
            // 
            // checkBoxDefectManagement
            // 
            this.checkBoxDefectManagement.AutoCheck = false;
            this.checkBoxDefectManagement.AutoSize = true;
            this.checkBoxDefectManagement.Location = new System.Drawing.Point(435, 247);
            this.checkBoxDefectManagement.Name = "checkBoxDefectManagement";
            this.checkBoxDefectManagement.Size = new System.Drawing.Size(122, 17);
            this.checkBoxDefectManagement.TabIndex = 46;
            this.checkBoxDefectManagement.Text = "Defect management";
            this.checkBoxDefectManagement.UseVisualStyleBackColor = true;
            // 
            // checkBoxBufferUnderrunProtection
            // 
            this.checkBoxBufferUnderrunProtection.AutoCheck = false;
            this.checkBoxBufferUnderrunProtection.AutoSize = true;
            this.checkBoxBufferUnderrunProtection.Location = new System.Drawing.Point(281, 265);
            this.checkBoxBufferUnderrunProtection.Name = "checkBoxBufferUnderrunProtection";
            this.checkBoxBufferUnderrunProtection.Size = new System.Drawing.Size(152, 17);
            this.checkBoxBufferUnderrunProtection.TabIndex = 45;
            this.checkBoxBufferUnderrunProtection.Text = "Buffer Underrun Protection";
            this.checkBoxBufferUnderrunProtection.UseVisualStyleBackColor = true;
            // 
            // checkBoxSMART
            // 
            this.checkBoxSMART.AutoCheck = false;
            this.checkBoxSMART.AutoSize = true;
            this.checkBoxSMART.Location = new System.Drawing.Point(281, 247);
            this.checkBoxSMART.Name = "checkBoxSMART";
            this.checkBoxSMART.Size = new System.Drawing.Size(79, 17);
            this.checkBoxSMART.TabIndex = 44;
            this.checkBoxSMART.Text = "S.M.A.R.T.";
            this.checkBoxSMART.UseVisualStyleBackColor = true;
            // 
            // checkBoxStreaming
            // 
            this.checkBoxStreaming.AutoCheck = false;
            this.checkBoxStreaming.AutoSize = true;
            this.checkBoxStreaming.Location = new System.Drawing.Point(128, 265);
            this.checkBoxStreaming.Name = "checkBoxStreaming";
            this.checkBoxStreaming.Size = new System.Drawing.Size(73, 17);
            this.checkBoxStreaming.TabIndex = 43;
            this.checkBoxStreaming.Text = "Streaming";
            this.checkBoxStreaming.UseVisualStyleBackColor = true;
            // 
            // checkBoxMultisession
            // 
            this.checkBoxMultisession.AutoCheck = false;
            this.checkBoxMultisession.AutoSize = true;
            this.checkBoxMultisession.Location = new System.Drawing.Point(128, 247);
            this.checkBoxMultisession.Name = "checkBoxMultisession";
            this.checkBoxMultisession.Size = new System.Drawing.Size(83, 17);
            this.checkBoxMultisession.TabIndex = 42;
            this.checkBoxMultisession.Text = "Multisession";
            this.checkBoxMultisession.UseVisualStyleBackColor = true;
            // 
            // checkBoxCPRMAuth
            // 
            this.checkBoxCPRMAuth.AutoCheck = false;
            this.checkBoxCPRMAuth.AutoSize = true;
            this.checkBoxCPRMAuth.Location = new System.Drawing.Point(6, 265);
            this.checkBoxCPRMAuth.Name = "checkBoxCPRMAuth";
            this.checkBoxCPRMAuth.Size = new System.Drawing.Size(82, 17);
            this.checkBoxCPRMAuth.TabIndex = 41;
            this.checkBoxCPRMAuth.Text = "CPRM Auth";
            this.checkBoxCPRMAuth.UseVisualStyleBackColor = true;
            // 
            // checkBoxCanSimulateWrite
            // 
            this.checkBoxCanSimulateWrite.AutoCheck = false;
            this.checkBoxCanSimulateWrite.AutoSize = true;
            this.checkBoxCanSimulateWrite.Location = new System.Drawing.Point(6, 247);
            this.checkBoxCanSimulateWrite.Name = "checkBoxCanSimulateWrite";
            this.checkBoxCanSimulateWrite.Size = new System.Drawing.Size(111, 17);
            this.checkBoxCanSimulateWrite.TabIndex = 40;
            this.checkBoxCanSimulateWrite.Text = "Can simulate write";
            this.checkBoxCanSimulateWrite.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteCDRWCav
            // 
            this.checkBoxWriteCDRWCav.AutoCheck = false;
            this.checkBoxWriteCDRWCav.AutoSize = true;
            this.checkBoxWriteCDRWCav.Location = new System.Drawing.Point(281, 56);
            this.checkBoxWriteCDRWCav.Name = "checkBoxWriteCDRWCav";
            this.checkBoxWriteCDRWCav.Size = new System.Drawing.Size(115, 17);
            this.checkBoxWriteCDRWCav.TabIndex = 39;
            this.checkBoxWriteCDRWCav.Text = "Write CD-RW CAV";
            this.checkBoxWriteCDRWCav.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteMountRainer
            // 
            this.checkBoxWriteMountRainer.AutoCheck = false;
            this.checkBoxWriteMountRainer.AutoSize = true;
            this.checkBoxWriteMountRainer.Location = new System.Drawing.Point(435, 146);
            this.checkBoxWriteMountRainer.Name = "checkBoxWriteMountRainer";
            this.checkBoxWriteMountRainer.Size = new System.Drawing.Size(118, 17);
            this.checkBoxWriteMountRainer.TabIndex = 38;
            this.checkBoxWriteMountRainer.Text = "Write Mount Rainer";
            this.checkBoxWriteMountRainer.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDplusRWDL
            // 
            this.checkBoxWriteDVDplusRWDL.AutoCheck = false;
            this.checkBoxWriteDVDplusRWDL.AutoSize = true;
            this.checkBoxWriteDVDplusRWDL.Location = new System.Drawing.Point(281, 200);
            this.checkBoxWriteDVDplusRWDL.Name = "checkBoxWriteDVDplusRWDL";
            this.checkBoxWriteDVDplusRWDL.Size = new System.Drawing.Size(119, 17);
            this.checkBoxWriteDVDplusRWDL.TabIndex = 37;
            this.checkBoxWriteDVDplusRWDL.Text = "Write DVD+RW DL";
            this.checkBoxWriteDVDplusRWDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDplusRDL
            // 
            this.checkBoxWriteDVDplusRDL.AutoCheck = false;
            this.checkBoxWriteDVDplusRDL.AutoSize = true;
            this.checkBoxWriteDVDplusRDL.Location = new System.Drawing.Point(281, 182);
            this.checkBoxWriteDVDplusRDL.Name = "checkBoxWriteDVDplusRDL";
            this.checkBoxWriteDVDplusRDL.Size = new System.Drawing.Size(108, 17);
            this.checkBoxWriteDVDplusRDL.TabIndex = 36;
            this.checkBoxWriteDVDplusRDL.Text = "Write DVD+R DL";
            this.checkBoxWriteDVDplusRDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteHDDVDRW
            // 
            this.checkBoxWriteHDDVDRW.AutoCheck = false;
            this.checkBoxWriteHDDVDRW.AutoSize = true;
            this.checkBoxWriteHDDVDRW.Location = new System.Drawing.Point(435, 128);
            this.checkBoxWriteHDDVDRW.Name = "checkBoxWriteHDDVDRW";
            this.checkBoxWriteHDDVDRW.Size = new System.Drawing.Size(118, 17);
            this.checkBoxWriteHDDVDRW.TabIndex = 33;
            this.checkBoxWriteHDDVDRW.Text = "Write HD DVD-RW";
            this.checkBoxWriteHDDVDRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteHDDVDR
            // 
            this.checkBoxWriteHDDVDR.AutoCheck = false;
            this.checkBoxWriteHDDVDR.AutoSize = true;
            this.checkBoxWriteHDDVDR.Location = new System.Drawing.Point(435, 110);
            this.checkBoxWriteHDDVDR.Name = "checkBoxWriteHDDVDR";
            this.checkBoxWriteHDDVDR.Size = new System.Drawing.Size(107, 17);
            this.checkBoxWriteHDDVDR.TabIndex = 32;
            this.checkBoxWriteHDDVDR.Text = "Write HD DVD-R";
            this.checkBoxWriteHDDVDR.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteBLURAYRE
            // 
            this.checkBoxWriteBLURAYRE.AutoCheck = false;
            this.checkBoxWriteBLURAYRE.AutoSize = true;
            this.checkBoxWriteBLURAYRE.Location = new System.Drawing.Point(435, 56);
            this.checkBoxWriteBLURAYRE.Name = "checkBoxWriteBLURAYRE";
            this.checkBoxWriteBLURAYRE.Size = new System.Drawing.Size(87, 17);
            this.checkBoxWriteBLURAYRE.TabIndex = 31;
            this.checkBoxWriteBLURAYRE.Text = "Write BD-RE";
            this.checkBoxWriteBLURAYRE.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteBLURAYR
            // 
            this.checkBoxWriteBLURAYR.AutoCheck = false;
            this.checkBoxWriteBLURAYR.AutoSize = true;
            this.checkBoxWriteBLURAYR.Location = new System.Drawing.Point(435, 37);
            this.checkBoxWriteBLURAYR.Name = "checkBoxWriteBLURAYR";
            this.checkBoxWriteBLURAYR.Size = new System.Drawing.Size(80, 17);
            this.checkBoxWriteBLURAYR.TabIndex = 30;
            this.checkBoxWriteBLURAYR.Text = "Write BD-R";
            this.checkBoxWriteBLURAYR.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDMRDL
            // 
            this.checkBoxWriteDVDMRDL.AutoCheck = false;
            this.checkBoxWriteDVDMRDL.AutoSize = true;
            this.checkBoxWriteDVDMRDL.Location = new System.Drawing.Point(435, 19);
            this.checkBoxWriteDVDMRDL.Name = "checkBoxWriteDVDMRDL";
            this.checkBoxWriteDVDMRDL.Size = new System.Drawing.Size(111, 17);
            this.checkBoxWriteDVDMRDL.TabIndex = 29;
            this.checkBoxWriteDVDMRDL.Text = "Write DVD-MRDL";
            this.checkBoxWriteDVDMRDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDDL
            // 
            this.checkBoxWriteDVDDL.AutoCheck = false;
            this.checkBoxWriteDVDDL.AutoSize = true;
            this.checkBoxWriteDVDDL.Location = new System.Drawing.Point(281, 128);
            this.checkBoxWriteDVDDL.Name = "checkBoxWriteDVDDL";
            this.checkBoxWriteDVDDL.Size = new System.Drawing.Size(105, 17);
            this.checkBoxWriteDVDDL.TabIndex = 28;
            this.checkBoxWriteDVDDL.Text = "Write DVD-R DL";
            this.checkBoxWriteDVDDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDplusRW
            // 
            this.checkBoxWriteDVDplusRW.AutoCheck = false;
            this.checkBoxWriteDVDplusRW.AutoSize = true;
            this.checkBoxWriteDVDplusRW.Location = new System.Drawing.Point(281, 164);
            this.checkBoxWriteDVDplusRW.Name = "checkBoxWriteDVDplusRW";
            this.checkBoxWriteDVDplusRW.Size = new System.Drawing.Size(102, 17);
            this.checkBoxWriteDVDplusRW.TabIndex = 27;
            this.checkBoxWriteDVDplusRW.Text = "Write DVD+RW";
            this.checkBoxWriteDVDplusRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDplusR
            // 
            this.checkBoxWriteDVDplusR.AutoCheck = false;
            this.checkBoxWriteDVDplusR.AutoSize = true;
            this.checkBoxWriteDVDplusR.Location = new System.Drawing.Point(281, 146);
            this.checkBoxWriteDVDplusR.Name = "checkBoxWriteDVDplusR";
            this.checkBoxWriteDVDplusR.Size = new System.Drawing.Size(91, 17);
            this.checkBoxWriteDVDplusR.TabIndex = 26;
            this.checkBoxWriteDVDplusR.Text = "Write DVD+R";
            this.checkBoxWriteDVDplusR.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDRAM
            // 
            this.checkBoxWriteDVDRAM.AutoCheck = false;
            this.checkBoxWriteDVDRAM.AutoSize = true;
            this.checkBoxWriteDVDRAM.Location = new System.Drawing.Point(281, 110);
            this.checkBoxWriteDVDRAM.Name = "checkBoxWriteDVDRAM";
            this.checkBoxWriteDVDRAM.Size = new System.Drawing.Size(104, 17);
            this.checkBoxWriteDVDRAM.TabIndex = 25;
            this.checkBoxWriteDVDRAM.Text = "Write DVD-RAM";
            this.checkBoxWriteDVDRAM.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDRW
            // 
            this.checkBoxWriteDVDRW.AutoCheck = false;
            this.checkBoxWriteDVDRW.AutoSize = true;
            this.checkBoxWriteDVDRW.Location = new System.Drawing.Point(281, 92);
            this.checkBoxWriteDVDRW.Name = "checkBoxWriteDVDRW";
            this.checkBoxWriteDVDRW.Size = new System.Drawing.Size(99, 17);
            this.checkBoxWriteDVDRW.TabIndex = 24;
            this.checkBoxWriteDVDRW.Text = "Write DVD-RW";
            this.checkBoxWriteDVDRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteDVDR
            // 
            this.checkBoxWriteDVDR.AutoCheck = false;
            this.checkBoxWriteDVDR.AutoSize = true;
            this.checkBoxWriteDVDR.Location = new System.Drawing.Point(281, 74);
            this.checkBoxWriteDVDR.Name = "checkBoxWriteDVDR";
            this.checkBoxWriteDVDR.Size = new System.Drawing.Size(88, 17);
            this.checkBoxWriteDVDR.TabIndex = 23;
            this.checkBoxWriteDVDR.Text = "Write DVD-R";
            this.checkBoxWriteDVDR.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteCDRW
            // 
            this.checkBoxWriteCDRW.AutoCheck = false;
            this.checkBoxWriteCDRW.AutoSize = true;
            this.checkBoxWriteCDRW.Location = new System.Drawing.Point(281, 37);
            this.checkBoxWriteCDRW.Name = "checkBoxWriteCDRW";
            this.checkBoxWriteCDRW.Size = new System.Drawing.Size(91, 17);
            this.checkBoxWriteCDRW.TabIndex = 22;
            this.checkBoxWriteCDRW.Text = "Write CD-RW";
            this.checkBoxWriteCDRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxWriteCDR
            // 
            this.checkBoxWriteCDR.AutoCheck = false;
            this.checkBoxWriteCDR.AutoSize = true;
            this.checkBoxWriteCDR.Location = new System.Drawing.Point(281, 19);
            this.checkBoxWriteCDR.Name = "checkBoxWriteCDR";
            this.checkBoxWriteCDR.Size = new System.Drawing.Size(80, 17);
            this.checkBoxWriteCDR.TabIndex = 21;
            this.checkBoxWriteCDR.Text = "Write CD-R";
            this.checkBoxWriteCDR.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadCDRWCav
            // 
            this.checkBoxReadCDRWCav.AutoCheck = false;
            this.checkBoxReadCDRWCav.AutoSize = true;
            this.checkBoxReadCDRWCav.Location = new System.Drawing.Point(6, 56);
            this.checkBoxReadCDRWCav.Name = "checkBoxReadCDRWCav";
            this.checkBoxReadCDRWCav.Size = new System.Drawing.Size(116, 17);
            this.checkBoxReadCDRWCav.TabIndex = 20;
            this.checkBoxReadCDRWCav.Text = "Read CD-RW CAV";
            this.checkBoxReadCDRWCav.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadMountRainer
            // 
            this.checkBoxReadMountRainer.AutoCheck = false;
            this.checkBoxReadMountRainer.AutoSize = true;
            this.checkBoxReadMountRainer.Location = new System.Drawing.Point(128, 200);
            this.checkBoxReadMountRainer.Name = "checkBoxReadMountRainer";
            this.checkBoxReadMountRainer.Size = new System.Drawing.Size(119, 17);
            this.checkBoxReadMountRainer.TabIndex = 19;
            this.checkBoxReadMountRainer.Text = "Read Mount Rainer";
            this.checkBoxReadMountRainer.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDplusRWDL
            // 
            this.checkBoxReadDVDplusRWDL.AutoCheck = false;
            this.checkBoxReadDVDplusRWDL.AutoSize = true;
            this.checkBoxReadDVDplusRWDL.Location = new System.Drawing.Point(128, 19);
            this.checkBoxReadDVDplusRWDL.Name = "checkBoxReadDVDplusRWDL";
            this.checkBoxReadDVDplusRWDL.Size = new System.Drawing.Size(120, 17);
            this.checkBoxReadDVDplusRWDL.TabIndex = 18;
            this.checkBoxReadDVDplusRWDL.Text = "Read DVD+RW DL";
            this.checkBoxReadDVDplusRWDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDplusRDL
            // 
            this.checkBoxReadDVDplusRDL.AutoCheck = false;
            this.checkBoxReadDVDplusRDL.AutoSize = true;
            this.checkBoxReadDVDplusRDL.Location = new System.Drawing.Point(6, 200);
            this.checkBoxReadDVDplusRDL.Name = "checkBoxReadDVDplusRDL";
            this.checkBoxReadDVDplusRDL.Size = new System.Drawing.Size(109, 17);
            this.checkBoxReadDVDplusRDL.TabIndex = 17;
            this.checkBoxReadDVDplusRDL.Text = "Read DVD+R DL";
            this.checkBoxReadDVDplusRDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadHDDVDROM
            // 
            this.checkBoxReadHDDVDROM.AutoCheck = false;
            this.checkBoxReadHDDVDROM.AutoSize = true;
            this.checkBoxReadHDDVDROM.Location = new System.Drawing.Point(128, 146);
            this.checkBoxReadHDDVDROM.Name = "checkBoxReadHDDVDROM";
            this.checkBoxReadHDDVDROM.Size = new System.Drawing.Size(125, 17);
            this.checkBoxReadHDDVDROM.TabIndex = 15;
            this.checkBoxReadHDDVDROM.Text = "Read HD DVD-ROM";
            this.checkBoxReadHDDVDROM.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadHDDVDRW
            // 
            this.checkBoxReadHDDVDRW.AutoCheck = false;
            this.checkBoxReadHDDVDRW.AutoSize = true;
            this.checkBoxReadHDDVDRW.Location = new System.Drawing.Point(128, 182);
            this.checkBoxReadHDDVDRW.Name = "checkBoxReadHDDVDRW";
            this.checkBoxReadHDDVDRW.Size = new System.Drawing.Size(119, 17);
            this.checkBoxReadHDDVDRW.TabIndex = 14;
            this.checkBoxReadHDDVDRW.Text = "Read HD DVD-RW";
            this.checkBoxReadHDDVDRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadHDDVDR
            // 
            this.checkBoxReadHDDVDR.AutoCheck = false;
            this.checkBoxReadHDDVDR.AutoSize = true;
            this.checkBoxReadHDDVDR.Location = new System.Drawing.Point(128, 164);
            this.checkBoxReadHDDVDR.Name = "checkBoxReadHDDVDR";
            this.checkBoxReadHDDVDR.Size = new System.Drawing.Size(108, 17);
            this.checkBoxReadHDDVDR.TabIndex = 13;
            this.checkBoxReadHDDVDR.Text = "Read HD DVD-R";
            this.checkBoxReadHDDVDR.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadBLURAYROM
            // 
            this.checkBoxReadBLURAYROM.AutoCheck = false;
            this.checkBoxReadBLURAYROM.AutoSize = true;
            this.checkBoxReadBLURAYROM.Location = new System.Drawing.Point(128, 56);
            this.checkBoxReadBLURAYROM.Name = "checkBoxReadBLURAYROM";
            this.checkBoxReadBLURAYROM.Size = new System.Drawing.Size(98, 17);
            this.checkBoxReadBLURAYROM.TabIndex = 12;
            this.checkBoxReadBLURAYROM.Text = "Read BD-ROM";
            this.checkBoxReadBLURAYROM.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadBLURAYRE
            // 
            this.checkBoxReadBLURAYRE.AutoCheck = false;
            this.checkBoxReadBLURAYRE.AutoSize = true;
            this.checkBoxReadBLURAYRE.Location = new System.Drawing.Point(128, 92);
            this.checkBoxReadBLURAYRE.Name = "checkBoxReadBLURAYRE";
            this.checkBoxReadBLURAYRE.Size = new System.Drawing.Size(88, 17);
            this.checkBoxReadBLURAYRE.TabIndex = 11;
            this.checkBoxReadBLURAYRE.Text = "Read BD-RE";
            this.checkBoxReadBLURAYRE.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadBLURAYR
            // 
            this.checkBoxReadBLURAYR.AutoCheck = false;
            this.checkBoxReadBLURAYR.AutoSize = true;
            this.checkBoxReadBLURAYR.Location = new System.Drawing.Point(128, 74);
            this.checkBoxReadBLURAYR.Name = "checkBoxReadBLURAYR";
            this.checkBoxReadBLURAYR.Size = new System.Drawing.Size(81, 17);
            this.checkBoxReadBLURAYR.TabIndex = 10;
            this.checkBoxReadBLURAYR.Text = "Read BD-R";
            this.checkBoxReadBLURAYR.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDMRDL
            // 
            this.checkBoxReadDVDMRDL.AutoCheck = false;
            this.checkBoxReadDVDMRDL.AutoSize = true;
            this.checkBoxReadDVDMRDL.Location = new System.Drawing.Point(128, 37);
            this.checkBoxReadDVDMRDL.Name = "checkBoxReadDVDMRDL";
            this.checkBoxReadDVDMRDL.Size = new System.Drawing.Size(112, 17);
            this.checkBoxReadDVDMRDL.TabIndex = 9;
            this.checkBoxReadDVDMRDL.Text = "Read DVD-MRDL";
            this.checkBoxReadDVDMRDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDDL
            // 
            this.checkBoxReadDVDDL.AutoCheck = false;
            this.checkBoxReadDVDDL.AutoSize = true;
            this.checkBoxReadDVDDL.Location = new System.Drawing.Point(6, 146);
            this.checkBoxReadDVDDL.Name = "checkBoxReadDVDDL";
            this.checkBoxReadDVDDL.Size = new System.Drawing.Size(106, 17);
            this.checkBoxReadDVDDL.TabIndex = 8;
            this.checkBoxReadDVDDL.Text = "Read DVD-R DL";
            this.checkBoxReadDVDDL.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDplusRW
            // 
            this.checkBoxReadDVDplusRW.AutoCheck = false;
            this.checkBoxReadDVDplusRW.AutoSize = true;
            this.checkBoxReadDVDplusRW.Location = new System.Drawing.Point(6, 182);
            this.checkBoxReadDVDplusRW.Name = "checkBoxReadDVDplusRW";
            this.checkBoxReadDVDplusRW.Size = new System.Drawing.Size(103, 17);
            this.checkBoxReadDVDplusRW.TabIndex = 7;
            this.checkBoxReadDVDplusRW.Text = "Read DVD+RW";
            this.checkBoxReadDVDplusRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDplusR
            // 
            this.checkBoxReadDVDplusR.AutoCheck = false;
            this.checkBoxReadDVDplusR.AutoSize = true;
            this.checkBoxReadDVDplusR.Location = new System.Drawing.Point(6, 164);
            this.checkBoxReadDVDplusR.Name = "checkBoxReadDVDplusR";
            this.checkBoxReadDVDplusR.Size = new System.Drawing.Size(92, 17);
            this.checkBoxReadDVDplusR.TabIndex = 6;
            this.checkBoxReadDVDplusR.Text = "Read DVD+R";
            this.checkBoxReadDVDplusR.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDRAM
            // 
            this.checkBoxReadDVDRAM.AutoCheck = false;
            this.checkBoxReadDVDRAM.AutoSize = true;
            this.checkBoxReadDVDRAM.Location = new System.Drawing.Point(6, 128);
            this.checkBoxReadDVDRAM.Name = "checkBoxReadDVDRAM";
            this.checkBoxReadDVDRAM.Size = new System.Drawing.Size(105, 17);
            this.checkBoxReadDVDRAM.TabIndex = 5;
            this.checkBoxReadDVDRAM.Text = "Read DVD-RAM";
            this.checkBoxReadDVDRAM.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDRW
            // 
            this.checkBoxReadDVDRW.AutoCheck = false;
            this.checkBoxReadDVDRW.AutoSize = true;
            this.checkBoxReadDVDRW.Location = new System.Drawing.Point(6, 110);
            this.checkBoxReadDVDRW.Name = "checkBoxReadDVDRW";
            this.checkBoxReadDVDRW.Size = new System.Drawing.Size(100, 17);
            this.checkBoxReadDVDRW.TabIndex = 4;
            this.checkBoxReadDVDRW.Text = "Read DVD-RW";
            this.checkBoxReadDVDRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVDR
            // 
            this.checkBoxReadDVDR.AutoCheck = false;
            this.checkBoxReadDVDR.AutoSize = true;
            this.checkBoxReadDVDR.Location = new System.Drawing.Point(6, 92);
            this.checkBoxReadDVDR.Name = "checkBoxReadDVDR";
            this.checkBoxReadDVDR.Size = new System.Drawing.Size(89, 17);
            this.checkBoxReadDVDR.TabIndex = 3;
            this.checkBoxReadDVDR.Text = "Read DVD-R";
            this.checkBoxReadDVDR.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadDVD
            // 
            this.checkBoxReadDVD.AutoCheck = false;
            this.checkBoxReadDVD.AutoSize = true;
            this.checkBoxReadDVD.Location = new System.Drawing.Point(6, 74);
            this.checkBoxReadDVD.Name = "checkBoxReadDVD";
            this.checkBoxReadDVD.Size = new System.Drawing.Size(106, 17);
            this.checkBoxReadDVD.TabIndex = 2;
            this.checkBoxReadDVD.Text = "Read DVD-ROM";
            this.checkBoxReadDVD.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadCDRW
            // 
            this.checkBoxReadCDRW.AutoCheck = false;
            this.checkBoxReadCDRW.AutoSize = true;
            this.checkBoxReadCDRW.Location = new System.Drawing.Point(6, 37);
            this.checkBoxReadCDRW.Name = "checkBoxReadCDRW";
            this.checkBoxReadCDRW.Size = new System.Drawing.Size(92, 17);
            this.checkBoxReadCDRW.TabIndex = 1;
            this.checkBoxReadCDRW.Text = "Read CD-RW";
            this.checkBoxReadCDRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxReadCDR
            // 
            this.checkBoxReadCDR.AutoCheck = false;
            this.checkBoxReadCDR.AutoSize = true;
            this.checkBoxReadCDR.Location = new System.Drawing.Point(6, 19);
            this.checkBoxReadCDR.Name = "checkBoxReadCDR";
            this.checkBoxReadCDR.Size = new System.Drawing.Size(81, 17);
            this.checkBoxReadCDR.TabIndex = 0;
            this.checkBoxReadCDR.Text = "Read CD-R";
            this.checkBoxReadCDR.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.textBox1.Enabled = false;
            this.textBox1.Location = new System.Drawing.Point(3, 3);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(616, 33);
            this.textBox1.TabIndex = 1;
            this.textBox1.Text = "If you didn\'t get the expected drive data it is possible that your drive doesn\'t " +
    "support the commands sent to the drive. Usually a Firmware update helps to fix t" +
    "his problem.";
            // 
            // tabPageMediumInfo
            // 
            this.tabPageMediumInfo.Controls.Add(this.labelMaxWriteSpeed);
            this.tabPageMediumInfo.Controls.Add(this.label29);
            this.tabPageMediumInfo.Controls.Add(this.labelVendorID);
            this.tabPageMediumInfo.Controls.Add(this.label28);
            this.tabPageMediumInfo.Controls.Add(this.treeViewMediumInfo);
            this.tabPageMediumInfo.Controls.Add(this.buttonEject);
            this.tabPageMediumInfo.Controls.Add(this.buttonRefresh);
            this.tabPageMediumInfo.Controls.Add(this.buttonTerminateLastSession);
            this.tabPageMediumInfo.Controls.Add(this.labelUpcEanCode);
            this.tabPageMediumInfo.Controls.Add(this.labelFreeSpace);
            this.tabPageMediumInfo.Controls.Add(this.labelUsedSpace);
            this.tabPageMediumInfo.Controls.Add(this.labelSize);
            this.tabPageMediumInfo.Controls.Add(this.label21);
            this.tabPageMediumInfo.Controls.Add(this.label22);
            this.tabPageMediumInfo.Controls.Add(this.label23);
            this.tabPageMediumInfo.Controls.Add(this.label24);
            this.tabPageMediumInfo.Controls.Add(this.labelTracks);
            this.tabPageMediumInfo.Controls.Add(this.labelSessions);
            this.tabPageMediumInfo.Controls.Add(this.labelLast);
            this.tabPageMediumInfo.Controls.Add(this.labelStatus);
            this.tabPageMediumInfo.Controls.Add(this.labelMedium);
            this.tabPageMediumInfo.Controls.Add(this.label11);
            this.tabPageMediumInfo.Controls.Add(this.label10);
            this.tabPageMediumInfo.Controls.Add(this.label9);
            this.tabPageMediumInfo.Controls.Add(this.label8);
            this.tabPageMediumInfo.Controls.Add(this.label7);
            this.tabPageMediumInfo.Location = new System.Drawing.Point(4, 22);
            this.tabPageMediumInfo.Name = "tabPageMediumInfo";
            this.tabPageMediumInfo.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPageMediumInfo.Size = new System.Drawing.Size(622, 506);
            this.tabPageMediumInfo.TabIndex = 3;
            this.tabPageMediumInfo.Text = "Medium Info";
            this.tabPageMediumInfo.UseVisualStyleBackColor = true;
            // 
            // labelMaxWriteSpeed
            // 
            this.labelMaxWriteSpeed.AutoSize = true;
            this.labelMaxWriteSpeed.Location = new System.Drawing.Point(558, 15);
            this.labelMaxWriteSpeed.Name = "labelMaxWriteSpeed";
            this.labelMaxWriteSpeed.Size = new System.Drawing.Size(16, 13);
            this.labelMaxWriteSpeed.TabIndex = 25;
            this.labelMaxWriteSpeed.Text = "...";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(436, 15);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(116, 13);
            this.label29.TabIndex = 24;
            this.label29.Text = "Maximum Write Speed:";
            // 
            // labelVendorID
            // 
            this.labelVendorID.AutoSize = true;
            this.labelVendorID.Location = new System.Drawing.Point(331, 104);
            this.labelVendorID.Name = "labelVendorID";
            this.labelVendorID.Size = new System.Drawing.Size(16, 13);
            this.labelVendorID.TabIndex = 23;
            this.labelVendorID.Text = "...";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(214, 104);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(58, 13);
            this.label28.TabIndex = 22;
            this.label28.Text = "Vendor ID:";
            // 
            // treeViewMediumInfo
            // 
            this.treeViewMediumInfo.Location = new System.Drawing.Point(6, 161);
            this.treeViewMediumInfo.Name = "treeViewMediumInfo";
            this.treeViewMediumInfo.Size = new System.Drawing.Size(608, 167);
            this.treeViewMediumInfo.TabIndex = 21;
            // 
            // buttonEject
            // 
            this.buttonEject.Image = global::CSharpUtilitiesSample.Properties.Resources.cd_eject;
            this.buttonEject.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.buttonEject.Location = new System.Drawing.Point(121, 334);
            this.buttonEject.Name = "buttonEject";
            this.buttonEject.Size = new System.Drawing.Size(109, 25);
            this.buttonEject.TabIndex = 20;
            this.buttonEject.Text = "&Eject";
            this.buttonEject.UseVisualStyleBackColor = true;
            this.buttonEject.Click += new System.EventHandler(this.ejectTrayToolStripMenuItem_Click);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Image = global::CSharpUtilitiesSample.Properties.Resources.refresh2;
            this.buttonRefresh.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.buttonRefresh.Location = new System.Drawing.Point(6, 334);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(109, 25);
            this.buttonRefresh.TabIndex = 19;
            this.buttonRefresh.Text = "&Refresh";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.getDiskInfoToolStripMenuItem_Click);
            // 
            // buttonTerminateLastSession
            // 
            this.buttonTerminateLastSession.Enabled = false;
            this.buttonTerminateLastSession.Location = new System.Drawing.Point(6, 133);
            this.buttonTerminateLastSession.Name = "buttonTerminateLastSession";
            this.buttonTerminateLastSession.Size = new System.Drawing.Size(147, 22);
            this.buttonTerminateLastSession.TabIndex = 18;
            this.buttonTerminateLastSession.Text = "&Terminate Last Session";
            this.buttonTerminateLastSession.UseVisualStyleBackColor = true;
            this.buttonTerminateLastSession.Click += new System.EventHandler(this.buttonTerminateLastSession_Click);
            // 
            // labelUpcEanCode
            // 
            this.labelUpcEanCode.AutoSize = true;
            this.labelUpcEanCode.Location = new System.Drawing.Point(331, 81);
            this.labelUpcEanCode.Name = "labelUpcEanCode";
            this.labelUpcEanCode.Size = new System.Drawing.Size(16, 13);
            this.labelUpcEanCode.TabIndex = 17;
            this.labelUpcEanCode.Text = "...";
            // 
            // labelFreeSpace
            // 
            this.labelFreeSpace.AutoSize = true;
            this.labelFreeSpace.Location = new System.Drawing.Point(331, 59);
            this.labelFreeSpace.Name = "labelFreeSpace";
            this.labelFreeSpace.Size = new System.Drawing.Size(16, 13);
            this.labelFreeSpace.TabIndex = 16;
            this.labelFreeSpace.Text = "...";
            // 
            // labelUsedSpace
            // 
            this.labelUsedSpace.AutoSize = true;
            this.labelUsedSpace.Location = new System.Drawing.Point(331, 37);
            this.labelUsedSpace.Name = "labelUsedSpace";
            this.labelUsedSpace.Size = new System.Drawing.Size(16, 13);
            this.labelUsedSpace.TabIndex = 15;
            this.labelUsedSpace.Text = "...";
            // 
            // labelSize
            // 
            this.labelSize.AutoSize = true;
            this.labelSize.Location = new System.Drawing.Point(331, 15);
            this.labelSize.Name = "labelSize";
            this.labelSize.Size = new System.Drawing.Size(16, 13);
            this.labelSize.TabIndex = 14;
            this.labelSize.Text = "...";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(214, 81);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(86, 13);
            this.label21.TabIndex = 13;
            this.label21.Text = "UPC/EAN code:";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(214, 59);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(65, 13);
            this.label22.TabIndex = 12;
            this.label22.Text = "Free Space:";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(214, 37);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(69, 13);
            this.label23.TabIndex = 11;
            this.label23.Text = "Used Space:";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(214, 15);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(30, 13);
            this.label24.TabIndex = 10;
            this.label24.Text = "Size:";
            // 
            // labelTracks
            // 
            this.labelTracks.AutoSize = true;
            this.labelTracks.Location = new System.Drawing.Point(78, 104);
            this.labelTracks.Name = "labelTracks";
            this.labelTracks.Size = new System.Drawing.Size(16, 13);
            this.labelTracks.TabIndex = 9;
            this.labelTracks.Text = "...";
            // 
            // labelSessions
            // 
            this.labelSessions.AutoSize = true;
            this.labelSessions.Location = new System.Drawing.Point(78, 81);
            this.labelSessions.Name = "labelSessions";
            this.labelSessions.Size = new System.Drawing.Size(16, 13);
            this.labelSessions.TabIndex = 8;
            this.labelSessions.Text = "...";
            // 
            // labelLast
            // 
            this.labelLast.AutoSize = true;
            this.labelLast.Location = new System.Drawing.Point(78, 59);
            this.labelLast.Name = "labelLast";
            this.labelLast.Size = new System.Drawing.Size(16, 13);
            this.labelLast.TabIndex = 7;
            this.labelLast.Text = "...";
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Location = new System.Drawing.Point(78, 37);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(16, 13);
            this.labelStatus.TabIndex = 6;
            this.labelStatus.Text = "...";
            // 
            // labelMedium
            // 
            this.labelMedium.AutoSize = true;
            this.labelMedium.Location = new System.Drawing.Point(78, 15);
            this.labelMedium.Name = "labelMedium";
            this.labelMedium.Size = new System.Drawing.Size(16, 13);
            this.labelMedium.TabIndex = 5;
            this.labelMedium.Text = "...";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(11, 104);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(43, 13);
            this.label11.TabIndex = 4;
            this.label11.Text = "Tracks:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(11, 81);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(52, 13);
            this.label10.TabIndex = 3;
            this.label10.Text = "Sessions:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(11, 59);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(30, 13);
            this.label9.TabIndex = 2;
            this.label9.Text = "Last:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(11, 37);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(40, 13);
            this.label8.TabIndex = 1;
            this.label8.Text = "Status:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(11, 15);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(47, 13);
            this.label7.TabIndex = 0;
            this.label7.Text = "Medium:";
            // 
            // tabPageImgCreation
            // 
            this.tabPageImgCreation.Controls.Add(this.groupBox2);
            this.tabPageImgCreation.Controls.Add(this.groupBox1);
            this.tabPageImgCreation.Controls.Add(this.groupBoxProcessInfo);
            this.tabPageImgCreation.Controls.Add(this.groupBoxImgCorrectionSettings);
            this.tabPageImgCreation.Controls.Add(this.buttonImgBrowse);
            this.tabPageImgCreation.Controls.Add(this.textBoxImgDestPath);
            this.tabPageImgCreation.Location = new System.Drawing.Point(4, 22);
            this.tabPageImgCreation.Name = "tabPageImgCreation";
            this.tabPageImgCreation.Size = new System.Drawing.Size(622, 506);
            this.tabPageImgCreation.TabIndex = 6;
            this.tabPageImgCreation.Text = "Image Creation";
            this.tabPageImgCreation.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonImgCheckFormat);
            this.groupBox2.Controls.Add(this.comboBoxImgFormat);
            this.groupBox2.Location = new System.Drawing.Point(413, 45);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox2.Size = new System.Drawing.Size(133, 81);
            this.groupBox2.TabIndex = 15;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Format";
            // 
            // buttonImgCheckFormat
            // 
            this.buttonImgCheckFormat.Location = new System.Drawing.Point(15, 50);
            this.buttonImgCheckFormat.Name = "buttonImgCheckFormat";
            this.buttonImgCheckFormat.Size = new System.Drawing.Size(106, 23);
            this.buttonImgCheckFormat.TabIndex = 10;
            this.buttonImgCheckFormat.Text = "Check Formats";
            this.buttonImgCheckFormat.UseVisualStyleBackColor = true;
            this.buttonImgCheckFormat.Click += new System.EventHandler(this.buttonImgCheckFormat_Click);
            // 
            // comboBoxImgFormat
            // 
            this.comboBoxImgFormat.FormattingEnabled = true;
            this.comboBoxImgFormat.Location = new System.Drawing.Point(15, 22);
            this.comboBoxImgFormat.Name = "comboBoxImgFormat";
            this.comboBoxImgFormat.Size = new System.Drawing.Size(107, 21);
            this.comboBoxImgFormat.TabIndex = 3;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonImgExecute);
            this.groupBox1.Controls.Add(this.checkBoxImgCreate);
            this.groupBox1.Controls.Add(this.checkBoxImgVerify);
            this.groupBox1.Location = new System.Drawing.Point(44, 245);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox1.Size = new System.Drawing.Size(502, 71);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Task";
            // 
            // buttonImgExecute
            // 
            this.buttonImgExecute.Location = new System.Drawing.Point(384, 42);
            this.buttonImgExecute.Name = "buttonImgExecute";
            this.buttonImgExecute.Size = new System.Drawing.Size(106, 23);
            this.buttonImgExecute.TabIndex = 12;
            this.buttonImgExecute.Text = "Execute";
            this.buttonImgExecute.UseVisualStyleBackColor = true;
            this.buttonImgExecute.Click += new System.EventHandler(this.buttonImgExecute_Click);
            // 
            // checkBoxImgCreate
            // 
            this.checkBoxImgCreate.AutoSize = true;
            this.checkBoxImgCreate.Checked = true;
            this.checkBoxImgCreate.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxImgCreate.Location = new System.Drawing.Point(30, 18);
            this.checkBoxImgCreate.Name = "checkBoxImgCreate";
            this.checkBoxImgCreate.Size = new System.Drawing.Size(195, 17);
            this.checkBoxImgCreate.TabIndex = 9;
            this.checkBoxImgCreate.Text = "Create image file from selected disc.";
            this.checkBoxImgCreate.UseVisualStyleBackColor = true;
            // 
            // checkBoxImgVerify
            // 
            this.checkBoxImgVerify.AutoSize = true;
            this.checkBoxImgVerify.Location = new System.Drawing.Point(30, 41);
            this.checkBoxImgVerify.Name = "checkBoxImgVerify";
            this.checkBoxImgVerify.Size = new System.Drawing.Size(320, 17);
            this.checkBoxImgVerify.TabIndex = 11;
            this.checkBoxImgVerify.Text = "Verify a created image file (Not the same as \"Verify after burn\")";
            this.checkBoxImgVerify.UseVisualStyleBackColor = true;
            // 
            // groupBoxProcessInfo
            // 
            this.groupBoxProcessInfo.Controls.Add(this.lblVerifySector);
            this.groupBoxProcessInfo.Controls.Add(this.lblStatus);
            this.groupBoxProcessInfo.Controls.Add(this.progressBarImg);
            this.groupBoxProcessInfo.Controls.Add(this.buttonImgCancel);
            this.groupBoxProcessInfo.Controls.Add(this.labelImgPercentage);
            this.groupBoxProcessInfo.Controls.Add(this.labelImgReadErr);
            this.groupBoxProcessInfo.Controls.Add(this.labelImgCurSec);
            this.groupBoxProcessInfo.Controls.Add(this.labelImgTtlSec);
            this.groupBoxProcessInfo.Location = new System.Drawing.Point(44, 321);
            this.groupBoxProcessInfo.Name = "groupBoxProcessInfo";
            this.groupBoxProcessInfo.Size = new System.Drawing.Size(502, 123);
            this.groupBoxProcessInfo.TabIndex = 13;
            this.groupBoxProcessInfo.TabStop = false;
            this.groupBoxProcessInfo.Text = "Process Information";
            // 
            // lblVerifySector
            // 
            this.lblVerifySector.AutoSize = true;
            this.lblVerifySector.Location = new System.Drawing.Point(210, 94);
            this.lblVerifySector.Name = "lblVerifySector";
            this.lblVerifySector.Size = new System.Drawing.Size(41, 13);
            this.lblVerifySector.TabIndex = 17;
            this.lblVerifySector.Text = "Sector:";
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Location = new System.Drawing.Point(45, 94);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(40, 13);
            this.lblStatus.TabIndex = 16;
            this.lblStatus.Text = "Status:";
            // 
            // progressBarImg
            // 
            this.progressBarImg.Location = new System.Drawing.Point(16, 19);
            this.progressBarImg.Name = "progressBarImg";
            this.progressBarImg.Size = new System.Drawing.Size(474, 23);
            this.progressBarImg.TabIndex = 15;
            // 
            // buttonImgCancel
            // 
            this.buttonImgCancel.Location = new System.Drawing.Point(384, 53);
            this.buttonImgCancel.Name = "buttonImgCancel";
            this.buttonImgCancel.Size = new System.Drawing.Size(106, 23);
            this.buttonImgCancel.TabIndex = 14;
            this.buttonImgCancel.Text = "Cancel";
            this.buttonImgCancel.UseVisualStyleBackColor = true;
            this.buttonImgCancel.Click += new System.EventHandler(this.buttonImgCancel_Click);
            // 
            // labelImgPercentage
            // 
            this.labelImgPercentage.AutoSize = true;
            this.labelImgPercentage.Location = new System.Drawing.Point(210, 73);
            this.labelImgPercentage.Name = "labelImgPercentage";
            this.labelImgPercentage.Size = new System.Drawing.Size(68, 13);
            this.labelImgPercentage.TabIndex = 3;
            this.labelImgPercentage.Text = "Percentage :";
            // 
            // labelImgReadErr
            // 
            this.labelImgReadErr.AutoSize = true;
            this.labelImgReadErr.Location = new System.Drawing.Point(210, 53);
            this.labelImgReadErr.Name = "labelImgReadErr";
            this.labelImgReadErr.Size = new System.Drawing.Size(40, 13);
            this.labelImgReadErr.TabIndex = 2;
            this.labelImgReadErr.Text = "Errors :";
            // 
            // labelImgCurSec
            // 
            this.labelImgCurSec.AutoSize = true;
            this.labelImgCurSec.Location = new System.Drawing.Point(45, 73);
            this.labelImgCurSec.Name = "labelImgCurSec";
            this.labelImgCurSec.Size = new System.Drawing.Size(81, 13);
            this.labelImgCurSec.TabIndex = 1;
            this.labelImgCurSec.Text = "Current Sector :";
            // 
            // labelImgTtlSec
            // 
            this.labelImgTtlSec.AutoSize = true;
            this.labelImgTtlSec.Location = new System.Drawing.Point(45, 53);
            this.labelImgTtlSec.Name = "labelImgTtlSec";
            this.labelImgTtlSec.Size = new System.Drawing.Size(76, 13);
            this.labelImgTtlSec.TabIndex = 0;
            this.labelImgTtlSec.Text = "Total Sectors :";
            // 
            // groupBoxImgCorrectionSettings
            // 
            this.groupBoxImgCorrectionSettings.Controls.Add(this.textBoxImgBadListPath);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.label19);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.checkBoxImgBadList);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.checkBoxImgBlankBad);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.numericUpDownImgSoftwareCount);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.numericUpDownImgHardwareCount);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.label18);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.label17);
            this.groupBoxImgCorrectionSettings.Controls.Add(this.checkBoxImgReadErrCorrection);
            this.groupBoxImgCorrectionSettings.Location = new System.Drawing.Point(44, 45);
            this.groupBoxImgCorrectionSettings.Name = "groupBoxImgCorrectionSettings";
            this.groupBoxImgCorrectionSettings.Size = new System.Drawing.Size(364, 194);
            this.groupBoxImgCorrectionSettings.TabIndex = 2;
            this.groupBoxImgCorrectionSettings.TabStop = false;
            this.groupBoxImgCorrectionSettings.Text = "Read Errors Correction Settings";
            // 
            // textBoxImgBadListPath
            // 
            this.textBoxImgBadListPath.Enabled = false;
            this.textBoxImgBadListPath.Location = new System.Drawing.Point(104, 157);
            this.textBoxImgBadListPath.Name = "textBoxImgBadListPath";
            this.textBoxImgBadListPath.Size = new System.Drawing.Size(236, 20);
            this.textBoxImgBadListPath.TabIndex = 8;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(69, 160);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(35, 13);
            this.label19.TabIndex = 7;
            this.label19.Text = "Path :";
            // 
            // checkBoxImgBadList
            // 
            this.checkBoxImgBadList.AutoSize = true;
            this.checkBoxImgBadList.Location = new System.Drawing.Point(30, 129);
            this.checkBoxImgBadList.Name = "checkBoxImgBadList";
            this.checkBoxImgBadList.Size = new System.Drawing.Size(103, 17);
            this.checkBoxImgBadList.TabIndex = 6;
            this.checkBoxImgBadList.Text = "Bad Sectors List";
            this.checkBoxImgBadList.UseVisualStyleBackColor = true;
            this.checkBoxImgBadList.CheckedChanged += new System.EventHandler(this.checkBoxImgBadList_CheckedChanged);
            // 
            // checkBoxImgBlankBad
            // 
            this.checkBoxImgBlankBad.AutoSize = true;
            this.checkBoxImgBlankBad.Checked = true;
            this.checkBoxImgBlankBad.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxImgBlankBad.Location = new System.Drawing.Point(30, 106);
            this.checkBoxImgBlankBad.Name = "checkBoxImgBlankBad";
            this.checkBoxImgBlankBad.Size = new System.Drawing.Size(114, 17);
            this.checkBoxImgBlankBad.TabIndex = 5;
            this.checkBoxImgBlankBad.Text = "Blank Bad Sectors";
            this.checkBoxImgBlankBad.UseVisualStyleBackColor = true;
            // 
            // numericUpDownImgSoftwareCount
            // 
            this.numericUpDownImgSoftwareCount.Location = new System.Drawing.Point(195, 77);
            this.numericUpDownImgSoftwareCount.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDownImgSoftwareCount.Name = "numericUpDownImgSoftwareCount";
            this.numericUpDownImgSoftwareCount.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownImgSoftwareCount.TabIndex = 4;
            // 
            // numericUpDownImgHardwareCount
            // 
            this.numericUpDownImgHardwareCount.Location = new System.Drawing.Point(195, 51);
            this.numericUpDownImgHardwareCount.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDownImgHardwareCount.Name = "numericUpDownImgHardwareCount";
            this.numericUpDownImgHardwareCount.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownImgHardwareCount.TabIndex = 3;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(69, 79);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(122, 13);
            this.label18.TabIndex = 2;
            this.label18.Text = "Software Retries Count :";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(69, 53);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(126, 13);
            this.label17.TabIndex = 1;
            this.label17.Text = "Hardware Retries Count :";
            // 
            // checkBoxImgReadErrCorrection
            // 
            this.checkBoxImgReadErrCorrection.AutoSize = true;
            this.checkBoxImgReadErrCorrection.Checked = true;
            this.checkBoxImgReadErrCorrection.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxImgReadErrCorrection.Location = new System.Drawing.Point(30, 28);
            this.checkBoxImgReadErrCorrection.Name = "checkBoxImgReadErrCorrection";
            this.checkBoxImgReadErrCorrection.Size = new System.Drawing.Size(175, 17);
            this.checkBoxImgReadErrCorrection.TabIndex = 0;
            this.checkBoxImgReadErrCorrection.Text = "Read Errors Correction Enabled";
            this.checkBoxImgReadErrCorrection.UseVisualStyleBackColor = true;
            this.checkBoxImgReadErrCorrection.CheckedChanged += new System.EventHandler(this.checkBoxImgReadErrCorrection_CheckedChanged);
            // 
            // buttonImgBrowse
            // 
            this.buttonImgBrowse.Location = new System.Drawing.Point(428, 17);
            this.buttonImgBrowse.Name = "buttonImgBrowse";
            this.buttonImgBrowse.Size = new System.Drawing.Size(106, 23);
            this.buttonImgBrowse.TabIndex = 1;
            this.buttonImgBrowse.Text = "Browse";
            this.buttonImgBrowse.UseVisualStyleBackColor = true;
            this.buttonImgBrowse.Click += new System.EventHandler(this.buttonImgBrowse_Click);
            // 
            // textBoxImgDestPath
            // 
            this.textBoxImgDestPath.Location = new System.Drawing.Point(44, 19);
            this.textBoxImgDestPath.Name = "textBoxImgDestPath";
            this.textBoxImgDestPath.Size = new System.Drawing.Size(364, 20);
            this.textBoxImgDestPath.TabIndex = 0;
            // 
            // tabPageDiscCopy
            // 
            this.tabPageDiscCopy.Controls.Add(this.groupBox4);
            this.tabPageDiscCopy.Controls.Add(this.groupBox3);
            this.tabPageDiscCopy.Controls.Add(this.groupBoxDscProcessInfo);
            this.tabPageDiscCopy.Controls.Add(this.groupBoxDscCorrectionSettings);
            this.tabPageDiscCopy.Controls.Add(this.comboBoxDscSourceDev);
            this.tabPageDiscCopy.Controls.Add(this.label25);
            this.tabPageDiscCopy.Location = new System.Drawing.Point(4, 22);
            this.tabPageDiscCopy.Name = "tabPageDiscCopy";
            this.tabPageDiscCopy.Size = new System.Drawing.Size(622, 506);
            this.tabPageDiscCopy.TabIndex = 7;
            this.tabPageDiscCopy.Text = "Disc Copy";
            this.tabPageDiscCopy.UseVisualStyleBackColor = true;
            this.tabPageDiscCopy.Enter += new System.EventHandler(this.tabPageDiscCopy_Enter);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label26);
            this.groupBox4.Controls.Add(this.comboBoxDscWriteMethod);
            this.groupBox4.Controls.Add(this.comboBoxDscReadMode);
            this.groupBox4.Controls.Add(this.label27);
            this.groupBox4.Location = new System.Drawing.Point(399, 45);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox4.Size = new System.Drawing.Size(150, 119);
            this.groupBox4.TabIndex = 22;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Read / Write";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(15, 28);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(77, 13);
            this.label26.TabIndex = 5;
            this.label26.Text = "Write Method :";
            // 
            // comboBoxDscWriteMethod
            // 
            this.comboBoxDscWriteMethod.FormattingEnabled = true;
            this.comboBoxDscWriteMethod.Location = new System.Drawing.Point(17, 45);
            this.comboBoxDscWriteMethod.Name = "comboBoxDscWriteMethod";
            this.comboBoxDscWriteMethod.Size = new System.Drawing.Size(84, 21);
            this.comboBoxDscWriteMethod.TabIndex = 18;
            // 
            // comboBoxDscReadMode
            // 
            this.comboBoxDscReadMode.FormattingEnabled = true;
            this.comboBoxDscReadMode.Location = new System.Drawing.Point(17, 84);
            this.comboBoxDscReadMode.Name = "comboBoxDscReadMode";
            this.comboBoxDscReadMode.Size = new System.Drawing.Size(84, 21);
            this.comboBoxDscReadMode.TabIndex = 19;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(15, 67);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(69, 13);
            this.label27.TabIndex = 17;
            this.label27.Text = "Read Mode :";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.checkBoxDscAutoErase);
            this.groupBox3.Controls.Add(this.checkBoxDscEject);
            this.groupBox3.Controls.Add(this.checkBoxDscVerify);
            this.groupBox3.Controls.Add(this.buttonDscCopy);
            this.groupBox3.Location = new System.Drawing.Point(47, 169);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.groupBox3.Size = new System.Drawing.Size(502, 90);
            this.groupBox3.TabIndex = 21;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Task";
            // 
            // checkBoxDscAutoErase
            // 
            this.checkBoxDscAutoErase.AutoSize = true;
            this.checkBoxDscAutoErase.Location = new System.Drawing.Point(28, 20);
            this.checkBoxDscAutoErase.Name = "checkBoxDscAutoErase";
            this.checkBoxDscAutoErase.Size = new System.Drawing.Size(112, 17);
            this.checkBoxDscAutoErase.TabIndex = 21;
            this.checkBoxDscAutoErase.Text = "Erase before copy";
            this.checkBoxDscAutoErase.UseVisualStyleBackColor = true;
            // 
            // checkBoxDscEject
            // 
            this.checkBoxDscEject.AutoSize = true;
            this.checkBoxDscEject.Location = new System.Drawing.Point(28, 41);
            this.checkBoxDscEject.Name = "checkBoxDscEject";
            this.checkBoxDscEject.Size = new System.Drawing.Size(100, 17);
            this.checkBoxDscEject.TabIndex = 20;
            this.checkBoxDscEject.Text = "Eject After Burn";
            this.checkBoxDscEject.UseVisualStyleBackColor = true;
            // 
            // checkBoxDscVerify
            // 
            this.checkBoxDscVerify.AutoSize = true;
            this.checkBoxDscVerify.Location = new System.Drawing.Point(28, 62);
            this.checkBoxDscVerify.Name = "checkBoxDscVerify";
            this.checkBoxDscVerify.Size = new System.Drawing.Size(102, 17);
            this.checkBoxDscVerify.TabIndex = 5;
            this.checkBoxDscVerify.Text = "Verify After Burn";
            this.checkBoxDscVerify.UseVisualStyleBackColor = true;
            // 
            // buttonDscCopy
            // 
            this.buttonDscCopy.Location = new System.Drawing.Point(319, 58);
            this.buttonDscCopy.Name = "buttonDscCopy";
            this.buttonDscCopy.Size = new System.Drawing.Size(171, 23);
            this.buttonDscCopy.TabIndex = 16;
            this.buttonDscCopy.Text = "Copy";
            this.buttonDscCopy.UseVisualStyleBackColor = true;
            this.buttonDscCopy.Click += new System.EventHandler(this.buttonDscCopy_Click);
            // 
            // groupBoxDscProcessInfo
            // 
            this.groupBoxDscProcessInfo.Controls.Add(this.lblSectors);
            this.groupBoxDscProcessInfo.Controls.Add(this.lblDscStatus);
            this.groupBoxDscProcessInfo.Controls.Add(this.progressBarDsc);
            this.groupBoxDscProcessInfo.Controls.Add(this.buttonDscCancel);
            this.groupBoxDscProcessInfo.Controls.Add(this.labelDscPercentage);
            this.groupBoxDscProcessInfo.Controls.Add(this.labelDscBytesWritten);
            this.groupBoxDscProcessInfo.Controls.Add(this.labelDscTtlBytes);
            this.groupBoxDscProcessInfo.Location = new System.Drawing.Point(47, 266);
            this.groupBoxDscProcessInfo.Name = "groupBoxDscProcessInfo";
            this.groupBoxDscProcessInfo.Size = new System.Drawing.Size(502, 162);
            this.groupBoxDscProcessInfo.TabIndex = 15;
            this.groupBoxDscProcessInfo.TabStop = false;
            this.groupBoxDscProcessInfo.Text = "Process Information";
            // 
            // lblSectors
            // 
            this.lblSectors.AutoSize = true;
            this.lblSectors.Location = new System.Drawing.Point(210, 94);
            this.lblSectors.Name = "lblSectors";
            this.lblSectors.Size = new System.Drawing.Size(41, 13);
            this.lblSectors.TabIndex = 19;
            this.lblSectors.Text = "Sector:";
            // 
            // lblDscStatus
            // 
            this.lblDscStatus.AutoSize = true;
            this.lblDscStatus.Location = new System.Drawing.Point(26, 94);
            this.lblDscStatus.Name = "lblDscStatus";
            this.lblDscStatus.Size = new System.Drawing.Size(40, 13);
            this.lblDscStatus.TabIndex = 16;
            this.lblDscStatus.Text = "Status:";
            // 
            // progressBarDsc
            // 
            this.progressBarDsc.Location = new System.Drawing.Point(16, 19);
            this.progressBarDsc.Name = "progressBarDsc";
            this.progressBarDsc.Size = new System.Drawing.Size(474, 23);
            this.progressBarDsc.TabIndex = 15;
            // 
            // buttonDscCancel
            // 
            this.buttonDscCancel.Location = new System.Drawing.Point(384, 132);
            this.buttonDscCancel.Name = "buttonDscCancel";
            this.buttonDscCancel.Size = new System.Drawing.Size(106, 23);
            this.buttonDscCancel.TabIndex = 14;
            this.buttonDscCancel.Text = "Cancel";
            this.buttonDscCancel.UseVisualStyleBackColor = true;
            this.buttonDscCancel.Click += new System.EventHandler(this.buttonDscCancel_Click);
            // 
            // labelDscPercentage
            // 
            this.labelDscPercentage.AutoSize = true;
            this.labelDscPercentage.Location = new System.Drawing.Point(210, 53);
            this.labelDscPercentage.Name = "labelDscPercentage";
            this.labelDscPercentage.Size = new System.Drawing.Size(68, 13);
            this.labelDscPercentage.TabIndex = 3;
            this.labelDscPercentage.Text = "Percentage :";
            // 
            // labelDscBytesWritten
            // 
            this.labelDscBytesWritten.AutoSize = true;
            this.labelDscBytesWritten.Location = new System.Drawing.Point(26, 74);
            this.labelDscBytesWritten.Name = "labelDscBytesWritten";
            this.labelDscBytesWritten.Size = new System.Drawing.Size(76, 13);
            this.labelDscBytesWritten.TabIndex = 1;
            this.labelDscBytesWritten.Text = "Bytes Written :";
            // 
            // labelDscTtlBytes
            // 
            this.labelDscTtlBytes.AutoSize = true;
            this.labelDscTtlBytes.Location = new System.Drawing.Point(26, 53);
            this.labelDscTtlBytes.Name = "labelDscTtlBytes";
            this.labelDscTtlBytes.Size = new System.Drawing.Size(66, 13);
            this.labelDscTtlBytes.TabIndex = 0;
            this.labelDscTtlBytes.Text = "Total Bytes :";
            // 
            // groupBoxDscCorrectionSettings
            // 
            this.groupBoxDscCorrectionSettings.Controls.Add(this.numericUpDownDscSoftwareCount);
            this.groupBoxDscCorrectionSettings.Controls.Add(this.numericUpDownDscHardwareCount);
            this.groupBoxDscCorrectionSettings.Controls.Add(this.label31);
            this.groupBoxDscCorrectionSettings.Controls.Add(this.label32);
            this.groupBoxDscCorrectionSettings.Controls.Add(this.checkBoxDscReadErrCorrection);
            this.groupBoxDscCorrectionSettings.Location = new System.Drawing.Point(44, 45);
            this.groupBoxDscCorrectionSettings.Name = "groupBoxDscCorrectionSettings";
            this.groupBoxDscCorrectionSettings.Size = new System.Drawing.Size(342, 119);
            this.groupBoxDscCorrectionSettings.TabIndex = 14;
            this.groupBoxDscCorrectionSettings.TabStop = false;
            this.groupBoxDscCorrectionSettings.Text = "Read Errors Correction Settings";
            // 
            // numericUpDownDscSoftwareCount
            // 
            this.numericUpDownDscSoftwareCount.Location = new System.Drawing.Point(195, 77);
            this.numericUpDownDscSoftwareCount.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDownDscSoftwareCount.Name = "numericUpDownDscSoftwareCount";
            this.numericUpDownDscSoftwareCount.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownDscSoftwareCount.TabIndex = 4;
            // 
            // numericUpDownDscHardwareCount
            // 
            this.numericUpDownDscHardwareCount.Location = new System.Drawing.Point(195, 51);
            this.numericUpDownDscHardwareCount.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDownDscHardwareCount.Name = "numericUpDownDscHardwareCount";
            this.numericUpDownDscHardwareCount.Size = new System.Drawing.Size(57, 20);
            this.numericUpDownDscHardwareCount.TabIndex = 3;
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(69, 79);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(122, 13);
            this.label31.TabIndex = 2;
            this.label31.Text = "Software Retries Count :";
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(69, 53);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(126, 13);
            this.label32.TabIndex = 1;
            this.label32.Text = "Hardware Retries Count :";
            // 
            // checkBoxDscReadErrCorrection
            // 
            this.checkBoxDscReadErrCorrection.AutoSize = true;
            this.checkBoxDscReadErrCorrection.Checked = true;
            this.checkBoxDscReadErrCorrection.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxDscReadErrCorrection.Location = new System.Drawing.Point(30, 28);
            this.checkBoxDscReadErrCorrection.Name = "checkBoxDscReadErrCorrection";
            this.checkBoxDscReadErrCorrection.Size = new System.Drawing.Size(175, 17);
            this.checkBoxDscReadErrCorrection.TabIndex = 0;
            this.checkBoxDscReadErrCorrection.Text = "Read Errors Correction Enabled";
            this.checkBoxDscReadErrCorrection.UseVisualStyleBackColor = true;
            this.checkBoxDscReadErrCorrection.CheckedChanged += new System.EventHandler(this.checkBoxDscReadErrCorrection_CheckedChanged);
            // 
            // comboBoxDscSourceDev
            // 
            this.comboBoxDscSourceDev.FormattingEnabled = true;
            this.comboBoxDscSourceDev.Location = new System.Drawing.Point(129, 18);
            this.comboBoxDscSourceDev.Name = "comboBoxDscSourceDev";
            this.comboBoxDscSourceDev.Size = new System.Drawing.Size(421, 21);
            this.comboBoxDscSourceDev.TabIndex = 1;
            this.comboBoxDscSourceDev.SelectedIndexChanged += new System.EventHandler(this.comboBoxDscSourceDev_SelectedIndexChanged);
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(45, 21);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(78, 13);
            this.label25.TabIndex = 0;
            this.label25.Text = "Source Device";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(11, 104);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(43, 13);
            this.label12.TabIndex = 4;
            this.label12.Text = "Tracks:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(11, 81);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(52, 13);
            this.label13.TabIndex = 3;
            this.label13.Text = "Sessions:";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(11, 59);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(30, 13);
            this.label14.TabIndex = 2;
            this.label14.Text = "Last:";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(11, 37);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(40, 13);
            this.label15.TabIndex = 1;
            this.label15.Text = "Status:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(11, 15);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(47, 13);
            this.label16.TabIndex = 0;
            this.label16.Text = "Medium:";
            // 
            // UtilitiesSampleForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(630, 591);
            this.Controls.Add(this.TabControl);
            this.Controls.Add(this.deviceComboBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "UtilitiesSampleForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IsoSDK .NET Utilities Sample";
            this.Load += new System.EventHandler(this.UtilitiesSampleForm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.TabControl.ResumeLayout(false);
            this.tabPageDriveInfo.ResumeLayout(false);
            this.tabPageDriveInfo.PerformLayout();
            this.tabPageDriveInfoEx.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridDriveInfoEx)).EndInit();
            this.tabPageDriveCapabilities.ResumeLayout(false);
            this.tabPageDriveCapabilities.PerformLayout();
            this.groupBoxDriveCaps.ResumeLayout(false);
            this.groupBoxDriveCaps.PerformLayout();
            this.tabPageMediumInfo.ResumeLayout(false);
            this.tabPageMediumInfo.PerformLayout();
            this.tabPageImgCreation.ResumeLayout(false);
            this.tabPageImgCreation.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBoxProcessInfo.ResumeLayout(false);
            this.groupBoxProcessInfo.PerformLayout();
            this.groupBoxImgCorrectionSettings.ResumeLayout(false);
            this.groupBoxImgCorrectionSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownImgSoftwareCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownImgHardwareCount)).EndInit();
            this.tabPageDiscCopy.ResumeLayout(false);
            this.tabPageDiscCopy.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBoxDscProcessInfo.ResumeLayout(false);
            this.groupBoxDscProcessInfo.PerformLayout();
            this.groupBoxDscCorrectionSettings.ResumeLayout(false);
            this.groupBoxDscCorrectionSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDscSoftwareCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDscHardwareCount)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deviceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem isDeviceReadyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ejectTrayToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeTrayToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem getDriveInfoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getDriveInfoExToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getCapabilitiesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem setRegionCodeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem imagesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mountImageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem unmountImageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aSPISPTIToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem interfaceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem internalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem wnApsiToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem frogAspiToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox deviceComboBox;
        private System.Windows.Forms.ToolStripMenuItem rescanDevicesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem burnDevicesOnlyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem disableImagewriterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem informationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem webToolStripMenuItem;
        private System.Windows.Forms.TabControl TabControl;
        private System.Windows.Forms.TabPage tabPageDriveInfo;
        private System.Windows.Forms.TabPage tabPageDriveInfoEx;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lblDITestWrite;
        private System.Windows.Forms.Label lblDIUnderrunProtection;
        private System.Windows.Forms.Label lblDIMaxReadSpeed;
        private System.Windows.Forms.Label lblDIMaxSpeed;
        private System.Windows.Forms.Label lblDIDiskType;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DataGridView dataGridDriveInfoEx;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnParameter;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnValue;
        private System.Windows.Forms.TabPage tabPageDriveCapabilities;
        private System.Windows.Forms.GroupBox groupBoxDriveCaps;
        private System.Windows.Forms.CheckBox checkBoxReadDVDplusRW;
        private System.Windows.Forms.CheckBox checkBoxReadDVDplusR;
        private System.Windows.Forms.CheckBox checkBoxReadDVDRAM;
        private System.Windows.Forms.CheckBox checkBoxReadDVDRW;
        private System.Windows.Forms.CheckBox checkBoxReadDVDR;
        private System.Windows.Forms.CheckBox checkBoxReadDVD;
        private System.Windows.Forms.CheckBox checkBoxReadCDRW;
        private System.Windows.Forms.CheckBox checkBoxReadCDR;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.CheckBox checkBoxReadHDDVDROM;
        private System.Windows.Forms.CheckBox checkBoxReadHDDVDRW;
        private System.Windows.Forms.CheckBox checkBoxReadHDDVDR;
        private System.Windows.Forms.CheckBox checkBoxReadBLURAYROM;
        private System.Windows.Forms.CheckBox checkBoxReadBLURAYRE;
        private System.Windows.Forms.CheckBox checkBoxReadBLURAYR;
        private System.Windows.Forms.CheckBox checkBoxReadDVDMRDL;
        private System.Windows.Forms.CheckBox checkBoxReadDVDDL;
        private System.Windows.Forms.CheckBox checkBoxReadCDRWCav;
        private System.Windows.Forms.CheckBox checkBoxReadMountRainer;
        private System.Windows.Forms.CheckBox checkBoxReadDVDplusRWDL;
        private System.Windows.Forms.CheckBox checkBoxReadDVDplusRDL;
        private System.Windows.Forms.CheckBox checkBoxWriteCDRWCav;
        private System.Windows.Forms.CheckBox checkBoxWriteMountRainer;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDplusRWDL;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDplusRDL;
        private System.Windows.Forms.CheckBox checkBoxWriteHDDVDRW;
        private System.Windows.Forms.CheckBox checkBoxWriteHDDVDR;
        private System.Windows.Forms.CheckBox checkBoxWriteBLURAYRE;
        private System.Windows.Forms.CheckBox checkBoxWriteBLURAYR;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDMRDL;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDDL;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDplusRW;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDplusR;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDRAM;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDRW;
        private System.Windows.Forms.CheckBox checkBoxWriteDVDR;
        private System.Windows.Forms.CheckBox checkBoxWriteCDRW;
        private System.Windows.Forms.CheckBox checkBoxWriteCDR;
        private System.Windows.Forms.CheckBox checkBoxLayerJumpRecording;
        private System.Windows.Forms.CheckBox checkBoxDefectManagement;
        private System.Windows.Forms.CheckBox checkBoxBufferUnderrunProtection;
        private System.Windows.Forms.CheckBox checkBoxSMART;
        private System.Windows.Forms.CheckBox checkBoxStreaming;
        private System.Windows.Forms.CheckBox checkBoxMultisession;
        private System.Windows.Forms.CheckBox checkBoxCPRMAuth;
        private System.Windows.Forms.CheckBox checkBoxCanSimulateWrite;
        private System.Windows.Forms.TabPage tabPageMediumInfo;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label labelUpcEanCode;
        private System.Windows.Forms.Label labelFreeSpace;
        private System.Windows.Forms.Label labelUsedSpace;
        private System.Windows.Forms.Label labelSize;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label labelTracks;
        private System.Windows.Forms.Label labelSessions;
        private System.Windows.Forms.Label labelLast;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.Label labelMedium;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Button buttonTerminateLastSession;
        private System.Windows.Forms.ToolStripMenuItem mediumToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getDiskInfoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem eraseToolStripMenuItem;
        private System.Windows.Forms.Button buttonEject;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.TreeView treeViewMediumInfo;
        private System.Windows.Forms.TabPage tabPageImgCreation;
        private System.Windows.Forms.GroupBox groupBoxImgCorrectionSettings;
        private System.Windows.Forms.TextBox textBoxImgBadListPath;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.CheckBox checkBoxImgBadList;
        private System.Windows.Forms.CheckBox checkBoxImgBlankBad;
        private System.Windows.Forms.NumericUpDown numericUpDownImgSoftwareCount;
        private System.Windows.Forms.NumericUpDown numericUpDownImgHardwareCount;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.CheckBox checkBoxImgReadErrCorrection;
        private System.Windows.Forms.Button buttonImgBrowse;
        private System.Windows.Forms.TextBox textBoxImgDestPath;
        private System.Windows.Forms.ComboBox comboBoxImgFormat;
        private System.Windows.Forms.CheckBox checkBoxImgCreate;
        private System.Windows.Forms.Button buttonImgCheckFormat;
        private System.Windows.Forms.GroupBox groupBoxProcessInfo;
        private System.Windows.Forms.ProgressBar progressBarImg;
        private System.Windows.Forms.Button buttonImgCancel;
        private System.Windows.Forms.Label labelImgPercentage;
        private System.Windows.Forms.Label labelImgReadErr;
        private System.Windows.Forms.Label labelImgCurSec;
        private System.Windows.Forms.Label labelImgTtlSec;
        private System.Windows.Forms.Button buttonImgExecute;
        private System.Windows.Forms.CheckBox checkBoxImgVerify;
        private System.Windows.Forms.TabPage tabPageDiscCopy;
        private System.Windows.Forms.GroupBox groupBoxDscProcessInfo;
        private System.Windows.Forms.ProgressBar progressBarDsc;
        private System.Windows.Forms.Button buttonDscCancel;
        private System.Windows.Forms.Label labelDscPercentage;
        private System.Windows.Forms.Label labelDscBytesWritten;
        private System.Windows.Forms.Label labelDscTtlBytes;
        private System.Windows.Forms.GroupBox groupBoxDscCorrectionSettings;
        private System.Windows.Forms.NumericUpDown numericUpDownDscSoftwareCount;
        private System.Windows.Forms.NumericUpDown numericUpDownDscHardwareCount;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.CheckBox checkBoxDscReadErrCorrection;
        private System.Windows.Forms.ComboBox comboBoxDscSourceDev;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Button buttonDscCopy;
        private System.Windows.Forms.ComboBox comboBoxDscReadMode;
        private System.Windows.Forms.ComboBox comboBoxDscWriteMethod;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.CheckBox checkBoxDscVerify;
        private System.Windows.Forms.SaveFileDialog saveFileDialogImgDest;
        private System.Windows.Forms.CheckBox checkBoxDscEject;
        private System.Windows.Forms.CheckBox checkBoxCompositeAV;
        private System.Windows.Forms.CheckBox checkBoxAudioPlayback;
        private System.Windows.Forms.CheckBox checkBoxDP2;
        private System.Windows.Forms.CheckBox checkBoxDP1;
        private System.Windows.Forms.CheckBox checkBoxM2F1;
        private System.Windows.Forms.CheckBox checkBoxCCDAAS;
        private System.Windows.Forms.CheckBox checkBoxCDTWrite;
        private System.Windows.Forms.CheckBox checkBoxCDTRead;
        private System.Windows.Forms.CheckBox checkBoxMethod2;
        private System.Windows.Forms.CheckBox checkBoxRWSCinLI;
        private System.Windows.Forms.CheckBox checkBoxSideChange;
        private System.Windows.Forms.CheckBox checkBoxSSS;
        private System.Windows.Forms.CheckBox checkBoxDiscPresent;
        private System.Windows.Forms.CheckBox checkBoxSepMute;
        private System.Windows.Forms.CheckBox checkBoxEject;
        private System.Windows.Forms.CheckBox checkBoxPreventLockJumper;
        private System.Windows.Forms.CheckBox checkBoxSepVolumeLevels;
        private System.Windows.Forms.CheckBox checkBoxLockState;
        private System.Windows.Forms.CheckBox checkBoxLockingMedia;
        private System.Windows.Forms.CheckBox checkBoxBarcodeRead;
        private System.Windows.Forms.CheckBox checkBoxUPCRead;
        private System.Windows.Forms.CheckBox checkBoxISRCRead;
        private System.Windows.Forms.CheckBox checkBoxC2P;
        private System.Windows.Forms.CheckBox checkBoxRWSCDeint;
        private System.Windows.Forms.CheckBox checkBoxRWSCRead;
        private System.Windows.Forms.CheckBox checkBoxCDDAC;
        private System.Windows.Forms.CheckBox checkBoxM2F2;
        private System.Windows.Forms.CheckBox checkBoxPacketWrite;
        private System.Windows.Forms.CheckBox checkBoxDAO96Raw;
        private System.Windows.Forms.CheckBox checkBoxDAO96Pack;
        private System.Windows.Forms.CheckBox checkBoxDAO16;
        private System.Windows.Forms.CheckBox checkBoxDAORaw;
        private System.Windows.Forms.Label labelVendorID;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label labelMaxWriteSpeed;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.CheckBox checkBoxLightScribe;
        private System.Windows.Forms.CheckBox checkBoxLabelFlash;
        private System.Windows.Forms.CheckBox chkReadBDREXL;
        private System.Windows.Forms.CheckBox chkReadBDRXL;
        private System.Windows.Forms.CheckBox chkWriteBDREXL;
        private System.Windows.Forms.CheckBox chkWriteBDRXL;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Label lblVerifySector;
        private System.Windows.Forms.Label lblDscStatus;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label lblSectors;
        private System.Windows.Forms.CheckBox checkBoxDscAutoErase;
    }
}

