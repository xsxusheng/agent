/*************************************************************************
	> File Name: rabbitmqConfig.cpp
	> Author:xus103 
	> Mail: 
	> Created Time: 2018年02月09日 星期五 15时15分39秒
 ************************************************************************/

#include <iostream>
#include <exception>
#include <string>
#include <stdlib.h>
#include "../utils/sv_log.h"
#include "../utils/AgentUtils.h"
#include "RabbitmqConfig.h"
using namespace std;

Properties* RabbitmqConfig::sm_props = NULL;

int RabbitmqConfig::Init()
{
    try {
        string rabbitmqConfFile("/opt/fonsview/NE/agent/etc/rabbitmq.properties");
        if(sm_props != NULL)
        {
            delete sm_props;
            sm_props = NULL;
        }
        sm_props = new Properties();
        sm_props->Load(rabbitmqConfFile);
    }catch(...){
        SV_LOG("read rabbitmq.properties error");
        return -1;
    }

    return 0;
}

string RabbitmqConfig::GetHost()
{
    string host = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    host = sm_props->GetValue("rabbitmq.host");
    if(host.empty())
    {
        SV_ERROR("Fail to get host");
        throw -1;
    }

    return host;
}

string RabbitmqConfig::GetVnmhost()
{
    string vnmhost = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    vnmhost = sm_props->GetValue("rabbitmq.vnmhost");
    if(vnmhost.empty())
    {
        SV_ERROR("Fail to get vnmhost");
        throw -1;
    }

    return vnmhost;
}

string RabbitmqConfig::GetUserName()
{
    string userName = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    userName = sm_props->GetValue("rabbitmq.username");
    if(userName.empty())
    {
        SV_ERROR("Fail to get userName");
        throw -1;
    }

    return userName;
}

string RabbitmqConfig::GetPassword()
{
    string password = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    password = sm_props->GetValue("rabbitmq.password");
    if(password.empty())
    {
        SV_ERROR("password is empty");
        throw -1;
    }

    return password;
}

int RabbitmqConfig::GetPort()
{
    string port = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    port = sm_props->GetValue("rabbitmq.port");
    if(port.empty())
    {
        return 5672;
    }

    return atoi(port.c_str());
        
}
string RabbitmqConfig::GetExchangeNmr()
{
    string exchangeNmr = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    exchangeNmr = sm_props->GetValue("rabbitmq.exchange_nmr");
    if(exchangeNmr.empty())
    {
        SV_ERROR("Fail to get exchangeNmr");
        throw -1;
    }

    return exchangeNmr;
        
}
string RabbitmqConfig::GetExchangeNms()
{
    string exchangeNms = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    exchangeNms = sm_props->GetValue("rabbitmq.exchange_nms");
    if(exchangeNms.empty())
    {
        SV_ERROR("Fail to get exchangeNms");
        throw -1;
    }

    return exchangeNms;
        
}

string RabbitmqConfig::GetSendCommQueue()
{
    string sendCommQueue = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    sendCommQueue = sm_props->GetValue("rabbitmq.queue_comm");
    if(sendCommQueue.empty())
    {
        SV_ERROR("Fail to get host");
        throw -1;
    }

    return sendCommQueue;
}

string RabbitmqConfig::GetRecvCommQueue()
{
    string recvCommQueue = "";

    recvCommQueue = AgentUtils::GetLocalIP();
    if(recvCommQueue.empty())
    {
        SV_ERROR("Fail to get host");
        throw -1;
    }

    SV_ERROR("%s", recvCommQueue.c_str());
    //127.0.0.1 --> 127_0_0_1
    while(1)
    {
        string::size_type pos(0);
        if((pos = recvCommQueue.find(".")) != string::npos)
        {
            recvCommQueue.replace(pos, 1, "_");
        }
        else
        {
            break;
        }
    }
    
    return recvCommQueue;
}

string RabbitmqConfig::GetHeartQueue()
{
    string heartQueue = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    heartQueue = sm_props->GetValue("rabbitmq.queue_heart");
    if(heartQueue.empty())
    {
        SV_ERROR("Fail to get heartQueue");
        throw -1;
    }

    return heartQueue;
}
string RabbitmqConfig::GetAlarmQueue()
{
    string alarmQueue = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    alarmQueue = sm_props->GetValue("rabbitmq.queue_alarm");
    if(alarmQueue.empty())
    {
        SV_ERROR("Fail to get alarmQueue");
        throw -1;
    }

    return alarmQueue;
}
string RabbitmqConfig::GetPerfQueue()
{
    string perfQueue = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    perfQueue = sm_props->GetValue("rabbitmq.queue_perf");
    if(perfQueue.empty())
    {
        SV_ERROR("Fail to get perfQueue");
        throw -1;
    }

    return perfQueue;
}

string RabbitmqConfig::GetCommRoutingKey()
{
    string commRoutingKey = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    commRoutingKey = sm_props->GetValue("rabbitmq.routing_key_comm");
    if(commRoutingKey.empty())
    {
        SV_ERROR("Fail to get commRoutingkey");
        throw -1;
    }

    return commRoutingKey;
}

string RabbitmqConfig::GetHeartRoutingKey()
{
    string heartRoutingKey = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    heartRoutingKey = sm_props->GetValue("rabbitmq.routing_key_heart");
    if(heartRoutingKey.empty())
    {
        SV_ERROR("Fail to get heartRoutingkey");
        throw -1;
    }

    return heartRoutingKey;
}

string RabbitmqConfig::GetAlarmRoutingKey()
{
    string alarmRoutingKey = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    alarmRoutingKey = sm_props->GetValue("rabbitmq.routing_key_alarm");
    if(alarmRoutingKey.empty())
    {
        SV_ERROR("Fail to get alarmRoutingkey");
        throw -1;
    }

    return alarmRoutingKey;
}

string RabbitmqConfig::GetPerfRoutingKey()
{
    string perfRoutingKey = "";

    if(sm_props == NULL)
    {
        SV_ERROR("sm_props is NULL");
        throw -1;
    }
    perfRoutingKey = sm_props->GetValue("rabbitmq.routing_key_perf");
    if(perfRoutingKey.empty())
    {
        SV_ERROR("Fail to get perfRoutingkey");
        throw -1;
    }

    return perfRoutingKey;
}
