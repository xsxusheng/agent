/**********************************************************
 * File: MainFSDiskUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "MainFSDiskUsageScalar.h"

#include "SigarAdapt.h"





CMainFSDiskUsageScalar::CMainFSDiskUsageScalar()
{
}


CMainFSDiskUsageScalar::~CMainFSDiskUsageScalar()
{
}



int CMainFSDiskUsageScalar::FetchData()
{
    return CSigar::GetCpuUsage();
}


void CMainFSDiskUsageScalar::UpdateThrod()
{
}


















