/*************************************************************************
	> File Name: agent_main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月02日 星期五 15时05分14秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h> 
#include <unistd.h>
#include "../msg/amqp_sendstring.h"
#include "../msg/amqp_receive_msg.h"
#include "../msg/RabbitmqConfig.h"
#include "ThreadPool.h"
#include "../msg/AmqpReceiveBuilder.h"
#include "../utils/AgentUtils.h"
#include "../utils/sv_log.h"
#include <string>
using namespace std;



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
    string logFile("/root/agent_demo/agent/etc/log.conf");
    if(sv_log_init(logFile.c_str(), 5) < 0)
            return -1;
    SV_LOG("%s", "init log");
    
    return 0;
}

int rabbitmq_init()
{
    RabbitmqConfig::Init();
    return 0;
}

int InitAgent()
{
    SV_LOG("init rabbitmq");
    rabbitmq_init();
    AmqpReceiveBuilder* messageAccess = AmqpReceiveBuilder::GetInstance();
    if(messageAccess == NULL)
    {
        SV_ERROR("Fail to get AmqpReceiveBuilder");
        return -1;
    }
    
    SV_LOG("init channel");
    if(messageAccess->InitAmqpMessageChannel() < 0)
    {
        SV_ERROR("Fail to init MQ channel");
        return -1;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    std::cout<<argv[0]<<std::endl;
    log_init();
    InitAgent();

    char aa[] = "abcde";
    int g = 2;

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

    delete executor;
    return 0;
}
