// ImageCreationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IsoSDKExport.h"
#include "UtilitiesMFC.h"
#include "ImageCreationDlg.h"
#include <cmath>
#include ".\imagecreationdlg.h"

// CImageCreationDlg dialog

IMPLEMENT_DYNAMIC(CImageCreationDlg, CDialog)
CImageCreationDlg::CImageCreationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageCreationDlg::IDD, pParent)
	,m_bExecution(FALSE)
{
}

CImageCreationDlg::~CImageCreationDlg()
{
}

void CImageCreationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageCreationDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE_CHECK, OnBtnImageCheck)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE_CREATE, OnBtnImageCreate)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_IMAGE, OnBtnCancelImage)	
	ON_BN_CLICKED(IDC_BUTTON_IMAGE_BROWSE, OnBtnImageBrowse)
	ON_BN_CLICKED(IDC_CHECK_BADSECTORS, UpdateControls)
	ON_BN_CLICKED(IDC_CHECK_READ_CORRECTION, UpdateControls)
	ON_MESSAGE(WM_CURRENT_DEVICE_CHANGE, OnUpdateInfo)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()	
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CImageCreationDlg message handlers

BOOL CImageCreationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_EDIT_HRETRIES)->SetWindowText(_T("20"));
	CheckDlgButton(IDC_CHECK_READ_CORRECTION, TRUE);
	CheckDlgButton(IDC_CHECK_CREATE, TRUE);
	CheckDlgButton(IDC_CHECK_BLANKBAD, TRUE);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->SetRange(0, 300);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN4))->SetRange(0, 300);

	OnBtnImageCheck();

	EnableControls(TRUE);

	m_pProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS_IMAGECREATE);

	UpdateControls();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CImageCreationDlg::OnBtnImageCheck()
{
	UpdateReadDevice();

	int16 nImageFormats;
	int32 nRes = ::GetPossibleImageFormats(&nImageFormats);
	HandleError(nRes);

	CComboBox *pFormatsCombo = (CComboBox *)GetDlgItem(IDC_COMBO_IMAGE_FORMAT);

	pFormatsCombo->ResetContent();

	if (nImageFormats & BS_IMG_ISO)
	{
		pFormatsCombo->AddString(_T("ISO"));
	}

	if (nImageFormats & BS_IMG_BIN)
	{
		pFormatsCombo->AddString(_T("BIN"));
	}

	if (pFormatsCombo->GetCount() == 0)
	{
		pFormatsCombo->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_IMAGE_BROWSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_IMAGE_CREATE)->EnableWindow(FALSE);
	}
	else
	{
		pFormatsCombo->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_IMAGE_BROWSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_IMAGE_CREATE)->EnableWindow(TRUE);

		pFormatsCombo->SetCurSel(0);
	}
}

