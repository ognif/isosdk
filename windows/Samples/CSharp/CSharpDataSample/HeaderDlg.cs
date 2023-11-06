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
    public partial class HeaderDlg : Form
    {
        private Burner m_burner;
        public HeaderDlg(Burner burner)
        {
            InitializeComponent();
            m_burner = burner;
            resetButton_Click(this, new EventArgs());
        }

        DateTime FileDateTime2DateTime(IsoSDK.FileDateTime fdt)
        {
            return new DateTime(fdt.Year + 1900, fdt.Month, fdt.Day, fdt.Hour, fdt.Minute, fdt.Second);
        }

        IsoSDK.FileDateTime DateTime2FileDateTime(DateTime dt)
        {
            return new IsoSDK.FileDateTime(dt.Year - 1900, dt.Month, dt.Day, dt.Hour, dt.Minute, dt.Second);
        }

        private void resetButton_Click(object sender, EventArgs e)
        {
            this.applicationTextBox.Text = m_burner.ISOExOptions.ApplicationIdentifier;
            this.bibliographicTextBox.Text = m_burner.ISOExOptions.BiblioIdentifier;
            this.copyrightTextBox.Text = m_burner.ISOExOptions.CopyrightFile;
            this.dataPreparerTextBox.Text = m_burner.ISOExOptions.DataPreparer;
            this.abstractTextBox.Text = m_burner.ISOExOptions.FileIdentifier;
            this.publisherTextBox.Text = m_burner.ISOExOptions.Publisher;
            this.systemIdentifierTextBox.Text = m_burner.ISOExOptions.SystemIdentifier;
            this.volumeSetTextBox.Text = m_burner.ISOExOptions.VolumeSet;
            this.versionCheckBox.Checked = m_burner.ISOExOptions.AddSuffix;    
            this.checkBoxUseCreation.Checked = m_burner.ISOExOptions.UseCreationDateTime ;
            this.checkBoxUseModification.Checked = m_burner.ISOExOptions.UseModificationDateTime ;
            this.checkBoxUseExpiration.Checked = m_burner.ISOExOptions.UseExpirationDateTime ;
            this.checkBoxUseEffective.Checked = m_burner.ISOExOptions.UseEffectiveDateTime ;
            this.dateTimePickerCreation.Value = FileDateTime2DateTime(m_burner.ISOExOptions.CreationDateTime);
            this.dateTimePickerModification.Value = FileDateTime2DateTime(m_burner.ISOExOptions.ModificationDateTime);
            this.dateTimePickerExpiration.Value = FileDateTime2DateTime(m_burner.ISOExOptions.ExpirationDateTime);
            this.dateTimePickerEffective.Value = FileDateTime2DateTime(m_burner.ISOExOptions.EffectiveDateTime);
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            m_burner.ISOExOptions.ApplicationIdentifier = this.applicationTextBox.Text;
            m_burner.ISOExOptions.BiblioIdentifier = this.bibliographicTextBox.Text;
            m_burner.ISOExOptions.CopyrightFile = this.copyrightTextBox.Text;
            m_burner.ISOExOptions.DataPreparer = this.dataPreparerTextBox.Text;
            m_burner.ISOExOptions.FileIdentifier = this.abstractTextBox.Text;
            m_burner.ISOExOptions.Publisher = this.publisherTextBox.Text;
            m_burner.ISOExOptions.SystemIdentifier = this.systemIdentifierTextBox.Text;
            m_burner.ISOExOptions.VolumeSet = this.volumeSetTextBox.Text;
            m_burner.ISOExOptions.AddSuffix = this.versionCheckBox.Checked;

            m_burner.ISOExOptions.UseCreationDateTime = this.checkBoxUseCreation.Checked;
            m_burner.ISOExOptions.UseModificationDateTime = this.checkBoxUseModification.Checked;
            m_burner.ISOExOptions.UseExpirationDateTime = this.checkBoxUseExpiration.Checked;
            m_burner.ISOExOptions.UseEffectiveDateTime = this.checkBoxUseEffective.Checked;

            m_burner.ISOExOptions.CreationDateTime = DateTime2FileDateTime(this.dateTimePickerCreation.Value);
            m_burner.ISOExOptions.EffectiveDateTime = DateTime2FileDateTime(this.dateTimePickerEffective.Value);
            m_burner.ISOExOptions.ExpirationDateTime = DateTime2FileDateTime(this.dateTimePickerExpiration.Value);
            m_burner.ISOExOptions.ModificationDateTime = DateTime2FileDateTime(this.dateTimePickerModification.Value);

            this.Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}