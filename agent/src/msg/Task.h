/*************************************************************************
* File Name : Task.h
* Author : xus103
* Created Time : 2018年03月27日
* Description : task object
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#ifndef _TASK_H_
#define _TASK_H_

#include <iostream>
#include <string>
#include <memory>
#include <pthread.h>
#include "Locker.h"
#include "../proto/Msg.pb.h"
#include "../proto/CtrlApp.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../proto/SoftwareInstall.pb.h"
#include "../proto/Config.pb.h"
#include "../utils/TimeUtils.h"
#include "AmqpMessageReceiveProcessor.h"
using namespace com::fiberhome::fums::proto;
using namespace std;

class Task
{
public:
	Task();
	Task(const string &message);
	~Task();
	enum State{
		TASK_IDLE = 0,
		TASK_RUNNING = 1,
		TASK_SUCCESS = 2,
		TASK_FAILED = 3,
		TASK_TIMEOUT = 4
	};
	/* 设置任务类型 */
	void SetTaskType(Header::DataType type);
	
	/* 获取任务类型*/
	Header::DataType GetTaskType();
	
	/* 设置任务处理的开始时间 */
	void SetStartTime();
	
	/* 判断任务是否处理超时 */
	bool IsTimeout();
	
	/* 获取当前任务所消耗的时间 */
	long GetTaskCostMSecTime();
	
	/* 设置任务超时时间， 单位秒 */
	void SetMSecTimeout(long duration);
	
	/* 设置任务状态 */
	void SetState(State state);
	
	/* 判断任务是否执行成功        */ 
	int GetState();
	
	/* 设置error原因 */
	void SetErrMessage(string &meessage);
	void SetErrMessage(string meessage);
	
	/* 获取error原因 */
	string GetErrMessage();
	
	/* 设置mq message */
	void SetMessage(const string &message);
	
	/* 获取mq message */
	string GetMessage();

	/* 设置线程ID */
	void SetTaskThreadId(pthread_t id);

	/* 获取线程ID */
	pthread_t GetTaskThreadId();

	/* 设置处理器 */
	void SetProcessor(AmqpMessageReceiveProcessor* processor);
	
	/* 获取处理器 */
	AmqpMessageReceiveProcessor* GetProcessor();

private:
	/* 任务类型 */
	Header::DataType m_taskType;
	/* 启动时间 */
	CTime m_startTime;
	/* 超时时间 */
	long m_mSecTimeout;
	/* 任务任务状态 */
	int m_state;
	/* 错误消息 */
	string m_errMessage;
	/* mq message */
	string m_message;
	/* 执行该任务的线程ID */
	pthread_t m_taskThreadId;
	//
	Locker m_locker;
	/* 处理器 */
	AmqpMessageReceiveProcessor* m_processor;
};

#endif

