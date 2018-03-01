/*************************************************************************
	> File Name: AmqpReceiveProcessor.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 11时01分00秒
 ************************************************************************/

#ifndef _AMQPRECEIVEPROCESSOR_H
#define _AMQPRECEIVEPROCESSOR_H
#include <string>
using namespace std;

class AmqpReceiveProcessor
{
    int ReceiveFromFUMS(string message);

private:
    int MessageProcess();
    int MessageDispatcher();
    int ProcessCommand();
    int ProcessRealQuery();
    int ProcessConfig();
    int ProcessSoftwareInstall();

};
#endif
