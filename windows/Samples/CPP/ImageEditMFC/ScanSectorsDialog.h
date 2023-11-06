#pragma once

#include "ErrorListLogCreator.h"

// KScanSectorsDialog dialog

class KScanSectorsDialog : public CDialog
{
	DECLARE_DYNAMIC(KScanSectorsDialog)

private :
	KScanSectorsDialog(CWnd* pParent = NULL);   // standard constructor

public :
	KScanSectorsDialog(CWnd* pParent, int32 nStartLBA, int32 nRegionSizeInSectors, ILogCreator* pLogCreator);
	virtual ~KScanSectorsDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCAN_SECTORS };

private :
	private:
	IScanLogger* m_pLogger;
	ILogCreator* m_pLogCreator;
	int32 m_nStartLBA;
	int32 m_nRegionSizeInSectors;
	CWinThread *m_pThread;

private :
	void EnableStart();
	void EnableStop();

	static UINT ScanThreadProc(LPVOID param);

	void ScanProc();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
};
