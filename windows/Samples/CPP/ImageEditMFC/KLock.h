#pragma once

class KLock
{
public:
	KLock(HANDLE hMutex, bool bAutoLock = true) :
		m_hMutex(hMutex)
	{
		if(bAutoLock)
		{
			Lock();
		}
	}

	virtual ~KLock()
	{
		Unlock();
	}

	void Lock()
	{
		WaitForSingleObject(m_hMutex, INFINITE);
	}

	void Unlock()
	{
		ReleaseMutex(m_hMutex);
	}

private:
	HANDLE	m_hMutex;
};