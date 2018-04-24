/*************************************************************************
	> File Name: AgentConfig.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月13日 星期二 16时45分49秒
 ************************************************************************/

#ifndef _AGENTUTILS_H_
#define _AGENTUTILS_H_
#include <string>
#include "Lock.h"
using namespace std;

class AgentUtils
{
public:
    static int Init();
    
    /* 获取agent当前状态 */
    static bool GetAgentRunning();

    /* 停止agent */
    static void StopAgent();

    //获取日志配置文件
    static string GetLogConfFile();

    //获取rabbitmq配置文件
    static string GetRabbitmqConfFile();

    //获取Agent主机配置门限脚本
    static string GetAgentEtcPath();

    //获取agent脚本路径
    static string GetAgentScriptPath();
    
    //获取agent日志路径
    static string GetAgentLogPath();

    //获取agent根目录
    static string GetAgentPath();

    //获取当前Agent版本
    static string GetAgentVersion();

    //获取脚本路径
    static string GetScripPath();

    //获取文件绝对路径
    static string GetFileAbsPath();

    //获取本地IP
    static string GetLocalIP();

    //获取本地IPV6
    static string GetLocalIPV6();

    //开启IPV6返回true, 否则返回false
    static bool UseIPV6();

    //获取APP消息端口
    static string GetAppMsgPort();

    //获取文件名
    static string GetFileName();

    //获取当前时间
    static unsigned long long GetCurrentTimeMsec();

private:
    static int __LoadSystemConfig(string &filName);
    static int __LoadAgentVersion(string &fileName);
private:
    static string sm_logConfFile;
    static string sm_rabbitmqConfFile;
    static string sm_systemConfigFile;
    static string sm_agentVersionFile;
    static string sm_agentVersion;
    static string sm_agentPath;
    static string sm_agentIP;
    static string sm_agentIPV6;
    static string sm_agentIP_FLAG;
    static string sm_appMsgPort;
    static bool   sm_agentRunning;
    static CMutex sm_lock;
};

#endif
