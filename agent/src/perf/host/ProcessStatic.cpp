/**********************************************************
 * File: ProcessStatic.cpp
 * Function: 
 *********************************************************/
#include "ProcessStatic.h"

#include "ProcInfo.h"
#include "HostStatus.h"
#include "Perf.pb.h"

#include "AmqpReceiveBuilder.h"
#include "AmqpMessageReceiveProcessor.h"
#include "AmqpMessageSendProcessor.h"
#include "ProtoBufPacker.h"

using namespace com::fiberhome::fums::proto;







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
    m_listProc.push_back("/opt/fonsview/NE/drs/bin/drs");

    m_lastReportFums.GetTimeNow();
}



CProcessStatic::~CProcessStatic()
{
    m_listProc.clear();
}





bool CProcessStatic::NeedReportFums()
{
    CTime tNow;

    if (tNow.DiffSec(m_lastReportFums) >= DEF_PROCESS_REPORT)
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
        CalcAvrg();
        SendToFums();
        ClearAvrg();
    }
}




bool CProcessStatic::CheckProcExist(string& args)
{
    list<string>::iterator it;

    for (it = m_listProc.begin(); it != m_listProc.end(); it++)
    {
        if ((args.find(*it) != string::npos)
            && (it->length() == args.length()))
        {
            return true;
        }
    }

    return false;
}




bool CProcessStatic::FindProc(string& findProc, string& args)
{
    list<string>::iterator it;

    for (it = m_listProc.begin(); it != m_listProc.end(); it++)
    {
        if ((args.find(*it) != string::npos)
            && (it->length() == args.length()))
        {
            findProc = (*it);
            return true;
        }
    }

    return false;
}





void CProcessStatic::GetProcStatus()
{
    long pid = 0;
    long totalMem = 0;
    unsigned long i = 0;
    unsigned long num = 0;

    string pidArgs;
    string procArgs;
    string procState;

    map<string, list<CProcess> >::iterator it;
    CProcPidList procPids;
    CProcCpu tCpu;
    CProcMem tMem;

    if (procPids.GetProcPidList() < 0)
    {
        SV_ERROR("Get Process pid list failed ...");
        return;
    }

    num = procPids.GetProcNum();
    for (i = 0; i < num; i++)
    {
        CProcess ps;
        pid = (long)procPids.GetProcsPid(i);
        pidArgs = CHostStatus::GetProcArgs(pid);
        if (FindProc(procArgs, pidArgs))
        {
            ps.SetPid(pid);
            ps.SetCommand(pidArgs);

            procState = CHostStatus::GetProcState(pid);
            ps.SetState(procState);

            tCpu = CHostStatus::GetProcCpu(pid);
            tMem = CHostStatus::GetProcMem(pid);
            totalMem = CHostStatus::FetchMemorySize(); /*MB*/

            ps.SetTime(tCpu.GetTotal());
            ps.SetCpu(tCpu.GetPercent());
            ps.SetRes(tMem.GetRes() / 1024);
            ps.SetShr(tMem.GetShare() / 1024);
            ps.SetVirt(tMem.GetSize() / 1024);
            ps.SetSize(tMem.GetRes() / 1024);
            ps.SetMem((double)(tMem.GetRes()) / (totalMem * 1024.0 * 1024.0));

            /*SV_LOG("PID=%ld, ARGS=[%s], STAT=%s, CPU=%f, CPUTOTAL=%llu, MEM=%f, MEMTOTAL=%ld, RES=%llu, SHR=%llu, SIZE=%llu, VIRT=%llu.",
                pid, pidArgs.c_str(), procState.c_str(), tCpu.GetPercent(), tCpu.GetTotal(), ps.GetMem(),
                totalMem, tMem.GetRes(), tMem.GetShare(), tMem.GetRes(), tMem.GetSize());*/


            /*如果没有，则新建一个；如果找到，则在原有上插入*/
            it = m_mapProcess.find(procArgs);
            if (it == m_mapProcess.end())
            {
                list<CProcess> listProcess;
                listProcess.push_back(ps);
                m_mapProcess.insert(pair<string, list<CProcess> >(procArgs, listProcess));
            }
            else
            {
                it->second.push_back(ps);
            }
        }
    }

    return;
}



