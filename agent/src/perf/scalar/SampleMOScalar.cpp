/**********************************************************
 * File: SampleMOScalar.cpp
 * Function: 
 *********************************************************/
#include "SampleMOScalar.h"






CSampleMOScalar::CSampleMOScalar()
{
}


CSampleMOScalar::~CSampleMOScalar()
{
}


int CSampleMOScalar::FetchData()
{
    return 0;
}


int CSampleMOScalar::FetchData(int **pUsage, unsigned long *pOutLen)
{
    return 0;
}





void CSampleMOScalar::Run()
{
    int val = 0;

    val = FetchData();
    if (IsAlarm())
    {
        UpdateThrod();
        ReportAlarm(val);
    }
}


void CSampleMOScalar::ReportAlarm(int val)
{
    /*连续多次大于二级门限，发送严重告警*/
    if (val >= GetMaxThrod())
    {
        SetMaxTimes(GetMaxTimes() + 1);
        if (GetMaxTimes() == GetTimesThrod())
        {
            SetMaxTimes(0);

            /*报告警*/
        }
    }
    else
    {
        SetMaxTimes(0);
    }
    
    /*连续多次小于一级门限，发送清除告警*/
    if (val <= GetMinThrod())
    {
        SetMinTimes(GetMinTimes() + 1);
        if (GetMinTimes() == GetTimesThrod())
        {
            SetMinTimes(0);

            /*报告警*/
        }
    }
    else
    {
        SetMinTimes(0);
    }
    
    /*连续多次介于一级和二级门限之间，发送清除告警*/
    if ((val > GetMinThrod()) && (val < GetMaxThrod()))
    {
        SetMidTimes(GetMidTimes() + 1);
        if (GetMidTimes() == GetTimesThrod())
        {
            SetMidTimes(0);

            /*报告警*/
        }
    }
    else
    {
        SetMidTimes(0);
    }
}












