// ImageEditMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "ImageEditMFCDlg.h"
#include "../Common/AboutDlgMFC.h"

#include "SaveDiscDialog.h"
#include "SaveContentDialog.h"
#include "Md5Dialog.h"
#include "PropertiesDlg.h"
#include "FilePropertiesDlg.h"
#include "SaveTrackDialog.h"
#include "SectorViewDialog.h"
#include "ScanSectorsDialog.h"
#include "AudioGrabbingDialog.h"
#include "AudioTrackPlayingDialog.h"
#include "CDTextReadDlg.h"
#include "config.h"
#include "PasswordDlg.h"

#include <sys/stat.h>

#define WEBSITELINK			"http://www.isosdk.com"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const CString audiofiles_ext[]= {_T(".wav"), _T(".mp3"), _T(".ogg"), _T(".wma"), 
										_T(".vqf"), _T(".aac"), _T(".m4a"), _T(".flac")};

static const int audiofiles_ext_size = 8;

#define DLG_IMAGES_PATTERN _T("All Supported|*.iso;*.bin;*.nrg;*.cdi;*.mdf;*.img;*.gi;*.pdi;*.dmg;*.b5i;*.b6i| iso files|*.iso| bin files|*.bin| nrg files|*.nrg| cdi files|*.cdi| mdf files|*.mdf| ccd files|*.ccd| img files|*.img| gi files|*.gi| pdi files|*.pdi| dmg files|*.dmg| b5i files|*.b5i| b6i files|*.b6i||")

CImageEditMFCDlg::CImageEditMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageEditMFCDlg::IDD, pParent)
	, m_bBurningDevicesOnly(false)
	, m_medium(0)
{	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_iconPlay = AfxGetApp()->LoadIcon(IDI_PLAY);
	m_iconStop = AfxGetApp()->LoadIcon(IDI_STOP);

	m_medium = NULL;
	m_pImageList = NULL;
}

CImageEditMFCDlg::~CImageEditMFCDlg()
{	
	::DeInitialize();
	if (m_medium != NULL)
		delete m_medium;
	if (m_pImageList != NULL)
		delete m_pImageList;
}

void CImageEditMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_cmbDevice);
	DDX_Control(pDX, IDC_TREE_LEFTPANEL, m_treeLeftPanel);
	DDX_Control(pDX, IDC_LIST_RIGHTPANEL, m_listRightPanel);
}

BEGIN_MESSAGE_MAP(CImageEditMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, OnCbnSelchangeComboDevice)
	ON_COMMAND(ID_DISC_VERIFY, OnDiscVerify)
	ON_COMMAND(ID_DISC_SAVE, OnDiscSave)
	ON_COMMAND(ID_IMAGE_MOUNTIMAGE, OnImageMountimage)
	ON_COMMAND(ID_IMAGE_UNMOUNTIMAGE, OnImageUnmountimage)
	ON_COMMAND(ID_IMAGES_MAKEMD5, OnImageMakeMd5)
	ON_COMMAND(ID_IMAGE_CHECKMD5FORIMAGE, OnImageCheckMd5)
	ON_COMMAND(ID_ASPI_RESCANDEVICES, OnAspiRescandevices)
	ON_COMMAND(ID_ASPI_BURNDEVICESONLY, OnAspiBurndevicesonly)
	ON_COMMAND(ID_ASPI_DISABLEIMAGEWIRTER, OnAspiDisableimagewirter)
	ON_COMMAND(ID_AUDIO_PLAYSELECTED, OnAudioPlayselected)
	ON_COMMAND(ID_AUDIO_GRABSELECTED, OnAudioGrabSelected)
	ON_COMMAND(ID_READ_CD_TEXT, OnReadCDText)
	ON_COMMAND(ID_READ_INDEXES, OnReadIndexes)
	ON_COMMAND(ID_READ_ISRC, OnReadISRC)
	ON_COMMAND(ID_AUDIO_GRABALL, OnAudioGrabAll)

	ON_COMMAND(ID_INFORMATION_SHOW, OnInformationShow)
	ON_COMMAND(ID_INFORMATION_WEB, OnInformationWeb)
	ON_COMMAND_EX_RANGE(ID_INTERFACE_INTERNAL, ID_INTERFACE_FROGASPI, OnSetAspi)
	ON_BN_CLICKED(IDC_OPEN_IMAGE, OnImageMountimage)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RIGHTPANEL, OnLvnItemchangedListRightpanel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_LEFTPANEL, OnTvnSelchangedTreeLeftpanel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RIGHTPANEL, OnNMDblclkListRightpanel)	
	ON_NOTIFY(NM_RCLICK, IDC_TREE_LEFTPANEL, OnNMRclickTreeLeftpanel)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RIGHTPANEL, OnNMRclickListRightpanel)

	ON_COMMAND(ID_SHOW_PROPERTIES, OnShowProperties)
	ON_COMMAND(ID_VIEW_SECTOR, OnViewSector)
	ON_COMMAND(ID_SCAN_SECTORS, OnScanSector)
	ON_COMMAND(ID_EXTRACT_TRACK, OnExtractTrack)
	ON_COMMAND(ID_EXTRACT_FILE, OnExtractFile)
	ON_COMMAND(ID_EXTRACT_FILEEX, OnExtractFileEx)
	ON_COMMAND(ID_CHECK_SIGNATURE, OnCheckSignature)
	ON_COMMAND(ID_EXTRACT_SYS, OnExtractFile)
	ON_COMMAND(ID_LIST_CONTENT, OnListContent)
	ON_COMMAND(ID_FILE_WRITELOG, OnSaveLog)
	ON_COMMAND(ID_AUDIO_EXIT, OnCancel)
	

END_MESSAGE_MAP()


// CImageEditMFCDlg message handlers

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Image Edit MFC Sample Application)

