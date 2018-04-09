/**********************************************************
 * File: ProcInfo.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>

using namespace std;






#define PROC_STATE_SLEEP  'S'
#define PROC_STATE_RUN    'R'
#define PROC_STATE_STOP   'T'
#define PROC_STATE_ZOMBIE 'Z'
#define PROC_STATE_IDLE   'D'

#define MAX_PROC_NAME_LEN 128


class CProcState
{
public:
    CProcState();
    ~CProcState();

    char* GetName(){return m_cName;}
    void SetName(char *name);

    char GetState(){return m_cState;}
    void SetState(char state);

    long GetPpid(){return m_nPpid;}
    void SetPpid(long pid){m_nPpid = pid;}

    int GetTty(){return m_nTty;}
    void SetTty(int tty){m_nTty = tty;}

    int GetPri(){return m_nPri;}
    void SetPri(int pri){m_nPri = pri;}

    int GetNice(){return m_nNice;}
    void SetNice(int nice){m_nNice = nice;}

    int GetProcessor(){return m_nProcessor;}
    void SetProcessor(int processor){m_nProcessor = processor;}

    unsigned long GetThread(){return m_nThreads;}
    void SetThread(unsigned long threads){m_nThreads = threads;}


    int GetProcState(long pid);


private:
    char m_cName[MAX_PROC_NAME_LEN];
    char m_cState;
    long m_nPpid;
    int m_nTty;
    int m_nPri;
    int m_nNice;
    int m_nProcessor;
    unsigned long m_nThreads;

};




class CProcArgs
{
public:
    CProcArgs();
    ~CProcArgs();

    unsigned long GetArgsNum(){return m_nArgsNum;}
    unsigned long GetArgsListNum();

    int AllocArgs(unsigned long size);
    void FreeArgs();

    char** GetArgs(){return m_cArgs;}
    char* GetArgs(unsigned long index);
    int SetArgs(unsigned long index, char *pArgs);

    int GetProcArgs(long pid);

private:
    unsigned long m_nArgsNum;
    char **m_cArgs;

};




class CProcCpu
{
public:
    CProcCpu(){};
    ~CProcCpu(){};

    unsigned long long GetStartTime(){return m_nStartTime;}
    void SetStartTime(unsigned long long startTime){m_nStartTime = startTime;}

    unsigned long long GetUser(){return m_nUser;}
    void SetUser(unsigned long long user){m_nUser = user;}

    unsigned long long GetSys(){return m_nSys;}
    void SetSys(unsigned long long sys){m_nSys = sys;}

    unsigned long long GetTotal(){return m_nTotal;}
    void SetTotal(unsigned long long total){m_nTotal = total;}

    unsigned long long GetLastTime(){return m_nLastTime;}
    void SetLastTime(unsigned long long stopped){m_nLastTime = stopped;}

    double GetPercent(){return m_fPercent;}
    void SetPercent(double percent){m_fPercent = percent;}


    int GetProcCpu(long pid);

private:
    unsigned long long m_nStartTime;
    unsigned long long m_nUser;
    unsigned long long m_nSys;
    unsigned long long m_nTotal;
    unsigned long long m_nLastTime;
    double m_fPercent;

};




class CProcMem
{
public:
    CProcMem();
    ~CProcMem();

    unsigned long long GetSize(){return m_nSize;}
    void SetSize(unsigned long long size){m_nSize = size;}

    unsigned long long GetRes(){return m_nRes;}
    void SetRes(unsigned long long res){m_nRes = res;}

    unsigned long long GetShare(){return m_nShare;}
    void SetShare(unsigned long long share){m_nShare = share;}


    int GetProcMem(long pid);


private:
    unsigned long long m_nSize;
    unsigned long long m_nRes;
    unsigned long long m_nShare;

};








class CProcPidList
{
public:
    CProcPidList();
    ~CProcPidList();


    unsigned long GetProcNum(){return m_nProcNum;}
    void SetProcNum(unsigned long num){m_nProcNum = num;}
    
    long* GetProcsPids(){return m_pPid;}
    long GetProcsPid(unsigned long index);
    int SetProcPid(unsigned long index, long pid);

    int AllocProcPid(unsigned long size);
    void FreeProcPid();


    int GetProcPidList();

private:
    unsigned long m_nProcNum;
    long *m_pPid;

};

























