// DiscCopyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UtilitiesMFC.h"
#include "IsoSDKExport.h"
#include "DiscCopyDlg.h"
#include <cmath>
#include ".\disccopydlg.h"


// CDiscCopyDlg dialog

IMPLEMENT_DYNAMIC(CDiscCopyDlg, CDialog)
CDiscCopyDlg::CDiscCopyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiscCopyDlg::IDD, pParent)
	, m_bExecution(FALSE)
{
}

CDiscCopyDlg::~CDiscCopyDlg()
{
}

void CDiscCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISCCOPY_SOURCEDEVICE, m_cmbSourceDevice);
}


BEGIN_MESSAGE_MAP(CDiscCopyDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_READ_CORRECTION, UpdateControls)
	ON_BN_CLICKED(IDC_DISCCOPY_CANCEL, OnBnClickedDisccopyCancel)
	ON_BN_CLICKED(IDC_DISCCOPY_COPY, OnBnClickedDisccopyCopy)
	ON_MESSAGE(WM_CURRENT_DEVICE_CHANGE, OnUpdateInfo)
	ON_CBN_SELCHANGE(IDC_DISCCOPY_SOURCEDEVICE, OnCbnSelchangeDisccopySourcedevice)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CDiscCopyDlg message handlers

BOOL CDiscCopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateDeviceCombo();
	OnUpdateInfo(0, 0);
	
	CheckDlgButton(IDC_CHECK_READ_CORRECTION, TRUE);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_H))->SetRange(0, 300);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_S))->SetRange(0, 300);

	EnableControls(TRUE);

	m_pProgress = (CProgressCtrl*)GetDlgItem(IDC_DISCCOPY_PROGRESS);

	SetDlgItemText(IDC_STATUS_INFO, _T("..."));

	UpdateControls();
	OnCbnSelchangeDisccopySourcedevice();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDiscCopyDlg::OnDestroy()
{
	CDialog::OnDestroy();	
}


void CDiscCopyDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		GetParent()->GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
	}
}

void CDiscCopyDlg::UpdateControls()
{	
	GetDlgItem(IDC_EDIT_HRETRIES)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_READ_CORRECTION));
	GetDlgItem(IDC_EDIT_SRETRIES)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_READ_CORRECTION));
}

void CDiscCopyDlg::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
			   double dBytesWritten, double dImageSize, CDiscCopyDlg *pDiscCopyDlg)
{
	CProgressCtrl *pProgress = (CProgressCtrl *)pDiscCopyDlg->GetDlgItem(IDC_DISCCOPY_PROGRESS);
	pProgress->SetPos((int)fPercent);

	CString strPercentage;
	strPercentage.Format(_T("Percentage: %d%%"), (int)fPercent);
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_PERCENTAGE, strPercentage);
	
	CString strTotalCurrent, strTotal;
	pDiscCopyDlg->GetDlgItemText(IDC_STATIC_TOTAL_SECTORS, strTotalCurrent);	
	strTotal.Format(_T("Total Bytes: %.0f"), dImageSize);

	if (strTotalCurrent != strTotal)
	{
		pDiscCopyDlg->SetDlgItemText(IDC_STATIC_TOTAL_SECTORS, strTotal);
	}

	CString strCurrent;
	strCurrent.Format(_T("Bytes Written: %.0f"), dBytesWritten);
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_CURRENT_SECTORS, strCurrent);	
}

void CDiscCopyDlg::OnJobDone(CDiscCopyDlg *pDiscCopyDlg)
{
	pDiscCopyDlg->EnableControls(TRUE);
	
	pDiscCopyDlg->m_pProgress->SetPos(0);
	
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_PERCENTAGE, _T("Percentage:"));
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_TOTAL_SECTORS, _T("Total Bytes:"));
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_CURRENT_SECTORS, _T("Bytes Written:"));

	int32 nRes = ::SetProcessEventCallback(NULL, NULL);
	pDiscCopyDlg->HandleError(nRes);

	nRes = ::SetJobDoneEventCallback(NULL, NULL);
	pDiscCopyDlg->HandleError(nRes);

	nRes = ::SetBurnDoneEventCallback(NULL, NULL);
	pDiscCopyDlg->HandleError(nRes);

	nRes = ::SetStartVerifyEventCallback(NULL, NULL);
	pDiscCopyDlg->HandleError(nRes);

	nRes = ::SetVerifySectorEventCallback(NULL, NULL);
	pDiscCopyDlg->HandleError(nRes);

	nRes = ::SetVerifyDoneEventCallback(NULL, NULL);
	pDiscCopyDlg->HandleError(nRes);
}

