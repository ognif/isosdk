using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
using IsoSDK;

namespace CSharpImageEditSample
{
    public partial class KSaveContentDialog : Form
    {
        private enum State
        {
            ST_NONE,
            ST_PROCESSING,
            ST_ABORTED,
            ST_CANCELLED,
            ST_DONE,
        };

        public enum EAim
	    {
		    AIM_IMPORT,
		    AIM_VERIFY,
	    };

        public enum Extract
        {
            IMP_EX,
            IMP_COMMON,
        };

        public class SaveContentParams
	    {
            public EAim enAim = EAim.AIM_IMPORT;
            public List<ITreeNode> nodes = null;
            public String strExtractionFolderPath = "";
            public String strPassword = "";
            public Extract extractSplitter = Extract.IMP_COMMON;

            public SaveContentParams(EAim _enAim, List<ITreeNode> _nodes, String _strExtractionFolderPath, String _strPassword, Extract _extractSplitter)		     
		    {
                nodes = _nodes;
		        enAim = _enAim;
		        strExtractionFolderPath = _strExtractionFolderPath;
                strPassword = _strPassword;
                extractSplitter = _extractSplitter;
            }
	    };


        delegate void OnJobDoneEventCallback(object sender, EventArgs e);
        delegate void SetProgressCallback(object sender, ProcessEventArgs e);
        delegate void OnBurnDoneEventCallback(object sender, BurnDoneEventArgs e);
        delegate void OnBurnFileEventCallback(object sender, BurnFileEventArgs e);
        
        delegate void LogPrintDelegate(String strText);
        delegate void FileNameDelegate(String strFileName);
        delegate void OnDoneDelegate();
        delegate void SetProgressDelegate(int nProgress, Int64 nBytesWritten);

        private Burner m_burner;
        private SaveContentParams m_cParams;
        private List<ITreeNode>.Enumerator m_iCurrentNode;

        private State m_enState = State.ST_NONE;
        private DateTime m_StartTime;

        private Int64 m_nTotalFiles = 0;

        private Int64 m_nTotalSize = 0;
        private Int64 m_nCurrJobsSize = 0;
        private Int64 m_nDoneJobsSize = 0;
        
        private KSaveContentDialog()
        {
            InitializeComponent();
        }

        public KSaveContentDialog(Burner burner, SaveContentParams cParams)
        {
            InitializeComponent();

            m_burner = burner;
            m_cParams = cParams;
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
                OnJobDone();
            }
        }

        private void OnJobDone()
        {
            switch (m_enState)
            {
                case State.ST_PROCESSING:
                    {
                        if (m_iCurrentNode.Current != null)
                        {
                            if (false == ProcessNextNode())
                            {
                                LogPrint("Internal error. Aborted.");
                                goto case State.ST_DONE;
                            }
                        }
                        else
                        {
                            LogPrint("Done. Tottal files : " + m_nTotalFiles.ToString());
                            goto case State.ST_DONE;
                        }
                    }
                    break;

                case State.ST_CANCELLED:

                    this.Close();

                    break;

                case State.ST_DONE:
                case State.ST_ABORTED:
                    {
                        Done();
                    }
                    break;

                default:
                    {
                        MessageBox.Show("Internal error");
                    }
                    break;
            }
        }

        private void Done()
        {
            m_enState = State.ST_DONE;
            buttonAbort.Enabled = true;
            buttonAbort.Text = "&Close";
            timer.Stop();
        }

