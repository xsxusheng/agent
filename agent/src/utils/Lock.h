/**********************************************************
 * File: Lock.h
 * Function: 
 *********************************************************/
#pragma once

#include <pthread.h>





class CLock
{
public:
    CLock(){};
    virtual ~CLock(){};

    virtual int Lock() = 0;
    virtual int UnLock() = 0;
    virtual int TryLock() = 0;

private:

};




class CMutex : public CLock
{
public:
    CMutex();
    virtual ~CMutex();


    virtual int Lock();
    virtual int UnLock();
    virtual int TryLock();

private:
    pthread_mutex_t m_lock;

};




class CRWLock : public CLock
{
public:
    CRWLock();
    virtual ~CRWLock();


    virtual int Lock();
    virtual int WrLock();
    virtual int RdLock();
    virtual int UnLock();
    virtual int TryLock();
    virtual int TryWrLock();
    virtual int TryRdLock();
    virtual int TimeRdLock(long ms);
    virtual int TimeWrLock(long ms);
  

private:
    pthread_rwlock_t m_lock;

};




class CSpinLock : public CLock
{
public:
    CSpinLock();
    virtual ~CSpinLock();


    virtual int Lock();
    virtual int UnLock();
    virtual int TryLock();

private:
    pthread_spinlock_t m_lock;

};













