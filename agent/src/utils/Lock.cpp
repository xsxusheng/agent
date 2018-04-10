/**********************************************************
 * File: Lock.cpp
 * Function: 
 *********************************************************/

#include "Lock.h"





CMutex::CMutex()
{
    pthread_mutex_init(&m_lock, NULL);
}


CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_lock);
}


int CMutex::Lock()
{
    return pthread_mutex_lock(&m_lock);
}


int CMutex::UnLock()
{
    return pthread_mutex_unlock(&m_lock);
}


int CMutex::TryLock()
{
    return pthread_mutex_trylock(&m_lock);
}



#if 0
#endif



CRWLock::CRWLock()
{
    pthread_rwlock_init(&m_lock, NULL);
}


CRWLock::~CRWLock()
{
    pthread_rwlock_destroy(&m_lock);
}


int CRWLock::Lock()
{
    return pthread_rwlock_wrlock(&m_lock);
}


int CRWLock::WrLock()
{
    return pthread_rwlock_wrlock(&m_lock);
}


int CRWLock::RdLock()
{
    return pthread_rwlock_rdlock(&m_lock);
}


int CRWLock::UnLock()
{
    return pthread_rwlock_unlock(&m_lock);
}


int CRWLock::TryLock()
{
    return pthread_rwlock_trywrlock(&m_lock);
}


int CRWLock::TryWrLock()
{
    return pthread_rwlock_trywrlock(&m_lock);
}


int CRWLock::TryRdLock()
{
    return pthread_rwlock_tryrdlock(&m_lock);
}

int CRWLock::TimeRdLock(long ms)
{
	struct timespec timeout;
	timeout.tv_nsec = ms*1000;
	return pthread_rwlock_timedrdlock(&m_lock, &timeout);
}

int CRWLock::TimeWrLock(long ms)
{
	struct timespec timeout;
	timeout.tv_nsec = ms*1000;
	return pthread_rwlock_timedwrlock(&m_lock, &timeout);
}


#if 0
#endif



CSpinLock::CSpinLock()
{
    pthread_spin_init(&m_lock, 0);
}


CSpinLock::~CSpinLock()
{
    pthread_spin_destroy(&m_lock);
}


int CSpinLock::Lock()
{
    return pthread_spin_lock(&m_lock);
}


int CSpinLock::UnLock()
{
    return pthread_spin_unlock(&m_lock);
}


int CSpinLock::TryLock()
{
    return pthread_spin_trylock(&m_lock);
}






