/*************************************************************************
	> File Name: agent_main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月02日 星期五 15时05分14秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h> 
#include <unistd.h>
#include <string>
#include "../msg/RabbitmqConfig.h"
#include "ThreadPool.h"
#include "../msg/AmqpReceiveBuilder.h"
#include "../msg/AmqpMessageReceiveProcessor.h"
#include "../msg/AmqpMessageSendProcessor.h"
#include "../proto/Msg.pb.h"
#include "../utils/AgentUtils.h"
#include "../utils/sv_log.h"
using namespace std;
using namespace com::fiberhome::fums::proto;



int fun1(int s, char *q)
{
    printf("s = %d\n", s);
    printf("q = %s\n", q);

    for(int i = 0; i<10; i++)
    {
        printf("sleep %d\n", i);
        sleep(1);
    }

    return 1;
}


int log_init()
{
    string logFile("/opt/fonsview/NE/agentd/etc/log.conf");
    if(sv_log_init(logFile.c_str(), 5) < 0)
    {
        return -1;
    }
    SV_LOG("%s", "init log");
    
    return 0;
}

int RabbitmqInit()
{
    SV_LOG("初始化MQ配置");
    RabbitmqConfig::Init();

    SV_LOG("启动MQ消息接收");
    AmqpReceiveBuilder* messageReceiver = AmqpReceiveBuilder::GetInstance();
    if(messageReceiver->Stop() == true)
    {
        messageReceiver->Start();
    }

    SV_LOG("初始化MQ消息发送处理器");
    AmqpMessageSendProcessor* messageProcessor = AmqpMessageSendProcessor::GetInstance();
    if(messageProcessor == NULL || messageProcessor->CheckSender() < 0)
    {
        SV_ERROR("AmqpMessageReceiveProcessor init error");
        return -1;
    }

    return 0;
}

int InitAgent()
{
    if(log_init() < 0)
    {
    	SV_ERROR("log init error");
	return -1;
    }

    if(RabbitmqInit() < 0)
    {
        SV_ERROR("RabbitmqInit error");
        return -1;
    }
    
    return 0;
}


int main(int argc, char *argv[])
{
    std::cout<<argv[0]<<std::endl;
    if(InitAgent() < 0)
    {
	SV_ERROR("init agent error");
	return 0;
    }

    //test
    Major major;
    Header* header = major.mutable_header();
    header->set_type(Header::ALARM);
    AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
    //char aa[] = "abcde";
	
    /*
    std::ThreadPool *executor = new (std::nothrow) ThreadPool{4};
    if(executor == NULL)
    {
        printf("new error\n");
        return -1;
    }
    std::future<int> f1 = executor->AddTaskToQueue(fun1, 1, aa);
    if(!executor->IsFullQueue())
        std::future<int> f2 = executor->AddTaskToQueue(fun1, 2, aa);
    std::future<int> f3 = executor->AddTaskToQueue(fun1, 3, aa);
    if(!executor->IsFullQueue())
        std::future<int> f4 = executor->AddTaskToQueue(fun1, 4, aa);
    std::future<int> f5 = executor->AddTaskToQueue(fun1, 5, aa);
    if(!executor->IsFullQueue())
        std::future<int> f6 = executor->AddTaskToQueue(fun1, 6, aa);
    std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
    sleep(5);
    SV_LOG("%s", "aaaa");
    */
    while(1)
    {
        sleep(10);
        printf("运行中。。。");
    }
    //delete executor;
    return 0;
}
