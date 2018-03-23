/**********************************************************
 * File: SampleMOScalar.h
 * Function: 
 *********************************************************/
#pragma once

#include "Timer.h"






class CSampleMOScalar : public CTimerBase
{
public:
    CSampleMOScalar();
    virtual ~CSampleMOScalar();

    virtual void Run();


    bool IsAlarm(){return m_bIsAlarm;}
    void SetAlarm(bool isAlarm){m_bIsAlarm = isAlarm;}

    int GetMaxThrod(){return m_nMaxThrod;}
    void SetMaxThrod(int val){m_nMaxThrod = val;}

    int GetMinThrod(){return m_nMinThrod;}
    void SetMinThrod(int val){m_nMinThrod = val;}

    int GetTimesThrod(){return m_nTimesThrod;}
    void SetTimesThrod(int val){m_nTimesThrod = val;}

    int GetMaxTimes(){return m_nMaxTimes;}
    void SetMaxTimes(int val){m_nMaxTimes = val;}

    int GetMinTimes(){return m_nMinTimes;}
    void SetMinTimes(int val){m_nMinTimes = val;}

    int GetMidTimes(){return m_nMidTimes;}
    void SetMidTimes(int val){m_nMidTimes = val;}



    virtual void UpdateThrod() = 0;
    virtual int FetchData();
    virtual int FetchData(int **pUsage, unsigned long *pOutLen);


    void ReportAlarm(int val);


    static CTimer* GetSampleTimer();


private:
    bool m_bIsAlarm;

    int m_nMaxThrod;
    int m_nMinThrod;

    int m_nTimesThrod;
    int m_nMaxTimes;
    int m_nMinTimes;
    int m_nMidTimes;


    static CTimer m_sTimer;

};





















