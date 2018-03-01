/*************************************************************************
	> File Name: AmqpMessage.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 16时29分35秒
 ************************************************************************/

#ifndef _AMQPMESSAGE_H
#define _AMQPMESSAGE_H
#include <string>
#ifdef __cplusplus
extern "C" {
#endif
#include <unistd.h>
#include <string.h>
#include <amqp.h>
#include <amqp_framing.h>
#include <amqp_tcp_socket.h>
#define AMQP_CONSUME_MAX_PREFETCH_COUNT 256
#ifdef __cplusplus
}
#endif
using namespace std;

class AmqpMessage
{
public:
    AmqpMessage();
    ~AmqpMessage();

protected:
    void Connection(string &ip, int port, string &virtualHost, string &userName, string &password);
    void CreateChannel();
    void ExchangeDeclare(string &exchange, string &exchangeType, int passive, int durable, int autoDelete, int internal);
    void QueueDeclare(string &queuename, int passive, int durable, int exclusive, int autoDelete);
    void QueueBind(string &queuename, string &exchange, string &routingKey);
    void BasicQos(int prefetchCount);
    void SetConsumer(string &queuename, int noAck);
    void ReceiveMessage(string &message);
    virtual void StartConsume();

private:
    int m_type;
    amqp_connection_state_t m_conn;
};
#endif
