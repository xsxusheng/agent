/**********************************************************
 * File: CpuUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "CpuUsageScalar.h"

#include "SigarAdapt.h"





CCpuUsageScalar::CCpuUsageScalar()
{
}


CCpuUsageScalar::~CCpuUsageScalar()
{
}



int CCpuUsageScalar::FetchData()
{
    return CSigar::GetCpuUsage();
}


void CCpuUsageScalar::UpdateThrod()
{
}





















