using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;
using System.Threading;


namespace CSharpImageEditSample
{
    public partial class KMD5Dialog : Form
    {
        private String m_strFileName = "";
        private String m_strMD5 = "";
        private DateTime m_StartTime;
        private bool m_bCancelPressed = false;
        private bool m_bDone = false;

        private int READ_SIZE = 1024 * 1024;

        delegate void ProgressDelegate(int nProgress);

        MD5CryptoServiceProvider m_md5 = new MD5CryptoServiceProvider();

        private KMD5Dialog()
        {
            InitializeComponent();
        }

        public KMD5Dialog(String strFileName)
        {
            InitializeComponent();

            m_strFileName = strFileName;
        }
        
        private void buttonCancel_Click(object sender, EventArgs e)
        {
            timer.Stop();
            m_bCancelPressed = true;

            if (m_bDone)
            {
                Close();
            }
        }

        void Calculate()
        {
            if (m_bCancelPressed)
            {
                m_bDone = true;
                buttonCancel.Text = "&Close";
                return;
            }

            FileStream fs = File.OpenRead(m_strFileName);
            int nFileLength = (int)fs.Length;

            byte[] buffer = new byte[READ_SIZE];

            int i = 0;
            for (; i < nFileLength; i += READ_SIZE)
            {
                if (i + READ_SIZE < nFileLength)
                {
                    fs.Read(buffer, 0, READ_SIZE);
                    
                    m_md5.TransformBlock(buffer, 0, buffer.Length, buffer, 0);
                }
                else
                {
                    fs.Read(buffer, 0, nFileLength - i);
                    m_md5.TransformFinalBlock(buffer, 0, nFileLength - i);
                }

                SetProgress((int)((100 * (double)i) / nFileLength));                
            }

	           
            m_bDone = true;		      
			GenerateMD5();

            SetProgress(100);	        
        }

        void SetProgress(int nProgress)
        {
            if (progressBar.InvokeRequired)
            {
                ProgressDelegate d = new ProgressDelegate(SetProgress);
                this.Invoke(d, new object[] { nProgress });
            }
            else
            {
                progressBar.Value = nProgress;

                if (nProgress == 100)
                {
                    buttonCancel.Text = "&Close";
                    timer.Stop();
                }
            }
        }

        void GenerateMD5()
        {
            byte[] pucharMD5 = m_md5.Hash;
	        
            m_strMD5 = "";
	        
	        for (int i = 0 ; i < 16; ++i)
	        {		
		        m_strMD5 += String.Format("{0:x}", pucharMD5[i]);
	        }	
        }

        public String GetMD5String()
        {
	        return m_strMD5;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            DateTime Now =
                new DateTime(((TimeSpan)(DateTime.Now - m_StartTime)).Ticks);

            MDLabelTime.Text = Now.ToLongTimeString();

            timer.Start();
        }

        private void KMD5Dialog_Load(object sender, EventArgs e)
        {
            labelPath.Text = m_strFileName;
            m_StartTime = DateTime.Now;
            timer.Start();

            Thread th = new Thread(new ThreadStart(this.Calculate));
            th.Start();
        }
    }
}