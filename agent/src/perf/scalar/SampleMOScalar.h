/**********************************************************
 * File: SampleMOScalar.h
 * Function: 
 *********************************************************/
#pragma once

#include "Timer.h"



enum{
    SCALAR_TYPE_CPU_USAGE,
    SCALAR_TYPE_MEM_USAGE,
    SCALAR_TYPE_DISK_USAGE,
    SCALAR_TYPE_SWAP_USAGE,
    SCALAR_TYPE_CPU_MONO_USAGE,
};




#define DEF_SCALAR_PERIOD 10


class CSampleMOScalar : public CTimerBase
{
public:
    CSampleMOScalar();
    virtual ~CSampleMOScalar();

    virtual void Run();


    bool IsAlarm(){return m_bIsAlarm;}
    void SetAlarm(bool isAlarm){m_bIsAlarm = isAlarm;}

    int GetType(){return m_nType;}

    double GetMaxThrod(){return m_nMaxThrod;}
    void SetMaxThrod(double val){m_nMaxThrod = val;}

    double GetMinThrod(){return m_nMinThrod;}
    void SetMinThrod(double val){m_nMinThrod = val;}

    int GetTimesThrod(){return m_nTimesThrod;}
    void SetTimesThrod(int val){m_nTimesThrod = val;}

    int GetMaxTimes(){return m_nMaxTimes;}
    void SetMaxTimes(int val){m_nMaxTimes = val;}

    int GetMinTimes(){return m_nMinTimes;}
    void SetMinTimes(int val){m_nMinTimes = val;}

    int GetMidTimes(){return m_nMidTimes;}
    void SetMidTimes(int val){m_nMidTimes = val;}



    virtual void UpdateThrod() = 0;
    virtual double FetchData();
    virtual int FetchData(int **pUsage, unsigned long *pOutLen);


    void ReportAlarm(double val);



protected:
    bool m_bIsAlarm;
    int m_nType;

    double m_nMaxThrod;
    double m_nMinThrod;

    int m_nTimesThrod;
    int m_nMaxTimes;
    int m_nMinTimes;
    int m_nMidTimes;


};





















