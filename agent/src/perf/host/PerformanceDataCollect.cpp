/**********************************************************
 * File: PerformanceDataCollect.cpp
 * Function: 
 *********************************************************/
#include "PerformanceDataCollect.h"

#include <map>

#include "HostStatus.h"
#include "ReaderData.h"
#include "StringUtils.h"





int CPerformanceDataCollect::m_sSeq = 0;



int CPerformanceDataCollect::GetSeq()
{
    return m_sSeq++;
}




#if 0
#endif




CPerformanceDataCollect::CPerformanceDataCollect()
{
    m_lastReportFums.GetTimeNow();
}



CPerformanceDataCollect::~CPerformanceDataCollect()
{
}






void CPerformanceDataCollect::Run()
{
    list<string>::iterator itList;
    map<string, string>::iterator itMap;
    CReaderData rd;

    rd.GetApps();
    if (rd.CheckAppListEmpty())
    {
        return;
    }

    for (itList = rd.m_listApp.begin(); itList != rd.m_listApp.end(); itList++)
    {
        if (strcasecmp(itList->c_str(), "CSD") == 0)
        {
            rd.Read("python /opt/fonsview/NE/csd/bin/csd_sts.py");
        }
        else if (strcasecmp(itList->c_str(), "LRS") == 0)
        {
            rd.Read("/opt/fonsview/NE/lrs/bin/lrs_sts.sh");
        }
        else if (strcasecmp(itList->c_str(), "CSV") == 0)
        {
            rd.Read("/opt/fonsview/NE/csv/bin/csv_sts.sh");
        }
        else if (strcasecmp(itList->c_str(), "CSP") == 0)
        {
            rd.Read("/opt/fonsview/NE/csp/bin/csp_sts.sh");
        }
        else if (strcasecmp(itList->c_str(), "CSX") == 0)
        {
            rd.Read("python /opt/fonsview/NE/csx/bin/csx_sts.py");
        }
        else
        {
            continue;
        }


        string sequence = CString::ToString(CPerformanceDataCollect::GetSeq());
        string creatTime = CTime::GetCurTimeStr();
        string cpuRatioTemp = CString::ToString(CHostStatus::GetCpuUsage());
        string usedMemory = CString::ToString(CHostStatus::FetchMemoryUsed() * 1024); /*KB*/
        string memoryUsage = CString::ToString((long)(CHostStatus::GetMemUsage() * 100L));
        string usedSysDisk = CString::ToString(CHostStatus::FetchDiskUsedSize());
        int diskUsage = CHostStatus::GetDiskUsage();
        string diskUsageStr = CString::ToString(diskUsage);
        
        string content = "";
        string usedDataDisk = "0";
        string totalDataDisk = "0";
        string cacheIn = "0";
        string cacheOut = "0";
        string concurrencies = "0";
        string connections = "0";
        string DNSRequests = "0";
        string DNSResponse = "0";
        string HTTPRequests = "0";
        string HTTPRedirects = "0";

        itMap = rd.m_mapSts.find("usedDataDisk");
        if (itMap != rd.m_mapSts.end())
        {
            usedDataDisk = itMap->second;
        }

        itMap = rd.m_mapSts.find("totalDataDisk");
        if (itMap != rd.m_mapSts.end())
        {
            totalDataDisk = itMap->second;
        }

        itMap = rd.m_mapSts.find("cache_in");
        if (itMap != rd.m_mapSts.end())
        {
            cacheIn = itMap->second;
        }

        itMap = rd.m_mapSts.find("cache_out");
        if (itMap != rd.m_mapSts.end())
        {
            cacheOut = itMap->second;
        }

        itMap = rd.m_mapSts.find("curconn");
        if (itMap != rd.m_mapSts.end())
        {
            concurrencies = itMap->second;
        }

        itMap = rd.m_mapSts.find("averagereq");
        if (itMap != rd.m_mapSts.end())
        {
            connections = itMap->second;
        }

        itMap = rd.m_mapSts.find("DNSRequests");
        if (itMap != rd.m_mapSts.end())
        {
            DNSRequests = itMap->second;
        }

        itMap = rd.m_mapSts.find("DNSResponse");
        if (itMap != rd.m_mapSts.end())
        {
            DNSResponse = itMap->second;
        }

        itMap = rd.m_mapSts.find("httpRequests");
        if (itMap != rd.m_mapSts.end())
        {
            HTTPRequests = itMap->second;
        }

        itMap = rd.m_mapSts.find("httpRedirects");
        if (itMap != rd.m_mapSts.end())
        {
            HTTPRedirects = itMap->second;
        }

        content = sequence + "\t" + creatTime + "\t" + cpuRatioTemp + "\t" + usedMemory + "\t" + usedSysDisk + "\t"
                        + usedDataDisk + "\t" + totalDataDisk + "\t" + cacheIn + "\t" + cacheOut + "\t" + concurrencies
                        + "\t" + connections + "\t" + DNSRequests + "\t" + DNSResponse + "\t" + HTTPRequests + "\t"
                        + HTTPRedirects + "\t" + memoryUsage + "\t" + diskUsageStr + "\n";

        SendDeviceDiskAlarm(diskUsage, (*itList));
    }
}



void CPerformanceDataCollect::SendDeviceDiskAlarm(int diskUsage, string& ne)
{
    string firstPro = "over level1 threshold alarm";
    string secondPro = "over level2 threshold alarm";
    string firstSpe = "device_disk_usage_rate_above_threshole_level1";
    string secondSpe = "device_disk_usage_rate_above_threshole_level2";
}












