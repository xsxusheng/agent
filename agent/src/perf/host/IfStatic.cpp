/**********************************************************
 * File: IfStatic.cpp
 * Function: 
 *********************************************************/
#include "IfStatic.h"

#include <cstdlib>
#include <vector>

#include "HostStatus.h"
#include "NetInterface.h"

//using namespace com::fiberhome::fums::proto;




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





void CIfStatic::Run()
{
    if (NeedReportFums())
    {
        SendToFums();
    }
}



void CIfStatic::SendToFums()
{
    unsigned long i = 0;
    unsigned long num = 0;
    CNetInterface netIf;
    
    netIf.GetNetIfStatus();
    num = netIf.GetNetIfNum();

    for (i = 0; i < num; i++)
    {
    }
}




















