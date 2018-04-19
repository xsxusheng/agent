/**********************************************************
 * File: HostStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>

#include "Timer.h"

using namespace std;




#define DEF_JOB_PERIOD 60


class CSchedulerActiveJob
{
public:

    static CSchedulerActiveJob* GetInstance();
    static void ReleaseInstance();

    int AddJob(CTimerBase *pObj, long timeout);
    int InitJob();


protected:
    CSchedulerActiveJob();
    ~CSchedulerActiveJob();

    int InitTimer();


private:
    CTimer m_timerJob;

    static CSchedulerActiveJob* sm_schedulerJob;

};



























