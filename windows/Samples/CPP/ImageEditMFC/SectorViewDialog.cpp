// SectorViewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "SectorViewDialog.h"

// KSectorViewDialog dialog

IMPLEMENT_DYNAMIC(KSectorViewDialog, CDialog)

KSectorViewDialog::KSectorViewDialog(CWnd* pParent, int32 nLBA)
	: CDialog(KSectorViewDialog::IDD, pParent)
	, m_unCurrentSector(nLBA)
	, m_bRaw(TRUE)
{
	AfxInitRichEdit();
}

KSectorViewDialog::~KSectorViewDialog()
{
}

void KSectorViewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_RAW, m_bRaw);
	DDX_Text(pDX, IDC_EDIT_SECTOR, m_unCurrentSector);
	DDX_Control(pDX, IDC_RICHEDIT_SECTOR, m_cRichEdit);
}


BEGIN_MESSAGE_MAP(KSectorViewDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnBnClickedButtonPrev)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SECTOR, OnDeltaposSpinSector)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnBnClickedButtonNext)
	ON_EN_CHANGE(IDC_EDIT_SECTOR, OnEnChangeEditSector)
	ON_BN_CLICKED(IDC_CHECK_RAW, OnCheckRaw)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// KSectorViewDialog message handlers

BOOL KSectorViewDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	CFont cFont;
	cFont.CreateFont(
		6,                         // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("courier"));            // lpszFacename

	((CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT_SECTOR))->SetFont(&cFont);

	OnLba();

	UpdateData(FALSE);

	return TRUE;
}

void KSectorViewDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_cRichEdit.m_hWnd != NULL)
	{
		CRect cRect;
		m_cRichEdit.GetWindowRect(&cRect);
		this->ScreenToClient(&cRect);
		cRect.right = cx - 10;
		cRect.bottom = cy - 10;
		m_cRichEdit.SetWindowPos(NULL, 0, 0, cRect.Width(), cRect.Height(), SWP_NOMOVE);
	}
}

void KSectorViewDialog::OnBnClickedButtonPrev()
{
	if (m_unCurrentSector > 0)
	{
		--m_unCurrentSector;
	}

	OnLba();
	UpdateData(FALSE);
}

void KSectorViewDialog::OnDeltaposSpinSector(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if ((int)m_unCurrentSector - pNMUpDown->iDelta >= 0)
	{
		m_unCurrentSector -= pNMUpDown->iDelta;
	}

	OnLba();
	UpdateData(FALSE);
}

void KSectorViewDialog::OnBnClickedButtonNext()
{
	++m_unCurrentSector;

	OnLba();
	UpdateData(FALSE);
}

void KSectorViewDialog::OnLba()
{
	std::vector<KString> stringsLines = ReadSector(m_bRaw, m_unCurrentSector);

	CString strContent;
	for(size_t i = 0; i < stringsLines.size(); ++i)
	{
		strContent += CString((const wchar_t *)stringsLines[i] ) + _T('\n');
	}

	m_cRichEdit.SetWindowText(strContent);
}

std::vector<KString> KSectorViewDialog::ReadSector(BOOL bReadRaw, UINT nLBA)
{
	int32 buff_length = bReadRaw ? 2352 : 2048;
	int8 nFormat = bReadRaw ? BS_IMG_BIN : BS_IMG_ISO;

	byte *buff = new byte[buff_length];
	int32 nRes = ::ReadSectors(BS_READ_DEVICE, nLBA, 1, nFormat, buff, buff_length);

	Sector2Text::SectorLines<Sector2Text::IsPrintableTranslator> vBuffer;
	vBuffer.setData(buff, buff_length);
	delete[] buff;
	return vBuffer.getLines();
}

void KSectorViewDialog::OnEnChangeEditSector()
{
	UpdateData();
	OnLba();
}

void KSectorViewDialog::OnOK()
{
	OnLba();
}

void KSectorViewDialog::OnCheckRaw()
{
	UpdateData(TRUE);
	OnLba();
	UpdateData(FALSE);
}