        private bool ProcessNextNode()
        {
            FileSystems FileSysType;
            int nTrackNumber = -1;

            FileSysNode fsnode = m_iCurrentNode.Current as FileSysNode;

            if (fsnode == null)
            {
                DirectoryNode dirnode = m_iCurrentNode.Current as DirectoryNode;

                if (dirnode != null)
                {
                    fsnode = dirnode.getFileSystemNode();
                }
                else
                {
                    FileNode filenode = m_iCurrentNode.Current as FileNode;

                    if (filenode != null)
                    {
                        fsnode = filenode.getFileSystemNode();
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            if (fsnode != null)
            {
                FileSysType = fsnode.getFileSysType();

                TrackNode tracknode = fsnode.getTrackNode();

                if (tracknode != null)
                {
                    TrackInfo info = tracknode.getTrackInfo();
                    nTrackNumber = info.TrackNumber;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

            if (CommonNet.Functions.HandleError(m_burner) == true)
            {
                return false;
            }

            m_nDoneJobsSize += m_nCurrJobsSize;
            m_nCurrJobsSize = 0;

            GenericInfo genericInfo = m_iCurrentNode.Current.getGenericInfo();

            String strPath;

            if (m_iCurrentNode.Current is FileSysNode)
            {
                strPath = "";
            }
            else
            {
                strPath = genericInfo.path + "\\" + genericInfo.name;
            }

            using (DiskSession session = m_burner.OpenDiskSession((int)DeviceIndex.Read, nTrackNumber, FileSysType))
            {

                if (EAim.AIM_IMPORT == m_cParams.enAim)
                {
                    if (Extract.IMP_COMMON == m_cParams.extractSplitter)
                    {
                        if (session.ImportFileEx(strPath, m_cParams.strExtractionFolderPath, m_cParams.strPassword) == false)
                        {
                            CommonNet.Functions.HandleError(m_burner);
                            return false;
                        }
                    }
                    else
                    {

                    }
                    if (session.ImportFile(strPath, m_cParams.strExtractionFolderPath) == false)
                    {
                        CommonNet.Functions.HandleError(m_burner);
                        return false;
                    }
                }
                else if (EAim.AIM_VERIFY == m_cParams.enAim)
                {
                    if (session.VerifyFile(strPath) == false)
                    {
                        CommonNet.Functions.HandleError(m_burner);
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }

            m_iCurrentNode.MoveNext();

            return true;
        }

        private void OnProcessEvent(object sender, ProcessEventArgs e)
        {
            if (progressBar.InvokeRequired)
            {
                SetProgressCallback d = new SetProgressCallback(OnProcessEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                SetProgress((int)e.m_fPercent, (Int64)e.m_dBytesWritten);
            }
        }

        private void SetProgress(int nProgress, Int64 nBytesWritten)
        {
            if (progressBar.InvokeRequired)
            {
                SetProgressDelegate d = new SetProgressDelegate(SetProgress);
                this.Invoke(d, new object[] { nProgress, nBytesWritten });
            }
            else
            {
                m_nCurrJobsSize = nBytesWritten;

                SCLabelBytes.Text = (m_nDoneJobsSize + m_nCurrJobsSize).ToString();

                int progress = (int)((m_nDoneJobsSize + m_nCurrJobsSize) * 100 / m_nTotalSize);
                if(progress > 100)
                {
                    progress = 100;
                }

                progressBar.Value = progress;
            }
        }

        private void OnBurnDoneEvent(object sender, BurnDoneEventArgs e)
        {
            if (e.m_strError.Length > 0)
            {
                if (this.InvokeRequired)
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

        private void OnBurnFileEvent(object sender, BurnFileEventArgs e)
        {
            LogPrint("Importing : " + e.m_strFileName);
            m_nTotalFiles++;
        }

        private void OnVerifyFileEvent(object sender, VerifyFileEventArgs e)
        {
            LogPrint("Verifying : " + e.m_strFileName);
            m_nTotalFiles++;
        }

        private void OnVerifyErrorEvent(object sender, VerifyErrorEventArgs e)
        {   
            LogPrint("Verify error : " + e.m_strFileName + " : " + e.m_strError);	
        }

        private void OnVerifyDoneEvent(object sender, VerifyDoneEventArgs e)
        {   
            LogPrint("Verify done : " + e.m_nNumErrors.ToString() + " errors");
        }

        private void RestoreEvents()
        {
            m_burner.JobDoneEvent -= new Burner.JobDoneEventHandler(OnJobDoneEvent);
            m_burner.ProcessEvent -= new Burner.ProcessEventHandler(OnProcessEvent);
            m_burner.BurnDoneEvent -= new Burner.BurnDoneEventHandler(OnBurnDoneEvent);
            m_burner.BurnFileEvent -= new Burner.BurnFileEventHandler(OnBurnFileEvent);
            m_burner.VerifyFileEvent -= new Burner.VerifyFileEventHandler(OnVerifyFileEvent);
            m_burner.VerifyErrorEvent -= new Burner.VerifyErrorEventHandler(OnVerifyErrorEvent);
            m_burner.VerifyDoneEvent -= new Burner.VerifyDoneEventHandler(OnVerifyDoneEvent);
        }

        private void KSaveContentDialog_Load(object sender, EventArgs e)
        {
            //--------------------------------------------------
            //Set the callbacks to receive infos later
            //--------------------------------------------------

            m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnJobDoneEvent);
            m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnProcessEvent);
            m_burner.BurnDoneEvent += new Burner.BurnDoneEventHandler(OnBurnDoneEvent);
            m_burner.BurnFileEvent += new Burner.BurnFileEventHandler(OnBurnFileEvent);
            m_burner.VerifyFileEvent += new Burner.VerifyFileEventHandler(OnVerifyFileEvent);
            m_burner.VerifyErrorEvent += new Burner.VerifyErrorEventHandler(OnVerifyErrorEvent);
            m_burner.VerifyDoneEvent += new Burner.VerifyDoneEventHandler(OnVerifyDoneEvent);

            if (EAim.AIM_IMPORT == m_cParams.enAim)
            {
                this.Text = "Importing content";
            }
            else if (EAim.AIM_VERIFY == m_cParams.enAim)
            {
                this.Text = "Verifying content";
            }
            else
            {
                Done();
                return;
            }

            m_enState = State.ST_PROCESSING;

            m_StartTime = DateTime.Now;
            timer.Start();

            m_nTotalSize = CalculateTotalSize(m_cParams.nodes.GetEnumerator());
            SCLabelTotal.Text = m_nTotalSize.ToString();

            m_iCurrentNode = m_cParams.nodes.GetEnumerator();
            m_iCurrentNode.MoveNext();
            //Call OnJobDone to start processing content
            OnJobDone();
        }

        Int64 CalculateTotalSize(List<ITreeNode>.Enumerator iCurrentNode)
        {
	        Int64 nTotalSize = 0;

            iCurrentNode.MoveNext();

	        while (iCurrentNode.Current != null)
	        {
		        nTotalSize += CalculateNodeSize(iCurrentNode.Current);
                iCurrentNode.MoveNext();
	        }

	        return nTotalSize;
        }

        Int64 CalculateNodeSize(ITreeNode node)
        {
            if (node is FileNode)
	        {
                return CalculateFileSize(node as FileNode);
	        }
	        else
	        {
		        int nCount = node.getChildsCount();

		        Int64 nTotalSize = 0;

		        for (int i = 0; i < nCount; i++)
		        {
			        nTotalSize += CalculateNodeSize(node.getChild(i));
		        }

		        return nTotalSize;
	        }
        }

        Int64 CalculateFileSize(FileNode filenode)
        {
	        if (filenode != null)
	        {
		        GenericInfo info = filenode.getGenericInfo();
		        return info.size;
	        }

	        return 0;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            DateTime Now = new DateTime(((TimeSpan)(DateTime.Now - m_StartTime)).Ticks);

            SCLabelTime.Text = Now.ToLongTimeString();

            timer.Start();
        }

        void LogPrint(String strText)
        {
            if (SCListBoxLog.InvokeRequired)
            {
                LogPrintDelegate d = new LogPrintDelegate(LogPrint);

                try
                {
                    this.Invoke(d, new object[] { strText });
                }
                catch (Exception) { };
            }
            else
            {
                SCListBoxLog.Items.Add(strText);
            }
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

        private void KSaveContentDialog_FormClosing(object sender, FormClosingEventArgs e)
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