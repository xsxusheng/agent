/**************************************************************
 * File: CpuUsage.h
 * Function: 封装Sigar功能
 *
 *************************************************************/
#pragma once

#include <cstring>
#include <string>

#include "sigar.h"

using namespace std;


class CCpuPerc
{
public:
    CCpuPerc();
    ~CCpuPerc();


    unsigned long long GetUser(){return m_nUser;}
    unsigned long long GetSys(){return m_nSys;}
    unsigned long long GetNice(){return m_nNice;}
    unsigned long long GetIdle(){return m_nIdle;}
    unsigned long long GetWait(){return m_nWait;}
    unsigned long long GetIrq(){return m_nIrq;}
    unsigned long long GetSoftIrq(){return m_nSoftIrq;}
    unsigned long long GetStolen(){return m_nStolen;}
    unsigned long long GetTotal(){return m_nTotal;}
    double GetCombined(){return m_fCombined;}


    void SetUser(unsigned long long user){m_nUser = user;}
    void SetSys(unsigned long long sys){m_nSys = sys;}
    void SetNice(unsigned long long nice){m_nNice = nice;}
    void SetIdle(unsigned long long idle){m_nIdle = idle;}
    void SetWait(unsigned long long wait){m_nWait = wait;}
    void SetIrq(unsigned long long irq){m_nIrq = irq;}
    void SetSoftIrq(unsigned long long softIrq){m_nSoftIrq = softIrq;}
    void SetStolen(unsigned long long stolen){m_nStolen = stolen;}
    void SetTotal(unsigned long long total){m_nTotal = total;}
    void SetCombined(double combined){m_fCombined = combined;}


    CCpuPerc& operator=(CCpuPerc& cpuPerc);

protected:


private:
    unsigned long long m_nUser;
    unsigned long long m_nSys;
    unsigned long long m_nNice;
    unsigned long long m_nIdle;
    unsigned long long m_nWait;
    unsigned long long m_nIrq;
    unsigned long long m_nSoftIrq;
    unsigned long long m_nStolen;
    unsigned long long m_nTotal;
    double m_fCombined;
};




class CCpuUsage
{
public:
    CCpuUsage();
    ~CCpuUsage();


    CCpuPerc *GetCpuPercs(){return m_pCpuPercs;}
    CCpuPerc *GetCpuPerc(unsigned long index);

    void SetCpuPerc(CCpuPerc& cpuPerc, unsigned long index);
    void SetCpuPerc(sigar_cpu_t& cpu, unsigned long index);

    unsigned long GetCpuNum(){return m_nCpuNum;}
    void SetCpuNum(unsigned long num){if(num > 0){m_nCpuNum = num;}}


    unsigned long GetCpuPercNum();
    int GetCpuStat();
    int GetCpuBaseInfo();


    int GetCpuUsage(CCpuPerc **pCpuPers, unsigned long *pOutCpuNum);
    int GetCpuPercsUsage(int **pUsage, unsigned long *pOutLen);
    string GetCpuUsageString();
    int GetCpuUsageTotal();
    


private:
    unsigned long m_nCpuNum;
    CCpuPerc *m_pCpuPercs;
};



















