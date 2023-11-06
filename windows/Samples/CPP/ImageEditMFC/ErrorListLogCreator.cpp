#include "StdAfx.h"
#include "ErrorListLogCreator.h"

CWnd* KErrorListLogCreator::CreateLoggingWidget(CWnd* pParent, CRect rect)
{
	CListBox *pText = new CListBox();
	
	DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_HSCROLL | 
		WS_TABSTOP | WS_VISIBLE;

	pText->Create(dwStyle, rect, pParent, 0);
	

	return pText;
}

IScanLogger* KErrorListLogCreator::CreateLogger()
{
	return new KErrorListLogger();
}

KErrorListLogger::KErrorListLogger():
	 m_nStartLba(0)
	,m_nRegionSizeInSectors(0)
	,m_pText(0)	
	,m_nBadSectors(0)
	,m_bCancelled(false)
{
}

void KErrorListLogger::ScrollToEndOfText()
{	
	m_pText->SetCurSel(m_pText->GetCount() - 1);	
}

void KErrorListLogger::SetStartLba(int32 nStartLba)
{
	m_nStartLba = nStartLba;
}

void KErrorListLogger::SetRegionSize(int32 nRegionSizeInSectors)
{
	m_nRegionSizeInSectors = nRegionSizeInSectors;
}

int32 KErrorListLogger::GetStartLba()
{
	return m_nStartLba;
}

int32 KErrorListLogger::GetRegionSize()
{
	return m_nRegionSizeInSectors;
}

void KErrorListLogger::LogSuccessiveRead(int32 nSuccessLba, int32 nSectors)
{	
	if(!m_bCancelled)
	{
		CString str;
		str.Format(_T("Sectors read successfully at LBA: %d. Quantity: %d."),
			nSuccessLba, nSectors);

		AppendLine(str);
		ScrollToEndOfText();
	}
}

bool KErrorListLogger::IsCancelled()
{	
	return m_bCancelled;
}

void KErrorListLogger::LogFailureRead(int32 nFailLba)
{	
	if(!m_bCancelled)
	{
		++m_nBadSectors;

		CString str;
		str.Format(_T("Sector read fail at LBA: %d."), nFailLba);
		AppendLine(str);	

		ScrollToEndOfText();
	}
}

void KErrorListLogger::Reset()
{	
	m_pText->ResetContent();
	AppendLine(_T("Scan log:"));
	
	CString str;
	str.Format(_T("Scanning %d sectors from LBA %d..."), 
		m_nRegionSizeInSectors, m_nStartLba);

	AppendLine(str);
	m_nBadSectors = 0;	
	m_bCancelled = false;	
	ScrollToEndOfText();
}

void KErrorListLogger::Done()
{
	CString str;
	str.Format(_T("Done. Sectors read: %d, from LBA: %d."), 
		m_nRegionSizeInSectors, m_nStartLba);
	
	AppendLine(str);
	
	str.Format(_T("Number of bad sectors: %d"), m_nBadSectors);

	AppendLine(str);

	ScrollToEndOfText();
}

void KErrorListLogger::Cancel()
{	
	m_bCancelled = true;	
	Yield();
	Sleep(500);
	
	CString str;
	str.Format(_T("User cancelled. Number of bad sectors: %d"), m_nBadSectors);

	AppendLine(str);	
	ScrollToEndOfText();
}

void KErrorListLogger::AttachToLoggingWidget(CWnd* pcLoggingWidget)
{
	CListBox* pText = 0;
	pText = dynamic_cast<CListBox*>(pcLoggingWidget);

	if (pText)
	{
		m_pText = pText;		
	}
}

void KErrorListLogger::AppendLine(CString strToAdd)
{
	m_pText->AddString(strToAdd);
}
