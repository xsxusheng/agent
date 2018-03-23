/**********************************************************
 * File: NetInterface.h
 * Function: 
 *********************************************************/
#pragma once

#include <cstring>

#include "sigar.h"
#include "MacroDefine.h"



#define NIC_LOCAL_LOOPBACK "lo"


#define MAX_IFNAME_LEN 256

typedef struct
{
    enum
    {
        SIGAR_AF_UNSPEC,
        SIGAR_AF_INET,
        SIGAR_AF_INET6,
        SIGAR_AF_LINK
    }family;

    union
    {
        unsigned int in;
        unsigned int in6[4];
        unsigned char mac[8];
    }addr;
}T_NET_ADDR;








class CNetIfStat
{
public:
    CNetIfStat();
    ~CNetIfStat();


    char* GetIfName(){return m_cIfName;}
    void SetIfName(char *ifName);

    unsigned long long GetRxPackets(){return m_nRxPackets;}
    void SetRxPackets(unsigned long long rxPackets){m_nRxPackets = rxPackets;}

    unsigned long long GetRxBytes(){return m_nRxBytes;}
    void SetRxBytes(unsigned long long rxBytes){m_nRxBytes = rxBytes;}

    unsigned long long GetRxErrors(){return m_nRxErrors;}
    void SetRxErrors(unsigned long long rxErrors){m_nRxErrors = rxErrors;}
    
    unsigned long long GetRxDropped(){return m_nRxDropped;}
    void SetRxDropped(unsigned long long rxDropped){m_nRxDropped = rxDropped;}

    unsigned long long GetRxOverruns(){return m_nRxOverruns;}
    void SetRxOverruns(unsigned long long rxOverruns){m_nRxOverruns = rxOverruns;}

    unsigned long long GetRxFrame(){return m_nRxFrame;}
    void SetRxFrame(unsigned long long rxFrame){m_nRxFrame = rxFrame;}

    unsigned long long GetTxPackets(){return m_nTxPackets;}
    void SetTxPackets(unsigned long long txPackets){m_nTxPackets = txPackets;}

    unsigned long long GetTxBytes(){return m_nTxBytes;}
    void SetTxBytes(unsigned long long txBytes){m_nTxBytes = txBytes;}

    unsigned long long GetTxErrors(){return m_nTxErrors;}
    void SetTxErrors(unsigned long long txErrors){m_nTxErrors = txErrors;}
    
    unsigned long long GetTxDropped(){return m_nTxDropped;}
    void SetTxDropped(unsigned long long txDropped){m_nTxDropped = txDropped;}

    unsigned long long GetTxOverruns(){return m_nTxOverruns;}
    void SetTxOverruns(unsigned long long txOverruns){m_nTxOverruns = txOverruns;}

    unsigned long long GetTxCollisions(){return m_nTxCollisions;}
    void SetTxCollisions(unsigned long long txCollisions){m_nTxCollisions = txCollisions;}

    unsigned long long GetTxCarrier(){return m_nTxCarrier;}
    void SetTxCarrier(unsigned long long txCarrier){m_nTxCarrier = txCarrier;}

    unsigned long long GetSpeed(){return m_nSpeed;}
    void SetSpeed(unsigned long long speed){m_nSpeed = speed;}


private:
    char m_cIfName[MAX_IFNAME_LEN];
    unsigned long long m_nRxPackets;
    unsigned long long m_nRxBytes;
    unsigned long long m_nRxErrors;
    unsigned long long m_nRxDropped;
    unsigned long long m_nRxOverruns;
    unsigned long long m_nRxFrame;
    unsigned long long m_nTxPackets;
    unsigned long long m_nTxBytes;
    unsigned long long m_nTxErrors;
    unsigned long long m_nTxDropped;
    unsigned long long m_nTxOverruns;
    unsigned long long m_nTxCollisions;
    unsigned long long m_nTxCarrier;
    unsigned long long m_nSpeed;
};







class CNetIfConfig
{
public:
    CNetIfConfig();
    ~CNetIfConfig();


    char* GetIfName(){return m_cIfName;}
    void SetIfName(char *ifName);
    
    char* GetType(){return m_cType;}
    void SetType(char *type);
    
    char* GetDesc(){return m_cDesc;}
    void SetDesc(char *desc);


    T_NET_ADDR* GetHwAddr(){return &m_hwAddr;}
    void SetHwAddr(sigar_net_address_t& addr);
    
    T_NET_ADDR* GetAddress(){return &m_address;}
    void SetAddress(sigar_net_address_t& addr);
    
    T_NET_ADDR* GetDestination(){return &m_destination;}
    void SetDesctination(sigar_net_address_t& addr);
    
    T_NET_ADDR* GetBroadcast(){return &m_broadcast;}
    void SetBroadcast(sigar_net_address_t& addr);
    
    T_NET_ADDR* GetNetmask(){return &m_netmask;}
    void SetNetMask(sigar_net_address_t& addr);
    
    T_NET_ADDR* GetAddr6(){return &m_addr6;}
    void SetAddr6(sigar_net_address_t& addr);


    unsigned long long GetFlags(){return m_nFlags;}
    void SetFlags(unsigned long long flags){m_nFlags = flags;}
    
    unsigned long long GetMtu(){return m_nMtu;}
    void SetMtu(unsigned long long mtu){m_nMtu = mtu;}
    
    unsigned long long GetMetric(){return m_nMetric;}
    void SetMetric(unsigned long long metric){m_nMetric = metric;}

    int GetTxQueueLen(){return m_nTxQueueLen;}
    void SetTxQueueLen(int len){m_nTxQueueLen = len;}
    
    int GetPrefix6Len(){return m_nPrefix6Len;}
    void SetPrefix6Len(int len){m_nPrefix6Len = len;}
    
    int GetScope6(){return m_nScope6;}
    void SetScope6(int scope){m_nScope6 = scope;}


private:
    char m_cIfName[MAX_IFNAME_LEN];
    char m_cType[64];
    char m_cDesc[256];
    
    T_NET_ADDR m_hwAddr;
    T_NET_ADDR m_address;
    T_NET_ADDR m_destination;
    T_NET_ADDR m_broadcast;
    T_NET_ADDR m_netmask;
    T_NET_ADDR m_addr6;
    
    unsigned long long m_nFlags;
    unsigned long long m_nMtu;
    unsigned long long m_nMetric;
    
    int m_nTxQueueLen;
    int m_nPrefix6Len;
    int m_nScope6;
};





class CNetInterface
{
public:
    CNetInterface();
    ~CNetInterface();

    unsigned long GetNetIfNum(){return m_nNetIfNum;}
    void SetNetIfNum(unsigned long num){if(num > 0){m_nNetIfNum = num;}}

    CNetIfStat *GetNetIfStat(){return m_pNetIfStat;}
    CNetIfStat *GetNetIfStat(unsigned long index);
    
    CNetIfConfig *GetNetIfConfig(){return m_pNetIfConfig;}
    CNetIfConfig *GetNetIfConfig(unsigned long index);


    unsigned long GetNetIfListNum();
    int GetNetIfStatus();


private:

    unsigned long m_nNetIfNum;
    CNetIfStat *m_pNetIfStat;
    CNetIfConfig *m_pNetIfConfig;

};
