void CImageCreationDlg::OnBtnImageCreate()
{
	CString strDest;
	GetDlgItemText(IDC_EDIT_DESTINATION, strDest);

	if (strDest == _T(""))
	{
		AfxMessageBox(_T("Destination file is not specified."));
		return;
	}

	CString strBadSectorsLogPath;
	GetDlgItemText(IDC_EDIT_BADSECTORSPATH, strBadSectorsLogPath);

	CString strFormat;
	GetDlgItemText(IDC_COMBO_IMAGE_FORMAT, strFormat);
	
	int16 nFormat = BS_IMG_ISO;
	
	if (strFormat == _T("ISO"))
	{
		nFormat = BS_IMG_ISO;
		
		if (strDest.Right(3).CompareNoCase(_T("iso")))
		{
			strDest += _T(".iso");
		}
	}
	else if (strFormat == _T("BIN"))
	{
		nFormat = BS_IMG_BIN;
		if (strDest.Right(3).CompareNoCase(_T("bin")))
		{
			strDest += _T(".bin");
		}
	}
	else
	{
		return;
	}

	SetDlgItemText(IDC_EDIT_DESTINATION, strDest);
	
	DWORD attr = GetFileAttributes(strDest);
    if(attr != INVALID_FILE_ATTRIBUTES && this->IsDlgButtonChecked(IDC_CHECK_CREATE))	
    {
		if (IDNO == AfxMessageBox(_T("Destination file exists. Do you want to replace it?"), MB_YESNO))
		{
			return;
		}
	}

	SCreateImageParams cCreateImageParams;
	cCreateImageParams.cErrorParams.bErrorCorrection = this->IsDlgButtonChecked(IDC_CHECK_READ_CORRECTION);
	cCreateImageParams.cErrorParams.bBlankBadSectors = this->IsDlgButtonChecked(IDC_CHECK_BLANKBAD);
	_tcscpy(cCreateImageParams.lpszBadSectorsFilePath, (const TCHAR*)strBadSectorsLogPath);
	_tcscpy(cCreateImageParams.lpszImagePath, (const TCHAR*)strDest);
	cCreateImageParams.nImageType = nFormat;
	cCreateImageParams.cErrorParams.nHardwareRetryCount = (uint8)GetDlgItemInt(IDC_EDIT_HRETRIES);
	cCreateImageParams.cErrorParams.nSoftwareRetryCount = (uint8)GetDlgItemInt(IDC_EDIT_SRETRIES);	
	//Set the Multiplier for verfification buffer. Default is one sector. 
	//We set 2 for 2*Sector
	cCreateImageParams.nVerifyBufferSectors = 8;
	cCreateImageParams.bFullCapacity = BS_TRUE;

	int8 dwOperation = 0;

	if (this->IsDlgButtonChecked(IDC_CHECK_CREATE))
	{
		dwOperation = BS_IMGTASK_CREATE;
	}

	if (this->IsDlgButtonChecked(IDC_CHECK_VERIFY))
	{
		dwOperation |= BS_IMGTASK_VERIFY;
	}

	if (!dwOperation)
	{
		AfxMessageBox(_T("Operation is not specified."));
		return;
	}

	if (!UpdateReadDevice())
	{
		return;
	}

	// Start image creation
	int32 res = ::CreateImage(cCreateImageParams, dwOperation);
	HandleError(res);

	if (res == BS_SDK_ERROR_NO)
	{
		EnableControls(FALSE);
		SetDlgItemText(IDC_STATIC_STATE, _T("Job state: Create"));


		int32 nRes = ::SetProcessEventCallback((ProcessEvent) CImageCreationDlg::OnProcessEvent, this);
		HandleError(nRes);

		nRes = ::SetJobDoneEventCallback((JobDoneEvent) CImageCreationDlg::OnJobDone, this);
		HandleError(nRes);

		nRes = ::SetBurnDoneEventCallback((BurnDoneEvent) CImageCreationDlg::OnBurnDone, this);
		HandleError(nRes);

		nRes = ::SetStartVerifyEventCallback((StartVerifyEvent)CImageCreationDlg::OnStartVerifyEvent, this);
		HandleError(nRes);

		nRes = ::SetVerifySectorEventCallback((VerifySectorEvent)CImageCreationDlg::OnVerifySectorEvent, this);
		HandleError(nRes);

		nRes = ::SetVerifyDoneEventCallback((VerifyDoneEvent)CImageCreationDlg::OnVerifyDoneEvent, this);
		HandleError(nRes);
	}
}

void CImageCreationDlg::OnBtnCancelImage()
{
	int32 nRes = ::Abort();
	HandleError(nRes);

	if (nRes)
	{
		EnableControls(TRUE);
	}
}

void CImageCreationDlg::OnBtnImageBrowse()
{
	CString strFormat;

	CComboBox *pFormatsCombo = (CComboBox *)GetDlgItem(IDC_COMBO_IMAGE_FORMAT);

	pFormatsCombo->GetWindowText(strFormat);

	CString strSaveParam;
	
	strSaveParam.Format(_T(" files (*.%s )|*.%s||"), strFormat, strFormat);
		
    CFileDialog cSaveFileDialog(FALSE, strFormat, NULL, 
		OFN_SHAREWARN|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFormat + strSaveParam);

	if (cSaveFileDialog.DoModal() == IDOK)
	{
		CString strSavePath = cSaveFileDialog.GetPathName();

		CEdit *pEditDest = (CEdit *)GetDlgItem(IDC_EDIT_DESTINATION);

		pEditDest->SetWindowText(strSavePath);
	}
}

void CImageCreationDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

void CImageCreationDlg::OnStartVerifyEvent(CImageCreationDlg *pImageCreationDlg)
{
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_STATE, _T("Job state: Verify"));
}

void CImageCreationDlg::OnVerifySectorEvent(double nSector, double tSector, bool nSuccess, CImageCreationDlg *pImageCreationDlg)
{
	CString strSectors;
	strSectors.Format(_T("Verify sectors: %.0f /%.0f"), nSector, tSector);
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_VERIFY_SECTORS, strSectors);
}

void CImageCreationDlg::OnVerifyDoneEvent(int nNumErrors, CImageCreationDlg *pImageCreationDlg)
{
	if (nNumErrors>0)
	{
		CString strMessage;
		strMessage.Format(_T("Verify failed with %i errors"), nNumErrors);
		AfxMessageBox(strMessage);
	}
}

