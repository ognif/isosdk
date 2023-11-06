namespace CSharpImageEditSample
{
    partial class KSectorViewDialog
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(KSectorViewDialog));
            this.buttonPrev = new System.Windows.Forms.Button();
            this.numericUpDownSector = new System.Windows.Forms.NumericUpDown();
            this.buttonNext = new System.Windows.Forms.Button();
            this.checkBoxRaw = new System.Windows.Forms.CheckBox();
            this.richTextBoxSectors = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSector)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonPrev
            // 
            this.buttonPrev.Location = new System.Drawing.Point(16, 15);
            this.buttonPrev.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonPrev.Name = "buttonPrev";
            this.buttonPrev.Size = new System.Drawing.Size(100, 28);
            this.buttonPrev.TabIndex = 0;
            this.buttonPrev.Text = "&Previous";
            this.buttonPrev.UseVisualStyleBackColor = true;
            this.buttonPrev.Click += new System.EventHandler(this.buttonPrev_Click);
            // 
            // numericUpDownSector
            // 
            this.numericUpDownSector.Location = new System.Drawing.Point(124, 18);
            this.numericUpDownSector.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.numericUpDownSector.Name = "numericUpDownSector";
            this.numericUpDownSector.Size = new System.Drawing.Size(73, 22);
            this.numericUpDownSector.TabIndex = 1;
            this.numericUpDownSector.ValueChanged += new System.EventHandler(this.numericUpDownSector_ValueChanged);
            // 
            // buttonNext
            // 
            this.buttonNext.Location = new System.Drawing.Point(205, 15);
            this.buttonNext.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonNext.Name = "buttonNext";
            this.buttonNext.Size = new System.Drawing.Size(100, 28);
            this.buttonNext.TabIndex = 2;
            this.buttonNext.Text = "&Next";
            this.buttonNext.UseVisualStyleBackColor = true;
            this.buttonNext.Click += new System.EventHandler(this.buttonNext_Click);
            // 
            // checkBoxRaw
            // 
            this.checkBoxRaw.AutoSize = true;
            this.checkBoxRaw.Checked = true;
            this.checkBoxRaw.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRaw.Location = new System.Drawing.Point(313, 20);
            this.checkBoxRaw.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.checkBoxRaw.Name = "checkBoxRaw";
            this.checkBoxRaw.Size = new System.Drawing.Size(57, 21);
            this.checkBoxRaw.TabIndex = 3;
            this.checkBoxRaw.Text = "Raw";
            this.checkBoxRaw.UseVisualStyleBackColor = true;
            this.checkBoxRaw.CheckedChanged += new System.EventHandler(this.checkBoxRaw_CheckedChanged);
            // 
            // richTextBoxSectors
            // 
            this.richTextBoxSectors.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.richTextBoxSectors.Location = new System.Drawing.Point(16, 50);
            this.richTextBoxSectors.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.richTextBoxSectors.Name = "richTextBoxSectors";
            this.richTextBoxSectors.Size = new System.Drawing.Size(843, 515);
            this.richTextBoxSectors.TabIndex = 4;
            this.richTextBoxSectors.Text = "";
            // 
            // KSectorViewDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(860, 562);
            this.Controls.Add(this.richTextBoxSectors);
            this.Controls.Add(this.checkBoxRaw);
            this.Controls.Add(this.buttonNext);
            this.Controls.Add(this.numericUpDownSector);
            this.Controls.Add(this.buttonPrev);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(878, 609);
            this.Name = "KSectorViewDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Sector View";
            this.Load += new System.EventHandler(this.KSectorViewDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSector)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonPrev;
        private System.Windows.Forms.NumericUpDown numericUpDownSector;
        private System.Windows.Forms.Button buttonNext;
        private System.Windows.Forms.CheckBox checkBoxRaw;
        private System.Windows.Forms.RichTextBox richTextBoxSectors;
    }
}