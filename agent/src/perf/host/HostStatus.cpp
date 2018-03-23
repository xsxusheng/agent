/**********************************************************
 * File: HostStatus.cpp
 * Function: 
 *********************************************************/
#include "HostStatus.h"
#include "CpuUsage.h"
#include "MemUsage.h"
#include "SwapUsage.h"
#include "FileSystem.h"
#include "NetInterface.h"



double CHostStatus::GetCpuUsage()
{
    CCpuUsage tCpuUsage;

    return tCpuUsage.GetCpuUsageTotal();
}


string CHostStatus::GetCpuUsageString()
{
    CCpuUsage tCpuUsage;

    return tCpuUsage.GetCpuUsageString();
}


int CHostStatus::GetCpuMonokaryonUsage(double **pUsage, unsigned long *pOutLen)
{
    CCpuUsage tCpuUsage;

    if (pUsage == NULL || pOutLen == NULL)
    {
        return -1;
    }

    return tCpuUsage.GetCpuPercsUsage(pUsage, pOutLen);
}



double CHostStatus::GetMemUsage()
{
    double usage = 0.0;
    CMemUsage tMemUsage;

    tMemUsage.GetMemUsage();
    usage = tMemUsage.GetMemFreePercent();
    return usage;
}



int CHostStatus::FetchMemorySize()
{
    unsigned long long total = 0;
    CMemUsage tMemUsage;

    tMemUsage.GetMemUsage();
    total = tMemUsage.GetMemTotal();
    total = total / (1024 * 1024);//MB
    return (int)total;
}




double CHostStatus::GetSwapUsage()
{
    int usage = 0.0;
    CSwapUsage tSwapUsage;

    tSwapUsage.GetSwapUsage();
    if (tSwapUsage.GetTotal() > 0)
    {
        usage = (double)((tSwapUsage.GetUsed() * 1.0) / (tSwapUsage.GetTotal() * 1.0));
    }

    usage = (double)((int)(usage * 100) / 100.0);
    return usage;
}



double CHostStatus::GetDiskUsage()
{
    int usage = 0;
    double avail = 0.0;
    double total = 0.0;
    CFileSystem tFileSystem;

    tFileSystem.GetFileSystem();
    total = (double)tFileSystem.GetFileSysTotal();
    avail = (double)tFileSystem.GetFileSysAvail();

    if (total > 0)
    {
        usage = (total - avail) / total;
    }

    usage = (double)((int)(usage * 100) / 100.0);
    return usage;
}



int CHostStatus::FetchMainFSDiskSize()
{
    return 0;
}



int CHostStatus::FetchNicUsage(long& rxSum, long& txSum)
{
    unsigned long i = 0;
    unsigned long cnt = 0;
    unsigned long num = 0;
    unsigned long long rx = 0;
    unsigned long long tx = 0;
    CNetInterface tNetIf;
    
    tNetIf.GetNetIfStatus();
    num = tNetIf.GetNetIfNum();
    for(i = 0; i < num; i++)
    {
        if (strcmp(tNetIf.GetNetIfStat(i)->GetIfName(), NIC_LOCAL_LOOPBACK) == 0)
        {
            continue;
        }
        rx += tNetIf.GetNetIfStat(i)->GetRxBytes();
        tx += tNetIf.GetNetIfStat(i)->GetTxBytes();
        cnt++;
    }

    rxSum = (long)(rx / cnt) / 1024L;
    txSum = (long)(tx / cnt) / 1024L;
    return 0;
}










