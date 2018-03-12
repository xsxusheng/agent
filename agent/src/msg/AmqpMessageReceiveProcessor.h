/*************************************************************************
* File Name : AmqpMessageReceiveProcessor.h
* Author : xus103
* Created Time : 2018年03月01日
* Description : rabbitmq message proccess function
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#ifndef _AMQPMESSAGERECEIVEPROCESSOR_H_
#define _AMQPMESSAGERECEIVEPROCESSOR_H_
#include "../utils/Thread.h"
#include "../proto/Msg.pb.h"
#include "../proto/CtrlApp.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../proto/SoftwareInstall.pb.h"
#include "../proto/Config.pb.h"
#include <string>
using namespace com::fiberhome::fums::proto;
using namespace std;

class AmqpMessageReceiveProcessor : public Thread
{
public:
    AmqpMessageReceiveProcessor(string message);
    ~AmqpMessageReceiveProcessor();
    int ReceiveFromFUMS(string message);
	int MessageProcess();
    int MessageDispatcher(Header::DataType type, const string &body);
    int ProcessCommand(const string &body);
    int ProcessRealQuery(const string &body);
    int ProcessConfig(const string &body);
    int ProcessSoftwareInstall(const string &body);

private:
    void __DoRun();

	int m_startTime;
	string m_message;

};
#endif
