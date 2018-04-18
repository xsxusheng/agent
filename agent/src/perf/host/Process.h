/**********************************************************
 * File: Process.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>
#include <list>

using namespace std;





class CProcess
{
public:
    CProcess();
    ~CProcess();


    long GetPid(){return m_nPid;}
    void SetPid(long pid){m_nPid = pid;}

    long GetSize(){return m_nSize;}
    void SetSize(long size){m_nSize = size;}

    long GetVirt(){return m_nVirt;}
    void SetVirt(long virt){m_nVirt = virt;}

    long GetRes(){return m_nRes;}
    void SetRes(long res){m_nRes = res;}

    long GetShr(){return m_nShr;}
    void SetShr(long shr){m_nShr = shr;}

    double GetCpu(){return m_fCpu;}
    void SetCpu(double cpu){m_fCpu = cpu;}

    double GetCpuMax(){return m_fCpuMax;}
    void SetCpuMax(double cpu){m_fCpuMax = cpu;}

    double GetMem(){return m_fMem;}
    void SetMem(double mem){m_fMem = mem;}

    double GetMemMax(){return m_fMemMax;}
    void SetMemMax(double mem){m_fMemMax = mem;}

    string GetCommand(){return m_strCommand;}
    void SetCommand(string& cmd){m_strCommand = cmd;}

    string GetTime(){return m_strTime;}
    void SetTime(string& time){m_strTime = time;}
    void SetTime(unsigned long long time);

    string GetState(){return m_strState;}
    void SetState(string& cmd){m_strState = cmd;}


private:

    long m_nPid;
    long m_nSize;
    long m_nVirt;
    long m_nRes;
    long m_nShr;
    
    double m_fCpu;
    double m_fCpuMax;
    double m_fMem;
    double m_fMemMax;
    
    string m_strCommand;
    string m_strTime;
    string m_strState;

};







