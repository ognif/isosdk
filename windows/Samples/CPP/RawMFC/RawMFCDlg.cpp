// RawMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MaskAndMode.h"
#include "RawMFC.h"
#include "RawMFCDlg.h"
#include "../Common/AboutDlgMFC.h"
#include "../Common/SampleBurnDlgMFC.h"
#include "IsoSDKExport.h"
#include ".\rawMFCdlg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <cassert>
#include <utility>
#include "MaskAndMode.h"
#include "config.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void SetMaskListChecks(CListCtrl& cList, int32 nMask)
{
	for(int i = 0; i < cList.GetItemCount(); ++i)
	{
		cList.SetCheck(i, BOOL(cList.GetItemData(i) & nMask));
	}
}

int32 Format2SectorSize(int8 nFormat)
{
	if (nFormat == BS_RTF_MODE1)
		return 2048;
	
	return 2352;
}


// CRawWriterDlg dialog


CRawWriterDlg::CRawWriterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRawWriterDlg::IDD, pParent)
	, m_bBurningDevicesOnly(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRawWriterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRACKMODE, cbTrackMode);
	DDX_Control(pDX, IDC_LISTDATAMASK, lstDataMask);
	DDX_Control(pDX, IDC_LISTIGNOREMASK, lstIgnoreMask);
	DDX_Control(pDX, IDC_TRACKITEMS, reportTrackItems);
	DDX_Control(pDX, IDC_TRACKNUMBER, edTrackNo);
	DDX_Control(pDX, IDC_CMBBX_DRIVES, m_cmbDevice);
	DDX_Control(pDX, IDC_ADDFILE, AddFileEdit);
}

BEGIN_MESSAGE_MAP(CRawWriterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADDTRACK, &CRawWriterDlg::OnBnClickedAddtrack)
	ON_BN_CLICKED(IDC_RESETTRACK, &CRawWriterDlg::OnBnClickedResettrack)
	ON_BN_CLICKED(IDC_DELETETRACK, &CRawWriterDlg::OnBnClickedDeletetrack)
	ON_COMMAND(ID_FILE_EXIT, OnExit)
	ON_COMMAND(ID_TRACKS_ADDTRACK, OnBnClickedAddtrack)		
	ON_COMMAND(ID_TRACKS_RESETTRACKLIST, OnReset)
	ON_COMMAND(ID_INFO_ABOUT, OnAboutBox)
	ON_COMMAND(ID_INFO_WEBSITE, OnVisitWeb)
    ON_COMMAND(ID_FILE_TRYTOANALYZEFILE, OnBnClickedAnalyzebutton)	
	ON_BN_CLICKED(IDC_SELFILE, &CRawWriterDlg::OnBnClickedSelfile)
	ON_COMMAND(ID_FILE_ADDFILE, OnBnClickedSelfile)	
    ON_BN_CLICKED(IDC_ANALIZEBUTTON, OnBnClickedAnalyzebutton)
	ON_COMMAND(ID_BURN_BURNWITHFOXBURNEREMBEDDEDDIALOG, OnBurnWithFoxBurnerEmbeddedDialog)
	ON_COMMAND(ID_FUNCTIONS_BURNDISC, OnBurnDiscWithDevelopedGUI)
	ON_COMMAND_EX_RANGE(ID_INTERFACE_ASPI, ID_INTERFACE_FROGASPI, OnSetAspi)	
	ON_COMMAND(ID_ASPI_BURNDEVICESONLY, OnBurningDevices)
	ON_COMMAND(ID_ASPI_DISABLEIMAGEWIRTER, OnDisableImagewriter)
	ON_CBN_SELCHANGE(IDC_CMBBX_DRIVES, OnDrives)
	ON_COMMAND(ID_BURN_ERASEDISK ,OnBurnErasedisk)	
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_TRACKITEMS, OnLvnItemchangedTrackitems)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_INDEX, OnDeltaposSpinIndex)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRACK, OnDeltaposSpinTrack)
	ON_COMMAND(ID_OPTIONS_EJECTDISC, OnSetEject)
	ON_COMMAND(ID_OPTIONS_VERIFY, OnSetVerify)
	ON_COMMAND(ID_OPTIONS_JOLIETFILESYSTEM, OnSetJoliet)
	ON_COMMAND(ID_OPTIONS_FINALIZE, OnSetFinalize)
	ON_COMMAND(ID_FILE_WRITELOGFILE, OnSaveLog)
