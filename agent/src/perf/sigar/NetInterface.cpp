/**********************************************************
 * File: NetInterface.cpp
 * Function: 
 *********************************************************/
#include "NetInterface.h"

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


void CNetIfStat::SetIfName(char *ifName)
{
    if(ifName != NULL)
    {
        memset(m_cIfName, 0, sizeof(m_cIfName));
        strncpy(m_cIfName, ifName, (MAX_IFNAME_LEN - 1));
    }
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
    if (num > 0)
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
        return 0;
    }

    if (netIfList.number <= 0)
    {
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
        return -1;
    }

    if (SIGAR_OK != sigar_net_interface_list_get(CSigar::GetSigar(), &netIfList))
    {
        return -1;
    }

    if (netIfList.number != GetNetIfNum())
    {
        sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
        return -1;
    }

    for (i = 0; i < netIfList.number; i++)
    {
        if (SIGAR_OK != (ret = sigar_net_interface_stat_get(CSigar::GetSigar(), netIfList.data[i], &ifstat)))
        {
            printf("sigar_net_interface_stat_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
            sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
            return -1;
        }

        if (GetNetIfStat(i) == NULL)
        {
            sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
            return -1;
        }

        GetNetIfStat(i)->SetIfName(netIfList.data[i]);
        if (strcmp(netIfList.data[i], NIC_LOCAL_LOOPBACK) == 0)
        {
            continue;
        }
        
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


        if (SIGAR_OK != (ret = sigar_net_interface_config_get(CSigar::GetSigar(), netIfList.data[i], &config)))
        {
            printf("sigar_net_interface_config_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
            sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
            return -1;
        }

        if (GetNetIfConfig(i) == NULL)
        {
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
    }

    sigar_net_interface_list_destroy(CSigar::GetSigar(), &netIfList);
    return 0;
}



























