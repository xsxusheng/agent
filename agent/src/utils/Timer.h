/**********************************************************
 * File: Timer.h
 * Function: 
 *********************************************************/
#pragma once

#include <list>
#include <cstring>

#include "Thread.h"
#include "TimeUtils.h"
#include "Lock.h"

using namespace std;


#define MAX_TIMER_NUM 128





class CTimerBase
{
public:
    CTimerBase(){};
    virtual ~CTimerBase(){}

    virtual void Run() = 0;

};





/*定时器节点*/
class CTimerNode
{
public:
    CTimerNode(){}
    ~CTimerNode(){}

    CTimerBase *GetNodeObj(){return m_pObj;}
    void SetNodeObj(CTimerBase *obj){m_pObj = obj;}

    int GetNodeId(){return m_nTid;}
    void SetNodeId(int tid){m_nTid = tid;}

    int GetNodeTimeout(){return m_nTimeout;}
    void SetNodeTimeout(int timeout){m_nTimeout = timeout;}

    CTime& GetNodeStartTime(){return m_startTime;}
    void SetNodeStartTime(CTime& time){m_startTime = time;}
    

private:
    /*基类指针，指向派生类的对象*/
    CTimerBase *m_pObj;


    /** 定时器唯一标识*/
	int m_nTid;

    /** 超时时间*/
	int m_nTimeout;

    /** 定时器开始时间*/
	CTime m_startTime;

};





typedef list<CTimerNode> TIMERLIST;

class CTimer : public Thread
{
public:
    CTimer();
    virtual ~CTimer();


    int GetFreeTimerId();
    int ReleaseTimerId(int tid);

    int TimerLock();
    int TimerUnLock();

    int TimerStart(CTimerBase *pObj, long timeout);
    int TimerDelete(int tid);

    void __DoRun();

private:
    CMutex m_lock;
    TIMERLIST m_TimerList;

    int m_sTidSet[MAX_TIMER_NUM];
};















