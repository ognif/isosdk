// GetCapa.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "UtilitiesMFC.h"
#include "IsoSDKExport.h"
#include "GetCapa.h"

// CCapabilitiesDlg-Dialogfeld

CCapabilitiesDlg::CCapabilitiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCapabilitiesDlg::IDD, pParent)
{
	m_mCapsMap[BS_READ_CDR] = IDC_CAP1;
	m_mCapsMap[BS_READ_CDRW] = IDC_CAP2;
	m_mCapsMap[BS_READ_DVD] = IDC_CAP3;
	m_mCapsMap[BS_READ_DVDR] = IDC_CAP4;
	m_mCapsMap[BS_READ_DVDRW] = IDC_CAP5;
	m_mCapsMap[BS_READ_DVDRAM] = IDC_CAP6;
	m_mCapsMap[BS_READ_DVDR_PLUS] = IDC_CAP7;
	m_mCapsMap[BS_READ_DVDRW_PLUS] = IDC_CAP8;
	m_mCapsMap[BS_READ_DVD_DL]	 = IDC_CAP9;
	m_mCapsMap[BS_READ_DVD_MRDL] = IDC_CAP10;
	m_mCapsMap[BS_READ_BLURAY_ROM] = IDC_CAP13;
	m_mCapsMap[BS_READ_BLURAY_R] = IDC_CAP11;
	m_mCapsMap[BS_READ_BLURAY_RE] = IDC_CAP12;
	m_mCapsMap[BS_READ_BLURAY_R_XL] = IDC_READ_BD_R_XL;
	m_mCapsMap[BS_READ_BLURAY_RE_XL] = IDC_READ_BD_RE_XL;
	m_mCapsMap[BS_READ_HDDVD_R] = IDC_CAP14;
	m_mCapsMap[BS_READ_HDDVD_RW] = IDC_CAP15;
	m_mCapsMap[BS_READ_HDDVD_ROM] = IDC_CAP16;
	m_mCapsMap[BS_READ_MOUNT_RAINER] = IDC_CAP20;
	m_mCapsMap[BS_READ_CDRW_CAV] = IDC_CAP21;
	m_mCapsMap[BS_READ_DVD_RDL_PLUS] = IDC_CAP18;
	m_mCapsMap[BS_READ_DVD_RWDL_PLUS] = IDC_CAP19;

	m_mCapsMap[BS_WRITE_CDR] = IDC_CAP22;
	m_mCapsMap[BS_WRITE_CDRW] = IDC_CAP23;
	m_mCapsMap[BS_WRITE_DVDR]	 = IDC_CAP24;
	m_mCapsMap[BS_WRITE_DVDRW]	 = IDC_CAP25;
	m_mCapsMap[BS_WRITE_DVDRAM] = IDC_CAP26;
	m_mCapsMap[BS_WRITE_DVDR_PLUS] = IDC_CAP27;
	m_mCapsMap[BS_WRITE_DVDRW_PLUS] = IDC_CAP28;
	m_mCapsMap[BS_WRITE_DVD_DL] = IDC_CAP29;
	m_mCapsMap[BS_WRITE_DVD_MRDL] = IDC_CAP30;
	m_mCapsMap[BS_WRITE_BLURAY_R] = IDC_CAP31;
	m_mCapsMap[BS_WRITE_BLURAY_RE] = IDC_CAP32;
	m_mCapsMap[BS_WRITE_BLURAY_R_XL] = IDC_WRITE_BD_R_XL;
	m_mCapsMap[BS_WRITE_BLURAY_RE_XL] = IDC_WRITE_BD_RE_XL;
	m_mCapsMap[BS_WRITE_HDDVD_R] = IDC_CAP33;
	m_mCapsMap[BS_WRITE_HDDVD_RW] = IDC_CAP34;
	m_mCapsMap[BS_WRITE_MOUNT_RAINER] = IDC_CAP39;
	m_mCapsMap[BS_WRITE_CDRW_CAV] = IDC_CAP40;
	m_mCapsMap[BS_WRITE_DVD_RDL_PLUS] = IDC_CAP37;
	m_mCapsMap[BS_WRITE_DVD_RWDL_PLUS] = IDC_CAP38;

	m_mCapsMap[BS_WRITE_TEST] = IDC_CAP41;
	m_mCapsMap[BS_UNDERRUN_PROTECTION] = IDC_CAP46;
	m_mCapsMap[BS_SMART] = IDC_CAP45;
	m_mCapsMap[BS_MULTISESSION] = IDC_CAP43;
	m_mCapsMap[BS_CPRMAUTH] = IDC_CAP42;
	m_mCapsMap[BS_DEFECTMANAGEMENT] = IDC_CAP47;
	m_mCapsMap[BS_STREAMING] = IDC_CAP44;
	m_mCapsMap[BS_LAYER_JUMP_RECORDING] = IDC_CAP48;

	m_mCapsMap[BS_ANALOG_AUDIO_PLAYBACK] = IDC_CAP49;
	m_mCapsMap[BS_COMPOSITE_AUDIO_AND_VIDEO] = IDC_CAP50;
	m_mCapsMap[BS_DIGITAL_PORT_1] = IDC_CAP51;
	m_mCapsMap[BS_DIGITAL_PORT_2] = IDC_CAP52;
	m_mCapsMap[BS_MODE2_FORM1_READ] = IDC_CAP53;
	m_mCapsMap[BS_MODE2_FORM2_READ] = IDC_CAP54;
	m_mCapsMap[BS_CDDA_COMMANDS] = IDC_CAP55;
	m_mCapsMap[BS_CDDA_STREAM_IS_ACCURATE] = IDC_CAP56;
	m_mCapsMap[BS_R_W_SUBCHANNELS_READ] = IDC_CAP57;
	m_mCapsMap[BS_R_W_SUBCHANNELS_DEINT_AND_CORR] = IDC_CAP58;
	m_mCapsMap[BS_C2_POINTERS] = IDC_CAP59;
	m_mCapsMap[BS_ISRC_READ] = IDC_CAP60;
	m_mCapsMap[BS_UPC_READ] = IDC_CAP61;
	m_mCapsMap[BS_BARCODE_READ] = IDC_CAP62;
	m_mCapsMap[BS_LOCK_MEDIA] = IDC_CAP63;
	m_mCapsMap[BS_LOCK_STATE] = IDC_CAP64;
	m_mCapsMap[BS_PREVENT_JUMPER] = IDC_CAP65;
	m_mCapsMap[BS_EJECT_INDIVIDUAL_OR_MAGAZINE] = IDC_CAP66;
	m_mCapsMap[BS_SEPARATE_VOLUME_LEVELS] = IDC_CAP67;
	m_mCapsMap[BS_SEPARATE_CHANNEL_MUTE] = IDC_CAP68;
	m_mCapsMap[BS_CHANGER_SUPPORTS_DISC_PRESENT] = IDC_CAP69;
	m_mCapsMap[BS_CHANGER_SOFTWARE_SLOT_SELECTION] = IDC_CAP70;
	m_mCapsMap[BS_CHANGER_SIDE_CHANGE_CAPABLE] = IDC_CAP71;
	m_mCapsMap[BS_R_W_SUBCHANNELS_IN_LEAD_IN_READ] = IDC_CAP72;
	m_mCapsMap[BS_METHOD_2_ADDRESSING_FIXED_PACKETS] = IDC_CAP73;
	m_mCapsMap[BS_CD_TEXT_READ] = IDC_CAP74;
	m_mCapsMap[BS_CD_TEXT_WRITE] = IDC_CAP75;
	m_mCapsMap[BS_DAO_RAW] = IDC_CAP76;
	m_mCapsMap[BS_DAO_16] = IDC_CAP77;
	m_mCapsMap[BS_DAO_96_PACK] = IDC_CAP78;
	m_mCapsMap[BS_DAO_96_RAW] = IDC_CAP79;
	m_mCapsMap[BS_PACKET_WRITE] = IDC_CAP80;

	m_mCapsMap[BS_LABELFLASH] = IDC_CAP_LABELFLASH;
	m_mCapsMap[BS_LIGHTSCRIBE] = IDC_CAP_LIGHTSCRIBE;
}


