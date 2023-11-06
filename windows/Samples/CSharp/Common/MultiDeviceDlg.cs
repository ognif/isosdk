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
		partial class MultiDeviceDlg : Form
		{
			private Burner m_burner;
			
			public MultiDeviceDlg(Burner burner)
			{
				InitializeComponent();
				m_burner = burner;
				deviceListView.Columns.Add("Devices", 300);

				UpdateDeviceList();

				okButton.Enabled = false;
			}
			private void UpdateDeviceList()
			{
				deviceListView.Items.Clear();
				string[] aDevices = m_burner.GetDevices(true);
				for (int i = 0; i < aDevices.Length; ++i)
				{
					deviceListView.Items.Add(aDevices[i]);
				}

			}
			private void exitButton_Click(object sender, EventArgs e)
			{
				this.Close();
			}

			private void okButton_Click(object sender, EventArgs e)
			{
				foreach (ListViewItem item in deviceListView.Items)
				{
					string str = item.Text;
					if (item.Selected)
					{
						m_burner.AddBurnDevice(str);
					}
					else
					{
						m_burner.RemoveBurnDevice(str);
					}
				}
				this.Close();
			}

			private void deviceListView_SelectedIndexChanged(object sender, EventArgs e)
			{
				okButton.Enabled = false;
				foreach (ListViewItem item in deviceListView.Items)
				{
					if (item.Selected)
					{
						okButton.Enabled = true;
					}
				}
			}
		}
	}
}