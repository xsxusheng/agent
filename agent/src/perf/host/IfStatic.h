/**********************************************************
 * File: IfStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <list>
#include <map>
#include "Timer.h"

using namespace std;



#define DEF_NETIF_REPORT (15 * 60)




class CNicStat
{
public:
    CNicStat();
    ~CNicStat();


    string GetIfName(){return m_strIfName;}
    void SetIfName(string& ifName){m_strIfName = ifName;}

    string GetIpAddr(){return m_strIpAddr;}
    void SetIpAddr(string& ipAddr){m_strIpAddr = ipAddr;}

    string GetSpeed(){return m_strSpeed;}
    void SetSpeed(string& speed){m_strSpeed = speed;}

    long GetRxPackets(){return m_nRxPackets;}
    void SetRxPackets(long rxPackets){m_nRxPackets = rxPackets;}

    long GetRxBytes(){return m_nRxBytes;}
    void SetRxBytes(long rxBytes){m_nRxBytes = rxBytes;}

    long GetRxErrors(){return m_nRxErrors;}
    void SetRxErrors(long rxErrors){m_nRxErrors = rxErrors;}
    
    long GetRxDropped(){return m_nRxDropped;}
    void SetRxDropped(long rxDropped){m_nRxDropped = rxDropped;}

    long GetRxOverruns(){return m_nRxOverruns;}
    void SetRxOverruns(long rxOverruns){m_nRxOverruns = rxOverruns;}

    long GetRxFrame(){return m_nRxFrame;}
    void SetRxFrame(long rxFrame){m_nRxFrame = rxFrame;}

    long GetTxPackets(){return m_nTxPackets;}
    void SetTxPackets(long txPackets){m_nTxPackets = txPackets;}

    long GetTxBytes(){return m_nTxBytes;}
    void SetTxBytes(long txBytes){m_nTxBytes = txBytes;}

    long GetTxErrors(){return m_nTxErrors;}
    void SetTxErrors(long txErrors){m_nTxErrors = txErrors;}
    
    long GetTxDropped(){return m_nTxDropped;}
    void SetTxDropped(long txDropped){m_nTxDropped = txDropped;}

    long GetTxOverruns(){return m_nTxOverruns;}
    void SetTxOverruns(long txOverruns){m_nTxOverruns = txOverruns;}


    long GetRxBytesMax(){return m_nRxBytesMax;}
    void SetRxBytesMax(long bytes){m_nRxBytesMax = bytes;}

    long GetTxBytesMax(){return m_nTxBytesMax;}
    void SetTxBytesMax(long bytes){m_nTxBytesMax = bytes;}

    long GetRxSpeed(){return m_nRxSpeed;}
    void SetRxSpeed(long speed){m_nRxSpeed = speed;}

    long GetTxSpeed(){return m_nTxSpeed;}
    void SetTxSpeed(long speed){m_nTxSpeed = speed;}

    long GetRxMaxSpeed(){return m_nRxMaxSpeed;}
    void SetRxMaxSpeed(long speed){m_nRxMaxSpeed = speed;}

    long GetTxMaxSpeed(){return m_nTxMaxSpeed;}
    void SetTxMaxSpeed(long speed){m_nTxMaxSpeed = speed;}


private:
    string m_strIfName;
    string m_strIpAddr;
    string m_strSpeed;

    long m_nSpeed;
    long m_nRxBytes;
    long m_nRxPackets;
    long m_nRxDropped;
    long m_nRxErrors;
    long m_nRxFrame;
    long m_nRxOverruns;

    long m_nTxBytes;
    long m_nTxPackets;
    long m_nTxDropped;
    long m_nTxErrors;
    long m_nTxOverruns;

    long m_nRxBytesMax;
    long m_nTxBytesMax;
    long m_nRxSpeed;
    long m_nTxSpeed;
    long m_nRxMaxSpeed;
    long m_nTxMaxSpeed;
};







class CIfStatic : public CTimerBase
{
public:
    CIfStatic();
    ~CIfStatic();
    

    void Run();

    void Populate(CNicStat *pNicStat);
    void Sample(bool flag);
    void SendToFums();
    bool NeedReportFums();


private:

    CTime m_lastReportFums;
    map<string, CNicStat> m_mapNicStat;

};









