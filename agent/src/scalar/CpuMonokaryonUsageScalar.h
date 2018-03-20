/**********************************************************
 * File: CpuMonokaryonUsageScalar.h
 * Function: 
 *********************************************************/
#pragma once

#include "SampleMOScalar.h"



class CCpuMonokaryonUsageScalar : public CSampleMOScalar
{
public:
    CCpuMonokaryonUsageScalar();
    virtual ~CCpuMonokaryonUsageScalar();


    void Run();


    virtual void UpdateThrod();
    virtual int FetchData(int **pUsage, unsigned long *pOutLen);


private:



};











