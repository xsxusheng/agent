/**********************************************************
 * File: PerformanceDataCollect.h
 * Function: 
 *********************************************************/
#pragma once

#include <cstring>
#include <string>

#include "Timer.h"
#include "TimeUtils.h"

#include "MacroDefine.h"



#define DEF_PERF_DATA_COLLECT_REPORT (15 * 60)


class CPerformanceDataCollect : public CTimerBase
{
public:
    CPerformanceDataCollect();
    ~CPerformanceDataCollect();


    void Run();

    void SendDeviceDiskAlarm(int diskUsage, string& ne);


    static int GetSeq();


private:
    static int m_sSeq;
    CTime m_lastReportFums;


};












