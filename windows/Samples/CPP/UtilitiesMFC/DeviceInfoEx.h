// DeviceInfoDlgEx.h : header file
//

#ifndef DEVICEINFODLGEX_H
#define DEVICEINFODLGEX_H

#if _MSC_VER > 1000
#	pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDeviceInfoExDlg dialog

class CDeviceInfoExDlg : public CDialog
{
	// Construction
public:
	CDeviceInfoExDlg(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_DRIVEINFOEX };

	void FillInfo();

	// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	void HandleError(int32);

	CListCtrl	m_lstParams;

	DECLARE_MESSAGE_MAP()
};

#endif // DEVICEINFODLGEX_H
