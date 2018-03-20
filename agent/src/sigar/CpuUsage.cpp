/**********************************************************
 * File: CpuUsage.cpp
 * Function: Sigar适配
 *********************************************************/
#include "CpuUsage.h"
#include "MacroDefine.h"
#include "TimeUtils.h"
#include "SigarAdapt.h"





#if 0
#endif






#if 0
#endif


CCpuPerc::CCpuPerc()
{
    m_nUser = 0;
    m_nSys = 0;
    m_nNice = 0;
    m_nIdle = 0;
    m_nWait = 0;
    m_nIrq = 0;
    m_nSoftIrq = 0;
    m_nStolen = 0;
    m_nTotal = 0;
    m_fCombined = 0;
}


CCpuPerc::~CCpuPerc()
{
}



CCpuPerc& CCpuPerc::operator=(CCpuPerc& cpuPerc)
{
    m_nUser = cpuPerc.m_nUser;
    m_nSys = cpuPerc.m_nSys;
    m_nNice = cpuPerc.m_nNice;
    m_nIdle = cpuPerc.m_nIdle;
    m_nWait = cpuPerc.m_nWait;
    m_nIrq = cpuPerc.m_nIrq;
    m_nSoftIrq = cpuPerc.m_nSoftIrq;
    m_nStolen = cpuPerc.m_nStolen;
    m_nTotal = cpuPerc.m_nTotal;
    m_fCombined = cpuPerc.m_fCombined;
    return *this;
}



#if 0
#endif



CCpuUsage::CCpuUsage()
{
    unsigned long num = 0;

    m_nCpuNum = 0;
    m_pCpuPercs = NULL;

    num = GetCpuPercNum();
    if (m_nCpuNum > 0)
    {
        m_pCpuPercs = new CCpuPerc[m_nCpuNum];
        if (m_pCpuPercs != NULL)
        {
            m_nCpuNum = num;
        }
    }
}



CCpuUsage::~CCpuUsage()
{
    if (m_pCpuPercs != NULL)
    {
        delete []m_pCpuPercs;
        m_pCpuPercs = NULL;
    }
    m_nCpuNum = 0;
}



CCpuPerc *CCpuUsage::GetCpuPerc(unsigned long index)
{
    if ((index > 0) && (index < m_nCpuNum) && (m_pCpuPercs != NULL))
    {
        return &m_pCpuPercs[index];
    }
    return NULL;
}


void CCpuUsage::SetCpuPerc(CCpuPerc& cpuPerc, unsigned long index)
{
    if ((index > 0) && (index < m_nCpuNum) && (m_pCpuPercs != NULL))
    {
        m_pCpuPercs[index] = cpuPerc;
    }
}



void CCpuUsage::SetCpuPerc(sigar_cpu_t& cpu, unsigned long index)
{
    if ((index > 0) && (index < m_nCpuNum) && (m_pCpuPercs != NULL))
    {
        m_pCpuPercs[index].SetUser(cpu.user);
        m_pCpuPercs[index].SetSys(cpu.sys);
        m_pCpuPercs[index].SetNice(cpu.nice);
        m_pCpuPercs[index].SetIdle(cpu.idle);
        m_pCpuPercs[index].SetWait(cpu.wait);
        m_pCpuPercs[index].SetIrq(cpu.irq);
        m_pCpuPercs[index].SetSoftIrq(cpu.soft_irq);
        m_pCpuPercs[index].SetStolen(cpu.stolen);
        m_pCpuPercs[index].SetTotal(cpu.total);
    }
}




