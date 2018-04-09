/**********************************************************
 * File: ProcessStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>

#include "Timer.h"
#include "Process.h"

using namespace std;



#define DEF_PROCESS_REPORT (15 * 60)


class CProcessStatic : public CTimerBase
{
public:
    CProcessStatic();
    ~CProcessStatic();


    void Run();
    bool NeedReportFums();

    bool CheckProcExist(string& args);


    void GetProcStatus();
    void CalcAvrg();
    void SendToFums();


private:
    list<string> m_listProc;
    list<CProcess> m_listprocess;

    CTime m_lastReportFums;

};






















