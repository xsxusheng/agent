/*************************************************************************
	> File Name: amqp_receive_msg.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月02日 星期五 20时04分23秒
 ************************************************************************/

#ifndef _AMQP_RECEIVE_MSG_H
#define _AMQP_RECEIVE_MSG_H
#endif

#include <string>
using namespace std;


int receive_message(string &hostname, int port, string &queuename, string &exchange, string &routingkey);
