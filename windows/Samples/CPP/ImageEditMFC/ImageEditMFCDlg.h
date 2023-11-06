// ImageEditMFCDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "TreeNodes.h"


// CImageEditMFCDlg dialog
class CImageEditMFCDlg : public CDialog
{
public:
	enum
	{
		ID_VIEW_SECTOR = WM_USER,
		ID_SCAN_SECTORS,
		ID_SHOW_PROPERTIES,
		ID_EXTRACT_TRACK,
		ID_EXTRACT_FILE,
		ID_EXTRACT_FILEEX,
		ID_CHECK_SIGNATURE,
		ID_EXTRACT_SYS,
		ID_LIST_CONTENT
	};

private:
	typedef std::vector<ITreeNode*> NodeList;

	NodeList m_cMenuNodes;

// Construction
public:
	CImageEditMFCDlg(CWnd* pParent = NULL);	// standard constructor
	~CImageEditMFCDlg();

// Dialog Data
	enum { IDD = IDD_IMAGEEDITMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	void HandleError(__int32);
	
	void UpdateDeviceCombo();

	void ReloadLeftPanel();
	void ReloadRightPanel();

	void BuildNode(HTREEITEM parent, ITreeNode* node);
	void SelectItem(HTREEITEM item);

	std::pair<int, int> GetNodeIcons(GenericInfo::Icon iconType);

	void ShowPopupForNodes(NodeList& nodes, int x, int y);

	void RecursivePrintContent(FILE *pFile, ITreeNode* pcNode, CString strFolderPath);

	DWORD doExtraction(int16 nTrackNumber, const CString& strFilePath, unsigned nFileFormat);

	int32 ExtractTextFromHandle(int32 hCdText,int32 nTrackNumber,int32 nCDTCI, CString& rText);

	bool IsImageDeviceEnabled() const;
	CString GetCurrentImagePath() const;

	bool m_bBurningDevicesOnly;
	CString m_strStartupDir;

	MediumNode* m_medium;

	CComboBox m_cmbDevice;
	CTreeCtrl m_treeLeftPanel;
	CListCtrl m_listRightPanel;

	CImageList* m_pImageList;
	
	HICON m_iconPlay, m_iconStop;
	HICON m_hIcon;

// Implementation
protected:
	
	// Generated message map functions
	virtual BOOL OnInitDialog();	
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboDevice();
	afx_msg void OnDiscVerify();
	afx_msg void OnDiscSave();
	afx_msg void OnImageMountimage();
	afx_msg void OnImageUnmountimage();
	afx_msg void OnImageMakeMd5();
	afx_msg void OnImageCheckMd5();	
	afx_msg void OnAspiRescandevices();
	afx_msg void OnAspiBurndevicesonly();
	afx_msg void OnAspiDisableimagewirter();
	afx_msg void OnAudioPlayselected();
	afx_msg void OnAudioGrabSelected();	
	afx_msg void OnAudioGrabAll();
	afx_msg void OnReadCDText();
	afx_msg void OnReadISRC();
	afx_msg void OnReadIndexes();
	afx_msg void OnInformationShow();
	afx_msg void OnInformationWeb();
	afx_msg BOOL OnSetAspi(UINT nAspi);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnItemchangedListRightpanel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeLeftpanel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListRightpanel(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnNMRclickTreeLeftpanel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListRightpanel(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnShowProperties();	
	afx_msg void OnViewSector();
	afx_msg void OnScanSector();
	afx_msg void OnExtractTrack();
	afx_msg void OnExtractFile();	
	afx_msg void OnExtractFileEx();
	afx_msg void OnCheckSignature();
	afx_msg void OnListContent();
	afx_msg void OnRefresh();
	afx_msg void OnSaveLog();
};

