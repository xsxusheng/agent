/**********************************************************
 * File: MemoryUsageScalar.h
 * Function: 
 *********************************************************/
#pragma once

#include "SampleMOScalar.h"



class CMemUsageScalar : public CSampleMOScalar
{
public:
    CMemUsageScalar();
    virtual ~CMemUsageScalar();


    virtual void UpdateThrod();
    virtual double FetchData();


private:

};










