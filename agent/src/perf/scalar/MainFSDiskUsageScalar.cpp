/**********************************************************
 * File: MainFSDiskUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "MainFSDiskUsageScalar.h"

#include "HostStatus.h"





CMainFSDiskUsageScalar::CMainFSDiskUsageScalar()
{
}


CMainFSDiskUsageScalar::~CMainFSDiskUsageScalar()
{
}



int CMainFSDiskUsageScalar::FetchData()
{
    return CHostStatus::GetCpuUsage();
}


void CMainFSDiskUsageScalar::UpdateThrod()
{
}


















