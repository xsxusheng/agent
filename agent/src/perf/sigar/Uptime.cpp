/**********************************************************
 * File: Uptime.cpp
 * Function: 
 *********************************************************/
#include "Uptime.h"

#include "SigarAdapt.h"







double CUptime::GetUptime()
{
    sigar_uptime_t uptime;

    if (SIGAR_OK == sigar_uptime_get(CSigar::GetSigar(), &uptime))
    {
        return uptime.uptime;
    }

    return 0.0;
}










