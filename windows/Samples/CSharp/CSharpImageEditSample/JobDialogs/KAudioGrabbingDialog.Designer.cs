namespace CSharpImageEditSample
{
    partial class KAudioGrabbingDialog
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
            this.components = new System.ComponentModel.Container();
            this.buttonConvert = new System.Windows.Forms.Button();
            this.labelTime = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.labelSize = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.labelBytes = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.labelTrack = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.cmbEncoder = new System.Windows.Forms.ComboBox();
            this.cmbBitrateType = new System.Windows.Forms.ComboBox();
            this.cmbCbrBitrate = new System.Windows.Forms.ComboBox();
            this.cmbVbrBitrateMin = new System.Windows.Forms.ComboBox();
            this.cmbVbrBitrateMax = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.textBoxPath = new System.Windows.Forms.TextBox();
            this.buttonBrowse = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.cmbTagChoise = new System.Windows.Forms.ComboBox();
            this.label13 = new System.Windows.Forms.Label();
            this.cmbQuality = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // buttonConvert
            // 
            this.buttonConvert.Location = new System.Drawing.Point(16, 355);
            this.buttonConvert.Name = "buttonConvert";
            this.buttonConvert.Size = new System.Drawing.Size(75, 23);
            this.buttonConvert.TabIndex = 17;
            this.buttonConvert.Text = "&Convert";
            this.buttonConvert.UseVisualStyleBackColor = true;
            this.buttonConvert.Click += new System.EventHandler(this.buttonConvert_Click);
            // 
            // labelTime
            // 
            this.labelTime.AutoSize = true;
            this.labelTime.Location = new System.Drawing.Point(91, 112);
            this.labelTime.Name = "labelTime";
            this.labelTime.Size = new System.Drawing.Size(0, 13);
            this.labelTime.TabIndex = 16;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 112);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Time left :";
            // 
            // labelSize
            // 
            this.labelSize.AutoSize = true;
            this.labelSize.Location = new System.Drawing.Point(114, 88);
            this.labelSize.Name = "labelSize";
            this.labelSize.Size = new System.Drawing.Size(0, 13);
            this.labelSize.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 88);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(96, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Track size (bytes) :";
            // 
            // labelBytes
            // 
            this.labelBytes.AutoSize = true;
            this.labelBytes.Location = new System.Drawing.Point(108, 63);
            this.labelBytes.Name = "labelBytes";
            this.labelBytes.Size = new System.Drawing.Size(0, 13);
            this.labelBytes.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 63);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(90, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "Bytes converted :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Total progress:";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(15, 36);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(303, 10);
            this.progressBar.TabIndex = 9;
            // 
            // labelTrack
            // 
            this.labelTrack.AutoSize = true;
            this.labelTrack.Location = new System.Drawing.Point(91, 136);
            this.labelTrack.Name = "labelTrack";
            this.labelTrack.Size = new System.Drawing.Size(0, 13);
            this.labelTrack.TabIndex = 19;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 136);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(74, 13);
            this.label6.TabIndex = 18;
            this.label6.Text = "Current track :";
            // 
            // cmbEncoder
            // 
            this.cmbEncoder.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbEncoder.FormattingEnabled = true;
            this.cmbEncoder.Items.AddRange(new object[] {
            "MP3",
            "AAC",
            "OGG",
            "OPUS",
            "FLAC"});
            this.cmbEncoder.Location = new System.Drawing.Point(15, 198);
            this.cmbEncoder.Name = "cmbEncoder";
            this.cmbEncoder.Size = new System.Drawing.Size(69, 21);
            this.cmbEncoder.TabIndex = 20;
            this.cmbEncoder.SelectedIndexChanged += new System.EventHandler(this.cmbEncoder_SelectedIndexChanged);
            // 
            // cmbBitrateType
            // 
            this.cmbBitrateType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBitrateType.FormattingEnabled = true;
            this.cmbBitrateType.Items.AddRange(new object[] {
            "Constant",
            "Variable"});
            this.cmbBitrateType.Location = new System.Drawing.Point(103, 198);
            this.cmbBitrateType.Name = "cmbBitrateType";
            this.cmbBitrateType.Size = new System.Drawing.Size(94, 21);
            this.cmbBitrateType.TabIndex = 21;
            this.cmbBitrateType.SelectedIndexChanged += new System.EventHandler(this.cmbBitrateType_SelectedIndexChanged);
            // 
            // cmbCbrBitrate
            // 
            this.cmbCbrBitrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbCbrBitrate.FormattingEnabled = true;
            this.cmbCbrBitrate.Items.AddRange(new object[] {
            "64 kBit/s",
            "96 kBit/s",
            "128 kBit/s",
            "192 kBit/s",
            "256 kBit/s",
            "320 kBit/s"});
            this.cmbCbrBitrate.Location = new System.Drawing.Point(103, 247);
            this.cmbCbrBitrate.Name = "cmbCbrBitrate";
            this.cmbCbrBitrate.Size = new System.Drawing.Size(94, 21);
            this.cmbCbrBitrate.TabIndex = 22;
            // 
            // cmbVbrBitrateMin
            // 
            this.cmbVbrBitrateMin.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbVbrBitrateMin.FormattingEnabled = true;
            this.cmbVbrBitrateMin.Items.AddRange(new object[] {
            "64 kBit/s",
            "96 kBit/s",
            "128 kBit/s",
            "192 kBit/s",
            "256 kBit/s",
            "320 kBit/s"});
            this.cmbVbrBitrateMin.Location = new System.Drawing.Point(224, 198);
            this.cmbVbrBitrateMin.Name = "cmbVbrBitrateMin";
            this.cmbVbrBitrateMin.Size = new System.Drawing.Size(94, 21);
            this.cmbVbrBitrateMin.TabIndex = 23;
            this.cmbVbrBitrateMin.SelectedIndexChanged += new System.EventHandler(this.cmbVbrBitrateMin_SelectedIndexChanged);
            // 
            // cmbVbrBitrateMax
            // 
            this.cmbVbrBitrateMax.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbVbrBitrateMax.FormattingEnabled = true;
            this.cmbVbrBitrateMax.Items.AddRange(new object[] {
            "64 kBit/s",
            "96 kBit/s",
            "128 kBit/s",
            "192 kBit/s",
            "256 kBit/s",
            "320 kBit/s"});
            this.cmbVbrBitrateMax.Location = new System.Drawing.Point(224, 247);
            this.cmbVbrBitrateMax.Name = "cmbVbrBitrateMax";
            this.cmbVbrBitrateMax.Size = new System.Drawing.Size(94, 21);
            this.cmbVbrBitrateMax.TabIndex = 24;
            this.cmbVbrBitrateMax.SelectedIndexChanged += new System.EventHandler(this.cmbVbrBitrateMax_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(13, 182);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 13);
            this.label7.TabIndex = 25;
            this.label7.Text = "Encoder :";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(100, 182);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(66, 13);
            this.label8.TabIndex = 26;
            this.label8.Text = "Bitrate type :";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(221, 182);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(88, 13);
            this.label9.TabIndex = 27;
            this.label9.Text = "VBR Min Bitrate :";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(100, 231);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(68, 13);
            this.label10.TabIndex = 28;
            this.label10.Text = "CBR Bitrate :";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(221, 231);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(91, 13);
            this.label11.TabIndex = 29;
            this.label11.Text = "VBR Max Bitrate :";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(13, 324);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(35, 13);
            this.label12.TabIndex = 30;
            this.label12.Text = "Path :";
            // 
            // textBoxPath
            // 
            this.textBoxPath.Location = new System.Drawing.Point(54, 321);
            this.textBoxPath.Name = "textBoxPath";
            this.textBoxPath.Size = new System.Drawing.Size(203, 20);
            this.textBoxPath.TabIndex = 31;
            // 
            // buttonBrowse
            // 
            this.buttonBrowse.Location = new System.Drawing.Point(263, 319);
            this.buttonBrowse.Name = "buttonBrowse";
            this.buttonBrowse.Size = new System.Drawing.Size(55, 23);
            this.buttonBrowse.TabIndex = 32;
            this.buttonBrowse.Text = "Browse";
            this.buttonBrowse.UseVisualStyleBackColor = true;
            this.buttonBrowse.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 294);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(66, 13);
            this.label3.TabIndex = 34;
            this.label3.Text = "Tag choise :";
            // 
            // cmbTagChoise
            // 
            this.cmbTagChoise.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbTagChoise.FormattingEnabled = true;
            this.cmbTagChoise.Items.AddRange(new object[] {
            "Don\'t add",
            "From CDText only",
            "From FreeDB only",
            "CDText first FreeDB last",
            "FreeDB first CDText last"});
            this.cmbTagChoise.Location = new System.Drawing.Point(103, 290);
            this.cmbTagChoise.Name = "cmbTagChoise";
            this.cmbTagChoise.Size = new System.Drawing.Size(215, 21);
            this.cmbTagChoise.TabIndex = 33;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(335, 182);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(42, 13);
            this.label13.TabIndex = 36;
            this.label13.Text = "Quality:";
            // 
            // cmbQuality
            // 
            this.cmbQuality.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbQuality.FormattingEnabled = true;
            this.cmbQuality.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9"});
            this.cmbQuality.Location = new System.Drawing.Point(338, 198);
            this.cmbQuality.Name = "cmbQuality";
            this.cmbQuality.Size = new System.Drawing.Size(94, 21);
            this.cmbQuality.TabIndex = 35;
            // 
            // KAudioGrabbingDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(449, 390);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.cmbQuality);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.cmbTagChoise);
            this.Controls.Add(this.buttonBrowse);
            this.Controls.Add(this.textBoxPath);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.cmbVbrBitrateMax);
            this.Controls.Add(this.cmbVbrBitrateMin);
            this.Controls.Add(this.cmbCbrBitrate);
            this.Controls.Add(this.cmbBitrateType);
            this.Controls.Add(this.cmbEncoder);
            this.Controls.Add(this.labelTrack);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.buttonConvert);
            this.Controls.Add(this.labelTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.labelSize);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.labelBytes);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.progressBar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "KAudioGrabbingDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Grabbing audio track...";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.KAudioGrabbingDialog_FormClosing);
            this.Load += new System.EventHandler(this.KAudioGrabbingDialog_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonConvert;
        private System.Windows.Forms.Label labelTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label labelSize;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label labelBytes;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label labelTrack;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox cmbEncoder;
        private System.Windows.Forms.ComboBox cmbBitrateType;
        private System.Windows.Forms.ComboBox cmbCbrBitrate;
        private System.Windows.Forms.ComboBox cmbVbrBitrateMin;
        private System.Windows.Forms.ComboBox cmbVbrBitrateMax;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBoxPath;
        private System.Windows.Forms.Button buttonBrowse;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cmbTagChoise;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.ComboBox cmbQuality;
    }
}