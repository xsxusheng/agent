/**********************************************************
 * File: DiskHealthStatus.h.h
 * Function: 
 *********************************************************/
#pragma once

#include <list>
#include "Timer.h"

using namespace std;



#define DISK_HEALTH_SCRIPT1 "./diskinfo"
#define DISK_HEALTH_SCRIPT2 "./diskinfo2"

#define DEF_DISK_HEALTH_REPORT (15 * 60)


class CDiskHealthStatus : public CTimerBase
{
public:
    CDiskHealthStatus();
    ~CDiskHealthStatus();



    void Run();

    void SendToFums();

    bool NeedReportFums();


private:

    CTime m_lastReportFums;

};































