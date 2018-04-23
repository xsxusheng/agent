/*************************************************************************
* File Name : AmqpMessage.cpp
* Author : xus103
* Created Time : 2018年03月01日
* Description : rabbitmq client operation function
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include <iostream>
#include <exception>
#include <malloc.h>
#include "AmqpMessage.h"
#include "../utils/sv_log.h"
using namespace std;


AmqpMessage::AmqpMessage()
{
    m_conn = NULL;
    //SV_LOG("构造函数 AmqpMessage");
}

AmqpMessage::~AmqpMessage()
{
    //SV_LOG("析构函数 AmqpMessage");
}

/***********************************************************************
 * FunctionName : DieOnAmqpError
 * Author : xus103
 * CreateDate : 2018/03/09
 * Description : 获取MQ操作的返回状态
 * InputParam : x - rpc reply
 				context - description
 * OutputParam :
 * Return Value : err type
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
int DieOnAmqpError(amqp_rpc_reply_t x, char const *context)
{
    switch (x.reply_type)
    {
        case AMQP_RESPONSE_NORMAL:
            return AMQP_RESPONSE_NORMAL;

        case AMQP_RESPONSE_NONE:
            //fprintf(stderr, "%s: missing RPC reply type!\n", context);
            SV_ERROR("%s: missing RPC reply type!\n", context);
            break;

        case AMQP_RESPONSE_LIBRARY_EXCEPTION:
            //fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
            SV_ERROR("%s: %s\n", context, amqp_error_string2(x.library_error));
        break;

        case AMQP_RESPONSE_SERVER_EXCEPTION:
            switch (x.reply.id)
            {
                case AMQP_CONNECTION_CLOSE_METHOD:
                {
                    amqp_connection_close_t *m = (amqp_connection_close_t *)x.reply.decoded;
                    //fprintf(stderr, "%s: server connection error %uh, message: %.*s\n", context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                    SV_ERROR("%s: server connection error %uh, message: %.*s\n", context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                     break;
                            
                }
                case AMQP_CHANNEL_CLOSE_METHOD:
                {
                    amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
                    //fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                    SV_ERROR("%s: server channel error %uh, message: %.*s\n",context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                    return AMQP_CHANNEL_CLOSE_METHOD;  
                }
                default:
                    //fprintf(stderr, "%s: unknown server error, method id 0x%08X\n", context, x.reply.id);
                    SV_ERROR("%s: unknown server error, method id 0x%08X\n", context, x.reply.id);
                    break;    
            }
            break;
    }

    return -1;
}


/***********************************************************************
 * FunctionName : Connection
 * Author : xus103
 * CreateDate : 2018/03/09
 * Description : 新建一个连接到mq server
 * InputParam : ip - rabbitmq server ip
 				port - rabbitmq port
 				virtualHost - vitual host "/"
 				userName - rabbitmq server user name
 				password - rabbitmq server user password
 * OutputParam : 无
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AmqpMessage::Connection(string &ip, int port, string &virtualHost, string &userName, string &password) 
{
	amqp_socket_t *socket = NULL;
    int error = AMQP_RESPONSE_NONE;
	
    if(ip.empty() || port <= 0 || virtualHost.empty() || userName.empty() || password.empty())
    {
        SV_ERROR("parameter error");
        throw -1;
    }   
    SV_LOG("connect mq server: ip: %s, port: %d, virtualHost: %s, userName: %s, password: %s", ip.c_str(), port, virtualHost.c_str(), userName.c_str(), password.c_str());

    m_conn = amqp_new_connection();
    if(m_conn == NULL)
    {
        SV_LOG("Fail to new amqp connection");
        throw -1;
    }
    socket = amqp_tcp_socket_new(m_conn);
    if(!socket)
    {
        SV_LOG("Fail to create TCP socket");
        throw -1;
    }

    int status = amqp_socket_open(socket, ip.c_str(), port);
    if(status)
    {
        SV_LOG("Fail to open TCP socket");
        throw -1;
    }

    error = DieOnAmqpError(amqp_login(m_conn, virtualHost.c_str(), 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, userName.c_str(), password.c_str()), "amqp login");
    if(error != AMQP_RESPONSE_NORMAL)
    {
        throw -1;
    }
}


/***********************************************************************
 * FunctionName : CreateChannel
 * Author : xus103
 * CreateDate : 2018/03/09
 * Description : 创建 mq channel
 * InputParam : 无
 * OutputParam : 无
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AmqpMessage::CreateChannel()
{
	int error = AMQP_RESPONSE_NONE;
	
	SV_LOG("creat_channel");
    if(m_conn == NULL)
    {
        SV_ERROR("can not create channel, m_conn is null");
        throw -1;
    }
   
    amqp_channel_open(m_conn, 1);
    error = DieOnAmqpError(amqp_get_rpc_reply(m_conn), "open channel");
	if(error != AMQP_RESPONSE_NORMAL)
    {
        SV_ERROR("xxx");
        throw -1;
    }
}



/***********************************************************************
 * FunctionName : ExchangeDeclare
 * Author : xus103
 * CreateDate : 2018/03/09
 * Description : 声明 mq exchange
 * InputParam : exchange : exchange
 				exchange : exchange 类型
 				passive :
 				durable : 持久化
 				autoDelete : 自动删除
 				internal : 
 * OutputParam : 无
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AmqpMessage::ExchangeDeclare(string &exchange, string &exchangeType, int passive, int durable, int autoDelete, int internal)
{
    int error = AMQP_RESPONSE_NONE;
	
	if(m_conn == NULL)
	{
		SV_ERROR("Can not declare exchange, m_conn is null");
		throw -1;
	}
	if(exchange.empty() || exchangeType.empty())
	{
		SV_ERROR("parameter error: exchange = %s, exchangeType = %s", exchange.c_str(), exchangeType.c_str());
		throw -1;
	}
	
    amqp_exchange_declare(m_conn, 1, amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(exchangeType.c_str()), passive, durable, autoDelete, internal, amqp_empty_table);
    error = DieOnAmqpError(amqp_get_rpc_reply(m_conn), "declare exchange");
    if(error != AMQP_RESPONSE_NORMAL)
    {
		SV_ERROR("declare exchange error");
        throw -1;
    }
}


/***********************************************************************
 * FunctionName : QueueDeclare
 * Author : xus103
 * CreateDate : 2018/03/09
 * Description : 声明 mq queue
 * InputParam : queuename : 队列
 				passive :
 				durable : 
 				exclusive : 连接不在时队列自动删除
 				auto_delete : consumer不在时自动删除
 * OutputParam : 无
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AmqpMessage::QueueDeclare(string &queuename, int passive, int durable, int exclusive, int auto_delete)
{
    int error = AMQP_RESPONSE_NONE;

	if(m_conn == NULL)
	{
		SV_ERROR("Can not declare queue, m_conn is null");
		throw -1;
	}
    if(queuename.empty())
    {
        SV_LOG("queuename is NULL");
        throw -1;
    }

    //amqp_queue_purge(m_conn, 1, amqp_cstring_bytes(queuename));
    //DieOnAmqpError(amqp_get_rpc_reply(m_conn), "");
    amqp_queue_declare(m_conn, 1, amqp_cstring_bytes(queuename.c_str()), passive, durable, exclusive, auto_delete, amqp_empty_table);
    error = DieOnAmqpError(amqp_get_rpc_reply(m_conn), "declare queue error");
    if(error != AMQP_RESPONSE_NORMAL)
    {
		SV_ERROR("queue declare error");
        throw -1;
    }
}

void AmqpMessage::QueueBind(string &queuename, string &exchange, string &routingKey)
{
    int error = AMQP_RESPONSE_NONE;
	
	if(queuename.empty() || exchange.empty() || routingKey.empty())
	{
		SV_LOG("parameter error: queuename = %s, exchange = %s, routingKey = %s", queuename.c_str(), exchange.c_str(), routingKey.c_str());
		throw -1;
	}
	
    if(m_conn == NULL)
    {
        SV_ERROR("can not bind queue, m_conn is null");
    }

    amqp_queue_bind(m_conn, 1, amqp_cstring_bytes(queuename.c_str()), amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(routingKey.c_str()), amqp_empty_table);
    error = DieOnAmqpError(amqp_get_rpc_reply(m_conn), "bind queue");
    if(error != AMQP_RESPONSE_NORMAL)
    {
		SV_ERROR("queue bind error");
        throw -1;
    }
}


void AmqpMessage::SetPublishProps(int durable)
{
    memset(&m_props, 0, sizeof(m_props));
    m_props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    m_props.content_type = amqp_cstring_bytes("text/plain");
    m_props.delivery_mode = 2;
}


void AmqpMessage::BasicPublish(string &exchange, string &routingKey, string &message)
{
    int result = 0;
    amqp_frame_t frame;
    amqp_rpc_reply_t ret;

    if(m_conn == NULL)
    {
        SV_ERROR("can not basic publish message, m_conn is null");
        throw -1;
    }
    if(exchange.empty() || routingKey.empty() || message.empty())
    {
        SV_ERROR("parameter error : exchange = %s, routingKey = %s", exchange.c_str(), routingKey.c_str());
        throw -1;
    }

    result = amqp_basic_publish(m_conn, 1, amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(routingKey.c_str()), 0, 0, &m_props, amqp_cstring_bytes(message.c_str()));
    if(result < 0)
    {
        SV_ERROR("basic publish message error");
        throw -1;
    }

    return;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 50000;
    if(AMQP_STATUS_OK != amqp_simple_wait_frame_noblock(m_conn, &frame, &timeout))
    {
        SV_ERROR("basic publish mesage timeout");
        throw -1;
    }

    if(AMQP_FRAME_METHOD == frame.frame_type)
    {
        amqp_method_t method = frame.payload.method;
        SV_LOG("method.id = %08X, method.name = %s", method.id, amqp_method_name(method.id));
        switch(method.id)
        {
            /* 如果开启消息确认机制，则消息被确认 */
            case AMQP_BASIC_ACK_METHOD:
            {
                amqp_basic_ack_t *s;
                s = (amqp_basic_ack_t *) method.decoded; 
                SV_LOG("Ack.delivery_tag = %d", s->delivery_tag);
                SV_LOG("Ack.multiple = %d", s->multiple);
            }
            break;

            /* 消息没有被确认 */
            case AMQP_BASIC_NACK_METHOD:
            {
                amqp_basic_nack_t *s;
                s = (amqp_basic_nack_t *) method.decoded;
                SV_LOG("NAck.delivery_tag = %d", s->delivery_tag);
                SV_LOG("NAck.multiple = %d", s->multiple);
                SV_LOG("NAck.requeue = %d", s->requeue);
            }
            break;
            /* if a published message couldn't be routed and the mandatory flag was set 
             * this is what would be returned. The message then needs to be read.
             */
            case AMQP_BASIC_RETURN_METHOD:
                {
                    amqp_message_t message;
                    amqp_basic_return_t *s;
                    char str[1024] = {0};
                    s = (amqp_basic_return_t *) method.decoded;
                    SV_LOG("Return.reply_code = %d", s->reply_code);
                    if(s->reply_text.len < 1024)
                    {
                        strncpy(str, (char *)s->reply_text.bytes, s->reply_text.len);
                    }
                    strncpy(str, (char *)s->reply_text.bytes, s->reply_text.len);
                    SV_LOG("Return.reply_text=%s\n", str);

                    ret = amqp_read_message(m_conn, frame.channel, &message, 0);
                    if (AMQP_RESPONSE_NORMAL != ret.reply_type)
                    {
                        SV_ERROR("amqp read message error");
                        throw -1;
                    }
                    if(message.body.len < 1024)
                    {
                        strncpy(str, (char *) message.body.bytes, message.body.len);
                        str[message.body.len] = 0;
                    }
                    SV_LOG("Return.message=%s\n", str);
                    amqp_destroy_message(&message);
                }
                break;

            case AMQP_CHANNEL_CLOSE_METHOD:
                SV_ERROR("amqp channel abnormal closed");
            case AMQP_CONNECTION_CLOSE_METHOD:
                SV_ERROR("amqp connection abnormal closed");
            default:
                SV_ERROR("basic publish exception");
                throw -1;
        }
    }
}


