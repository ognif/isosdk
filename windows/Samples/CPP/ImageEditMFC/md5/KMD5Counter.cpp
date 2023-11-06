#include "stdafx.h"
#include "KMD5Counter.h"
#include <process.h>
#include "../KLock.h"

void KMD5Counter::start()
{
	UINT nCountingThreadID;
	m_hCountingThread = (HANDLE)_beginthreadex(NULL, 0, &fncThreadCounting, this, 0, &nCountingThreadID);
}

unsigned __stdcall KMD5Counter::fncThreadCounting(void* pArg)
{
    KMD5Counter* pCounter = (KMD5Counter*)pArg;
    //
	pCounter->StartCountingMD5();
	//
	return 1;
}


KMD5Counter::~KMD5Counter()
{
	CloseHandle(m_hMutex);
}

KMD5Counter::KMD5Counter(KMD5DataSource *pSource) :	
	m_nProgress(0),
	m_pcSource(pSource),
	m_cMD5State(),
	m_bCancelPressed(false)
{
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
	MD5_Init(&m_cMD5State);
}

KMD5Counter::KMD5Counter() :	
	m_nProgress(0),
	m_pcSource(0),
	m_cMD5State(),
	m_bCancelPressed(false)
{
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
	MD5_Init(&m_cMD5State);
}

void KMD5Counter::SetDataSource(KMD5DataSource *pSource)
{
	m_pcSource = pSource;
}

bool KMD5Counter::IsCountingDone()
{
	return m_pcSource->EndOfData();
}

unsigned char* KMD5Counter::GetMD5()
{	
	KLock lock(m_hMutex);

	{
		if (m_bCancelPressed)
		{	
			return 0;
		}
	}

	unsigned char* res = new unsigned char[MD5_DIGEST_LENGTH];

	MD5_Final(res, &m_cMD5State);
	return res;
}

int KMD5Counter::GetProgress()
{	
	int tmp = 0;

	KLock lock(m_hMutex);
	
	tmp = m_nProgress;
	
	return tmp;
}


void KMD5Counter::StartCountingMD5()
{
	KMD5DataSource::DataPacket cPacket;

	while (!m_pcSource->EndOfData())
	{	
		cPacket = m_pcSource->GetNextDataPacket();

		MD5_Update(&m_cMD5State, cPacket.data, cPacket.length);

		KLock lock(m_hMutex);

		{
			m_nProgress = m_pcSource->GetProgress();

			if(m_bCancelPressed)
			{
				return;
			}
		}
	}
}

void KMD5Counter::Cancel()
{
	KLock lock(m_hMutex);

	m_bCancelPressed = true;	
}