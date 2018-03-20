/**********************************************************
 * File: MainFSDiskUsageScalar.h
 * Function: 
 *********************************************************/
#pragma once

#include "SampleMOScalar.h"





class CMainFSDiskUsageScalar : public CSampleMOScalar
{
public:
    CMainFSDiskUsageScalar();
    virtual ~CMainFSDiskUsageScalar();


    virtual void UpdateThrod();
    virtual int FetchData();


private:

};





