void CImageCreationDlg::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
			   double dCurrentSector, double dImageSize, CImageCreationDlg *pImageCreationDlg)
{
	CProgressCtrl *pProgress = (CProgressCtrl *)pImageCreationDlg->GetDlgItem(IDC_PROGRESS_IMAGECREATE);
	pProgress->SetPos((int)fPercent);

	CString strPercentage;
	strPercentage.Format(_T("Percentage: %d%%"), (int)fPercent);
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_PERCENTAGE, strPercentage);
	
	CString strTotalCurrent, strTotal;
	pImageCreationDlg->GetDlgItemText(IDC_STATIC_TOTAL_SECTORS, strTotalCurrent);	
	strTotal.Format(_T("Total Sectors: %.0f"), dImageSize);

	if (strTotalCurrent != strTotal)
	{
		pImageCreationDlg->SetDlgItemText(IDC_STATIC_TOTAL_SECTORS, strTotal);
	}

	CString strCurrent;
	strCurrent.Format(_T("Current Sector: %.0f"), dCurrentSector);
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_CURRENT_SECTORS, strCurrent);

	CString strErrorCount;	
	strErrorCount.Format(_T("Read Errors: %d"), (int)ceil(fDeviceBuffer * 1000));
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_READ_ERRORS, strErrorCount);
}

void CImageCreationDlg::EnableControls(BOOL bEnable)
{
	GetDlgItem(IDC_BUTTON_CANCEL_IMAGE)->EnableWindow(!bEnable);
	GetDlgItem(IDC_BUTTON_IMAGE_CREATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_IMAGE_CREATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DESTINATION)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_IMAGE_BROWSE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_IMAGE_FORMAT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_IMAGE_CHECK)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_CREATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_VERIFY)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_READ_CORRECTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HRETRIES)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SRETRIES)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BLANKBAD)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BADSECTORS)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_BADSECTORSPATH)->EnableWindow(bEnable);

	m_bExecution = !bEnable;
}

void CImageCreationDlg::OnJobDone(CImageCreationDlg *pImageCreationDlg)
{	
	pImageCreationDlg->EnableControls(TRUE);

	pImageCreationDlg->m_pProgress->SetPos(0);
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_PERCENTAGE, _T("Percentage:"));
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_TOTAL_SECTORS, _T("Total Sectors:"));
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_CURRENT_SECTORS, _T("Current Sector:"));
	pImageCreationDlg->SetDlgItemText(IDC_STATIC_READ_ERRORS, _T("Read Errors:"));

	int32 nRes = ::SetProcessEventCallback(NULL, NULL);
	pImageCreationDlg->HandleError(nRes);

	nRes = ::SetJobDoneEventCallback(NULL, NULL);
	pImageCreationDlg->HandleError(nRes);

	nRes = ::SetBurnDoneEventCallback(NULL, NULL);
	pImageCreationDlg->HandleError(nRes);

	nRes = ::SetStartVerifyEventCallback(NULL, NULL);
	pImageCreationDlg->HandleError(nRes);

	nRes = ::SetVerifySectorEventCallback(NULL, NULL);
	pImageCreationDlg->HandleError(nRes);

	nRes = ::SetVerifyDoneEventCallback(NULL, NULL);
	pImageCreationDlg->HandleError(nRes);
}

void CImageCreationDlg::OnBurnDone(const TCHAR* pcError, CImageCreationDlg *pImageCreationDlg) 
{
	if ((pcError != NULL) && (0 != _tcslen(pcError))) 
	{
		AfxMessageBox(pcError);
	}	
}

LRESULT CImageCreationDlg::OnUpdateInfo(WPARAM,LPARAM)
{
	OnBtnImageCheck();

	SExtendedDeviceInformation sDeviceInfo;

	int32 nRes = ::GetDeviceInformationEx(BS_READ_DEVICE, &sDeviceInfo);
	HandleError(nRes);

	CString strRetryCount;
	strRetryCount.Format(_T("%d"), sDeviceInfo.nReadRetryCount);
	GetDlgItem(IDC_EDIT_HRETRIES)->SetWindowText(strRetryCount);

	return 0;
}

void CImageCreationDlg::UpdateControls()
{
	GetDlgItem(IDC_EDIT_BADSECTORSPATH)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_BADSECTORS));
	GetDlgItem(IDC_EDIT_HRETRIES)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_READ_CORRECTION));
	GetDlgItem(IDC_EDIT_SRETRIES)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_READ_CORRECTION));
}

void CImageCreationDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
		GetParent()->GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}

void CImageCreationDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (m_bExecution)
	{
		return;
	}

	if (bShow)
	{
		OnBtnImageCheck();
	}
}

bool CImageCreationDlg::UpdateReadDevice()
{
	// Get current burn device

	TCHAR	chBurnDevices[26][50];
	int32	nBurnDevices = 0;
	int32 res = ::GetBurnDevices(chBurnDevices, &nBurnDevices);
	HandleError(res);

	if (res != BS_SDK_ERROR_NO)
	{
		HandleError(res);
		return false;
	}

	// Multidevice is not allowed

	if (nBurnDevices > 1)
	{
		HandleError(BS_SDK_ERROR_NOT_ALLOWED);
		return false;
	}

	// Set current read device to current burn device
	res = ::SetReadDevice(chBurnDevices[0]);
	if (res != BS_SDK_ERROR_NO)
	{
		HandleError(res);
		return false;
	}

	return true;
}
