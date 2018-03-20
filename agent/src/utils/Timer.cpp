/**********************************************************
 * File: Timer.cpp
 * Function: 
 *********************************************************/

#include "Timer.h"




CTimer::CTimer()
{
    m_TimerList.clear();
    memset(m_sTidSet, 0, sizeof(m_sTidSet));
}


CTimer::~CTimer()
{
    m_TimerList.clear();
    memset(m_sTidSet, 0, sizeof(m_sTidSet));
}


int CTimer::TimerLock()
{
    return m_lock.Lock();
}


int CTimer::TimerUnLock()
{
    return m_lock.UnLock();
}


int CTimer::GetFreeTimerId()
{
    int i = 0;
    int tid = -1;

    TimerLock();
    for (i = 0; i < MAX_TIMER_NUM; i++)
    {
        if (m_sTidSet[i] != 0)
        {
            tid = i;
            break;
        }
    }

    TimerUnLock();
    return tid;
}


int CTimer::ReleaseTimerId(int tid)
{
    if (tid < 0 || tid >= MAX_TIMER_NUM)
    {
        return -1;
    }

    TimerLock();
    m_sTidSet[tid] = 0;
    TimerUnLock();
    return 0;
}


int CTimer::TimerStart(CTimerBase *pObj, long timeout)
{
    int tid = -1;
    CTimerNode node;

    if (pObj == NULL || timeout <= 0)
    {
        return -1;
    }
    
    /*防止链表无线放大*/
    if (m_TimerList.size() >= MAX_TIMER_NUM)
    {
        return -1;
    }

    node.GetNodeStartTime().GetTimeNow();
    node.SetNodeTimeout(timeout);
    node.SetNodeId(GetFreeTimerId());
    if (node.GetNodeId() < 0)
    {
        return -1;
    }

    TimerLock();

    if (m_TimerList.size() < MAX_TIMER_NUM)
    {
        m_TimerList.push_back(node);
        tid = node.GetNodeId();
    }
    
    TimerUnLock();

    if (tid < 0)
    {
        /*如果链表插入失败，需要释放TID资源*/
        ReleaseTimerId(node.GetNodeId());
    }
    return tid;
}


int CTimer::TimerDelete(int tid)
{
    TIMERLIST::iterator it;

    TimerLock();
    for(it = m_TimerList.begin(); it != m_TimerList.end();)
    {
        if (it->GetNodeId() == tid)
        {
            /*ERASE方法调用后指向下一个节点*/
            it = m_TimerList.erase(it);
        }
        else
        {
            it++;
        }
    }
    TimerUnLock();
    return 0;
}



void CTimer::__DoRun()
{
    CTime tNow;
    TIMERLIST::iterator it;

    while(1)
    {
        /*默认每秒遍历一次*/
        CTime::secSleep(1);

        /*获取当前时间*/
        tNow.GetTimeNow();
        
        TimerLock();
        for (it = m_TimerList.begin(); it != m_TimerList.end(); it++)
        {
            if (tNow.DiffSec(it->GetNodeStartTime()) >= it->GetNodeTimeout())
            {
                it->GetNodeObj()->Run();

                /*更新最近一次的启动时间*/
                it->SetNodeStartTime(tNow);
            }
        }
        TimerUnLock();
    }
}





