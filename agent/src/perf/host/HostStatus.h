/**********************************************************
 * File: HostStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>

using namespace std;







class CHostStatus
{
public:

    static double GetCpuUsage();
    static string GetCpuUsageString();
    static int GetCpuMonokaryonUsage(double **pUsage, unsigned long *pOutLen);

    static double GetMemUsage();
    static double GetSwapUsage();
    static double GetDiskUsage();

    static int FetchMemorySize();
    static int FetchMainFSDiskSize();

    static int FetchNicUsage(long& rxSum, long& txSum);

private:


};














