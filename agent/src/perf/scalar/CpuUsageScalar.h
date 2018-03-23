/**********************************************************
 * File: CpuUsageScalar.h
 * Function: 
 *********************************************************/
#pragma once

#include "SampleMOScalar.h"


class CCpuUsageScalar : public CSampleMOScalar
{
public:
    CCpuUsageScalar();
    virtual ~CCpuUsageScalar();


    virtual void UpdateThrod();
    virtual int FetchData();


private:

};










