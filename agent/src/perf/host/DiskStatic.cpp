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

//using namespace com::fiberhome::fums::proto;




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



void CDiskStatic::Run()
{
    Sample();
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
        return;
    }

    CString::Split(strDisk, split, "\n");
    for (i = 0; i < split.size(); i++)
    {
        CDisk disk;
        CString::Split(split[i], diskSplit, " ");
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




void SendToFums()
{
}















