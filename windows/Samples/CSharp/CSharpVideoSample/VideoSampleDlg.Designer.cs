namespace CSharpVideoSample
{
    partial class VideoSampleDlg
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(VideoSampleDlg));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addVideoStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addPictureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteSelectedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.burnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.burnWithCustomDialogToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eraseDiskToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.ejectDiskToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.jolietFileSystemToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.label2 = new System.Windows.Forms.Label();
            this.projectTypeComboBox = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.sizeProgressBar = new System.Windows.Forms.ProgressBar();
            this.videoListView = new System.Windows.Forms.ListView();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageVideo = new System.Windows.Forms.TabPage();
            this.tabPagePictures = new System.Windows.Forms.TabPage();
            this.pictureListView = new System.Windows.Forms.ListView();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusProgress = new System.Windows.Forms.ToolStripProgressBar();
            this.menuStrip1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPageVideo.SuspendLayout();
            this.tabPagePictures.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.burnToolStripMenuItem,
            this.aSPISPTIToolStripMenuItem,
            this.informationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(564, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addVideoStripMenuItem,
            this.addPictureToolStripMenuItem,
            this.deleteSelectedToolStripMenuItem,
            this.resetToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // addVideoStripMenuItem
            // 
            this.addVideoStripMenuItem.Image = global::CSharpVideoSample.Properties.Resources.addvideo;
            this.addVideoStripMenuItem.Name = "addVideoStripMenuItem";
            this.addVideoStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addVideoStripMenuItem.Text = "Add Video...";
            this.addVideoStripMenuItem.Click += new System.EventHandler(this.AddFile);
            // 
            // addPictureToolStripMenuItem
            // 
            this.addPictureToolStripMenuItem.Image = global::CSharpVideoSample.Properties.Resources.addvideo;
            this.addPictureToolStripMenuItem.Name = "addPictureToolStripMenuItem";
            this.addPictureToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addPictureToolStripMenuItem.Text = "Add Picture...";
            this.addPictureToolStripMenuItem.Click += new System.EventHandler(this.AddFile);
            // 
            // deleteSelectedToolStripMenuItem
            // 
            this.deleteSelectedToolStripMenuItem.Image = global::CSharpVideoSample.Properties.Resources.delvideo;
            this.deleteSelectedToolStripMenuItem.Name = "deleteSelectedToolStripMenuItem";
            this.deleteSelectedToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.deleteSelectedToolStripMenuItem.Text = "Delete selected";
            this.deleteSelectedToolStripMenuItem.Click += new System.EventHandler(this.deleteSelectedToolStripMenuItem_Click);
            // 
            // resetToolStripMenuItem
            // 
            this.resetToolStripMenuItem.Image = global::CSharpVideoSample.Properties.Resources.reset;
            this.resetToolStripMenuItem.Name = "resetToolStripMenuItem";
            this.resetToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.resetToolStripMenuItem.Text = "Reset";
            this.resetToolStripMenuItem.Click += new System.EventHandler(this.resetToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(150, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Image = global::CSharpVideoSample.Properties.Resources.cancel;
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // burnToolStripMenuItem
            // 
            this.burnToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.burnWithCustomDialogToolStripMenuItem,
            this.eraseDiskToolStripMenuItem,
            this.toolStripSeparator2,
            this.toolStripMenuItem1});
            this.burnToolStripMenuItem.Name = "burnToolStripMenuItem";
            this.burnToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.burnToolStripMenuItem.Text = "&Burn";
            // 
            // burnWithCustomDialogToolStripMenuItem
            // 
            this.burnWithCustomDialogToolStripMenuItem.Image = global::CSharpVideoSample.Properties.Resources.burn;
            this.burnWithCustomDialogToolStripMenuItem.Name = "burnWithCustomDialogToolStripMenuItem";
            this.burnWithCustomDialogToolStripMenuItem.Size = new System.Drawing.Size(213, 22);
            this.burnWithCustomDialogToolStripMenuItem.Text = "&Burn with custom dialog...";
            this.burnWithCustomDialogToolStripMenuItem.Click += new System.EventHandler(this.burnWithCustomDialogToolStripMenuItem_Click);
            // 
            // eraseDiskToolStripMenuItem
            // 
            this.eraseDiskToolStripMenuItem.Image = global::CSharpVideoSample.Properties.Resources.erase;
            this.eraseDiskToolStripMenuItem.Name = "eraseDiskToolStripMenuItem";
            this.eraseDiskToolStripMenuItem.Size = new System.Drawing.Size(213, 22);
            this.eraseDiskToolStripMenuItem.Text = "&Erase Disk...";
            this.eraseDiskToolStripMenuItem.Click += new System.EventHandler(this.eraseDiskToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(210, 6);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ejectDiskToolStripMenuItem,
            this.jolietFileSystemToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(213, 22);
            this.toolStripMenuItem1.Text = "&Options";
            // 
            // ejectDiskToolStripMenuItem
            // 
            this.ejectDiskToolStripMenuItem.Checked = true;
            this.ejectDiskToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ejectDiskToolStripMenuItem.Name = "ejectDiskToolStripMenuItem";
            this.ejectDiskToolStripMenuItem.Size = new System.Drawing.Size(163, 22);
            this.ejectDiskToolStripMenuItem.Text = "&Eject Disk";
            // 
            // jolietFileSystemToolStripMenuItem
            // 
            this.jolietFileSystemToolStripMenuItem.Checked = true;
            this.jolietFileSystemToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.jolietFileSystemToolStripMenuItem.Name = "jolietFileSystemToolStripMenuItem";
            this.jolietFileSystemToolStripMenuItem.Size = new System.Drawing.Size(163, 22);
            this.jolietFileSystemToolStripMenuItem.Text = "&Joliet File System";
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
            this.internalToolStripMenuItem.Click += new System.EventHandler(this.AspiToolStripMenuItem_Click);
            // 
            // wnApsiToolStripMenuItem
            // 
            this.wnApsiToolStripMenuItem.Name = "wnApsiToolStripMenuItem";
            this.wnApsiToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.wnApsiToolStripMenuItem.Text = "WnApsi";
            this.wnApsiToolStripMenuItem.Click += new System.EventHandler(this.AspiToolStripMenuItem_Click);
            // 
            // frogAspiToolStripMenuItem
            // 
            this.frogAspiToolStripMenuItem.Name = "frogAspiToolStripMenuItem";
            this.frogAspiToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.frogAspiToolStripMenuItem.Text = "FrogAspi";
            this.frogAspiToolStripMenuItem.Click += new System.EventHandler(this.AspiToolStripMenuItem_Click);
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
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Device:";
            // 
            // deviceComboBox
            // 
            this.deviceComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.deviceComboBox.FormattingEnabled = true;
            this.deviceComboBox.Location = new System.Drawing.Point(115, 34);
            this.deviceComboBox.Name = "deviceComboBox";
            this.deviceComboBox.Size = new System.Drawing.Size(274, 21);
            this.deviceComboBox.TabIndex = 2;
            this.deviceComboBox.SelectedIndexChanged += new System.EventHandler(this.deviceComboBox_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(25, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Project type:";
            // 
            // projectTypeComboBox
            // 
            this.projectTypeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.projectTypeComboBox.FormattingEnabled = true;
            this.projectTypeComboBox.Items.AddRange(new object[] {
            "VCD",
            "SVCD"});
            this.projectTypeComboBox.Location = new System.Drawing.Point(115, 61);
            this.projectTypeComboBox.Name = "projectTypeComboBox";
            this.projectTypeComboBox.Size = new System.Drawing.Size(84, 21);
            this.projectTypeComboBox.TabIndex = 4;
            this.projectTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.projectTypeComboBox_SelectedIndexChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(518, 352);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 13);
            this.label8.TabIndex = 32;
            this.label8.Text = "750 MB";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(412, 352);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 13);
            this.label7.TabIndex = 31;
            this.label7.Text = "600 MB";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(306, 352);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(44, 13);
            this.label6.TabIndex = 30;
            this.label6.Text = "450 MB";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(200, 352);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 13);
            this.label5.TabIndex = 29;
            this.label5.Text = "300 MB";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(94, 352);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 13);
            this.label4.TabIndex = 28;
            this.label4.Text = "150 MB";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(0, 352);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(32, 13);
            this.label3.TabIndex = 27;
            this.label3.Text = "0 MB";
            // 
            // sizeProgressBar
            // 
            this.sizeProgressBar.Location = new System.Drawing.Point(12, 325);
            this.sizeProgressBar.Maximum = 750;
            this.sizeProgressBar.Name = "sizeProgressBar";
            this.sizeProgressBar.Size = new System.Drawing.Size(528, 23);
            this.sizeProgressBar.TabIndex = 26;
            // 
            // videoListView
            // 
            this.videoListView.FullRowSelect = true;
            this.videoListView.HideSelection = false;
            this.videoListView.Location = new System.Drawing.Point(6, 3);
            this.videoListView.Name = "videoListView";
            this.videoListView.Size = new System.Drawing.Size(511, 196);
            this.videoListView.TabIndex = 33;
            this.videoListView.UseCompatibleStateImageBehavior = false;
            this.videoListView.View = System.Windows.Forms.View.Details;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPageVideo);
            this.tabControl1.Controls.Add(this.tabPagePictures);
            this.tabControl1.Location = new System.Drawing.Point(12, 88);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(528, 231);
            this.tabControl1.TabIndex = 34;
            // 
            // tabPageVideo
            // 
            this.tabPageVideo.Controls.Add(this.videoListView);
            this.tabPageVideo.Location = new System.Drawing.Point(4, 22);
            this.tabPageVideo.Name = "tabPageVideo";
            this.tabPageVideo.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageVideo.Size = new System.Drawing.Size(520, 205);
            this.tabPageVideo.TabIndex = 0;
            this.tabPageVideo.Text = "Video";
            this.tabPageVideo.UseVisualStyleBackColor = true;
            // 
            // tabPagePictures
            // 
            this.tabPagePictures.Controls.Add(this.pictureListView);
            this.tabPagePictures.Location = new System.Drawing.Point(4, 22);
            this.tabPagePictures.Name = "tabPagePictures";
            this.tabPagePictures.Padding = new System.Windows.Forms.Padding(3);
            this.tabPagePictures.Size = new System.Drawing.Size(520, 205);
            this.tabPagePictures.TabIndex = 1;
            this.tabPagePictures.Text = "Pictures";
            this.tabPagePictures.UseVisualStyleBackColor = true;
            // 
            // pictureListView
            // 
            this.pictureListView.FullRowSelect = true;
            this.pictureListView.HideSelection = false;
            this.pictureListView.Location = new System.Drawing.Point(6, 3);
            this.pictureListView.Name = "pictureListView";
            this.pictureListView.Size = new System.Drawing.Size(511, 196);
            this.pictureListView.TabIndex = 34;
            this.pictureListView.UseCompatibleStateImageBehavior = false;
            this.pictureListView.View = System.Windows.Forms.View.Details;
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabel,
            this.statusProgress});
            this.statusStrip1.Location = new System.Drawing.Point(0, 373);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(564, 22);
            this.statusStrip1.TabIndex = 35;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(16, 17);
            this.statusLabel.Text = "   ";
            // 
            // statusProgress
            // 
            this.statusProgress.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.statusProgress.Name = "statusProgress";
            this.statusProgress.Size = new System.Drawing.Size(100, 16);
            this.statusProgress.Visible = false;
            // 
            // VideoSampleDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(564, 395);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.sizeProgressBar);
            this.Controls.Add(this.projectTypeComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.deviceComboBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "VideoSampleDlg";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IsoSDK .NET Video Sample";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPageVideo.ResumeLayout(false);
            this.tabPagePictures.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addPictureToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteSelectedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem burnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem burnWithCustomDialogToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem eraseDiskToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem ejectDiskToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem jolietFileSystemToolStripMenuItem;
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
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox deviceComboBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox projectTypeComboBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ProgressBar sizeProgressBar;
        private System.Windows.Forms.ListView videoListView;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageVideo;
        private System.Windows.Forms.TabPage tabPagePictures;
        private System.Windows.Forms.ToolStripMenuItem addVideoStripMenuItem;
        private System.Windows.Forms.ListView pictureListView;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.ToolStripProgressBar statusProgress;
    }
}

