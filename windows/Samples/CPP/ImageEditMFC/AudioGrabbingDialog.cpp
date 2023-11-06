// AudioGrabbingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageEditMFC.h"
#include "AudioGrabbingDialog.h"



int ComboIndex2Bitrate(int nIndex)
{
	switch (nIndex)
	{
		case 0 :
			return 64;
		case 1 :
			return 96;
		case 2 :
			return 128;
		case 3 :
			return 192;
		case 4 :
			return 256;
		case 5 :
			return 320;
		default:
			return 128;
	}
}

int ComboIndex2EncoderIndex(int nIndex)
{
	switch (nIndex)
	{
		case 0 :
			return BS_ET_MP3;
		case 1 :
			return BS_ET_AAC;
		case 2 :
			return BS_ET_OGG;
		case 3 :
			return BS_ET_OPUS;
		case 4:
			return BS_ET_FLAC;
		default :
			return BS_ET_MP3;
	}
}

CString ComboIndex2FileExt(int nIndex)
{
	switch (ComboIndex2EncoderIndex(nIndex))
	{
		case BS_ET_MP3:
			return _T(".mp3");

		case BS_ET_AAC:
			return _T(".aac");

		case BS_ET_OGG:
			return _T(".ogg");

		case BS_ET_OPUS:
			return _T(".opus");

		case BS_ET_FLAC:
			return _T(".flac");

		default :
			return _T("");
	}

}

int ComboIndex2TagChoice(int nIndex)
{
	switch (nIndex)
	{
		case 0 :
			return BS_TCH_NONE;
		case 1 :
			return BS_TCH_CDTEXT;
		case 2 :
			return BS_TCH_INTERNETDB;
		case 3 :
			return BS_TCH_CDTEXT_INTERNETDB;
		case 4 :
			return BS_TCH_INTERNETDB_CDTEXT;
		default :
			return BS_TCH_NONE;
	}
}




// KAudioGrabbingDialog dialog

IMPLEMENT_DYNAMIC(KAudioGrabbingDialog, CDialog)
KAudioGrabbingDialog::KAudioGrabbingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KAudioGrabbingDialog::IDD, pParent)
	,m_bReady(false)
{
}

KAudioGrabbingDialog::KAudioGrabbingDialog(std::vector<int32> vTracks, CWnd* pParent)
	:CDialog(KAudioGrabbingDialog::IDD, pParent)	
	,m_enState(ST_NONE)
	,m_vTracks(vTracks)
	,m_bReady(true)
{	
}

KAudioGrabbingDialog::~KAudioGrabbingDialog()
{
}

void KAudioGrabbingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENCODER, m_cmbEncoder);
	DDX_Control(pDX, IDC_COMBO_BITRATE_TYPE, m_cmbBitrateType);
	DDX_Control(pDX, IDC_COMBO_CBR_BITRATE, m_cmbBitrate);
	DDX_Control(pDX, IDC_COMBO_VBR_MIN_BITRATE, m_cmbBitrateMin);
	DDX_Control(pDX, IDC_COMBO_VBR_MAX_BITRATE, m_cmbBitrateMax);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_cmbBitrateQuality);
	DDX_Control(pDX, IDC_COMBO_TAGS_Choice, m_cmbTagsChoice);
}


BEGIN_MESSAGE_MAP(KAudioGrabbingDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_ENCODER, OnEncoderTypeChanged)
	ON_CBN_SELCHANGE(IDC_COMBO_BITRATE_TYPE, OnBitrateTypeBox)
	ON_CBN_SELCHANGE(IDC_COMBO_VBR_MIN_BITRATE, OnMinBitrateBox)
	ON_CBN_SELCHANGE(IDC_COMBO_VBR_MAX_BITRATE, OnMaxBitrateBox)
	ON_MESSAGE(WM_BURNDONE_NOTIFY, OnOnBurnDoneNotify)
END_MESSAGE_MAP()


// KAudioGrabbingDialog message handlers