void CDiscCopyDlg::OnBurnDone(const TCHAR* pcError, CDiscCopyDlg *pDiscCopyDlg)
{
	pDiscCopyDlg->SetDlgItemText(IDC_STATUS_INFO, _T("Copy Done"));

	if ((pcError != NULL) && (0 != _tcslen(pcError))) 
	{
		AfxMessageBox(pcError);
	}
}

void CDiscCopyDlg::UpdateDeviceCombo()
{
	m_cmbSourceDevice.ResetContent();

	// Get devices list

	TCHAR chListDevices[26][50];
	int32 nUsed = 0;
	int32 nRes = ::GetDevices(chListDevices, &nUsed, BS_FALSE);
	HandleError(nRes);

	// Get current read device

	TCHAR pchDevice[50];
	int32 nLength = sizeof(pchDevice) / sizeof(TCHAR);
	nRes = ::GetReadDevice(pchDevice, &nLength);
	HandleError(nRes);

	// Add devices to combo box

	for (int i = 0; i < nUsed; i++)
	{
		m_cmbSourceDevice.AddString(chListDevices[i]);

		// Set selection on current device
		if (0 == _tcsncmp(pchDevice, chListDevices[i], 2)) 
		{
			m_cmbSourceDevice.SetCurSel(i);
		}
	}
}
void CDiscCopyDlg::OnBnClickedDisccopyCancel()
{
	int32 nRes = ::Abort();
	HandleError(nRes);
}

