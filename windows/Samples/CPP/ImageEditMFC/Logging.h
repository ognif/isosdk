#ifndef _LOGGING_INTERFACES_H_
#define _LOGGING_INTERFACES_H_

#include "IsoSDKDefinitions.h"

/* If there is a need to change the type of logger you need to
1) Create logging widget (for example RichEditCtrl)
2) Create your own logger to manage logging widget, inheriting from IScanLogger
3) Create fabrique class which can create 1) and 2), inheriting from ILogCreator
4) Modify only one function in ImageEditMFCDlg.cpp, adding your LogCreator:

*/

interface IScanLogger
{
public:
	virtual void SetStartLba(int32 nStartLba) = 0;
	virtual void SetRegionSize(int32 nRegionSizeInSectors) = 0;
	virtual int32 GetStartLba() = 0;
	virtual int32 GetRegionSize() = 0;
	virtual void LogSuccessiveRead(int32 nSuccessLba, int32 nSectors) = 0;
	virtual void LogFailureRead(int32 nFailLba) = 0;
	virtual void Reset() = 0;
	virtual void Done() = 0;
	virtual void Cancel() = 0;
	virtual bool IsCancelled() = 0;
	virtual void AttachToLoggingWidget(CWnd* pcLoggingWidget) = 0;
};

interface ILogCreator
{
public:
	virtual CWnd* CreateLoggingWidget(CWnd* pParent, CRect rect) = 0;
	virtual IScanLogger* CreateLogger() = 0;
};

#endif //#ifndef _LOGGING_INTERFACES_H_