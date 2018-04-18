/**********************************************************
 * File: SampleMOScalar.cpp
 * Function: 
 *********************************************************/
#include "SampleMOScalar.h"
#include "sv_log.h"





CSampleMOScalar::CSampleMOScalar()
{
    m_bIsAlarm = true;

    m_nMaxThrod = 0;
    m_nMinThrod = 0;

    m_nTimesThrod = 0;
    m_nMaxTimes = 0;
    m_nMinTimes = 0;
    m_nMidTimes = 0;
}


CSampleMOScalar::~CSampleMOScalar()
{
}


double CSampleMOScalar::FetchData()
{
    return 0;
}


int CSampleMOScalar::FetchData(int **pUsage, unsigned long *pOutLen)
{
    return 0;
}





void CSampleMOScalar::Run()
{
    double val = 0.0;

    val = FetchData();
    if (IsAlarm())
    {
        UpdateThrod();
        ReportAlarm(val);
    }
}


void CSampleMOScalar::ReportAlarm(double val)
{
    SV_LOG("CSampleMOScalar::ReportAlarm: Type=%d Cur_Val=%f, Max=%f Min=%f ...",
        GetType(), val, GetMaxThrod(), GetMinThrod());

    /*连续多次大于二级门限，发送严重告警*/
    if (val >= GetMaxThrod())
    {
        SetMaxTimes(GetMaxTimes() + 1);
        if (GetMaxTimes() >= GetTimesThrod())
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
        if (GetMinTimes() >= GetTimesThrod())
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
        if (GetMidTimes() >= GetTimesThrod())
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












