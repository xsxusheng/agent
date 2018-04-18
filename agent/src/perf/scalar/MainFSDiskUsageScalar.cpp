/**********************************************************
 * File: MainFSDiskUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "MainFSDiskUsageScalar.h"

#include "HostStatus.h"





CMainFSDiskUsageScalar::CMainFSDiskUsageScalar()
{
    m_nType = SCALAR_TYPE_DISK_USAGE;
}


CMainFSDiskUsageScalar::~CMainFSDiskUsageScalar()
{
}



double CMainFSDiskUsageScalar::FetchData()
{
    double usage = 0.0;

    usage = CHostStatus::FetchDiskUsage();
    usage = (double)((int)(usage * 10.0) / 10); /*放大100倍，精度1*/
    return usage;
}


void CMainFSDiskUsageScalar::UpdateThrod()
{
    m_nMaxThrod = 90.0;
    m_nMinThrod = 70.0;
    m_nTimesThrod = 2;
}


















