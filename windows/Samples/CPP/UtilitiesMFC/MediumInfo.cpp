// MediumInfo.cpp : implementation file
//

#include "stdafx.h"
#include "UtilitiesMFC.h"
#include "IsoSDKExport.h"
#include "MediumInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CMediumInfo dialog

CMediumInfoDlg::CMediumInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMediumInfoDlg::IDD, pParent)
{
}

void CMediumInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SESSIONS, m_ctrlSessions);
}

BEGIN_MESSAGE_MAP(CMediumInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_TERMINATE, OnBtnTerminate)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_EJECT, OnBtnEject)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMediumInfo message handlers

BOOL CMediumInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CMediumInfoDlg::HandleError(__int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
		GetParent()->GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}

LRESULT CMediumInfoDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DEVICECHANGE) {

		if (wParam == 0x8000 || wParam == 0x8004) {

			if (wParam == 0x8000) {

				Sleep(3000);
			}

			FillInfo();

		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CMediumInfoDlg::FillInfo()
{
	// Clear all controls

	GetDlgItem(IDC_BTN_TERMINATE)->EnableWindow(FALSE);

	m_ctrlSessions.DeleteAllItems();

	SetDlgItemText(IDC_MEDIUM, _T("..."));
	SetDlgItemText(IDC_STATUS, _T("..."));
	SetDlgItemText(IDC_LASTSESSION, _T("..."));
	SetDlgItemText(IDC_SIZE1, _T("..."));
	SetDlgItemText(IDC_USEDSPACE, _T("..."));
	SetDlgItemText(IDC_FREESPACE, _T("..."));
	SetDlgItemText(IDC_CATALOGNUMBER, _T("..."));
	SetDlgItemText(IDC_VENDORID, _T("..."));
	SetDlgItemText(IDC_NUMSESSIONS, _T("..."));
	SetDlgItemText(IDC_NUMTRACKS, _T("..."));
	SetDlgItemText(IDC_MAXWRITESPEED, _T("..."));

	// Get medium information

	SMediumInfo mi;
	int32 nError = ::GetMediumInformation(BS_CURRENT_DEVICE, &mi);

	if (_tcscmp(mi.chMediumType, _T("BS_NDEF")) == 0)
	{
		SetDlgItemText(IDC_MEDIUM, _T("No Medium"));
		return;
	}

	SetDlgItemText(IDC_MEDIUM, mi.chMediumType);
	SetDlgItemText(IDC_CATALOGNUMBER, mi.chUPCEANCode);
	SetDlgItemText(IDC_VENDORID, mi.chVendorID);
	SetDlgItemText(IDC_NUMSESSIONS, IntToStr(mi.nLastSession));
	SetDlgItemText(IDC_NUMTRACKS, IntToStr(mi.nLastTrack));

	const double MEGABYTE = 1024.0 * 1024.0;

	switch (mi.nMediumStatus) {

		case BS_MS_EMPTY_DISK:
			SetDlgItemText(IDC_USEDSPACE, RealToStr(mi.dMediumUsedSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_FREESPACE, RealToStr(mi.dMediumFreeSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_SIZE1, RealToStr(mi.dMediumSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_STATUS, _T("Empty Disk"));
			break;

		case BS_MS_INCOMPLETE_DISK:
			SetDlgItemText(IDC_USEDSPACE, RealToStr(mi.dMediumUsedSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_FREESPACE, RealToStr(mi.dMediumFreeSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_SIZE1, RealToStr(mi.dMediumSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_STATUS, _T("Incomplete Disk"));
			break;

		case BS_MS_COMPLETE_DISK:
			SetDlgItemText(IDC_USEDSPACE, RealToStr(mi.dMediumUsedSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_SIZE1, RealToStr(mi.dMediumSize / MEGABYTE) + _T(" MB"));
			SetDlgItemText(IDC_STATUS, _T("Complete Disk"));
			break;
	}

	switch (mi.nLastSessionStatus)
	{
	case BS_LS_EMPTY_SESSION:
		SetDlgItemText(IDC_LASTSESSION, _T("Empty Session"));
		break;

	case BS_LS_INCOMPLETE_SESSION:
		SetDlgItemText(IDC_LASTSESSION, _T("Incomplete session"));
		break;

	case BS_LS_DAMAGED_SESSION:
		SetDlgItemText(IDC_LASTSESSION, _T("Damaged session"));
		break;

	case BS_LS_COMPLETE_SESSION:
		SetDlgItemText(IDC_LASTSESSION, _T("Complete session"));
		break;
	}

	CString strMaxWriteSpeed = _T("Unknown");
	if (mi.fMaxWriteSpeed > 0)
		strMaxWriteSpeed.Format(_T("%.1fx"), mi.fMaxWriteSpeed);
	SetDlgItemText(IDC_MAXWRITESPEED, strMaxWriteSpeed);

	CString strExtDiskType;
	switch(mi.nExtendedMediumType)
	{
	case BS_EMT_CD_ROM:		strExtDiskType = _T("CD-ROM"); break;
	case BS_EMT_CD_ROM_XA:	strExtDiskType = _T("CD-ROM XA"); break;
	case BS_EMT_CD_AUDIO:   strExtDiskType = _T("Audio CD"); break;
	case BS_EMT_CD_MIXED_MODE: strExtDiskType = _T("Mixed Mode CD"); break;
	case BS_EMT_CD_ENHANCED: strExtDiskType = _T("Enhanced CD"); break;
	case BS_EMT_CD_MULTISESSION: strExtDiskType = _T("Multisession CD"); break;
	case BS_EMT_DVD: strExtDiskType = _T("DVD"); break;
	case BS_EMT_BD: strExtDiskType = _T("BD"); break;
	case BS_EMT_HDDVD: strExtDiskType = _T("HDDVD"); break;
	default: break;
	}

	if (mi.nFirstSession > 0 && mi.nLastSession > 0)
	{
		HTREEITEM hDiskItem = m_ctrlSessions.InsertItem(strExtDiskType);

		for (int32 i = mi.nFirstSession; i <= mi.nLastSession; i++)
		{
			SSessionInfo si;
			nError = ::GetSessionInformation(BS_CURRENT_DEVICE, i, &si);
			HandleError(nError);

			double dSessionSizeInMB = (si.dSessionSize * 2048.0)/MEGABYTE;

			CString strSession = _T("Session ") + IntToStr(i) + _T(" (") + RealToStr(dSessionSizeInMB) + _T(" MB)");
			HTREEITEM hSessionItem = m_ctrlSessions.InsertItem(strSession, hDiskItem);

			for(int32 j = si.nFirstTrack; j <= si.nLastTrack; ++j)
			{
				STrackInfo ti;
				nError = ::GetTrackInformation(BS_CURRENT_DEVICE, j, &ti);
				HandleError(nError);

				CString strTrackFormat;
				switch(ti.nFormat)
				{
				case BS_TF_AUDIO: strTrackFormat = _T("Audio"); break;
				case BS_TF_DATA_MODE1: strTrackFormat = _T("mode 1"); break;
				case BS_TF_DATA_MODE2: strTrackFormat = _T("mode 2"); break;
				}

				CString strFileSys;

				if (ti.nFormat != BS_TF_AUDIO)
				{
					if (ti.nFileSystem & BS_FS_ISO9660)
					{
						strFileSys += _T("ISO 9660");
						if (ti.nFileSystem & BS_FS_JOLIET)
							strFileSys += _T("/Joliet");
					}

					if (ti.nFileSystem & BS_FS_UDF)
					{
						if (!strFileSys.IsEmpty())
							strFileSys += _T("/");
						strFileSys += _T("UDF");
					}

					if (ti.nFileSystem & BS_FS_BOOTABLE)
						strFileSys += _T("/bootable");
				}

				CString strTrack = _T("Track ") + IntToStr(j) + _T("  ") + IntToStr(ti.nStartLBA) +
					_T("  (") + RealToStr((ti.nSize*2048.0)/MEGABYTE) + _T("MB) ") + strFileSys + _T(" ") + strTrackFormat;
				m_ctrlSessions.InsertItem(strTrack, hSessionItem);
			}

			m_ctrlSessions.Expand(hSessionItem, TVE_EXPAND);
		}

		m_ctrlSessions.Expand(hDiskItem, TVE_EXPAND);
	}
}

void CMediumInfoDlg::OnBtnTerminate()
{
	int32 nError = ::CloseSession(BS_CURRENT_DEVICE);
	HandleError(nError);
}

void CMediumInfoDlg::OnBtnRefresh()
{
	FillInfo();
}

void CMediumInfoDlg::OnBtnEject()
{
	int32 nError = ::EjectDevice(BS_CURRENT_DEVICE);
	HandleError(nError);
}
