/**********************************************************
 * File: SwapUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "SwapUsageScalar.h"

#include "HostStatus.h"




CSwapUsageScalar::CSwapUsageScalar()
{
    m_nType = SCALAR_TYPE_SWAP_USAGE;
}


CSwapUsageScalar::~CSwapUsageScalar()
{
}


double CSwapUsageScalar::FetchData()
{
    double usage = CHostStatus::GetSwapUsage();

    usage = (double)((int)(usage * 10.0) / 10);
    return usage;
}


void CSwapUsageScalar::UpdateThrod()
{
    m_nMaxThrod = 90.0;
    m_nMinThrod = 70.0;
    m_nTimesThrod = 2;
}




















