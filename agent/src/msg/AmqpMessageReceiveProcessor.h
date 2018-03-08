/*************************************************************************
	> File Name: AmqpMessageReceiveProcessor.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 11时01分00秒
 ************************************************************************/

#ifndef _AMQPMESSAGERECEIVEPROCESSOR_H_
#define _AMQPMESSAGERECEIVEPROCESSOR_H_
#include "../utils/Thread.h"
#include <string>

using namespace std;

class AmqpMessageReceiveProcessor : public Thread
{
public:
    AmqpMessageReceiveProcessor();
    ~AmqpMessageReceiveProcessor();
    int ReceiveFromFUMS(string message);

private:
    int MessageProcess();
    int MessageDispatcher();
    int ProcessCommand();
    int ProcessRealQuery();
    int ProcessConfig();
    int ProcessSoftwareInstall();
    void Run();

};
#endif
