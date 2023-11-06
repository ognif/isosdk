namespace CSharpDataSample
{
    partial class BootImageDlg
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BootImageDlg));
            this.label1 = new System.Windows.Forms.Label();
            this.imageTextBox = new System.Windows.Forms.TextBox();
            this.imageButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.developerTextBox = new System.Windows.Forms.TextBox();
            this.loadTextBox = new System.Windows.Forms.TextBox();
            this.sectorTextBox = new System.Windows.Forms.TextBox();
            this.bootableCheckBox = new System.Windows.Forms.CheckBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.platformComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.emulationComboBox = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.resetButton = new System.Windows.Forms.Button();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 16);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Boot image:";
            // 
            // imageTextBox
            // 
            this.imageTextBox.Location = new System.Drawing.Point(21, 37);
            this.imageTextBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.imageTextBox.Name = "imageTextBox";
            this.imageTextBox.Size = new System.Drawing.Size(323, 22);
            this.imageTextBox.TabIndex = 1;
            // 
            // imageButton
            // 
            this.imageButton.Location = new System.Drawing.Point(355, 36);
            this.imageButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.imageButton.Name = "imageButton";
            this.imageButton.Size = new System.Drawing.Size(28, 25);
            this.imageButton.TabIndex = 2;
            this.imageButton.Text = "...";
            this.imageButton.UseVisualStyleBackColor = true;
            this.imageButton.Click += new System.EventHandler(this.imageButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.developerTextBox);
            this.groupBox1.Controls.Add(this.loadTextBox);
            this.groupBox1.Controls.Add(this.sectorTextBox);
            this.groupBox1.Controls.Add(this.bootableCheckBox);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.platformComboBox);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.emulationComboBox);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(21, 69);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Size = new System.Drawing.Size(361, 266);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            // 
            // developerTextBox
            // 
            this.developerTextBox.Location = new System.Drawing.Point(128, 201);
            this.developerTextBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.developerTextBox.Name = "developerTextBox";
            this.developerTextBox.Size = new System.Drawing.Size(195, 22);
            this.developerTextBox.TabIndex = 10;
            // 
            // loadTextBox
            // 
            this.loadTextBox.Location = new System.Drawing.Point(128, 165);
            this.loadTextBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.loadTextBox.Name = "loadTextBox";
            this.loadTextBox.Size = new System.Drawing.Size(100, 22);
            this.loadTextBox.TabIndex = 9;
            // 
            // sectorTextBox
            // 
            this.sectorTextBox.Location = new System.Drawing.Point(128, 129);
            this.sectorTextBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.sectorTextBox.Name = "sectorTextBox";
            this.sectorTextBox.Size = new System.Drawing.Size(100, 22);
            this.sectorTextBox.TabIndex = 8;
            // 
            // bootableCheckBox
            // 
            this.bootableCheckBox.AutoSize = true;
            this.bootableCheckBox.Location = new System.Drawing.Point(13, 235);
            this.bootableCheckBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bootableCheckBox.Name = "bootableCheckBox";
            this.bootableCheckBox.Size = new System.Drawing.Size(152, 21);
            this.bootableCheckBox.TabIndex = 7;
            this.bootableCheckBox.Text = "Make disk bootable";
            this.bootableCheckBox.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 206);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(94, 17);
            this.label6.TabIndex = 6;
            this.label6.Text = "Developer ID:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 170);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(102, 17);
            this.label5.TabIndex = 5;
            this.label5.Text = "Load segment:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 134);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(92, 17);
            this.label4.TabIndex = 4;
            this.label4.Text = "Sector count:";
            // 
            // platformComboBox
            // 
            this.platformComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.platformComboBox.FormattingEnabled = true;
            this.platformComboBox.Location = new System.Drawing.Point(9, 89);
            this.platformComboBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.platformComboBox.Name = "platformComboBox";
            this.platformComboBox.Size = new System.Drawing.Size(243, 24);
            this.platformComboBox.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 68);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Platform:";
            // 
            // emulationComboBox
            // 
            this.emulationComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.emulationComboBox.FormattingEnabled = true;
            this.emulationComboBox.Location = new System.Drawing.Point(9, 33);
            this.emulationComboBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.emulationComboBox.Name = "emulationComboBox";
            this.emulationComboBox.Size = new System.Drawing.Size(243, 24);
            this.emulationComboBox.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 12);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(185, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "Boot media type(emulation):";
            // 
            // resetButton
            // 
            this.resetButton.Location = new System.Drawing.Point(21, 342);
            this.resetButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.resetButton.Name = "resetButton";
            this.resetButton.Size = new System.Drawing.Size(100, 28);
            this.resetButton.TabIndex = 4;
            this.resetButton.Text = "Reset";
            this.resetButton.UseVisualStyleBackColor = true;
            this.resetButton.Click += new System.EventHandler(this.resetButton_Click);
            // 
            // okButton
            // 
            this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.okButton.Location = new System.Drawing.Point(175, 342);
            this.okButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(100, 28);
            this.okButton.TabIndex = 5;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(283, 342);
            this.cancelButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(100, 28);
            this.cancelButton.TabIndex = 6;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // BootImageDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(401, 390);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.resetButton);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.imageButton);
            this.Controls.Add(this.imageTextBox);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "BootImageDlg";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Boot image options";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox imageTextBox;
        private System.Windows.Forms.Button imageButton;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button resetButton;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox platformComboBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox emulationComboBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox developerTextBox;
        private System.Windows.Forms.TextBox loadTextBox;
        private System.Windows.Forms.TextBox sectorTextBox;
        private System.Windows.Forms.CheckBox bootableCheckBox;
    }
}