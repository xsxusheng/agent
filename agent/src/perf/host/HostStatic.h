/**********************************************************
 * File: HostStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <list>
#include "Timer.h"
#include "TimeUtils.h"

using namespace std;


#define CPU_PEROID 5



#define DEF_HOST_STATIC_REPORT (15 * 60)

class CHostStatic : public CTimerBase
{
public:
    CHostStatic();
    ~CHostStatic();


    void Run();
    bool NeedReportFums();


    void StartFetchData();
    void SendToFums();


    void AddCpuUsage(double usage);
    void AddMemUsage(double usage);
    void AddMemTotal(int total);
    void AddIfUsage(long rxUsage, long txUsage);


    void CalcCpuAveUsage();
    void CalcMemAveUsage();
    void CalcIfAveUsage();
    void CalcMemTotal();

    void CalcMaxCpuUsage();
    void CalcMaxMemUsage();

    void CalcMaxContinueTime();


    void ClearCpuUsageList(){m_cpuUsageList.clear();}
    void ClearMemUsageList(){m_memUsageList.clear();}
    void ClearMemTotalList(){m_memTotalList.clear();}
    void ClearIfUsageList(){m_rxUsageList.clear();m_txUsageList.clear();}


private:

    CTime m_lastReportFums;

    list<double> m_cpuUsageList;
    list<double> m_memUsageList;
    list<int> m_memTotalList;
    
    list<long> m_rxUsageList;
    list<long> m_txUsageList;

    double m_fCpuUsageAve;
    double m_fMemUsageAve;
    double m_nMemTotalAve;

    double m_fMaxCpuUsage;
    double m_fMaxMemUsage;

    long m_nRxUsageAve;
    long m_nTxUsageAve;

    int m_nMaxContinueTime;
    int m_nTcpLinkNum;
    int m_nTcpInboundTotal;
    int m_nTcpOutboundTotal;
};


























