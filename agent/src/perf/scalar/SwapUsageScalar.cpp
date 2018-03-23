/**********************************************************
 * File: SwapUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "SwapUsageScalar.h"

#include "HostStatus.h"




CSwapUsageScalar::CSwapUsageScalar()
{
}


CSwapUsageScalar::~CSwapUsageScalar()
{
}


int CSwapUsageScalar::FetchData()
{
    return CHostStatus::GetSwapUsage();
}


void CSwapUsageScalar::UpdateThrod()
{
}




















