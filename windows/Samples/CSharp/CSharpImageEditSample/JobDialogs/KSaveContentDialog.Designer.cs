namespace CSharpImageEditSample
{
    partial class KSaveContentDialog
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
            this.SCLabelTime = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SCLabelTotal = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SCLabelBytes = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.SCListBoxLog = new System.Windows.Forms.ListBox();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // buttonAbort
            // 
            this.buttonAbort.Location = new System.Drawing.Point(15, 251);
            this.buttonAbort.Name = "buttonAbort";
            this.buttonAbort.Size = new System.Drawing.Size(75, 23);
            this.buttonAbort.TabIndex = 17;
            this.buttonAbort.Text = "&Abort";
            this.buttonAbort.UseVisualStyleBackColor = true;
            this.buttonAbort.Click += new System.EventHandler(this.buttonAbort_Click);
            // 
            // SCLabelTime
            // 
            this.SCLabelTime.AutoSize = true;
            this.SCLabelTime.Location = new System.Drawing.Point(83, 111);
            this.SCLabelTime.Name = "SCLabelTime";
            this.SCLabelTime.Size = new System.Drawing.Size(0, 13);
            this.SCLabelTime.TabIndex = 16;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(14, 111);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(63, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Total Time: ";
            // 
            // SCLabelTotal
            // 
            this.SCLabelTotal.AutoSize = true;
            this.SCLabelTotal.Location = new System.Drawing.Point(139, 86);
            this.SCLabelTotal.Name = "SCLabelTotal";
            this.SCLabelTotal.Size = new System.Drawing.Size(0, 13);
            this.SCLabelTotal.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 86);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(119, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Total track size (bytes): ";
            // 
            // SCLabelBytes
            // 
            this.SCLabelBytes.AutoSize = true;
            this.SCLabelBytes.Location = new System.Drawing.Point(90, 63);
            this.SCLabelBytes.Name = "SCLabelBytes";
            this.SCLabelBytes.Size = new System.Drawing.Size(0, 13);
            this.SCLabelBytes.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 63);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "Bytes written: ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Total progress:";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(15, 36);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(289, 11);
            this.progressBar.TabIndex = 9;
            // 
            // SCListBoxLog
            // 
            this.SCListBoxLog.FormattingEnabled = true;
            this.SCListBoxLog.Location = new System.Drawing.Point(17, 132);
            this.SCListBoxLog.Name = "SCListBoxLog";
            this.SCListBoxLog.Size = new System.Drawing.Size(287, 108);
            this.SCListBoxLog.TabIndex = 20;
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // KSaveContentDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(306, 269);
            this.Controls.Add(this.SCListBoxLog);
            this.Controls.Add(this.buttonAbort);
            this.Controls.Add(this.SCLabelTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.SCLabelTotal);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.SCLabelBytes);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.progressBar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(322, 308);
            this.Name = "KSaveContentDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Saving/checking content...";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.KSaveContentDialog_FormClosing);
            this.Load += new System.EventHandler(this.KSaveContentDialog_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonAbort;
        private System.Windows.Forms.Label SCLabelTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label SCLabelTotal;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label SCLabelBytes;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.ListBox SCListBoxLog;
        private System.Windows.Forms.Timer timer;
    }
}