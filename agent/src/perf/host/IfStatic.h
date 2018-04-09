/**********************************************************
 * File: IfStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <list>
#include "Timer.h"

using namespace std;



#define DEF_NETIF_REPORT (15 * 60)


class CIfStatic : CTimerBase
{
public:
    CIfStatic();
    ~CIfStatic();
    

    void Run();


    void Sample();
    void SendToFums();
    bool NeedReportFums();


private:

    CTime m_lastReportFums;


};









