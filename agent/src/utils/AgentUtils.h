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
private:
    static const int ALARM_FILTER_TIMES = 5;
    static const string rabbitmqConfFile;
public:
    //获取当前Agent版本
    string GetAgentVersion();
    //获取当前时间
    unsigned long long GetCurrentTimeMsec();
    //获取脚本路径
    string GetScripPath();
    //获取文件绝对路径
    string GetFileAbsPath();
    //获取本地IP
    string GetLocalIP();
    //获取文件名
    string GetFileName();
    //获取rabbitmq配置文件
    string GetRabbitmqConfFile();
};
