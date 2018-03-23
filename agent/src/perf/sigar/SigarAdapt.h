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



protected:

private:
    static sigar_t *sm_pSigar;

};












