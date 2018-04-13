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

    m_listCpu.clear();
    m_listMem.clear();
    m_listSize.clear();
    m_listVirt.clear();
    m_listRes.clear();
    m_listShr.clear();
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

    m_listCpu.clear();
    m_listMem.clear();
    m_listSize.clear();
    m_listVirt.clear();
    m_listRes.clear();
    m_listShr.clear();
}




void CProcess::SetTime(unsigned long long time)
{
    char tStr[64] = {0};

    snprintf(tStr, (sizeof(tStr)-1), "%lld", time);
    m_strTime.assign(tStr);
}






int CProcess::AddCpuList(double cpu)
{
    m_listCpu.push_back(cpu);
    return 0;
}



void CProcess::ClearCpuList()
{
    m_listMem.clear();
}



int CProcess::CalcCpuAve()
{
    double sum = 0.0;
    double max = 0.0;
    list<double>::iterator it;

    for (it = m_listCpu.begin(); it != m_listCpu.end(); it++)
    {
        sum += *it;
        if (sum > (*it))
        {
            max = *it;
        }
    }

    SetCpu(sum / m_listCpu.size());
    SetCpuMax(max);
    return 0;
}



int CProcess::AddMemList(double mem)
{
    m_listMem.push_back(mem);
    return 0;
}



void CProcess::ClearMemList()
{
    m_listMem.clear();
}



int CProcess::CalcMemAve()
{
    double sum = 0.0;
    double max = 0.0;
    list<double>::iterator it;

    for (it = m_listMem.begin(); it != m_listMem.end(); it++)
    {
        sum += *it;
        if (sum > (*it))
        {
            max = *it;
        }
    }

    SetMem(sum / m_listMem.size());
    SetMemMax(max);
    return 0;
}



int CProcess::AddSizeList(unsigned long long size)
{
    m_listSize.push_back(size);
    return 0;
}



void CProcess::ClearSizeList()
{
    m_listSize.clear();
}



int CProcess::CalcSizeAve()
{
    unsigned long long sum = 0;
    list<unsigned long long>::iterator it;

    for (it = m_listSize.begin(); it != m_listSize.end(); it++)
    {
        sum += *it;
    }

    SetSize(sum / m_listSize.size());
    return 0;
}



int CProcess::AddVirtList(unsigned long long virt)
{
    m_listVirt.push_back(virt);
    return 0;
}



void CProcess::ClearVirtList()
{
    m_listVirt.clear();
}



int CProcess::CalcVirtAve()
{
    unsigned long long sum = 0;
    list<unsigned long long>::iterator it;

    for (it = m_listVirt.begin(); it != m_listVirt.end(); it++)
    {
        sum += *it;
    }

    SetSize(sum / m_listVirt.size());
    return 0;
}



int CProcess::AddResList(unsigned long long size)
{
    m_listRes.push_back(size);
    return 0;
}



void CProcess::ClearResList()
{
    m_listRes.clear();
}



int CProcess::CalcResAve()
{
    unsigned long long sum = 0;
    list<unsigned long long>::iterator it;

    for (it = m_listRes.begin(); it != m_listRes.end(); it++)
    {
        sum += *it;
    }

    SetSize(sum / m_listRes.size());
    return 0;
}



int CProcess::AddShrList(unsigned long long size)
{
    m_listShr.push_back(size);
    return 0;
}



void CProcess::ClearShrList()
{
    m_listShr.clear();
}



int CProcess::CalcShrAve()
{
    unsigned long long sum = 0;
    list<unsigned long long>::iterator it;

    for (it = m_listShr.begin(); it != m_listShr.end(); it++)
    {
        sum += *it;
    }

    SetSize(sum / m_listShr.size());
    return 0;
}














