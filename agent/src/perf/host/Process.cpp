/**********************************************************
 * File: Process.cpp
 * Function: 
 *********************************************************/
#include "Process.h"

#include <cstdio>



CProcess::CProcess()
{
    m_nPid = 0;
    m_nSize = 0;
    m_nVirt = 0;
    m_nRes = 0;
    m_nShr = 0;

    m_fCpu = 0;
    m_fCpuMax = 0;
    m_fMem = 0;
    m_fMemMax = 0;

    m_strCommand.clear();
    m_strTime.clear();
    m_strState.clear();
}


CProcess::~CProcess()
{
    m_nPid = 0;
    m_nSize = 0;
    m_nVirt = 0;
    m_nRes = 0;
    m_nShr = 0;

    m_fCpu = 0;
    m_fCpuMax = 0;
    m_fMem = 0;
    m_fMemMax = 0;

    m_strCommand.clear();
    m_strTime.clear();
    m_strState.clear();
}




void CProcess::SetTime(unsigned long long time)
{
    char tStr[64] = {0};

    snprintf(tStr, (sizeof(tStr)-1), "%lld", time);
    m_strTime.assign(tStr);
}

















