using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CSharpUtilitiesSample
{
    public partial class RegionSelectDialog : Form
    {
        private int m_nRegionalCode;

        public RegionSelectDialog()
        {
            InitializeComponent();
            m_nRegionalCode = 1;
        }

        public int GetRegionalCode()
        {
            return m_nRegionalCode;
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (sender is RadioButton)
            {
                if ((sender as RadioButton).Checked)
                {
                    m_nRegionalCode = int.Parse((sender as RadioButton).Tag.ToString());
                }
            }
        }
    }
}