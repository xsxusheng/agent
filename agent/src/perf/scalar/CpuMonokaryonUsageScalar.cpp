/**********************************************************
 * File: CpuMonokaryonUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "CpuMonokaryonUsageScalar.h"
#include "sv_log.h"
#include "HostStatus.h"





CCpuMonokaryonUsageScalar::CCpuMonokaryonUsageScalar()
{
    m_nType = SCALAR_TYPE_CPU_MONO_USAGE;
}


CCpuMonokaryonUsageScalar::~CCpuMonokaryonUsageScalar()
{
}



int CCpuMonokaryonUsageScalar::FetchData(double **pUsage, unsigned long *pOutLen)
{
    if (pUsage == NULL || pOutLen == NULL)
    {
        return -1;
    }
    return CHostStatus::GetCpuMonokaryonUsage(pUsage, pOutLen);
}


void CCpuMonokaryonUsageScalar::UpdateThrod()
{
    m_nMaxThrod = 90.0;
    m_nMinThrod = 70.0;
    m_nTimesThrod = 2;
}



void CCpuMonokaryonUsageScalar::Run()
{
    unsigned long i = 0;
    unsigned long len = 0;
    double usageMax = 0.0;
    double *usageTotal = NULL;

    FetchData(&usageTotal, &len);
    if (usageTotal == NULL || len <= 0)
    {
        SV_ERROR("Fetch Cpumonokaryon usage error.");
        return;
    }

    if (IsAlarm())
    {
        UpdateThrod();
        for (i = 0; i < len; i++)
        {
            if (usageMax < usageTotal[i])
            {
                usageMax = usageTotal[i];
            }
        }

        ReportAlarm(usageMax);
    }

    /*释放空间*/
    delete []usageTotal;
    usageTotal = NULL;
}






