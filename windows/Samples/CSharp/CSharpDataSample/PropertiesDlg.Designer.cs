namespace CSharpDataSample
{
    partial class PropertiesDlg
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PropertiesDlg));
            this.label1 = new System.Windows.Forms.Label();
            this.nameLabel = new System.Windows.Forms.Label();
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.fileCreationDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.fileModificationDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.fileLastAccessDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.fileCreationTimeLabel = new System.Windows.Forms.Label();
            this.fileModificationTimeLabel = new System.Windows.Forms.Label();
            this.fileLastAccessTimeLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.hiddenAttributeCheckBox = new System.Windows.Forms.CheckBox();
            this.advancedHiddenAttributeCheckBox = new System.Windows.Forms.CheckBox();
            this.attributesLabel = new System.Windows.Forms.Label();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.globalTimesCheckbox = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label1.Location = new System.Drawing.Point(12, 44);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(323, 2);
            this.label1.TabIndex = 0;
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(12, 15);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(38, 13);
            this.nameLabel.TabIndex = 1;
            this.nameLabel.Text = "Name:";
            // 
            // nameTextBox
            // 
            this.nameTextBox.Location = new System.Drawing.Point(83, 12);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(252, 20);
            this.nameTextBox.TabIndex = 2;
            this.nameTextBox.Validating += new System.ComponentModel.CancelEventHandler(this.nameTextBox_Validating);
            // 
            // fileCreationDateTimePicker
            // 
            this.fileCreationDateTimePicker.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.fileCreationDateTimePicker.Location = new System.Drawing.Point(83, 58);
            this.fileCreationDateTimePicker.Name = "fileCreationDateTimePicker";
            this.fileCreationDateTimePicker.Size = new System.Drawing.Size(169, 20);
            this.fileCreationDateTimePicker.TabIndex = 3;
            // 
            // fileModificationDateTimePicker
            // 
            this.fileModificationDateTimePicker.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.fileModificationDateTimePicker.Location = new System.Drawing.Point(83, 84);
            this.fileModificationDateTimePicker.Name = "fileModificationDateTimePicker";
            this.fileModificationDateTimePicker.Size = new System.Drawing.Size(169, 20);
            this.fileModificationDateTimePicker.TabIndex = 4;
            // 
            // fileLastAccessDateTimePicker
            // 
            this.fileLastAccessDateTimePicker.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.fileLastAccessDateTimePicker.Location = new System.Drawing.Point(83, 110);
            this.fileLastAccessDateTimePicker.Name = "fileLastAccessDateTimePicker";
            this.fileLastAccessDateTimePicker.Size = new System.Drawing.Size(169, 20);
            this.fileLastAccessDateTimePicker.TabIndex = 5;
            // 
            // fileCreationTimeLabel
            // 
            this.fileCreationTimeLabel.AutoSize = true;
            this.fileCreationTimeLabel.Location = new System.Drawing.Point(12, 62);
            this.fileCreationTimeLabel.Name = "fileCreationTimeLabel";
            this.fileCreationTimeLabel.Size = new System.Drawing.Size(47, 13);
            this.fileCreationTimeLabel.TabIndex = 6;
            this.fileCreationTimeLabel.Text = "Created:";
            // 
            // fileModificationTimeLabel
            // 
            this.fileModificationTimeLabel.AutoSize = true;
            this.fileModificationTimeLabel.Location = new System.Drawing.Point(12, 88);
            this.fileModificationTimeLabel.Name = "fileModificationTimeLabel";
            this.fileModificationTimeLabel.Size = new System.Drawing.Size(50, 13);
            this.fileModificationTimeLabel.TabIndex = 7;
            this.fileModificationTimeLabel.Text = "Modified:";
            // 
            // fileLastAccessTimeLabel
            // 
            this.fileLastAccessTimeLabel.AutoSize = true;
            this.fileLastAccessTimeLabel.Location = new System.Drawing.Point(12, 114);
            this.fileLastAccessTimeLabel.Name = "fileLastAccessTimeLabel";
            this.fileLastAccessTimeLabel.Size = new System.Drawing.Size(57, 13);
            this.fileLastAccessTimeLabel.TabIndex = 8;
            this.fileLastAccessTimeLabel.Text = "Accessed:";
            // 
            // label2
            // 
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label2.Location = new System.Drawing.Point(12, 142);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(323, 2);
            this.label2.TabIndex = 9;
            // 
            // hiddenAttributeCheckBox
            // 
            this.hiddenAttributeCheckBox.AutoSize = true;
            this.hiddenAttributeCheckBox.Location = new System.Drawing.Point(83, 192);
            this.hiddenAttributeCheckBox.Name = "hiddenAttributeCheckBox";
            this.hiddenAttributeCheckBox.Size = new System.Drawing.Size(60, 17);
            this.hiddenAttributeCheckBox.TabIndex = 10;
            this.hiddenAttributeCheckBox.Text = "Hidden";
            this.hiddenAttributeCheckBox.UseVisualStyleBackColor = true;
            // 
            // advancedHiddenAttributeCheckBox
            // 
            this.advancedHiddenAttributeCheckBox.AutoSize = true;
            this.advancedHiddenAttributeCheckBox.Location = new System.Drawing.Point(149, 192);
            this.advancedHiddenAttributeCheckBox.Name = "advancedHiddenAttributeCheckBox";
            this.advancedHiddenAttributeCheckBox.Size = new System.Drawing.Size(110, 17);
            this.advancedHiddenAttributeCheckBox.TabIndex = 11;
            this.advancedHiddenAttributeCheckBox.Text = "Advanced hidden";
            this.advancedHiddenAttributeCheckBox.UseVisualStyleBackColor = true;
            // 
            // attributesLabel
            // 
            this.attributesLabel.AutoSize = true;
            this.attributesLabel.Location = new System.Drawing.Point(12, 192);
            this.attributesLabel.Name = "attributesLabel";
            this.attributesLabel.Size = new System.Drawing.Size(54, 13);
            this.attributesLabel.TabIndex = 12;
            this.attributesLabel.Text = "Attributes:";
            // 
            // okButton
            // 
            this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.okButton.Location = new System.Drawing.Point(179, 229);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 23);
            this.okButton.TabIndex = 13;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.CausesValidation = false;
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(260, 229);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 14;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label3.Location = new System.Drawing.Point(10, 178);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(323, 2);
            this.label3.TabIndex = 15;
            // 
            // globalTimesCheckbox
            // 
            this.globalTimesCheckbox.AutoSize = true;
            this.globalTimesCheckbox.Location = new System.Drawing.Point(15, 152);
            this.globalTimesCheckbox.Name = "globalTimesCheckbox";
            this.globalTimesCheckbox.Size = new System.Drawing.Size(276, 17);
            this.globalTimesCheckbox.TabIndex = 16;
            this.globalTimesCheckbox.Text = "Set times for global usage (Files, Directories, Disc FS)";
            this.globalTimesCheckbox.UseVisualStyleBackColor = true;
            // 
            // PropertiesDlg
            // 
            this.AcceptButton = this.okButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(347, 265);
            this.Controls.Add(this.globalTimesCheckbox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.attributesLabel);
            this.Controls.Add(this.advancedHiddenAttributeCheckBox);
            this.Controls.Add(this.hiddenAttributeCheckBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.fileLastAccessTimeLabel);
            this.Controls.Add(this.fileModificationTimeLabel);
            this.Controls.Add(this.fileCreationTimeLabel);
            this.Controls.Add(this.fileLastAccessDateTimePicker);
            this.Controls.Add(this.fileModificationDateTimePicker);
            this.Controls.Add(this.fileCreationDateTimePicker);
            this.Controls.Add(this.nameTextBox);
            this.Controls.Add(this.nameLabel);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "PropertiesDlg";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Properties";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.DateTimePicker fileCreationDateTimePicker;
        private System.Windows.Forms.DateTimePicker fileModificationDateTimePicker;
        private System.Windows.Forms.DateTimePicker fileLastAccessDateTimePicker;
        private System.Windows.Forms.Label fileCreationTimeLabel;
        private System.Windows.Forms.Label fileModificationTimeLabel;
        private System.Windows.Forms.Label fileLastAccessTimeLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox hiddenAttributeCheckBox;
        private System.Windows.Forms.CheckBox advancedHiddenAttributeCheckBox;
        private System.Windows.Forms.Label attributesLabel;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox globalTimesCheckbox;
    }
}