END_MESSAGE_MAP()


// CRawWriterDlg message handlers

#define APP_TITLE STR(IsoSDK IsoSDK_VERSION_MAJOR.IsoSDK_VERSION_MINOR Raw MFC Sample Application)

BOOL CRawWriterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	SetWindowText(_T(APP_TITLE));
	GetDlgItem(IDC_TRACKNUMBER)->SetWindowText(_T("1"));
	GetDlgItem(IDC_TRACKINDEX)->SetWindowText(_T("1"));

	
	m_strModeAudio.Format(IDS_MODE_AUDIO);
	m_strMode1.Format(IDS_MODE_1);
	m_strMode2Formless.Format(IDS_MODE_2_FORMLESS);
	m_strMode2Form1.Format(IDS_MODE_2_FORM_1);
	m_strMode2Form2.Format(IDS_MODE_2_FORM_2);
	m_strModeCDG.Format(IDS_MODE_CDG);
	m_strModeUnknown.Format(IDS_MODE_UNKNOWN);

	m_strRdtSyncHeader.Format(IDS_BS_RDT_SYNC_HEADER);
	m_strRdtSubHeaders.Format(IDS_BS_RDT_SUBHEADERS);
	m_strRdtData.Format(IDS_BS_RDT_DATA);
	m_strRdtEdcEcc.Format(IDS_BS_RDT_EDC_ECC);
	m_strRdtSubChPq.Format(IDS_BS_RDT_SUBCH_PQ);
	m_strRdtSubChPw.Format(IDS_BS_RDT_SUBCH_PW);
	m_strRdtSubChRw.Format(IDS_BS_RDT_SUBCH_RW);


	cbTrackMode.AddString(m_strModeAudio);
	cbTrackMode.AddString(m_strMode1);
	cbTrackMode.AddString(m_strMode2Formless);
	cbTrackMode.AddString(m_strMode2Form1);
	cbTrackMode.AddString(m_strMode2Form2);
	cbTrackMode.SetCurSel(1);

	InitMaskList(lstDataMask);
	InitMaskList(lstIgnoreMask);

	reportTrackItems.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	reportTrackItems.InsertColumn(0, _T("No."), LVCFMT_LEFT, 35);
	reportTrackItems.InsertColumn(1, _T("Ind."), LVCFMT_LEFT, 35);
	reportTrackItems.InsertColumn(2, _T("Mode"), LVCFMT_LEFT, 90);
	reportTrackItems.InsertColumn(3, _T("Data Mask"), LVCFMT_LEFT, 150);
	reportTrackItems.InsertColumn(4, _T("Ignore Mask"), LVCFMT_LEFT, 150);
	reportTrackItems.InsertColumn(5, _T("Start Adress"), LVCFMT_LEFT, 80);
	reportTrackItems.InsertColumn(6, _T("Length"), LVCFMT_LEFT, 60);
	reportTrackItems.InsertColumn(7, _T("Offset"), LVCFMT_LEFT, 60);

	GetDlgItem(IDC_STARTADRESS)->SetWindowText(_T("0"));
	GetDlgItem(IDC_OFFSET)->SetWindowText(_T("0"));
	GetDlgItem(IDC_TRACKLENGTH)->SetWindowText(_T("0"));
	

	//--------------------------------------------------
    //Init the SDK
    //--------------------------------------------------

	TCHAR chLicenseKey[35] = _T("67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7");
	int32 res = ::Initialize(chLicenseKey, BS_ASPI_INTERNAL, BS_TRUE);
	if (res != BS_SDK_ERROR_NO) {
		HandleError(res);
		PostQuitMessage(0);
		return FALSE;
	}
	
	//----------------------------------------------------------
    //We need to set a project. So we set default project first
	//----------------------------------------------------------

	res = ::CreateProject(BS_BURNER_RAW, BS_CONTINUE_NO_SESSION);
	HandleError(res);

	//--------------------------------------------------
    //Set the Options. Remember, not all Options are 
	//available on all projects. Read Help
    //--------------------------------------------------
	
	SOptions opt;
	res = ::GetOptions(&opt);
	HandleError(res);

	opt.bTestBurn = BS_FALSE;
	opt.bPerformOPC = BS_FALSE;
	opt.bJolietFileSystem = BS_TRUE;
	opt.bEjectAfterBurn = BS_TRUE;
	opt.nCacheSize = 4*1024*1024;
	opt.bFinalize = BS_FALSE;

	m_bEjectAfterBurn = opt.bEjectAfterBurn;	
	m_bJoliet = opt.bJolietFileSystem;
	m_bFinalize = opt.bFinalize;
	m_bVerify = opt.bVerifyAfterBurn;

	_tcscpy(opt.chVolumeLabel, _T("IsoSDK"));
	res = ::SetOptions(opt);
	HandleError(res);

	UpdateDeviceCombo();

	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISC, m_bEjectAfterBurn ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_FINALIZE, m_bFinalize ? MF_CHECKED : MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_OPTIONS_VERIFY, m_bVerify ? MF_CHECKED : MF_UNCHECKED);

	GetCurrentDirectory(_MAX_PATH, m_strStartupDir.GetBuffer(_MAX_PATH));
	m_strStartupDir.ReleaseBuffer();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRawWriterDlg::InitMaskList(CListCtrl& cList)
{
	cList.SetExtendedStyle(LVS_EX_CHECKBOXES);

	cList.InsertColumn(0, _T(""), LVCFMT_LEFT, 150);

	cList.InsertItem (0, m_strRdtSyncHeader);
	cList.SetItemData(0, BS_RDT_SYNC_HEADER);
	cList.InsertItem (1, m_strRdtSubHeaders);
	cList.SetItemData(1, BS_RDT_SUBHEADERS);
	cList.InsertItem (2, m_strRdtData);
	cList.SetItemData(2, BS_RDT_DATA);
	cList.InsertItem (3, m_strRdtEdcEcc);
	cList.SetItemData(3, BS_RDT_EDC_ECC);
	cList.InsertItem (4, m_strRdtSubChPq);
	cList.SetItemData(4, BS_RDT_SUBCH_PQ);
	cList.InsertItem (5, m_strRdtSubChPw);
	cList.SetItemData(5, BS_RDT_SUBCH_PW);
	cList.InsertItem (6, m_strRdtSubChRw);
	cList.SetItemData(6, BS_RDT_SUBCH_RW);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRawWriterDlg::OnPaint()
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
HCURSOR CRawWriterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRawWriterDlg::OnBnClickedAddtrack()
{
	SRAWTrackToAdd track;

	int nNumb = 1;
	int nInd = -1;

	if (m_vTracks.size() > 0)
	{
		nNumb = m_vTracks.back().nNumber + 1;
		nInd = m_vTracks.back().nIndex;
	}
	
	int nItemPos = reportTrackItems.GetItemCount();

	CString strValue;
	int nTrackNumber, nTrackIndex;

	GetDlgItem(IDC_TRACKNUMBER)->GetWindowText(strValue);
	nTrackNumber = _ttoi(strValue);
	
	GetDlgItem(IDC_TRACKINDEX)->GetWindowText(strValue);
	nTrackIndex = _ttoi(strValue);

	if (nNumb == nTrackNumber || 
		(nNumb - 1 == nTrackNumber && nTrackIndex > nInd &&
		(nItemPos - 2 < 0 || m_vTracks[nItemPos - 2].nNumber != nTrackNumber )))
	{
		track.nNumber = nTrackNumber;
		
		CString itemBuilder;
		
		itemBuilder.Format(_T("%d"), nTrackNumber);
		reportTrackItems.InsertItem(nItemPos, itemBuilder);
		
		
		itemBuilder.Format(_T("%d"), nTrackIndex);
		reportTrackItems.SetItemText(nItemPos, 1, itemBuilder);

		track.nIndex = nTrackIndex;/////////

		cbTrackMode.GetLBText(cbTrackMode.GetCurSel(), itemBuilder);
		reportTrackItems.SetItemText(nItemPos, 2, itemBuilder);

		track.nFormat = MaskAndMode::str2format(itemBuilder);
		track.nDataTypeMask = 0;

		for (int i = 0; i < lstDataMask.GetItemCount(); i++)
		{
			if (lstDataMask.GetCheck(i))
			{
				track.nDataTypeMask |= lstDataMask.GetItemData(i);
			}
		}

		// --- ADDED
		itemBuilder =  MaskAndMode::getMask<CString>(track.nDataTypeMask);

		reportTrackItems.SetItemText(nItemPos, 3, itemBuilder);

		track.nIgnoreDataMask = 0;

		for (int i = 0; i < lstIgnoreMask.GetItemCount(); i++)
		{
			if (lstIgnoreMask.GetCheck(i))
			{
				track.nIgnoreDataMask |= lstIgnoreMask.GetItemData(i);
			}
		}

		// --- ADDED
		itemBuilder =  MaskAndMode::getMask<CString>(track.nIgnoreDataMask);

		reportTrackItems.SetItemText(nItemPos, 4, itemBuilder);
		
		itemBuilder = _T("");
		GetDlgItem(IDC_STARTADRESS)->GetWindowText(itemBuilder);
		reportTrackItems.SetItemText(nItemPos, 5, itemBuilder);

		track.nStartAddress = _ttoi(itemBuilder);

		itemBuilder = _T("");
		GetDlgItem(IDC_TRACKLENGTH)->GetWindowText(itemBuilder);
		reportTrackItems.SetItemText(nItemPos, 6, itemBuilder);
		track.nLength = _ttoi(itemBuilder);

		if (track.nLength <= 0)
		{			
			reportTrackItems.DeleteItem(nItemPos);
			AfxMessageBox(_T("The length of the track should be more than '0'"));
			return;
		}

		itemBuilder = _T("");
		GetDlgItem(IDC_OFFSET)->GetWindowText(itemBuilder);
		reportTrackItems.SetItemText(nItemPos, 7, itemBuilder);
		track.nOffset = _ttoi(itemBuilder);
		
		m_vTracks.push_back(track);
	}
	else
	{
		MessageBox(_T("Track number or Index is not correct."),
			_T("Error"), MB_OK | MB_ICONERROR);
	}
}

void CRawWriterDlg::OnExit()
{	
	OnCancel();
}

void CRawWriterDlg::OnReset()
{
	::ClearAll();
	
	AddFileEdit.SetWindowText(_T(""));

    m_vTracks.clear();
	
	reportTrackItems.DeleteAllItems();

	SetMaskListChecks(lstIgnoreMask, 0);
	SetMaskListChecks(lstDataMask, 0);
	cbTrackMode.SetCurSel(1);

	GetDlgItem(IDC_STARTADRESS)->SetWindowText(_T(""));
	GetDlgItem(IDC_TRACKLENGTH)->SetWindowText(_T(""));
	GetDlgItem(IDC_OFFSET)->SetWindowText(_T(""));
}

void CRawWriterDlg::OnAboutBox()
{
	CAboutDlg dlg(this);
	dlg.DoModal();
}

void CRawWriterDlg::OnVisitWeb()
{
	ShellExecute(0, _T("open"), _T("http://www.isosdk.com"), 0, 0, SW_SHOW);
}

void CRawWriterDlg::OnBnClickedSelfile()
{
	OnReset();
	CString selName;
	OPENFILENAME ofn = {sizeof(ofn)};
	ofn.hwndOwner = this->m_hWnd;
	ofn.lpstrFilter = _T("All Files (*.*)\0*.*\0");
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = selName.GetBuffer(MAX_PATH);
	
	if (GetOpenFileName(&ofn))
	{
		SFileToAdd	fileToAdd;

		//set disc image file path
		fileToAdd.lpszSourceFilePath = ofn.lpstrFile;

		//add file for burning
		int32 res = ::AddFile(fileToAdd);
		HandleError(res);

		selName.ReleaseBuffer();
        AddFileEdit.SetWindowText(selName);		
	}
}


BOOL CRawWriterDlg::OnMountImage(UINT)
{
	CFileDialog  dlg(TRUE, NULL, NULL, 0, _T("ISO Files (*.iso)|*.iso||"), this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPath = dlg.GetPathName();

		if (strPath.Find(_T(".iso\0")) == -1)
		{
			strPath += _T(".iso");
		}

		int32 res = ::SetImageFilePath(strPath);
		HandleError(res);
		return res == BS_SDK_ERROR_NO ? TRUE : FALSE;
	}

	return FALSE;
}

void CRawWriterDlg::OnUnmountImage()
{
	::SetImageFilePath(NULL);
}

int64 CRawWriterDlg::AddTrackInfo(int32 nNumber, int32 nIndex, int64 nDiskOffset, int8 nTrackFormat, STrackInfo sTrack)
{	
	CString itemBuilder;

	int nTrackListNumber = reportTrackItems.GetItemCount();

	SRAWTrackToAdd rawTrack;
	rawTrack.nNumber = nNumber;
	rawTrack.nIndex = nIndex;
	rawTrack.nOffset = nDiskOffset;
	rawTrack.nStartAddress = sTrack.nStartLBA;
	rawTrack.nFormat = nTrackFormat;
	rawTrack.nDataTypeMask = BS_RDT_DATA;
	rawTrack.nIgnoreDataMask = 0;
	rawTrack.nLength = sTrack.nSize;
	

	switch(nTrackFormat)
	{
		case BS_RTF_MODE2_FORM1:
			rawTrack.nDataTypeMask   |= BS_RDT_SUBHEADERS|BS_RDT_EDC_ECC;
			rawTrack.nIgnoreDataMask |= BS_RDT_EDC_ECC;
			break;

		case BS_RTF_MODE2_FORM2:
			rawTrack.nDataTypeMask   |= BS_RDT_SYNC_HEADER|BS_RDT_SUBHEADERS|BS_RDT_EDC_ECC;
			rawTrack.nIgnoreDataMask |= BS_RDT_SYNC_HEADER|BS_RDT_EDC_ECC;
			break;
	}

	//add to vector
	m_vTracks.push_back(rawTrack);

	itemBuilder.Format(_T("%d"), rawTrack.nNumber);

	reportTrackItems.InsertItem(nTrackListNumber, itemBuilder);

	itemBuilder.Format(_T("%d"), rawTrack.nIndex);
	reportTrackItems.SetItemText(nTrackListNumber, 1, itemBuilder);

	reportTrackItems.SetItemText(nTrackListNumber, 2, MaskAndMode::getMode<CString>(rawTrack.nFormat));
	
	reportTrackItems.SetItemText(nTrackListNumber, 3, MaskAndMode::getMask<CString>(rawTrack.nDataTypeMask));

	reportTrackItems.SetItemText(nTrackListNumber, 4, MaskAndMode::getMask<CString>(rawTrack.nIgnoreDataMask));

	itemBuilder.Format(_T("%d"), rawTrack.nStartAddress);
	reportTrackItems.SetItemText(nTrackListNumber, 5, itemBuilder);

	itemBuilder.Format(_T("%d"), rawTrack.nLength);
	reportTrackItems.SetItemText(nTrackListNumber, 6, itemBuilder);

	itemBuilder.Format(_T("%d"), rawTrack.nOffset);
	reportTrackItems.SetItemText(nTrackListNumber, 7, itemBuilder);
	
	itemBuilder.Format(_T("%d"), nNumber + 1);
	edTrackNo.SetWindowText(itemBuilder);

	nDiskOffset += (int64)rawTrack.nLength * Format2SectorSize(rawTrack.nFormat);	

	return nDiskOffset;
}


void CRawWriterDlg::OnBnClickedAnalyzebutton()
{
	USES_CONVERSION;
    CString FileName;
    AddFileEdit.GetWindowText(FileName);

    if (FileName.IsEmpty())
    {
        MessageBox(_T("File name is not specified."), _T("Error"), MB_OK | MB_ICONERROR);
        return;
    }

	OnReset();

	SFileToAdd	fileToAdd;			
	fileToAdd.lpszSourceFilePath = FileName;

	int32 res = ::AddFile(fileToAdd);
	HandleError(res);

	int64 nDiskOffset = 0;
	int32 nCurrentLastSector = 0;

	res = ::SetImageFilePath(fileToAdd.lpszSourceFilePath);
	HandleError(res);

	if (res != BS_SDK_ERROR_NO)
	{
		return;
	}

	res = ::SetReadDevice(CString(_T('#')));
	HandleError(res);

	if (res != BS_SDK_ERROR_NO)
	{
		return;
	}
	
	SMediumInfo mi;
	res = ::GetMediumInformation(BS_READ_DEVICE, &mi);
	HandleError(res);


	//First pregap (-150) analize

	nDiskOffset = 0;

	if (mi.nFirstSession > 0 && mi.nLastSession > 0)
	{
		for (int32 i = mi.nFirstSession; i <= mi.nLastSession; i++)
		{
			SSessionInfo si;
			res = ::GetSessionInformation(BS_READ_DEVICE, i, &si);
			HandleError(res);

			for(int32 j = si.nFirstTrack; j <= si.nLastTrack; ++j)
			{
				STrackInfo cTrackInfo;
				res = ::GetTrackInformation(BS_READ_DEVICE, j, &cTrackInfo);
				HandleError(res);

				nDiskOffset += (int64)cTrackInfo.nSize * Format2SectorSize(cTrackInfo.nFormat);
			}
		}
#if _MSC_VER < 1400
		__stat64 devStat;
#else
		struct _stat64 devStat;
#endif
		if (0 != _tstat64(FileName, &devStat))
		{	
			return;
		}
		
		if (nDiskOffset < devStat.st_size)
		{
			//need first pregap
			nCurrentLastSector = -150;
		}
	}

	nDiskOffset = 0;

	int nTrackNumber = reportTrackItems.GetItemCount() + 1;

	if (mi.nFirstSession > 0 && mi.nLastSession > 0)
	{
		for (int32 i = mi.nFirstSession; i <= mi.nLastSession; i++)
		{
			SSessionInfo si;
			res = ::GetSessionInformation(BS_READ_DEVICE, i, &si);
			HandleError(res);

			for(int32 j = si.nFirstTrack; j <= si.nLastTrack; ++j)
			{
				STrackInfo cTrackInfo;
				res = ::GetTrackInformation(BS_READ_DEVICE, j, &cTrackInfo);
				HandleError(res);

				int8 nTrackFormat;
				res = ::GetTrackFormatEx(BS_READ_DEVICE, j, &nTrackFormat);
				HandleError(res);

				if (nCurrentLastSector != cTrackInfo.nStartLBA)
				{
					STrackInfo cPregapInfo;
					cPregapInfo.nStartLBA = nCurrentLastSector;
					cPregapInfo.nSize = cTrackInfo.nStartLBA - nCurrentLastSector;

					nDiskOffset = AddTrackInfo(nTrackNumber, 0, nDiskOffset, nTrackFormat, cPregapInfo);
				}
		
				nDiskOffset = AddTrackInfo(nTrackNumber, 1, nDiskOffset, nTrackFormat, cTrackInfo);

				nCurrentLastSector = cTrackInfo.nStartLBA + cTrackInfo.nSize;

				++nTrackNumber;
			}
		}
	}

	res = ::SetImageFilePath(_T(""));
	HandleError(res);
}


void CRawWriterDlg::OnBurnDiscWithDevelopedGUI()
{
	if(m_vTracks.empty())
	{
		AfxMessageBox(_T("Please, create at least one track."));
		return;
	}

	// Synchronize options and menu controls

	UpdateOptions();

	// Get current device
	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	HandleError(res);

	// Also set special options for image writer
	SOptions opt;

	// Load current options first
	res = ::GetOptions(&opt);
	HandleError(res);

	if (0 == _tcsncmp(_T("#"), chBurnDevices[0], 1))  // Iso writer selected
	{
		if (!OnMountImage(0))
			return;

		opt.nCopies = 0;	// No need for copies
		opt.bTestBurn = BS_FALSE;	// Test burn not supported
		opt.bVerifyAfterBurn = BS_FALSE;	// Test burn not supported

		// Then save options
		res = ::SetOptions(opt);
		HandleError(res);		
	}

	//set logical structure of disc for burning
	res = ::SetRAWStructure(&m_vTracks.front(), (int32)m_vTracks.size());
	HandleError(res);

	CSampleBurnDlg dlg(this);
	dlg.DoModal();
}

void CRawWriterDlg::OnBurnWithFoxBurnerEmbeddedDialog()
{
	if(m_vTracks.empty())
	{
		AfxMessageBox(_T("Please, create at least one track."));
		return;
	}
	//set logical structure of disc for burning
	int32 res = ::SetRAWStructure(&m_vTracks.front(), (int32)m_vTracks.size());
	HandleError(res);
	
	// Set options
	SOptions opt;	

	res = ::GetOptions(&opt);
	HandleError(res);
	
	_tcscpy(opt.chVolumeLabel, _T("New"));
	opt.bEjectAfterBurn = m_bEjectAfterBurn;
	opt.bFinalize = m_bFinalize;
	opt.bJolietFileSystem = m_bJoliet;
	opt.bVerifyAfterBurn = m_bVerify;
	
	res = ::SetOptions(opt);
	HandleError(res);
	
	res = ::BurnDialog();
	HandleError(res);
}

BOOL CRawWriterDlg::OnSetAspi(UINT nAspi)
{
	::SetASPI(nAspi - ID_INTERFACE_ASPI);

	int32 nActualAspi = 0;
	::GetASPI(&nActualAspi);

	GetMenu()->CheckMenuItem(ID_INTERFACE_ASPI, nActualAspi == BS_ASPI_INTERNAL ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_INTERFACE_SPTI, nActualAspi == BS_ASPI_WNASPI ? MF_CHECKED : MF_UNCHECKED );
	GetMenu()->CheckMenuItem(ID_INTERFACE_FROGASPI, nActualAspi == BS_ASPI_FROGASPI ? MF_CHECKED : MF_UNCHECKED );

	UpdateDeviceCombo();
	return TRUE;
}

void CRawWriterDlg::OnBurningDevices()
{
	// Set internal flag and update devices list

	m_bBurningDevicesOnly = !m_bBurningDevicesOnly;

	GetMenu()->CheckMenuItem(ID_ASPI_BURNDEVICESONLY, m_bBurningDevicesOnly ? MF_CHECKED : MF_UNCHECKED);

	UpdateDeviceCombo();
}

void CRawWriterDlg::OnDisableImagewriter()
{
	bool bDisable = GetMenu()->GetMenuState(ID_ASPI_DISABLEIMAGEWIRTER, MF_BYCOMMAND) == MF_UNCHECKED;
	// Disable or enable image writer

	::EnableImageDevice(bDisable ? BS_FALSE : BS_TRUE);

	// Update devices list

	UpdateDeviceCombo();

	GetMenu()->CheckMenuItem(ID_ASPI_DISABLEIMAGEWIRTER, bDisable ? MF_CHECKED : MF_UNCHECKED);
}


//--------------------------------------------------
//A new Drive was selected. Set now to SDK.
//--------------------------------------------------
void CRawWriterDlg::OnDrives() 
{
	int index = m_cmbDevice.GetCurSel();

	if (index == m_cmbDevice.GetCount()-1 && m_bMultideviceEnabled)
	{
		// Open multidevice dialog if multidevice is selected

		::MultiDeviceDialog();

		// Multidevice dialog set current device, so we
		// should update device combo

		UpdateDeviceCombo();
	} 
	else if (CB_ERR < index) 
	{
		CString strDevice;
		m_cmbDevice.GetLBText(index, strDevice);

		// Set current device

		int32 res = ::SetBurnDevice(strDevice);
		HandleError(res);
	}
}

void CRawWriterDlg::UpdateDeviceCombo()
{
	m_cmbDevice.ResetContent();
	m_bMultideviceEnabled = false;

	// Get devices list

	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 res = ::GetDevices(chListDevices, &nUsed, m_bBurningDevicesOnly ? BS_TRUE : BS_FALSE);
	HandleError(res);

	// Get current device

	// Get current device
	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	HandleError(res);

	// Add devices to combo box

	for (int i = 0; i < nUsed; i++) 
	{	
		m_cmbDevice.AddString(chListDevices[i]);

		// Set selection on current device

		if (nBurnDevices > 0) {
			if (0 == _tcsncmp(chBurnDevices[0], chListDevices[i], 2)) {
				m_cmbDevice.SetCurSel(i);
			}
		}
	}

	// Append multidevice item if more than one device in list

	if (nUsed > 1) 
	{
		m_bMultideviceEnabled = true;
		m_cmbDevice.AddString(_T("Multiple devices"));
	}

	// Select multidevice item if more than one device is active

	if (nBurnDevices > 1)
		m_cmbDevice.SetCurSel(m_cmbDevice.GetCount()-1);
}


void CRawWriterDlg::HandleError(__int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		__int32 nLength = 2048;

		GetText(errCode, chError, &nLength);

		MessageBox(chError, _T("Error"), MB_OK|MB_ICONERROR);
	}
}

