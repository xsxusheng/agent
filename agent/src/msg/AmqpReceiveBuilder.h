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
	//获取单实例
    static AmqpReceiveBuilder* GetInstance();
    //初始化消息接收channel
    int InitMessageChannel();
	//判断mq消息接收client是否停止
    bool Stop();

protected:
    AmqpReceiveBuilder();
private:
    void __StartConsume();
	//实例化基类接口
    void __DoRun();
    //创建消息接收通道
    void __AmqpMessageProcess(string message);
    static Locker sm_lock;
    static AmqpReceiveBuilder *sm_amqpReceiveBuilder;
    bool m_stop; 
};
#endif
