namespace CSharpRawSample
{
    partial class RawSampleForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RawSampleForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tracksToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tryToToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.addTrackToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetTrackListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.burnDevelopedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eraseToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ejectDiskToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.verifyAfterBurnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.jolietFileSystemToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.finalizeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemAspiSpti = new System.Windows.Forms.ToolStripMenuItem();
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
            this.deviceComboBox = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonAnalyze = new System.Windows.Forms.Button();
            this.buttonBrowse = new System.Windows.Forms.Button();
            this.comboBoxAddFile = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.buttonDeleteTrack = new System.Windows.Forms.Button();
            this.buttonAddTrack = new System.Windows.Forms.Button();
            this.buttonResetForm = new System.Windows.Forms.Button();
            this.textBoxOffset = new System.Windows.Forms.TextBox();
            this.textBoxTrackLength = new System.Windows.Forms.TextBox();
            this.textBoxStartAddress = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.checkBoxIgnoreSubchRW = new System.Windows.Forms.CheckBox();
            this.checkBoxIgnoreData = new System.Windows.Forms.CheckBox();
            this.checkBoxIgnoreSubchPW = new System.Windows.Forms.CheckBox();
            this.checkBoxIgnoreSyncHeader = new System.Windows.Forms.CheckBox();
            this.checkBoxIgnoreSubchPQ = new System.Windows.Forms.CheckBox();
            this.checkBoxIgnoreSubHeaders = new System.Windows.Forms.CheckBox();
            this.checkBoxIgnoreEdcEcc = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.checkBoxSubchRW = new System.Windows.Forms.CheckBox();
            this.checkBoxSubchPW = new System.Windows.Forms.CheckBox();
            this.checkBoxSubchPQ = new System.Windows.Forms.CheckBox();
            this.checkBoxEdcEcc = new System.Windows.Forms.CheckBox();
            this.checkBoxData = new System.Windows.Forms.CheckBox();
            this.checkBoxSubHeaders = new System.Windows.Forms.CheckBox();
            this.checkBoxSyncHeader = new System.Windows.Forms.CheckBox();
            this.comboBoxTrackMode = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.numericUpDownTrackIndex = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.numericUpDownTrackNumber = new System.Windows.Forms.NumericUpDown();
            this.listViewTracks = new System.Windows.Forms.ListView();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTrackIndex)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTrackNumber)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.tracksToolStripMenuItem,
            this.toolStripMenuItem1,
            this.toolStripMenuItemAspiSpti,
            this.informationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(692, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addFileToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // addFileToolStripMenuItem
            // 
            this.addFileToolStripMenuItem.Image = global::CSharpRawSample.Properties.Resources.addfile;
            this.addFileToolStripMenuItem.Name = "addFileToolStripMenuItem";
            this.addFileToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.addFileToolStripMenuItem.Text = "&Add File";
            this.addFileToolStripMenuItem.Click += new System.EventHandler(this.addFileToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(114, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Image = global::CSharpRawSample.Properties.Resources.cancel;
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // tracksToolStripMenuItem
            // 
            this.tracksToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tryToToolStripMenuItem,
            this.toolStripSeparator3,
            this.addTrackToolStripMenuItem,
            this.resetTrackListToolStripMenuItem});
            this.tracksToolStripMenuItem.Name = "tracksToolStripMenuItem";
            this.tracksToolStripMenuItem.Size = new System.Drawing.Size(51, 20);
            this.tracksToolStripMenuItem.Text = "&Tracks";
            // 
            // tryToToolStripMenuItem
            // 
            this.tryToToolStripMenuItem.Name = "tryToToolStripMenuItem";
            this.tryToToolStripMenuItem.Size = new System.Drawing.Size(168, 22);
            this.tryToToolStripMenuItem.Text = "Try to Analyze &File";
            this.tryToToolStripMenuItem.Click += new System.EventHandler(this.tryToToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(165, 6);
            // 
            // addTrackToolStripMenuItem
            // 
            this.addTrackToolStripMenuItem.Name = "addTrackToolStripMenuItem";
            this.addTrackToolStripMenuItem.Size = new System.Drawing.Size(168, 22);
            this.addTrackToolStripMenuItem.Text = "&Add Track";
            this.addTrackToolStripMenuItem.Click += new System.EventHandler(this.addTrackToolStripMenuItem_Click);
            // 
            // resetTrackListToolStripMenuItem
            // 
            this.resetTrackListToolStripMenuItem.Name = "resetTrackListToolStripMenuItem";
            this.resetTrackListToolStripMenuItem.Size = new System.Drawing.Size(168, 22);
            this.resetTrackListToolStripMenuItem.Text = "&Reset  Tracklist";
            this.resetTrackListToolStripMenuItem.Click += new System.EventHandler(this.resetTrackListToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.burnDevelopedToolStripMenuItem,
            this.eraseToolStripMenuItem2,
            this.toolStripSeparator2,
            this.optionsToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(44, 20);
            this.toolStripMenuItem1.Text = "&Burn";
            // 
            // burnDevelopedToolStripMenuItem
            // 
            this.burnDevelopedToolStripMenuItem.Image = global::CSharpRawSample.Properties.Resources.burn_iso;
            this.burnDevelopedToolStripMenuItem.Name = "burnDevelopedToolStripMenuItem";
            this.burnDevelopedToolStripMenuItem.Size = new System.Drawing.Size(214, 22);
            this.burnDevelopedToolStripMenuItem.Text = "Burn with developed GUI...";
            this.burnDevelopedToolStripMenuItem.Click += new System.EventHandler(this.burnDevelopedToolStripMenuItem_Click);
            // 
            // eraseToolStripMenuItem2
            // 
            this.eraseToolStripMenuItem2.Image = global::CSharpRawSample.Properties.Resources.cd_erase;
            this.eraseToolStripMenuItem2.Name = "eraseToolStripMenuItem2";
            this.eraseToolStripMenuItem2.Size = new System.Drawing.Size(214, 22);
            this.eraseToolStripMenuItem2.Text = "Erase Disk...";
            this.eraseToolStripMenuItem2.Click += new System.EventHandler(this.eraseToolStripMenuItem2_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(211, 6);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ejectDiskToolStripMenuItem,
            this.verifyAfterBurnToolStripMenuItem,
            this.jolietFileSystemToolStripMenuItem,
            this.finalizeToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(214, 22);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // ejectDiskToolStripMenuItem
            // 
            this.ejectDiskToolStripMenuItem.Checked = true;
            this.ejectDiskToolStripMenuItem.CheckOnClick = true;
            this.ejectDiskToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ejectDiskToolStripMenuItem.Name = "ejectDiskToolStripMenuItem";
            this.ejectDiskToolStripMenuItem.Size = new System.Drawing.Size(163, 22);
            this.ejectDiskToolStripMenuItem.Text = "Eject Disk";
            // 
            // verifyAfterBurnToolStripMenuItem
            // 
            this.verifyAfterBurnToolStripMenuItem.CheckOnClick = true;
            this.verifyAfterBurnToolStripMenuItem.Name = "verifyAfterBurnToolStripMenuItem";
            this.verifyAfterBurnToolStripMenuItem.Size = new System.Drawing.Size(163, 22);
            this.verifyAfterBurnToolStripMenuItem.Text = "Verify after burn";
            // 
            // jolietFileSystemToolStripMenuItem
            // 
            this.jolietFileSystemToolStripMenuItem.Checked = true;
            this.jolietFileSystemToolStripMenuItem.CheckOnClick = true;
            this.jolietFileSystemToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.jolietFileSystemToolStripMenuItem.Name = "jolietFileSystemToolStripMenuItem";
            this.jolietFileSystemToolStripMenuItem.Size = new System.Drawing.Size(163, 22);
            this.jolietFileSystemToolStripMenuItem.Text = "Joliet File System";
            // 
            // finalizeToolStripMenuItem
            // 
            this.finalizeToolStripMenuItem.Checked = true;
            this.finalizeToolStripMenuItem.CheckOnClick = true;
            this.finalizeToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.finalizeToolStripMenuItem.Name = "finalizeToolStripMenuItem";
            this.finalizeToolStripMenuItem.Size = new System.Drawing.Size(163, 22);
            this.finalizeToolStripMenuItem.Text = "Finalize";
            // 
            // toolStripMenuItemAspiSpti
            // 
            this.toolStripMenuItemAspiSpti.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.interfaceToolStripMenuItem,
            this.rescanDevicesToolStripMenuItem,
            this.burnDevicesOnlyToolStripMenuItem,
            this.disableImagewriterToolStripMenuItem});
            this.toolStripMenuItemAspiSpti.Name = "toolStripMenuItemAspiSpti";
            this.toolStripMenuItemAspiSpti.Size = new System.Drawing.Size(70, 20);
            this.toolStripMenuItemAspiSpti.Text = "A&SPI/SPTI";
            // 
            // interfaceToolStripMenuItem
            // 
            this.interfaceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.internalToolStripMenuItem,
            this.wnApsiToolStripMenuItem,
            this.frogAspiToolStripMenuItem});
            this.interfaceToolStripMenuItem.Name = "interfaceToolStripMenuItem";
            this.interfaceToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.interfaceToolStripMenuItem.Text = "Interface";
            // 
            // internalToolStripMenuItem
            // 
            this.internalToolStripMenuItem.Name = "internalToolStripMenuItem";
            this.internalToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.internalToolStripMenuItem.Text = "Internal";
            this.internalToolStripMenuItem.Click += new System.EventHandler(this.internalToolStripMenuItem_Click);
            // 
            // wnApsiToolStripMenuItem
            // 
            this.wnApsiToolStripMenuItem.Name = "wnApsiToolStripMenuItem";
            this.wnApsiToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.wnApsiToolStripMenuItem.Text = "WnApsi";
            this.wnApsiToolStripMenuItem.Click += new System.EventHandler(this.wnApsiToolStripMenuItem_Click);
            // 
            // frogAspiToolStripMenuItem
            // 
            this.frogAspiToolStripMenuItem.Name = "frogAspiToolStripMenuItem";
            this.frogAspiToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.frogAspiToolStripMenuItem.Text = "FrogAspi";
            this.frogAspiToolStripMenuItem.Click += new System.EventHandler(this.frogAspiToolStripMenuItem_Click);
            // 
            // rescanDevicesToolStripMenuItem
            // 
            this.rescanDevicesToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("rescanDevicesToolStripMenuItem.Image")));
            this.rescanDevicesToolStripMenuItem.Name = "rescanDevicesToolStripMenuItem";
            this.rescanDevicesToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.rescanDevicesToolStripMenuItem.Text = "Rescan Devices";
            this.rescanDevicesToolStripMenuItem.Click += new System.EventHandler(this.rescanDevicesToolStripMenuItem_Click);
            // 
            // burnDevicesOnlyToolStripMenuItem
            // 
            this.burnDevicesOnlyToolStripMenuItem.Checked = true;
            this.burnDevicesOnlyToolStripMenuItem.CheckOnClick = true;
            this.burnDevicesOnlyToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.burnDevicesOnlyToolStripMenuItem.Name = "burnDevicesOnlyToolStripMenuItem";
            this.burnDevicesOnlyToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.burnDevicesOnlyToolStripMenuItem.Text = "Burn Devices Only";
            this.burnDevicesOnlyToolStripMenuItem.CheckedChanged += new System.EventHandler(this.burnDevicesOnlyToolStripMenuItem_CheckedChanged);
            // 
            // disableImagewriterToolStripMenuItem
            // 
            this.disableImagewriterToolStripMenuItem.CheckOnClick = true;
            this.disableImagewriterToolStripMenuItem.Name = "disableImagewriterToolStripMenuItem";
            this.disableImagewriterToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.disableImagewriterToolStripMenuItem.Text = "Disable Imagewriter";
            this.disableImagewriterToolStripMenuItem.CheckedChanged += new System.EventHandler(this.disableImagewriterToolStripMenuItem_CheckedChanged);
            // 
            // informationToolStripMenuItem
            // 
            this.informationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.webToolStripMenuItem});
            this.informationToolStripMenuItem.Name = "informationToolStripMenuItem";
            this.informationToolStripMenuItem.Size = new System.Drawing.Size(82, 20);
            this.informationToolStripMenuItem.Text = "&Information";
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
            // deviceComboBox
            // 
            this.deviceComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.deviceComboBox.FormattingEnabled = true;
            this.deviceComboBox.Location = new System.Drawing.Point(12, 19);
            this.deviceComboBox.Name = "deviceComboBox";
            this.deviceComboBox.Size = new System.Drawing.Size(253, 21);
            this.deviceComboBox.TabIndex = 5;
            this.deviceComboBox.SelectedIndexChanged += new System.EventHandler(this.deviceComboBox_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.deviceComboBox);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.Location = new System.Drawing.Point(0, 24);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(692, 45);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Devices";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonAnalyze);
            this.groupBox2.Controls.Add(this.buttonBrowse);
            this.groupBox2.Controls.Add(this.comboBoxAddFile);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox2.Location = new System.Drawing.Point(0, 69);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(692, 50);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Add File";
            // 
            // buttonAnalyze
            // 
            this.buttonAnalyze.Location = new System.Drawing.Point(572, 16);
            this.buttonAnalyze.Name = "buttonAnalyze";
            this.buttonAnalyze.Size = new System.Drawing.Size(106, 27);
            this.buttonAnalyze.TabIndex = 2;
            this.buttonAnalyze.Text = "Try to Analyze";
            this.buttonAnalyze.UseVisualStyleBackColor = true;
            this.buttonAnalyze.Click += new System.EventHandler(this.buttonAnalyze_Click);
            // 
            // buttonBrowse
            // 
            this.buttonBrowse.Location = new System.Drawing.Point(532, 18);
            this.buttonBrowse.Name = "buttonBrowse";
            this.buttonBrowse.Size = new System.Drawing.Size(34, 21);
            this.buttonBrowse.TabIndex = 1;
            this.buttonBrowse.Text = "...";
            this.buttonBrowse.UseVisualStyleBackColor = true;
            this.buttonBrowse.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // comboBoxAddFile
            // 
            this.comboBoxAddFile.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxAddFile.FormattingEnabled = true;
            this.comboBoxAddFile.Location = new System.Drawing.Point(15, 19);
            this.comboBoxAddFile.Name = "comboBoxAddFile";
            this.comboBoxAddFile.Size = new System.Drawing.Size(511, 21);
            this.comboBoxAddFile.TabIndex = 0;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.buttonDeleteTrack);
            this.groupBox3.Controls.Add(this.buttonAddTrack);
            this.groupBox3.Controls.Add(this.buttonResetForm);
            this.groupBox3.Controls.Add(this.textBoxOffset);
            this.groupBox3.Controls.Add(this.textBoxTrackLength);
            this.groupBox3.Controls.Add(this.textBoxStartAddress);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.panel2);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.panel1);
            this.groupBox3.Controls.Add(this.comboBoxTrackMode);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.numericUpDownTrackIndex);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.numericUpDownTrackNumber);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox3.Location = new System.Drawing.Point(0, 119);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(692, 373);
            this.groupBox3.TabIndex = 8;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Track Settings";
            // 
            // buttonDeleteTrack
            // 
            this.buttonDeleteTrack.Location = new System.Drawing.Point(486, 345);
            this.buttonDeleteTrack.Name = "buttonDeleteTrack";
            this.buttonDeleteTrack.Size = new System.Drawing.Size(94, 23);
            this.buttonDeleteTrack.TabIndex = 18;
            this.buttonDeleteTrack.Text = "&Delete Track";
            this.buttonDeleteTrack.UseVisualStyleBackColor = true;
            this.buttonDeleteTrack.Click += new System.EventHandler(this.buttonDeleteTrack_Click);
            // 
            // buttonAddTrack
            // 
            this.buttonAddTrack.Location = new System.Drawing.Point(586, 345);
            this.buttonAddTrack.Name = "buttonAddTrack";
            this.buttonAddTrack.Size = new System.Drawing.Size(94, 23);
            this.buttonAddTrack.TabIndex = 17;
            this.buttonAddTrack.Text = "&Add Track";
            this.buttonAddTrack.UseVisualStyleBackColor = true;
            this.buttonAddTrack.Click += new System.EventHandler(this.buttonAddTrack_Click);
            // 
            // buttonResetForm
            // 
            this.buttonResetForm.Location = new System.Drawing.Point(15, 345);
            this.buttonResetForm.Name = "buttonResetForm";
            this.buttonResetForm.Size = new System.Drawing.Size(86, 23);
            this.buttonResetForm.TabIndex = 16;
            this.buttonResetForm.Text = "Reset Form";
            this.buttonResetForm.UseVisualStyleBackColor = true;
            this.buttonResetForm.Click += new System.EventHandler(this.buttonResetForm_Click);
            // 
            // textBoxOffset
            // 
            this.textBoxOffset.Location = new System.Drawing.Point(131, 297);
            this.textBoxOffset.Name = "textBoxOffset";
            this.textBoxOffset.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.textBoxOffset.Size = new System.Drawing.Size(115, 20);
            this.textBoxOffset.TabIndex = 15;
            // 
            // textBoxTrackLength
            // 
            this.textBoxTrackLength.Location = new System.Drawing.Point(131, 274);
            this.textBoxTrackLength.Name = "textBoxTrackLength";
            this.textBoxTrackLength.Size = new System.Drawing.Size(115, 20);
            this.textBoxTrackLength.TabIndex = 14;
            // 
            // textBoxStartAddress
            // 
            this.textBoxStartAddress.Location = new System.Drawing.Point(131, 251);
            this.textBoxStartAddress.Name = "textBoxStartAddress";
            this.textBoxStartAddress.Size = new System.Drawing.Size(115, 20);
            this.textBoxStartAddress.TabIndex = 13;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 300);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(72, 13);
            this.label8.TabIndex = 12;
            this.label8.Text = "Offset (bytes):";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 277);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(117, 13);
            this.label7.TabIndex = 11;
            this.label7.Text = "Track Length (sectors):";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 254);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(116, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "Start Address (sectors):";
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel2.Controls.Add(this.checkBoxIgnoreSubchRW);
            this.panel2.Controls.Add(this.checkBoxIgnoreData);
            this.panel2.Controls.Add(this.checkBoxIgnoreSubchPW);
            this.panel2.Controls.Add(this.checkBoxIgnoreSyncHeader);
            this.panel2.Controls.Add(this.checkBoxIgnoreSubchPQ);
            this.panel2.Controls.Add(this.checkBoxIgnoreSubHeaders);
            this.panel2.Controls.Add(this.checkBoxIgnoreEdcEcc);
            this.panel2.Location = new System.Drawing.Point(457, 66);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(189, 170);
            this.panel2.TabIndex = 9;
            // 
            // checkBoxIgnoreSubchRW
            // 
            this.checkBoxIgnoreSubchRW.AutoSize = true;
            this.checkBoxIgnoreSubchRW.Location = new System.Drawing.Point(22, 144);
            this.checkBoxIgnoreSubchRW.Name = "checkBoxIgnoreSubchRW";
            this.checkBoxIgnoreSubchRW.Size = new System.Drawing.Size(137, 17);
            this.checkBoxIgnoreSubchRW.TabIndex = 13;
            this.checkBoxIgnoreSubchRW.Text = "BS_RDT_SUBCH_RW";
            this.checkBoxIgnoreSubchRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxIgnoreData
            // 
            this.checkBoxIgnoreData.AutoSize = true;
            this.checkBoxIgnoreData.Location = new System.Drawing.Point(22, 52);
            this.checkBoxIgnoreData.Name = "checkBoxIgnoreData";
            this.checkBoxIgnoreData.Size = new System.Drawing.Size(104, 17);
            this.checkBoxIgnoreData.TabIndex = 9;
            this.checkBoxIgnoreData.Text = "BS_RDT_DATA";
            this.checkBoxIgnoreData.UseVisualStyleBackColor = true;
            // 
            // checkBoxIgnoreSubchPW
            // 
            this.checkBoxIgnoreSubchPW.AutoSize = true;
            this.checkBoxIgnoreSubchPW.Location = new System.Drawing.Point(22, 121);
            this.checkBoxIgnoreSubchPW.Name = "checkBoxIgnoreSubchPW";
            this.checkBoxIgnoreSubchPW.Size = new System.Drawing.Size(136, 17);
            this.checkBoxIgnoreSubchPW.TabIndex = 12;
            this.checkBoxIgnoreSubchPW.Text = "BS_RDT_SUBCH_PW";
            this.checkBoxIgnoreSubchPW.UseVisualStyleBackColor = true;
            // 
            // checkBoxIgnoreSyncHeader
            // 
            this.checkBoxIgnoreSyncHeader.AutoSize = true;
            this.checkBoxIgnoreSyncHeader.Location = new System.Drawing.Point(22, 6);
            this.checkBoxIgnoreSyncHeader.Name = "checkBoxIgnoreSyncHeader";
            this.checkBoxIgnoreSyncHeader.Size = new System.Drawing.Size(155, 17);
            this.checkBoxIgnoreSyncHeader.TabIndex = 7;
            this.checkBoxIgnoreSyncHeader.Text = "BS_RDT_SYNC_HEADER";
            this.checkBoxIgnoreSyncHeader.UseVisualStyleBackColor = true;
            // 
            // checkBoxIgnoreSubchPQ
            // 
            this.checkBoxIgnoreSubchPQ.AutoSize = true;
            this.checkBoxIgnoreSubchPQ.Location = new System.Drawing.Point(22, 98);
            this.checkBoxIgnoreSubchPQ.Name = "checkBoxIgnoreSubchPQ";
            this.checkBoxIgnoreSubchPQ.Size = new System.Drawing.Size(133, 17);
            this.checkBoxIgnoreSubchPQ.TabIndex = 11;
            this.checkBoxIgnoreSubchPQ.Text = "BS_RDT_SUBCH_PQ";
            this.checkBoxIgnoreSubchPQ.UseVisualStyleBackColor = true;
            // 
            // checkBoxIgnoreSubHeaders
            // 
            this.checkBoxIgnoreSubHeaders.AutoSize = true;
            this.checkBoxIgnoreSubHeaders.Location = new System.Drawing.Point(22, 29);
            this.checkBoxIgnoreSubHeaders.Name = "checkBoxIgnoreSubHeaders";
            this.checkBoxIgnoreSubHeaders.Size = new System.Drawing.Size(149, 17);
            this.checkBoxIgnoreSubHeaders.TabIndex = 8;
            this.checkBoxIgnoreSubHeaders.Text = "BS_RDT_SUBHEADERS";
            this.checkBoxIgnoreSubHeaders.UseVisualStyleBackColor = true;
            // 
            // checkBoxIgnoreEdcEcc
            // 
            this.checkBoxIgnoreEdcEcc.AutoSize = true;
            this.checkBoxIgnoreEdcEcc.Location = new System.Drawing.Point(22, 75);
            this.checkBoxIgnoreEdcEcc.Name = "checkBoxIgnoreEdcEcc";
            this.checkBoxIgnoreEdcEcc.Size = new System.Drawing.Size(124, 17);
            this.checkBoxIgnoreEdcEcc.TabIndex = 10;
            this.checkBoxIgnoreEdcEcc.Text = "BS_RDT_EDC_ECC";
            this.checkBoxIgnoreEdcEcc.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(383, 66);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(68, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Ignore mask:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 66);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(81, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Datatype mask:";
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Controls.Add(this.checkBoxSubchRW);
            this.panel1.Controls.Add(this.checkBoxSubchPW);
            this.panel1.Controls.Add(this.checkBoxSubchPQ);
            this.panel1.Controls.Add(this.checkBoxEdcEcc);
            this.panel1.Controls.Add(this.checkBoxData);
            this.panel1.Controls.Add(this.checkBoxSubHeaders);
            this.panel1.Controls.Add(this.checkBoxSyncHeader);
            this.panel1.Location = new System.Drawing.Point(99, 66);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(189, 170);
            this.panel1.TabIndex = 6;
            // 
            // checkBoxSubchRW
            // 
            this.checkBoxSubchRW.AutoSize = true;
            this.checkBoxSubchRW.Location = new System.Drawing.Point(16, 144);
            this.checkBoxSubchRW.Name = "checkBoxSubchRW";
            this.checkBoxSubchRW.Size = new System.Drawing.Size(137, 17);
            this.checkBoxSubchRW.TabIndex = 6;
            this.checkBoxSubchRW.Text = "BS_RDT_SUBCH_RW";
            this.checkBoxSubchRW.UseVisualStyleBackColor = true;
            // 
            // checkBoxSubchPW
            // 
            this.checkBoxSubchPW.AutoSize = true;
            this.checkBoxSubchPW.Location = new System.Drawing.Point(16, 121);
            this.checkBoxSubchPW.Name = "checkBoxSubchPW";
            this.checkBoxSubchPW.Size = new System.Drawing.Size(136, 17);
            this.checkBoxSubchPW.TabIndex = 5;
            this.checkBoxSubchPW.Text = "BS_RDT_SUBCH_PW";
            this.checkBoxSubchPW.UseVisualStyleBackColor = true;
            // 
            // checkBoxSubchPQ
            // 
            this.checkBoxSubchPQ.AutoSize = true;
            this.checkBoxSubchPQ.Location = new System.Drawing.Point(16, 98);
            this.checkBoxSubchPQ.Name = "checkBoxSubchPQ";
            this.checkBoxSubchPQ.Size = new System.Drawing.Size(133, 17);
            this.checkBoxSubchPQ.TabIndex = 4;
            this.checkBoxSubchPQ.Text = "BS_RDT_SUBCH_PQ";
            this.checkBoxSubchPQ.UseVisualStyleBackColor = true;
            // 
            // checkBoxEdcEcc
            // 
            this.checkBoxEdcEcc.AutoSize = true;
            this.checkBoxEdcEcc.Location = new System.Drawing.Point(16, 75);
            this.checkBoxEdcEcc.Name = "checkBoxEdcEcc";
            this.checkBoxEdcEcc.Size = new System.Drawing.Size(124, 17);
            this.checkBoxEdcEcc.TabIndex = 3;
            this.checkBoxEdcEcc.Text = "BS_RDT_EDC_ECC";
            this.checkBoxEdcEcc.UseVisualStyleBackColor = true;
            // 
            // checkBoxData
            // 
            this.checkBoxData.AutoSize = true;
            this.checkBoxData.Location = new System.Drawing.Point(16, 52);
            this.checkBoxData.Name = "checkBoxData";
            this.checkBoxData.Size = new System.Drawing.Size(104, 17);
            this.checkBoxData.TabIndex = 2;
            this.checkBoxData.Text = "BS_RDT_DATA";
            this.checkBoxData.UseVisualStyleBackColor = true;
            // 
            // checkBoxSubHeaders
            // 
            this.checkBoxSubHeaders.AutoSize = true;
            this.checkBoxSubHeaders.Location = new System.Drawing.Point(16, 29);
            this.checkBoxSubHeaders.Name = "checkBoxSubHeaders";
            this.checkBoxSubHeaders.Size = new System.Drawing.Size(149, 17);
            this.checkBoxSubHeaders.TabIndex = 1;
            this.checkBoxSubHeaders.Text = "BS_RDT_SUBHEADERS";
            this.checkBoxSubHeaders.UseVisualStyleBackColor = true;
            // 
            // checkBoxSyncHeader
            // 
            this.checkBoxSyncHeader.AutoSize = true;
            this.checkBoxSyncHeader.Location = new System.Drawing.Point(16, 6);
            this.checkBoxSyncHeader.Name = "checkBoxSyncHeader";
            this.checkBoxSyncHeader.Size = new System.Drawing.Size(155, 17);
            this.checkBoxSyncHeader.TabIndex = 0;
            this.checkBoxSyncHeader.Text = "BS_RDT_SYNC_HEADER";
            this.checkBoxSyncHeader.UseVisualStyleBackColor = true;
            // 
            // comboBoxTrackMode
            // 
            this.comboBoxTrackMode.FormattingEnabled = true;
            this.comboBoxTrackMode.Location = new System.Drawing.Point(470, 22);
            this.comboBoxTrackMode.Name = "comboBoxTrackMode";
            this.comboBoxTrackMode.Size = new System.Drawing.Size(194, 21);
            this.comboBoxTrackMode.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(396, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(68, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Track Mode:";
            // 
            // numericUpDownTrackIndex
            // 
            this.numericUpDownTrackIndex.Location = new System.Drawing.Point(315, 23);
            this.numericUpDownTrackIndex.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownTrackIndex.Name = "numericUpDownTrackIndex";
            this.numericUpDownTrackIndex.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownTrackIndex.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(152, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(157, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Track Index (0-pregap, 1-track):";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(78, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Track Number:";
            // 
            // numericUpDownTrackNumber
            // 
            this.numericUpDownTrackNumber.Location = new System.Drawing.Point(96, 23);
            this.numericUpDownTrackNumber.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.numericUpDownTrackNumber.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownTrackNumber.Name = "numericUpDownTrackNumber";
            this.numericUpDownTrackNumber.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownTrackNumber.TabIndex = 0;
            this.numericUpDownTrackNumber.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // listViewTracks
            // 
            this.listViewTracks.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.listViewTracks.FullRowSelect = true;
            this.listViewTracks.HideSelection = false;
            this.listViewTracks.Location = new System.Drawing.Point(0, 498);
            this.listViewTracks.Name = "listViewTracks";
            this.listViewTracks.Size = new System.Drawing.Size(692, 96);
            this.listViewTracks.TabIndex = 9;
            this.listViewTracks.UseCompatibleStateImageBehavior = false;
            this.listViewTracks.View = System.Windows.Forms.View.Details;
            this.listViewTracks.SelectedIndexChanged += new System.EventHandler(this.listViewTracks_SelectedIndexChanged);
            // 
            // RawSampleForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(692, 594);
            this.Controls.Add(this.listViewTracks);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "RawSampleForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IsoSDK .NET Raw Sample";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTrackIndex)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTrackNumber)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tracksToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem informationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem webToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemAspiSpti;
        private System.Windows.Forms.ToolStripMenuItem interfaceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem internalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem wnApsiToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem frogAspiToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem rescanDevicesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem burnDevicesOnlyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem disableImagewriterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem burnDevelopedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem eraseToolStripMenuItem2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ejectDiskToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem verifyAfterBurnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem jolietFileSystemToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem finalizeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tryToToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem addTrackToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetTrackListToolStripMenuItem;
        private System.Windows.Forms.ComboBox deviceComboBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonAnalyze;
        private System.Windows.Forms.Button buttonBrowse;
        private System.Windows.Forms.ComboBox comboBoxAddFile;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ListView listViewTracks;
        private System.Windows.Forms.NumericUpDown numericUpDownTrackIndex;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDownTrackNumber;
        private System.Windows.Forms.ComboBox comboBoxTrackMode;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.CheckBox checkBoxSubchRW;
        private System.Windows.Forms.CheckBox checkBoxSubchPW;
        private System.Windows.Forms.CheckBox checkBoxSubchPQ;
        private System.Windows.Forms.CheckBox checkBoxEdcEcc;
        private System.Windows.Forms.CheckBox checkBoxData;
        private System.Windows.Forms.CheckBox checkBoxSubHeaders;
        private System.Windows.Forms.CheckBox checkBoxSyncHeader;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.CheckBox checkBoxIgnoreSubchRW;
        private System.Windows.Forms.CheckBox checkBoxIgnoreData;
        private System.Windows.Forms.CheckBox checkBoxIgnoreSubchPW;
        private System.Windows.Forms.CheckBox checkBoxIgnoreSyncHeader;
        private System.Windows.Forms.CheckBox checkBoxIgnoreSubchPQ;
        private System.Windows.Forms.CheckBox checkBoxIgnoreSubHeaders;
        private System.Windows.Forms.CheckBox checkBoxIgnoreEdcEcc;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button buttonDeleteTrack;
        private System.Windows.Forms.Button buttonAddTrack;
        private System.Windows.Forms.Button buttonResetForm;
        private System.Windows.Forms.TextBox textBoxOffset;
        private System.Windows.Forms.TextBox textBoxTrackLength;
        private System.Windows.Forms.TextBox textBoxStartAddress;
    }
}

