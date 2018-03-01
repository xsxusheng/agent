/*
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MIT
 *
 * Portions created by Alan Antonuk are Copyright (c) 2012-2013
 * Alan Antonuk. All Rights Reserved.
 *
 * Portions created by VMware are Copyright (c) 2007-2012 VMware, Inc.
 * All Rights Reserved.
 *
 * Portions created by Tony Garnock-Jones are Copyright (c) 2009-2010
 * VMware, Inc. and Tony Garnock-Jones. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ***** END LICENSE BLOCK *****
 */

#include <iostream>
#include <string>
#include "amqp_sendstring.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/layout.h>
#include <iomanip>
 
static log4cplus::BasicConfigurator config;
static log4cplus::Logger logger;
 
 
 
using namespace std;
#ifdef __cplusplus
extern "C" { 
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <amqp.h>
#include <amqp_tcp_socket.h>

int sendStr(const char *hostname, int port, const char *queue, const char *exchange, const char *routingkey, const char *messagebody) {

	amqp_socket_t *socket = NULL;
	amqp_connection_state_t conn;


	conn = amqp_new_connection();

	socket = amqp_tcp_socket_new(conn);
	if (!socket) {
		printf("creating TCP socket");
	}

	int status = amqp_socket_open(socket, hostname, port);
	if (status) {
		printf("opening TCP socket");
	}

	amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN,
                               "admin", "admin");
                    
	amqp_channel_open(conn, 1);
	amqp_get_rpc_reply(conn);

	{
		amqp_basic_properties_t props;
		props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
		props.content_type = amqp_cstring_bytes("text/plain");
		props.delivery_mode = 2; /* persistent delivery mode */
    LOG4CPLUS_INFO(logger, "hello send");
		amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange),
                                    amqp_cstring_bytes(routingkey), 0, 0,
                                    &props, amqp_cstring_bytes(messagebody));
    LOG4CPLUS_INFO(logger, "hello send");

	}

	amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
	amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
	amqp_destroy_connection(conn);
	return 0;
}

#ifdef __cplusplus
}
#endif

int send_message(string &hostname, int port, string &queue, string &exchange, string &routingkey, string &messagebody)
{
    config.configure();
    logger = log4cplus::Logger::getInstance("main");
    LOG4CPLUS_INFO(logger, "hello send");
	sendStr(hostname.c_str(), port, queue.c_str(), exchange.c_str(), routingkey.c_str(), messagebody.c_str());

    return 0;
}

/*int main()
{
	sendStr("172.16.17.118", 5672, "amq.direct", "test", "xusheng test");
	
	return 0;
}*/
