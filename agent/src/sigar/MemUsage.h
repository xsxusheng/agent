/**********************************************************
 * File: MemUsage.h
 * Function: 
 *********************************************************/
#pragma once



class CMemUsage
{
public:
    CMemUsage();
    ~CMemUsage();


    unsigned long long GetMemRam(){return m_nRam;}
    unsigned long long GetMemTotal(){return m_nTotal;}
    unsigned long long GetMemUsed(){return m_nUsed;}
    unsigned long long GetMemFree(){return m_nFree;}
    unsigned long long GetMemActualUsed(){return m_nActualUsed;}
    unsigned long long GetMemActualFree(){return m_nActualFree;}
    double GetMemUsedPercent(){return m_fUsedPercent;}
    double GetMemFreePercent(){return m_fFreePercent;}


    int GetMemUsage();


protected:


private:
    unsigned long long m_nRam;
    unsigned long long m_nTotal;
    unsigned long long m_nUsed;
    unsigned long long m_nFree;
    unsigned long long m_nActualUsed;
    unsigned long long m_nActualFree;
    double m_fUsedPercent;
    double m_fFreePercent;

};


















