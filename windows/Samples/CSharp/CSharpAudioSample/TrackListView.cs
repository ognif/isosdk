using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpAudioSample
{
    public class KAudioFileProperty
    {   
        public string Performer;
        public string Title;
        public string Arranger;
        public string Composer;
        public string SongWriter;
        public string Message;
        public string McnIsrc;
        public int Pause;
        public bool PauseInFrames;
        public List<int> vIndexes;
        public int nPlayTime;

        public KAudioFileProperty()
        {
            Pause = 2;
            PauseInFrames = false;
            Performer = Title = Arranger = 
            Composer = SongWriter = 
            Message = McnIsrc = "";
            nPlayTime = 0;
            vIndexes = new List<int>();
        }
        
        public KAudioFileProperty(KAudioFileProperty rhs)
        {
            Pause = rhs.Pause;
            PauseInFrames = rhs.PauseInFrames;
            Performer = rhs.Performer;
            Title = rhs.Title;
            Arranger = rhs.Arranger;
            Composer = rhs.Composer;
            SongWriter = rhs.SongWriter;
            Message = rhs.Message;
            McnIsrc = rhs.McnIsrc;
            nPlayTime = rhs.nPlayTime;
            vIndexes = rhs.vIndexes;
        }
    }

    public class IndexesListItem
    {
        public String  m_strText;
        public int     m_nData;

        public IndexesListItem(String strText, int nData)
        {
            m_strText = strText;
            m_nData = nData;
        }

        public override string ToString()
        {
            return m_strText;
        }
    }

    class TrackListView
    {
        private ListView m_listView;
        private Burner m_burner;
        private string m_strCurDirectory;
        private int m_nAllLength;
        private KAudioFileProperty m_DiskCDText;
        
        public TrackListView(ListView listView, Burner burner)
        {
            m_burner = burner;

            m_listView = listView;            
            m_listView.Columns.Add("File Name",350);
            m_listView.Columns.Add("Play Time",100);

            m_nAllLength = 0;

            m_strCurDirectory = @"\";

            m_DiskCDText = new KAudioFileProperty();
        }
        public bool AddFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.CheckFileExists = true;
            ofd.CheckPathExists = true;
            ofd.Filter = "MP3 files (*.mp3)|*.mp3|Ape files (*.ape)|*.ape|Opus files (*.opus)|*.opus|Wave files (*.wav)|*.wav|Oga files (*.oga)|*.oga|OGG Vorbis files(*.ogg)|*.ogg|Windows Media Files(*.wma)|*.wma|VQF Files (*.vqf)|*.vqf|AAC FIles(*.aac)|*.aac|M4A Files(*.m4a)|*.m4a|WavPack files (*.wv)|*.wv|FLAC files(*.flac)|*.flac";
            ofd.Multiselect = true;
            ofd.Title = "Select files to add";

            bool bRes = true;

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                foreach (string fileName in ofd.FileNames)
                {
                    bool b = DoAddFile(fileName);
                    bRes = bRes && b;
                }
            }

            return bRes;
        }

        public int GetSizeInSeconds()
        {
            return m_nAllLength;
        }

        private bool DoAddFile(string fullName)
        {            
            bool bRes = m_burner.AddFile(fullName, m_strCurDirectory, "", false, SavePathOption.DontSavePath);
            if (!bRes)
            {
                CommonNet.Functions.HandleError(m_burner);
                return bRes;
            }

            double dPlayTime = m_burner.GetPrecisePlayTime(fullName);
            int nPlayTime = System.Convert.ToInt32(Math.Ceiling(dPlayTime));

            m_nAllLength += nPlayTime;

            ListViewItem item = new ListViewItem(fullName);
            
            KAudioFileProperty prop = new KAudioFileProperty();
            prop.nPlayTime = nPlayTime;
            item.Tag = prop;

            item.SubItems.Add((nPlayTime / 3600).ToString("00:") + ( (nPlayTime % 3600) / 60).ToString("00:") + (nPlayTime % 60).ToString("00"));
            
            m_listView.Items.Add(item);            
            return true;
        }

        public bool DeleteSelected()
        {
            if (m_listView.SelectedItems.Count == 0)
            {
                return false;
            }

            foreach (ListViewItem lvi in m_listView.SelectedItems)
            {
                if (!DeleteItem(lvi))
                {
                    return false;
                }
            }

            return true;        
        }

        private bool DeleteItem(ListViewItem lvi)
        {
            if (!m_burner.RemoveFile((lvi.Index + 1).ToString("00"), m_strCurDirectory))
            {
                CommonNet.Functions.HandleError(m_burner);
                return false;
            }

            m_nAllLength -= m_burner.GetPlayTime(lvi.Text);
            m_listView.Items.Remove(lvi);
            return true;
        }

        public void ResetList()
        {
            foreach (ListViewItem lvi in m_listView.Items)
            {
                DeleteItem(lvi);
            }
        }
        public void Play()
        {
            if (m_listView.SelectedItems.Count == 0)
            {
                return;
            }
            m_burner.PlayAudioFile(m_listView.SelectedItems[0].Text);
            CommonNet.Functions.HandleError(m_burner);
        }

        public void TrackCDText()
        {
            if (m_listView.SelectedItems.Count != 1)
            {
                MessageBox.Show("Select one track, please...", "Message");
                return;
            }

            CDTextDlg dlg = new CDTextDlg(false, 
                m_listView.SelectedItems[0].Tag as KAudioFileProperty);
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                KAudioFileProperty property = dlg.GetProperty();
                m_listView.SelectedItems[0].Tag = property;


                AudioFileProperty audio_property = new AudioFileProperty();
                audio_property.SourceFilePath = 
                    (m_listView.SelectedItems[0].Index + 1).ToString("00");
                audio_property.Title = property.Title;
                audio_property.Performer = property.Performer;
                audio_property.SongWriter = property.SongWriter;
                audio_property.Composer = property.Composer;
                audio_property.Arranger = property.Arranger;
                audio_property.Message = property.Message;
                audio_property.McnIsrc = property.McnIsrc;
                audio_property.Pause = property.Pause;
                audio_property.PauseInFrames = property.PauseInFrames;

                audio_property.IndexesLength = property.vIndexes.Count;
                audio_property.Indexes = new int[property.vIndexes.Count];
                property.vIndexes.CopyTo(audio_property.Indexes);


                bool bRes = m_burner.SetAudioFileProperty(audio_property);
                CommonNet.Functions.HandleError(m_burner);
            }
        }

        public void DiskCDText()
        {
            CDTextDlg dlg = new CDTextDlg(true, m_DiskCDText);
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                KAudioFileProperty property = dlg.GetProperty();
                m_DiskCDText = property;

                AudioFileProperty audio_property = new AudioFileProperty();
                audio_property.SourceFilePath = m_strCurDirectory;
                audio_property.Title = property.Title;
                audio_property.Performer = property.Performer;
                audio_property.SongWriter = property.SongWriter;
                audio_property.Composer = property.Composer;
                audio_property.Arranger = property.Arranger;
                audio_property.Message = property.Message;
                audio_property.McnIsrc = property.McnIsrc;
                audio_property.Pause = property.Pause;
                
                audio_property.IndexesLength = property.vIndexes.Count;
                audio_property.Indexes = new int[property.vIndexes.Count];
                property.vIndexes.CopyTo(audio_property.Indexes);

                bool bRes = m_burner.SetAudioFileProperty(audio_property);
                CommonNet.Functions.HandleError(m_burner);
            }            
        }

        public void SetRootDirectory(string path)
        {
            m_strCurDirectory = path;
        }
    }
}
