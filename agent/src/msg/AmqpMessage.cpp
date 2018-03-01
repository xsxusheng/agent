/*************************************************************************
	> File Name: AmqpMessage.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 16时38分53秒
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
    SV_LOG("构造函数 AmqpMessage");
}

AmqpMessage::~AmqpMessage()
{
    SV_LOG("析构函数 AmqpMessage");
}

int DieOnAmqpError(amqp_rpc_reply_t x, char const *context)
{
    switch (x.reply_type)
    {
        case AMQP_RESPONSE_NORMAL:
            return AMQP_RESPONSE_NORMAL;

        case AMQP_RESPONSE_NONE:
            fprintf(stderr, "%s: missing RPC reply type!\n", context);
            SV_ERROR("%s: missing RPC reply type!\n", context);
            break;

        case AMQP_RESPONSE_LIBRARY_EXCEPTION:
            fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
            SV_ERROR("%s: %s\n", context, amqp_error_string2(x.library_error));
        break;

        case AMQP_RESPONSE_SERVER_EXCEPTION:
            switch (x.reply.id)
            {
                case AMQP_CONNECTION_CLOSE_METHOD:
                {
                    amqp_connection_close_t *m = (amqp_connection_close_t *)x.reply.decoded;
                    fprintf(stderr, "%s: server connection error %uh, message: %.*s\n", context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                    SV_ERROR("%s: server connection error %uh, message: %.*s\n", context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                     break;
                            
                }
                case AMQP_CHANNEL_CLOSE_METHOD:
                {
                    amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
                    fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                    SV_ERROR("%s: server channel error %uh, message: %.*s\n",context, m->reply_code, (int)m->reply_text.len, (char *)m->reply_text.bytes);
                    return AMQP_CHANNEL_CLOSE_METHOD;  
                }
                default:
                    fprintf(stderr, "%s: unknown server error, method id 0x%08X\n", context, x.reply.id);
                    SV_ERROR("%s: unknown server error, method id 0x%08X\n", context, x.reply.id);
                    break;    
            }
            break;
    }

    return -1;
}



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
	SV_LOG("bind queue : queue = %s, exchange = %s, routing_key = %s", queuename.c_str(), exchange.c_str(), routingKey.c_str());

    amqp_queue_bind(m_conn, 1, amqp_cstring_bytes(queuename.c_str()), amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(routingKey.c_str()), amqp_empty_table);
    error = DieOnAmqpError(amqp_get_rpc_reply(m_conn), "bind queue");
    if(error != AMQP_RESPONSE_NORMAL)
    {
		SV_ERROR("queue bind error");
        throw -1;
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

void AmqpMessage::StartConsume()
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



