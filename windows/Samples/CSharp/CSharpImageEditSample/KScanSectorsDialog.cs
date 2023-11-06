using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using IsoSDK;
using System.Threading;

namespace CSharpImageEditSample
{
    public partial class KScanSectorsDialog : Form
    {
        private Burner m_burner;
        private KErrorListLogger m_Logger = null;
        private Thread m_thread = null;
        private volatile bool m_bStopFlag = false;

        delegate void SetProgressDelegate(int nProgress);
        delegate void StopEnableDelegate(bool bEnable);

        private KScanSectorsDialog()
        {
            InitializeComponent();
        }

        public KScanSectorsDialog(Burner burner, int nStartLBA, int nRegionSizeInSectors)
        {
            InitializeComponent();

            m_burner = burner;

            m_Logger = new KErrorListLogger(richTextBox);
            m_Logger.SetStartLba(nStartLBA);
            m_Logger.SetRegionSize(nRegionSizeInSectors);
        }

        private void OnStart()
        {
            //Set ReadSpeeed Sample for CD.
            //Speed[] aReadSpeeds = m_burner.GetPossibleReadSpeeds();
            //m_burner.SetReadSpeed((int)DeviceIndex.Read, 882);
            //CommonNet.Functions.HandleError(m_burner);

            m_bStopFlag = false;
            m_thread = new Thread(new ThreadStart(Execute));
            m_thread.Start();

            StopEnable(true);
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            OnStart();
        }

        private void KScanSectorsDialog_Load(object sender, EventArgs e)
        {
            OnStart();
        }

        private void OnStop()
        {
            m_bStopFlag = true;

            if (m_thread.IsAlive)
            {
                MessageBox.Show("Aborted by user");
                m_thread.Join();
            }
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            OnStop();
        }

        private void Execute()
	    {
		    if (m_Logger.GetRegionSize() != 0)
		    {
			    m_Logger.Reset();		

			    const int nMaxSectorsToRead = 27;

			    int nCurLba;
			    int nSectorsToRead = nMaxSectorsToRead;

			    for (nCurLba = m_Logger.GetStartLba(); nCurLba < m_Logger.GetStartLba() + 
                    m_Logger.GetRegionSize(); )
			    {
                    if (m_bStopFlag)
                    {
                        m_Logger.Cancel();
                        StopEnable(false);
                        SetProgress(0);
                        
                        return;
                    }

				    if (nCurLba + nMaxSectorsToRead >= m_Logger.GetStartLba() + m_Logger.GetRegionSize())
				    {
					    nSectorsToRead = m_Logger.GetStartLba() + m_Logger.GetRegionSize() - nCurLba;
				    }

				    const int buff_length = 2352 * nMaxSectorsToRead;

				    byte[] buff = m_burner.ReadSectors((int)DeviceIndex.Read, nCurLba, 
                        nSectorsToRead, ImageFormat.Bin, buff_length);

				    if(!CommonNet.Functions.HandleError(m_burner))
				    {
					    m_Logger.LogSuccessiveRead(nCurLba, nSectorsToRead);
				    }
				    else
				    {
					    int nErrLba = nCurLba;
					    
                        for(;nCurLba < nErrLba + nSectorsToRead; ++nCurLba)
					    {
                            if (m_bStopFlag)
                            {
                                break;
                            }

                            buff = m_burner.ReadSectors((int)DeviceIndex.Read, nCurLba, 1, 
                                ImageFormat.Bin, buff_length);

                            if (m_burner.GetLastError() == ErrorCode.SdkErrorNo)				
						    {
							    m_Logger.LogSuccessiveRead(nCurLba, 1);
						    }
						    else
						    {
							    m_Logger.LogFailureRead(nCurLba);
						    }
					    }
				    }

                    SetProgress((100 * (nCurLba + 1 - m_Logger.GetStartLba())) / 
                        m_Logger.GetRegionSize());
                        				
				    nCurLba += nSectorsToRead;			
			    }	

			    m_Logger.Done();
                SetProgress(100);

                StopEnable(false);
		    }
	    }

