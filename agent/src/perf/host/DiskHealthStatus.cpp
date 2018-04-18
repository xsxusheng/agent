/**********************************************************
 * File: DiskHealthStatus.cpp
 * Function: 
 *********************************************************/
#include "DiskHealthStatus.h"

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






CDiskHealthStatus::CDiskHealthStatus()
{
    m_lastReportFums.GetTimeNow();
}



CDiskHealthStatus::~CDiskHealthStatus()
{
}



bool CDiskHealthStatus::NeedReportFums()
{
    CTime tNow;

    if (tNow.DiffSec(m_lastReportFums) >= DEF_DISK_HEALTH_REPORT)
    {
        /*重置上次上报时间*/
        m_lastReportFums = tNow;
        return true;
    }
    return false;
}





void CDiskHealthStatus::Run()
{
    if (NeedReportFums())
    {
        SendToFums();
    }
}



void CDiskHealthStatus::SendToFums()
{
    unsigned int i = 0;
    bool badFlag = false;
    
    string::size_type pos = 0;
    string::size_type ok = 0;
    string::size_type passed = 0;
    string::size_type notSupport = 0;
    
    string result;
    string scPath = DISK_HEALTH_SCRIPT1;
    string diskName;
    string badDiskName;

    vector<string> vDiskName;
    vector<string> vDiskNames;

    result.erase();
    if (CScriptAction::ExecuteScript(scPath, result) < 0)
    {
        SV_ERROR("ExecuteScript %s error.", scPath.c_str());
        return;
    }

    CString::Split(result, vDiskName, ";");
    diskName = vDiskName[0];

    pos = diskName.find("=");
    if (pos != string::npos)
    {
        diskName = diskName.substr(pos + 1);
    }

    CString::Split(diskName, vDiskNames, "]");
    for (i = 0; i < vDiskNames.size(); i++)
    {
        diskName = vDiskNames[i];

        result.erase();

        string script(scPath + " " + diskName);
        if (CScriptAction::ExecuteScript(script, result) < 0)
        {
            continue;
        }

        ok = result.find("OK");
        passed = result.find("PASSED");
        notSupport = result.find("not supported");
        if ((ok == string::npos) && (passed == string::npos) && (notSupport == string::npos))
        {
            if (badFlag)
            {
                badDiskName.append(",");
            }
            
            badDiskName.append(diskName);
            badFlag = true;
        }
    }

    if (badFlag)
    {
        SV_INFO("DISK_HEALTH_STATUS: FAILED, DISK_NAME=%s.", badDiskName.c_str());
    }
    else
    {
        SV_INFO("DISK_HEALTH_STATUS: PASSED.");
    }
}















