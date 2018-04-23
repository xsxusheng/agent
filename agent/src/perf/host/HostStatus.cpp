/**********************************************************
 * File: HostStatus.cpp
 * Function: 
 *********************************************************/
#include "HostStatus.h"
#include "sv_log.h"
#include "CpuUsage.h"
#include "MemUsage.h"
#include "SwapUsage.h"
#include "FileSystem.h"
#include "NetInterface.h"
#include "ProcInfo.h"
#include "StringUtils.h"
#include "SystemInfo.h"
#include "Uptime.h"






int CHostStatus::InitHostStatus()
{
    if (CSigar::InitSigar() < 0)
    {
        SV_FATAL("Init Sigar adapter failed...");
        return -1;
    }

    SV_LOG("Init Sigar adapter success...");
    return 0;
}



int CHostStatus::FetchCpuNum()
{
    CCpuInfoList tCpuInfo;
    return (int)tCpuInfo.GetCpuInfoNum();
}



double CHostStatus::GetCpuUsage()
{
    double usage = 0.0;
    CCpuUsage tCpuUsage;

    usage = tCpuUsage.GetCpuUsageTotal();
    usage = (double)((int)(usage * 1000.0) / 10); /*放大100倍，精度1位*/
    return usage;
}



double CHostStatus::FetchCpuUsage()
{
    return GetCpuUsage();
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
    int ret = 0;
    unsigned long i = 0;
    CCpuUsage tCpuUsage;

    if (pUsage == NULL || pOutLen == NULL)
    {
        SV_ERROR("Input para is null.");
        return -1;
    }

    ret = tCpuUsage.GetCpuPercsUsage(pUsage, pOutLen);
    if (((*pUsage) == NULL) || (*pOutLen <= 0))
    {
        SV_ERROR("GetCpuPercsUsage pOutlen(%lu) error.", (*pOutLen));
        ret = -1;
    }
    
    for (i = 0; i < *pOutLen; i++)
    {
        (*pUsage)[i] = (double)((int)((*pUsage)[i] * 1000.0) / 10); /*放大100倍，精度1位*/
    }
    return ret;
}


int CHostStatus::FetchCpuMonokaryonUsage(double **pUsage, unsigned long *pOutLen)
{
    return GetCpuMonokaryonUsage(pUsage, pOutLen);
}



int CHostStatus::FetchCpuFrequency()
{
    CCpuInfoList tCpuList;

    if (tCpuList.GetCpuInfoList() < 0)
    {
        SV_ERROR("GetCpuInfoList error.");
        return 0;
    }
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
    usage = tMemUsage.GetMemUsedPercent();
    return usage;
}



double CHostStatus::FetchMemUsage()
{
    double usage = 0.0;
    CMemUsage tMemUsage;

    tMemUsage.GetMemUsage();
    usage = tMemUsage.GetMemUsedPercent();
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

    usage = usage * 100.0;
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













