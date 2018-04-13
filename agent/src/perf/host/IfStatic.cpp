/**********************************************************
 * File: IfStatic.cpp
 * Function: 
 *********************************************************/
#include "IfStatic.h"

#include <cstdlib>
#include <vector>

#include "StringUtils.h"
#include "HostStatus.h"
#include "NetInterface.h"

#include "AmqpReceiveBuilder.h"
#include "AmqpMessageReceiveProcessor.h"
#include "AmqpMessageSendProcessor.h"
#include "ProtoBufPacker.h"

using namespace com::fiberhome::fums::proto;







CNicStat::CNicStat()
{
    m_strIfName.clear();
    m_strIpAddr.clear();
    m_strSpeed.clear();

    m_nSpeed = 0;
    m_nRxBytes = 0;
    m_nRxPackets = 0;
    m_nRxDropped = 0;
    m_nRxErrors = 0;
    m_nRxFrame = 0;
    m_nRxOverruns = 0;

    m_nTxBytes = 0;
    m_nTxPackets = 0;
    m_nTxDropped = 0;
    m_nTxErrors = 0;
    m_nTxOverruns = 0;

    m_nRxBytesMax = 0;
    m_nTxBytesMax = 0;
    m_nRxSpeed = 0;
    m_nTxSpeed = 0;
    m_nRxMaxSpeed = 0;
    m_nTxMaxSpeed = 0;
}




CNicStat::~CNicStat()
{
    m_strIfName.clear();
    m_strIpAddr.clear();
    m_strSpeed.clear();

    m_nSpeed = 0;
    m_nRxBytes = 0;
    m_nRxPackets = 0;
    m_nRxDropped = 0;
    m_nRxErrors = 0;
    m_nRxFrame = 0;
    m_nRxOverruns = 0;

    m_nTxBytes = 0;
    m_nTxPackets = 0;
    m_nTxDropped = 0;
    m_nTxErrors = 0;
    m_nTxOverruns = 0;

    m_nRxBytesMax = 0;
    m_nTxBytesMax = 0;
    m_nRxSpeed = 0;
    m_nTxSpeed = 0;
    m_nRxMaxSpeed = 0;
    m_nTxMaxSpeed = 0;
}





#if 0
#endif






CIfStatic::CIfStatic()
{
    m_lastReportFums.GetTimeNow();
}



CIfStatic::~CIfStatic()
{
}




bool CIfStatic::NeedReportFums()
{
    CTime tNow;

    if (m_lastReportFums.DiffSec(tNow) >= DEF_NETIF_REPORT)
    {
        /*重置上次上报时间*/
        m_lastReportFums = tNow;
        return true;
    }
    return false;
}



void CIfStatic::Populate(CNicStat *pNicStat)
{
    long rxBytes = 0;
    long txBytes = 0;
    long diffTime = 0;

    CTime startTime;
    CTime endTime;

    CNetIfStat netStat;
    CNetIfStat netStat2;

    if (pNicStat == NULL)
    {
        return;
    }

    startTime.GetTimeNow();
    string ifName = pNicStat->GetIfName();
    if (netStat.GetNetIfStat(ifName.c_str()) < 0)
    {
        return;
    }

    /*暂停1秒第二次采样*/
    CTime::msecSleep(1000);
    endTime.GetTimeNow();
    if (netStat2.GetNetIfStat(ifName.c_str()) < 0)
    {
        return;
    }

    rxBytes = netStat2.GetRxBytes() - netStat.GetRxBytes();
    txBytes = netStat2.GetTxBytes() - netStat.GetTxBytes();

    diffTime = endTime.DiffMSec(startTime);
    pNicStat->SetRxSpeed((rxBytes * 8) / diffTime);
    pNicStat->SetTxSpeed((txBytes * 8) / diffTime);


    if (pNicStat->GetRxBytesMax() < rxBytes)
    {
        pNicStat->SetRxBytesMax(rxBytes);
    }

    if (pNicStat->GetTxBytesMax() < txBytes)
    {
        pNicStat->SetTxBytesMax(txBytes);
    }


    if (pNicStat->GetRxMaxSpeed() < pNicStat->GetRxSpeed())
    {
        pNicStat->SetRxMaxSpeed(pNicStat->GetRxSpeed());
    }

    if (pNicStat->GetTxMaxSpeed() < pNicStat->GetTxSpeed())
    {
        pNicStat->SetTxMaxSpeed(pNicStat->GetTxSpeed());
    }
}



