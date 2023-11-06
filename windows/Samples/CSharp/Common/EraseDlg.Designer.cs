namespace CommonNet
{
	namespace Dialogs
    {
    partial class EraseDlg
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EraseDlg));
            this.label1 = new System.Windows.Forms.Label();
            this.deviceComboBox = new System.Windows.Forms.ComboBox();
            this.eraseProgressBar = new System.Windows.Forms.ProgressBar();
            this.label2 = new System.Windows.Forms.Label();
            this.fastButton = new System.Windows.Forms.Button();
            this.completeButton = new System.Windows.Forms.Button();
            this.exitButton = new System.Windows.Forms.Button();
            this.textLabel = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBoxEject = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
                this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Device:";
            // 
            // deviceComboBox
            // 
            this.deviceComboBox.FormattingEnabled = true;
            this.deviceComboBox.Location = new System.Drawing.Point(64, 19);
            this.deviceComboBox.Name = "deviceComboBox";
            this.deviceComboBox.Size = new System.Drawing.Size(300, 21);
            this.deviceComboBox.TabIndex = 1;
            // 
            // eraseProgressBar
            // 
            this.eraseProgressBar.Location = new System.Drawing.Point(16, 68);
            this.eraseProgressBar.Name = "eraseProgressBar";
            this.eraseProgressBar.Size = new System.Drawing.Size(348, 16);
            this.eraseProgressBar.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(16, 106);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Status";
            // 
            // fastButton
            // 
            this.fastButton.Location = new System.Drawing.Point(127, 223);
            this.fastButton.Name = "fastButton";
            this.fastButton.Size = new System.Drawing.Size(75, 23);
            this.fastButton.TabIndex = 5;
            this.fastButton.Text = "Fast";
            this.fastButton.UseVisualStyleBackColor = true;
            this.fastButton.Click += new System.EventHandler(this.fastButton_Click);
            // 
            // completeButton
            // 
            this.completeButton.Location = new System.Drawing.Point(208, 223);
            this.completeButton.Name = "completeButton";
            this.completeButton.Size = new System.Drawing.Size(75, 23);
            this.completeButton.TabIndex = 6;
            this.completeButton.Text = "Complete";
            this.completeButton.UseVisualStyleBackColor = true;
            this.completeButton.Click += new System.EventHandler(this.completeButton_Click);
            // 
            // exitButton
            // 
            this.exitButton.Location = new System.Drawing.Point(289, 223);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(75, 23);
            this.exitButton.TabIndex = 7;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
            // 
            // textLabel
            // 
            this.textLabel.AutoSize = true;
            this.textLabel.Location = new System.Drawing.Point(108, 39);
            this.textLabel.Name = "textLabel";
            this.textLabel.Size = new System.Drawing.Size(133, 13);
            this.textLabel.TabIndex = 0;
            this.textLabel.Text = "Waiting for user interaction";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textLabel);
            this.groupBox1.Location = new System.Drawing.Point(16, 122);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(348, 83);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            // 
            // checkBoxEject
            // 
            this.checkBoxEject.AutoSize = true;
            this.checkBoxEject.Checked = true;
            this.checkBoxEject.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxEject.Location = new System.Drawing.Point(19, 227);
            this.checkBoxEject.Name = "checkBoxEject";
            this.checkBoxEject.Size = new System.Drawing.Size(50, 17);
            this.checkBoxEject.TabIndex = 9;
            this.checkBoxEject.Text = "Eject";
            this.checkBoxEject.UseVisualStyleBackColor = true;
            // 
            // EraseDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(376, 266);
            this.ControlBox = false;
            this.Controls.Add(this.checkBoxEject);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.completeButton);
            this.Controls.Add(this.fastButton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.eraseProgressBar);
            this.Controls.Add(this.deviceComboBox);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "EraseDlg";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "IsoSDK .NET";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox deviceComboBox;
        private System.Windows.Forms.ProgressBar eraseProgressBar;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button fastButton;
        private System.Windows.Forms.Button completeButton;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.Label textLabel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox checkBoxEject;
    }
	}
}