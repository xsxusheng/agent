/**********************************************************
 * File: NetInterface.cpp
 * Function: 
 *********************************************************/
#include "NetInterface.h"

#include <arpa/inet.h>

#include "sv_log.h"
#include "sigar.h"
#include "SigarAdapt.h"




CNetIfStat::CNetIfStat()
{
    memset(m_cIfName, 0, sizeof(m_cIfName));
    m_nRxPackets = 0;
    m_nRxBytes = 0;
    m_nRxErrors = 0;
    m_nRxDropped = 0;
    m_nRxOverruns = 0;
    m_nRxFrame = 0;
    m_nTxPackets = 0;
    m_nTxBytes = 0;
    m_nTxErrors = 0;
    m_nTxDropped = 0;
    m_nTxOverruns = 0;
    m_nTxCollisions = 0;
    m_nTxCarrier = 0;
    m_nSpeed = 0;
}


CNetIfStat::~CNetIfStat()
{
}


void CNetIfStat::SetIfName(const char *ifName)
{
    if(ifName != NULL)
    {
        memset(m_cIfName, 0, sizeof(m_cIfName));
        strncpy(m_cIfName, ifName, (MAX_IFNAME_LEN - 1));
    }
}



int CNetIfStat::GetNetIfStat(const char *ifName)
{
    int ret = 0;
    sigar_net_interface_stat_t ifstat;

    if (ifName == NULL)
    {
        SV_ERROR("Input para is null.");
        return -1;
    }
    
    if (SIGAR_OK != (ret = sigar_net_interface_stat_get(CSigar::GetSigar(), ifName, &ifstat)))
    {
        SV_ERROR("sigar_net_interface_stat_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
        return -1;
    }

    SetIfName(ifName);
    if (strcmp(ifName, NIC_LOCAL_LOOPBACK) == 0)
    {
        return 0;
    }
    
    SetRxPackets(ifstat.rx_packets);
    SetRxBytes(ifstat.rx_bytes);
    SetRxErrors(ifstat.rx_errors);
    SetRxDropped(ifstat.rx_dropped);
    SetRxOverruns(ifstat.rx_overruns);
    SetRxFrame(ifstat.rx_frame);
    SetTxPackets(ifstat.tx_packets);
    SetTxBytes(ifstat.tx_bytes);
    SetTxErrors(ifstat.tx_errors);
    SetTxDropped(ifstat.tx_dropped);
    SetTxOverruns(ifstat.tx_overruns);
    SetTxCollisions(ifstat.tx_collisions);
    SetTxCarrier(ifstat.tx_carrier);
    SetSpeed(ifstat.speed);
    return 0;
}





#if 0
#endif



CNetIfConfig::CNetIfConfig()
{
}


CNetIfConfig::~CNetIfConfig()
{
}


void CNetIfConfig::SetIfName(char *ifName)
{
    if(ifName != NULL)
    {
        memset(m_cIfName, 0, sizeof(m_cIfName));
        strncpy(m_cIfName, ifName, (MAX_IFNAME_LEN - 1));
    }
}


void CNetIfConfig::SetType(char *type)
{
    if(type != NULL)
    {
        memset(m_cType, 0, sizeof(m_cType));
        strncpy(m_cType, type, (sizeof(m_cType) - 1));
    }
}


void CNetIfConfig::SetDesc(char *desc)
{
    if(desc != NULL)
    {
        memset(m_cDesc, 0, sizeof(m_cDesc));
        strncpy(m_cDesc, desc, (sizeof(m_cDesc) - 1));
    }
}


void CNetIfConfig::SetHwAddr(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_hwAddr, &addr, sizeof(T_NET_ADDR));
    }
}



int CNetIfConfig::GetAddress(string& ipAddr)
{
    char strIp[MAX_IP_LEN] = {0};

    if (m_address.family == T_NET_ADDR::SIGAR_AF_INET)
    {
        inet_ntop(AF_INET, &m_address.addr.in, strIp, (MAX_IP_LEN-1));
        ipAddr = strIp;
    }
    else if (m_address.family == T_NET_ADDR::SIGAR_AF_INET6)
    {
        inet_ntop(AF_INET6, &m_address.addr.in6, strIp, (MAX_IP_LEN-1));
        ipAddr = strIp;
    }
    else
    {
        return -1;
    }

    return 0;
}



