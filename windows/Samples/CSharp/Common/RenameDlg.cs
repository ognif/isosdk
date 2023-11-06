using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CommonNet
{
    namespace Dialogs
    {
        public partial class RenameDlg : Form
        {
            private string strRenamed;
            public RenameDlg(string strFile)
            {
                InitializeComponent();
                renameLabel.Text = String.Format("Rename {0} to:", strFile);
            }

            private void okButton_Click(object sender, EventArgs e)
            {
                strRenamed = renameTextBox.Text;
                this.Close();
            }

            private void cancelButton_Click(object sender, EventArgs e)
            {
                this.Close();
            }
            public string GetFileName()
            {
                return strRenamed;
            }
        }
    }
}