namespace CommonNet
{
    namespace Dialogs
    {
        partial class BurnDlgDevel
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BurnDlgDevel));
            this.lstLog = new System.Windows.Forms.ListBox();
            this.btnSaveLog = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.pgsTotal = new System.Windows.Forms.ProgressBar();
            this.pgsBuffer = new System.Windows.Forms.ProgressBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.separator = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lblSpeed = new System.Windows.Forms.Label();
            this.lblTime = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label5 = new System.Windows.Forms.Label();
            this.lblFile = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.separator)).BeginInit();
            this.SuspendLayout();
            // 
            // lstLog
            // 
            this.lstLog.FormattingEnabled = true;
            this.lstLog.ItemHeight = 16;
            this.lstLog.Location = new System.Drawing.Point(12, 12);
            this.lstLog.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.lstLog.Name = "lstLog";
            this.lstLog.Size = new System.Drawing.Size(507, 148);
            this.lstLog.TabIndex = 0;
            // 
            // btnSaveLog
            // 
            this.btnSaveLog.Location = new System.Drawing.Point(16, 332);
            this.btnSaveLog.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSaveLog.Name = "btnSaveLog";
            this.btnSaveLog.Size = new System.Drawing.Size(132, 31);
            this.btnSaveLog.TabIndex = 1;
            this.btnSaveLog.Text = "Save Log";
            this.btnSaveLog.UseVisualStyleBackColor = true;
            this.btnSaveLog.Click += new System.EventHandler(this.btnSaveLog_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(385, 332);
            this.btnCancel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(133, 30);
            this.btnCancel.TabIndex = 2;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // pgsTotal
            // 
            this.pgsTotal.Location = new System.Drawing.Point(17, 290);
            this.pgsTotal.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pgsTotal.Name = "pgsTotal";
            this.pgsTotal.Size = new System.Drawing.Size(500, 23);
            this.pgsTotal.TabIndex = 3;
            // 
            // pgsBuffer
            // 
            this.pgsBuffer.Location = new System.Drawing.Point(17, 241);
            this.pgsBuffer.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pgsBuffer.Name = "pgsBuffer";
            this.pgsBuffer.Size = new System.Drawing.Size(499, 25);
            this.pgsBuffer.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 272);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(105, 17);
            this.label1.TabIndex = 5;
            this.label1.Text = "Total Progress:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 223);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(101, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "Current Buffer:";
            // 
            // separator
            // 
            this.separator.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.separator.Location = new System.Drawing.Point(16, 213);
            this.separator.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.separator.Name = "separator";
            this.separator.Size = new System.Drawing.Size(497, 4);
            this.separator.TabIndex = 7;
            this.separator.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 187);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(104, 17);
            this.label3.TabIndex = 8;
            this.label3.Text = "Current Speed:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(340, 169);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 17);
            this.label4.TabIndex = 9;
            this.label4.Text = "Total Time:";
            // 
            // lblSpeed
            // 
            this.lblSpeed.AutoSize = true;
            this.lblSpeed.Location = new System.Drawing.Point(112, 187);
            this.lblSpeed.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSpeed.Name = "lblSpeed";
            this.lblSpeed.Size = new System.Drawing.Size(46, 17);
            this.lblSpeed.TabIndex = 10;
            this.lblSpeed.Text = "label5";
            // 
            // lblTime
            // 
            this.lblTime.AutoSize = true;
            this.lblTime.Location = new System.Drawing.Point(417, 169);
            this.lblTime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(64, 17);
            this.lblTime.TabIndex = 11;
            this.lblTime.Text = "00:00:00";
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 169);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 17);
            this.label5.TabIndex = 12;
            this.label5.Text = "Write File:";
            // 
            // lblFile
            // 
            this.lblFile.AutoSize = true;
            this.lblFile.Location = new System.Drawing.Point(81, 169);
            this.lblFile.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblFile.Name = "lblFile";
            this.lblFile.Size = new System.Drawing.Size(0, 17);
            this.lblFile.TabIndex = 13;
            // 
            // BurnDlgDevel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(533, 372);
            this.Controls.Add(this.lblFile);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.lblTime);
            this.Controls.Add(this.lblSpeed);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.separator);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pgsBuffer);
            this.Controls.Add(this.pgsTotal);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSaveLog);
            this.Controls.Add(this.lstLog);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "BurnDlgDevel";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "BurnDlgDevel";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.BurnDlgDevel_FormClosed);
            this.Load += new System.EventHandler(this.BurnDlgDevel_Load);
            ((System.ComponentModel.ISupportInitialize)(this.separator)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

            }

            #endregion

            private System.Windows.Forms.ListBox lstLog;
            private System.Windows.Forms.Button btnSaveLog;
            private System.Windows.Forms.Button btnCancel;
            private System.Windows.Forms.ProgressBar pgsTotal;
            private System.Windows.Forms.ProgressBar pgsBuffer;
            private System.Windows.Forms.Label label1;
            private System.Windows.Forms.Label label2;
            private System.Windows.Forms.PictureBox separator;
            private System.Windows.Forms.Label label3;
            private System.Windows.Forms.Label label4;
            private System.Windows.Forms.Label lblSpeed;
            private System.Windows.Forms.Label lblTime;
            private System.Windows.Forms.Timer timer1;
            private System.Windows.Forms.Label label5;
            private System.Windows.Forms.Label lblFile;
        }
    }
}