void CNetIfConfig::SetAddress(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_address, &addr, sizeof(T_NET_ADDR));
    }
}


void CNetIfConfig::SetDesctination(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_destination, &addr, sizeof(T_NET_ADDR));
    }
}


void CNetIfConfig::SetBroadcast(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_broadcast, &addr, sizeof(T_NET_ADDR));
    }
}


void CNetIfConfig::SetNetMask(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_netmask, &addr, sizeof(T_NET_ADDR));
    }
}


void CNetIfConfig::SetAddr6(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_addr6, &addr, sizeof(T_NET_ADDR));
    }
}





#if 0
#endif


CNetInterface::CNetInterface()
{
    unsigned long num = 0;

    m_nNetIfNum = 0;
    m_pNetIfStat = NULL;
    m_pNetIfConfig = NULL;

    num = GetNetIfListNum();
    if ((num > 0) && (num <= MAX_NIC_NUM))
    {
        m_pNetIfStat = new CNetIfStat[num];
        if (m_pNetIfStat == NULL)
        {
            return;
        }

        m_pNetIfConfig = new CNetIfConfig[num];
        if (m_pNetIfConfig == NULL)
        {
            delete []m_pNetIfStat;
            m_pNetIfStat = NULL;
            return;
        }
        
        m_nNetIfNum = num;
    }
}



CNetInterface::~CNetInterface()
{
    m_nNetIfNum = 0;
    if (m_pNetIfStat != NULL)
    {
        delete []m_pNetIfStat;
        m_pNetIfStat = NULL;
    }
    if (m_pNetIfConfig != NULL)
    {
        delete []m_pNetIfConfig;
        m_pNetIfConfig = NULL;
    }
}



unsigned long CNetInterface::GetNetIfListNum()
{
    unsigned long num = 0;
    sigar_net_interface_list_t netIfList;

    if (SIGAR_OK != sigar_net_interface_list_get(CSigar::GetSigar(), &netIfList))
    {
        SV_ERROR("sigar_net_interface_list_get failed...");
        return 0;
    }

    if (netIfList.number <= 0)
    {
        SV_ERROR("sigar_net_interface_list_get number %d error...", netIfList.number);
        return 0;
    }

    num = netIfList.number;
    sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
    return num;
}



CNetIfStat* CNetInterface::GetNetIfStat(unsigned long index)
{
    unsigned long num = 0;

    if (m_pNetIfStat == NULL)
    {
        SV_ERROR("Input para is null.");
        return NULL;
    }

    num = GetNetIfNum();
    if ((num > 0) && (index < num))
    {
        return &m_pNetIfStat[index];
    }
    return NULL;
}



CNetIfConfig* CNetInterface::GetNetIfConfig(unsigned long index)
{
    unsigned long num = 0;

    if (m_pNetIfConfig == NULL)
    {
        SV_ERROR("Input para is null.");
        return NULL;
    }

    num = GetNetIfNum();
    if ((num > 0) && (index < num))
    {
        return &m_pNetIfConfig[index];
    }
    return NULL;
}





