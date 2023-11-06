using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using IsoSDK;

namespace CommonNet
{
    namespace Dialogs
    {
        public partial class BurnDlgDevel : Form
        {
            delegate void AddLogLineCallback(string text);
            delegate void SetProgressCallback(int progress, int buffer);
            delegate void OnJobDoneEventCallback(object sender, EventArgs e);
            delegate void OnBurnFileEventCallback(object sender, BurnFileEventArgs e);
            delegate bool OnCompareFilesForArrangementEventCallback(object sender, CompareFilesForArrangementEventArgs  e);

            enum BurnState
            {
                ST_NONE,
                ST_BURN,
                ST_FINALIZE,
                ST_VERIFY
            };

            private Burner m_burner;
            private bool m_bImagePathChanged;

            private bool m_bInitialized;

            public bool CanStart
            {
                get
                {
                    return m_bInitialized;
                }
            }

            BurnState m_enState = BurnState.ST_NONE;

            string m_strLabel;
            string m_strDevice;
            System.DateTime m_tmStart = System.DateTime.Now;

            const string BURN_TITLE_FORMAT = "{0}% written on {1} [{2}]";
            const string VERIFY_TITLE_FORMAT = "{0}% verified on {1} [{2}]";

            private string m_strIsoFilePath;

            public BurnDlgDevel(Burner burner, string isoImagePath)
            {
                InitializeComponent();
                m_bInitialized = false;
                m_bImagePathChanged = false;
                m_burner = burner;
                m_strIsoFilePath = isoImagePath;

                m_burner.BurnDoneEvent += new Burner.BurnDoneEventHandler(OnBurnDoneEvent);
                m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnJobDoneEvent);
                m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnProcessEvent);
                m_burner.FinalizeEvent += new Burner.FinalizeEventHandler(OnFinalizeEvent);
                m_burner.StartVerifyEvent += new Burner.StartVerifyEventHandler(OnStartVerifyEvent);
                m_burner.VerifyDoneEvent += new Burner.VerifyDoneEventHandler(OnVerifyDoneEvent);
                m_burner.VerifyFileEvent += new Burner.VerifyFileEventHandler(OnVerifyFileEvent);
                m_burner.VerifyErrorEvent += new Burner.VerifyErrorEventHandler(OnVerifyErrorEvent);
                m_burner.BurnFileEvent += new Burner.BurnFileEventHandler(OnBurnFileEvent);
                m_burner.CompareFilesForArrangementEvent += new Burner.CompareFilesForArrangementHandler(OnCompareFile);

                // Get volume label

                m_strLabel = m_burner.Options.VolumeLabel;

                m_strDevice = m_burner.BurnDevice + ":";

                if (m_strDevice.StartsWith("#"))// Image file selected.
                {
                    m_bImagePathChanged = true;

                    SaveFileDialog dlg = new SaveFileDialog();
                    ProjectType pt = m_burner.GetProjectType();
                    switch (pt)
                    {                    
                        case ProjectType.Audio:
                        case ProjectType.MixedMode:
                        case ProjectType.Vcd:
                        case ProjectType.Svcd:
                            dlg.Filter = "CUE/BIN Files (*.cue)|*.cue";
                        break;
                        
                        default:
                            dlg.Filter = "ISO files (*.iso)|*.iso";
                        break;
                    }
                    
                    if (dlg.ShowDialog() == DialogResult.OK)
                    {
                        string filename = dlg.FileName;
                        m_burner.SetImageFilePath(filename);
                        m_burner.Options.EjectAfterBurn = true;
                        m_burner.Options.TestBurn = false;
                        m_burner.Options.VerifyAfterBurn = false;
                    }
                    else
                    {
                        m_bInitialized = false;
                        return;
                    }
                }
                // Update window's title

                this.Text = String.Format(BURN_TITLE_FORMAT, 0, m_strDevice, m_strLabel);

                //--------------------------------------------------
                // Start burning
                //--------------------------------------------------

                // It's mandatory to prepare project before burning

                
                AddLogLine("Prepare Collection");

