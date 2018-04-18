/**********************************************************
 * File: SchedulerActiveJob.cpp
 * Function: 
 *********************************************************/
#include "SchedulerActiveJob.h"
#include "sv_log.h"
#include "CpuMonokaryonUsageScalar.h"
#include "CpuUsageScalar.h"
#include "MainFSDiskUsageScalar.h"
#include "MemoryUsageScalar.h"
#include "SwapUsageScalar.h"
#include "HostStatic.h"
#include "ProcessStatic.h"
#include "DiskStatic.h"
#include "IfStatic.h"
#include "DiskHealthStatus.h"
#include "PerformanceDataCollect.h"
#include "DnsRedirectRequest.h"






CSchedulerActiveJob* CSchedulerActiveJob::sm_schedulerJob = NULL;





CSchedulerActiveJob::CSchedulerActiveJob()
{
}


CSchedulerActiveJob::~CSchedulerActiveJob()
{
}




CSchedulerActiveJob* CSchedulerActiveJob::GetInstance()
{
    if (sm_schedulerJob == NULL)
    {
        sm_schedulerJob = new CSchedulerActiveJob();
        if (sm_schedulerJob == NULL)
        {
            SV_ERROR("New CSchedulerActiveJob error...");
            return NULL;
        }

        /*启动定时器*/
        sm_schedulerJob->InitTimer();
        SV_LOG("Init scheduler timer success ...");

        /*启动定时器任务*/
        sm_schedulerJob->InitJob();
        SV_LOG("Init scheduler job success ...");
    }
    
    return sm_schedulerJob;
}



int CSchedulerActiveJob::InitTimer()
{
    m_timerJob.Start();
    return 0;
}




int CSchedulerActiveJob::AddJob(CTimerBase *pObj, long timeout)
{
    m_timerJob.TimerStart(pObj, timeout);
    return 0;
}



int CSchedulerActiveJob::InitJob()
{
    /*USAGE信息*/
    AddJob(new CCpuUsageScalar(), DEF_SCALAR_PERIOD);
    AddJob(new CMemUsageScalar(), DEF_SCALAR_PERIOD);
    AddJob(new CMainFSDiskUsageScalar(), DEF_SCALAR_PERIOD);
    AddJob(new CSwapUsageScalar(), DEF_SCALAR_PERIOD);
    AddJob(new CCpuMonokaryonUsageScalar(), DEF_SCALAR_PERIOD);

    /*JOB信息*/
    AddJob(new CHostStatic(), DEF_JOB_PERIOD);
    AddJob(new CProcessStatic(), DEF_JOB_PERIOD);
    AddJob(new CDiskStatic(), DEF_JOB_PERIOD);
    AddJob(new CIfStatic(), DEF_JOB_PERIOD);
    AddJob(new CDiskHealthStatus(), DEF_JOB_PERIOD);
    AddJob(new CPerformanceDataCollect(), DEF_JOB_PERIOD);
    AddJob(new CDnsRedirectRequest(), DEF_JOB_PERIOD);

    return 0;
}






























