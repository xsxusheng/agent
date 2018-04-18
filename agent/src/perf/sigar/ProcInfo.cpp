/**********************************************************
 * File: ProcInfo.cpp
 * Function: 
 *********************************************************/
#include "ProcInfo.h"

#include <cstring>

#include "sv_log.h"
#include "SigarAdapt.h"



CProcState::CProcState()
{
    memset(m_cName, 0, sizeof(m_cName));
}


CProcState::~CProcState()
{
}



void CProcState::SetName(char *name)
{
    if(name != NULL)
    {
        strncpy(m_cName, name, (MAX_PROC_NAME_LEN-1));
    }
}



void CProcState::SetState(char state)
{
    if ((state == PROC_STATE_SLEEP)
        || (state == PROC_STATE_RUN)
        || (state == PROC_STATE_STOP)
        || (state == PROC_STATE_ZOMBIE)
        || (state == PROC_STATE_IDLE))
    {
        m_cState = state;
    }
}



int CProcState::GetProcState(long pid)
{
    sigar_proc_state_t proc_state;

    if (SIGAR_OK != sigar_proc_state_get(CSigar::GetSigar(), pid, &proc_state))
    {
        return -1;
    }

    SetName(proc_state.name);
    SetState(proc_state.state);
    SetPpid((long)proc_state.ppid);
    SetTty(proc_state.tty);
    SetPri(proc_state.priority);
    SetNice(proc_state.nice);
    SetProcessor(proc_state.processor);
    SetThread((unsigned long)proc_state.threads);
    return 0;
}





#if 0
#endif



CProcArgs::CProcArgs()
{
    m_nArgsNum = 0;
    m_cArgs = NULL;
}



CProcArgs::~CProcArgs()
{
    FreeArgs();
}



int CProcArgs::AllocArgs(unsigned long size)
{
    if (size <= 0)
    {
        return -1;
    }
    
    if (m_cArgs != NULL)
    {
        FreeArgs();
    }

    m_cArgs = new char* [size];
    if (m_cArgs != NULL)
    {
        memset(m_cArgs, 0, size);
        m_nArgsNum = size;
        return 0;
    }

    return -1;
}


void CProcArgs::FreeArgs()
{
    unsigned long i = 0;

    if (m_cArgs != NULL)
    {
        for (i = 0; i < m_nArgsNum; i++)
        {
            if (m_cArgs[i] != NULL)
            {
                delete []m_cArgs[i];
                m_cArgs[i] = NULL;
            }
        }
        delete []m_cArgs;
    }
    m_nArgsNum = 0;
}



char* CProcArgs::GetArgs(unsigned long index)
{
    if (index >= GetArgsNum())
    {
        return NULL;
    }

    if (m_cArgs != NULL)
    {
        return m_cArgs[index];
    }

    return NULL;
}



int CProcArgs::SetArgs(unsigned long index, char *pArgs)
{
    int len = 0;

    if ((index >= GetArgsNum()) || (pArgs == NULL) || (m_cArgs == NULL))
    {
        return -1;
    }

    len = strlen(pArgs) + 1;
    m_cArgs[index] = new char[len];
    if (m_cArgs[index] != NULL)
    {
        memset(m_cArgs[index], 0, len);
        strncpy(m_cArgs[index], pArgs, (len - 1));
        return 0;
    }

    return -1;
}





int CProcArgs::GetProcArgs(long pid)
{
    unsigned long i = 0;
    unsigned long num = 0;
    sigar_proc_args_t args;

    if (SIGAR_OK != sigar_proc_args_get(CSigar::GetSigar(), (sigar_pid_t)pid, &args))
    {
        return -1;
    }

    if ((args.number <= 0) || (args.data == NULL))
    {
        sigar_proc_args_destroy(CSigar::GetSigar(), &args);
        return -1;
    }

    num = args.number;
    if (AllocArgs(num) < 0)
    {
        sigar_proc_args_destroy(CSigar::GetSigar(), &args);
        return -1;
    }
    
    for (i = 0; i < num; i++)
    {
        if (args.data[i] != NULL)
        {
            SetArgs(i,  args.data[i]);
        }
    }
    
    sigar_proc_args_destroy(CSigar::GetSigar(), &args);
    return num;
}




#if 0
#endif




CProcMem::CProcMem()
{
    m_nSize = 0;
    m_nRes = 0;
    m_nShare = 0;
}



CProcMem::~CProcMem()
{
    m_nSize = 0;
    m_nRes = 0;
    m_nShare = 0;
}





int CProcCpu::GetProcCpu(long pid)
{
    sigar_proc_cpu_t proc_cpu;

    if (SIGAR_OK != sigar_proc_cpu_get(CSigar::GetSigar(), (sigar_pid_t)pid, &proc_cpu))
    {
        SV_ERROR("sigar_proc_cpu_get failed...");
        return -1;
    }

    SetStartTime(proc_cpu.start_time);
    SetUser(proc_cpu.user);
    SetSys(proc_cpu.sys);
    SetTotal(proc_cpu.total);
    SetLastTime(proc_cpu.last_time);
    SetPercent(proc_cpu.percent);
    /*SV_LOG("GetProcCpu: START_TIME=%llu, END_TIME=%llu, USER=%llu, SYS=%llu, TOTAL=%llu, PERCENT=%f.",
        proc_cpu.start_time, proc_cpu.last_time, proc_cpu.user, proc_cpu.sys, proc_cpu.total, proc_cpu.percent);*/
    return 0;
}




