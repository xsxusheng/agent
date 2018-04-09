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
    CSchedulerActiveJob();
    ~CSchedulerActiveJob();


    int AddJob(CTimerBase *pObj, long timeout);
    int InitJob();



private:
    CTimer m_timerJob;

};



























