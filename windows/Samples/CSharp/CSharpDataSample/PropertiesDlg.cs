using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using IsoSDK;
using System.Globalization;

namespace CSharpDataSample
{
    public partial class PropertiesDlg : Form
    {
        public PropertiesDlg(Burner burner, FileEntry fileEntry)
        {
            InitializeComponent();

            m_burner = burner;
            m_fileEntry = fileEntry;

            nameTextBox.Text = fileEntry.Name;

            string dateTimeFormat = CultureInfo.CurrentCulture.DateTimeFormat.ShortDatePattern + " " +
                CultureInfo.CurrentCulture.DateTimeFormat.LongTimePattern;
            fileCreationDateTimePicker.CustomFormat = dateTimeFormat;
            fileCreationDateTimePicker.Value = fileEntry.CreationTime.ToDateTime();

            fileModificationDateTimePicker.CustomFormat = dateTimeFormat;
            fileModificationDateTimePicker.Value = fileEntry.DateTime.ToDateTime();

            fileLastAccessDateTimePicker.CustomFormat = dateTimeFormat;
            fileLastAccessDateTimePicker.Value = fileEntry.AccessTime.ToDateTime();

            hiddenAttributeCheckBox.Checked = (fileEntry.Attributes & FileAttributes.Hidden) != 0;
            advancedHiddenAttributeCheckBox.Checked = (fileEntry.Attributes & FileAttributes.AdvancedHidden) != 0;
        }

        private void nameTextBox_Validating(object sender, CancelEventArgs e)
        {
            if (String.IsNullOrEmpty(nameTextBox.Text))
            {
                MessageBox.Show("File name cannot be empty.", Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Error);
                e.Cancel = true;
            }
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            string path = m_fileEntry.Path;
            if (path != "\\")
                path += "\\";
            string sourcePath = path + m_fileEntry.Name;
            string destinationPath = path + nameTextBox.Text;

            // Rename the file if the name has been changed.
            if (sourcePath != destinationPath)
            {
                if (!m_burner.RenameFile(sourcePath, destinationPath))
                {
                    HandleError();
                    return;
                }
            }

            // Set creation, modification and last access time.
            FileDateTime creationTime = new FileDateTime(fileCreationDateTimePicker.Value);
            FileDateTime modificationTime = new FileDateTime(fileModificationDateTimePicker.Value);
            FileDateTime lastAccessTime = new FileDateTime(fileLastAccessDateTimePicker.Value);
            if (!m_burner.SetFileTimes(destinationPath, creationTime, modificationTime, lastAccessTime))
            {
                HandleError();
                return;
            }

            if (globalTimesCheckbox.Checked)
            {
                m_burner.FileDateTimeEx.UseCustomTimes = true;
                m_burner.FileDateTimeEx.UseCreationDateTime = true;
                m_burner.FileDateTimeEx.UseModificationDateTime = true;
                m_burner.FileDateTimeEx.UseLastAccessDateTime = true;
                m_burner.FileDateTimeEx.CreationDateTime = new FileDateTime(fileCreationDateTimePicker.Value);
                m_burner.FileDateTimeEx.ModificationDateTime = new FileDateTime(fileModificationDateTimePicker.Value);
                m_burner.FileDateTimeEx.LastAccessDateTime = new FileDateTime(fileLastAccessDateTimePicker.Value);
            }

            // Set file attributes.
            m_fileEntry.Attributes &= ~(FileAttributes.Hidden | FileAttributes.AdvancedHidden);
            if (hiddenAttributeCheckBox.Checked)
                m_fileEntry.Attributes |= FileAttributes.Hidden;
            if (advancedHiddenAttributeCheckBox.Checked)
                m_fileEntry.Attributes |= FileAttributes.AdvancedHidden;
            if (!m_burner.SetFileAttr(destinationPath, m_fileEntry.Attributes))
                HandleError();
        }

        private void HandleError()
        {
            if (m_burner.GetLastError() != ErrorCode.SdkErrorNo)
                MessageBox.Show(m_burner.GetText((int)m_burner.GetLastError()), Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private Burner m_burner;
        private FileEntry m_fileEntry;
    }
}
