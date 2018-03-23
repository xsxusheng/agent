/**********************************************************
 * File: CpuUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "CpuUsageScalar.h"

#include "HostStatus.h"





CCpuUsageScalar::CCpuUsageScalar()
{
}


CCpuUsageScalar::~CCpuUsageScalar()
{
}



int CCpuUsageScalar::FetchData()
{
    return CHostStatus::GetCpuUsage();
}


void CCpuUsageScalar::UpdateThrod()
{
}





















