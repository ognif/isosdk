// DeviceInfoDlgEx.cpp : implementation file
//

#include "stdafx.h"
#include "UtilitiesMFC.h"
#include "IsoSDKExport.h"
#include "DeviceInfoEx.h"

/////////////////////////////////////////////////////////////////////////////
// CDeviceInfoExDlg dialog


CDeviceInfoExDlg::CDeviceInfoExDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDeviceInfoExDlg::IDD, pParent)
{
}

BEGIN_MESSAGE_MAP(CDeviceInfoExDlg, CDialog)
END_MESSAGE_MAP()

void CDeviceInfoExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROPERTIESEX, m_lstParams);
}

BOOL CDeviceInfoExDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstParams.InsertColumn(0, _T("Parameter"), LVCFMT_LEFT, 200);
	m_lstParams.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 200);

	m_lstParams.InsertItem(0, _T("Full name of device"));
	m_lstParams.InsertItem(1, _T("Firmware revision"));
	m_lstParams.InsertItem(2, _T("Firmware creation date"));
	m_lstParams.InsertItem(3, _T("Region code set"));
	m_lstParams.InsertItem(4, _T("Region code changes left"));
	m_lstParams.InsertItem(5, _T("Region code vendor resets left"));
	m_lstParams.InsertItem(6, _T("Loader type"));
	m_lstParams.InsertItem(7, _T("Connection interface"));
	m_lstParams.InsertItem(8, _T("Drive interface"));
	m_lstParams.InsertItem(9, _T("Number of volume levels"));
	m_lstParams.InsertItem(10, _T("Buffer size"));
	m_lstParams.InsertItem(11, _T("Serial number"));
	m_lstParams.InsertItem(12, _T("Read retry count"));
	m_lstParams.InsertItem(13, _T("IDE transfer mode"));

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDeviceInfoDlg message handlers

void CDeviceInfoExDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
		GetParent()->GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}

void CDeviceInfoExDlg::FillInfo()
{
	SExtendedDeviceInformation	infoEx;
	if (::GetDeviceInformationEx(BS_CURRENT_DEVICE, &infoEx) == BS_SDK_ERROR_NO)
	{
		m_lstParams.SetItemText(0, 1, infoEx.lpszName);
		m_lstParams.SetItemText(1, 1, infoEx.lpszRevision);

		CString strFirmwareCreationDate = _T("Unknown");
		if (infoEx.FirmwareCreationDate != 0)
			strFirmwareCreationDate = CTime(infoEx.FirmwareCreationDate).Format(_T("%c"));
		m_lstParams.SetItemText(2, 1, strFirmwareCreationDate);

		m_lstParams.SetItemText(3, 1, IntToStr(infoEx.nRegionCode));
		m_lstParams.SetItemText(4, 1, IntToStr(infoEx.nRegionCodeChangesLeft));
		m_lstParams.SetItemText(5, 1, IntToStr(infoEx.nRegionCodeVendorResetsLeft));
		m_lstParams.SetItemText(6, 1, infoEx.lpszLoaderType);
		m_lstParams.SetItemText(7, 1, infoEx.lpszConnectionInterface);
		m_lstParams.SetItemText(8, 1, infoEx.lpszPhysicalInterface);
		m_lstParams.SetItemText(9, 1, IntToStr(infoEx.nNumberOfVolumeLevels));
		m_lstParams.SetItemText(10, 1, IntToStr(infoEx.nBufferSize));
		m_lstParams.SetItemText(11, 1, infoEx.lpszSerialNumber);
		m_lstParams.SetItemText(12, 1, IntToStr(infoEx.nReadRetryCount));

		TCHAR *pszIdeTransferMode = _T("Not applicable");
		switch (infoEx.nIdeTransferMode)
		{
		case BS_TM_UNKNOWN:
			pszIdeTransferMode = _T("Unknown");
			break;
		case BS_TM_PIO:
			pszIdeTransferMode = _T("PIO");
			break;
		case BS_TM_DMA:
			pszIdeTransferMode = _T("DMA");
			break;
		}
		m_lstParams.SetItemText(13, 1, pszIdeTransferMode);
	}
}
