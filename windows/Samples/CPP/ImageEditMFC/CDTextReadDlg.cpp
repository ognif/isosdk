#include "stdafx.h"
#include "CDTextReadDlg.h"

// KCDTextReadDialog dialog

IMPLEMENT_DYNAMIC(KCDTextReadDialog, CDialog)
KCDTextReadDialog::KCDTextReadDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KCDTextReadDialog::IDD, pParent)
{
}

KCDTextReadDialog::KCDTextReadDialog(CWnd* pParent, 
		const TCHAR* strArranger,
		const TCHAR* strComposer,
		const TCHAR* strSongWriter,
		const TCHAR* strPerformer,
		const TCHAR* strTitle,
		const TCHAR* strMessage
		)
		:CDialog(KCDTextReadDialog::IDD, pParent)
		,m_strArranger(strArranger)
		,m_strComposer(strComposer)
		,m_strSongWriter(strSongWriter)
		,m_strPerformer(strPerformer)
		,m_strTitle(strTitle)
		,m_strMessage(strMessage)
{
}		

KCDTextReadDialog::~KCDTextReadDialog()
{
}

void KCDTextReadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);		
}


BEGIN_MESSAGE_MAP(KCDTextReadDialog, CDialog)	
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// KCDTextReadDialog message handlers

BOOL KCDTextReadDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	SetDlgItemText(IDC_CDT_ARRANGER, (const TCHAR*)m_strArranger);
	SetDlgItemText(IDC_CDT_COMPOSER, (const TCHAR*)m_strComposer);
	SetDlgItemText(IDC_CDT_MESSAGE, (const TCHAR*)m_strMessage);
	SetDlgItemText(IDC_CDT_PERFOMER, (const TCHAR*)m_strPerformer);
	SetDlgItemText(IDC_CDT_SONG_WRITER, (const TCHAR*)m_strSongWriter);
	SetDlgItemText(IDC_CDT_TITLE, (const TCHAR*)m_strTitle);	

	return TRUE;
}