void CDiscCopyDlg::OnBnClickedDisccopyCopy()
{


	SDiskCopyOptions cDiskCopyOptions;
	cDiskCopyOptions.bVerifyAfterBurn = this->IsDlgButtonChecked(IDC_CHECK_VERIFYAFTER);
	cDiskCopyOptions.bEjectAfterBurn = this->IsDlgButtonChecked(IDC_CHECK_EJECTAFTER);

	CComboBox *pModeCombo = (CComboBox *)GetDlgItem(IDC_DISCCOPY_READMODE);	
	CString strMode;
	pModeCombo->GetWindowText(strMode);

	if (strMode == _T("ISO"))
	{
		cDiskCopyOptions.nReadMode = BS_RM_USERDATA;
	}
	else if (strMode == _T("RAW"))
	{
		cDiskCopyOptions.nReadMode = BS_RM_RAW;
	}
	else if (strMode == _T("RAW+SubCh"))
	{
		cDiskCopyOptions.nReadMode = BS_RM_RAW_SUBCHANNEL;
	}else
	{
		AfxMessageBox(_T("Please, specify read mode."), MB_OK, MB_ICONERROR);
		return;
	}

	CComboBox *pWrMethodCombo = (CComboBox *)GetDlgItem(IDC_DISCCOPY_WRITEMETHOD);	
	CString strWrMethod;
	pWrMethodCombo->GetWindowText(strWrMethod);
	
	if (strWrMethod == _T("DAO"))
	{
		cDiskCopyOptions.nWriteMethod = BS_WM_DAO;
	}
	else if (strWrMethod == _T("DAO96"))
	{
		cDiskCopyOptions.nWriteMethod = BS_WM_DAO96;
	}
	else
	{
		AfxMessageBox(_T("Please, specify write method."), MB_OK, MB_ICONERROR);
		return;
	}

	//Set the Multiplier for verfification buffer. Default is one sector. 
	//We set 2 for 2*Sector
	cDiskCopyOptions.nVerifyBufferSectors = 8;
	cDiskCopyOptions.bFullCapacity = BS_TRUE;
	
	SReadErrorCorrectionParams cCorrectionParams;
	cCorrectionParams.bErrorCorrection = this->IsDlgButtonChecked(IDC_CHECK_READ_CORRECTION);
	cCorrectionParams.nHardwareRetryCount = (uint8)GetDlgItemInt(IDC_EDIT_HRETRIES);
	cCorrectionParams.nSoftwareRetryCount = (uint8)GetDlgItemInt(IDC_EDIT_SRETRIES);

	cDiskCopyOptions.cErrorParams = cCorrectionParams;
	SOptions opt;
	::GetOptions(&opt);
	opt.bAutoErase = this->IsDlgButtonChecked(IDC_CHECK_AUTOERASE);
	::SetOptions(opt);

	CString strSourceDevice;
	m_cmbSourceDevice.GetWindowText(strSourceDevice);

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 nRes = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	HandleError(nRes);

	if (0 == _tcsncmp(chBurnDevices[0], strSourceDevice, 2))
	{
		AfxMessageBox(_T("Source and Destination devices cannot be the same."), MB_OK, MB_ICONERROR);
		return;
	}

	nRes = ::SetReadDevice(strSourceDevice);
	HandleError(nRes);

	if (nRes == BS_SDK_ERROR_NO)
	{
		nRes = ::CopyDisk(cDiskCopyOptions);
		HandleError(nRes);

		if (nRes == BS_SDK_ERROR_NO) {

			SetDlgItemText(IDC_STATIC_STATUS, _T("Job state: Copy"));

			nRes = ::SetProcessEventCallback((ProcessEvent)CDiscCopyDlg::OnProcessEvent, this);
			HandleError(nRes);

			nRes = ::SetJobDoneEventCallback((JobDoneEvent)CDiscCopyDlg::OnJobDone, this);
			HandleError(nRes);

			nRes = ::SetBurnDoneEventCallback((BurnDoneEvent)CDiscCopyDlg::OnBurnDone, this);
			HandleError(nRes);

			nRes = ::SetStartVerifyEventCallback((StartVerifyEvent)CDiscCopyDlg::OnStartVerifyEvent, this);
			HandleError(nRes);

			nRes = ::SetVerifySectorEventCallback((VerifySectorEvent)CDiscCopyDlg::OnVerifySectorEvent, this);
			HandleError(nRes);

			nRes = ::SetVerifyDoneEventCallback((VerifyDoneEvent)CDiscCopyDlg::OnVerifyDoneEvent, this);
			HandleError(nRes);

			nRes = ::SetInfoTextEventCallback((InfoTextEvent)CDiscCopyDlg::OnInfoTextEvent, BS_IL_INFO, this);
			HandleError(nRes);
		}

	}

	if (nRes == BS_SDK_ERROR_NO)
	{
		EnableControls(FALSE);
	}
}

LRESULT CDiscCopyDlg::OnUpdateInfo(WPARAM, LPARAM)
{
	CComboBox *pWrMethodCombo = (CComboBox *)GetDlgItem(IDC_DISCCOPY_WRITEMETHOD);
	pWrMethodCombo->ResetContent();
	
	pWrMethodCombo->AddString(_T("DAO"));

	SMediumInfo cMediumInfo;
	int32 nRes = ::GetMediumInformation(BS_CURRENT_DEVICE, &cMediumInfo);
	HandleError(nRes);

	if (cMediumInfo.wMediumTypeCode == BS_CD_ROM ||
		cMediumInfo.wMediumTypeCode == BS_CD_R ||
		cMediumInfo.wMediumTypeCode == BS_CD_RW)
	{
		pWrMethodCombo->AddString(_T("DAO96"));
	}
	
	pWrMethodCombo->SetCurSel(0);

	return 0;
}

