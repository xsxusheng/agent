/*************************************************************************
	> File Name: AmqpMessageSendProcessor.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月04日 星期日 15时30分40秒
 ************************************************************************/

#ifndef _AMQPMESSAGESENDPROCESSOR_H
#define _AMQPMESSAGESENDPROCESSOR_H
#include "Locker.h"
#include "AmqpSendBuilder.h"

class AmqpMessageSendProcessor
{
public:
    static AmqpMessageSendProcessor* GetInstance();
    int CheckSender();
    int SendMessageToFums(Major &major);

protected:
    AmqpMessageSendProcessor();

private:
    static Locker sm_lock;
    static AmqpMessageSendProcessor* sm_amqpMessageSendProcessor;
    AmqpSendBuilder* m_messageSender;

};
#endif
