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
queue<Major>* AmqpMessageSendProcessor::msgQueue = new (std::nothrow) queue<Major>;


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
	    else
	    {
		sm_amqpMessageSendProcessor->Start();
	    }
            
        }
        sm_lock.unlock();
    }

    return sm_amqpMessageSendProcessor;
}

void AmqpMessageSendProcessor::__DoRun()
{
	if(msgQueue == NULL || m_messageSender == NULL)
	{
		return;
	}
	while(1)
	{
		if(msgQueue->empty())
		{
			usleep(1000);
			continue;		
		}
		Major major = msgQueue->front();
		m_messageSender->SendMessageToFums(major);
		msgQueue->pop();
	}
}


int AmqpMessageSendProcessor::SendMessageToFums(Major &msg)
{
	//static int i = 0;
	//SV_LOG("send------------------------------%d", i++);
    	if(msgQueue == NULL)
	{
		return -1;
	}

	msgQueue->push(msg);

    	return 0;
}

