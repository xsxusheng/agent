/*************************************************************************
	> File Name: AmqpMessageSendProcessor.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年03月04日 星期日 15时30分55秒
 ************************************************************************/

#include <iostream>
#include "../utils/sv_log.h"
#include "AmqpMessageSendProcessor.h" 

AmqpMessageSendProcessor* AmqpMessageSendProcessor::sm_amqpMessageSendProcessor = NULL;
Locker AmqpMessageSendProcessor::sm_lock;


AmqpMessageSendProcessor::AmqpMessageSendProcessor()
{
    m_messageSender = new (std::nothrow) AmqpSendBuilder();
    if(m_messageSender == NULL)
    {
        SV_ERROR("new error");
    }
    else
    {
        if(m_messageSender->InitMessageChannel() < 0)
        {
            SV_ERROR("init channel error");
            delete m_messageSender;
            m_messageSender = NULL;
        }
    }

}


int AmqpMessageSendProcessor::CheckSender()
{
    if(m_messageSender == NULL)
    {
        SV_ERROR("Fail to create message sender");
        return -1;
    }

    return 0;
}


/*
 * 获取mq发送处理器单实例
 */
AmqpMessageSendProcessor* AmqpMessageSendProcessor::GetInstance()
{
    if(sm_amqpMessageSendProcessor == NULL)
    {
        sm_lock.lock();
        if(sm_amqpMessageSendProcessor == NULL)
        {
            sm_amqpMessageSendProcessor = new (std::nothrow) AmqpMessageSendProcessor();
            if(sm_amqpMessageSendProcessor == NULL)
            {
                SV_ERROR("new error");
            }
            
        }
        sm_lock.unlock();
    }

    return sm_amqpMessageSendProcessor;
}


int AmqpMessageSendProcessor::SendMessageToFums(Major &msg)
{
    if(m_messageSender == NULL)
    {
        SV_ERROR("message sender error, please check the status of rabbitmq server");
        return -1;
    }
    m_messageSender->SendMessageToFums(msg);
    return 0;
}