BOOL KAudioGrabbingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_bReady)
	{
		return 0;
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);			// Set small icon

	m_nCurrentTrack = 0;

	//--------------------------------------------------
	//Set the callbacks to receive infos later
	//--------------------------------------------------
	
	SetProcessEventCallback((ProcessEvent) /*static*/ KAudioGrabbingDialog::OnProcessEvent, this);
	SetJobDoneEventCallback((JobDoneEvent) /*static*/ KAudioGrabbingDialog::OnJobDoneEvent, this);
	SetBurnDoneEventCallback((BurnDoneEvent) /*static*/ KAudioGrabbingDialog::OnBurnDoneEvent, this);

	CString strTrack;
	strTrack.Format(_T("%d"), m_vTracks[m_nCurrentTrack]);
	SetDlgItemText(IDC_CUR_TRACK, strTrack);
	
	m_cmbEncoder.AddString(_T("MP3"));
	m_cmbEncoder.AddString(_T("AAC"));
	m_cmbEncoder.AddString(_T("OGG"));
	m_cmbEncoder.AddString(_T("OPUS"));
	m_cmbEncoder.AddString(_T("FLAC"));
	m_cmbEncoder.SetCurSel(0);

	m_cmbBitrateType.AddString(_T("Constant"));
	m_cmbBitrateType.AddString(_T("Variable"));
	m_cmbBitrateType.AddString(_T("Average"));
	m_cmbBitrateType.SetCurSel(0);

	m_cmbBitrate.AddString(_T("64 kBit/s"));
	m_cmbBitrate.AddString(_T("96 kBit/s"));
	m_cmbBitrate.AddString(_T("128 kBit/s"));
	m_cmbBitrate.AddString(_T("192 kBit/s"));
	m_cmbBitrate.AddString(_T("256 kBit/s"));
	m_cmbBitrate.AddString(_T("320 kBit/s"));
	m_cmbBitrate.SetCurSel(0);

	m_cmbBitrateMin.AddString(_T("64 kBit/s"));
	m_cmbBitrateMin.AddString(_T("96 kBit/s"));
	m_cmbBitrateMin.AddString(_T("128 kBit/s"));
	m_cmbBitrateMin.AddString(_T("192 kBit/s"));
	m_cmbBitrateMin.AddString(_T("256 kBit/s"));
	m_cmbBitrateMin.AddString(_T("320 kBit/s"));
	m_cmbBitrateMin.SetCurSel(0);

	m_cmbBitrateMax.AddString(_T("64 kBit/s"));
	m_cmbBitrateMax.AddString(_T("96 kBit/s"));
	m_cmbBitrateMax.AddString(_T("128 kBit/s"));
	m_cmbBitrateMax.AddString(_T("192 kBit/s"));
	m_cmbBitrateMax.AddString(_T("256 kBit/s"));
	m_cmbBitrateMax.AddString(_T("320 kBit/s"));
	m_cmbBitrateMax.SetCurSel(0);

	
	m_cmbBitrateQuality.AddString(_T("1"));
	m_cmbBitrateQuality.AddString(_T("2"));
	m_cmbBitrateQuality.AddString(_T("3"));
	m_cmbBitrateQuality.AddString(_T("4"));
	m_cmbBitrateQuality.AddString(_T("5"));
	m_cmbBitrateQuality.AddString(_T("6"));
	m_cmbBitrateQuality.AddString(_T("7"));
	m_cmbBitrateQuality.AddString(_T("8"));
	m_cmbBitrateQuality.AddString(_T("9"));
	m_cmbBitrateQuality.SetCurSel(0);


	m_cmbTagsChoice.AddString(_T("Don't add"));
	m_cmbTagsChoice.AddString(_T("From CD-Text only"));
	m_cmbTagsChoice.AddString(_T("From Internet only"));
	m_cmbTagsChoice.AddString(_T("CD-Text first Internet last"));
	m_cmbTagsChoice.AddString(_T("Internet first CD-Text last"));
	m_cmbTagsChoice.SetCurSel(1);
	
	m_enState = ST_NONE;
	SetDlgItemText(IDOK, _T("&Convert"));

	OnBitrateTypeBox();

	return TRUE;
}

void KAudioGrabbingDialog::OnBnClickedButtonBrowse()
{
	CString strPattern;
	CString strExt = ComboIndex2FileExt(m_cmbEncoder.GetCurSel());
	strPattern.Format(_T("Supported format (*%s)|*%s||"), strExt, strExt);

	CFileDialog  dlg(FALSE, NULL, NULL, 0, strPattern, this);
	

	if (dlg.DoModal() == IDOK)
	{

		CString strFileName = dlg.GetPathName();

		if (!strFileName.GetLength())
		{
			return;
		}

		int pos = strFileName.ReverseFind(_T('.'));

		if (pos != -1)
		{
			strFileName = strFileName.Left(pos) + strExt;
		}
		else
		{
			strFileName += strExt;
		}

		SetDlgItemText(IDC_EDIT_PATH, strFileName);
	}
}

