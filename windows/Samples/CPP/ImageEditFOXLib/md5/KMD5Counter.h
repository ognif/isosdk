#ifndef _K_MD5_COUNTER_H_
#define _K_MD5_COUNTER_H_

#include "KMD5DataSource.h"
#include "md5.h"

#include "fx.h"
#include "FXThread.h"

class KMD5Counter : public FXThread
{
private:
	FXMutex m_cMutex;
	int m_nProgress;
	KMD5DataSource* m_pcSource;
	MD5_CTX	m_cMD5State;
	volatile bool m_bCancelPressed;
public:
	virtual FXint run();

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

