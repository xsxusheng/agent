/**********************************************************
 * File: MemUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "MemoryUsageScalar.h"

#include "SigarAdapt.h"


CMemUsageScalar::CMemUsageScalar()
{
}


CMemUsageScalar::~CMemUsageScalar()
{
}


int CMemUsageScalar::FetchData()
{
    return CSigar::GetMemUsage();
}


void CMemUsageScalar::UpdateThrod()
{
}