void AmqpMessage::BasicQos(int prefetchCount)
{
    if(m_conn == NULL)
    {
        SV_ERROR("can not set basic qos");
        throw -1;
    }

    if(prefetchCount < 0 || prefetchCount > AMQP_CONSUME_MAX_PREFETCH_COUNT)
    {
        SV_ERROR("parameter error : prefetchCount = %d", prefetchCount);
        throw -1;
    }

    if(!amqp_basic_qos(m_conn, 1, 0, prefetchCount, 0))
    {
        SV_ERROR("set basic qos error");
        throw -1;
    }
}

void AmqpMessage::SetConsumer(string &queuename, int noAck)
{
    int error = AMQP_RESPONSE_NONE;

    if(m_conn == NULL)
    {
        SV_ERROR("can not set consumer, m_conn is null");
        throw -1;
    }
    if(queuename.empty())
    {
        SV_ERROR("parameter error : queuename = %s", queuename.c_str());
        throw -1;
    }
    
    amqp_basic_consume(m_conn, 1, amqp_cstring_bytes(queuename.c_str()), amqp_empty_bytes, 0, noAck, 0, amqp_empty_table);
    error = DieOnAmqpError(amqp_get_rpc_reply(m_conn), "set consume");
    if(error != AMQP_RESPONSE_NORMAL)
    {
        SV_ERROR("set consumer error");
        throw -1;
    }
}

void AmqpMessage::ReceiveMessage(string &message)
{
    amqp_rpc_reply_t res;
    amqp_envelope_t envelope;

    SV_LOG("receive_message");
	if(m_conn == NULL)
	{
		SV_ERROR("Can not receive message, m_conn is null");
		throw -1;
	}
	
    amqp_maybe_release_buffers(m_conn);
    res = amqp_consume_message(m_conn, &envelope, NULL, 0);
    if(res.reply_type != AMQP_RESPONSE_NORMAL)
    {
        SV_ERROR("read message error");
        return;
    }
    SV_LOG("receive_message a message");
    if(envelope.message.body.bytes == NULL || envelope.message.body.len <= 0)
    {
        return;
    }
    char *buffer = (char *) malloc(envelope.message.body.len * sizeof(char));
    if(buffer == NULL)
    {
        SV_ERROR("malloc error");
        return;
    }
    memcpy(buffer, envelope.message.body.bytes, envelope.message.body.len);
	
    SV_LOG("r: %s", buffer);
    message = buffer;
	free(buffer);
}

void AmqpMessage::__StartConsume()
{
    string message;
    
    SV_LOG("start consume");
    while(1)
    {
        message = "";
        ReceiveMessage(message);
        sleep(1);
    }
}



