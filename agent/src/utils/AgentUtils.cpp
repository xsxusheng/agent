/*************************************************************************
	> File Name: AgentUtils.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月13日 星期二 17时03分41秒
 ************************************************************************/

#include <iostream>
#include "sv_log.h"
#include "AgentUtils.h"
using namespace std;


#ifdef _WIN32  
    #include <winsock2.h>  
    #include <time.h>  
#else  
    #include <sys/time.h>  
    #include <stddef.h>
#endif  
  
string AgentUtils::sm_etcPath("/opt/fonsview/NE/agent/etc/");
string AgentUtils::sm_rabbitmqConfFile("rabbitmq.properties");
string AgentUtils::sm_systemConfigFile("SystemConfig.properties");
string AgentUtils::sm_agentVersionFile("version.properties");
string AgentUtils::sm_agentIP("127.0.0.1");
string AgentUtils::sm_appMsgPort("5672");


string AgentUtils::GetRabbitmqConfFile()
{
    return sm_rabbitmqConfFile;
}


int AgentUtils::Init()
{
    string systemConfigPath = sm_etcPath + sm_systemConfigFile;
    if(__LoadSystemConfig(systemConfigPath) < 0)
    {
        SV_ERROR("Load Agent System Config Error");
        return -1;
    }

    string versionFilePath = sm_etcPath + sm_agentVersionFile;
    if(__LoadAgentVersion(versionFilePath) < 0)
    {
        SV_ERROR("Load Agent System Version Error");
    }

    return 0;
}

string AgentUtils::GetLocalIP()
{
	return sm_agentIP;
}


int AgentUtils::__LoadSystemConfig(string &fileName)
{

    return 0;
}

int AgentUtils::__LoadAgentVersion(string &fileName)
{
    return 0;
}

unsigned long long AgentUtils::GetCurrentTimeMsec()  
{  
#ifdef _WIN32  
        struct timeval tv;  
        time_t clock;  
        struct tm tm;  
        SYSTEMTIME wtm;  
  
        GetLocalTime(&wtm);  
        tm.tm_year = wtm.wYear - 1900;  
        tm.tm_mon = wtm.wMonth - 1;  
        tm.tm_mday = wtm.wDay;  
        tm.tm_hour = wtm.wHour;  
        tm.tm_min = wtm.wMinute;  
        tm.tm_sec = wtm.wSecond;  
        tm.tm_isdst = -1;  
        clock = mktime(&tm);  
        tv.tv_sec = clock;  
        tv.tv_usec = wtm.wMilliseconds * 1000;  
        return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);  
#else  
        struct timeval tv;  
        gettimeofday(&tv, NULL);
        return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);  
#endif  
}
