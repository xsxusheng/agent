/**********************************************************
 * File: MemUsage.cpp
 * Function: 
 *********************************************************/
#include "MemUsage.h"

#include "sigar.h"
#include "SigarAdapt.h"





CMemUsage::CMemUsage()
{
    m_nRam = 0;
    m_nTotal = 0;
    m_nUsed = 0;
    m_nFree = 0;
    m_nActualUsed = 0;
    m_nActualFree = 0;
    m_fUsedPercent = 0.0;
    m_fFreePercent = 0.0;
}



CMemUsage::~CMemUsage()
{
    m_nRam = 0;
    m_nTotal = 0;
    m_nUsed = 0;
    m_nFree = 0;
    m_nActualUsed = 0;
    m_nActualFree = 0;
    m_fUsedPercent = 0.0;
    m_fFreePercent = 0.0;
}



int CMemUsage::GetMemUsage()
{
    sigar_mem_t mem;

    if (SIGAR_OK != sigar_mem_get(CSigar::GetSigar(), &mem))
    {
        return -1;
    }

    m_nRam = mem.ram;
    m_nTotal = mem.total;
    m_nUsed = mem.used;
    m_nFree = mem.free;
    m_nActualUsed = mem.actual_used;
    m_nActualFree = mem.actual_free;
    m_fUsedPercent = mem.used_percent;
    m_fFreePercent = mem.free_percent;

    return 0;
}















