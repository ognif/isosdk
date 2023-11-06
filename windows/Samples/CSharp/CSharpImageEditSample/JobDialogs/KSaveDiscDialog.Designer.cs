namespace CSharpImageEditSample
{
    partial class KSaveDiscDialog
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
            this.buttonAbort = new System.Windows.Forms.Button();
            this.SDLabelTime = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SDLabelTotal = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SDLabelSector = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.SDLabelErrors = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // buttonAbort
            // 
            this.buttonAbort.Location = new System.Drawing.Point(14, 162);
            this.buttonAbort.Name = "buttonAbort";
            this.buttonAbort.Size = new System.Drawing.Size(75, 23);
            this.buttonAbort.TabIndex = 17;
            this.buttonAbort.Text = "&Abort";
            this.buttonAbort.UseVisualStyleBackColor = true;
            this.buttonAbort.Click += new System.EventHandler(this.buttonAbort_Click);
            // 
            // SDLabelTime
            // 
            this.SDLabelTime.AutoSize = true;
            this.SDLabelTime.Location = new System.Drawing.Point(80, 136);
            this.SDLabelTime.Name = "SDLabelTime";
            this.SDLabelTime.Size = new System.Drawing.Size(0, 13);
            this.SDLabelTime.TabIndex = 16;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(11, 136);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(63, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Total Time: ";
            // 
            // SDLabelTotal
            // 
            this.SDLabelTotal.AutoSize = true;
            this.SDLabelTotal.Location = new System.Drawing.Point(89, 88);
            this.SDLabelTotal.Name = "SDLabelTotal";
            this.SDLabelTotal.Size = new System.Drawing.Size(0, 13);
            this.SDLabelTotal.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 88);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(76, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Total Sectors: ";
            // 
            // SDLabelSector
            // 
            this.SDLabelSector.AutoSize = true;
            this.SDLabelSector.Location = new System.Drawing.Point(99, 65);
            this.SDLabelSector.Name = "SDLabelSector";
            this.SDLabelSector.Size = new System.Drawing.Size(0, 13);
            this.SDLabelSector.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(81, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "Current Sector: ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Total progress:";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(15, 38);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(285, 10);
            this.progressBar.TabIndex = 9;
            // 
            // SDLabelErrors
            // 
            this.SDLabelErrors.AutoSize = true;
            this.SDLabelErrors.Location = new System.Drawing.Point(81, 112);
            this.SDLabelErrors.Name = "SDLabelErrors";
            this.SDLabelErrors.Size = new System.Drawing.Size(0, 13);
            this.SDLabelErrors.TabIndex = 19;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 112);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(69, 13);
            this.label6.TabIndex = 18;
            this.label6.Text = "Read Errors: ";
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // KSaveDiscDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(318, 197);
            this.Controls.Add(this.SDLabelErrors);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.buttonAbort);
            this.Controls.Add(this.SDLabelTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.SDLabelTotal);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.SDLabelSector);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.progressBar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "KSaveDiscDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Saving disc...";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.KSaveDiscDialog_FormClosing);
            this.Load += new System.EventHandler(this.KSaveDiscDialog_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonAbort;
        private System.Windows.Forms.Label SDLabelTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label SDLabelTotal;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label SDLabelSector;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label SDLabelErrors;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Timer timer;
    }
}