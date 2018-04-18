/**********************************************************
 * File: HostStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>

#include "ProcInfo.h"
#include "TimeUtils.h"

using namespace std;




#define DEF_FUMS_REPORT (15 * 60)




class CHostStatus
{
public:

    static int InitHostStatus();

    static int FetchCpuNum();
    static double GetCpuUsage();
    static double FetchCpuUsage();
    static string GetCpuUsageString();
    static string FetchCpuMonokaryonUsage();
    static int GetCpuMonokaryonUsage(double **pUsage, unsigned long *pOutLen);
    static int FetchCpuMonokaryonUsage(double **pUsage, unsigned long *pOutLen);
    static int FetchCpuFrequency();
    static string FetchCpuLoadAverage();


    static double GetMemUsage();
    static double FetchMemUsage();

    static long FetchMemorySize();
    static long FetchMemoryUsed();

    static double GetSwapUsage();
    static double FetchSwapUsage();

    static int GetDiskUsage();
    static int FetchDiskUsage();

    static int FetchDiskTotal();
    static int FetchMainFSDiskSize();
    static int FetchDiskAvailableSize();
    static int FetchDiskUsedSize();

    static string GetProcArgs(long pid);
    static string GetProcState(long pid);
    static CProcCpu GetProcCpu(long pid);
    static CProcMem GetProcMem(long pid);

    static int FetchNicUsage(long& rxSum, long& txSum);

    static string FetchSysDesc();
    static double FetchUpTime();

    static int GetTcpEstablished();
    static int FetchAllInputBandWidth();
    static int FetchAllOutputBandWidth();

private:


};














