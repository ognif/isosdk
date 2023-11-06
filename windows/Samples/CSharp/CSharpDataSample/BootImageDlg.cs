using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpDataSample
{
    public partial class BootImageDlg : Form
    {
        private Burner m_burner;
        public BootImageDlg(Burner burner)
        {
            m_burner = burner;
            InitializeComponent();
          
            emulationComboBox.Items.Add("No Emulation");
            emulationComboBox.Items.Add("1.2 MB Floppy");
            emulationComboBox.Items.Add("1.44 MB Floppy");
            emulationComboBox.Items.Add("2.88 MB Floppy");
            emulationComboBox.Items.Add("HardDisk");

            platformComboBox.Items.Add("80x86");
            platformComboBox.Items.Add("PowerPC");
            platformComboBox.Items.Add("Mac");

            resetButton_Click(this, EventArgs.Empty);

        }

        private void imageButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Image files (*.img)|*.img";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                imageTextBox.Text = dlg.FileName;
            }
        }

        private void resetButton_Click(object sender, EventArgs e)
        {
            imageTextBox.Text = m_burner.Options.BootImage;
            sectorTextBox.Text = m_burner.BootOptions.SectorCount.ToString();
            loadTextBox.Text = m_burner.BootOptions.LoadSegment.ToString();
            developerTextBox.Text = m_burner.BootOptions.DeveloperID;
            bootableCheckBox.Checked = m_burner.BootOptions.BootIndicator;
            emulationComboBox.SelectedIndex = m_burner.BootOptions.Emulation;
            platformComboBox.SelectedIndex = m_burner.BootOptions.PlatformID;            
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            m_burner.Options.Bootable = bootableCheckBox.Checked;
            m_burner.Options.BootImage = imageTextBox.Text;
            m_burner.BootOptions.SectorCount = Convert.ToInt32(sectorTextBox.Text);
            m_burner.BootOptions.LoadSegment = Convert.ToInt32(loadTextBox.Text);
            m_burner.BootOptions.DeveloperID = developerTextBox.Text;
            m_burner.BootOptions.BootIndicator = bootableCheckBox.Checked;
            m_burner.BootOptions.Emulation = emulationComboBox.SelectedIndex;
            m_burner.BootOptions.PlatformID = platformComboBox.SelectedIndex;
            this.Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}