CCapabilitiesDlg::~CCapabilitiesDlg()
{
}

void CCapabilitiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	int32 nCapsHandle;

	int32 nErr = ::GetDeviceCapabilitiesHandle(BS_CURRENT_DEVICE, &nCapsHandle);
	if(nErr != BS_SDK_ERROR_NO)
	{
		MessageBox(_T("Error returned from GetDeviceCapabilitiesHandle()"), _T("Error"));
		return;
	}

	CapsMap::iterator it = m_mCapsMap.begin();
	for(; it != m_mCapsMap.end(); ++it)
	{
		BS_BOOL bRes;
		
		nErr = ::AnalyseDeviceCapability(nCapsHandle, it->first, &bRes);
		
		if(nErr != BS_SDK_ERROR_NO)
		{
			MessageBox(_T("Error returned from AnalyseDeviceCapability()"), _T("Error"));
			return;
		}

		CheckDlgButton(it->second, bRes ? TRUE : FALSE);
	}
	
	nErr = ::ReleaseDeviceCapabilities(nCapsHandle);
	if(nErr != BS_SDK_ERROR_NO)
	{
		MessageBox(_T("Error returned from ReleaseDeviceCapabilities()"), _T("Error"));
		return;
	}
}


BEGIN_MESSAGE_MAP(CCapabilitiesDlg, CDialog)
END_MESSAGE_MAP()


// CCapabilitiesDlg-Meldungshandler

BOOL CCapabilitiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CCapabilitiesDlg::FillInfos()
{
	UpdateData(FALSE);
}

void CCapabilitiesDlg::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
		GetParent()->GetParent()->SendMessage(WM_ERROR_NOTIFY, 0, errCode);
}
