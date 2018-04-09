/**********************************************************
 * File: ProcessStatic.cpp
 * Function: 
 *********************************************************/
#include "ProcessStatic.h"

#include "ProcInfo.h"
#include "HostStatus.h"


CProcessStatic::CProcessStatic()
{
    m_listProc.clear();
    m_listProc.push_back("/opt/fonsview/bin/daemon");
    m_listProc.push_back("HostAgent");
    m_listProc.push_back("/opt/fonsview/3RD/jre/bin/java");
    m_listProc.push_back("/opt/fonsview/NE/lrs/bin/lrs");
    m_listProc.push_back("/usr/local/bin/python ./csagent.py");
    m_listProc.push_back("/usr/local/bin/python csxagent.py");
    m_listProc.push_back("/usr/local/bin/python ./cspagent.py");
    m_listProc.push_back("/usr/local/bin/python csvagent.py");
    m_listProc.push_back("/usr/bin/java -jar /opt/fonsview/NE/lcm/lcm.jar");
    m_listProc.push_back("/usr/local/squid/sbin/squid -s");

    m_lastReportFums.GetTimeNow();
}



CProcessStatic::~CProcessStatic()
{
    m_listProc.clear();
}





bool CProcessStatic::NeedReportFums()
{
    CTime tNow;

    if (m_lastReportFums.DiffSec(tNow) >= DEF_PROCESS_REPORT)
    {
        /*重置上次上报时间*/
        m_lastReportFums = tNow;
        return true;
    }
    return false;
}





void CProcessStatic::Run()
{
    GetProcStatus();

    /*文件生成周期为15分钟*/
    if (NeedReportFums())
    {
        SendToFums();
    }
}




bool CProcessStatic::CheckProcExist(string& args)
{
    list<string>::iterator it;

    for (it = m_listProc.begin(); it != m_listProc.end(); it++)
    {
        if (args.find(*it) != string::npos)
        {
            return true;
        }
    }

    return false;
}





void CProcessStatic::GetProcStatus()
{
    long pid = 0;
    long rssMem = 0;
    long totalMem = 0;
    unsigned long i = 0;
    unsigned long num = 0;

    string pidArgs;
    string procState;

    list<string>::iterator it;
    CProcPidList procPids;
    CProcCpu tCpu;
    CProcMem tMem;

    procPids.GetProcPidList();
    num = procPids.GetProcNum();

    for (i = 0; i < num; i++)
    {
        CProcess ps;
        pid = (long)procPids.GetProcsPid(i);
        pidArgs = CHostStatus::GetProcArgs(pid);
        if (CheckProcExist(pidArgs))
        {
            ps.SetPid(pid);
            ps.SetCommand(pidArgs);

            procState = CHostStatus::GetProcState(pid);
            ps.SetState(procState);

            tCpu = CHostStatus::GetProcCpu(pid);
            tMem = CHostStatus::GetProcMem(pid);
            totalMem = CHostStatus::FetchMemorySize();

            ps.SetTime(tCpu.GetTotal());
            ps.AddCpuList(tCpu.GetPercent());
            ps.AddResList(tMem.GetRes() / 1024);
            ps.AddShrList(tMem.GetShare() / 1024);
            ps.AddVirtList(tMem.GetSize() / 1024);
            ps.AddSizeList(rssMem / 1024);
            ps.AddMemList((double)(rssMem / (totalMem * 1024)));
        }

        m_listprocess.push_back(ps);
    }

    return;
}



void CProcessStatic::CalcAvrg()
{
    
    list<CProcess>::iterator it;
    for (it = m_listprocess.begin(); it != m_listprocess.end(); it++)
    {
        it->CalcCpuAve();
        it->CalcMemAve();
        it->CalcResAve();
        it->CalcShrAve();
        it->CalcSizeAve();
        it->CalcVirtAve();
    }
}



void CProcessStatic::SendToFums()
{
}

