BOOL CImageEditMFCDlg::OnInitDialog()
{	
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetWindowText(_T(APP_TITLE));

	TCHAR chLicenseKey[35] = _T("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7");
	int32 res = ::Initialize(chLicenseKey, BS_ASPI_INTERNAL, BS_TRUE);
	if (res != BS_SDK_ERROR_NO) {
		HandleError(res);
		PostQuitMessage(0);
		return FALSE;
	}

	///Insert collumns into playlist
	CString strColumns;
	strColumns.LoadString(IDS_COLUMN_NAME);
	m_listRightPanel.InsertColumn(0, strColumns, LVCFMT_LEFT, 120, 0);
	strColumns.LoadString(IDS_COLUMN_LBA);
	m_listRightPanel.InsertColumn(1, strColumns, LVCFMT_LEFT, 60, 1);
	strColumns.LoadString(IDS_COLUMN_SIZE);
	m_listRightPanel.InsertColumn(2, strColumns, LVCFMT_LEFT, 75, 2);
	strColumns.LoadString(IDS_COLUMN_MODIFIED);
	m_listRightPanel.InsertColumn(3, strColumns, LVCFMT_LEFT, 120, 3);
	
	m_listRightPanel.SetExtendedStyle(m_listRightPanel.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	// TODO: Add extra initialization here

	GetMenu()->CheckMenuItem(ID_INTERFACE_INTERNAL, MF_CHECKED);
	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	m_pImageList = new CImageList();
	m_pImageList->Create(16, 16, ILC_COLOR8, 6, 0);

	m_pImageList->SetBkColor(RGB(255,255,255));
	

	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_DISC));	
	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_AUDIO));
	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_FILESYS));
	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_OPENDIR));
	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_CLOSEDIR));	
	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_FILE));
	
	m_treeLeftPanel.SetImageList(m_pImageList, TVSIL_NORMAL);
	m_listRightPanel.SetImageList(m_pImageList, LVSIL_SMALL);

	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("");

	m_treeLeftPanel.InsertItem(&tvInsert);
	
	UpdateDeviceCombo();

	GetCurrentDirectory(_MAX_PATH, m_strStartupDir.GetBuffer(_MAX_PATH));
	m_strStartupDir.ReleaseBuffer();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageEditMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageEditMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageEditMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_treeLeftPanel.m_hWnd != NULL)
	{
		CRect cTreeRect;
		m_treeLeftPanel.GetWindowRect(&cTreeRect);
		this->ScreenToClient(&cTreeRect);
		cTreeRect.bottom = cy - 2;
		m_treeLeftPanel.SetWindowPos(NULL, 0, 0, cTreeRect.Width(), cTreeRect.Height(), SWP_NOMOVE);
	}

	if (m_listRightPanel.m_hWnd != NULL)
	{
		CRect cListRect;
		m_listRightPanel.GetWindowRect(&cListRect);
		this->ScreenToClient(&cListRect);
		cListRect.right = cx - 2;
		cListRect.bottom = cy - 2;
		m_listRightPanel.SetWindowPos(NULL, 0, 0, cListRect.Width(), cListRect.Height(), SWP_NOMOVE);
	}
}

void CImageEditMFCDlg::OnCbnSelchangeComboDevice()
{
	int index = m_cmbDevice.GetCurSel();

	CString strDevice;
	m_cmbDevice.GetLBText(index, strDevice);

	// Set current device

	int32 res = ::SetReadDevice(strDevice);
	HandleError(res);

	ReloadLeftPanel();
}

void CImageEditMFCDlg::ReloadLeftPanel()
{
	// clear left and right panels	
	m_listRightPanel.DeleteAllItems();
	m_treeLeftPanel.DeleteAllItems();

	// delete old information
	delete m_medium;
	m_medium = 0;

	HTREEITEM hRoot = m_treeLeftPanel.InsertItem(_T("Root"));

	SMediumInfo sMediumInfo;
	int32 res = ::GetMediumInformation(BS_READ_DEVICE, &sMediumInfo);

	if (res != BS_SDK_ERROR_NO)
	{
		if (res == BS_SCSI_ERROR_DISK_31)
		{
			HTREEITEM hTreeItem = m_treeLeftPanel.GetRootItem();

			m_treeLeftPanel.SetItemText(hTreeItem, _T("No medium"));
			UpdateData(FALSE);
		}
		else
		{
			HandleError(res);
		}

		return;
	}

	// no errors occured, so build a new tree
	m_medium = MediumNode::create(sMediumInfo);

	BuildNode(NULL, m_medium);
	UpdateData(FALSE);
}

void CImageEditMFCDlg::ReloadRightPanel()
{
	// get currently selected item on left panel
	HTREEITEM hSelected = m_treeLeftPanel.GetSelectedItem();

	if (hSelected == NULL)
	{
		return;
	}

	HTREEITEM hParent = m_treeLeftPanel.GetParentItem(hSelected);

	ITreeNode* node = (ITreeNode *)m_treeLeftPanel.GetItemData(hSelected);
	ITreeNode* parent = hParent ? (ITreeNode *)m_treeLeftPanel.GetItemData(hParent) : NULL;
	
	if (node == NULL)
	{
		return;
	}

	// clear right panel
	m_listRightPanel.DeleteAllItems();

	// if there is parent node, add .. item for it
	if (parent)
	{
		int nParentItem = m_listRightPanel.InsertItem(0, _T(".."));
		m_listRightPanel.SetItemData(nParentItem, (DWORD_PTR)parent);
	}

	int nLastDir = m_listRightPanel.GetItemCount();  // Index for directory insertion

	for (int i = 0; i < int(node->getChildsCount()); ++i)
	{
		// get child node
		ITreeNode* child = node->getChild(i);

		// get info for child node
		GenericInfo info = child->getGenericInfo();

		// get open/close icons for child node
		std::pair<int, int> icons = GetNodeIcons(info.icon);

		int nItem = 0;
		if (dynamic_cast<FileNode*>(child))
		{
			nItem = m_listRightPanel.InsertItem(m_listRightPanel.GetItemCount(), info.name, icons.second);
		}
		else
		{
			nItem = m_listRightPanel.InsertItem(nLastDir, info.name, icons.second);
			nLastDir = nItem + 1;
		}

		m_listRightPanel.SetItemData(nItem, (DWORD_PTR)child);

		CString temp;
		temp.Format(_T("%d"), info.lba);
		m_listRightPanel.SetItemText(nItem, 1, temp);
		temp.Format(_T("%I64d"), (int64)info.size);
		m_listRightPanel.SetItemText(nItem, 2, temp);
		m_listRightPanel.SetItemText(nItem, 3, info.date);
	}
}

void CImageEditMFCDlg::BuildNode(HTREEITEM parent, ITreeNode* node)
{
	// skip files
	if (dynamic_cast<FileNode*>(node) != 0)
	{
		return;
	}

	GenericInfo nodeInfo = node->getGenericInfo();

	std::pair<int, int> icons = GetNodeIcons(nodeInfo.icon);

	HTREEITEM treeItem;

	if (parent == NULL)
	{
		treeItem = m_treeLeftPanel.GetRootItem();

		if (treeItem)
		{
			m_treeLeftPanel.SetItemText(treeItem, nodeInfo.name);
		}
	}
	else
	{
		treeItem = m_treeLeftPanel.InsertItem(nodeInfo.name, icons.first, 
			icons.second, parent);
	}

	m_treeLeftPanel.SetItemData(treeItem, (DWORD_PTR)node);

	size_t childsCount = node->getChildsCount();

	for (unsigned i = 0; i < childsCount; ++i)
	{
		BuildNode(treeItem, node->getChild(i));
	}

	// do not expand directories
	if (dynamic_cast<DirectoryNode*>(node) == 0)
	{
		m_treeLeftPanel.Expand(treeItem, TVE_EXPAND);
	}
}

