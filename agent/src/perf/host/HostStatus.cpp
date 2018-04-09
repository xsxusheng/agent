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
#include "ProcInfo.h"







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



long CHostStatus::FetchMemorySize()
{
    unsigned long long total = 0;
    CMemUsage tMemUsage;

    tMemUsage.GetMemUsage();
    total = tMemUsage.GetMemTotal();
    total = total / (1024 * 1024);//MB
    return (long)total;
}



long CHostStatus::FetchMemoryUsed()
{
    unsigned long long used = 0;
    CMemUsage tMemUsage;

    tMemUsage.GetMemUsage();
    used = tMemUsage.GetMemUsed();
    used = used / (1024 * 1024);//MB
    return (long)used;
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



long CHostStatus::FetchMainFSDiskSize()
{
    return 0;
}



long CHostStatus::FetchDiskAvailableSize()
{
    return 0;
}



long CHostStatus::FetchDiskUsedSize()
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



string CHostStatus::GetProcArgs(long pid)
{
    unsigned long i = 0;
    unsigned long num = 0;
    string args("");
    CProcArgs procArgs;

    if (procArgs.GetProcArgs(pid) < 0)
    {
        return args;
    }

    num = procArgs.GetArgsNum();
    for (i = 0; i < num; i++)
    {
        args.append(procArgs.GetArgs(i));
        if (i < (num -1))
        {
            args.append(" ");
        }
    }
    return args;
}



string CHostStatus::GetProcState(long pid)
{
    char tState = 0;
    string state("STOP"); 
    CProcState procStat;

    if (procStat.GetProcState(pid) < 0)
    {
        state.assign("STOP");
        return state;
    }
    
    tState = procStat.GetState();
    switch(tState)
    {
        case PROC_STATE_SLEEP:
        {
            state.assign("SLEEP");
            break;
        }
        case PROC_STATE_RUN:
        {
            state.assign("RUN");
            break;
        }
        case PROC_STATE_STOP:
        {
            state.assign("STOP");
            break;
        }
        case PROC_STATE_ZOMBIE:
        {
            state.assign("ZOMBIE");
            break;
        }
        case PROC_STATE_IDLE:
        {
            state.assign("IDLE");
            break;
        }
        default:
        {
            state.assign("STOP");
            break;
        }
    }

    return state;
}



CProcCpu CHostStatus::GetProcCpu(long pid)
{
    CProcCpu tProcCpu;

    tProcCpu.GetProcCpu(pid);
    return tProcCpu;
}



CProcMem CHostStatus::GetProcMem(long pid)
{
    CProcMem tProcMem;

    tProcMem.GetProcMem(pid);
    return tProcMem;
}












