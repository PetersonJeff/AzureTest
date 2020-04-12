#pragma once

#if !defined (WIN32) && !defined (WIN64)
#  include <pthread.h>
#endif

class UtilMutex
{
public:
	UtilMutex();
	~UtilMutex();

	void lock();
	void unlock();

protected:
	void* _mutex;

#if !defined (WIN32) && !defined (WIN64)
	pthread_t _threadID;  // required for pthread mutex
#endif
	
};

class UtilAutoLock
{
public:
	UtilAutoLock(UtilMutex& inMutex)
	{
		m_mutex = &inMutex;
		m_mutex->lock();
		m_locked = true;
	}

	~UtilAutoLock()
	{
		if (m_locked)
			m_mutex->unlock();
	}

	void lock()
	{
		m_mutex->lock();
		m_locked = true;
	}

	void unlock()
	{
		if (m_locked)
			m_mutex->unlock();
		m_locked = false;
	}

private:
	UtilMutex* m_mutex;
	bool       m_locked;
};