std::pair<int, int> CImageEditMFCDlg::GetNodeIcons(GenericInfo::Icon iconType)
{
	switch (iconType)
	{
		case GenericInfo::ICON_MEDIUM:
		case GenericInfo::ICON_SESSION:
		case GenericInfo::ICON_TRACK_DATA:			
			return std::make_pair(0, 0);

		case GenericInfo::ICON_TRACK_AUDIO:
			return std::make_pair(1, 1);

		case GenericInfo::ICON_FILESYS_ISO:
		case GenericInfo::ICON_FILESYS_JOLIET:
		case GenericInfo::ICON_FILESYS_ROCKRIDGE:
		case GenericInfo::ICON_FILESYS_UDF:
		case GenericInfo::ICON_FILESYS_BOOT:
			return std::make_pair(2, 2);

		case GenericInfo::ICON_DIRECTORY:
			return std::make_pair(3, 4);

		case GenericInfo::ICON_FILE:
			return std::make_pair(5, 5);

		default:
			return std::make_pair(0, 0);
	}	
}


void CImageEditMFCDlg::OnDiscVerify()
{
	NodeList nodes;

	HTREEITEM hItem = m_treeLeftPanel.GetRootItem();

	//Session
	HTREEITEM hSessionItem = m_treeLeftPanel.GetNextItem(hItem, TVGN_CHILD);

	while (hSessionItem)
	{
		//Track
		HTREEITEM hTrackItem = m_treeLeftPanel.GetNextItem(hSessionItem, TVGN_CHILD);

		while (hTrackItem)
		{
			//File System
			HTREEITEM hSysItem = m_treeLeftPanel.GetNextItem(hTrackItem, TVGN_CHILD);
			
			while (hSysItem)
			{
				nodes.push_back((ITreeNode*)m_treeLeftPanel.GetItemData(hSysItem));

				hSysItem = m_treeLeftPanel.GetNextItem(hSysItem, TVGN_NEXT);
			}

			hTrackItem = m_treeLeftPanel.GetNextItem(hTrackItem, TVGN_NEXT);
		}

		hSessionItem = m_treeLeftPanel.GetNextItem(hSessionItem, TVGN_NEXT);
	}

	KSaveContentDialog::SSaveContentParams params(KSaveContentDialog::AIM_VERIFY, nodes);
	KSaveContentDialog dlg(params);
	dlg.DoModal();
}

void CImageEditMFCDlg::OnDiscSave()
{
	std::vector<int16> vFileFormats;
	std::vector<CString> vDefExtensions;

	CString strPatternList;
	
	int16 nImageFormats;
	::GetPossibleImageFormats(&nImageFormats);

	if (!nImageFormats)
	{
		AfxMessageBox(_T("Disc is incorrect or no disc is inserted."));
		
		return;
	}
	
	if (nImageFormats & BS_IMG_ISO)
	{	
		strPatternList =_T("ISO files (*.iso)|*.iso|");
		vFileFormats.push_back(BS_IMG_ISO);
		vDefExtensions.push_back(_T(".iso"));
	}

	if (nImageFormats & BS_IMG_BIN)
	{
		strPatternList += _T("BIN files (*.bin)|*.bin|");
		vFileFormats.push_back(BS_IMG_BIN);
		vDefExtensions.push_back(_T(".bin"));
	}

	CFileDialog  dlg(FALSE, NULL, NULL, 0, strPatternList, this);
	//dlg.SetWindowText(_T("Choose file to save disk image"));

	if (dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName() + dlg.GetFileExt();
		
		int nFilterIndex = dlg.GetOFN().nFilterIndex - 1;
			
		if (dlg.GetFileExt() == _T(""))
		{
			strFileName += vDefExtensions[nFilterIndex];
		}
		
		KSaveDiscDialog dlg(this, strFileName, vFileFormats[nFilterIndex]);
		dlg.DoModal();
	}
}

void CImageEditMFCDlg::OnImageMountimage()
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, DLG_IMAGES_PATTERN, this);

	if (dlg.DoModal() == IDOK)
	{
		int32 res = ::SetImageFilePath(dlg.GetPathName());
		HandleError(res);

		if (IsImageDeviceEnabled())
		{
			m_cmbDevice.SetCurSel(0);
			OnCbnSelchangeComboDevice();
		}
		else
		{
			m_cmbDevice.DeleteString(m_cmbDevice.FindString(0, _T(">")));
			m_cmbDevice.AddString(_T("> ") + dlg.GetFileName());
			m_cmbDevice.SetCurSel(m_cmbDevice.GetCount() - 1);
			OnCbnSelchangeComboDevice();
		}
	}
}

void CImageEditMFCDlg::OnImageUnmountimage()
{
	int32 res = ::SetImageFilePath(NULL);
	HandleError(res);

	CString strDevice;
	m_cmbDevice.GetWindowText(strDevice);

	if (strDevice[0] == '#' || strDevice[0] == '>')
	{
		OnCbnSelchangeComboDevice();
	}
}

void CImageEditMFCDlg::OnImageMakeMd5()
{
	CString strImagePath = GetCurrentImagePath();

	if (strImagePath.IsEmpty())
	{
		CFileDialog  dlg(TRUE, NULL, NULL, 0, DLG_IMAGES_PATTERN, this);

		if (dlg.DoModal() == IDOK)
			strImagePath = dlg.GetPathName();
	}

	if (!strImagePath.IsEmpty())
	{
		KMd5Dialog md5Dlg(this, strImagePath);
		
		md5Dlg.DoModal();

		CStringA strMD5 = md5Dlg.GetMD5String();

		if (strMD5.GetLength() == 0)
		{
			AfxMessageBox(_T("Calculating MD5 hash problem"));
			return;
		}

		CString strMD5FileName = strImagePath.Left(strImagePath.Find(_T('.'))) + _T(".md5");
		
		if (FILE *pFile = _tfopen(strMD5FileName, _T("wb")))
		{
			fwrite((const char*)strMD5, 1, strMD5.GetLength(), pFile);
			fclose(pFile);
			AfxMessageBox(_T("MD5 hash \" ") + CString(strMD5) + 
				_T("\" has been written to file:\n") + strMD5FileName + _T(" ."));
		}
		else
		{
			USES_CONVERSION;
			AfxMessageBox(_T("Can't write MD5 hash \" ") + CString(strMD5) + 
				_T("\" to file ") + strMD5FileName + _T(" ."));
		}
	}
}