void CRawWriterDlg::OnBurnErasedisk()
{
	__int32 nError = EraseDialog(_T("IsoSDK"));
	HandleError(nError);

	UpdateDeviceCombo();
}

void CRawWriterDlg::OnLvnItemchangedTrackitems(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	CString strTemp;

	strTemp.Format(_T("%d"), m_vTracks[pNMLV->iItem].nNumber);
	edTrackNo.SetWindowText(strTemp);	

	strTemp.Format(_T("%d"), m_vTracks[pNMLV->iItem].nIndex);
	GetDlgItem(IDC_TRACKINDEX)->SetWindowText(strTemp);	

	GetDlgItem(IDC_TRACKMODE)->SetWindowText(reportTrackItems.GetItemText(pNMLV->iItem, 1));

	strTemp.Format(_T("%d"), m_vTracks[pNMLV->iItem].nStartAddress);
	GetDlgItem(IDC_STARTADRESS)->SetWindowText(strTemp);

	strTemp.Format(_T("%d"), m_vTracks[pNMLV->iItem].nLength);
	GetDlgItem(IDC_TRACKLENGTH)->SetWindowText(strTemp);
	
	strTemp.Format(_T("%d"), m_vTracks[pNMLV->iItem].nOffset);
	GetDlgItem(IDC_OFFSET)->SetWindowText(strTemp);

	cbTrackMode.SelectString(0, MaskAndMode::getFormat<CString>(m_vTracks[pNMLV->iItem]));

	int n = m_vTracks[pNMLV->iItem].nDataTypeMask;

	SetMaskListChecks(lstDataMask, m_vTracks[pNMLV->iItem].nDataTypeMask);
	SetMaskListChecks(lstIgnoreMask, m_vTracks[pNMLV->iItem].nIgnoreDataMask);

	*pResult = 0;
}

