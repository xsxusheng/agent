/**********************************************************
 * File: SwapUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "SwapUsageScalar.h"

#include "SigarAdapt.h"




CSwapUsageScalar::CSwapUsageScalar()
{
}


CSwapUsageScalar::~CSwapUsageScalar()
{
}


int CSwapUsageScalar::FetchData()
{
    return CSigar::GetSwapUsage();
}


void CSwapUsageScalar::UpdateThrod()
{
}




