void CImageEditMFCDlg::OnImageCheckMd5()
{
	CString strImagePath = GetCurrentImagePath();

	if (strImagePath.IsEmpty())
	{
		CFileDialog  dlg(TRUE, NULL, NULL, 0, DLG_IMAGES_PATTERN, this);
		if (dlg.DoModal() == IDOK)
			strImagePath = dlg.GetPathName();
	}

	if (!strImagePath.IsEmpty())
	{
		CString strMD5FileName = strImagePath.Left(strImagePath.Find(_T('.'))) + _T(".md5");

#if _MSC_VER < 1400
		__stat64 devStat;
#else
		struct _stat64 devStat;
#endif
		int nFileSize = 0;
		if (0 == _tstat64(strMD5FileName, &devStat))
		{
			nFileSize = (int)devStat.st_size;
		}
		else
		{
			AfxMessageBox(_T("Can't find MD5 file \"") + strMD5FileName + _T("\"."));
			return;
		}

		KMd5Dialog md5Dlg(this, strImagePath);
		md5Dlg.DoModal();

		CStringA strMD5 = md5Dlg.GetMD5String();

		if (strMD5.GetLength() == 0)
		{
			AfxMessageBox(_T("Calculating MD5 hash problem"));
			return;
		}

		// Allocate buffer to read MD5
		CStringA strMD5FromFile;
		char* szBuffer = strMD5FromFile.GetBuffer(nFileSize + 1);
		szBuffer[nFileSize] = 0;

		// Read digest from file
		FILE *pFile = _tfopen(strMD5FileName, _T("r"));
		fread(szBuffer, nFileSize, 1, pFile);
		fclose(pFile);

		// Release buffer
		strMD5FromFile.ReleaseBuffer();

		// Compare calculated digest with digest from file
		if (strMD5 == strMD5FromFile)
		{
			AfxMessageBox(_T("MD5 hash \" ") + CString(strMD5) + 
				_T("\" is equal to those in ") + strMD5FileName + _T(" file."));
		}
		else
		{
			AfxMessageBox(_T("MD5 hash \" ") + CString(strMD5) + 
				_T("\" differs from those in .md5 file: \" ") + 
				CString(strMD5FromFile) + _T("\"."));
		}
	}
}

void CImageEditMFCDlg::OnAspiRescandevices()
{
	int32 res = ::RescanDevices();
	HandleError(res);

	// Update devices list

	UpdateDeviceCombo();
}

void CImageEditMFCDlg::OnAspiBurndevicesonly()
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = !m_bBurningDevicesOnly;

	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	UpdateDeviceCombo();
}

bool CImageEditMFCDlg::IsImageDeviceEnabled() const
{
	return GetMenu()->GetMenuState(ID_ASPI_DISABLEIMAGEWIRTER, MF_BYCOMMAND) == MF_UNCHECKED;
}

CString CImageEditMFCDlg::GetCurrentImagePath() const
{
	int32 nLength = 0;
	::GetImageFilePath(NULL, &nLength);

	CString strPath;
	::GetImageFilePath(strPath.GetBuffer(nLength), &nLength);
	strPath.ReleaseBuffer();

	return strPath;
}

void CImageEditMFCDlg::OnAspiDisableimagewirter()
{
	bool bDisable = IsImageDeviceEnabled();
	// Disable or enable image writer

	::EnableImageDevice(bDisable ? BS_FALSE : BS_TRUE);

	// Update devices list

	UpdateDeviceCombo();

	GetMenu()->CheckMenuItem(ID_ASPI_DISABLEIMAGEWIRTER, bDisable ? MF_CHECKED : MF_UNCHECKED);
}

void CImageEditMFCDlg::OnAudioPlayselected()
{
	TrackNode *pcTrackNode = 0;

	// First, try the right panel
	int indx_r = m_listRightPanel.GetSelectionMark();

	// If item is selected
	if (indx_r != -1)
	{
		ITreeNode* node = (ITreeNode*)m_listRightPanel.GetItemData(indx_r);
		// Check if it is TrackNode
		pcTrackNode = dynamic_cast<TrackNode*>(node);
	}

	// No track nodes are selected at right panel, so try left
	if (!pcTrackNode)
	{
		// Get selected item at the left panel
		HTREEITEM hItem = m_treeLeftPanel.GetSelectedItem();
		if (hItem != NULL)
		{
			ITreeNode* node = (ITreeNode*)m_treeLeftPanel.GetItemData(hItem);
			// Check if it is TrackItem
			pcTrackNode = dynamic_cast<TrackNode*>(node);
		}		
	}

	// If audio trac track is selected
	if (pcTrackNode && pcTrackNode->getTrackInfo().nFormat == BS_TF_AUDIO)
	{
		// Start playing selected track
		const STrackInfo& cSTrackInfo = pcTrackNode->getTrackInfo();
		
		KPlayTrackDialog dlg(cSTrackInfo.nTrackNumber);
		dlg.DoModal();
	}
}

void CImageEditMFCDlg::OnReadISRC()
{
	ASSERT(!m_cMenuNodes.empty());
	TrackNode* pcTrackNode = 0;
	pcTrackNode = dynamic_cast<TrackNode*>(m_cMenuNodes[0]);
	if(!pcTrackNode)
	{
		return;
	}

	int32 nTrackNumber = (int32) pcTrackNode->getTrackInfo().nTrackNumber;

	int32 res;
	TCHAR strISRC[13];
	HandleError(res = ::GetTrackISRC(BS_READ_DEVICE, nTrackNumber, strISRC));

	if(res != BS_SDK_ERROR_NO)
	{
		return;
	}
	
	strISRC[12] = TCHAR(0);

	MessageBox(KString(strISRC), _T("Track ISRC"));
}

void CImageEditMFCDlg::OnReadIndexes()
{
	ASSERT(!m_cMenuNodes.empty());
	TrackNode* pcTrackNode = 0;
	pcTrackNode = dynamic_cast<TrackNode*>(m_cMenuNodes[0]);
	if(!pcTrackNode)
	{
		return;
	}

	int32 nTrackNumber = (int32) pcTrackNode->getTrackInfo().nTrackNumber;

	const int32 max = 100;
	std::vector<int32> Indexes(max);
	int32 nInd  = max;
	int32 res;
	HandleError(res = ::GetTrackIndexes(BS_READ_DEVICE, nTrackNumber, &(Indexes[0]), &nInd));

	KString text, tmp;
	text = "";
	for(int i = 0; (i < nInd) && (i < 10); ++i)
	{
		tmp.Format("Index %d : %d\n", i, Indexes[i]);
		text += tmp;
	}

	if(nInd >= 10)
	{
		text += "...\nToo many indexes";
	}

	tmp.Format("\nPause length: %d", Indexes[1] - Indexes[0]);
	text += tmp;

	MessageBox(text, _T("Track indexes"));
}