        private void SetProgress(int nProgress)
        {
            if (progressBar.InvokeRequired)
            {
                SetProgressDelegate d = new SetProgressDelegate(SetProgress);

                try
                {
                    this.Invoke(d, new object[] { nProgress });
                }
                catch (Exception)
                {
                    return;
                }
            }
            else
            {
                progressBar.Value = nProgress;
            }
        }

        private void StopEnable(bool bEnable)
        {
            if (buttonStop.InvokeRequired)
            {
                StopEnableDelegate d = new StopEnableDelegate(StopEnable);

                try
                {
                    this.Invoke(d, new object[] { bEnable });
                }
                catch (Exception)
                {
                    return;
                }
            }
            else
            {
                buttonStop.Enabled = bEnable;
                buttonStart.Enabled = !bEnable;
            }
        }

        private void KScanSectorsDialog_FormClosing(object sender, FormClosingEventArgs e)
        {
            OnStop();
        }
    }

    public class KErrorListLogger
    {
        private RichTextBox m_richTextBox = null;

        private int m_nStartLba = 0;
        private int m_nRegionSizeInSectors = 0;
        private int m_nBadSectors = 0;

        delegate void OnWriteTextDelegate(String strText, bool bRewrite);        

        private KErrorListLogger()
        {
        }

        public KErrorListLogger(RichTextBox richTextBox)
        {
            m_richTextBox = richTextBox;
        }

        public void ScrollToEndOfText()
        {
            m_richTextBox.ScrollToCaret();
        }

        public void SetStartLba(int nStartLba)
        {
            m_nStartLba = nStartLba;
        }

        public void SetRegionSize(int nRegionSizeInSectors)
        {
            m_nRegionSizeInSectors = nRegionSizeInSectors;
        }

        public int GetStartLba()
        {
            return m_nStartLba;
        }

        public int GetRegionSize()
        {
            return m_nRegionSizeInSectors;
        }

        private void WriteText(String strText, bool bRewrite)
        {
            if (m_richTextBox.InvokeRequired)
            {
                try
                {
                    OnWriteTextDelegate d = new OnWriteTextDelegate(WriteText);
                    m_richTextBox.Parent.Invoke(d, new object[] { strText, bRewrite });
                }
                catch (Exception)
                {
                    return;
                }
            }
            else
            {
                if (bRewrite)
                {
                    m_richTextBox.Text = strText;
                }
                else
                {
                    m_richTextBox.AppendText(strText);
                }

                ScrollToEndOfText();
            }
        }

        public void LogSuccessiveRead(int nSuccessLba, int nSectors)
        {
            //Do nothing
            String str = String.Format("Sectors read successfully at LBA: {0:D}. Quantity: {1:D}.\n", 
                nSuccessLba, nSectors);
            WriteText(str, false);
        }

        public void LogFailureRead(int nFailLba)
        {
            ++m_nBadSectors;

            String str = String.Format("Sector read fail at LBA: {0:D}.\n", nFailLba);
            WriteText(str, false);
        }

        public void Reset()
        {
            WriteText("Scan log:\n", true);
            
            String str = String.Format("Scanning {0:D} sectors from LBA {1:D}...\n", m_nRegionSizeInSectors, m_nStartLba);
            WriteText(str, false);
            m_nBadSectors = 0;
        }

        public void Done()
        {
            String str = String.Format("Done. Sectors read: {0:D}, from LBA: {1:D}.\nNumber of bad sectors: {2:D}\n",
                m_nRegionSizeInSectors, m_nStartLba, m_nBadSectors);

            WriteText(str, false);
        }

        public void Cancel()
        {
            String str = String.Format("User cancelled. Number of bad sectors: {0:D}\n",
                m_nBadSectors);

            WriteText(str, false);
        }
    }
}