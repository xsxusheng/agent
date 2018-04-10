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
#include "StringUtils.h"
#include "SystemInfo.h"
#include "Uptime.h"




int CHostStatus::FetchCpuNum()
{
    CCpuInfoList tCpuInfo;
    return (int)tCpuInfo.GetCpuInfoNum();
}



double CHostStatus::GetCpuUsage()
{
    CCpuUsage tCpuUsage;

    return tCpuUsage.GetCpuUsageTotal();
}



double CHostStatus::FetchCpuUsage()
{
    CCpuUsage tCpuUsage;

    return tCpuUsage.GetCpuUsageTotal();
}


string CHostStatus::GetCpuUsageString()
{
    CCpuUsage tCpuUsage;

    return tCpuUsage.GetCpuUsageString();
}



string FetchCpuMonokaryonUsage()
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


int CHostStatus::FetchCpuMonokaryonUsage(double **pUsage, unsigned long *pOutLen)
{
    CCpuUsage tCpuUsage;

    if (pUsage == NULL || pOutLen == NULL)
    {
        return -1;
    }

    return tCpuUsage.GetCpuPercsUsage(pUsage, pOutLen);
}



int CHostStatus::FetchCpuFrequency()
{
    CCpuInfoList tCpuList;

    tCpuList.GetCpuInfoList();
    return tCpuList.GetCpuInfo(0)->GetMhz();
}



string CHostStatus::FetchCpuLoadAverage()
{
    int i = 0;
    string total("");
    CLoadAvg tLoadAvg;

    tLoadAvg.GetLoadAvgInfo();
    for (i = 0; i < MAX_LOAD_AVG_NUM; i++)
    {
        total.append(CString::ToString(tLoadAvg.GetLoadAvg(i)));
        if (i < (MAX_LOAD_AVG_NUM - 1))
        {
            total.append(",");
        }
    }

    return total;
}




double CHostStatus::GetMemUsage()
{
    double usage = 0.0;
    CMemUsage tMemUsage;

    tMemUsage.GetMemUsage();
    usage = tMemUsage.GetMemFreePercent();
    return usage;
}



double CHostStatus::FetchMemUsage()
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
    return FetchSwapUsage();
}




double CHostStatus::FetchSwapUsage()
{
    double usage = 0.0;
    CSwapUsage tSwapUsage;

    tSwapUsage.GetSwapUsage();
    if (tSwapUsage.GetTotal() > 0)
    {
        usage = (double)(tSwapUsage.GetUsed()) / (double)(tSwapUsage.GetTotal());
    }

    usage = usage * 100;
    return usage;
}



int CHostStatus::FetchDiskTotal()
{
    unsigned long i = 0;
    unsigned long total = 0;

    CFileSystem tFileSystem;

    tFileSystem.GetFileSystem();
    for (i = 0; i < tFileSystem.GetFileSystemNum(); i++)
    {
        total += tFileSystem.GetFileSystemInfo(i)->GetFileSysTotal();
    }

    return (int)(total / (1024 * 1024)); /*GB*/
}



int CHostStatus::GetDiskUsage()
{
    return FetchDiskUsage();
}



int CHostStatus::FetchDiskUsage()
{
    double usage = 0.0;

    int mainFSTotalSize = FetchMainFSDiskSize();
    int mainFSAvailableSize = FetchDiskAvailableSize();
    int mainFSUsedSize = mainFSTotalSize - mainFSAvailableSize;

    usage = (double)mainFSUsedSize / (double)mainFSTotalSize;
    return (int)(usage * 100);
}



int CHostStatus::FetchMainFSDiskSize()
{
    unsigned long i = 0;
    unsigned long total = 0;
    CFileSystem tFileSystem;

    tFileSystem.GetFileSystem();
    for (i = 0; i < tFileSystem.GetFileSystemNum(); i++)
    {
        if (tFileSystem.GetFileSystemInfo(i)->GetFileSystemType() == FSTYPE_LOCAL_DISK)
        {
            total += tFileSystem.GetFileSystemInfo(i)->GetFileSysTotal();
        }
    }

    return (int)(total / (1024 * 1024)); /*GB*/
}



int CHostStatus::FetchDiskAvailableSize()
{
    unsigned long i = 0;
    unsigned long total = 0;
    CFileSystem tFileSystem;

    tFileSystem.GetFileSystem();
    for (i = 0; i < tFileSystem.GetFileSystemNum(); i++)
    {
        if (strcmp(tFileSystem.GetFileSystemInfo(i)->GetDirName(), "identifier") == 0)
        {
            continue;
        }
        
        if (tFileSystem.GetFileSystemInfo(i)->GetFileSystemType() == FSTYPE_LOCAL_DISK)
        {
            total += tFileSystem.GetFileSystemInfo(i)->GetFileSysAvail();
        }
    }

    return (int)(total / (1024 * 1024)); /*GB*/
}



int CHostStatus::FetchDiskUsedSize()
{
    return FetchMainFSDiskSize() - FetchDiskAvailableSize();
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




string CHostStatus::FetchSysDesc()
{
    CSystemInfo os;

    os.GetName();
    return string("-os") + os.GetName() + " -arch" + os.GetArch() + " -desc" + os.GetDesc() + " -agent version:";
}




double CHostStatus::FetchUpTime()
{
    CUptime uptime;
    return uptime.GetUptime();
}



int CHostStatus::GetTcpEstablished()
{
    CNetStat tNetStat;

    tNetStat.GetNetStat();
    return tNetStat.GetTcpStates(TCP_ESTABLISHED);
}



int CHostStatus::FetchAllInputBandWidth()
{
    CNetStat tNetStat;

    tNetStat.GetNetStat();
    return tNetStat.GetAllInboundTotal();
}



int CHostStatus::FetchAllOutputBandWidth()
{
    CNetStat tNetStat;

    tNetStat.GetNetStat();
    return tNetStat.GetAllOutboundTotal();
}













