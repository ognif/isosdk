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
    public partial class KSaveDiscDialog : Form
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
        private String m_strFileName = "";
        private ImageFormat m_Format;
        private DateTime m_StartTime;

        protected KSaveDiscDialog()
        {
            InitializeComponent();
        }

        public KSaveDiscDialog(Burner burner, String strFileName, ImageFormat Format)
        {
            InitializeComponent();

            m_burner = burner;
            m_strFileName = strFileName;
            m_Format = Format;
        }

        private void KSaveDiscDialog_Load(object sender, EventArgs e)
        {
            //--------------------------------------------------
	        //Set the callbacks to receive infos later
	        //--------------------------------------------------
        	
	        m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnJobDoneEvent);
            m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnProcessEvent);
            m_burner.BurnDoneEvent += new Burner.BurnDoneEventHandler(OnBurnDoneEvent);

	        m_enState = State.ST_PROCESSING;
        		
	        CreateImageParams createImageParams = new CreateImageParams();
            createImageParams.ErrorParams = new ReadErrorCorrectionParams();

	        createImageParams.ErrorParams.ErrorCorrection = true;
            createImageParams.ErrorParams.HardwareRetryCount = 20;
            createImageParams.ErrorParams.SoftwareRetryCount = 20;
            createImageParams.ErrorParams.BlankBadSectors = true;
            createImageParams.BadSectorsFilePath = "";
            createImageParams.ImagePath = m_strFileName;
	        createImageParams.ImageType = m_Format;
        		
	        m_burner.CreateImage(createImageParams, ImageTask.Create);
	        CommonNet.Functions.HandleError(m_burner);

            m_StartTime = DateTime.Now;
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

            SDLabelTime.Text = Now.ToLongTimeString();

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
                SetProgress((int)e.m_fPercent, e.m_dBytesWritten, 
                    (int)e.m_dImageSize, (int)e.m_fDeviceBuffer * 1000);
            }
        }

        private void SetProgress(int nProgress, double dCurrentSector, double dTotalSectors, int nErrorsCount)
        {
            progressBar.Value = Convert.ToInt32(nProgress);

            SDLabelTotal.Text = Convert.ToInt64(dTotalSectors).ToString();
            SDLabelSector.Text = Convert.ToInt64(dCurrentSector).ToString();
            SDLabelErrors.Text = nErrorsCount.ToString();
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

        private void KSaveDiscDialog_FormClosing(object sender, FormClosingEventArgs e)
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