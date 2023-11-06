#pragma once

#include "Logging.h"

class KErrorListLogCreator : public ILogCreator
{
public:
	virtual CWnd* CreateLoggingWidget(CWnd* pParent, CRect rect);
	virtual IScanLogger* CreateLogger();
};


class KErrorListLogger : public IScanLogger
{
private:
	int32 m_nStartLba;
	int32 m_nBadSectors;
	int32 m_nRegionSizeInSectors;
	CListBox* m_pText;

	volatile bool m_bCancelled;	

	void ScrollToEndOfText();
	void AppendLine(CString strToAdd);

public:	
	KErrorListLogger();

public:
	virtual void SetStartLba(int32 nStartLba);
	virtual void SetRegionSize(int32 nRegionSizeInSectors);
	virtual int32 GetStartLba();
	virtual int32 GetRegionSize();
	virtual void LogSuccessiveRead(int32 nSuccessLba, int32 nSectors);
	virtual void LogFailureRead(int32 nFailLba);
	virtual void Reset();
	virtual void Done();
	virtual void Cancel();
	virtual bool IsCancelled();
	virtual void AttachToLoggingWidget(CWnd* pcLoggingWidget);
};
