/**************************************************************
 * File: SigarAdapt.h
 * Function: 封装Sigar功能
 *
 *************************************************************/
#pragma once

#include <string>

#include "sigar.h"

using namespace std;



class CSigar
{
public:
	CSigar();
	~CSigar();

    static int InitSigar();
    static void DestroySigar();
    static sigar_t *GetSigar();


    static int GetCpuUsage();
    static string GetCpuUsageString();
    static int GetCpuMonokaryonUsage(int **pUsage, unsigned long *pOutLen);

    static int GetMemUsage();
    static int GetSwapUsage();
    static int GetDiskUsage();


protected:

private:
    static sigar_t *sm_pSigar;

};












