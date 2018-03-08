/*************************************************************************
	> File Name: AmqpReceiveBuilder.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月14日 星期三 15时40分07秒
 ************************************************************************/

#ifndef _AMQPRECEIVEBUILDER_H
#define _AMQPRECEIVEBUILDER_H
#include <string>
#include "../utils/Thread.h"
#include "AmqpMessage.h"
#include "Locker.h"
using namespace std;


class AmqpReceiveBuilder : public AmqpMessage, public Thread
{
public:
    static AmqpReceiveBuilder* GetInstance();
    
    int InitMessageChannel();
    bool Stop();

protected:
    AmqpReceiveBuilder();
private:
    void __StartConsume();
    void __DoRun();
    //创建消息接收通道
    void __AmqpMessageProcess(string message);
    static Locker sm_lock;
    static AmqpReceiveBuilder *sm_amqpReceiveBuilder;
    bool m_stop; 
};
#endif
