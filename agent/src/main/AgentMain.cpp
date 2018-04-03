/*************************************************************************
* File Name : agent_main.cpp
* Author : xus103
* Created Time : 2018年03月01日
* Description : main function
* CopyRight : Copyright(c) 2000-2020 firberhome
* OtherInfo :
* ModifyLog :
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
#include "../utils/ProtoBufPacker.h"
#include "../proto/HeartProto.pb.h"
using namespace std;
using namespace com::fiberhome::fums::proto;


//日志系统初始化
static int log_init()
{
    string logFile(AgentUtils::GetAgentEtcPath() + AgentUtils::GetLogConfFile());
    if(sv_log_init(logFile.c_str(), 5) < 0)
    {
        return -1;
    }
    SV_LOG("%s", "init log");
    
    return 0;
}

//Rabbitmq 客户端初始化
static int RabbitmqInit()
{
    SV_LOG("初始化MQ配置");
    RabbitmqConfig::Init();

    SV_LOG("启动MQ消息接收");
    AmqpReceiveBuilder* messageReceiver = AmqpReceiveBuilder::GetInstance();
    if(messageReceiver == NULL || messageReceiver->Stop() == false)
    {
	SV_ERROR("get messageReceiver error");
	return -1;
    }
    SV_LOG("start messageReceiver");
    messageReceiver->Start();

    SV_LOG("初始化MQ消息发送处理器");
    AmqpMessageSendProcessor* messageProcessor = AmqpMessageSendProcessor::GetInstance();
    if(messageProcessor == NULL || messageProcessor->CheckSender() < 0)
    {
        SV_ERROR("AmqpMessageReceiveProcessor init error");
        return -1;
    }

    return 0;
}


//初始化agent
static int InitAgent()
{
    AgentUtils::Init();

    if(log_init() < 0)
    {
	return -1;
    }

    if(RabbitmqInit() < 0)
    {
        SV_ERROR("RabbitmqInit error");
        return -1;
    }
    
    return 0;
}

//agent 程序入口
int main(int argc, char *argv[])
{
    if(InitAgent() < 0)
    {
		SV_ERROR("init agent error");
		return 0;
    }

    //test
    
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
	//heart test
        sleep(5);
	HeartData heartData;
	heartData.set_hearttype(HeartData::AGENT);
	heartData.set_msg("Hello, World!");
	heartData.set_uniqueid(AgentUtils::GetCurrentTimeMsec());
	Major major = ProtoBufPacker::PackHeartBeatData(ProtoBufPacker::SerializeToArray<HeartData>(heartData));

    	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
        printf("运行中。。。");
    }
    //delete executor;
    return 0;
}