void CProcessStatic::CalcAvrg()
{
    list<CProcess>::iterator itList;
    list<CProcess>::reverse_iterator ritList;
    map<string, list<CProcess> >::iterator itMap;

    for (itMap = m_mapProcess.begin(); itMap != m_mapProcess.end(); itMap++)
    {
        double cpuSum = 0.0;
        double memSum = 0.0;
        double sizeSum = 0.0;
        double virtSum = 0.0;
        double resSum = 0.0;
        double shrSum = 0.0;
        double cpuMax = 0.0;
        double memMax = 0.0;

        size_t size = 0;
        string tStr;
        CProcess ps;

        /*匹配最后一个*/
        ritList = itMap->second.rbegin();
        size = itMap->second.size();

        tStr = ritList->GetCommand();
        ps.SetCommand(tStr);

        tStr = ritList->GetState();
        ps.SetState(tStr);

        tStr = ritList->GetTime();
        ps.SetTime(tStr);
        ps.SetPid(ritList->GetPid());

        for (itList = itMap->second.begin(); itList != itMap->second.end(); itList++)
        {
            cpuSum += itList->GetCpu();
            memSum += itList->GetMem();
            sizeSum += itList->GetSize();
            virtSum += itList->GetVirt();
            resSum += itList->GetRes();
            shrSum += itList->GetShr();

            if (cpuMax < itList->GetCpu())
            {
                cpuMax = itList->GetCpu();
            }

            if (memMax < itList->GetMem())
            {
                memMax = itList->GetMem();
            }
        }

        ps.SetCpu(cpuSum / size);
        ps.SetMem(memSum / size);
        ps.SetSize(sizeSum / size);
        ps.SetVirt(virtSum / size);
        ps.SetRes(resSum / size);
        ps.SetShr(shrSum / size);
        ps.SetCpuMax(cpuMax);
        ps.SetMemMax(memMax);

        m_listProcess.push_back(ps);
    }
}



void CProcessStatic::ClearAvrg()
{
    m_listProcess.clear();
    m_mapProcess.clear();
}



void CProcessStatic::SendToFums()
{
    list<CProcess>::iterator it;
    ProcessData data;

    for (it = m_listProcess.begin(); it != m_listProcess.end(); it++)
    {
        SingleProcessPerfData *singleData = data.add_perfdata();
        singleData->set_pid(it->GetPid());
        singleData->set_command(it->GetCommand());
        singleData->set_cpu((float)it->GetCpu());
        singleData->set_mem((float)it->GetMem());
        singleData->set_size(it->GetSize());
        singleData->set_virt(it->GetVirt());
        singleData->set_res(it->GetRes());
        singleData->set_shr(it->GetShr());
        singleData->set_time(it->GetTime());
        singleData->set_state(it->GetState());
        singleData->set_cpumax((float)it->GetCpuMax());
        singleData->set_memmax((float)it->GetMemMax());

        SV_INFO("PROCESS_STATIC: PID=%ld, Cmd=%s, CPU=%f, CPUMAX=%f, MEM=%f, MEMMAX=%f, Size=%ld, Virt=%ld, Res=%ld, Shr=%ld, Time=%s, State=%s.",
            it->GetPid(), it->GetCommand().c_str(), it->GetCpu(), it->GetCpuMax(), it->GetMem(), it->GetMemMax(),
            it->GetSize(), it->GetVirt(), it->GetRes(), it->GetShr(), it->GetTime().c_str(), it->GetState().c_str());
    }

    Major major = ProtoBufPacker::PackPerfEntity(ProtoBufPacker::SerializeToArray<ProcessData>(data), PerfData::PROCESS_TYPE);
    AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
}

















