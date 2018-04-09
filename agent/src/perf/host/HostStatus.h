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

    static bool NeedReportFums();


    static double GetCpuUsage();
    static string GetCpuUsageString();
    static int GetCpuMonokaryonUsage(double **pUsage, unsigned long *pOutLen);

    static double GetMemUsage();
    static double GetSwapUsage();
    static double GetDiskUsage();

    static long FetchMemorySize();
    static long FetchMemoryUsed();
    static long FetchMainFSDiskSize();
    static long FetchDiskAvailableSize();
    static long FetchDiskUsedSize();

    static string GetProcArgs(long pid);
    static string GetProcState(long pid);
    static CProcCpu GetProcCpu(long pid);
    static CProcMem GetProcMem(long pid);

    static int FetchNicUsage(long& rxSum, long& txSum);

private:


};