void CImageEditMFCDlg::OnReadCDText()
{
	ASSERT(!m_cMenuNodes.empty());
	TrackNode* pcTrackNode = 0;
	pcTrackNode = dynamic_cast<TrackNode*>(m_cMenuNodes[0]);
	if(!pcTrackNode)
	{
		return;
	}

	int32 nTrackNumber = (int32) pcTrackNode->getTrackInfo().nTrackNumber;

	CString strArranger,
			strComposer,
			strSongWriter,
			strPerformer,
			strMessage,
			strTitle;

	int32 hCdText;
	
	int32 res;
	
	HandleError(res = ::ReadCDText(BS_READ_DEVICE, &hCdText));
	if(res != BS_SDK_ERROR_NO)
	{
		return;
	}

	HandleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_ARRANGER, strArranger));
	HandleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_COMPOSER, strComposer));
	HandleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_MESSAGE, strMessage));
	HandleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_PERFORMER, strPerformer));
	HandleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_SONG_WRITER, strSongWriter));
	HandleError(ExtractTextFromHandle(hCdText, nTrackNumber, BS_CDTCI_TITLE, strTitle));

	HandleError(res = ::CloseCDTextHandle(hCdText));
	if(res != BS_SDK_ERROR_NO)
	{
		return;
	}


	KCDTextReadDialog dlg(this,
		strArranger,
		strComposer,
		strSongWriter,
		strPerformer,
		strTitle,
		strMessage
		);

	dlg.DoModal();
	
	return;
}

void CImageEditMFCDlg::OnAudioGrabSelected()
{
	TrackNode *pcTrackNode = 0;

	// First, try the right panel
	int indx_r = m_listRightPanel.GetSelectionMark();

	// If item is selected
	if (indx_r != -1)
	{
		ITreeNode* node = (ITreeNode*)m_listRightPanel.GetItemData(indx_r);
		// Check if it is TrackNode
		pcTrackNode = dynamic_cast<TrackNode*>(node);
	}

	// No track nodes are selected at right panel, so try left
	if (!pcTrackNode)
	{
		// Get selected item at the left panel
		HTREEITEM hItem = m_treeLeftPanel.GetSelectedItem();
		if (hItem != NULL)
		{
			ITreeNode* node = (ITreeNode*)m_treeLeftPanel.GetItemData(hItem);
			// Check if it is TrackItem
			pcTrackNode = dynamic_cast<TrackNode*>(node);
		}
	}

	// If audio trac track is selected
	if (pcTrackNode && pcTrackNode->getTrackInfo().nFormat == BS_TF_AUDIO)
	{
		const STrackInfo& cSTrackInfo = pcTrackNode->getTrackInfo();

		// Make the vector of tracks to grab
		std::vector<int32> vTracks;
		vTracks.push_back(cSTrackInfo.nTrackNumber);

		// Invoke audio grabbing dialog
		KAudioGrabbingDialog dlg(vTracks);
		dlg.DoModal();
	}
}

void CImageEditMFCDlg::OnAudioGrabAll()
{	
	std::vector<int32> vTracks;
	TrackNode *pcTrackNode = 0;

	HTREEITEM hItem = m_treeLeftPanel.GetRootItem();

	//Session
	HTREEITEM hSessionItem = m_treeLeftPanel.GetNextItem(hItem, TVGN_CHILD);

	while (hSessionItem)
	{
		//Track
		HTREEITEM hTrackItem = m_treeLeftPanel.GetNextItem(hSessionItem, TVGN_CHILD);

		while (hTrackItem)
		{
			ITreeNode* node = (ITreeNode*)m_treeLeftPanel.GetItemData(hTrackItem);
			
			hTrackItem = m_treeLeftPanel.GetNextItem(hTrackItem, TVGN_NEXT);
		
			if (node == NULL)
			{
				continue;
			}

			pcTrackNode = dynamic_cast<TrackNode*>(node);

			if (pcTrackNode)
			{
				if (dynamic_cast<TrackNode*>(node)->getGenericInfo().icon == 
					GenericInfo::ICON_TRACK_AUDIO)
				{
					const STrackInfo& cSTrackInfo = pcTrackNode->getTrackInfo();
					vTracks.push_back(cSTrackInfo.nTrackNumber);
				}
			}
		}

		hSessionItem = m_treeLeftPanel.GetNextItem(hSessionItem, TVGN_NEXT);
	}

	if (vTracks.size() > 0)
	{
		KAudioGrabbingDialog dlg(vTracks);
		dlg.DoModal();
	}
}

void CImageEditMFCDlg::OnInformationShow()
{
	CAboutDlg	dlg(this);
	dlg.DoModal();
}

void CImageEditMFCDlg::OnInformationWeb()
{
	ShellExecute(0, _T("open"), _T(WEBSITELINK), 0, 0, SW_SHOW);
}

void CImageEditMFCDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		__int32 nLength = 2048;

		GetText(errCode, chError, &nLength);

		MessageBox(chError, _T("Error"), MB_OK | MB_ICONERROR);
	}
}

BOOL CImageEditMFCDlg::OnSetAspi(UINT nAspi)
{
	::SetASPI(nAspi - ID_INTERFACE_INTERNAL);

	int32 nActualAspi = 0;
	::GetASPI(&nActualAspi);

	GetMenu()->CheckMenuItem(ID_INTERFACE_INTERNAL, nActualAspi == BS_ASPI_INTERNAL ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_INTERFACE_WINASPI, nActualAspi == BS_ASPI_WNASPI ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_INTERFACE_FROGASPI, nActualAspi == BS_ASPI_FROGASPI ? MF_CHECKED : MF_UNCHECKED );

	UpdateDeviceCombo();
	return TRUE;
}

