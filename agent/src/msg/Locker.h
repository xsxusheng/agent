/*************************************************************************
	> File Name: locker.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月14日 星期三 15时36分40秒
 ************************************************************************/

#ifndef _LOCKER_H
#define _LOCKER_H
#include <pthread.h>
#include "../utils/sv_log.h"

class Locker 
{ 
public: 
    inline Locker()
    {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        if(0 != pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE))
        {
            SV_LOG("pthread_mutexattr_settype error. ");
        }
        
        pthread_mutex_init(&mutex, &attr);
        pthread_mutexattr_destroy(&attr);
    } 
    inline ~Locker()
    {
        pthread_mutex_destroy(&mutex);
    } 
    inline void lock()
    {
        pthread_mutex_lock(&mutex);
    } 
    inline void unlock()
    {
        pthread_mutex_unlock(&mutex);
    } 
private: 
    pthread_mutex_t mutex; 
};

#endif
