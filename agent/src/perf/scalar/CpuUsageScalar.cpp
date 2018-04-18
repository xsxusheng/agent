/**********************************************************
 * File: CpuUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "CpuUsageScalar.h"
#include "sv_log.h"
#include "HostStatus.h"





CCpuUsageScalar::CCpuUsageScalar()
{
    m_nType = SCALAR_TYPE_CPU_USAGE;
}


CCpuUsageScalar::~CCpuUsageScalar()
{
}



double CCpuUsageScalar::FetchData()
{
    return CHostStatus::GetCpuUsage();
}


void CCpuUsageScalar::UpdateThrod()
{
    m_nMaxThrod = 50.0;
    m_nMinThrod = 10.0;
    m_nTimesThrod = 2;
}





















