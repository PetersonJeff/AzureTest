#include "pch.h"
#include "UtilMutex.h"

#include <cstdlib>

#if defined (WIN32) || defined (WIN64)
#  include <process.h>
#  include <windows.h>
#else
#  include <stdlib.h>
#  include <unistd.h>
#  include <sched.h>
#  include <errno.h>
#endif


UtilMutex::UtilMutex() {
#if defined (WIN32) || defined (WIN64)
	_mutex = malloc(sizeof(CRITICAL_SECTION));
	::InitializeCriticalSection((CRITICAL_SECTION*)_mutex);
#else
	m_mutex = ::malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((pthread_mutex_t*)m_mutex, NULL);
	m_threadID = 0;
#endif
}


UtilMutex::~UtilMutex() {
#if defined (WIN32) || defined (WIN64)
	::DeleteCriticalSection((CRITICAL_SECTION*)_mutex);
#else
	pthread_mutex_destroy((pthread_mutex_t*)m_mutex);
#endif
	::free(_mutex);
}


void UtilMutex::lock() {
#if defined (WIN32) || defined (WIN64)
	::EnterCriticalSection((CRITICAL_SECTION*)_mutex);
#else
	//
	// See if the mutex is already locked by anyone,
	// if not this call will lock it.
	//
	if (pthread_mutex_trylock((pthread_mutex_t*)m_mutex) == EBUSY) {
		//
		// Make sure that current thread has not already locked
		// the mutex...
		//
		if (pthread_equal(m_threadID, pthread_self())) {
			return;
		}

		//
		// Attempt to lock the mutex in this thread ...
		//

		pthread_mutex_lock((pthread_mutex_t*)m_mutex);

		m_threadID = pthread_self();

		return;
	}
	else {
		//
		// If mutex wasn't busy, trylock() locked it ...
		// 
		m_threadID = pthread_self();
	}
#endif
}


void UtilMutex::unlock() {
#if defined (WIN32) || defined (WIN64)
	::LeaveCriticalSection((CRITICAL_SECTION*)_mutex);
#else
	m_threadID = 0;		// set the threadid to 0 for lock
	pthread_mutex_unlock((pthread_mutex_t*)m_mutex);
#endif
}
