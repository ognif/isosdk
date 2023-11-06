#ifndef _LOGGING_INTERFACES_H_
#define _LOGGING_INTERFACES_H_

#include "IsoSDKDefinitions.h"

namespace ScanSectorsLogging
{

	struct  SReadResults
	{
		bool	bSuccessive;
		int32 	nLBA;
		int32	nNumSectors;
	};
	
	class ILogGUI
	{
	 public:
		virtual void AddResults(const SReadResults&) = 0;		
		virtual bool Stopped(void) = 0;
		virtual void Finish() = 0;
	};
	
}

#endif //#ifndef _LOGGING_INTERFACES_H_
