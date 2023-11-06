#pragma once

class KCriticalSection
{
private:
	KCriticalSection(const KCriticalSection&);

public:
	KCriticalSection()
	{
		InitializeCriticalSection(&m_hHandle);
	}

	~KCriticalSection()
	{
		Lock();
		UnLock();
		DeleteCriticalSection(&m_hHandle);
	}

	DWORD Lock(DWORD dwMilliseconds = INFINITE) const
	{
		EnterCriticalSection(&const_cast<KCriticalSection*>(this)->m_hHandle);
		return 0;
	}

	DWORD UnLock() const
	{
		LeaveCriticalSection(&const_cast<KCriticalSection*>(this)->m_hHandle);
		return 0;
	}

	const CRITICAL_SECTION & GetHandle()
	{
		return m_hHandle;
	}

private:
	CRITICAL_SECTION m_hHandle;	
};
