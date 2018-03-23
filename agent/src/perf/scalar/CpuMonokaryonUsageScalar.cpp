/**********************************************************
 * File: CpuMonokaryonUsageScalar.cpp
 * Function: 
 *********************************************************/
#include "CpuMonokaryonUsageScalar.h"

#include "HostStatus.h"





CCpuMonokaryonUsageScalar::CCpuMonokaryonUsageScalar()
{
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
}



void CCpuMonokaryonUsageScalar::Run()
{
    int usageMax = 0;
    unsigned long i = 0;
    unsigned long len = 0;
    double *usageTotal = NULL;

    FetchData(&usageTotal, &len);
    if (usageTotal == NULL || len <= 0)
    {
        return;
    }
    
    if (IsAlarm())
    {
        UpdateThrod();
        for (i = 0; i < len; i++)
        {
            if (usageMax > usageTotal[i])
            {
                usageMax = usageTotal[i];
            }
        }
        
        ReportAlarm(usageMax);
    }
}