void CImageEditMFCDlg::UpdateDeviceCombo()
{
	CString strOldDevice;
	m_cmbDevice.GetWindowText(strOldDevice);

	m_cmbDevice.ResetContent();
	
	// Get devices list

	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 res = ::GetDevices(chListDevices, &nUsed, m_bBurningDevicesOnly ? TRUE : FALSE);
	HandleError(res);

	// Get current device

	TCHAR pchDevice[50];
	int32 nLength = sizeof(pchDevice) / sizeof(TCHAR);
	res = ::GetReadDevice(pchDevice, &nLength);
	HandleError(res);

	// Add devices to combo box

	for (int i = 0; i < nUsed; i++)
	{
		m_cmbDevice.AddString(chListDevices[i]);

		// Set selection on current device

		if (0 == _tcsncmp(pchDevice, chListDevices[i], 2))
		{
			m_cmbDevice.SetCurSel(i);
		}
	}

	// Check if any device is selected
	if (m_cmbDevice.GetCurSel() == -1)
	{
		// No device is selected, so select first
		m_cmbDevice.SetCurSel(0);
		OnCbnSelchangeComboDevice();
	}
	else
	{
		// Check if device is changed
		CString strCurDevice;
		m_cmbDevice.GetWindowText(strCurDevice);

		// If device is changed reload all information
		if (strCurDevice != strOldDevice)
			ReloadLeftPanel();
	}
}
void CImageEditMFCDlg::OnLvnItemchangedListRightpanel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;	
}

void CImageEditMFCDlg::OnTvnSelchangedTreeLeftpanel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	ReloadRightPanel();
}

void CImageEditMFCDlg::OnNMDblclkListRightpanel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (pNMLV->iItem < 0)
		return;

	ITreeNode* node = (ITreeNode *)m_listRightPanel.GetItemData(pNMLV->iItem);

	if (node == NULL)
		return;

	// get currently selected item on left panel
	HTREEITEM hSelected = m_treeLeftPanel.GetSelectedItem();

	if (hSelected == NULL)
		return;

	// check for ".."
	{
		HTREEITEM hParent = m_treeLeftPanel.GetParentItem(hSelected);

		if (hParent)
		{
			ITreeNode* parent = (ITreeNode*)m_treeLeftPanel.GetItemData(hParent);

			if (parent && parent == node)
			{
				SelectItem(hParent);				
				return;
			}
		}
	}

	m_treeLeftPanel.Expand(hSelected, TVE_EXPAND);

	HTREEITEM hSubItem = m_treeLeftPanel.GetChildItem(hSelected);

	for (; hSubItem; hSubItem = m_treeLeftPanel.GetNextItem(hSubItem, TVGN_NEXT))
	{
		ITreeNode* subNode = (ITreeNode*)m_treeLeftPanel.GetItemData(hSubItem);

		if (!subNode)
			continue;

		if (subNode == node)
		{
			SelectItem(hSubItem);			
			return;
		}
	}
}

void CImageEditMFCDlg::SelectItem(HTREEITEM item)
{
	m_treeLeftPanel.SelectItem(item);
	m_treeLeftPanel.EnsureVisible(item);
	ReloadRightPanel();
}

void CImageEditMFCDlg::OnNMRclickTreeLeftpanel(NMHDR *pNMHDR, LRESULT *pResult)
{	
	*pResult = 0;

	DWORD dw = GetMessagePos();

	CPoint pt;
	GetCursorPos(&pt);	
	m_treeLeftPanel.ScreenToClient(&pt);  	

	HTREEITEM hItem = m_treeLeftPanel.HitTest(pt);
	
	if (!hItem)
	{
		return;
	}
	
	m_treeLeftPanel.SelectItem(hItem);
	
	ITreeNode* node = (ITreeNode *)m_treeLeftPanel.GetItemData(hItem);
	
	if (node == NULL)
	{
		return;
	}

	NodeList nodes;
	nodes.push_back(node);
	
	POINT point;
	GetCursorPos(&point);
	
	// show menu for current nodes
	ShowPopupForNodes(nodes, point.x, point.y);
}

void CImageEditMFCDlg::OnNMRclickListRightpanel(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV->iItem < 0)
	{
		return;
	}

	m_listRightPanel.SetSelectionMark(pNMLV->iItem);


	NodeList nodes;

	POSITION pos = m_listRightPanel.GetFirstSelectedItemPosition();
	
	while (pos)
	{
		int nIndex = m_listRightPanel.GetNextSelectedItem(pos);

		if (nIndex >= 0)
		{
			nodes.push_back((ITreeNode*)m_listRightPanel.GetItemData(nIndex));
		}
	}

	// show menu for current nodes
	if (nodes.size() > 0)
	{	
		POINT point;
		GetCursorPos(&point);
	
		// show menu for current nodes
		ShowPopupForNodes(nodes, point.x, point.y);
	}
}

void CImageEditMFCDlg::ShowPopupForNodes(NodeList& nodes, int x, int y)
{
	ASSERT(!nodes.empty());
	
	CMenu popupMenu;
	popupMenu.CreatePopupMenu();

	m_cMenuNodes = nodes;
	
	if (dynamic_cast<FileSysNode*>(nodes[0]))
	{
		popupMenu.AppendMenu(MF_STRING, ID_EXTRACT_SYS, _T("Extract File System"));
	}

	if (dynamic_cast<TrackNode*>(nodes[0]))
	{
		popupMenu.AppendMenu(MF_STRING, ID_EXTRACT_TRACK, _T("Extract Track(s)"));
	}

	if (dynamic_cast<FileNode*>(nodes[0]) ||
		dynamic_cast<DirectoryNode*>(nodes[0]))
	{	
		popupMenu.AppendMenu(MF_STRING, ID_EXTRACT_FILE, _T("Extract Content"));
	}

	if (dynamic_cast<FileNode*>(nodes[0]))
	{
		popupMenu.AppendMenu(MF_STRING, ID_EXTRACT_FILEEX, _T("Extract Files Ex (Compress / Encrypted)"));
	}

	if (dynamic_cast<FileNode*>(nodes[0]))
	{
		popupMenu.AppendMenu(MF_STRING, ID_CHECK_SIGNATURE, _T("Check if source is compressed and/or encrypted"));
	}

	if (dynamic_cast<DirectoryNode*>(nodes[0]) ||
		dynamic_cast<FileSysNode*>(nodes[0]))
	{
		popupMenu.AppendMenu(MF_STRING, ID_LIST_CONTENT, _T("List Content"));		
	}

	if (nodes.size() == 1)
	{
		popupMenu.AppendMenu(MF_STRING, ID_VIEW_SECTOR, _T("View Sector"));
		popupMenu.AppendMenu(MF_STRING, ID_SCAN_SECTORS, _T("Scan Sectors"));
		
		// property command is available for all nodes
		popupMenu.AppendMenu(MF_STRING, ID_SHOW_PROPERTIES, _T("Properties"));
		
		if (dynamic_cast<TrackNode*>(nodes[0]) && 
			dynamic_cast<TrackNode*>(nodes[0])->getGenericInfo().icon == 
			GenericInfo::ICON_TRACK_AUDIO)
		{
			popupMenu.AppendMenu(MF_STRING, ID_AUDIO_PLAYSELECTED, _T("Play"));
			popupMenu.AppendMenu(MF_STRING, ID_AUDIO_GRABSELECTED, _T("Grab Audio"));
			popupMenu.AppendMenu(MF_STRING, ID_READ_CD_TEXT, _T("Read CD-Text"));			
			popupMenu.AppendMenu(MF_STRING, ID_READ_INDEXES, _T("Read Indexes"));		
			popupMenu.AppendMenu(MF_STRING, ID_READ_ISRC, _T("Read ISRC"));		
		}		
	}
		
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, x, y, this);
}