                if (m_strIsoFilePath.Length == 0)
                    m_burner.Prepare();

                HandleError(m_burner.GetLastError());
                if (m_burner.GetLastError() == ErrorCode.SdkErrorNo)
                {
                    // Get current burn speed

                    int nSpeed = m_burner.BurnSpeed;

                    if (nSpeed == 0)
                        nSpeed = m_burner.GetMaxBurnSpeed(0);

                    // Update speed label

                    lblSpeed.Text = String.Format("{0} KB/s", nSpeed);

                    // Project is successfully prepared - burn it

                    AddLogLine("Start Burning...");
                    if (m_strIsoFilePath.Length == 0) { 
                        m_burner.Burn();
                        HandleError(m_burner.GetLastError());
                    }
                    else
                    {
                        BurnIsoOptions options = new BurnIsoOptions();
                        options.AutoErase = true;
                        options.EjectAfterBurn = true;
                        options.FinalizeDisk = true;
                        options.PerformOPC = true;
                        options.UnderrunProtection = true;

                        m_burner.BurnISO(m_strIsoFilePath, options);
                    }

                    if (m_burner.GetLastError() == ErrorCode.SdkErrorNo)
                    {
                        // Burning successfully started
                        m_enState = BurnState.ST_BURN;
                        timer1.Enabled = true;
                        m_bInitialized = true;
                    }
                    else
                    {
                        m_bInitialized = false;
                        HandleError(m_burner.GetLastError());
                    }
                }
                else
                {
                    m_bInitialized = false;
                    HandleError(m_burner.GetLastError());
                }
            }

            public void ResetCallbacks()
            {
                m_burner.BurnDoneEvent -= new Burner.BurnDoneEventHandler(OnBurnDoneEvent);
                m_burner.JobDoneEvent -= new Burner.JobDoneEventHandler(OnJobDoneEvent);
                m_burner.ProcessEvent -= new Burner.ProcessEventHandler(OnProcessEvent);
                m_burner.FinalizeEvent -= new Burner.FinalizeEventHandler(OnFinalizeEvent);
                m_burner.StartVerifyEvent -= new Burner.StartVerifyEventHandler(OnStartVerifyEvent);
                m_burner.VerifyDoneEvent -= new Burner.VerifyDoneEventHandler(OnVerifyDoneEvent);
                m_burner.VerifyFileEvent -= new Burner.VerifyFileEventHandler(OnVerifyFileEvent);
                m_burner.VerifyErrorEvent -= new Burner.VerifyErrorEventHandler(OnVerifyErrorEvent);
                m_burner.BurnFileEvent -= new Burner.BurnFileEventHandler(OnBurnFileEvent);
                m_burner.CompareFilesForArrangementEvent -= new Burner.CompareFilesForArrangementHandler(OnCompareFile);
            }

            private void AddLogLine(string text)
            {
                if (lstLog.InvokeRequired)
                {
                    AddLogLineCallback d = new AddLogLineCallback(AddLogLine);
                    this.Invoke(d, new object[] { text });
                }
                else
                {
                    lstLog.Items.Add(text);
                }
            }

            private void SetProgress(int progress, int buffer)
            {
                if (pgsTotal.InvokeRequired)
                {
                    SetProgressCallback d = new SetProgressCallback(SetProgress);
                    this.Invoke(d, new object[] { progress, buffer });
                }
                else
                {
                    pgsBuffer.Value = buffer;
                    pgsTotal.Value = progress;

                    UpdateTitle();
                }
            }

            private void UpdateTitle()
            {
                if (m_enState == BurnState.ST_BURN || m_enState == BurnState.ST_FINALIZE)
                {
                    int progress = m_enState == BurnState.ST_BURN ? pgsTotal.Value : 100;
                    if (progress != 0)
                    {
                        this.Text = String.Format(BURN_TITLE_FORMAT, progress, m_strDevice, m_strLabel);
                    }
                }
                else if (m_enState == BurnState.ST_VERIFY)
                {
                    if (pgsTotal.Value != 0)
                    {
                        this.Text = String.Format(VERIFY_TITLE_FORMAT, pgsTotal.Value, m_strDevice, m_strLabel);
                    }
                }
            }

