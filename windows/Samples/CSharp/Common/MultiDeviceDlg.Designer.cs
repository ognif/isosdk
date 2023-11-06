namespace CommonNet
{
	namespace Dialogs
    {
		partial class MultiDeviceDlg
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
                this.deviceListView = new System.Windows.Forms.ListView();
                this.okButton = new System.Windows.Forms.Button();
                this.exitButton = new System.Windows.Forms.Button();
                this.SuspendLayout();
                // 
                // deviceListView
                // 
                this.deviceListView.Location = new System.Drawing.Point(16, 11);
                this.deviceListView.Name = "deviceListView";
                this.deviceListView.Size = new System.Drawing.Size(253, 109);
                this.deviceListView.TabIndex = 1;
                this.deviceListView.UseCompatibleStateImageBehavior = false;
                this.deviceListView.View = System.Windows.Forms.View.Details;
                this.deviceListView.SelectedIndexChanged += new System.EventHandler(this.deviceListView_SelectedIndexChanged);
                // 
                // okButton
                // 
                this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
                this.okButton.Location = new System.Drawing.Point(103, 139);
                this.okButton.Name = "okButton";
                this.okButton.Size = new System.Drawing.Size(75, 23);
                this.okButton.TabIndex = 2;
                this.okButton.Text = "OK";
                this.okButton.UseVisualStyleBackColor = true;
                this.okButton.Click += new System.EventHandler(this.okButton_Click);
                // 
                // exitButton
                // 
                this.exitButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
                this.exitButton.Location = new System.Drawing.Point(194, 139);
                this.exitButton.Name = "exitButton";
                this.exitButton.Size = new System.Drawing.Size(75, 23);
                this.exitButton.TabIndex = 3;
                this.exitButton.Text = "Exit";
                this.exitButton.UseVisualStyleBackColor = true;
                this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
                // 
                // MultiDeviceDlg
                // 
                this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
                this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
                this.ClientSize = new System.Drawing.Size(292, 176);
                this.Controls.Add(this.exitButton);
                this.Controls.Add(this.okButton);
                this.Controls.Add(this.deviceListView);
                this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
                this.Name = "MultiDeviceDlg";
                this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
                this.Text = "Select multiple devices";
                this.ResumeLayout(false);

            }

            #endregion

            private System.Windows.Forms.ListView deviceListView;
            private System.Windows.Forms.Button okButton;
            private System.Windows.Forms.Button exitButton;
        }
	}
}