void KAudioGrabbingDialog::OnBnClickedOk()
{
	if (ST_NONE == m_enState)
	{
		if (m_nCurrentTrack < m_vTracks.size())
		{
			CString strSavePath;	
			GetDlgItemText(IDC_EDIT_PATH, strSavePath);

			if (strSavePath.IsEmpty())
			{
				AfxMessageBox(_T("Please, specify the file name."));
				return;
			}

			int32 res;
			SAudioGrabbingParams params;

			switch (m_cmbBitrateType.GetCurSel()) {
			case 0:
				params.nBitrateType = BS_BT_CONSTANT;
				break;
			case 1:
				params.nBitrateType = BS_BT_VARIABLE;
				break;
			case 2:
				params.nBitrateType = BS_BT_AVERAGE;
				break;

			}
			

			params.nBitrate		= ComboIndex2Bitrate(m_cmbBitrate.GetCurSel());
			params.nMinBitrate	= ComboIndex2Bitrate(m_cmbBitrateMin.GetCurSel());
			params.nMaxBitrate	= ComboIndex2Bitrate(m_cmbBitrateMax.GetCurSel());
			params.nQuality		= m_cmbBitrateQuality.GetCurSel()+1;
			params.nEncoderType = ComboIndex2EncoderIndex(m_cmbEncoder.GetCurSel());
			params.nTagChoice	= ComboIndex2TagChoice(m_cmbTagsChoice.GetCurSel());

			if(params.nTagChoice >= BS_TCH_INTERNETDB)
			{
				int32 h = BS_INVALID_TAG_HANDLE;
				::TagsFromNetworkDialog(BS_READ_DEVICE, &h);			
				params.nNetworkTagsHandle = h;
			}
			
			res = ::GrabAudioTrack(params, m_vTracks[m_nCurrentTrack++], strSavePath);
			HandleError(res);
			
			if (res == BS_SDK_ERROR_NO)
			{
				SYSTEMTIME timeNow;
				GetSystemTime(&timeNow);
				CTime time(timeNow);
				m_timeStart = CTimeSpan(time.GetTime());
	
				SetTimer(1, 1000, NULL);

				m_enState = ST_PROCESSING;
				SetDlgItemText(IDOK, _T("&Abort"));

				m_cmbEncoder.EnableWindow(FALSE);
				m_cmbBitrateType.EnableWindow(FALSE);
				m_cmbBitrate.EnableWindow(FALSE);
				m_cmbBitrateMin.EnableWindow(FALSE);
				m_cmbBitrateMax.EnableWindow(FALSE);
				m_cmbTagsChoice.EnableWindow(FALSE);
				m_cmbBitrateQuality.EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_BROWSE)->EnableWindow(FALSE);
			}
		}
		else
		{
			ATLASSERT(0);
		}
	}
	else if (m_enState == ST_PROCESSING)
	{
		m_enState = ST_ABORTED;
		
		if (BS_SDK_ERROR_NO == ::Abort())
		{
			GetDlgItem(IDOK)->EnableWindow(FALSE);
		}
		else
		{
			Done();
		}
	}		
	else
	{
		RestoreEvents();
		OnOK();
	}
}

void KAudioGrabbingDialog::OnTimer(UINT_PTR ID)
{
	SYSTEMTIME timeNow;
	GetSystemTime(&timeNow);
	CTime time(timeNow);
	CTimeSpan timeCurrent = CTimeSpan(time.GetTime());
	timeCurrent -=  m_timeStart;

	CString strElapsed;
	strElapsed.Format(_T("%.2d:%.2d:%.2d"), timeCurrent.GetHours(),
		timeCurrent.GetMinutes(), timeCurrent.GetSeconds());
	
	SetDlgItemText(IDC_TIME, strElapsed);
	
	if (m_enState != ST_PROCESSING)
	{
		KillTimer(1);
	}
}

void KAudioGrabbingDialog::RestoreEvents()
{	
	SetJobDoneEventCallback(NULL, NULL);
	SetProcessEventCallback(NULL, NULL);
	SetBurnDoneEventCallback(NULL, NULL);
}

/*static*/ void KAudioGrabbingDialog::OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, 
				double dBytesWritten, double dImageSize, KAudioGrabbingDialog *pDlg) 
{
	pDlg->SetProgress((int)fPercent, dBytesWritten, dImageSize);	
}

