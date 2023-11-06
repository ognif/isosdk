using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CSharpAudioSample
{
    public partial class CDTextDlg : Form
    {
        bool m_bDisc = false;
        int m_nPlayTime = 0;

        public CDTextDlg()
        {
            InitializeComponent();
            SetProperty(new KAudioFileProperty());
        }

        public CDTextDlg(bool disc, KAudioFileProperty property)
        {
            InitializeComponent();

            tabControlCDText.TabPages.Clear();
            tabControlCDText.TabPages.Add(tabPageCDText);
                
            m_bDisc = disc;

            if (disc)
            {
                labelDiscCode.Text = "UPC/EAN";
                textBoxPause.Enabled = false;
                checkBoxPauseInFrames.Enabled = false;
            }
            else
            {
                labelDiscCode.Text = "ISRC";
                tabControlCDText.TabPages.Add(tabPageIndexes);
            }

            if (property != null)
            {
                SetProperty(property);
            }
            else
            {
                throw new System.NullReferenceException("Null ref to Property in CDTextDlg()");
            }
        }

        public void SetProperty(KAudioFileProperty property)
        {
            textBoxArranger.Text = property.Arranger;
            textBoxComposer.Text = property.Composer;
            textBoxMessage.Text = property.Message;
            textBoxPause.Text = property.Pause.ToString();
            textBoxPerformer.Text = property.Performer;
            textBoxSongWriter.Text = property.SongWriter;
            textBoxTitle.Text = property.Title;
            textBoxCode.Text = property.McnIsrc;
            checkBoxPauseInFrames.Checked = property.PauseInFrames;

            listBoxIndexes.Items.Clear();

            if (!m_bDisc)
            {
                for (int i = 0; i < property.vIndexes.Count; ++i)
                {
                    int nTime = property.vIndexes[i];
                    int nMin = (nTime / 75) / 60;
                    int nSec = (nTime / 75) % 60;
                    int nFrame = nTime % 75;
                
                    String strIndex = nMin.ToString("00:") + nSec.ToString("00:") +
                        nFrame.ToString("00");

                    int nPos = listBoxIndexes.Items.Add(new IndexesListItem(strIndex, nTime));
                }

                m_nPlayTime = property.nPlayTime;
            }
        }

        private string GetTitle()
        {
            return textBoxTitle.Text;
        }

        private string GetComposer()
        {
            return textBoxComposer.Text;
        }

        private string GetPerformer()
        {
            return textBoxPerformer.Text;
        }

        private string GetSongWriter()
        {
            return textBoxSongWriter.Text;
        }

        private string GetArranger()
        {
            return textBoxArranger.Text;
        }

        private string GetMessage()
        {
            return textBoxMessage.Text;
        }

        private string GetMcnIsrc()
        {
            return textBoxCode.Text;
        }

        private int GetPause()
        {
            try
            {
                int res = int.Parse(textBoxPause.Text);
                return res;
            }
            catch (SystemException)
            {
                return 2;
            }            
        }

        private bool GetPauseInFrames()
        {
            return checkBoxPauseInFrames.Checked;
        }

        public KAudioFileProperty GetProperty()
        {
            KAudioFileProperty res = new KAudioFileProperty();
            res.Arranger = GetArranger();
            res.Composer = GetComposer();
            res.Message = GetMessage();
            res.Pause = GetPause();
            res.PauseInFrames = GetPauseInFrames();
            res.Performer = GetPerformer();
            res.SongWriter = GetSongWriter();
            res.Title = GetTitle();
            res.McnIsrc = GetMcnIsrc();

            res.nPlayTime = m_nPlayTime;

            if (!m_bDisc)
            {
                res.vIndexes.Clear();

	            for(int i = 0; i < listBoxIndexes.Items.Count; ++i)
                {
                    res.vIndexes.Add(((IndexesListItem)listBoxIndexes.Items[i]).m_nData);
                }
		        
                res.vIndexes.Sort();
            }

            return res;
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            SetProperty(new KAudioFileProperty());
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            int nMin = (int)numericUpDownM.Value;
            int nSec = (int)numericUpDownS.Value;
            int nFrame = (int)numericUpDownF.Value;

            String strIndex = nMin.ToString("00:") + nSec.ToString("00:") +
                nFrame.ToString("00");

            if (-1 == listBoxIndexes.FindString(strIndex))
            {
                int nTime = (nMin * 60 + nSec) * 75 + nFrame;

                if (nTime <= 0 || nTime >= m_nPlayTime * 75)
                {
                    MessageBox.Show("Index is invalid.", "Track properties");
                    return;
                }

                listBoxIndexes.Items.Add(new IndexesListItem(strIndex, nTime));
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            int nSelected = listBoxIndexes.SelectedIndex;

            if (nSelected >= 0)
            {
                listBoxIndexes.Items.RemoveAt(nSelected);
            }
        }
        
    }
}