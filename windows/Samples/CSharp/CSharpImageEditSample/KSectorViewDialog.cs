using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using IsoSDK;
using Sector2Text;

namespace CSharpImageEditSample
{
    public partial class KSectorViewDialog : Form
    {
        private Burner m_burner = null;
        
        //private int m_nBufferStartLba = -1;
        //private int m_nBufferEndLba = -1;
        private int m_nCurrentLba = 0;
        private bool m_bReadRaw = true;

        SectorLines m_Buffer = new SectorLines();

        protected KSectorViewDialog()
        {
            InitializeComponent();
        }

        public KSectorViewDialog(Burner burner, int nLba)
        {
            InitializeComponent();

            m_burner = burner;
            m_nCurrentLba = nLba;
        }

        private void buttonPrev_Click(object sender, EventArgs e)
        {
            if (m_nCurrentLba > 0)
            {
                --m_nCurrentLba;

                numericUpDownSector.Value = Convert.ToDecimal(m_nCurrentLba);
            }
        }

        private void KSectorViewDialog_Load(object sender, EventArgs e)
        {   
            OnLba();
        }

        private void buttonNext_Click(object sender, EventArgs e)
        {
            ++m_nCurrentLba;

            numericUpDownSector.Value = Convert.ToDecimal(m_nCurrentLba);
        }

        void OnLba()
        {
	        List<String> stringsLines = ReadSector(m_bReadRaw, m_nCurrentLba);	

	        richTextBoxSectors.Text = "";

	        for(int i = 0; i < stringsLines.Count; ++i)
	        {
		        richTextBoxSectors.AppendText(stringsLines[i] + '\n' );
	        }	        
        }

        private List<String> ReadSector(bool bReadRaw, int nLba)
        {            
	        int buff_length = bReadRaw ? 2352 : 2048;
            ImageFormat Format = bReadRaw ? ImageFormat.Bin : ImageFormat.Iso;

            byte[] buff = m_burner.ReadSectors((int)DeviceIndex.Read, m_nCurrentLba, 1, Format, buff_length);
            CommonNet.Functions.HandleError(m_burner);

            m_Buffer.setData(buff, (uint)buff_length);
	        
	        return m_Buffer.getLines();
        }

        private void checkBoxRaw_CheckedChanged(object sender, EventArgs e)
        {
            m_bReadRaw = checkBoxRaw.Checked;

            OnLba();
        }

        private void numericUpDownSector_ValueChanged(object sender, EventArgs e)
        {
            m_nCurrentLba = Convert.ToInt32(numericUpDownSector.Value);
            OnLba();
        }
    }
}