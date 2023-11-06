// ExtInfos.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DataMFC.h"
#include "ExtInfos.h"
#include "DataMFCDlg.h"

#include "IsoSDKExport.h"
#include <strsafe.h>

IMPLEMENT_DYNAMIC(CExtInfos, CDialog)

CExtInfos::CExtInfos(CWnd* pParent /*=NULL*/)
	: CDialog(CExtInfos::IDD, pParent)
{
}

CExtInfos::~CExtInfos()
{
}

void CExtInfos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SYSTEM_IDENT, m_strSystemIdent);
	DDX_Text(pDX, IDC_VOLUMESET, m_strVolumeSet);
	DDX_Text(pDX, IDC_PUBLISHER, m_strPublisher);
	DDX_Text(pDX, IDC_DATAPRE, m_strDataPreparer);
	DDX_Text(pDX, IDC_APPLICATION, m_strApplication);
	DDX_Text(pDX, IDC_COPYRIGHT, m_strCopyright);
	DDX_Text(pDX, IDC_ABSTRACT, m_strAbstact);
	DDX_Text(pDX, IDC_BIBLIO, m_strBiblio);
	DDX_Check(pDX, IDC_ADD_VERSION_NUMBERS, m_bAddFileSuffix);
	DDX_Check(pDX, IDC_USECREATION, m_bUseCreationDateTime);
	DDX_Check(pDX, IDC_USEMODIFICATION, m_bUseModificationDateTime);
	DDX_Check(pDX, IDC_USEEXPIRATION, m_bUseExpirationDateTime);
	DDX_Check(pDX, IDC_USEEFFECTIVE, m_bUseEffectiveDateTime);
	DDX_DateTimeCtrl(pDX, IDC_CREATIONTIME, m_cCreationDateTime);
	DDX_DateTimeCtrl(pDX, IDC_MODIFICATIONTIME, m_cModificationDateTime);
	DDX_DateTimeCtrl(pDX, IDC_EXPIRATIONTIME, m_cExpirationDateTime);
	DDX_DateTimeCtrl(pDX, IDC_EFFECTIVETIME, m_cEffectiveDateTime);

	DDV_MaxChars(pDX, m_strSystemIdent, 16);
	DDV_MaxChars(pDX, m_strVolumeSet, 64);
	DDV_MaxChars(pDX, m_strPublisher, 64);
	DDV_MaxChars(pDX, m_strDataPreparer, 64);
	DDV_MaxChars(pDX, m_strApplication, 64);
	DDV_MaxChars(pDX, m_strCopyright, 19);
	DDV_MaxChars(pDX, m_strAbstact, 19);
	DDV_MaxChars(pDX, m_strBiblio, 19);
}


BEGIN_MESSAGE_MAP(CExtInfos, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RESET, OnBnClickedReset)
END_MESSAGE_MAP()


// CExtInfos-Meldungshandler

SFileDateTime CTimeToSFileDateTime(const CTime& time)
{
	SFileDateTime res;
	res.nYear = time.GetYear() - 1900;
	res.nMonth = time.GetMonth();
	res.nDay = time.GetDay();
	res.nHour = time.GetHour();
	res.nMinute = time.GetMinute();
	res.nSecond = time.GetSecond();
	return res;
}