void CRawWriterDlg::OnDeltaposSpinIndex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	
	if (pNMUpDown->iDelta < 0)
	{
        GetDlgItem(IDC_TRACKINDEX)->SetWindowText(_T("1"));				
	}
	else
	{
        GetDlgItem(IDC_TRACKINDEX)->SetWindowText(_T("0"));		
	}	

	*pResult = 0;
}

void CRawWriterDlg::OnDeltaposSpinTrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	CString strValue;
	int nValue;

	GetDlgItem(IDC_TRACKNUMBER)->GetWindowText(strValue);
	nValue = _ttoi(strValue);
	
	if (pNMUpDown->iDelta < 0)
	{
		nValue++;

		strValue.Format(_T("%d"), nValue);

        GetDlgItem(IDC_TRACKNUMBER)->SetWindowText(strValue);		
		
	}
	else
	{
		nValue--;

		if (nValue > 0)
		{
			strValue.Format(_T("%d"), nValue);
			GetDlgItem(IDC_TRACKNUMBER)->SetWindowText(strValue);
		}			
	}	

	*pResult = 0;
}


void CRawWriterDlg::OnSetEject() 
{
	m_bEjectAfterBurn = !m_bEjectAfterBurn;
	GetMenu()->CheckMenuItem(ID_OPTIONS_EJECTDISC, m_bEjectAfterBurn ? MF_CHECKED : MF_UNCHECKED);
}

