/**********************************************************
 * File: PerformanceDataCollect.cpp
 * Function: 
 *********************************************************/
#include "PerformanceDataCollect.h"

#include <map>

#include "HostStatus.h"
#include "ReaderData.h"
#include "StringUtils.h"

#include "AmqpReceiveBuilder.h"
#include "AmqpMessageReceiveProcessor.h"
#include "AmqpMessageSendProcessor.h"
#include "ProtoBufPacker.h"

using namespace com::fiberhome::fums::proto;





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
    AppPerfData data;

    rd.GetApps();
    if (rd.CheckAppListEmpty())
    {
        return;
    }

    for (itList = rd.m_listApp.begin(); itList != rd.m_listApp.end(); itList++)
    {
        SingleAppPerfData *singleData = data.add_perfdata();

        if (strcasecmp(itList->c_str(), "CSD") == 0)
        {
            rd.Read("python /opt/fonsview/NE/csd/bin/csd_sts.py");
            singleData->set_apptype(SingleAppPerfData::CSD);
        }
        else if (strcasecmp(itList->c_str(), "LRS") == 0)
        {
            rd.Read("/opt/fonsview/NE/lrs/bin/lrs_sts.sh");
            singleData->set_apptype(SingleAppPerfData::LRS);
        }
        else if (strcasecmp(itList->c_str(), "CSV") == 0)
        {
            rd.Read("/opt/fonsview/NE/csv/bin/csv_sts.sh");
            singleData->set_apptype(SingleAppPerfData::CSV);
        }
        else if (strcasecmp(itList->c_str(), "CSP") == 0)
        {
            rd.Read("/opt/fonsview/NE/csp/bin/csp_sts.sh");
            singleData->set_apptype(SingleAppPerfData::CSP);
        }
        else if (strcasecmp(itList->c_str(), "CSX") == 0)
        {
            rd.Read("python /opt/fonsview/NE/csx/bin/csx_sts.py");
            singleData->set_apptype(SingleAppPerfData::CSX);
        }
        else
        {
            continue;
        }


        int sequence = CPerformanceDataCollect::GetSeq();
        string strSequence = CString::ToString(sequence);
        string createTime = CTime::GetCurTimeStr();
        double cpuRatioTemp = CHostStatus::GetCpuUsage();
        string strCpuRatioTemp = CString::ToString(cpuRatioTemp);
        double usedMemory = CHostStatus::FetchMemoryUsed() * 1024;
        string strUsedMemory = CString::ToString(usedMemory); /*KB*/
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

        singleData->set_sequence(sequence);
        singleData->set_createtime(createTime);
        singleData->set_cpuratio(cpuRatioTemp);
        singleData->set_usedmemory(usedMemory);

        itMap = rd.m_mapSts.find("usedDataDisk");
        if (itMap != rd.m_mapSts.end())
        {
            usedDataDisk = itMap->second;
            singleData->set_useddatadisk(CString::StrTod(usedDataDisk));
        }

        itMap = rd.m_mapSts.find("totalDataDisk");
        if (itMap != rd.m_mapSts.end())
        {
            totalDataDisk = itMap->second;
            singleData->set_totaldatadisk(CString::StrTod(totalDataDisk));
        }

        itMap = rd.m_mapSts.find("cache_in");
        if (itMap != rd.m_mapSts.end())
        {
            cacheIn = itMap->second;
            singleData->set_cachein(CString::StrTod(cacheIn));
        }

        itMap = rd.m_mapSts.find("cache_out");
        if (itMap != rd.m_mapSts.end())
        {
            cacheOut = itMap->second;
            singleData->set_cacheout(CString::StrTod(cacheOut));
        }

        itMap = rd.m_mapSts.find("curconn");
        if (itMap != rd.m_mapSts.end())
        {
            concurrencies = itMap->second;
            singleData->set_curconn(CString::StrTod(concurrencies));
        }

        itMap = rd.m_mapSts.find("averagereq");
        if (itMap != rd.m_mapSts.end())
        {
            connections = itMap->second;
            singleData->set_averagereq(CString::StrTod(connections));
        }

        itMap = rd.m_mapSts.find("DNSRequests");
        if (itMap != rd.m_mapSts.end())
        {
            DNSRequests = itMap->second;
            singleData->set_dnsrequests(CString::StrTod(DNSRequests));
        }

        itMap = rd.m_mapSts.find("DNSResponse");
        if (itMap != rd.m_mapSts.end())
        {
            DNSResponse = itMap->second;
            singleData->set_dnsresponse(CString::StrTod(DNSResponse));
        }

        itMap = rd.m_mapSts.find("httpRequests");
        if (itMap != rd.m_mapSts.end())
        {
            HTTPRequests = itMap->second;
            singleData->set_httprequests(CString::StrTod(HTTPRequests));
        }

        itMap = rd.m_mapSts.find("httpRedirects");
        if (itMap != rd.m_mapSts.end())
        {
            HTTPRedirects = itMap->second;
            singleData->set_httpredirects(CString::StrTod(HTTPRedirects));
        }

        content = strSequence + "\t" + createTime + "\t" + strCpuRatioTemp + "\t" + strUsedMemory + "\t" + usedSysDisk + "\t"
                        + usedDataDisk + "\t" + totalDataDisk + "\t" + cacheIn + "\t" + cacheOut + "\t" + concurrencies
                        + "\t" + connections + "\t" + DNSRequests + "\t" + DNSResponse + "\t" + HTTPRequests + "\t"
                        + HTTPRedirects + "\t" + memoryUsage + "\t" + diskUsageStr + "\n";

        SendDeviceDiskAlarm(diskUsage, (*itList));
    }

    Major major = ProtoBufPacker::PackPerfEntity(ProtoBufPacker::SerializeToArray<AppPerfData>(data), PerfData::APP_PERF);
    AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
}



void CPerformanceDataCollect::SendDeviceDiskAlarm(int diskUsage, string& ne)
{
    string firstPro = "over level1 threshold alarm";
    string secondPro = "over level2 threshold alarm";
    string firstSpe = "device_disk_usage_rate_above_threshole_level1";
    string secondSpe = "device_disk_usage_rate_above_threshole_level2";
}












