/**********************************************************
 * File: ProcessStatic.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>
#include <map>

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
    bool FindProc(string& findProc, string& args);


    void GetProcStatus();
    void CalcAvrg();
    void ClearAvrg();
    void SendToFums();


private:
    list<string> m_listProc;
    list<CProcess> m_listProcess;
    map<string, list<CProcess> > m_mapProcess;

    CTime m_lastReportFums;

};






















