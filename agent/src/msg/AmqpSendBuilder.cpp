/*************************************************************************
	> File Name: AmqpSendBuilder.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年03月01日 星期四 15时51分42秒
 ************************************************************************/

#include<iostream>
#include "../utils/sv_log.h"
#include "../utils/base64.h"
#include "../utils/ProtoBufPacker.h"
#include "RabbitmqConfig.h"
#include "AmqpSendBuilder.h"

AmqpSendBuilder::AmqpSendBuilder()
{
    SV_LOG("connection");
}


AmqpSendBuilder::~AmqpSendBuilder()
{
    SV_LOG("disconnection");
}

int AmqpSendBuilder::InitMessageChannel()
{
    string host;
    int port;
    string vnmhost;
    string userName;
    string password;
    string exchange;
    string exchngeType("direct");

    try
    {
        host = RabbitmqConfig::GetHost();
        port = RabbitmqConfig::GetPort();
        vnmhost = RabbitmqConfig::GetVnmhost();
        userName = RabbitmqConfig::GetUserName();
        password = RabbitmqConfig::GetPassword();
        exchange = RabbitmqConfig::GetExchangeNmr();
    }catch(...){
        SV_ERROR("InitMessageChannel parameter error");
        return -1;
    }

    try
    {
        Connection(host, port, vnmhost, userName, password);
        CreateChannel();
        ExchangeDeclare(exchange, exchngeType, 0, 1, 0, 0);
    }catch(...){
        SV_ERROR("InitMessageChannel connection error");
        return -1;
    }


    return 0;
}

string AmqpSendBuilder::GetSendQueuename(int msgType)
{
    string queuename;

    if(msgType == Header::PERF)
    {
        queuename = RabbitmqConfig::GetPerfQueue();
        SV_LOG("msgType PERF");
    }
    else if(msgType == Header::ALARM)
    {
        queuename = RabbitmqConfig::GetAlarmQueue();
        SV_LOG("msgType ALARM");
        
    }
    else if(msgType == Header::HEART)
    {
        queuename = RabbitmqConfig::GetHeartQueue();
    }
    else
    {
        queuename = RabbitmqConfig::GetSendCommQueue();
    }

    return queuename;
}

string AmqpSendBuilder::GetSendRoutingKey(int msgType)
{
    string routingKey;

    if(msgType == Header::PERF)
    {
        routingKey = RabbitmqConfig::GetPerfRoutingKey();
        SV_LOG("msgType PERF");
    }
    else if(msgType == Header::ALARM)
    {
        routingKey = RabbitmqConfig::GetAlarmRoutingKey();
        SV_LOG("msgType ALARM");
        
    }
    else if(msgType == Header::HEART)
    {
        routingKey = RabbitmqConfig::GetHeartRoutingKey();
    }
    else
    {
        routingKey = RabbitmqConfig::GetCommRoutingKey();
    }

    return routingKey;
}

int AmqpSendBuilder::SendMessageToFums(Major &major)
{
    int msgType = 0;
    string queuename;
    string routingKey;
    string exchange;

    if(!major.has_header())
    {
	SV_ERROR("parse message error");
	return -1;
    }
	ProtoBufPacker::ProtoToString(major);
    try
    {
    	/* 获取消息类型 */
        msgType =  major.header().type();
		string message(base64_encode(ProtoBufPacker::SerializeToArray(major)));
		
        //queuename = GetSendQueuename(msgType);
        routingKey = GetSendRoutingKey(msgType);
        exchange = RabbitmqConfig::GetExchangeNmr();
		

        //QueueDeclare(queuename, 0, 1, 1, 1);
        //QueueBind(queuename, exchange, routingKey);
        /* persistent delivery mode */
        //SetPublishProps(2);
        BasicPublish(exchange, routingKey, message);
    }catch(...){
        SV_ERROR("send message error");
    }

    return 0;
}