int CNetInterface::GetNetIfStatus()
{
    int ret = 0;
    unsigned long i = 0;
    CNetIfStat *netIfStat = NULL;
    sigar_net_interface_list_t netIfList;
    sigar_net_interface_stat_t ifstat;
    sigar_net_interface_config_t config;

    netIfStat = GetNetIfStat();
    if (netIfStat == NULL)
    {
        SV_ERROR("Input para is null.");
        return -1;
    }

    if (SIGAR_OK != sigar_net_interface_list_get(CSigar::GetSigar(), &netIfList))
    {
        SV_ERROR("sigar_net_interface_list_get failed...");
        return -1;
    }

    if (netIfList.number != GetNetIfNum())
    {
        SV_ERROR("sigar_net_interface_list_get number %lu,%lu error...", netIfList.number, GetNetIfNum());
        sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
        return -1;
    }

    for (i = 0; i < netIfList.number; i++)
    {
        memset(&config, 0, sizeof(sigar_net_interface_config_t));
        memset(&ifstat, 0, sizeof(sigar_net_interface_stat_t));

        if (SIGAR_OK != (ret = sigar_net_interface_config_get(CSigar::GetSigar(), netIfList.data[i], &config)))
        {
            SV_ERROR("sigar_net_interface_config_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
            sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
            return -1;
        }

        if (GetNetIfConfig(i) == NULL)
        {
            SV_ERROR("sigar_net_interface_list_get GetNetIfConfig(i) == NULL...");
            sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
            return -1;
        }

        GetNetIfConfig(i)->SetIfName(config.name);
        GetNetIfConfig(i)->SetType(config.type);
        GetNetIfConfig(i)->SetDesc(config.description);
        GetNetIfConfig(i)->SetFlags(config.flags);
        GetNetIfConfig(i)->SetMtu(config.mtu);
        GetNetIfConfig(i)->SetMetric(config.metric);
        
        GetNetIfConfig(i)->SetHwAddr(config.hwaddr);
        GetNetIfConfig(i)->SetAddress(config.address);
        GetNetIfConfig(i)->SetDesctination(config.destination);
        GetNetIfConfig(i)->SetBroadcast(config.broadcast);
        GetNetIfConfig(i)->SetNetMask(config.netmask);
        GetNetIfConfig(i)->SetAddr6(config.address6);


        if (SIGAR_OK != (ret = sigar_net_interface_stat_get(CSigar::GetSigar(), netIfList.data[i], &ifstat)))
        {
            SV_ERROR("sigar_net_interface_stat_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
            sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
            return -1;
        }

        if (GetNetIfStat(i) == NULL)
        {
            SV_ERROR("sigar_net_interface_list_get GetNetIfStat(i) == NULL...");
            sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
            return -1;
        }

        GetNetIfStat(i)->SetIfName(netIfList.data[i]);
        GetNetIfStat(i)->SetRxPackets(ifstat.rx_packets);
        GetNetIfStat(i)->SetRxBytes(ifstat.rx_bytes);
        GetNetIfStat(i)->SetRxErrors(ifstat.rx_errors);
        GetNetIfStat(i)->SetRxDropped(ifstat.rx_dropped);
        GetNetIfStat(i)->SetRxOverruns(ifstat.rx_overruns);
        GetNetIfStat(i)->SetRxFrame(ifstat.rx_frame);
        GetNetIfStat(i)->SetTxPackets(ifstat.tx_packets);
        GetNetIfStat(i)->SetTxBytes(ifstat.tx_bytes);
        GetNetIfStat(i)->SetTxErrors(ifstat.tx_errors);
        GetNetIfStat(i)->SetTxDropped(ifstat.tx_dropped);
        GetNetIfStat(i)->SetTxOverruns(ifstat.tx_overruns);
        GetNetIfStat(i)->SetTxCollisions(ifstat.tx_collisions);
        GetNetIfStat(i)->SetTxCarrier(ifstat.tx_carrier);
        GetNetIfStat(i)->SetSpeed(ifstat.speed);
    }

    sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
    return 0;
}





#if 0
#endif



CNetConn::CNetConn()
{
    m_nLocalPort = 0;
    m_nRemotePort = 0;
    m_nUid = 0;
    m_nInode = 0;
    m_nType = 0;
    m_nState = 0;
    m_nSendQueue = 0;
    m_nReceiveQueue = 0;
    memset(&m_localAddress, 0, sizeof(m_localAddress));
    memset(&m_remoteAddress, 0, sizeof(m_remoteAddress));
}



CNetConn::~CNetConn()
{
}



void CNetConn::SetLocalAddr(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_localAddress, &addr, sizeof(T_NET_ADDR));
    }
}