void CExtInfos::OnBnClickedOk()
{
	USES_CONVERSION;

	SISOInfoEx info;
	memset(&info, 0, sizeof(info));

	UpdateData(TRUE);

	_tcsncpy(info.ISOSystemIdentifier, m_strSystemIdent, 31);
	_tcsncpy(info.ISOSetIdentifier, m_strVolumeSet, 128);
	_tcsncpy(info.ISOPublisherIdentifier, m_strPublisher, 128);
	_tcsncpy(info.ISODataPreparerIdentifier, m_strDataPreparer, 128);
	_tcsncpy(info.ISOApplicationIdentifier, m_strApplication, 128);
	_tcsncpy(info.ISOCopyrightFileIdentifier, m_strCopyright, 36);
	_tcsncpy(info.ISOAbstractFileIdentifier, m_strAbstact, 36);
	_tcsncpy(info.ISOBiblioIdentifier, m_strBiblio, 36);

	info.ISOAddSuffix = m_bAddFileSuffix ? BS_TRUE : BS_FALSE;
	info.ISOUseCreationDateTime = m_bUseCreationDateTime ? BS_TRUE : BS_FALSE;
	info.ISOUseModificationDateTime = m_bUseModificationDateTime ? BS_TRUE : BS_FALSE;
	info.ISOUseExpirationDateTime = m_bUseExpirationDateTime ? BS_TRUE : BS_FALSE;
	info.ISOUseEffectiveDateTime = m_bUseEffectiveDateTime ? BS_TRUE : BS_FALSE;

	info.ISOCreationDateTime = CTimeToSFileDateTime(m_cCreationDateTime);
	info.ISOModificationDateTime = CTimeToSFileDateTime(m_cModificationDateTime);
	info.ISOExpirationDateTime = CTimeToSFileDateTime(m_cExpirationDateTime);
	info.ISOEffectiveDateTime = CTimeToSFileDateTime(m_cEffectiveDateTime);

	int32 res = ::SetISOInfoEx(info);
	HandleError(res);

	OnOK();
}

BOOL CExtInfos::OnInitDialog()
{
	CDialog::OnInitDialog();

	OnBnClickedReset();

	const TCHAR* lpszFormat = _T("dd MMMM yyyy HH:mm:ss");

	((CDateTimeCtrl*)GetDlgItem(IDC_CREATIONTIME))->SetFormat(lpszFormat);
	((CDateTimeCtrl*)GetDlgItem(IDC_MODIFICATIONTIME))->SetFormat(lpszFormat);
	((CDateTimeCtrl*)GetDlgItem(IDC_EXPIRATIONTIME))->SetFormat(lpszFormat);
	((CDateTimeCtrl*)GetDlgItem(IDC_EFFECTIVETIME))->SetFormat(lpszFormat);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CExtInfos::OnBnClickedCancel()
{
	OnCancel();
}

CTime SFileTimeToCTime(const SFileDateTime& time)
{
	return CTime(time.nYear + 1900, time.nMonth, time.nDay, time.nHour, time.nMinute, time.nSecond);
}

void CExtInfos::OnBnClickedReset()
{
	SISOInfoEx info;

	int32 res = ::GetISOInfoEx(&info);
	HandleError(res);

	m_strSystemIdent = info.ISOSystemIdentifier;
	m_strVolumeSet = info.ISOSetIdentifier;
	m_strPublisher = info.ISOPublisherIdentifier;
	m_strDataPreparer = info.ISODataPreparerIdentifier;
	m_strApplication = info.ISOApplicationIdentifier;
	m_strCopyright = info.ISOCopyrightFileIdentifier;
	m_strAbstact = info.ISOAbstractFileIdentifier;
	m_strBiblio = info.ISOBiblioIdentifier;

	m_bAddFileSuffix = info.ISOAddSuffix == BS_FALSE ? FALSE : TRUE;

	m_bUseCreationDateTime = info.ISOUseCreationDateTime == BS_FALSE ? FALSE : TRUE;
	m_bUseModificationDateTime = info.ISOUseModificationDateTime == BS_FALSE ? FALSE : TRUE;
	m_bUseExpirationDateTime = info.ISOUseExpirationDateTime == BS_FALSE ? FALSE : TRUE;
	m_bUseEffectiveDateTime = info.ISOUseEffectiveDateTime == BS_FALSE ? FALSE : TRUE;

	m_cCreationDateTime = SFileTimeToCTime(info.ISOCreationDateTime);
	m_cModificationDateTime = SFileTimeToCTime(info.ISOModificationDateTime);
	m_cExpirationDateTime = SFileTimeToCTime(info.ISOExpirationDateTime);
	m_cEffectiveDateTime = SFileTimeToCTime(info.ISOEffectiveDateTime);

	UpdateData(FALSE);
}

void CExtInfos::HandleError(__int32 nError)
{
	if (nError != BS_SDK_ERROR_NO)
		GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, nError);
}
