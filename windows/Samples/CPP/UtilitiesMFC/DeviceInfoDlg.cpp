// DeviceInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UtilitiesMFC.h"
#include "IsoSDKExport.h"
#include "DeviceInfoDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDeviceInfoDlg dialog


CDeviceInfoDlg::CDeviceInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceInfoDlg::IDD, pParent)
{
}



BEGIN_MESSAGE_MAP(CDeviceInfoDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceInfoDlg message handlers

void CDeviceInfoDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
		GetParent()->GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}

void CDeviceInfoDlg::FillInfo()
{
	int32 nError = 0;

	// Get disk type

	SMediumInfo mi;
	::GetMediumInformation(BS_CURRENT_DEVICE, &mi);

	if (_tcscmp(mi.chMediumType, _T("BS_NDEF")) == 0)
		SetDlgItemText(IDC_DISKTYPE, _T("No Medium"));
	else
		SetDlgItemText(IDC_DISKTYPE, mi.chMediumType);

	// Get max. burn speed

	int32 nSpeed = 0;
	nError = ::GetMaxBurnSpeed(BS_CURRENT_DEVICE, &nSpeed);
	HandleError(nError);
	SetDlgItemText(IDC_MAXBURNSPEED, IntToStr(nSpeed));

	// Get max. read speed

	nError = ::GetMaxReadSpeed(BS_CURRENT_DEVICE, &nSpeed);
	HandleError(nError);
	SetDlgItemText(IDC_MAXREADSPEED, IntToStr(nSpeed));

	// Get capabilities

	//Create a handle
	int32 nCapsHandle;
 
	//Set the handle
	nError = GetDeviceCapabilitiesHandle(BS_CURRENT_DEVICE, &nCapsHandle);
	HandleError(nError);

	BS_BOOL bRes = false;
	nError = AnalyseDeviceCapability(nCapsHandle, BS_WRITE_TEST, &bRes);
	HandleError(nError);

	// Get Test write capability

	if (bRes == BS_TRUE)
		SetDlgItemText(IDC_TESTWRITE, _T("Supported"));
	else
		SetDlgItemText(IDC_TESTWRITE, _T("Not Supported"));

	bRes = BS_FALSE;
	nError = AnalyseDeviceCapability(nCapsHandle, BS_UNDERRUN_PROTECTION, &bRes);
	HandleError(nError);

	// Get Underrun protection capability

	if (bRes == BS_TRUE)
		SetDlgItemText(IDC_PROTECTION, _T("Supported"));
	else
		SetDlgItemText(IDC_PROTECTION, _T("Not Supported"));

	nError = ReleaseDeviceCapabilities(nCapsHandle);
	HandleError(nError);
}
