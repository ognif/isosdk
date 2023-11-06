namespace CSharpImageEditSample
{
    partial class KTrackPlayDialog
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
            this.STLabelTime = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.STLabelTotal = new System.Windows.Forms.Label();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.STLabelBytes = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // buttonAbort
            // 
            this.buttonAbort.Location = new System.Drawing.Point(12, 128);
            this.buttonAbort.Name = "buttonAbort";
            this.buttonAbort.Size = new System.Drawing.Size(75, 23);
            this.buttonAbort.TabIndex = 17;
            this.buttonAbort.Text = "&Abort";
            this.buttonAbort.UseVisualStyleBackColor = true;
            this.buttonAbort.Click += new System.EventHandler(this.buttonAbort_Click);
            // 
            // STLabelTime
            // 
            this.STLabelTime.AutoSize = true;
            this.STLabelTime.Location = new System.Drawing.Point(79, 101);
            this.STLabelTime.Name = "STLabelTime";
            this.STLabelTime.Size = new System.Drawing.Size(0, 13);
            this.STLabelTime.TabIndex = 16;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 101);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(63, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Total Time: ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 76);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(119, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Total track size (bytes): ";
            // 
            // STLabelTotal
            // 
            this.STLabelTotal.AutoSize = true;
            this.STLabelTotal.Location = new System.Drawing.Point(135, 76);
            this.STLabelTotal.Name = "STLabelTotal";
            this.STLabelTotal.Size = new System.Drawing.Size(0, 13);
            this.STLabelTotal.TabIndex = 14;
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // STLabelBytes
            // 
            this.STLabelBytes.AutoSize = true;
            this.STLabelBytes.Location = new System.Drawing.Point(89, 53);
            this.STLabelBytes.Name = "STLabelBytes";
            this.STLabelBytes.Size = new System.Drawing.Size(0, 13);
            this.STLabelBytes.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "Bytes written: ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Total progress:";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(13, 26);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(285, 10);
            this.progressBar.TabIndex = 9;
            // 
            // KTrackPlayDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(304, 154);
            this.Controls.Add(this.buttonAbort);
            this.Controls.Add(this.STLabelTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.STLabelTotal);
            this.Controls.Add(this.STLabelBytes);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.progressBar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(320, 193);
            this.Name = "KTrackPlayDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Playing track...";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.KTrackPlayDialog_FormClosing);
            this.Load += new System.EventHandler(this.KTrackPlayDialog_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonAbort;
        private System.Windows.Forms.Label STLabelTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label STLabelTotal;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label STLabelBytes;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ProgressBar progressBar;
    }
}