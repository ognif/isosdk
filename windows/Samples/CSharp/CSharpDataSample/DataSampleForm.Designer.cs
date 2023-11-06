namespace CSharpDataSample
{
    partial class DataSampleForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DataSampleForm));
            this.deviceComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.projectTypeComboBox = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.fileListView = new System.Windows.Forms.ListView();
            this.sizeProgressBar = new System.Windows.Forms.ProgressBar();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addFolderToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.addFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.renameFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteSelectedToolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.resetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.propertiesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.burnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.burnDevelopedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eraseToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ejectDiskToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.verifyAfterBurnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rockRidgeFileSystemToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.jolietFileSystemToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.finalizeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.AllowLowercaseNamesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.AllowManyDirectoriesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.AllowLongISO9660NamesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.AllowLongJolietNamesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ISOLevelComboBox = new System.Windows.Forms.ToolStripComboBox();
            this.additionalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.additionalISOHeaderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bootDiskSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importFromSessionToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.imagesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mountIMageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.unmountImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.burnDiskImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // deviceComboBox
            // 
            this.deviceComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.deviceComboBox.FormattingEnabled = true;
            this.deviceComboBox.Location = new System.Drawing.Point(74, 27);
            this.deviceComboBox.Name = "deviceComboBox";
            this.deviceComboBox.Size = new System.Drawing.Size(460, 21);
            this.deviceComboBox.TabIndex = 1;
            this.deviceComboBox.SelectedIndexChanged += new System.EventHandler(this.deviceComboBox_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Device:";
            // 
            // projectTypeComboBox
            // 
            this.projectTypeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.projectTypeComboBox.FormattingEnabled = true;
            this.projectTypeComboBox.Location = new System.Drawing.Point(84, 65);
            this.projectTypeComboBox.Name = "projectTypeComboBox";
            this.projectTypeComboBox.Size = new System.Drawing.Size(135, 21);
            this.projectTypeComboBox.TabIndex = 9;
            this.projectTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.projectTypeComboBox_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Project type:";
            // 
            // fileListView
            // 
            this.fileListView.FullRowSelect = true;
            this.fileListView.HideSelection = false;
            this.fileListView.Location = new System.Drawing.Point(12, 92);
            this.fileListView.MultiSelect = false;
            this.fileListView.Name = "fileListView";
            this.fileListView.Size = new System.Drawing.Size(532, 232);
            this.fileListView.TabIndex = 16;
            this.fileListView.UseCompatibleStateImageBehavior = false;
            this.fileListView.View = System.Windows.Forms.View.Details;
            this.fileListView.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.fileListView_ItemSelectionChanged);
            this.fileListView.DoubleClick += new System.EventHandler(this.fileListView_DoubleClick);
            // 
            // sizeProgressBar
            // 
            this.sizeProgressBar.Location = new System.Drawing.Point(15, 330);
            this.sizeProgressBar.Maximum = 750;
            this.sizeProgressBar.Name = "sizeProgressBar";
            this.sizeProgressBar.Size = new System.Drawing.Size(528, 23);
            this.sizeProgressBar.TabIndex = 19;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 357);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(32, 13);
            this.label3.TabIndex = 20;
            this.label3.Text = "0 MB";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(97, 357);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 13);
            this.label4.TabIndex = 21;
            this.label4.Text = "150 MB";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(203, 357);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 13);
            this.label5.TabIndex = 22;
            this.label5.Text = "300 MB";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(309, 357);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(44, 13);
            this.label6.TabIndex = 23;
            this.label6.Text = "450 MB";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(415, 357);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 13);
            this.label7.TabIndex = 24;
            this.label7.Text = "600 MB";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(521, 357);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 13);
            this.label8.TabIndex = 25;
            this.label8.Text = "750 MB";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addFileToolStripMenuItem,
            this.addFolderToolStripMenuItem2,
            this.addFolderToolStripMenuItem,
            this.renameFileToolStripMenuItem,
            this.deleteSelectedToolStripMenuItem3,
            this.resetToolStripMenuItem,
            this.propertiesToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem,
            this.toolStripMenuItem2});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // addFileToolStripMenuItem
            // 
            this.addFileToolStripMenuItem.Image = global::CSharpDataSample.Properties.Resources.addfile;
            this.addFileToolStripMenuItem.Name = "addFileToolStripMenuItem";
            this.addFileToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addFileToolStripMenuItem.Text = "Add File...";
            this.addFileToolStripMenuItem.Click += new System.EventHandler(this.addFileButton_Click);
            // 
            // addFolderToolStripMenuItem2
            // 
            this.addFolderToolStripMenuItem2.Image = ((System.Drawing.Image)(resources.GetObject("addFolderToolStripMenuItem2.Image")));
            this.addFolderToolStripMenuItem2.Name = "addFolderToolStripMenuItem2";
            this.addFolderToolStripMenuItem2.Size = new System.Drawing.Size(153, 22);
            this.addFolderToolStripMenuItem2.Text = "Add Folder...";
            this.addFolderToolStripMenuItem2.Click += new System.EventHandler(this.addFolderButton_Click);
            // 
            // addFolderToolStripMenuItem
            // 
            this.addFolderToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("addFolderToolStripMenuItem.Image")));
            this.addFolderToolStripMenuItem.Name = "addFolderToolStripMenuItem";
            this.addFolderToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addFolderToolStripMenuItem.Text = "Create Folder...";
            this.addFolderToolStripMenuItem.Click += new System.EventHandler(this.createDirButton_Click);
            // 
            // renameFileToolStripMenuItem
            // 
            this.renameFileToolStripMenuItem.Name = "renameFileToolStripMenuItem";
            this.renameFileToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.renameFileToolStripMenuItem.Text = "Rename File...";
            this.renameFileToolStripMenuItem.Click += new System.EventHandler(this.renameButton_Click);
            // 
            // deleteSelectedToolStripMenuItem3
            // 
            this.deleteSelectedToolStripMenuItem3.Image = global::CSharpDataSample.Properties.Resources.delete;
            this.deleteSelectedToolStripMenuItem3.Name = "deleteSelectedToolStripMenuItem3";
            this.deleteSelectedToolStripMenuItem3.Size = new System.Drawing.Size(153, 22);
            this.deleteSelectedToolStripMenuItem3.Text = "Delete selected";
            this.deleteSelectedToolStripMenuItem3.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // resetToolStripMenuItem
            // 
            this.resetToolStripMenuItem.Image = global::CSharpDataSample.Properties.Resources.reset;
            this.resetToolStripMenuItem.Name = "resetToolStripMenuItem";
            this.resetToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.resetToolStripMenuItem.Text = "Reset";
            this.resetToolStripMenuItem.Click += new System.EventHandler(this.resetButton_Click);
            // 
            // propertiesToolStripMenuItem
            // 
            this.propertiesToolStripMenuItem.Name = "propertiesToolStripMenuItem";
            this.propertiesToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.propertiesToolStripMenuItem.Text = "Properties...";
            this.propertiesToolStripMenuItem.Click += new System.EventHandler(this.propertiesToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(150, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Image = global::CSharpDataSample.Properties.Resources.cancel;
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(153, 22);
            // 
            // burnToolStripMenuItem
            // 
            this.burnToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.burnDevelopedToolStripMenuItem,
            this.eraseToolStripMenuItem2,
            this.toolStripSeparator2,
            this.optionsToolStripMenuItem});
            this.burnToolStripMenuItem.Name = "burnToolStripMenuItem";
            this.burnToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.burnToolStripMenuItem.Text = "&Burn";
            // 
            // burnDevelopedToolStripMenuItem
            // 
            this.burnDevelopedToolStripMenuItem.Image = global::CSharpDataSample.Properties.Resources.burn;
            this.burnDevelopedToolStripMenuItem.Name = "burnDevelopedToolStripMenuItem";
            this.burnDevelopedToolStripMenuItem.Size = new System.Drawing.Size(218, 26);
            this.burnDevelopedToolStripMenuItem.Text = "Burn with developed GUI...";
            this.burnDevelopedToolStripMenuItem.Click += new System.EventHandler(this.burnButton_Click);
            // 
            // eraseToolStripMenuItem2
            // 
            this.eraseToolStripMenuItem2.Image = global::CSharpDataSample.Properties.Resources.cd_erase;
            this.eraseToolStripMenuItem2.Name = "eraseToolStripMenuItem2";
            this.eraseToolStripMenuItem2.Size = new System.Drawing.Size(218, 26);
            this.eraseToolStripMenuItem2.Text = "Erase Disk...";
            this.eraseToolStripMenuItem2.Click += new System.EventHandler(this.eraseButton_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(215, 6);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ejectDiskToolStripMenuItem,
            this.verifyAfterBurnToolStripMenuItem,
            this.rockRidgeFileSystemToolStripMenuItem,
            this.jolietFileSystemToolStripMenuItem,
            this.finalizeToolStripMenuItem,
            this.toolStripSeparator3,
            this.AllowLowercaseNamesToolStripMenuItem,
            this.AllowManyDirectoriesToolStripMenuItem,
            this.AllowLongISO9660NamesToolStripMenuItem,
            this.AllowLongJolietNamesToolStripMenuItem,
            this.ISOLevelComboBox});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(218, 26);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // ejectDiskToolStripMenuItem
            // 
            this.ejectDiskToolStripMenuItem.Checked = true;
            this.ejectDiskToolStripMenuItem.CheckOnClick = true;
            this.ejectDiskToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ejectDiskToolStripMenuItem.Name = "ejectDiskToolStripMenuItem";
            this.ejectDiskToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.ejectDiskToolStripMenuItem.Text = "Eject Disk";
            // 
            // verifyAfterBurnToolStripMenuItem
            // 
            this.verifyAfterBurnToolStripMenuItem.Checked = true;
            this.verifyAfterBurnToolStripMenuItem.CheckOnClick = true;
            this.verifyAfterBurnToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.verifyAfterBurnToolStripMenuItem.Name = "verifyAfterBurnToolStripMenuItem";
            this.verifyAfterBurnToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.verifyAfterBurnToolStripMenuItem.Text = "Verify after burn";
            // 
            // rockRidgeFileSystemToolStripMenuItem
            // 
            this.rockRidgeFileSystemToolStripMenuItem.CheckOnClick = true;
            this.rockRidgeFileSystemToolStripMenuItem.Name = "rockRidgeFileSystemToolStripMenuItem";
            this.rockRidgeFileSystemToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.rockRidgeFileSystemToolStripMenuItem.Text = "Rock Ridge File System";
            // 
            // jolietFileSystemToolStripMenuItem
            // 
            this.jolietFileSystemToolStripMenuItem.Checked = true;
            this.jolietFileSystemToolStripMenuItem.CheckOnClick = true;
            this.jolietFileSystemToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.jolietFileSystemToolStripMenuItem.Name = "jolietFileSystemToolStripMenuItem";
            this.jolietFileSystemToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.jolietFileSystemToolStripMenuItem.Text = "Joliet File System";
            // 
            // finalizeToolStripMenuItem
            // 
            this.finalizeToolStripMenuItem.Checked = true;
            this.finalizeToolStripMenuItem.CheckOnClick = true;
            this.finalizeToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.finalizeToolStripMenuItem.Name = "finalizeToolStripMenuItem";
            this.finalizeToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.finalizeToolStripMenuItem.Text = "Finalize";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(219, 6);
            // 
            // AllowLowercaseNamesToolStripMenuItem
            // 
            this.AllowLowercaseNamesToolStripMenuItem.CheckOnClick = true;
            this.AllowLowercaseNamesToolStripMenuItem.Name = "AllowLowercaseNamesToolStripMenuItem";
            this.AllowLowercaseNamesToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.AllowLowercaseNamesToolStripMenuItem.Text = "Allow Lowercase Names";
            // 
            // AllowManyDirectoriesToolStripMenuItem
            // 
            this.AllowManyDirectoriesToolStripMenuItem.CheckOnClick = true;
            this.AllowManyDirectoriesToolStripMenuItem.Name = "AllowManyDirectoriesToolStripMenuItem";
            this.AllowManyDirectoriesToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.AllowManyDirectoriesToolStripMenuItem.Text = "Allow Many Directories";
            // 
            // AllowLongISO9660NamesToolStripMenuItem
            // 
            this.AllowLongISO9660NamesToolStripMenuItem.CheckOnClick = true;
            this.AllowLongISO9660NamesToolStripMenuItem.Name = "AllowLongISO9660NamesToolStripMenuItem";
            this.AllowLongISO9660NamesToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.AllowLongISO9660NamesToolStripMenuItem.Text = "Allow Long ISO 9660 Names";
            // 
            // AllowLongJolietNamesToolStripMenuItem
            // 
            this.AllowLongJolietNamesToolStripMenuItem.CheckOnClick = true;
            this.AllowLongJolietNamesToolStripMenuItem.Name = "AllowLongJolietNamesToolStripMenuItem";
            this.AllowLongJolietNamesToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.AllowLongJolietNamesToolStripMenuItem.Text = "Allow Long Joliet Names";
            // 
            // ISOLevelComboBox
            // 
            this.ISOLevelComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ISOLevelComboBox.Items.AddRange(new object[] {
            "ISO Level 1",
            "ISO Level 2",
            "ISO Level 3",
            "ISO Level Romeo"});
            this.ISOLevelComboBox.Name = "ISOLevelComboBox";
            this.ISOLevelComboBox.Size = new System.Drawing.Size(121, 23);
            // 
            // additionalToolStripMenuItem
            // 
            this.additionalToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.additionalISOHeaderToolStripMenuItem,
            this.bootDiskSettingsToolStripMenuItem,
            this.importFromSessionToolStripMenuItem1});
            this.additionalToolStripMenuItem.Name = "additionalToolStripMenuItem";
            this.additionalToolStripMenuItem.Size = new System.Drawing.Size(74, 20);
            this.additionalToolStripMenuItem.Text = "&Additional";
            // 
            // additionalISOHeaderToolStripMenuItem
            // 
            this.additionalISOHeaderToolStripMenuItem.Name = "additionalISOHeaderToolStripMenuItem";
            this.additionalISOHeaderToolStripMenuItem.Size = new System.Drawing.Size(200, 22);
            this.additionalISOHeaderToolStripMenuItem.Text = "Additional ISO Header...";
            this.additionalISOHeaderToolStripMenuItem.Click += new System.EventHandler(this.extendedHeaderToolStripMenuItem_Click);
            // 
            // bootDiskSettingsToolStripMenuItem
            // 
            this.bootDiskSettingsToolStripMenuItem.Name = "bootDiskSettingsToolStripMenuItem";
            this.bootDiskSettingsToolStripMenuItem.Size = new System.Drawing.Size(200, 22);
            this.bootDiskSettingsToolStripMenuItem.Text = "BootDisk Settings...";
            this.bootDiskSettingsToolStripMenuItem.Click += new System.EventHandler(this.bootToolStripMenuItem_Click);
            // 
            // importFromSessionToolStripMenuItem1
            // 
            this.importFromSessionToolStripMenuItem1.Name = "importFromSessionToolStripMenuItem1";
            this.importFromSessionToolStripMenuItem1.Size = new System.Drawing.Size(200, 22);
            this.importFromSessionToolStripMenuItem1.Text = "Import from Session...";
            this.importFromSessionToolStripMenuItem1.Click += new System.EventHandler(this.importFromSessionToolStripMenuItem_Click);
            // 
            // imagesToolStripMenuItem
            // 
            this.imagesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mountIMageToolStripMenuItem,
            this.unmountImageToolStripMenuItem,
            this.toolStripMenuItem1,
            this.burnDiskImageToolStripMenuItem});
            this.imagesToolStripMenuItem.Name = "imagesToolStripMenuItem";
            this.imagesToolStripMenuItem.Size = new System.Drawing.Size(57, 20);
            this.imagesToolStripMenuItem.Text = "&Images";
            // 
            // mountIMageToolStripMenuItem
            // 
            this.mountIMageToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("mountIMageToolStripMenuItem.Image")));
            this.mountIMageToolStripMenuItem.Name = "mountIMageToolStripMenuItem";
            this.mountIMageToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.mountIMageToolStripMenuItem.Text = "Mount image...";
            this.mountIMageToolStripMenuItem.Click += new System.EventHandler(this.mountIMageToolStripMenuItem_Click);
            // 
            // unmountImageToolStripMenuItem
            // 
            this.unmountImageToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("unmountImageToolStripMenuItem.Image")));
            this.unmountImageToolStripMenuItem.Name = "unmountImageToolStripMenuItem";
            this.unmountImageToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.unmountImageToolStripMenuItem.Text = "Unmount image";
            this.unmountImageToolStripMenuItem.Click += new System.EventHandler(this.unmountImageToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(158, 6);
            // 
            // burnDiskImageToolStripMenuItem
            // 
            this.burnDiskImageToolStripMenuItem.Image = global::CSharpDataSample.Properties.Resources.burn;
            this.burnDiskImageToolStripMenuItem.Name = "burnDiskImageToolStripMenuItem";
            this.burnDiskImageToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.burnDiskImageToolStripMenuItem.Text = "Burn Disk Image";
            this.burnDiskImageToolStripMenuItem.Click += new System.EventHandler(this.burnDiskImageToolStripMenuItem_Click);
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
            this.burnDevicesOnlyToolStripMenuItem.CheckStateChanged += new System.EventHandler(this.burnDevicesOnlyToolStripMenuItem_CheckStateChanged);
            // 
            // disableImagewriterToolStripMenuItem
            // 
            this.disableImagewriterToolStripMenuItem.CheckOnClick = true;
            this.disableImagewriterToolStripMenuItem.Name = "disableImagewriterToolStripMenuItem";
            this.disableImagewriterToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.disableImagewriterToolStripMenuItem.Text = "Disable Imagewriter";
            this.disableImagewriterToolStripMenuItem.CheckStateChanged += new System.EventHandler(this.disableImagewriterToolStripMenuItem_CheckStateChanged);
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
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.burnToolStripMenuItem,
            this.additionalToolStripMenuItem,
            this.imagesToolStripMenuItem,
            this.aSPISPTIToolStripMenuItem,
            this.informationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.menuStrip1.Size = new System.Drawing.Size(555, 24);
            this.menuStrip1.TabIndex = 17;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // DataSampleForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(555, 371);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.sizeProgressBar);
            this.Controls.Add(this.fileListView);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.projectTypeComboBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.deviceComboBox);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "DataSampleForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IsoSDK .NET Data Sample";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox deviceComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox projectTypeComboBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListView fileListView;
        private System.Windows.Forms.ProgressBar sizeProgressBar;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;        
        private System.Windows.Forms.ToolStripMenuItem addFolderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem renameFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteSelectedToolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem resetToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem burnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem burnDevelopedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem eraseToolStripMenuItem2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ejectDiskToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem verifyAfterBurnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem jolietFileSystemToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem finalizeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem additionalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem additionalISOHeaderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem bootDiskSettingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importFromSessionToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem imagesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mountIMageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem unmountImageToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem burnDiskImageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aSPISPTIToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem interfaceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem internalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem wnApsiToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem frogAspiToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem rescanDevicesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem burnDevicesOnlyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem disableImagewriterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem informationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem webToolStripMenuItem;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem addFolderToolStripMenuItem2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem AllowLowercaseNamesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem AllowManyDirectoriesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem rockRidgeFileSystemToolStripMenuItem;
        private System.Windows.Forms.ToolStripComboBox ISOLevelComboBox;
        private System.Windows.Forms.ToolStripMenuItem AllowLongISO9660NamesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem AllowLongJolietNamesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem addFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem propertiesToolStripMenuItem;
    }
}