int CProcMem::GetProcMem(long pid)
{
    sigar_proc_mem_t proc_mem;

    if (SIGAR_OK != sigar_proc_mem_get(CSigar::GetSigar(), (sigar_pid_t)pid, &proc_mem))
    {
        SV_ERROR("sigar_proc_mem_get failed...");
        return -1;
    }

    SetSize(proc_mem.size);
    SetRes(proc_mem.resident);
    SetShare(proc_mem.share);
    //SV_LOG("GetProcMem: SIZE=%llu, RES=%llu, SHR=%llu.", proc_mem.size, proc_mem.resident, proc_mem.share);
    return 0;
}




#if 0
#endif



CProcPidList::CProcPidList()
{
    m_pPid = NULL;
    m_nProcNum = 0;
}



CProcPidList::~CProcPidList()
{
    FreeProcPid();
}



int CProcPidList::AllocProcPid(unsigned long size)
{
    if ((size <= 0) || (size > MAX_PROC_LIST_NUM))
    {
        SV_ERROR("Input para size %lu error.", size);
        return -1;
    }
    
    if (m_pPid != NULL)
    {
        FreeProcPid();
    }

    m_pPid = new long[size];
    if (m_pPid != NULL)
    {
        SetProcNum(size);
        return 0;
    }

    return -1;
}



void CProcPidList::FreeProcPid()
{
    if (m_pPid != NULL)
    {
        delete []m_pPid;
        m_pPid = NULL;
        m_nProcNum = 0;
    }
}



long CProcPidList::GetProcsPid(unsigned long index)
{
    if (index >= GetProcNum() || m_pPid == NULL)
    {
        return 0;
    }
    return m_pPid[index];
}



int CProcPidList::SetProcPid(unsigned long index, long pid)
{
    if (index >= GetProcNum() || m_pPid == NULL)
    {
        return -1;
    }

    m_pPid[index] = pid;
    return 0;
}



int CProcPidList::GetProcPidList()
{
    unsigned long i = 0;
    sigar_proc_list_t proclist;

    if (SIGAR_OK != sigar_proc_list_get(CSigar::GetSigar(), &proclist))
    {
        SV_ERROR("sigar_proc_list_get failed ...");
        return -1;
    }

    if (proclist.number <= 0)
    {
        SV_ERROR("sigar_proc_list_get number %lu ...", proclist.number);
        sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
        return -1;
    }

    if (AllocProcPid(proclist.number) < 0)
    {
        sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
        return -1;
    }
    
    for (i = 0; i < proclist.number; i++)
    {
        SetProcPid(i, proclist.data[i]);
    }

    sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
    return 0;
}







#if 0





CProcessInfo::CProcessInfo()
{
    unsigned long num = 0;

    m_nProcNum = 0;
    num = GetProcListNum();
    if (num > 0)
    {
        m_pProcs = new CProcess[num];
        if (m_pProcs == NULL)
        {
            return;
        }
        m_nProcNum = num;
    }
}



CProcessInfo::~CProcessInfo()
{
    if (m_pProcs != NULL)
    {
        delete []m_pProcs;
        m_pProcs = NULL;
        m_nProcNum = 0;
    }
}



unsigned long CProcessInfo::GetProcListNum()
{
    unsigned long num = 0;
    sigar_proc_list_t proclist;

    if (SIGAR_OK != sigar_proc_list_get(CSigar::GetSigar(), &proclist))
    {
        return 0;
    }

    if (proclist.number > 0)
    {
        num = proclist.number;
    }
    sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
    return num;
}




CProcess* CProcessInfo::GetProcess(unsigned long index)
{
    if (index >= m_nProcNum)
    {
        return NULL;
    }
    
    if (m_pProcs != NULL)
    {
        return m_pProcs[index];
    }

    return NULL;
}



int CProcessInfo::GetProcList()
{
    int ret = 0;
    unsigned long i = 0;
    unsigned long num = 0;
    CProcess* pProc = NULL;
    sigar_proc_list_t proclist;
    sigar_proc_mem_t proc_mem;
    sigar_proc_cpu_t proc_cpu;
    sigar_proc_state_t proc_state;

    if (GetProcess() == NULL)
    {
        return -1;
    }

    if (SIGAR_OK != sigar_proc_list_get(CSigar::GetSigar(), &proclist))
    {
        return -1;
    }

    num = GetProcNum();
    if (proclist.number != num)
    {
        sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
        return -1;
    }


    for (i = 0; i < num; i++)
    {
        pProc = GetProcess(i);
        if (pProc == NULL)
        {
            sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
            return -1;
        }
        
        pProc->SetPid((long)proclist.data[i]);
        if (SIGAR_OK != (ret = sigar_proc_mem_get(CSigar::GetSigar(), proclist.data[i], &proc_mem)))
        {
            printf("sigar_proc_mem_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
            sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
            return -1;
        }

        pProc->SetSize((long)proc_mem.size);
        pProc->SetRes((long)proc_mem.resident);
        pProc->SetShr((long)proc_mem.share);


        if (SIGAR_OK != (ret = sigar_proc_cpu_get(CSigar::GetSigar(), proclist.data[i], &proc_cpu)))
        {
            printf("sigar_proc_time_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
            sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
            return -1;
        }

        pProc->SetCpu(proc_cpu.percent);


        if (SIGAR_OK != (ret = sigar_proc_state_get(CSigar::GetSigar(), proclist.data[i], &proc_state)))
        {
            printf("sigar_proc_state_get ret = %d (%s)\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
            sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
            return -1;
        }
    }
    
    sigar_proc_list_destroy(CSigar::GetSigar(), &proclist);
    return num;
}


#endif










