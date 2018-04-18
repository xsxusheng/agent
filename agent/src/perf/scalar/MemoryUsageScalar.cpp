/**********************************************************
 * File: MemUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "MemoryUsageScalar.h"

#include "HostStatus.h"


CMemUsageScalar::CMemUsageScalar()
{
    m_nType = SCALAR_TYPE_MEM_USAGE;
}


CMemUsageScalar::~CMemUsageScalar()
{
}


double CMemUsageScalar::FetchData()
{
    double usage = 0.0;

    usage = CHostStatus::GetMemUsage();
    usage = (double)((int)(usage * 10.0) / 10); /*精度1*/
    return usage;
}


void CMemUsageScalar::UpdateThrod()
{
    m_nMaxThrod = 90.0;
    m_nMinThrod = 70.0;
    m_nTimesThrod = 2;
}