unsigned long CCpuUsage::GetCpuPercNum()
{
    int ret = 0;
    sigar_cpu_info_list_t tCpu;
    
    if (SIGAR_OK != (ret = sigar_cpu_info_list_get(CSigar::GetSigar(), &tCpu)))
    {
        printf("sigar_cpu_info_list_get return = %d (%s).\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
        return 0;
    }

    sigar_cpu_info_list_destroy(CSigar::GetSigar(), &tCpu);
    return tCpu.number;
}



int CCpuUsage::GetCpuStat()
{
    int ret = 0;
    unsigned long i = 0;
    sigar_cpu_list_t tCpuList;

    if (m_pCpuPercs == NULL)
    {
        return -1;
    }

    if (SIGAR_OK != (ret = sigar_cpu_list_get(CSigar::GetSigar(), &tCpuList)))
    {
        printf("sigar_cpu_list_get return = %d (%s).\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
        return -1;
    }

    for (i = 0; i < tCpuList.number; i++)
    {
        SetCpuPerc(tCpuList.data[i], i);
    }
    
    sigar_cpu_list_destroy(CSigar::GetSigar(), &tCpuList);
    return 0;
}



int CCpuUsage::GetCpuUsage(CCpuPerc **pCpuPers, unsigned long *pOutCpuNum)
{
    int i = 0;
    int tCpuNum = 0;
    unsigned long long totalOld = 0;
    unsigned long long totalCur = 0;
    unsigned long long idleOld = 0;
    unsigned long long idleCur = 0;
    CCpuPerc *tCpuPerc = NULL;
    CCpuPerc *tOldCpuPerc = NULL;
    CCpuPerc *tCurCpuPerc = NULL;
    CCpuUsage tOldCpuUsage;
    CCpuUsage tCurCpuUsage;

    if (pCpuPers == NULL || pOutCpuNum == NULL)
    {
        return -1;
    }

    /*CPU需要获取2次，取其中差值*/
    tOldCpuUsage.GetCpuStat();
    CTime::msecSleep(1);
    tCurCpuUsage.GetCpuStat();

    tCpuNum = tOldCpuUsage.m_nCpuNum < tCurCpuUsage.m_nCpuNum ? tOldCpuUsage.m_nCpuNum : tCurCpuUsage.m_nCpuNum;
    *pCpuPers = new CCpuPerc[tCpuNum];
    if (*pCpuPers == NULL)
    {
        return -1;
    }
    *pOutCpuNum = tCpuNum;

    for (i = 0; i < tCpuNum; i++)
    {
        tCpuPerc = &(*pCpuPers)[i];
        tOldCpuPerc = tOldCpuUsage.GetCpuPerc(i);
        tCurCpuPerc = tCurCpuUsage.GetCpuPerc(i);
        
        idleOld = tOldCpuPerc->GetIdle();
        idleCur = tCurCpuPerc->GetIdle();
        
        totalOld = tOldCpuPerc->GetUser() + tOldCpuPerc->GetSys() + tOldCpuPerc->GetNice()
            + tOldCpuPerc->GetIdle() + tOldCpuPerc->GetWait() + tOldCpuPerc->GetIrq()
            + tOldCpuPerc->GetSoftIrq() + tOldCpuPerc->GetStolen();
        totalCur = tCurCpuPerc->GetUser() + tCurCpuPerc->GetSys() + tCurCpuPerc->GetNice()
            + tCurCpuPerc->GetIdle() + tCurCpuPerc->GetWait() + tCurCpuPerc->GetIrq()
            + tCurCpuPerc->GetSoftIrq() + tCurCpuPerc->GetStolen();
        
        if ((totalCur - totalOld) > 0)
        {
            tCurCpuPerc->SetCombined(double((totalCur - totalOld) + (idleCur - idleOld)) / double(totalCur - totalOld));
        }
        else
        {
            tCurCpuPerc->SetCombined(0.0);
        }

        *tCpuPerc = *tCurCpuPerc;
    }
    return 0;
}



string CCpuUsage::GetCpuUsageString()
{
    unsigned long i = 0;
    unsigned long tCpuNum = 0;
    char tStr[64] = {0};
    string usageStr("");
    CCpuPerc *tCpuPerc = NULL;

    if (CCpuUsage::GetCpuUsage(&tCpuPerc, &tCpuNum) != 0)
    {
        printf("GetCpuUsage error.");
        return "";
    }

    if (tCpuPerc == NULL)
    {
        return "";
    }

    if (tCpuNum <= 0)
    {
        delete []tCpuPerc;
        tCpuPerc = NULL;
        return "";
    }

    for (i = 0; i < tCpuNum; i++)
    {
        if (i < (tCpuNum - 1))
        {
            memset(tStr, 0, sizeof(tStr));
            sprintf(tStr, "%d,", (int)(tCpuPerc[i].GetCombined() * 100.0));
            usageStr.append(tStr);
        }
        else
        {
            memset(tStr, 0, sizeof(tStr));
            sprintf(tStr, "%d", (int)(tCpuPerc[i].GetCombined() * 100.0));
            usageStr.append(tStr);
        }
    }

    delete []tCpuPerc;
    tCpuPerc = NULL;
    tCpuNum = 0;
    return usageStr;
}



int CCpuUsage::GetCpuPercsUsage(int **pUsage, unsigned long *pOutLen)
{
    unsigned long i = 0;
    unsigned long tCpuNum = 0;
    CCpuPerc *tCpuPerc = NULL;

    if (pUsage == NULL || pOutLen == NULL)
    {
        return -1;
    }

    if (CCpuUsage::GetCpuUsage(&tCpuPerc, &tCpuNum) != 0)
    {
        printf("GetCpuUsage error.");
        return -1;
    }

    if (tCpuPerc == NULL)
    {
        return -1;
    }

    if (tCpuNum <= 0)
    {
        delete []tCpuPerc;
        tCpuPerc = NULL;
        return -1;
    }

    *pUsage = new int[tCpuNum];
    if (*pUsage == NULL)
    {
        delete [](tCpuPerc);
        tCpuPerc = NULL;
        return -1;
    }
    
    *pOutLen = tCpuNum;
    for (i = 0; i < tCpuNum; i++)
    {
        (*pUsage)[i] = (int)(tCpuPerc[i].GetCombined() * 100.0);
    }

    delete []tCpuPerc;
    tCpuPerc = NULL;
    tCpuNum = 0;
    return 0;
}




int CCpuUsage::GetCpuUsageTotal()
{
    int usage = 0;
    unsigned long i = 0;
    unsigned long tCpuNum = 0;
    double total = 0.0;
    CCpuPerc *tCpuPerc = NULL;

    if (CCpuUsage::GetCpuUsage(&tCpuPerc, &tCpuNum) != 0)
    {
        printf("GetCpuUsage error.");
        return 0;
    }

    if (tCpuPerc == NULL)
    {
        return 0;
    }

    if (tCpuNum <= 0)
    {
        delete []tCpuPerc;
        tCpuPerc = NULL;
        tCpuNum = 0;
        return 0;
    }

    for (i = 0; i < tCpuNum; i++)
    {
        total += tCpuPerc[i].GetCombined();
    }

    usage = (int)((total * 100.0) / tCpuNum);

    delete []tCpuPerc;
    tCpuPerc = NULL;
    tCpuNum = 0;
    return usage;
}



int CCpuUsage::GetCpuBaseInfo()
{
    int ret = 0;
    sigar_cpu_info_list_t tCpuInfo;
    
    if (SIGAR_OK != (ret = sigar_cpu_info_list_get(CSigar::GetSigar(), &tCpuInfo)))
    {
        sigar_cpu_info_list_destroy(CSigar::GetSigar(), &tCpuInfo);
        printf("sigar_cpu_info_list_get return = %d (%s).\n", ret, sigar_strerror(CSigar::GetSigar(), ret));
        return -1;
    }
    
    sigar_cpu_info_list_destroy(CSigar::GetSigar(), &tCpuInfo);
    return 0;
}






