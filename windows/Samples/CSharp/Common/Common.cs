using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using IsoSDK;

namespace CommonNet
{
    public class Functions
    {
        public static bool HandleError(Burner burner)
        {
            if (burner.GetLastError() != 0)
            {
                System.Windows.Forms.MessageBox.Show(burner.GetText((Int32)burner.GetLastError()), "SDK Error");
                return true;
            }
            return false;
        }

        public static void GoToPixbytesSite()
        {
            
            try
            {
                System.Diagnostics.Process.Start("http://www.isosdk.com/");
            }
            catch (SystemException e)
            {
                WebSiteLinkForm WebSiteForm = new WebSiteLinkForm();
                WebSiteForm.Show();
            }
            
        }

        public static String formatDate(FileEntry info)
        {
            return String.Format("{0,2:D2}.{1,2:D2}.{2,4:D4} {3,2:D2}:{4,2:D2}:{5,2:D2}",
                (int)info.DateTime.Day,
                (int)info.DateTime.Month,
                (int)info.DateTime.Year + 1900,
                (int)info.DateTime.Hour,
                (int)info.DateTime.Minute,
                (int)info.DateTime.Second);
        }

        public static String formatTime(FileDateTime info)
        {
            return String.Format("{0,2:D2}.{1,2:D2}.{2,4:D4} {3,2:D2}:{4,2:D2}:{5,2:D2}",
                (int)info.Day,
                (int)info.Month,
                (int)info.Year + 1900,
                (int)info.Hour,
                (int)info.Minute,
                (int)info.Second);
        }

    }

    public class Burning
    {
        public static void BurnDeveloped(Burner burner, string isoImagePath)
        {
            Dialogs.BurnDlgDevel dlg = new Dialogs.BurnDlgDevel(burner, isoImagePath);
            if (!dlg.CanStart)
            {
                return;
            }
            dlg.ShowDialog();
            dlg.ResetCallbacks();
        }
    }

    public class Erase
    {
        public static void EraseDeveloped(Burner burner)
        {
            Dialogs.EraseDlg dlg = new Dialogs.EraseDlg(burner);
            if (!dlg.CanStart)
            {
                return;
            }
            dlg.ShowDialog();
            dlg.ResetCallbacks();
        }
    }

    public class Additional
    {
        public static void About()
        {
            Dialogs.AboutDlg dlg = new Dialogs.AboutDlg();
            dlg.ShowDialog();
        }

        public static DialogResult Multiselection(Burner burner)
        {
            Dialogs.MultiDeviceDlg dlg = new Dialogs.MultiDeviceDlg(burner);

            return dlg.ShowDialog();
        }
    }
}
