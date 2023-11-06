using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using IsoSDK;
using System.Drawing;

namespace CSharpAudioSample
{
    public class FileListView
    {
        private ListView m_listView;
        private Burner m_burner;
        private string m_strCurDirectory;
        private ImageList m_imageList;

        public FileListView(ListView listView, Burner burner)
        {
            m_burner = burner;
            m_listView = listView;
            m_listView.Columns.Add("Name", 200);
            m_listView.Columns.Add("Size", 60);
            m_listView.Columns.Add("Modified Date", 160);

            m_imageList = new ImageList();

            m_imageList.Images.Add((Image)new Bitmap(GetType(), "minidoc.gif"));
            m_imageList.Images.Add((Image)new Bitmap(GetType(), "minifolder.gif"));

            m_listView.SmallImageList = m_imageList;

            SelectDirectory(@"\data");
        }
        private void SelectDirectory(string strDir)
        {
            ClearItems();
            m_strCurDirectory = strDir;

            using (DiskSession session = m_burner.OpenDiskSession(0))
            {
                using (DiskDirectory directory = session.OpenDirectory(strDir))
                {
                    if (directory == null)
                        return;

                    if (strDir != @"\data")
                    {
                        ListViewItem item = new ListViewItem("..");
                        item.ImageIndex = 1;
                        m_listView.Items.Add(item);
                    }

                    Int64 size;
                    string strSize;
                    int fileCount = directory.FilesCount;
                    for (int nIndex = 0; nIndex < fileCount; ++nIndex)
                    {
                        FileEntry entry = directory.get_Files(nIndex);

                        ListViewItem item = new ListViewItem(entry.Name);

                        if ((entry.Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                        {
                            string strDirPath = m_strCurDirectory;

                            strDirPath += @"\";

                            strDirPath += entry.Name;
                            size = GetDirectorySize(strDirPath);
                            item.ImageIndex = 1;
                        }
                        else
                        {
                            size = entry.Size;
                            item.ImageIndex = 0;
                        }
                        if (size > 1024 * 1024)
                        {
                            size = size / (1024 * 1024);
                            strSize = String.Format("{0} MB", size);
                        }
                        else
                        {
                            strSize = String.Format("{0} bytes", size);
                        }
                        DateTime dateTime = new DateTime(entry.DateTime.Year + 1900,
                                                        entry.DateTime.Month,
                                                        entry.DateTime.Day,
                                                        entry.DateTime.Hour,
                                                        entry.DateTime.Minute,
                                                        entry.DateTime.Second);

                        item.SubItems.Add(strSize);
                        item.SubItems.Add(dateTime.ToString());

                        m_listView.Items.Add(item);
                    }
                }
            }
        }

        public void OnDoubleClicked()
        {
            if (m_listView.SelectedItems.Count < 1)
            {
                return;
            }

            if (m_listView.SelectedItems[0].Text == "..")
            {
                //return to parent directory
                int index = m_strCurDirectory.LastIndexOf(@"\");
                if (index > 0)
                {
                    m_strCurDirectory = m_strCurDirectory.Substring(0, index);
                }
                else
                {
                    m_strCurDirectory = @"\data";
                }
                SelectDirectory(m_strCurDirectory);
            }
            else if (m_listView.SelectedItems[0].ImageIndex == 1) // if directory
            {                
                m_strCurDirectory += @"\";                
                m_strCurDirectory += m_listView.SelectedItems[0].Text;
                SelectDirectory(m_strCurDirectory);
            }
        }
        public void CreateFolder()
        {
            CommonNet.Dialogs.CreateFolderDlg dlg = new CommonNet.Dialogs.CreateFolderDlg();
            string strFolderName;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                strFolderName = dlg.GetText();
                if (strFolderName.Length > 0)
                {
                    m_burner.CreateDir(strFolderName, m_strCurDirectory);

                    SelectDirectory(m_strCurDirectory);
                }
            }
        }
        public void ResetList()
        {
            using (DiskSession ds = m_burner.OpenDiskSession(0))
            {
                CommonNet.Functions.HandleError(m_burner);
                using (DiskDirectory dd = ds.OpenDirectory(@"\data"))
                {
                    CommonNet.Functions.HandleError(m_burner);
                    int nFiles = dd.FilesCount;
                    for (int i = 0; i < nFiles; ++i)
                    {
                        FileEntry fe = dd.get_Files(0);
                        CommonNet.Functions.HandleError(m_burner);
                        if ((fe.Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                        {
                            string s = fe.Path + "\\" + fe.Name;
                            bool bRes = m_burner.RemoveDir(s);
                            CommonNet.Functions.HandleError(m_burner);
                        }
                        else
                        {

                            bool bRes = m_burner.RemoveFile(fe.Name, fe.Path);
                            CommonNet.Functions.HandleError(m_burner);
                        }
                    }
                }
            }

            SelectDirectory(@"\data");
        }

        public void AddFile()
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Multiselect = true;
            dlg.Filter = "All files (*.*)|*.*";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                foreach (string str in dlg.FileNames)
                {
                    m_burner.AddFile(str, m_strCurDirectory, str.Substring(str.LastIndexOf(@"\") + 1),
                        false, SavePathOption.DontSavePath);                    
                }
                SelectDirectory(m_strCurDirectory);
            }
        }
   
        public void AddFolder()
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            dlg.ShowNewFolderButton = false;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                m_burner.AddDir(dlg.SelectedPath, m_strCurDirectory, "*", FileAttributes.All, true,
                    SavePathOption.ParentOnly);
            }
            SelectDirectory(m_strCurDirectory);
        }

        public Int64 GetDirectorySize(string strDirPath)
        {
            Int64 size = 0;

            using (DiskSession session = m_burner.OpenDiskSession(0))
            {
                using (DiskDirectory directory = session.OpenDirectory(strDirPath))
                {
                    int nFileCount = directory.FilesCount;
                    for (Int32 nIndex = 0; nIndex < nFileCount; ++nIndex)
                    {
                        FileEntry entry = directory.get_Files(nIndex);


                        if ((entry.Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                        {
                            string strDir = entry.Path;
                            strDir += @"\";
                            strDir += entry.Name;

                            size += GetDirectorySize(strDir);
                        }
                        else
                        {
                            size += entry.Size;
                        }
                    }
                }
            }

            return size;
        }
        public int GetSizeInSeconds()
        {
            Int64 sizeInBytes = GetDirectorySize(@"\data");
            //                             bytes per sample      sample rate
            int res = (int)(sizeInBytes / (       4          *      44100   ));
            return res;
        }
        private void ClearItems()
        {
            for (int i = m_listView.Items.Count; i > 0; --i)
            {
                RemoveItem(i - 1);
            }

        }
        public void RemoveItem(int nIndex)
        {
            m_listView.Items.RemoveAt(nIndex);
        }
        public void RefreshList()
        {
            SelectDirectory(@"\data");
        }

        public void DeleteItem()
        {
            if (m_listView.SelectedItems.Count < 1)
                return;

            using (DiskSession session = m_burner.OpenDiskSession(0))
            {
                using (DiskDirectory directory = session.OpenDirectory(m_strCurDirectory))
                {
                    int nIndex = m_listView.SelectedIndices[0];
                    if (m_strCurDirectory != @"\data")
                    {
                        --nIndex;
                    }

                    FileEntry entry = directory.get_Files(nIndex);

                    if ((entry.Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                    {
                        string strDestPath = entry.Path;
                        strDestPath += @"\";
                        strDestPath += entry.Name;
                        m_burner.RemoveDir(strDestPath);
                    }
                    else
                    {
                        m_burner.RemoveFile(entry.Name, entry.Path);
                    }
                }
            }

            SelectDirectory(m_strCurDirectory);
        }
        public void RenameFile()
        {
            if (m_listView.SelectedItems.Count < 1)
            {
                return;
            }

            if (m_listView.SelectedItems[0].Text == "..")
            {
                return;
            }

            using (DiskSession session = m_burner.OpenDiskSession(0))
            {
                using (DiskDirectory directory = session.OpenDirectory(m_strCurDirectory))
                {
                    int nIndex = m_listView.SelectedIndices[0];
                    if (m_strCurDirectory != @"\data")
                    {
                        --nIndex;
                    }

                    FileEntry entry = directory.get_Files(nIndex);

                    bool bFolder = false;
                    if ((entry.Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                    {
                        bFolder = true;
                    }

                    CommonNet.Dialogs.RenameDlg dlg = new CommonNet.Dialogs.RenameDlg(entry.Name);
                    if (dlg.ShowDialog() == DialogResult.OK)
                    {
                        string strNewFileName = dlg.GetFileName();
                        if (strNewFileName.Length > 0)
                        {
                            string strSourcePath = entry.Path;

                            strSourcePath += @"\";
                            strSourcePath += entry.Name;

                            if (bFolder)
                            {
                                m_burner.RenameDir(strSourcePath, strNewFileName);
                            }
                            else
                            {
                                m_burner.RenameFile(strSourcePath, strNewFileName);
                            }
                            SelectDirectory(m_strCurDirectory);
                        }
                    }
                }
            }
        }
    };
}
