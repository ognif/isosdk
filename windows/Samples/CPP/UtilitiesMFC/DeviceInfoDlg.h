// DeviceInfoDlg.h : header file
//

#ifndef DEVICEINFODLG_H
#define DEVICEINFODLG_H

#if _MSC_VER > 1000
#	pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDeviceInfoDlg dialog

class CDeviceInfoDlg : public CDialog
{
// Construction
public:
	CDeviceInfoDlg(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_DRIVEINFO };

	void FillInfo();

// Implementation
protected:
	void HandleError(int32);

	DECLARE_MESSAGE_MAP()
};

#endif // DEVICEINFODLG_H
