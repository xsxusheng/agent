/**********************************************************
 * File: NetInterface.h
 * Function: 
 *********************************************************/
#pragma once

#include <cstring>

#include "SigarAdapt.h"
#include "MacroDefine.h"



#define NIC_LOCAL_LOOPBACK "lo"

#define MAX_IP_LEN 48
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
    void SetIfName(const char *ifName);

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


    int GetNetIfStat(const char *ifName);


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
    int GetAddress(string& ipAddr);
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








#define NETCONN_CLIENT SIGAR_NETCONN_CLIENT
#define NETCONN_SERVER SIGAR_NETCONN_SERVER

#define NETCONN_TCP SIGAR_NETCONN_TCP
#define NETCONN_UDP SIGAR_NETCONN_UDP
#define NETCONN_RAW SIGAR_NETCONN_RAW
#define NETCONN_UNIX SIGAR_NETCONN_UNIX


enum {
    TCP_ESTABLISHED = SIGAR_TCP_ESTABLISHED,
    TCP_SYN_SENT = SIGAR_TCP_SYN_SENT,
    TCP_SYN_RECV = SIGAR_TCP_SYN_RECV,
    TCP_FIN_WAIT1 = SIGAR_TCP_FIN_WAIT1,
    TCP_FIN_WAIT2 = SIGAR_TCP_FIN_WAIT2,
    TCP_TIME_WAIT = SIGAR_TCP_TIME_WAIT,
    TCP_CLOSE = SIGAR_TCP_CLOSE,
    TCP_CLOSE_WAIT = SIGAR_TCP_CLOSE_WAIT,
    TCP_LAST_ACK = SIGAR_TCP_LAST_ACK,
    TCP_LISTEN = SIGAR_TCP_LISTEN,
    TCP_CLOSING = SIGAR_TCP_CLOSING,
    TCP_IDLE = SIGAR_TCP_IDLE,
    TCP_BOUND = SIGAR_TCP_BOUND,
    TCP_UNKNOWN = SIGAR_TCP_UNKNOWN
};


class CNetConn
{
public:
    CNetConn();
    ~CNetConn();


    unsigned long GetLocalPort(){return m_nLocalPort;}
    void SetLocalPort(unsigned long port){m_nLocalPort = port;}

    T_NET_ADDR* GetLocalAddr(){return &m_localAddress;}
    void SetLocalAddr(sigar_net_address_t& addr);

    unsigned long GetRemotePort(){return m_nRemotePort;}
    void SetRemotePort(unsigned long port){m_nRemotePort = port;}

    T_NET_ADDR* GetRemoteAddr(){return &m_remoteAddress;}
    void SetRemoteAddr(sigar_net_address_t& addr);

    unsigned long GetUid(){return m_nUid;}
    void SetUid(unsigned long uid){m_nUid = uid;}

    unsigned long GetInode(){return m_nInode;}
    void SetInode(unsigned long inode){m_nInode = inode;}
    
    int GetType(){return m_nType;}
    void SetType(unsigned long type){m_nType = type;}
    
    int GetState(){return m_nState;}
    void SetState(unsigned long state){m_nState = state;}
    
    unsigned long GetSendQueue(){return m_nSendQueue;}
    void SetSendQueue(unsigned long queue){m_nSendQueue = queue;}
    
    unsigned long GetReceiveQueue(){return m_nReceiveQueue;}
    void SetReceiveQueue(unsigned long queue){m_nReceiveQueue = queue;}


private:
    unsigned long m_nLocalPort;
    T_NET_ADDR m_localAddress;
    unsigned long m_nRemotePort;
    T_NET_ADDR m_remoteAddress;
    unsigned long m_nUid;
    unsigned long m_nInode;
    int m_nType;
    int m_nState;
    unsigned long m_nSendQueue;
    unsigned long m_nReceiveQueue;


};



class CNetConnList
{
public:
    CNetConnList();
    ~CNetConnList();


    void FreeNetConnList();


    unsigned long GetNetConnNum(){return m_nNetConnNum;}
    CNetConn* GetNetConn(unsigned long index);
    
    int GetNetConnList();
    int GetNetConnList(int flag);


private:
    unsigned long m_nNetConnNum;
    CNetConn *m_pNetConn;

};








class CNetStat
{
public:
    CNetStat();
    ~CNetStat();


    int GetTcpStates(int state);
    unsigned int GetTcpInboundTotal(){return m_nTcpInboundTotal;}
    unsigned int GetTcpOutboundTotal(){return m_nTcpOutboundTotal;}
    unsigned int GetAllInboundTotal(){return m_nAllInboundTotal;}
    unsigned int GetAllOutboundTotal(){return m_nAllOutboundTotal;}

    int GetNetStat();



private:
    int m_nTcpStates[SIGAR_TCP_UNKNOWN];
    unsigned int m_nTcpInboundTotal;
    unsigned int m_nTcpOutboundTotal;
    unsigned int m_nAllInboundTotal;
    unsigned int m_nAllOutboundTotal;


};











