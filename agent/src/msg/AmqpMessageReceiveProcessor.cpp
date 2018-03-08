/*************************************************************************
	> File Name: AmqpMessageReceiveProcessor.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 13时33分07秒
 ************************************************************************/

#include <iostream>
#include "../utils/sv_log.h"
#include "AmqpMessageReceiveProcessor.h"
using namespace std;

AmqpMessageReceiveProcessor::AmqpMessageReceiveProcessor()
{
    
}


AmqpMessageReceiveProcessor::~AmqpMessageReceiveProcessor()
{

}

void AmqpMessageReceiveProcessor::Run()
{
    SV_LOG("MQ接收器线程结束");
}


/*
 * MQ消息处理
 */
int AmqpMessageReceiveProcessor::MessageProcess()
{
    return 0;
}

/*
 * 根据消息类型分发处理
 */
int AmqpMessageReceiveProcessor::MessageDispatcher()
{
    return 0;
}

/*
 * 处理CMD命令
 */
int AmqpMessageReceiveProcessor::ProcessCommand()
{
    return 0;
}

/*
 * 实时查询
 */
int AmqpMessageReceiveProcessor::ProcessRealQuery()
{
    return 0;
}

/*
 * 配置下传处理
 */
int AmqpMessageReceiveProcessor::ProcessConfig()
{
    return 0;
}

/*
 * 软件升级处理
 */
int AmqpMessageReceiveProcessor::ProcessSoftwareInstall()
{
    return 0;
}

