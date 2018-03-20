/**********************************************************
 * File: SigarAdapt.cpp
 * Function: Sigar
 *********************************************************/
#include "SigarAdapt.h"

#include "CpuUsage.h"
#include "MemUsage.h"
#include "FileSystem.h"
#include "SwapUsage.h"



sigar_t *CSigar::sm_pSigar = NULL;



#if 0
#endif



int CSigar::InitSigar()
{
    sm_pSigar = NULL;
	if (SIGAR_OK == sigar_open(&sm_pSigar))
	{
        return 0;
	}
    return -1;
}


void CSigar::DestroySigar()
{
    if (sm_pSigar != NULL)
    {
	    sigar_close(sm_pSigar);
        sm_pSigar = NULL;
    }
}


sigar_t *CSigar::GetSigar()
{
    return sm_pSigar;
}



#if 0
#endif



CSigar::CSigar()
{
}


CSigar::~CSigar()
{
}


int CSigar::GetCpuUsage()
{
    CCpuUsage tCpuUsage;

    return tCpuUsage.GetCpuUsageTotal();
}


string CSigar::GetCpuUsageString()
{
    CCpuUsage tCpuUsage;

    return tCpuUsage.GetCpuUsageString();
}


int CSigar::GetCpuMonokaryonUsage(int **pUsage, unsigned long *pOutLen)
{
    CCpuUsage tCpuUsage;

    if (pUsage == NULL || pOutLen == NULL)
    {
        return -1;
    }

    return tCpuUsage.GetCpuPercsUsage(pUsage, pOutLen);
}



int CSigar::GetMemUsage()
{
    int usage = 0;
    CMemUsage tMemUsage;

    tMemUsage.GetMemUsage();
    usage = (int)tMemUsage.GetMemFreePercent();
    return usage;
}



int CSigar::GetSwapUsage()
{
    int usage = 0;
    CSwapUsage tSwapUsage;

    tSwapUsage.GetSwapUsage();
    if (tSwapUsage.GetTotal() > 0)
    {
        usage = (int)(100.0 * (double)(tSwapUsage.GetUsed() / tSwapUsage.GetTotal()));
    }
    return usage;
}



int CSigar::GetDiskUsage()
{
    int usage = 0;
    double avail = 0.0;
    double total = 0.0;
    CFileSystem tFileSystem;

    tFileSystem.GetFileSystem();
    total = (double)tFileSystem.GetFileSysTotal();
    avail = (double)tFileSystem.GetFileSysAvail();

    if (total > 0)
    {
        usage = (int)(100.0 * (total - avail) / total);
    }
    return usage;
}
