void KAudioGrabbingDialog::SetProgress(int nProgress, double dBytesWritten, double dTrackSize)
{
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS))->SetPos(nProgress);

	CString strTmp;
	strTmp.Format(_T("%.0f"), dBytesWritten);
	SetDlgItemText(IDC_BYTES, strTmp);

	
	strTmp.Format(_T("%.0f"), dTrackSize);
	SetDlgItemText(IDC_TOTAL, strTmp);	
}

/*static*/ void KAudioGrabbingDialog::OnJobDoneEvent(KAudioGrabbingDialog *pDlg) 
{
	pDlg->OnJobDone();
}

void KAudioGrabbingDialog::OnJobDone()
{
	switch (m_enState)
	{	
		case ST_ABORTED :

			m_enState = ST_DONE;
			Done();

		break;

		case ST_PROCESSING :
	
			if (m_nCurrentTrack == m_vTracks.size())
			{
				Done();
			}
			else
			{
				m_enState = ST_NONE;

				CString strTrack;
				strTrack.Format(_T("%d"), m_vTracks[m_nCurrentTrack]);
				SetDlgItemText(IDC_CUR_TRACK, strTrack);

				CString temp;
				temp.Format(_T("Track%d"), m_vTracks[m_nCurrentTrack]);
				CString strSavePath;
				GetDlgItemText(IDC_EDIT_PATH, strSavePath);

				strSavePath = strSavePath.Left(strSavePath.ReverseFind(_T('\\')) + 1);
				strSavePath += temp;
				strSavePath += ComboIndex2FileExt(m_cmbEncoder.GetCurSel());
				SetDlgItemText(IDC_EDIT_PATH, strSavePath);
				
				SetDlgItemText(IDOK, _T("&Convert"));
			}

		break;

		case ST_CANCELLED :

			this->PostMessage(WM_CLOSE);

		break;
	}
}

void KAudioGrabbingDialog::Done()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	SetDlgItemText(IDOK, _T("&Close"));
	KillTimer(1);
}

/*static*/ void KAudioGrabbingDialog::OnBurnDoneEvent(const TCHAR *pcError, KAudioGrabbingDialog *pDlg)
{
	pDlg->SendMessage(WM_BURNDONE_NOTIFY, (WPARAM)pcError);
}

LRESULT KAudioGrabbingDialog::OnOnBurnDoneNotify(WPARAM pcError, LPARAM)
{
	if (pcError && _tcslen((TCHAR *)pcError) > 0)
	{
		AfxMessageBox((TCHAR *)pcError);
	}

	return 0;
}

void KAudioGrabbingDialog::HandleError(int32 errCode)
{
	if (errCode != BS_SDK_ERROR_NO)
	{
		TCHAR chError[2048];
		int32 nLength = 2048;

		// Get error description
		::GetText(errCode, chError, &nLength);

#ifdef _UNICODE
		KString strError = KStringFormat(_T("error: %ls"), chError);
#else
		KString strError = KStringFormat(_T("error: %hs"), chError);
#endif

		AfxMessageBox(strError);
	}
}


void KAudioGrabbingDialog::OnEncoderTypeChanged()
{
	bool bVariablePossible = false;
	bool bAveragePossible = false;

	switch (ComboIndex2EncoderIndex(m_cmbEncoder.GetCurSel()))
	{
		case BS_ET_MP3:
			bAveragePossible = true;
			bVariablePossible = true;
			break;
		case BS_ET_OGG:
		case BS_ET_AAC:
		case BS_ET_OPUS:
			bVariablePossible = true;
		break;

		
		case BS_ET_FLAC:
			bVariablePossible = false;
		break;
	}

	m_cmbBitrateType.ResetContent();
	m_cmbBitrateType.AddString(_T("Constant"));

	if (bVariablePossible)
	{
		m_cmbBitrateType.AddString(_T("Variable"));
	}
	if (bAveragePossible)
	{
		m_cmbBitrateType.AddString(_T("Average"));
	}

	m_cmbBitrateType.SetCurSel(0);
	OnBitrateTypeBox();

	CString strFileName(_T(""));
	GetDlgItemText(IDC_EDIT_PATH, strFileName);

	if (!strFileName.IsEmpty())
	{
		CString strExt = ComboIndex2FileExt(m_cmbEncoder.GetCurSel());

		int pos = strFileName.ReverseFind(_T('.'));

		if (pos != -1)
		{
			strFileName = strFileName.Left(pos) + strExt;
		}
		else
		{
			strFileName += strExt;
		}

		SetDlgItemText(IDC_EDIT_PATH, strFileName);
	}
}

