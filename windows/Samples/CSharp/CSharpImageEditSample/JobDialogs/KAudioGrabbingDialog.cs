using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpImageEditSample
{
    public partial class KAudioGrabbingDialog : Form
    {
        enum State
        {
            ST_NONE,
            ST_PROCESSING,
            ST_ABORTED,
            ST_CANCELLED,
            ST_DONE,
        };

        delegate void OnJobDoneEventCallback(object sender, EventArgs e);
        delegate void SetProgressCallback(object sender, ProcessEventArgs e);
        delegate void OnBurnDoneEventCallback(object sender, BurnDoneEventArgs e);

        private List<uint> m_vTracks = null;
        private Burner m_burner;
        private State m_enState = State.ST_NONE;
        private double m_dTotalSize;
        private DateTime m_StartTime;
        private int m_nCurrentTrack = 0;

        protected KAudioGrabbingDialog()
        {
            InitializeComponent();
        }

        public KAudioGrabbingDialog(Burner burner, List<uint> vTracks)
        {
            m_burner = burner;
            m_vTracks = vTracks;

            InitializeComponent();
        }

        private void KAudioGrabbingDialog_Load(object sender, EventArgs e)
        {
            cmbEncoder.SelectedIndex = 0;
            cmbBitrateType.SelectedIndex = 0;
            cmbCbrBitrate.SelectedIndex = 0;
            cmbVbrBitrateMin.SelectedIndex = 0;
            cmbVbrBitrateMax.SelectedIndex = 0;
            cmbQuality.SelectedIndex = 0;
            cmbTagChoise.SelectedIndex = 0;


            //--------------------------------------------------
            //Set the callbacks to receive infos later
            //--------------------------------------------------

            m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnJobDoneEvent);
            m_burner.BurnDoneEvent += new Burner.BurnDoneEventHandler(OnBurnDoneEvent);
            m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnProcessEvent);

            m_enState = State.ST_NONE;
        }

        private uint ComboIndex2Bitrate(int nIndex)
        {
            switch (nIndex)
            {
                case 0:
                    return 64;
                case 1:
                    return 96;
                case 2:
                    return 128;
                case 3:
                    return 192;
                case 4:
                    return 256;
                case 5:
                    return 320;
                default:
                    return 128;
            }
        }

        private AudioFormat ComboIndex2AudioFormat(int nIndex)
        {
            switch (nIndex)
            {
                case 0:
                    return AudioFormat.Mp3;
                case 1:
                    return AudioFormat.Aac;
                case 2:
                    return AudioFormat.Ogg;
                case 3:
                    return AudioFormat.Opus;
                case 4:
                    return AudioFormat.Flac;
                default:
                    return AudioFormat.Mp3;
            }
        }

        private String ComboIndex2FileExt(int nIndex)
        {
            switch (ComboIndex2AudioFormat(nIndex))
            {
                case AudioFormat.Mp3:
                    return ".mp3";

                case AudioFormat.Aac:
                    return ".aac";

                case AudioFormat.Ogg:
                    return ".ogg";

                case AudioFormat.Opus:
                    return ".opus";

                case AudioFormat.Flac:
                    return ".flac";

                default:
                    return "";
            }
        }

        private TagChoiceType ComboIndex2TagChoise(int nIndex)
        {
            switch (nIndex)
            {
                case 0:
                    return TagChoiceType.None;
                case 1:
                    return TagChoiceType.CdText;
                case 2:
                    return TagChoiceType.FreeDb;
                case 3:
                    return TagChoiceType.CdText_FreeDb;
                case 4:
                    return TagChoiceType.FreeDb_CdText;
                default:
                    return TagChoiceType.None;
            }
        }

        private void buttonBrowse_Click(object sender, EventArgs e)
        {   
	        String strExt = ComboIndex2FileExt(cmbEncoder.SelectedIndex);		
	        
            String strSaveParam = String.Format("Supported format files (*{0:S} )|*{0:S}", strExt);

            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = strSaveParam;

            if (dlg.ShowDialog() == DialogResult.OK)            
            {
		        String strFileName = dlg.FileName;

		        if (strFileName.Length == 0)
		        {
			        return;
		        }

                textBoxPath.Text = strFileName;
	        }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            DateTime Now =
                new DateTime(((TimeSpan)(DateTime.Now - m_StartTime)).Ticks);

            labelTime.Text = Now.ToLongTimeString();

            timer.Start();
        }

        private void RestoreEvents()
        {
            m_burner.JobDoneEvent -= new Burner.JobDoneEventHandler(OnJobDoneEvent);
            m_burner.ProcessEvent -= new Burner.ProcessEventHandler(OnProcessEvent);
            m_burner.BurnDoneEvent -= new Burner.BurnDoneEventHandler(OnBurnDoneEvent);
        }

        private void OnBurnDoneEvent(object sender, BurnDoneEventArgs e)
        {
            if (e.m_strError.Length > 0)
            {
                if (progressBar.InvokeRequired)
                {
                    OnBurnDoneEventCallback d = new OnBurnDoneEventCallback(OnBurnDoneEvent);

                    try
                    {
                        this.Invoke(d, new object[] { sender, e });
                    }
                    catch (Exception) { };
                }
                else
                {
                    MessageBox.Show(e.m_strError);
                }
            }
        }

        private void OnJobDoneEvent(object sender, EventArgs e)
        {
            if (progressBar.InvokeRequired)
            {
                OnJobDoneEventCallback d = new OnJobDoneEventCallback(OnJobDoneEvent);

                try
                {
                    this.Invoke(d, new object[] { sender, e });
                }
                catch (Exception) { };
            }
            else
            {
                switch (m_enState)
                {
                    case State.ST_PROCESSING:

                        if (m_nCurrentTrack == m_vTracks.Count)
                        {
                            Done();
                        }
                        else
                        {
                            labelTrack.Text = m_vTracks[m_nCurrentTrack].ToString();

                            String temp = "Track" + m_vTracks[m_nCurrentTrack].ToString();

                            String strSavePath = textBoxPath.Text;

                            strSavePath = strSavePath.Substring(0, strSavePath.LastIndexOf('\\') + 1);
                            strSavePath += temp;
                            strSavePath += ComboIndex2FileExt(cmbEncoder.SelectedIndex);
                            textBoxPath.Text = strSavePath;

                            m_enState = State.ST_NONE;
                            buttonConvert.Text = "&Convert";
                        }

                    break;

                    case State.ST_ABORTED:

                        Done();

                    break;

                    case State.ST_CANCELLED:

                        this.Close();

                    break;
                }
            }
        }

        private void Done()
        {
            m_enState = State.ST_DONE;
            buttonConvert.Enabled = true;
            buttonConvert.Text = "&Close";
            timer.Stop();
        }

        private void OnProcessEvent(object sender, ProcessEventArgs e)
        {
            if (progressBar.InvokeRequired)
            {
                SetProgressCallback d = new SetProgressCallback(OnProcessEvent);

                try
                {
                    this.Invoke(d, new object[] { sender, e });
                }
                catch (Exception) { };
            }
            else
            {
                SetProgress(e.m_fPercent, e.m_fDeviceBuffer, e.m_dImageSize, e.m_dBytesWritten);
            }
        }

        private void SetProgress(float fBurnPercent, float fBuffer, double dSize, double dBytesWritten)
        {
            progressBar.Value = Convert.ToInt32(fBurnPercent);

            if (m_dTotalSize == 0 || m_dTotalSize != dSize)
            {
                m_dTotalSize = dSize;
                labelSize.Text = Convert.ToInt64(dSize).ToString();
            }

            labelBytes.Text = Convert.ToInt64(dBytesWritten).ToString();
        }

        private void buttonConvert_Click(object sender, EventArgs e)
        {
            if (m_enState == State.ST_NONE && m_nCurrentTrack < m_vTracks.Count)
            {
                AudioGrabbingParams AudioParams = new AudioGrabbingParams();
                String strSavePath;

                switch(cmbBitrateType.SelectedIndex)
                {
                    case 0:
                        AudioParams.BitrateType = BitrateType.Constant;
                        break;
                    case 1:
                        AudioParams.BitrateType = BitrateType.Variable;
                        break;
                    case 3:
                        AudioParams.BitrateType = BitrateType.Average;
                        break;
                }



                AudioParams.Bitrate = ComboIndex2Bitrate(cmbCbrBitrate.SelectedIndex);
                AudioParams.MinBitrate = ComboIndex2Bitrate(cmbVbrBitrateMin.SelectedIndex);
                AudioParams.MaxBitrate = ComboIndex2Bitrate(cmbVbrBitrateMax.SelectedIndex);
                AudioParams.Quality = ComboIndex2Bitrate(cmbQuality.SelectedIndex);
                AudioParams.EncoderType = ComboIndex2AudioFormat(cmbEncoder.SelectedIndex);
                AudioParams.TagChoice = ComboIndex2TagChoise(cmbTagChoise.SelectedIndex);

                if ((int)AudioParams.TagChoice > 1)
                {
                    AudioParams.NetworkTags = m_burner.TagsFromNetworkDialog(-2);
                }

                strSavePath = textBoxPath.Text;

                if (strSavePath.Length == 0)
                {
                    MessageBox.Show("Please, specify the file name.", "Error");
                    return;
                }

                m_burner.GrabAudioTrack(AudioParams, m_vTracks[m_nCurrentTrack++], strSavePath);


                if (!CommonNet.Functions.HandleError(m_burner))
                {
                    m_StartTime = DateTime.Now;

                    timer.Start();

                    m_enState = State.ST_PROCESSING;
                    buttonConvert.Text = "&Abort";

                    cmbEncoder.Enabled = false;
                    cmbBitrateType.Enabled = false;
                    cmbCbrBitrate.Enabled = false;
                    cmbVbrBitrateMin.Enabled = false;
                    cmbVbrBitrateMax.Enabled = false;
                    cmbQuality.Enabled = false;
                    cmbTagChoise.Enabled = false;
                    buttonBrowse.Enabled = false;
                }
            }
            else if (m_enState == State.ST_PROCESSING)
            {
                m_enState = State.ST_ABORTED;

                m_burner.Abort();

                if (ErrorCode.SdkErrorNo == m_burner.GetLastError())
                {
                    buttonConvert.Enabled = false;
                }
                else
                {
                    Done();
                }
            }
            else
            {
                RestoreEvents();
                this.Close();
            }
        }

        private void KAudioGrabbingDialog_FormClosing(object sender, FormClosingEventArgs e)
        {
            m_enState = State.ST_CANCELLED;
            m_burner.Abort();

            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
            {
                timer.Stop();
                RestoreEvents();

                e.Cancel = false;
            }
            else
            {
                e.Cancel = true;
            }
        }

        private void cmbEncoder_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool bVariablePossible = false;
            bool bAveragePossible = false;

            switch (ComboIndex2AudioFormat(cmbEncoder.SelectedIndex))
	        {
		        case AudioFormat.Mp3:
                    bAveragePossible = true;
                    bVariablePossible = true;
                    break;
                case AudioFormat.Aac:
                case AudioFormat.Opus:
		        case AudioFormat.Ogg:
			        bVariablePossible = true;
		        break;
		        case AudioFormat.Flac:
			        bVariablePossible = false;
		        break;
	        }

            cmbBitrateType.Items.Clear();
            cmbBitrateType.Items.Add("Constant");

	        if (bVariablePossible)
	        {
                cmbBitrateType.Items.Add("Variable");
	        }
            if (bAveragePossible)
            {
                cmbBitrateType.Items.Add("Average");
            }

            cmbBitrateType.SelectedIndex = 0;

            String strFileName = textBoxPath.Text;

            if (strFileName.Length != 0)
            {
                String strExt = ComboIndex2FileExt(cmbEncoder.SelectedIndex);

                int pos = strFileName.LastIndexOf('.');

                if (pos != -1)
                {
                    strFileName = strFileName.Substring(0, pos) + strExt;
                }
                else
                {
                    strFileName += strExt;
                }

                textBoxPath.Text = strFileName;
            }
        }

        private void cmbBitrateType_SelectedIndexChanged(object sender, EventArgs e)
        {
            int item = cmbBitrateType.SelectedIndex;

            switch (ComboIndex2AudioFormat(cmbEncoder.SelectedIndex))
            {
                case AudioFormat.Mp3:
                    switch (item)
                    {
                        case 0:
                            cmbCbrBitrate.Enabled = true;
                            cmbVbrBitrateMin.Enabled = false;
                            cmbVbrBitrateMax.Enabled = false;
                            cmbQuality.Enabled = false;
                            break;
                        case 1:
                            cmbCbrBitrate.Enabled = false;
                            cmbVbrBitrateMin.Enabled = true;
                            cmbVbrBitrateMax.Enabled = true;
                            cmbQuality.Enabled = false;
                            break;
                        case 2:
                            cmbCbrBitrate.Enabled = true;
                            cmbVbrBitrateMin.Enabled = false;
                            cmbVbrBitrateMax.Enabled = false;
                            cmbQuality.Enabled = false;
                            break;

                    }
                    break;
                case AudioFormat.Ogg:
                    switch (item)
                    {
                        case 0:
                            cmbCbrBitrate.Enabled = true;
                            cmbVbrBitrateMin.Enabled = false;
                            cmbVbrBitrateMax.Enabled = false;
                            cmbQuality.Enabled = false;
                            break;
                        case 1:
                            cmbCbrBitrate.Enabled = false;
                            cmbVbrBitrateMin.Enabled = true;
                            cmbVbrBitrateMax.Enabled = true;
                            cmbQuality.Enabled = false;
                            break;

                    }
                    break;
                case AudioFormat.Aac:
                    switch (item)
                    {
                        case 0:
                            cmbCbrBitrate.Enabled = true;
                            cmbVbrBitrateMin.Enabled = false;
                            cmbVbrBitrateMax.Enabled = false;
                            cmbQuality.Enabled = false;
                            break;
                        case 1:
                            cmbCbrBitrate.Enabled = false;
                            cmbVbrBitrateMin.Enabled = false;
                            cmbVbrBitrateMax.Enabled = false;
                            cmbQuality.Enabled = true;
                            break;

                    }
                    break;
                case AudioFormat.Opus:
                    cmbCbrBitrate.Enabled = true;
                    cmbVbrBitrateMin.Enabled = false;
                    cmbVbrBitrateMax.Enabled = false;
                    cmbQuality.Enabled = true;
                    break;
                case AudioFormat.Flac:
                    cmbCbrBitrate.Enabled = false;
                    cmbVbrBitrateMin.Enabled = false;
                    cmbVbrBitrateMax.Enabled = false;
                    cmbQuality.Enabled = true;
                    break;
            }
        }

        private void cmbVbrBitrateMin_SelectedIndexChanged(object sender, EventArgs e)
        {
            uint nMinBitrate = ComboIndex2Bitrate(cmbVbrBitrateMin.SelectedIndex);
            uint nMaxBitrate = ComboIndex2Bitrate(cmbVbrBitrateMax.SelectedIndex);

            if (nMinBitrate > nMaxBitrate)
            {
                cmbVbrBitrateMax.SelectedIndex = cmbVbrBitrateMin.SelectedIndex;
            }
        }

        private void cmbVbrBitrateMax_SelectedIndexChanged(object sender, EventArgs e)
        {
            uint nMinBitrate = ComboIndex2Bitrate(cmbVbrBitrateMin.SelectedIndex);
            uint nMaxBitrate = ComboIndex2Bitrate(cmbVbrBitrateMax.SelectedIndex);

            if (nMaxBitrate < nMinBitrate)
            {
                cmbVbrBitrateMin.SelectedIndex = cmbVbrBitrateMax.SelectedIndex;
            }
        }
    }
}