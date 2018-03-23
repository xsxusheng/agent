/**********************************************************
 * File: SwapUsage.cpp
 * Function: SWAP
 *********************************************************/
#include "SwapUsage.h"

#include "sigar.h"
#include "SigarAdapt.h"


CSwapUsage::CSwapUsage()
{
}



CSwapUsage::~CSwapUsage()
{
}




int CSwapUsage::GetSwapUsage()
{
    sigar_swap_t swap;

    if (SIGAR_OK != sigar_swap_get(CSigar::GetSigar(), &swap))
    {
        printf("sigar_swap_get error.");
        return -1;
    }

    m_nTotal = swap.total;
    m_nUsed = swap.used;
    m_nFree = swap.free;
    m_nPageIn = swap.page_in;
    m_nPageOut = swap.page_out;
    
    return 0;
}
