void CRawWriterDlg::OnSetVerify()
{
	m_bVerify = !m_bVerify;
	GetMenu()->CheckMenuItem(ID_OPTIONS_VERIFY, m_bVerify ? MF_CHECKED : MF_UNCHECKED);
}

void CRawWriterDlg::OnSetJoliet() 
{
	m_bJoliet = !m_bJoliet;
	GetMenu()->CheckMenuItem(ID_OPTIONS_JOLIETFILESYSTEM, m_bJoliet ? MF_CHECKED : MF_UNCHECKED);    
}

void CRawWriterDlg::OnSetFinalize() 
{
	m_bFinalize = !m_bFinalize;
	GetMenu()->CheckMenuItem(ID_OPTIONS_FINALIZE, m_bFinalize ? MF_CHECKED : MF_UNCHECKED);
}
int32 CRawWriterDlg::UpdateOptions()
{
	// Load options from controls

	SOptions opt;

	int32 res = ::GetOptions(&opt);
	HandleError(res);

	_tcscpy(opt.chVolumeLabel, _T("New"));
	opt.bEjectAfterBurn = m_bEjectAfterBurn;
	opt.bFinalize = m_bFinalize;
	opt.bJolietFileSystem = m_bJoliet;
	opt.bVerifyAfterBurn = m_bVerify;	

	// Set option to FoxBruner

	res = ::SetOptions(opt);
	HandleError(res);
	return res;
}

void CRawWriterDlg::OnBnClickedResettrack()
{
	OnReset();
}

void CRawWriterDlg::OnBnClickedDeletetrack()
{
	int nSelected = reportTrackItems.GetSelectionMark();

	if (nSelected != -1)
	{
		reportTrackItems.DeleteItem(nSelected);

		m_vTracks.erase(m_vTracks.begin() + nSelected);		
	}
}

void CRawWriterDlg::OnSaveLog()
{
	//Please note that the root folder is basing on the caller. If you run from debugger the startup dir is the project file path.
	//If you run the sample from explorer / terminal it is the path of the executable.
	::SaveLogToFile(m_strStartupDir + _T("\\FoxSampleRawW.log"));
}