void CNetConn::SetRemoteAddr(sigar_net_address_t& addr)
{
    if (sizeof(T_NET_ADDR) == sizeof(sigar_net_address_t))
    {
        memcpy(&m_remoteAddress, &addr, sizeof(T_NET_ADDR));
    }
}




CNetConnList::CNetConnList()
{
    m_nNetConnNum = 0;
    m_pNetConn = NULL;
}



CNetConnList::~CNetConnList()
{
    FreeNetConnList();
}



void CNetConnList::FreeNetConnList()
{
    if (m_pNetConn != NULL)
    {
        delete []m_pNetConn;
        m_pNetConn = NULL;
    }
    m_nNetConnNum = 0;
}




CNetConn* CNetConnList::GetNetConn(unsigned long index)
{
    if ((index < m_nNetConnNum) || (m_pNetConn != NULL))
    {
        return &m_pNetConn[index];
    }

    return NULL;
}



int CNetConnList::GetNetConnList()
{
	int ret = 0;
    sigar_net_connection_list_t connlist;

    if (SIGAR_OK != (ret = sigar_net_connection_list_get(CSigar::GetSigar(), &connlist,
        SIGAR_NETCONN_SERVER | SIGAR_NETCONN_CLIENT |
        SIGAR_NETCONN_TCP | SIGAR_NETCONN_UDP)))
    {
        SV_ERROR("sigar_net_connection_list_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
        return -1;
	}

    if (connlist.number > 0)
    {
        FreeNetConnList();
        m_pNetConn = new CNetConn[connlist.number];
        if (m_pNetConn == NULL)
        {
            sigar_net_connection_list_destroy(CSigar::GetSigar(), &connlist);
            return -1;
        }
        m_nNetConnNum = connlist.number;
    }

    sigar_net_connection_list_destroy(CSigar::GetSigar(), &connlist);
    return 0;
}





int CNetConnList::GetNetConnList(int flag)
{
	int ret = 0;
    sigar_net_connection_list_t connlist;

    if (SIGAR_OK != (ret = sigar_net_connection_list_get(CSigar::GetSigar(), &connlist, flag)))
    {
        SV_ERROR("sigar_net_connection_list_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
        return -1;
	}

    if (connlist.number > 0)
    {
        FreeNetConnList();
        m_pNetConn = new CNetConn[connlist.number];
        if (m_pNetConn == NULL)
        {
            sigar_net_connection_list_destroy(CSigar::GetSigar(), &connlist);
            return -1;
        }
        m_nNetConnNum = connlist.number;
    }

    sigar_net_connection_list_destroy(CSigar::GetSigar(), &connlist);
    return 0;
}







CNetStat::CNetStat()
{
    m_nTcpInboundTotal = 0;
    m_nTcpOutboundTotal = 0;
    m_nAllInboundTotal = 0;
    m_nAllOutboundTotal = 0;
    memset(m_nTcpStates, 0, sizeof(m_nTcpStates));
}



CNetStat::~CNetStat()
{
}




int CNetStat::GetTcpStates(int state)
{
    if ((state >= 0) && (state < SIGAR_TCP_UNKNOWN))
    {
        return m_nTcpStates[state];
    }

    return 0;
}



int CNetStat::GetNetStat()
{
    int ret = 0;
    sigar_net_stat_t netstat;

    if (SIGAR_OK != sigar_net_stat_get(CSigar::GetSigar(), &netstat,
        SIGAR_NETCONN_SERVER | SIGAR_NETCONN_CLIENT | SIGAR_NETCONN_TCP | SIGAR_NETCONN_UDP))
    {
        SV_ERROR("sigar_net_stat_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
        return -1;
    }

    memcpy(m_nTcpStates, netstat.tcp_states, sizeof(m_nTcpStates));
    m_nTcpInboundTotal = netstat.tcp_inbound_total;
    m_nTcpOutboundTotal = netstat.tcp_outbound_total;
    m_nAllInboundTotal = netstat.all_inbound_total;
    m_nAllOutboundTotal = netstat.all_outbound_total;
    return 0;
}





