/*************************************************************************
	> File Name: AmqpSendBuilder.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月24日 星期六 14时49分29秒
 ************************************************************************/

#ifndef _AMQPSENDBUILDER_H
#define _AMQPSENDBUILDER_H
#include <string>
#include "../proto/Msg.pb.h"
#include "AmqpMessage.h"
using namespace com::fiberhome::fums::proto;
using namespace std;

class AmqpSendBuilder : public AmqpMessage
{
public:
    AmqpSendBuilder();
    ~AmqpSendBuilder();
    int InitMessageChannel();
    int SendMessageToFums(Major &msg);
    string GetSendQueuename(int msgType);
    string GetSendRoutingKey(int msgType);
};
#endif
