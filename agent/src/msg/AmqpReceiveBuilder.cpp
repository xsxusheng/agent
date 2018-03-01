/*************************************************************************
	> File Name: AmqpReceiveBuilder.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月22日 星期四 16时21分15秒
 ************************************************************************/

#include <iostream>
#include <exception>
#include <unistd.h>
#include "AmqpReceiveBuilder.h"
#include "../utils/sv_log.h"
#include "RabbitmqConfig.h"
using namespace std;

/*
 * 初始化为NULL
 */
AmqpReceiveBuilder* AmqpReceiveBuilder::amqpReceiveBuilder = NULL;
Locker AmqpReceiveBuilder::lock;

AmqpReceiveBuilder::AmqpReceiveBuilder()
{
    ;
}

/*
 * 获取mq接收消息的单实例
 */
AmqpReceiveBuilder* AmqpReceiveBuilder::GetInstance()
{
    if(amqpReceiveBuilder == NULL)
    {
        lock.lock();
        if(amqpReceiveBuilder == NULL)
        {
            amqpReceiveBuilder = new AmqpReceiveBuilder();
        }
        lock.unlock();
    }

    return amqpReceiveBuilder;
}


/*
 * 初始化MQ消息通道
 */
int AmqpReceiveBuilder::InitAmqpMessageChannel()
{
    int res = 0;

    res = CreateAmqpReceiveMessageChannel();
    if(res < 0)
    {
        return -1;
    }

    return 0;
}
int AmqpReceiveBuilder::CreateAmqpReceiveMessageChannel()
{
    string host("");
    int port;
    string vnmhost("");
    string userName("");
    string password = "";
    string commQueue = "";
    string commExchage = "";
    string commExchageType("direct");
    string commRoutingKey = "";


    try
    {
        host = RabbitmqConfig::GetHost();
        port = RabbitmqConfig::GetPort();
        vnmhost = RabbitmqConfig::GetVnmhost();
        userName = RabbitmqConfig::GetUserName();
        password = RabbitmqConfig::GetPassword();
        commQueue = RabbitmqConfig::GetCommQueue();
        commExchage = RabbitmqConfig::GetExchangeNms();
        commRoutingKey = RabbitmqConfig::GetCommRoutingKey();
    }catch(exception& e){
        SV_LOG("CreateAmqpReceiveMessageChannel parameter error");
        return -1;
    }

    SV_LOG("commQueue is %s", commQueue.c_str());
    try
    {
        Connection(host, port, vnmhost, userName, password);
        CreateChannel();
        ExchangeDeclare(commExchage, commExchageType, 0, 1, 0, 0);
        QueueDeclare(commQueue, 0, 1, 0, 0);
        QueueBind(commQueue, commExchage, commRoutingKey);
        BasicQos(10);
        SetConsumer(commQueue, 1);
        StartConsume();
    }catch(...){
        SV_ERROR("CreateAmqpReceiveMessageChannel error");
    }

    return 0;
}

void AmqpReceiveBuilder::StartConsume()
{
    string message;
    
    SV_LOG("start consume");
    while(1)
    {
        SV_LOG("start consume i");
        message = "";
        AmqpMessage::ReceiveMessage(message);
        cout<<message<<endl;
        SV_LOG(const_cast <char *>(message.c_str()));
        sleep(1);
    }
}
