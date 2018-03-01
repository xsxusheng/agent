/*************************************************************************
	> File Name: AmqpReceiveBuilder.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月14日 星期三 15时40分07秒
 ************************************************************************/

#ifndef _AMQPRECEIVEBUILDER_H
#define _AMQPRECEIVEBUILDER_H
#include <string>
#include "AmqpMessage.h"
#include "Locker.h"
using namespace std;


class AmqpReceiveBuilder : public AmqpMessage
{
public:
    static AmqpReceiveBuilder* GetInstance();
    
    int InitAmqpMessageChannel();

protected:
    AmqpReceiveBuilder();
private:
    void StartConsume();
private:
    //创建消息接收通道
    int CreateAmqpReceiveMessageChannel();
    void AmqpMessageProcess(string message);
    static Locker lock;
    static AmqpReceiveBuilder *amqpReceiveBuilder;
};
#endif