void CDiscCopyDlg::OnCbnSelchangeDisccopySourcedevice()
{
	CString strSourceDevice;
	m_cmbSourceDevice.GetWindowText(strSourceDevice);

	int32 nRes = ::SetReadDevice(strSourceDevice);
	HandleError(nRes);

	CComboBox *pModeCombo = (CComboBox *)GetDlgItem(IDC_DISCCOPY_READMODE);
	pModeCombo->ResetContent();

	pModeCombo->AddString(_T("ISO"));

	SMediumInfo cMediumInfo;
	nRes = ::GetMediumInformation(BS_READ_DEVICE, &cMediumInfo);

	if (nRes == BS_SCSI_ERROR_DISK_31)
	{
		cMediumInfo.wMediumTypeCode = BS_CD_ROM;
		nRes = BS_SDK_ERROR_NO;
	}

	HandleError(nRes);

	if (cMediumInfo.wMediumTypeCode == BS_CD_ROM ||
		cMediumInfo.wMediumTypeCode == BS_CD_R ||
		cMediumInfo.wMediumTypeCode == BS_CD_RW)
	{
		pModeCombo->AddString(_T("RAW"));
		pModeCombo->AddString(_T("RAW+SubCh"));		
	}
	
	pModeCombo->SetCurSel(0);

	SExtendedDeviceInformation sDeviceInfo;
	nRes = ::GetDeviceInformationEx(BS_READ_DEVICE, &sDeviceInfo);
	HandleError(nRes);

	CString strRetryCount;
	strRetryCount.Format(_T("%d"), sDeviceInfo.nReadRetryCount);
	GetDlgItem(IDC_EDIT_HRETRIES)->SetWindowText(strRetryCount);
}


void CDiscCopyDlg::EnableControls(BOOL bEnable)
{
	GetDlgItem(IDC_DISCCOPY_CANCEL)->EnableWindow(!bEnable);
	GetDlgItem(IDC_DISCCOPY_WRITEMETHOD)->EnableWindow(bEnable);
	GetDlgItem(IDC_DISCCOPY_READMODE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_VERIFYAFTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_EJECTAFTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_DISCCOPY_COPY)->EnableWindow(bEnable);
	GetDlgItem(IDC_DISCCOPY_SOURCEDEVICE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_READ_CORRECTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HRETRIES)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SRETRIES)->EnableWindow(bEnable);	
	GetDlgItem(IDC_CHECK_AUTOERASE)->EnableWindow(bEnable);

	m_bExecution = !bEnable;
}

void CDiscCopyDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (m_bExecution)
		return;

	if (bShow)
		OnUpdateInfo(0, 0);
}


void CDiscCopyDlg::OnStartVerifyEvent(CDiscCopyDlg *pDiscCopyDlg)
{
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_STATUS, _T("Job state: Verify"));
	pDiscCopyDlg->SetDlgItemText(IDC_STATUS_INFO, _T("Start verify process"));
}

void CDiscCopyDlg::OnVerifySectorEvent(double nSector, double tSector, bool nSuccess, CDiscCopyDlg *pDiscCopyDlg)
{
	CString strSectors;
	strSectors.Format(_T("Verify sectors: %.0f /%.0f"), nSector, tSector);
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_VERIFYSTATUS, strSectors);
}

void CDiscCopyDlg::OnVerifyDoneEvent(int nNumErrors, CDiscCopyDlg *pDiscCopyDlg)
{
	pDiscCopyDlg->SetDlgItemText(IDC_STATIC_STATUS, _T("Job state: Done"));
	pDiscCopyDlg->SetDlgItemText(IDC_STATUS_INFO, _T("Verify Done"));
	
	if (nNumErrors>0)
	{
		CString strMessage;
		strMessage.Format(_T("Verify failed with %i errors"), nNumErrors);
		AfxMessageBox(strMessage);
	}
}

void CDiscCopyDlg::OnInfoTextEvent(const TCHAR* pcInfoText, int32 nLevel, CDiscCopyDlg *pDiscCopyDlg)
{
	pDiscCopyDlg->SetDlgItemText(IDC_STATUS_INFO, pcInfoText);
}