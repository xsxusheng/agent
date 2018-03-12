/*************************************************************************
	> File Name: AgentConfig.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月13日 星期二 16时45分49秒
 ************************************************************************/

#include <string>
using namespace std;

class AgentUtils
{
public:
    static int Init();
    //获取当前Agent版本
    static string GetAgentVersion();
    //获取当前时间
    static unsigned long long GetCurrentTimeMsec();
    //获取脚本路径
    static string GetScripPath();
    //获取文件绝对路径
    static string GetFileAbsPath();
    //获取本地IP
    static string GetLocalIP();
    //获取文件名
    static string GetFileName();
    //获取rabbitmq配置文件
    static string GetRabbitmqConfFile();

private:
    static int __LoadSystemConfig(string &filName);
    static int __LoadAgentVersion(string &fileName);
private:
    static string sm_rabbitmqConfFile;
    static string sm_systemConfigFile;
    static string sm_agentVersionFile;
    static string sm_agentIP;
    static string sm_appMsgPort;
    static string sm_etcPath;
};
