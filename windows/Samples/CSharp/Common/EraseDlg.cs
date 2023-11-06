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

    public partial class EraseDlg : Form
    {
        // This delegate enables asynchronous calls for setting
        // the text property on a TextBox control.
        delegate void SetTextCallback(string text);
        delegate void JobDoneCallback(object sender, EventArgs e);
        delegate void ProgressCallback(object sender, ProcessEventArgs e);

        private Burner m_burner;
        private bool m_bInitialized;

            public bool CanStart
            {
                get
                {
                    return m_bInitialized;
                }
            }

            public EraseDlg(Burner burner)
        {
            InitializeComponent();
            m_burner = burner;

            UpdateDeviceCombo();

            deviceComboBox.Enabled = false;

            m_burner.EraseDoneEvent += new Burner.EraseDoneEventHandler(OnEraseDoneEvent);
            m_burner.ProcessEvent += new Burner.ProcessEventHandler(OnProcessEvent);
            m_burner.JobDoneEvent += new Burner.JobDoneEventHandler(OnJobDoneEvent);

            eraseProgressBar.Maximum = 100;

                
            m_bInitialized = true;
            }

        public void ResetCallbacks()
        {
            m_burner.EraseDoneEvent -= new Burner.EraseDoneEventHandler(OnEraseDoneEvent);
            m_burner.ProcessEvent -= new Burner.ProcessEventHandler(OnProcessEvent);
            m_burner.JobDoneEvent -= new Burner.JobDoneEventHandler(OnJobDoneEvent);
        }

        private void OnEraseDoneEvent(object sender, EraseDoneEventArgs e)
        {
            if (e.m_strError.Length > 0)
            {
                SetStatusText(e.m_strError);
            }
            else
            {
                SetStatusText("Erase done");
                eraseProgressBar.Value = 100;
            }
        }
        private void OnJobDoneEvent(object sender, EventArgs e)
        {
            if (fastButton.InvokeRequired)
            {
                JobDoneCallback d = new JobDoneCallback(OnJobDoneEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                fastButton.Enabled = true;
                completeButton.Enabled = true;
                exitButton.Enabled = true;
                checkBoxEject.Enabled = true;

                eraseProgressBar.Value = 0;
            }
        }
        private void OnProcessEvent(object sender, ProcessEventArgs e)
        {
            if (eraseProgressBar.InvokeRequired)
            {
                ProgressCallback d = new ProgressCallback(OnProcessEvent);
                this.Invoke(d, new object[] { sender, e });
            }
            else
            {
                eraseProgressBar.Value = Convert.ToInt32(e.m_fPercent);
            }
        }

        private void UpdateDeviceCombo()
        {
            deviceComboBox.Items.Clear();
            string[] aDevices = m_burner.GetDevices(true);
            string[] bDevices = m_burner.GetBurnDevices();
            
            for (int i = 0; i < aDevices.Length; ++i)
            {
                deviceComboBox.Items.Add(aDevices[i]);
                if (bDevices.Length > 0)
                {
                    if (String.Compare(bDevices[0], 0, aDevices[i], 0, 2) == 0)
                    {
                        deviceComboBox.SelectedIndex = i;
                    }
                }
                  
            }
            deviceComboBox.Items.Add("Multiple devices");
            if (bDevices.Length > 1)
            {
                deviceComboBox.SelectedIndex = aDevices.Length;
            }
        }

        private void fastButton_Click(object sender, EventArgs e)
        {
            Erase(true, checkBoxEject.Checked);
        }

        private void completeButton_Click(object sender, EventArgs e)
        {
            Erase(false, checkBoxEject.Checked);
        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void Erase(bool bFast, bool bEject)
        {
            m_burner.Erase(bFast, bEject);
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
            {
                SetStatusText("Error occured");
            }
            else
            {
                SetStatusText("Erasing CD/DVD...");
                fastButton.Enabled = false;
                completeButton.Enabled = false;
                exitButton.Enabled = false;
                checkBoxEject.Enabled = false;
            }
        }

        private void SetStatusText(string strText)
        {
            if (this.textLabel.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetStatusText);
                this.Invoke(d, new object[] { strText });
            }
            else
            {
                textLabel.Text = strText;
                textLabel.Location =
                    new Point(groupBox1.Size.Width / 2 - textLabel.Size.Width / 2, textLabel.Location.Y);
            }
        }
    }
	}
}