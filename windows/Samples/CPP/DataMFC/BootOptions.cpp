// BootOptions.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DataMFC.h"
#include "BootOptions.h"
#include "DataMFCDlg.h"

#include "IsoSDKExport.h"

// CBootOptions-Dialogfeld

IMPLEMENT_DYNAMIC(CBootOptions, CDialog)

CBootOptions::CBootOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CBootOptions::IDD, pParent)
{
	m_strSectorCount = _T("1");
	m_strLoadSegment = _T("07C0");
	m_strBootImage = _T("");
	m_strDeveloperID = _T("");
}

void CBootOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLATFORM, m_cmbPlatform);
	DDX_Control(pDX, IDC_EMULATION, m_cmbEmulation);
	DDX_Text(pDX, IDC_DEVELOPERID, m_strDeveloperID);
	DDX_Control(pDX, IDC_BOOTABLE, m_btnBoot);
	DDX_Text(pDX, IDC_STARTSECTOR, m_strLoadSegment);
	DDX_Text(pDX, IDC_SECTORCOUNT, m_strSectorCount);
	DDX_Text(pDX, IDC_BOOTIMAGE, m_strBootImage);
}


BEGIN_MESSAGE_MAP(CBootOptions, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_BOOTIMAGE, OnBnClickedSelectImageFile)
	ON_BN_CLICKED(IDC_RESET, OnBnClickedReset)
END_MESSAGE_MAP()


// CBootOptions-Meldungshandler

BOOL CBootOptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	OnBnClickedReset();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CBootOptions::OnBnClickedOk()
{
	UpdateData(TRUE);

	SOptions opt;
	int32 res = ::GetOptions(&opt);
	HandleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		_tcsncpy(opt.chBootImage, m_strBootImage, _MAX_PATH);
		opt.bBootable = m_btnBoot.GetCheck() ? BS_TRUE : BS_FALSE;

		res = ::SetOptions(opt);
		HandleError(res);
	}

	SBootInfoEx info;
	res = ::GetBootInfoEx(&info);
	HandleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		USES_CONVERSION;

		memset(&info, 0, sizeof(SBootInfoEx));

		_tcsncpy(info.DeveloperID, m_strDeveloperID, 24*sizeof(TCHAR));

		info.BootIndicator	= m_btnBoot.GetCheck() ? BS_TRUE : BS_FALSE;
		info.Emulation		= m_cmbEmulation.GetCurSel();
		info.LoadSegment	= _tcstol(m_strLoadSegment, NULL, 16);
		info.PlatformID		= m_cmbPlatform.GetCurSel();
		info.SectorCount	= _tstoi(m_strSectorCount);

		res = ::SetBootInfoEx(info);
		HandleError(res);
	}

	OnOK();
}

void CBootOptions::OnBnClickedSelectImageFile()
{
	//--------------------------------------------------
	//Set and call the API Selectdialog
	//--------------------------------------------------
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = this->m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("Image Files (*.img)\0*.img;*.bin\0");
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		m_strBootImage = szFile;
		UpdateData(FALSE);
	}
}

void CBootOptions::OnBnClickedReset()
{
	SOptions opt;
	int32 res = ::GetOptions(&opt);
	HandleError(res);

	if (BS_SDK_ERROR_NO == res)
		m_strBootImage = opt.chBootImage;

	SBootInfoEx info;
	res = ::GetBootInfoEx(&info);
	HandleError(res);

	if (BS_SDK_ERROR_NO == res)
	{
		m_btnBoot.SetCheck(info.BootIndicator ? TRUE : FALSE);
		m_strDeveloperID	= info.DeveloperID;
		m_cmbEmulation.SetCurSel(info.Emulation);
		m_cmbPlatform.SetCurSel(info.PlatformID);
		m_strSectorCount.Format(_T("%d"), info.SectorCount);
		m_strLoadSegment.Format(_T("%X"), info.LoadSegment);
	}

	UpdateData(FALSE);
}

void CBootOptions::HandleError(__int32 nError)
{
	if (nError != BS_SDK_ERROR_NO)
		GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, nError);
}