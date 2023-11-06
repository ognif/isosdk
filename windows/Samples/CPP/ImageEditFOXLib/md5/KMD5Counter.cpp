#include "stdafx.h"
#include "KMD5Counter.h"

FX::FXint KMD5Counter::run()
{
	StartCountingMD5();
	return 1;
}

KMD5Counter::~KMD5Counter()
{}

KMD5Counter::KMD5Counter(KMD5DataSource *pSource) :
	m_cMutex(),
	m_nProgress(0),
	m_pcSource(pSource),
	m_cMD5State(),
	m_bCancelPressed(false)
{	
	MD5_Init(&m_cMD5State);
}

KMD5Counter::KMD5Counter() :
	m_cMutex(),
	m_nProgress(0),
	m_pcSource(0),
	m_cMD5State(),
	m_bCancelPressed(false)
{	
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
	
	m_cMutex.lock();
	{
		if(m_bCancelPressed)
		{
			m_cMutex.unlock();
			return 0;
		}
	}
	m_cMutex.unlock();

	unsigned char* res = new unsigned char[MD5_DIGEST_LENGTH];

	MD5_Final(res, &m_cMD5State);
	return res;
}

int KMD5Counter::GetProgress()
{	
	int tmp = 0;
	m_cMutex.lock();
	tmp = m_nProgress;
	m_cMutex.unlock();
	
	return tmp;
}


void KMD5Counter::StartCountingMD5()
{
	KMD5DataSource::DataPacket cPacket;

	while(!m_pcSource->EndOfData())
	{	
		cPacket = m_pcSource->GetNextDataPacket();

		MD5_Update(&m_cMD5State, cPacket.data, cPacket.length);

		m_cMutex.lock();

		{
			m_nProgress = m_pcSource->GetProgress();

			if(m_bCancelPressed)
			{
				m_cMutex.unlock();
				return;
			}
		}

		m_cMutex.unlock();
	}
}

void KMD5Counter::Cancel()
{
	m_cMutex.lock();
	m_bCancelPressed = true;
	m_cMutex.unlock();
}