void CIfStatic::Sample(bool flag)
{
    unsigned long i = 0;
    unsigned long num = 0;
    string ifName;
    string ipAddr;
    string speed;
    CNicStat *pNicStat = NULL;
    map<string, CNicStat>::iterator it;
    CNetInterface netIf;

    netIf.GetNetIfStatus();
    num = netIf.GetNetIfNum();

    for (i = 0; i < num; i++)
    {
        ifName = netIf.GetNetIfStat(i)->GetIfName();
        it = m_mapNicStat.find(ifName);
        if (it != m_mapNicStat.end())
        {
            continue;
        }

        CNicStat nicStat;
        nicStat.SetIfName(ifName);

        netIf.GetNetIfConfig(i)->GetAddress(ipAddr);
        nicStat.SetIpAddr(ipAddr);

        speed = CString::ToString(netIf.GetNetIfConfig()->GetMtu());
        nicStat.SetSpeed(speed);

        /*插入新值*/
        m_mapNicStat.insert(pair<string, CNicStat>(ifName, nicStat));
    }


    for (i = 0; i < num; i++)
    {
        ifName = netIf.GetNetIfStat(i)->GetIfName();
        it = m_mapNicStat.find(ifName);
        if (it == m_mapNicStat.end())
        {
            continue;
        }

        pNicStat = &(it->second);
        Populate(pNicStat);

        if (flag)
        {
            pNicStat->SetRxBytes((long)netIf.GetNetIfStat()->GetRxBytes());
            pNicStat->SetRxPackets((long)netIf.GetNetIfStat()->GetRxPackets());
            pNicStat->SetRxErrors((long)netIf.GetNetIfStat()->GetRxErrors());
            pNicStat->SetRxDropped((long)netIf.GetNetIfStat()->GetRxDropped());
            pNicStat->SetRxOverruns((long)netIf.GetNetIfStat()->GetRxOverruns());
            pNicStat->SetRxFrame((long)netIf.GetNetIfStat()->GetRxFrame());
            
            pNicStat->SetTxBytes((long)netIf.GetNetIfStat()->GetTxBytes());
            pNicStat->SetTxPackets((long)netIf.GetNetIfStat()->GetTxPackets());
            pNicStat->SetTxErrors((long)netIf.GetNetIfStat()->GetTxErrors());
            pNicStat->SetTxDropped((long)netIf.GetNetIfStat()->GetTxDropped());
            pNicStat->SetTxOverruns((long)netIf.GetNetIfStat()->GetTxOverruns());
        }
    }
}





void CIfStatic::Run()
{
    Sample(false);
    if (NeedReportFums())
    {
        Sample(true);
        SendToFums();
        m_mapNicStat.clear();
    }
}



void CIfStatic::SendToFums()
{
    map<string, CNicStat>::iterator it;
    NicData data;

    for (it = m_mapNicStat.begin(); it != m_mapNicStat.end(); it++)
    {
        SingleNicPerfData *singleData = data.add_perfdata();

        singleData->set_nicname(it->second.GetIfName());
        singleData->set_nicipaddress(it->second.GetIpAddr());
        singleData->set_nicspeed(it->second.GetSpeed());
        singleData->set_nicrxbytes(it->second.GetRxBytes());
        singleData->set_nictxbytes(it->second.GetTxBytes());
        singleData->set_nicrxpackets(it->second.GetRxPackets());
        singleData->set_nicrxdropped(it->second.GetRxDropped());
        singleData->set_nicrxerrors(it->second.GetRxErrors());
        singleData->set_nicrxframe(it->second.GetRxFrame());
        singleData->set_nicrxoverruns(it->second.GetRxOverruns());
        singleData->set_nictxpackets(it->second.GetTxPackets());
        singleData->set_nictxdropped(it->second.GetTxDropped());
        singleData->set_nictxerrors(it->second.GetTxErrors());
        singleData->set_nictxoverruns(it->second.GetTxOverruns());
        singleData->set_nicoutputbandwidth(0);
        singleData->set_nicinputbandwidth(0);
        singleData->set_nicrxbytesmax(it->second.GetRxBytesMax());
        singleData->set_nictxbytesmax(it->second.GetTxBytesMax());
        singleData->set_nicrxspeed(it->second.GetRxSpeed());
        singleData->set_nictxspeed(it->second.GetTxSpeed());
        singleData->set_nicrxmaxspeed(it->second.GetRxMaxSpeed());
        singleData->set_nictxmaxspeed(it->second.GetTxMaxSpeed());
    }

    Major major = ProtoBufPacker::PackPerfEntity(ProtoBufPacker::SerializeToArray<NicData>(data), PerfData::NIC_TYPE);
    AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
}




















