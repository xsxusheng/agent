/*************************************************************************
	> File Name: AmqpMessageSendProcessor.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月04日 星期日 15时30分40秒
 ************************************************************************/

#ifndef _AMQPMESSAGESENDPROCESSOR_H
#define _AMQPMESSAGESENDPROCESSOR_H
#include <iostream>
#include <queue>
#include "../utils/Thread.h"
#include "../proto/Msg.pb.h"
#include "Locker.h"
#include "AmqpSendBuilder.h"
using namespace com::fiberhome::fums::proto;


class AmqpMessageSendProcessor : public Thread
{
public:
    static AmqpMessageSendProcessor* GetInstance();
    int CheckSender();
    int SendMessageToFums(Major &major);

protected:
    AmqpMessageSendProcessor();

private:
    void __DoRun();
    static queue<Major> *msgQueue;
    static Locker sm_lock;
    static AmqpMessageSendProcessor* sm_amqpMessageSendProcessor;
    AmqpSendBuilder* m_messageSender;

};
#endif
