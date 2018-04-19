/**********************************************************
 * File: HostStatic.cpp
 * Function: 
 *********************************************************/
#include "HostStatic.h"
#include "Perf.pb.h"
#include "HostStatus.h"

#include "AmqpReceiveBuilder.h"
#include "AmqpMessageReceiveProcessor.h"
#include "AmqpMessageSendProcessor.h"
#include "ProtoBufPacker.h"

using namespace com::fiberhome::fums::proto;



CHostStatic::CHostStatic()
{
    m_fCpuUsageAve = 0.0;
    m_fMemUsageAve = 0.0;
    m_nMemTotalAve = 0.0;

    m_fMaxCpuUsage = 0.0;
    m_fMaxMemUsage = 0.0;

    m_nDiskUsage = 0;
    m_nDiskTotal = 0;

    m_nRxUsageAve = 0;
    m_nTxUsageAve = 0;

    m_nMaxContinueTime = 0;
    m_nTcpLinkNum = 0;
    m_nTcpInboundTotal = 0;
    m_nTcpOutboundTotal = 0;

    m_cpuUsageList.clear();
    m_memUsageList.clear();
    m_memTotalList.clear();
    m_rxUsageList.clear();
    m_txUsageList.clear();
    m_lastReportFums.GetTimeNow();
}



CHostStatic::~CHostStatic()
{
    m_cpuUsageList.clear();
    m_memUsageList.clear();
    m_memTotalList.clear();
    m_rxUsageList.clear();
    m_txUsageList.clear();
}



void CHostStatic::Run()
{
    StartFetchData();

    /*文件生成周期为15分钟*/
    if (NeedReportFums())
    {
        SendToFums();
    }
}



bool CHostStatic::NeedReportFums()
{
    CTime tNow;

    if (tNow.DiffSec(m_lastReportFums) >= DEF_HOST_STATIC_REPORT)
    {
        /*重置上次上报时间*/
        m_lastReportFums = tNow;
        return true;
    }
    return false;
}




void CHostStatic::StartFetchData()
{
    long rxSum = 0;
    long txSum = 0;

    AddCpuUsage(CHostStatus::GetCpuUsage());
    AddMemUsage(CHostStatus::GetMemUsage());
    AddMemTotal((int)CHostStatus::FetchMemorySize());

    CHostStatus::FetchNicUsage(rxSum,  txSum);
    AddIfUsage(rxSum, txSum);
}


void CHostStatic::SendToFums()
{
    string timeNow;
    Hostdata data;

    /*计算平均占用率*/
    CalcCpuAveUsage();
    CalcMemAveUsage();
    CalcIfAveUsage();
    CalcMemTotal();

    /*计算峰值*/
    CalcMaxCpuUsage();
    CalcMaxMemUsage();

    /*计算峰值持续时间*/
    CalcMaxContinueTime();

    m_nDiskUsage = CHostStatus::GetDiskUsage();
    m_nDiskTotal = CHostStatus::FetchMainFSDiskSize();


    CTime::GetTimeNowStr(timeNow);
    data.set_querytime(timeNow);
    data.set_cpuaveusage(m_fCpuUsageAve);
    data.set_cpumaxusge(m_fMaxCpuUsage);
    data.set_maxcontiuetime(m_nMaxContinueTime);
    data.set_memusageave(m_fMemUsageAve);
    data.set_rxflowave(m_nRxUsageAve);
    data.set_txflowave(m_nTxUsageAve);
    data.set_tcplinknum(m_nTcpLinkNum);
    data.set_tcpinboundtotal(m_nTcpInboundTotal);
    data.set_tcpoutboundtotal(m_nTcpOutboundTotal);
    data.set_memtotal(m_nMemTotalAve);
    data.set_diskusage(m_nDiskUsage);
    data.set_memmaxusage(m_fMaxMemUsage);
    data.set_disktotal(m_nDiskTotal);

    SV_INFO("HOST_STATIC: TimeNow=%s, CpuUsage=%f, CpuUsageMax=%f, ContTime=%d, MemUsage=%f, MemUsageMax=%f, "
        "MemTotal=%f, DiskUsage=%d, DiskTotal=%d, RxUsage=%ld, TxUsage=%ld, TcpLink=%d, TcpInTotal=%d, TcpOutTotal=%d.",
        timeNow.c_str(), m_fCpuUsageAve, m_fMaxCpuUsage, m_nMaxContinueTime, m_fMemUsageAve, m_fMaxMemUsage,
        m_nMemTotalAve, m_nDiskUsage, m_nDiskTotal, m_nRxUsageAve, m_nTxUsageAve, m_nTcpLinkNum, m_nTcpInboundTotal, m_nTcpOutboundTotal);

    /*发送消息*/
    Major major = ProtoBufPacker::PackPerfEntity(ProtoBufPacker::SerializeToArray<Hostdata>(data), PerfData::HOST_TYPE);
    AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);


    /*清空当前信息*/
    ClearCpuUsageList();
    ClearMemUsageList();
    ClearMemTotalList();
    ClearIfUsageList();
}



