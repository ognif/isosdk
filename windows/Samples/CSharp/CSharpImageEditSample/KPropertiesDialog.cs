using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using IsoSDK;

namespace CSharpImageEditSample
{
    public partial class KPropertiesDialog : Form
    {
        protected KPropertiesDialog()
        {        
        }

        public KPropertiesDialog(ITreeNode node)
        {
            InitializeComponent();

            KProperties properties = node.getProperties();
            for (int i = 0; i < properties.Count; ++i)
            {
                String[] subItems = {properties[i].Key, properties[i].Value};
                ListViewItem item = new ListViewItem(subItems, 0);
                listViewParams.Items.Add(item);                
            }

            if (node is FileNode)
            {
                FileNode fileNode = (FileNode)node;
                foreach (Extent extent in fileNode.AllocationTable.Extents)
                {
                    String[] subItems = { Convert.ToString(extent.Location), Convert.ToString(extent.Length) };
                    ListViewItem item = new ListViewItem(subItems, 0);
                    allocationListView.Items.Add(item);
                }
            }
            else
            {
                tabControl.TabPages.Remove(allocationTabPage);
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}