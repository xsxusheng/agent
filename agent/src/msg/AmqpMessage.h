/*************************************************************************
* File Name : AmqpMessage.h
* Author : xus103
* Created Time : 2018年03月01日
* Description : rabbitmq client operation function
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
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
    virtual ~AmqpMessage();

protected:
	/* 连接 mq server */
    void Connection(string &ip, int port, string &virtualHost, string &userName, string &password);
	/* 创建 mq channel */
    void CreateChannel();
	/* 声明 mq exchange */
    void ExchangeDeclare(string &exchange, string &exchangeType, int passive, int durable, int autoDelete, int internal);
	/* 声明 mq queue */
    void QueueDeclare(string &queuename, int passive, int durable, int exclusive, int autoDelete);
	/* 绑定mq queue */
    void QueueBind(string &queuename, string &exchange, string &routingKey);
	/* 设置属性 */
    void SetPublishProps(int durable = 2);
	/* 发送一条消息 */
    void BasicPublish(string &exchange, string &routingKey, string &message);
	/* 设置qos */
    void BasicQos(int prefetchCount);
	/* 设置consumer */
    void SetConsumer(string &queuename, int noAck);
	/* 接收一条消息 */
    void ReceiveMessage(string &message);
    
private:
	virtual void __StartConsume();
    int m_type;
    amqp_basic_properties_t m_props;
    amqp_connection_state_t m_conn;
};
#endif