void KAudioGrabbingDialog::OnBitrateTypeBox()
{
	int item = m_cmbBitrateType.GetCurSel();

	switch (ComboIndex2EncoderIndex(m_cmbEncoder.GetCurSel()))
	{
	case BS_ET_MP3:
		switch (item) {
		case 0:
			m_cmbBitrate.EnableWindow();
			m_cmbBitrateMin.EnableWindow(FALSE);
			m_cmbBitrateMax.EnableWindow(FALSE);
			m_cmbBitrateQuality.EnableWindow(FALSE);
			break;
		case 1:
			m_cmbBitrate.EnableWindow(FALSE);
			m_cmbBitrateMin.EnableWindow();
			m_cmbBitrateMax.EnableWindow();
			m_cmbBitrateQuality.EnableWindow(FALSE);
			break;
		case 2:
			m_cmbBitrate.EnableWindow();
			m_cmbBitrateMin.EnableWindow(FALSE);
			m_cmbBitrateMax.EnableWindow(FALSE);
			m_cmbBitrateQuality.EnableWindow(FALSE);
			break;
		}
		break;
	case BS_ET_OGG:
		switch (item) {
		case 0:
			m_cmbBitrate.EnableWindow();
			m_cmbBitrateMin.EnableWindow(FALSE);
			m_cmbBitrateMax.EnableWindow(FALSE);
			m_cmbBitrateQuality.EnableWindow(FALSE);
			break;
		case 1:
			m_cmbBitrate.EnableWindow(FALSE);
			m_cmbBitrateMin.EnableWindow();
			m_cmbBitrateMax.EnableWindow();
			m_cmbBitrateQuality.EnableWindow(FALSE);
			break;
		}
		break;
	
	case BS_ET_AAC:
		switch (item) {
		case 0:
			m_cmbBitrate.EnableWindow();
			m_cmbBitrateMin.EnableWindow(FALSE);
			m_cmbBitrateMax.EnableWindow(FALSE);
			m_cmbBitrateQuality.EnableWindow(FALSE);
			break;
		case 1:
			m_cmbBitrate.EnableWindow(FALSE);
			m_cmbBitrateMin.EnableWindow(FALSE);
			m_cmbBitrateMax.EnableWindow(FALSE);
			m_cmbBitrateQuality.EnableWindow();
			break;
		}
		break;
	case BS_ET_OPUS:
		m_cmbBitrate.EnableWindow();
		m_cmbBitrateMin.EnableWindow(FALSE);
		m_cmbBitrateMax.EnableWindow(FALSE);
		m_cmbBitrateQuality.EnableWindow();
		break;
	case BS_ET_FLAC:
		m_cmbBitrate.EnableWindow(FALSE);
		m_cmbBitrateMin.EnableWindow(FALSE);
		m_cmbBitrateMax.EnableWindow(FALSE);
		m_cmbBitrateQuality.EnableWindow();
		break;
	}

}

void KAudioGrabbingDialog::OnMinBitrateBox()
{
	int nMinBitrate	= ComboIndex2Bitrate(m_cmbBitrateMin.GetCurSel());
	int nMaxBitrate	= ComboIndex2Bitrate(m_cmbBitrateMax.GetCurSel());

	if (nMinBitrate > nMaxBitrate)
	{
		m_cmbBitrateMax.SetCurSel(m_cmbBitrateMin.GetCurSel());
	}
}

void KAudioGrabbingDialog::OnMaxBitrateBox()
{
	int nMinBitrate	= ComboIndex2Bitrate(m_cmbBitrateMin.GetCurSel());
	int nMaxBitrate	= ComboIndex2Bitrate(m_cmbBitrateMax.GetCurSel());

	if (nMaxBitrate < nMinBitrate)
	{
		m_cmbBitrateMin.SetCurSel(m_cmbBitrateMax.GetCurSel());
	}
}

void KAudioGrabbingDialog::OnCancel()
{
	m_enState = ST_CANCELLED;
	
	if (::Abort() != BS_SDK_ERROR_NO)
	{
		KillTimer(1);
		RestoreEvents();
		CDialog::OnCancel();
	}
}