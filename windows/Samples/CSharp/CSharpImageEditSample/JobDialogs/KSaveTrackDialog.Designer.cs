namespace CSharpImageEditSample
{
    partial class KSaveTrackDialog
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
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.STLabelBytes = new System.Windows.Forms.Label();
            this.STLabelTotal = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.STLabelTime = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.buttonAbort = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(13, 28);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(285, 10);
            this.progressBar.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Total progress:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Bytes written: ";
            // 
            // STLabelBytes
            // 
            this.STLabelBytes.AutoSize = true;
            this.STLabelBytes.Location = new System.Drawing.Point(89, 55);
            this.STLabelBytes.Name = "STLabelBytes";
            this.STLabelBytes.Size = new System.Drawing.Size(0, 13);
            this.STLabelBytes.TabIndex = 3;
            // 
            // STLabelTotal
            // 
            this.STLabelTotal.AutoSize = true;
            this.STLabelTotal.Location = new System.Drawing.Point(135, 78);
            this.STLabelTotal.Name = "STLabelTotal";
            this.STLabelTotal.Size = new System.Drawing.Size(0, 13);
            this.STLabelTotal.TabIndex = 5;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 78);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(119, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Total track size (bytes): ";
            // 
            // STLabelTime
            // 
            this.STLabelTime.AutoSize = true;
            this.STLabelTime.Location = new System.Drawing.Point(79, 103);
            this.STLabelTime.Name = "STLabelTime";
            this.STLabelTime.Size = new System.Drawing.Size(0, 13);
            this.STLabelTime.TabIndex = 7;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 103);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(63, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "Total Time: ";
            // 
            // buttonAbort
            // 
            this.buttonAbort.Location = new System.Drawing.Point(12, 130);
            this.buttonAbort.Name = "buttonAbort";
            this.buttonAbort.Size = new System.Drawing.Size(75, 23);
            this.buttonAbort.TabIndex = 8;
            this.buttonAbort.Text = "&Abort";
            this.buttonAbort.UseVisualStyleBackColor = true;
            this.buttonAbort.Click += new System.EventHandler(this.buttonAbort_Click);
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // KSaveTrackDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(304, 154);
            this.Controls.Add(this.buttonAbort);
            this.Controls.Add(this.STLabelTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.STLabelTotal);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.STLabelBytes);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.progressBar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(320, 193);
            this.Name = "KSaveTrackDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Saving track...";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.KSaveTrackDialog_FormClosing);
            this.Load += new System.EventHandler(this.KSaveTrackDialog_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label STLabelBytes;
        private System.Windows.Forms.Label STLabelTotal;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label STLabelTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button buttonAbort;
        private System.Windows.Forms.Timer timer;
    }
}