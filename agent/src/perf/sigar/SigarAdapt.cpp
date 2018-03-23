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















