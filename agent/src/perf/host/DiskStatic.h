/**********************************************************
 * File: DiskStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <list>
#include "Timer.h"

using namespace std;



class CDisk
{
public:
    CDisk();
    ~CDisk();


    string GetDev(){return m_strDev;}
    void SetDev(string& dev){m_strDev = dev;}

    float GetTps(){return m_fTps;}
    void SetTps(float tps){m_fTps = tps;}

    float GetRdSec(){return m_fRdSec;}
    void SetRdSec(float rdSec){m_fRdSec = rdSec;}

    float GetWrSec(){return m_fWrSec;}
    void SetWrSec(float wrSec){m_fWrSec = wrSec;}

    float GetAvgrq(){return m_fAvgrq;}
    void SetAvgrq(float avgrq){m_fAvgrq = avgrq;}

    float GetAvgqu(){return m_fAvgqu;}
    void SetAvgqu(float avgqu){m_fAvgqu = avgqu;}

    float GetAwait(){return m_fAwait;}
    void SetAwait(float await){m_fAwait = await;}

    float GetSvctm(){return m_fSvctm;}
    void SetSvctm(float svctm){m_fSvctm = svctm;}

    float GetUtil(){return m_fUtil;}
    void SetUtil(float util){m_fUtil = util;}



private:

    string m_strDev;
    float m_fTps;
    float m_fRdSec;
    float m_fWrSec;
    float m_fAvgrq;
    float m_fAvgqu;
    float m_fAwait;
    float m_fSvctm;
    float m_fUtil;

};





#define DISK_STAT_SCRIPT "./diskstat.sh"
#define MAX_DISK_SPLIT_NUM 10
#define DEF_DISK_STATIC_REPORT (15 * 60)


class CDiskStatic : public CTimerBase
{
public:
    CDiskStatic();
    ~CDiskStatic();


    void Run();


    void Sample();
    void SendToFums();
    bool NeedReportFums();


private:
    CTime m_lastReportFums;
    list<CDisk> m_listDisk;

};




















