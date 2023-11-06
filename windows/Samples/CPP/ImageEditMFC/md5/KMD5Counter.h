#ifndef _K_MD5_COUNTER_H_
#define _K_MD5_COUNTER_H_

#include "KMD5DataSource.h"
#include "md5.h"



class KMD5Counter
{
private:	
	
	int m_nProgress;
	
	KMD5DataSource* m_pcSource;
	
	MD5_CTX	m_cMD5State;
	
	volatile bool m_bCancelPressed;

	HANDLE m_hMutex;

	HANDLE m_hCountingThread;

protected :

	static unsigned __stdcall fncThreadCounting(void* pArg);

public:
	void start();

	KMD5Counter();
	KMD5Counter(KMD5DataSource* pSource);
	~KMD5Counter();

	void SetDataSource(KMD5DataSource* pSource);
	
	void StartCountingMD5();
	unsigned char* GetMD5();
	bool IsCountingDone();
	int GetProgress();
	void Cancel();
};

#endif// _K_MD5_COUNTER_H_

