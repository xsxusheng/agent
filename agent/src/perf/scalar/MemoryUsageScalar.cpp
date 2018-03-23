/**********************************************************
 * File: MemUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "MemoryUsageScalar.h"

#include "HostStatus.h"


CMemUsageScalar::CMemUsageScalar()
{
}


CMemUsageScalar::~CMemUsageScalar()
{
}


int CMemUsageScalar::FetchData()
{
    return CHostStatus::GetMemUsage();
}


void CMemUsageScalar::UpdateThrod()
{
}





