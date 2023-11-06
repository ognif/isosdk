using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpDataSample
{
    public partial class ImportSessionDlg : Form
    {
        private Burner m_burner;
        private int m_nSession;
        public int Session
        {
            get
            {
                return m_nSession;
            }
        }
        public ImportSessionDlg(Burner burner)
        {
            InitializeComponent();
            m_burner = burner;
            sessionListView.Columns.Add("#", 30);
            sessionListView.Columns.Add("Start LBA", 100);
            sessionListView.Columns.Add("Size", 100);

            int nLastSession = m_burner.GetMediumInfo().LastSession;
            for (int i = 0; i < nLastSession; ++i)
            {
                sessionListView.Items.Add((i+1).ToString());
                sessionListView.Items[i].SubItems.Add(
                    m_burner.GetSessionInfo(i+1).StartLBA.ToString());
                sessionListView.Items[i].SubItems.Add(
                    m_burner.GetSessionInfo(i+1).Size.ToString());               
            }
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            if (sessionListView.SelectedIndices.Count > 0)
            {
                m_nSession = sessionListView.SelectedIndices[0] + 1;
            }
            else
            {
                m_nSession = 0;
            }
            this.Close();
        }
    }
}