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
#include "AmqpMessageReceiveProcessor.h"
#include "TaskManager.h"
using namespace std;

/*
 * 初始化为NULL
 */
AmqpReceiveBuilder* AmqpReceiveBuilder::sm_amqpReceiveBuilder = NULL;
Locker AmqpReceiveBuilder::sm_lock;

AmqpReceiveBuilder::AmqpReceiveBuilder() : m_stop(true)
{

    SV_LOG("构造函数 AmqpReceiveBuilder");
}

/*
 * 获取mq接收消息的单实例
 */
AmqpReceiveBuilder* AmqpReceiveBuilder::GetInstance()
{
    if(sm_amqpReceiveBuilder == NULL)
    {
        sm_lock.lock();
        if(sm_amqpReceiveBuilder == NULL)
        {
            sm_amqpReceiveBuilder = new (std::nothrow) AmqpReceiveBuilder();
        }
        sm_lock.unlock();
    }

    return sm_amqpReceiveBuilder;
}

bool AmqpReceiveBuilder::Stop()
{
    return m_stop;
}

void AmqpReceiveBuilder::__DoRun()
{
    m_stop = false;
    SV_LOG("启动MQ消息监听线程");
    InitMessageChannel();
    SV_LOG("停止MQ消息监听线程");
    m_stop = true;
}


/*
 * 初始化MQ消息通道
 */
int AmqpReceiveBuilder::InitMessageChannel()
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
        commQueue = RabbitmqConfig::GetRecvCommQueue();
        commExchage = RabbitmqConfig::GetExchangeNms();
        commRoutingKey = commQueue;
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
        __StartConsume();
    }catch(...){
        SV_ERROR("CreateAmqpReceiveMessageChannel error");
    }

    return 0;
}

void AmqpReceiveBuilder::__StartConsume()
{
    TaskManager* taskManager = NULL;;
    string message;
    bool ready = true;
    
    SV_LOG("start consume");
    while(1)
    {	
    	message = "";
		sleep(1);
        AmqpMessage::ReceiveMessage(message);
		for(int i = 0; i<1; i++)
		{
			taskManager = TaskManager::GetInstance();
			taskManager->MessageProcess(message);
			usleep(10000);
			ready = false;
			while(!ready)
			{
        		taskManager = TaskManager::GetInstance();
				taskManager->CheckTask();
				ready = !taskManager->TaskIsFull();
				if(!ready)
				{
					sleep(1);
				}
			}
		}
    }
}