            private void HandleError(ErrorCode errorCode)
            {
                if (errorCode != 0)
                {
                    // Get error description
                    string text = m_burner.GetText((Int32)errorCode);

                    AddLogLine(text);
                }
            }

            private void OnFinalizeEvent(object sender, EventArgs e)
            {
                AddLogLine("Finalize...");
                m_enState = BurnState.ST_FINALIZE;
            }

            private void OnBurnDoneEvent(object sender, BurnDoneEventArgs e)
            {
                if (e.m_strError.Length > 0)
                {
                    AddLogLine(e.m_strError);
                    AddLogLine("Burn Done With Errors");
                }
                else
                {
                    AddLogLine("Burn Done");
                }

                SetProgress(0, 0);
            }

            private void OnProcessEvent(object sender, ProcessEventArgs e)
            {
                SetProgress((int)e.m_fPercent, (int)e.m_fCache);
            }

            private void OnStartVerifyEvent(object sender, EventArgs e)
            {
                AddLogLine("Start Verify...");
                m_enState = BurnState.ST_VERIFY;
            }

            private void OnVerifyFileEvent(object sender, VerifyFileEventArgs e)
            {
                AddLogLine(e.m_strFileName);
            }

            private void OnVerifyErrorEvent(object sender, VerifyErrorEventArgs e)
            {
                AddLogLine(e.m_strError + ": " + e.m_strFileName);
            }

            private void OnVerifyDoneEvent(object sender, VerifyDoneEventArgs e)
            {
                AddLogLine("Verify complete");
                SetProgress(0, 0);
            }

            private void OnJobDoneEvent(object sender, EventArgs e)
            {
                if (btnCancel.InvokeRequired)
                {
                    OnJobDoneEventCallback d = new OnJobDoneEventCallback(OnJobDoneEvent);
                    this.Invoke(d, new object[] { sender, e });
                }
                else
                {
                    btnCancel.Text = "Close";
                    m_enState = BurnState.ST_NONE;
                    timer1.Enabled = false;
                }
            }

            private bool OnCompareFile(object sender, CompareFilesForArrangementEventArgs e)
            {
                if (lblFile.InvokeRequired)
                {
                    OnCompareFilesForArrangementEventCallback d = new OnCompareFilesForArrangementEventCallback(OnCompareFile);
                    this.Invoke(d, new object[] { sender, e });
                }
                else
                {
                    lblFile.Text = e.m_file1.ToString();
                }
                return true;
            }

            private void OnBurnFileEvent(object sender, BurnFileEventArgs e)
            {
                if (lblFile.InvokeRequired)
                {
                    OnBurnFileEventCallback d = new OnBurnFileEventCallback(OnBurnFileEvent);
                    this.Invoke(d, new object[] { sender, e });
                }
                else
                {
                    lblFile.Text = e.m_strFileName;
                }
                
            }

            private void btnCancel_Click(object sender, EventArgs e)
            {
                if (m_enState != BurnState.ST_NONE)
                {
                    m_burner.Abort();
                }
                else
                {
                    this.Close();
                }
            }

            private void btnSaveLog_Click(object sender, EventArgs e)
            {
                SaveFileDialog dlg = new SaveFileDialog();
                dlg.Filter = "All files (*.*)|*.*";
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    m_burner.SaveLogToFile(dlg.FileName);
                }
            }

            private void timer1_Tick(object sender, EventArgs e)
            {
                System.TimeSpan elapsed = System.DateTime.Now - m_tmStart;
                lblTime.Text = String.Format("{0}:{1}:{2}", elapsed.Hours.ToString("##"), elapsed.Minutes.ToString("##"), elapsed.Seconds.ToString("##"));
            }

            private void BurnDlgDevel_FormClosed(object sender, FormClosedEventArgs e)
            {
                if(m_bImagePathChanged)
                {
                    m_burner.SetImageFilePath("");
                }
            }

            private void BurnDlgDevel_Load(object sender, EventArgs e)
            {

            }
        }
    }
}