void CImageEditMFCDlg::OnShowProperties()
{
	ASSERT(!m_cMenuNodes.empty());

	FileNode *fileNode = dynamic_cast<FileNode*>(m_cMenuNodes[0]);
	KPropertiesDlg *dlg = fileNode ? new KFilePropertiesDlg(this, fileNode) :
		new KPropertiesDlg(this, m_cMenuNodes[0]);
	dlg->DoModal();
	delete dlg;
}

void CImageEditMFCDlg::OnViewSector()
{
	ASSERT(!m_cMenuNodes.empty());

	KSectorViewDialog dlg(this, m_cMenuNodes[0]->getGenericInfo().lba);
	dlg.DoModal();
}

void CImageEditMFCDlg::OnScanSector()
{
	ASSERT(!m_cMenuNodes.empty());
	
	GenericInfo cGI = m_cMenuNodes[0]->getGenericInfo();
	
	KErrorListLogCreator cLogCreator;
	KScanSectorsDialog dlg(this, cGI.lba, (int32)(cGI.size), &cLogCreator);
	dlg.DoModal();
}

void CImageEditMFCDlg::OnExtractTrack()
{
	ASSERT(!m_cMenuNodes.empty());

	for(size_t i = 0; i < m_cMenuNodes.size(); ++i)
	{
		TrackNode* pcTrackNode = 0;
		pcTrackNode = dynamic_cast<TrackNode*>(m_cMenuNodes[i]);
		
		CString strPatternList;
		std::vector<unsigned> vFileFormats;
		std::vector<CString> vDefExtensions;
		
		if (pcTrackNode)
		{
			const STrackInfo& cTrackInfo = pcTrackNode->getTrackInfo();
			
			switch (cTrackInfo.nFormat)
			{
				case BS_TF_AUDIO:
				{	
					strPatternList = _T("WAVE files (*.wav)|*.wav|BIN files (RAW FORMAT) (*.bin)|*.bin||");

					vFileFormats.push_back(BS_FF_WAVE);
					vFileFormats.push_back(BS_FF_BIN);

					vDefExtensions.push_back(_T(".wav"));
					vDefExtensions.push_back(_T(".bin"));
				}
				break;

				case BS_TF_DATA_MODE1:
				{
					strPatternList = _T("ISO files (*.iso)|*.iso");

					vFileFormats.push_back(BS_FF_ISO);
					vDefExtensions.push_back(_T(".iso"));
					
					//Check Disk
					SMediumInfo cMediumInfo;
					int32 nRes = ::GetMediumInformation(BS_READ_DEVICE, &cMediumInfo);

					if (cMediumInfo.wMediumTypeCode >= BS_CD_ROM &&
						cMediumInfo.wMediumTypeCode <= BS_CD_RW)
					{
						strPatternList += _T("|BIN files (RAW FORMAT) (*.bin)|*.bin||");

						vFileFormats.push_back(BS_FF_BIN);
						vDefExtensions.push_back(_T(".bin"));
					}
				}
				break;

				case BS_TF_DATA_MODE2:
				{	
					strPatternList = _T("MPEG files (*.mpg)|*.mpg|BIN files (RAW FORMAT) (*.bin)|*.bin||");

					vFileFormats.push_back(BS_FF_MPEG);
					vFileFormats.push_back(BS_FF_BIN);

					vDefExtensions.push_back(_T(".mpg"));
					vDefExtensions.push_back(_T(".bin"));
				}
				break;

			default:
				{
					HandleError(BS_SDK_ERROR_NOT_IMPLEMENTED);
					return;
				}
			}

			CString strDefaultName;

			strDefaultName.Format(_T("Track %d%s"), cTrackInfo.nTrackNumber, 
				vDefExtensions.size() > 0 ? vDefExtensions[0] : _T(""));
			
			CFileDialog  dlg(FALSE, NULL, strDefaultName, 
				OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_SHAREWARN,
				strPatternList, this);
			

			if (dlg.DoModal() != IDOK)
			{
				continue;
			}

			
			CString strFileName = dlg.GetPathName();
			
			int nFilterIndex = dlg.GetOFN().nFilterIndex - 1;
			
			if (dlg.GetFileExt() == _T(""))
			{
				strFileName += vDefExtensions[nFilterIndex];
			}

			if (doExtraction(cTrackInfo.nTrackNumber, strFileName, vFileFormats[nFilterIndex]) != IDOK)
			{
				break;
			}

		}// if(pcTrackNode)
		else
		{
			continue;
		}
	}
	
	// end
}

DWORD CImageEditMFCDlg::doExtraction(int16 nTrackNumber, 
									   const CString& strFilePath, 
									   unsigned int nFileFormat)
{
	KSaveTrackDialog dlg(this, nTrackNumber, strFilePath, nFileFormat);
	return (DWORD)dlg.DoModal();
}


void CImageEditMFCDlg::OnExtractFile()
{
	ASSERT(!m_cMenuNodes.empty());

	CString strFolderName = _T("");

	BROWSEINFO info;		
	
	TCHAR displayName[MAX_PATH];
	TCHAR selectedPath[MAX_PATH];

	info.hwndOwner = this->GetSafeHwnd();
	info.pidlRoot = NULL;
	info.pszDisplayName = displayName;
	
	info.lpszTitle = _T("Choose folder for extraction");
	info.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT |BIF_NEWDIALOGSTYLE/* |BIF_EDITBOX*/ ;
	info.lpfn = NULL;
	info.lParam = NULL;	
	info.iImage = 0;

	LPITEMIDLIST selectedFolder = SHBrowseForFolder(&info);

	if (selectedFolder != NULL) 
	{
		if (SHGetPathFromIDList(selectedFolder, selectedPath)) 
		{
			strFolderName = CString(selectedPath);
		}

		if (strFolderName == _T(""))
		{
			AfxMessageBox(_T("Extraction path cannot be empty."));
			return;
		}

		KSaveContentDialog::SSaveContentParams params(KSaveContentDialog::AIM_IMPORT, 
			m_cMenuNodes, strFolderName);

		KSaveContentDialog dlg(params);
		dlg.DoModal();
	}
}

