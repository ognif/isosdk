using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using IsoSDK;

namespace CSharpImageEditSample
{
    public partial class KSaveTrackDialog : Form
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

        private Burner m_burner;
        private State m_enState = State.ST_NONE;
        private int m_nTrackNumber;
        private String m_strFilePath;
        private SaveTrackFileFormat m_FileFormat;        
        private double m_dTotalSize;
        private DateTime m_StartTime;

        private KSaveTrackDialog()
        {   
        }

        public KSaveTrackDialog(Burner burner, int nTrackNumber, 
            String strFilePath, SaveTrackFileFormat FileFormat)
        {
            m_burner = burner;

	        m_nTrackNumber = nTrackNumber;
	        m_strFilePath = strFilePath;
            m_FileFormat = FileFormat;

            InitializeComponent();
        }

        private void KSaveTrackDialog_Load(object sender, EventArgs e)
        {
	        //--------------------------------------------------
	        //Set the callbacks to receive infos later
	        //--------------------------------------------------

            m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnJobDoneEvent);
            m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnProcessEvent);
            m_burner.BurnDoneEvent += new Burner.BurnDoneEventHandler(OnBurnDoneEvent);

            m_enState = State.ST_PROCESSING;
        	
	        m_burner.SaveTrackToFile((int)DeviceIndex.Read, m_nTrackNumber, 
                m_strFilePath, m_FileFormat);

	        CommonNet.Functions.HandleError(m_burner);

            m_StartTime = DateTime.Now;
            m_dTotalSize = 0;

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

        private void timer_Tick(object sender, EventArgs e)
        {
            DateTime Now = new DateTime(((TimeSpan)(DateTime.Now - m_StartTime)).Ticks);

            STLabelTime.Text = Now.ToLongTimeString();

            timer.Start();
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
                catch (Exception) { }
            }
            else
            {
                switch (m_enState)
                {
                    case State.ST_PROCESSING:
                    case State.ST_ABORTED:

                        m_enState = State.ST_DONE;
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
            buttonAbort.Enabled = true;
            buttonAbort.Text = "&Close";
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
                STLabelTotal.Text = Convert.ToInt64(dSize).ToString();
            }

            STLabelBytes.Text = Convert.ToInt64(dBytesWritten).ToString();
        }

        private void buttonAbort_Click(object sender, EventArgs e)
        {
            if (m_enState == State.ST_PROCESSING)
            {
                m_enState = State.ST_ABORTED;

                m_burner.Abort();

                if (ErrorCode.SdkErrorNo == m_burner.GetLastError())
                {
                    buttonAbort.Enabled = false;
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

        private void KSaveTrackDialog_FormClosing(object sender, FormClosingEventArgs e)
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
    }
}