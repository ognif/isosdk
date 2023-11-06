namespace CSharpImageEditSample
{
    partial class ImageEditForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ImageEditForm));
            this.treeViewLeftPanel = new System.Windows.Forms.TreeView();
            this.imageListIcons = new System.Windows.Forms.ImageList();
            this.listViewRightPanel = new System.Windows.Forms.ListView();
            this.columnHeaderName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeaderLba = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeaderSize = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeaderModified = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.discToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.verifyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mountToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.unmountToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.makeMd5ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.checkMd5ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.audioToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.playSelectedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.grabAllTracksToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.comboBoxDevices = new System.Windows.Forms.ComboBox();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.buttonOpenImage = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // treeViewLeftPanel
            // 
            this.treeViewLeftPanel.ImageIndex = 0;
            this.treeViewLeftPanel.ImageList = this.imageListIcons;
            this.treeViewLeftPanel.Location = new System.Drawing.Point(0, 66);
            this.treeViewLeftPanel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.treeViewLeftPanel.Name = "treeViewLeftPanel";
            this.treeViewLeftPanel.SelectedImageIndex = 0;
            this.treeViewLeftPanel.Size = new System.Drawing.Size(307, 527);
            this.treeViewLeftPanel.TabIndex = 0;
            this.treeViewLeftPanel.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewLeftPanel_AfterSelect);
            this.treeViewLeftPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.treeViewLeftPanel_MouseUp);
            // 
            // imageListIcons
            // 
            this.imageListIcons.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListIcons.ImageStream")));
            this.imageListIcons.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListIcons.Images.SetKeyName(0, "burn_iso.png");
            this.imageListIcons.Images.SetKeyName(1, "burn_iso.png");
            this.imageListIcons.Images.SetKeyName(2, "audio.png");
            this.imageListIcons.Images.SetKeyName(3, "audio.png");
            this.imageListIcons.Images.SetKeyName(4, "iso.png");
            this.imageListIcons.Images.SetKeyName(5, "iso.png");
            this.imageListIcons.Images.SetKeyName(6, "closed_folder.png");
            this.imageListIcons.Images.SetKeyName(7, "open_folder.png");
            this.imageListIcons.Images.SetKeyName(8, "minidoc.png");
            this.imageListIcons.Images.SetKeyName(9, "minidoc.png");
            // 
            // listViewRightPanel
            // 
            this.listViewRightPanel.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderName,
            this.columnHeaderLba,
            this.columnHeaderSize,
            this.columnHeaderModified});
            this.listViewRightPanel.FullRowSelect = true;
            this.listViewRightPanel.Location = new System.Drawing.Point(312, 66);
            this.listViewRightPanel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.listViewRightPanel.Name = "listViewRightPanel";
            this.listViewRightPanel.Size = new System.Drawing.Size(548, 527);
            this.listViewRightPanel.SmallImageList = this.imageListIcons;
            this.listViewRightPanel.TabIndex = 1;
            this.listViewRightPanel.UseCompatibleStateImageBehavior = false;
            this.listViewRightPanel.View = System.Windows.Forms.View.Details;
            this.listViewRightPanel.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listViewRightPanel_MouseDoubleClick);
            this.listViewRightPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.listViewRightPanel_MouseUp);
            // 
            // columnHeaderName
            // 
            this.columnHeaderName.Text = "Name";
            // 
            // columnHeaderLba
            // 
            this.columnHeaderLba.Text = "LBA";
            // 
            // columnHeaderSize
            // 
            this.columnHeaderSize.Text = "Size";
            // 
            // columnHeaderModified
            // 
            this.columnHeaderModified.Text = "Modified";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.discToolStripMenuItem,
            this.imageToolStripMenuItem,
            this.audioToolStripMenuItem,
            this.toolStripMenuItemAspiSpti,
            this.informationToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(8, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(847, 28);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // discToolStripMenuItem
            // 
            this.discToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.verifyToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.discToolStripMenuItem.Name = "discToolStripMenuItem";
            this.discToolStripMenuItem.Size = new System.Drawing.Size(49, 24);
            this.discToolStripMenuItem.Text = "&Disc";
            // 
            // verifyToolStripMenuItem
            // 
            this.verifyToolStripMenuItem.Name = "verifyToolStripMenuItem";
            this.verifyToolStripMenuItem.Size = new System.Drawing.Size(177, 26);
            this.verifyToolStripMenuItem.Text = "&Verify";
            this.verifyToolStripMenuItem.Click += new System.EventHandler(this.verifyToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(177, 26);
            this.saveToolStripMenuItem.Text = "&Save in image";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(174, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("exitToolStripMenuItem.Image")));
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(177, 26);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // imageToolStripMenuItem
            // 
            this.imageToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mountToolStripMenuItem,
            this.unmountToolStripMenuItem,
            this.toolStripSeparator2,
            this.makeMd5ToolStripMenuItem,
            this.checkMd5ToolStripMenuItem});
            this.imageToolStripMenuItem.Name = "imageToolStripMenuItem";
            this.imageToolStripMenuItem.Size = new System.Drawing.Size(63, 24);
            this.imageToolStripMenuItem.Text = "&Image";
            // 
            // mountToolStripMenuItem
            // 
            this.mountToolStripMenuItem.Name = "mountToolStripMenuItem";
            this.mountToolStripMenuItem.Size = new System.Drawing.Size(228, 26);
            this.mountToolStripMenuItem.Text = "&Mount image...";
            this.mountToolStripMenuItem.Click += new System.EventHandler(this.mountToolStripMenuItem_Click);
            // 
            // unmountToolStripMenuItem
            // 
            this.unmountToolStripMenuItem.Name = "unmountToolStripMenuItem";
            this.unmountToolStripMenuItem.Size = new System.Drawing.Size(228, 26);
            this.unmountToolStripMenuItem.Text = "&Unmount image";
            this.unmountToolStripMenuItem.Click += new System.EventHandler(this.unmountToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(225, 6);
            // 
            // makeMd5ToolStripMenuItem
            // 
            this.makeMd5ToolStripMenuItem.Name = "makeMd5ToolStripMenuItem";
            this.makeMd5ToolStripMenuItem.Size = new System.Drawing.Size(228, 26);
            this.makeMd5ToolStripMenuItem.Text = "M&ake MD5 for image";
            this.makeMd5ToolStripMenuItem.Click += new System.EventHandler(this.makeMd5ToolStripMenuItem_Click);
            // 
            // checkMd5ToolStripMenuItem
            // 
            this.checkMd5ToolStripMenuItem.Name = "checkMd5ToolStripMenuItem";
            this.checkMd5ToolStripMenuItem.Size = new System.Drawing.Size(228, 26);
            this.checkMd5ToolStripMenuItem.Text = "&Check MD5 for image";
            this.checkMd5ToolStripMenuItem.Click += new System.EventHandler(this.checkMd5ToolStripMenuItem_Click);
            // 
            // audioToolStripMenuItem
            // 
            this.audioToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.playSelectedToolStripMenuItem,
            this.grabAllTracksToolStripMenuItem});
            this.audioToolStripMenuItem.Name = "audioToolStripMenuItem";
            this.audioToolStripMenuItem.Size = new System.Drawing.Size(61, 24);
            this.audioToolStripMenuItem.Text = "&Audio";
            // 
            // playSelectedToolStripMenuItem
            // 
            this.playSelectedToolStripMenuItem.Image = global::CSharpImageEditSample.Properties.Resources.play;
            this.playSelectedToolStripMenuItem.Name = "playSelectedToolStripMenuItem";
            this.playSelectedToolStripMenuItem.Size = new System.Drawing.Size(178, 26);
            this.playSelectedToolStripMenuItem.Text = "Play selected";
            this.playSelectedToolStripMenuItem.Click += new System.EventHandler(this.OnPlay);
            // 
            // grabAllTracksToolStripMenuItem
            // 
            this.grabAllTracksToolStripMenuItem.Name = "grabAllTracksToolStripMenuItem";
            this.grabAllTracksToolStripMenuItem.Size = new System.Drawing.Size(178, 26);
            this.grabAllTracksToolStripMenuItem.Text = "Grab all tracks";
            this.grabAllTracksToolStripMenuItem.Click += new System.EventHandler(this.grabAllTracksToolStripMenuItem_Click);
            // 
            // toolStripMenuItemAspiSpti
            // 
            this.toolStripMenuItemAspiSpti.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.interfaceToolStripMenuItem,
            this.rescanDevicesToolStripMenuItem,
            this.burnDevicesOnlyToolStripMenuItem,
            this.disableImagewriterToolStripMenuItem});
            this.toolStripMenuItemAspiSpti.Name = "toolStripMenuItemAspiSpti";
            this.toolStripMenuItemAspiSpti.Size = new System.Drawing.Size(85, 24);
            this.toolStripMenuItemAspiSpti.Text = "A&SPI/SPTI";
            // 
            // interfaceToolStripMenuItem
            // 
            this.interfaceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.internalToolStripMenuItem,
            this.wnApsiToolStripMenuItem,
            this.frogAspiToolStripMenuItem});
            this.interfaceToolStripMenuItem.Name = "interfaceToolStripMenuItem";
            this.interfaceToolStripMenuItem.Size = new System.Drawing.Size(218, 26);
            this.interfaceToolStripMenuItem.Text = "Interface";
            // 
            // internalToolStripMenuItem
            // 
            this.internalToolStripMenuItem.Name = "internalToolStripMenuItem";
            this.internalToolStripMenuItem.Size = new System.Drawing.Size(143, 26);
            this.internalToolStripMenuItem.Text = "Internal";
            this.internalToolStripMenuItem.Click += new System.EventHandler(this.internalToolStripMenuItem_Click);
            // 
            // wnApsiToolStripMenuItem
            // 
            this.wnApsiToolStripMenuItem.Name = "wnApsiToolStripMenuItem";
            this.wnApsiToolStripMenuItem.Size = new System.Drawing.Size(143, 26);
            this.wnApsiToolStripMenuItem.Text = "WnApsi";
            this.wnApsiToolStripMenuItem.Click += new System.EventHandler(this.wnApsiToolStripMenuItem_Click);
            // 
            // frogAspiToolStripMenuItem
            // 
            this.frogAspiToolStripMenuItem.Name = "frogAspiToolStripMenuItem";
            this.frogAspiToolStripMenuItem.Size = new System.Drawing.Size(143, 26);
            this.frogAspiToolStripMenuItem.Text = "FrogAspi";
            this.frogAspiToolStripMenuItem.Click += new System.EventHandler(this.frogAspiToolStripMenuItem_Click);
            // 
            // rescanDevicesToolStripMenuItem
            // 
            this.rescanDevicesToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("rescanDevicesToolStripMenuItem.Image")));
            this.rescanDevicesToolStripMenuItem.Name = "rescanDevicesToolStripMenuItem";
            this.rescanDevicesToolStripMenuItem.Size = new System.Drawing.Size(218, 26);
            this.rescanDevicesToolStripMenuItem.Text = "Rescan Devices";
            this.rescanDevicesToolStripMenuItem.Click += new System.EventHandler(this.rescanDevicesToolStripMenuItem_Click);
            // 
            // burnDevicesOnlyToolStripMenuItem
            // 
            this.burnDevicesOnlyToolStripMenuItem.CheckOnClick = true;
            this.burnDevicesOnlyToolStripMenuItem.Name = "burnDevicesOnlyToolStripMenuItem";
            this.burnDevicesOnlyToolStripMenuItem.Size = new System.Drawing.Size(218, 26);
            this.burnDevicesOnlyToolStripMenuItem.Text = "Burn Devices Only";
            this.burnDevicesOnlyToolStripMenuItem.CheckedChanged += new System.EventHandler(this.burnDevicesOnlyToolStripMenuItem_CheckedChanged);
            // 
            // disableImagewriterToolStripMenuItem
            // 
            this.disableImagewriterToolStripMenuItem.CheckOnClick = true;
            this.disableImagewriterToolStripMenuItem.Name = "disableImagewriterToolStripMenuItem";
            this.disableImagewriterToolStripMenuItem.Size = new System.Drawing.Size(218, 26);
            this.disableImagewriterToolStripMenuItem.Text = "Disable Imagewriter";
            this.disableImagewriterToolStripMenuItem.CheckedChanged += new System.EventHandler(this.disableImagewriterToolStripMenuItem_CheckedChanged);
            // 
            // informationToolStripMenuItem
            // 
            this.informationToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.webToolStripMenuItem});
            this.informationToolStripMenuItem.Name = "informationToolStripMenuItem";
            this.informationToolStripMenuItem.Size = new System.Drawing.Size(99, 24);
            this.informationToolStripMenuItem.Text = "I&nformation";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(125, 26);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // webToolStripMenuItem
            // 
            this.webToolStripMenuItem.Name = "webToolStripMenuItem";
            this.webToolStripMenuItem.Size = new System.Drawing.Size(125, 26);
            this.webToolStripMenuItem.Text = "Web";
            this.webToolStripMenuItem.Click += new System.EventHandler(this.webToolStripMenuItem_Click);
            // 
            // comboBoxDevices
            // 
            this.comboBoxDevices.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDevices.FormattingEnabled = true;
            this.comboBoxDevices.Location = new System.Drawing.Point(0, 33);
            this.comboBoxDevices.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.comboBoxDevices.Name = "comboBoxDevices";
            this.comboBoxDevices.Size = new System.Drawing.Size(307, 24);
            this.comboBoxDevices.TabIndex = 4;
            this.comboBoxDevices.SelectedIndexChanged += new System.EventHandler(this.comboBoxDevices_SelectedIndexChanged);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(316, 31);
            this.buttonRefresh.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(100, 28);
            this.buttonRefresh.TabIndex = 5;
            this.buttonRefresh.Text = "Refresh";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // buttonOpenImage
            // 
            this.buttonOpenImage.Location = new System.Drawing.Point(424, 31);
            this.buttonOpenImage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonOpenImage.Name = "buttonOpenImage";
            this.buttonOpenImage.Size = new System.Drawing.Size(116, 28);
            this.buttonOpenImage.TabIndex = 6;
            this.buttonOpenImage.Text = "Open Image...";
            this.buttonOpenImage.UseVisualStyleBackColor = true;
            this.buttonOpenImage.Click += new System.EventHandler(this.mountToolStripMenuItem_Click);
            // 
            // ImageEditForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(847, 576);
            this.Controls.Add(this.buttonOpenImage);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.comboBoxDevices);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.listViewRightPanel);
            this.Controls.Add(this.treeViewLeftPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(865, 623);
            this.Name = "ImageEditForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IsoSDK .NET Image Edit Sample";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ImageEditForm_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView treeViewLeftPanel;
        private System.Windows.Forms.ListView listViewRightPanel;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem discToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem imageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mountToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem unmountToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem makeMd5ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem audioToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem playSelectedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemAspiSpti;
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
        private System.Windows.Forms.ToolStripMenuItem verifyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem checkMd5ToolStripMenuItem;
        private System.Windows.Forms.ComboBox comboBoxDevices;
        private System.Windows.Forms.ColumnHeader columnHeaderName;
        private System.Windows.Forms.ColumnHeader columnHeaderLba;
        private System.Windows.Forms.ColumnHeader columnHeaderSize;
        private System.Windows.Forms.ColumnHeader columnHeaderModified;
        private System.Windows.Forms.ImageList imageListIcons;
        private System.Windows.Forms.ToolStripMenuItem grabAllTracksToolStripMenuItem;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.Button buttonOpenImage;
    }
}

