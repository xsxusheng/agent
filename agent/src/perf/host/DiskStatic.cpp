/**********************************************************
 * File: DiskStatic.cpp
 * Function: 
 *********************************************************/
#include "DiskStatic.h"

#include <cstdlib>
#include <vector>

#include "HostStatus.h"
#include "ScriptAction.h"
#include "StringUtils.h"

#include "AmqpReceiveBuilder.h"
#include "AmqpMessageReceiveProcessor.h"
#include "AmqpMessageSendProcessor.h"
#include "ProtoBufPacker.h"

using namespace com::fiberhome::fums::proto;





CDisk::CDisk()
{
    m_strDev.clear();
    m_fTps = 0.0;
    m_fRdSec = 0.0;
    m_fWrSec = 0.0;
    m_fAvgrq = 0.0;
    m_fAvgqu = 0.0;
    m_fAwait = 0.0;
    m_fSvctm = 0.0;
    m_fUtil = 0.0;
}



CDisk::~CDisk()
{
    m_strDev.clear();
    m_fTps = 0.0;
    m_fRdSec = 0.0;
    m_fWrSec = 0.0;
    m_fAvgrq = 0.0;
    m_fAvgqu = 0.0;
    m_fAwait = 0.0;
    m_fSvctm = 0.0;
    m_fUtil = 0.0;
}



#if 0
#endif



CDiskStatic::CDiskStatic()
{
    m_listDisk.clear();
}



CDiskStatic::~CDiskStatic()
{
    m_listDisk.clear();
}



bool CDiskStatic::NeedReportFums()
{
    CTime tNow;

    if (tNow.DiffSec(m_lastReportFums) >= DEF_DISK_STATIC_REPORT)
    {
        /*重置上次上报时间*/
        m_lastReportFums = tNow;
        return true;
    }
    return false;
}



void CDiskStatic::Run()
{
    Sample();

    /*文件生成周期为15分钟*/
    if (NeedReportFums())
    {
        SendToFums();
        m_listDisk.clear();
    }
}



void CDiskStatic::Sample()
{
    unsigned int i = 0;
    string strDisk;
    string script(DISK_STAT_SCRIPT);
    vector<string> split;
    vector<string> diskSplit;

    if (CScriptAction::ExecuteScript(script, strDisk) < 0)
    {
        SV_ERROR("ExecuteScript %s failed.", script.c_str());
        return;
    }

    /*第一行数据为标题，需跳过*/
    CString::Split2(strDisk, split, "\n");
    for (i = 1; i < split.size(); i++)
    {
        CDisk disk;

        CString::Split2(split[i], diskSplit, " ");
        //SV_LOG("DISK_STAT: size=%d, [[%s]]", diskSplit.size(), split[i].c_str());
        if (diskSplit.size() < MAX_DISK_SPLIT_NUM)
        {
            continue;
        }
        
        disk.SetDev(diskSplit[1]);
        disk.SetTps(CString::StrTof(diskSplit[2]));
        disk.SetRdSec(CString::StrTof(diskSplit[3]));
        disk.SetWrSec(CString::StrTof(diskSplit[4]));
        disk.SetAvgrq(CString::StrTof(diskSplit[5]));
        disk.SetAvgqu(CString::StrTof(diskSplit[6]));
        disk.SetAwait(CString::StrTof(diskSplit[7]));
        disk.SetSvctm(CString::StrTof(diskSplit[8]));
        disk.SetUtil(CString::StrTof(diskSplit[9]));

        m_listDisk.push_back(disk);
        diskSplit.clear();
    }

    split.clear();
}




void CDiskStatic::SendToFums()
{
    list<CDisk>::iterator it;
    DiskData data;

    for (it = m_listDisk.begin(); it != m_listDisk.end(); it++)
    {
        SingleDiskPerfData *singleData = data.add_perfdata();

        singleData->set_dev(it->GetDev());
        singleData->set_tps(it->GetTps());
        singleData->set_rd_sec(it->GetRdSec());
        singleData->set_wr_sec(it->GetWrSec());
        singleData->set_avgqu_sz(it->GetAvgqu());
        singleData->set_avgrq_sz(it->GetAvgrq());
        singleData->set_await(it->GetAwait());
        singleData->set_svctm(it->GetSvctm());
        singleData->set_util(it->GetUtil());

        SV_LOG("DEV=%s, TPS=%f, RDSEC=%f, WRSEC=%f, AVGQU=%f, AVGRQ=%f, AWAIT=%f, SVCTM=%f, UTIL=%f.",
            it->GetDev().c_str(), it->GetTps(), it->GetRdSec(), it->GetWrSec(), it->GetAvgqu(), it->GetAvgrq(),
            it->GetAwait(), it->GetSvctm(), it->GetUtil());
    }

    Major major = ProtoBufPacker::PackPerfEntity(ProtoBufPacker::SerializeToArray<DiskData>(data), PerfData::DISK_TYPE);
    AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
}