void CImageEditMFCDlg::OnCheckSignature()
{
	int nRes = ::CheckSignature();
	CString sourceType = _T("");
	switch (nRes) {
	case BS_SDK_COMPENC_ENCRYPTED:
		sourceType = _T("Disc or Image is encrypted!");
		break;
	case BS_SDK_COMPENC_COMPRESSED:
		sourceType = _T("Disc or Image is compressed!");
		break;
	case BS_SDK_COMPENC_BOTH:
		sourceType = _T("Disc or Image is compressed and encrypted!");
		break;
	default:
		sourceType = _T("Disc or Image is not compressed and encrypted!");
	}
	MessageBox(sourceType, _T("Is disc/image encrypted or compressed?"), MB_ICONINFORMATION);

}

void CImageEditMFCDlg::OnExtractFileEx()
{
	ASSERT(!m_cMenuNodes.empty());

	CString strFolderName = _T("");

	BROWSEINFO info;

	TCHAR displayName[MAX_PATH];
	TCHAR selectedPath[MAX_PATH];

	info.hwndOwner = this->GetSafeHwnd();
	info.pidlRoot = NULL;
	info.pszDisplayName = displayName;

	info.lpszTitle = _T("Choose folder for extraction");
	info.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT | BIF_NEWDIALOGSTYLE/* |BIF_EDITBOX*/;
	info.lpfn = NULL;
	info.lParam = NULL;
	info.iImage = 0;

	LPITEMIDLIST selectedFolder = SHBrowseForFolder(&info);

	if (selectedFolder != NULL)
	{
		if (SHGetPathFromIDList(selectedFolder, selectedPath))
		{
			strFolderName = CString(selectedPath);
		}

		if (strFolderName == _T(""))
		{
			AfxMessageBox(_T("Extraction path cannot be empty."));
			return;
		}

		CString strTmpName = _T("");
		int nRes = ::CheckSignature();
		if (nRes == BS_SDK_COMPENC_ENCRYPTED || nRes == BS_SDK_COMPENC_BOTH) {
			CPasswordDlg cDlg;
			if (IDOK == cDlg.DoModal())
			{
				strTmpName = cDlg.m_strPassword;
			
			} else {
				AfxMessageBox(_T("Password is needed for encrypted files."));
				return;
			}
		}

		

		KSaveContentDialog::SSaveContentParams params(KSaveContentDialog::AIM_IMPORT,
			m_cMenuNodes, strFolderName, strTmpName, BS_IMPOPTS_EX);

		KSaveContentDialog dlg(params);
		dlg.DoModal();
	}
}

void CImageEditMFCDlg::OnListContent()
{
	ASSERT(!m_cMenuNodes.empty());

	CFileDialog  dlg(FALSE, NULL, NULL, 0, _T("Text files (*.txt)|*.txt"), this);

	if (dlg.DoModal() == IDOK)
	{

		CString strFileName = dlg.GetFileName();

		if (!strFileName.GetLength())
		{
			return;
		}

		if (_T("") == dlg.GetFileExt())
		{
			strFileName += _T(".txt");
		}
	
		FILE *pFile = _tfopen(strFileName, _T("w"));
		
		RecursivePrintContent(pFile, m_cMenuNodes[0], CString(PATHSEPSTRING));
		
		fclose(pFile);
	}
}

void CImageEditMFCDlg::RecursivePrintContent(FILE *pFile, ITreeNode* pcNode, CString strFolderPath)
{
	int32 res = 0;
	
	FileSysNode *pcFSysNode = 0;
	pcFSysNode = dynamic_cast<FileSysNode*>(pcNode);

	if (pcFSysNode)
	{
		int32 nChildCount = (int32)pcFSysNode->getChildsCount();

		for (int32 i = 0; i < nChildCount; i++)
		{
			RecursivePrintContent(pFile, pcFSysNode->getChild(i), strFolderPath);
		}
	}
	else
	{
		DirectoryNode* pcDirNode = 0;
		pcDirNode = dynamic_cast<DirectoryNode*>(pcNode);

		if (pcDirNode)
		{
			GenericInfo info = pcDirNode->getGenericInfo();

			strFolderPath += info.name;
			strFolderPath += PATHSEPSTRING;

			CString strWrite(strFolderPath);
			strWrite += _T("\n");
			
			fwrite(strWrite.GetBuffer(0), sizeof(TCHAR), strWrite.GetLength(), pFile);
			strWrite.ReleaseBuffer();

			int32 nChildCount = (int32)pcDirNode->getChildsCount();

			for (int32 i = 0; i < nChildCount; i++)
			{
				RecursivePrintContent(pFile, pcDirNode->getChild(i), strFolderPath);
			}
		}
		else
		{
			FileNode* pcFileNode = 0;
			pcFileNode = dynamic_cast<FileNode*>(pcNode);

			if(pcFileNode)
			{
				GenericInfo info = pcFileNode->getGenericInfo();
				
				CString strWrite(strFolderPath);
				strWrite += info.name;
				strWrite += _T("\n");
				
				fwrite(strWrite.GetBuffer(0), sizeof(TCHAR), strWrite.GetLength(), pFile);
				strWrite.ReleaseBuffer();
			}
		}
	}
}

int32 CImageEditMFCDlg::ExtractTextFromHandle(int32 handle,int32 nTrackNumber,int32 nCDTCI, CString& rText)
{
	int32 nLen = 0;
	int32 res;

	HandleError(res = ::GetCDTextTrackTagString(handle, nTrackNumber, nCDTCI, 0, &nLen));
	if(res != BS_SDK_ERROR_NO)
	{
		return res;
	}

	if(!nLen || nLen == 1)
	{
		rText = L"";
		return BS_SDK_ERROR_NO;
	}

	TCHAR *pBuf = new TCHAR[nLen];
	HandleError(res = ::GetCDTextTrackTagString(handle, nTrackNumber, nCDTCI, pBuf, &nLen));
	if(res != BS_SDK_ERROR_NO)
	{
		delete pBuf;
		return res;
	}

	pBuf[nLen-1] = _T('\0');
	rText = CString(pBuf);

	delete pBuf;

	return BS_SDK_ERROR_NO;
}

void CImageEditMFCDlg::OnRefresh()
{
	ReloadLeftPanel();
}

void CImageEditMFCDlg::OnSaveLog()
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(m_strStartupDir + _T("\\FoxSampleImageEditW.log"));
}