void CHostStatic::AddCpuUsage(double usage)
{
    m_cpuUsageList.push_back(usage);
}


void CHostStatic::AddMemUsage(double usage)
{
    m_memUsageList.push_back(usage);
}


void CHostStatic::AddMemTotal(int total)
{
    m_memTotalList.push_back(total);
}


void CHostStatic::AddIfUsage(long rxUsage, long txUsage)
{
    m_rxUsageList.push_back(rxUsage);
    m_txUsageList.push_back(txUsage);
}



void CHostStatic::CalcCpuAveUsage()
{
    double sum = 0.0;
    list<double>::iterator it;

    m_fCpuUsageAve = 0.0;
    for (it = m_cpuUsageList.begin(); it != m_cpuUsageList.end(); it++)
    {
        sum += *it;
    }
    m_fCpuUsageAve = sum / m_cpuUsageList.size();
}


void CHostStatic::CalcMemAveUsage()
{
    double sum = 0.0;
    list<double>::iterator it;

    m_fMemUsageAve = 0.0;
    for (it = m_memUsageList.begin(); it != m_memUsageList.end(); it++)
    {
        sum += *it;
    }
    m_fMemUsageAve = sum / m_memUsageList.size();
}


void CHostStatic::CalcIfAveUsage()
{
    double sum = 0.0;
    list<long>::iterator it;

    m_nRxUsageAve = 0.0;
    for (it = m_rxUsageList.begin(); it != m_rxUsageList.end(); it++)
    {
        sum += *it;
    }
    m_nRxUsageAve = sum / m_rxUsageList.size();

    m_nTxUsageAve = 0.0;
    for (it = m_txUsageList.begin(); it != m_txUsageList.end(); it++)
    {
        sum += *it;
    }
    m_nTxUsageAve = sum / m_txUsageList.size();
}


void CHostStatic::CalcMemTotal()
{
    int sum = 0;
    list<int>::iterator it;

    m_nMemTotalAve = 0.0;
    for (it = m_memTotalList.begin(); it != m_memTotalList.end(); it++)
    {
        sum += *it;
    }
    m_nMemTotalAve = sum / m_memTotalList.size();
}


void CHostStatic::CalcMaxCpuUsage()
{
    m_fMaxCpuUsage = 0.0;
    list<double>::iterator it;

    m_fMaxCpuUsage = 0.0;
    for (it = m_cpuUsageList.begin(); it != m_cpuUsageList.end(); it++)
    {
        if (m_fMaxCpuUsage < *it)
        {
            m_fMaxCpuUsage = *it;
        }
    }
}


void CHostStatic::CalcMaxMemUsage()
{
    m_fMaxMemUsage = 0.0;
    list<double>::iterator it;

    m_fMaxMemUsage = 0.0;
    for (it = m_memUsageList.begin(); it != m_memUsageList.end(); it++)
    {
        if (m_fMaxMemUsage < *it)
        {
            m_fMaxMemUsage = *it;
        }
    }
}


void CHostStatic::CalcMaxContinueTime()
{
    int times = 0;
    list<double>::iterator it;

    for (it = m_cpuUsageList.begin(); it != m_cpuUsageList.end(); it++)
    {
        if (m_fMaxCpuUsage == *it)
        {
            times++;
        }
    }
    m_nMaxContinueTime = times * CPU_PEROID;
}




