/*************************************************************************
* File Name : TaskManager.h
* Author : xus103
* Created Time : 2018年03月28日
* Description : task object
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../proto/Msg.pb.h"
#include "../proto/CtrlApp.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../proto/SoftwareInstall.pb.h"
#include "../proto/Config.pb.h"
#include "Locker.h"
#include "Task.h"

using namespace com::fiberhome::fums::proto;
using namespace std;

class TaskManager
{
public:
	enum TaskLimit{
		/* 软件升级同时执行的最大任务数 */
		SOFTWARE_TASK_COUNT_LIMIT = 1,
		/* 实时查询同时执行的最大任务数 */
		REALQUERY_TASK_COUNT_LIMIT = 10,
		/* 配置下发同时执行的最大任务数 */
		CONFIG_TASK_COUNT_LIMIT = 20,
		/* APP控制同时执行的最大任务数 */
		CTRL_APP_TASK_COUNT_LIMIT = 5,
		/* 同时执行的最大总任务数 */
		ALL_TASK_COUNT_LIMIT = 20
	};	

	
	/* 获取任务管理单实例 */
	static TaskManager* GetInstance();
	void MessageProcess(const string &message);
	Task* BuildTask(const string &message);
	Task* BuildRealQueryTask(const string &message, const string &body, Header::DataType type);
	Task* BuildSoftWareTask(const string &message, const string &body, Header::DataType type);
	Task* BuildConfigTask(const string &message, const string &body, Header::DataType type);
	Task* BuildCtrlAppTask(const string &message, const string &body, Header::DataType type);
	/* 添加一个任务到任务管理容器 */
	int AddTask(Task *task);
	
	/* 删除一个任务 */
	void DeleteTask(Task *task);

	/* 检查任务 */
	void CheckTask();

	/* 判断某一类型任务是否到达允许执行的最大任务数 */
	bool TaskIsFullByType(Header::DataType type);

	/* 判断任务是否到达允许执行的最大任务数 */
	bool TaskIsFull();
	
	/* 获取线程要执行的任务 */
	Task* GetTaskByThreadId(pthread_t id);
	
private:
	/*当前正在执行的任务总数 */
	int m_allTaskCount;
	/* 当前正在执行的软件升级任务数 */
	int m_softwareTaskCount;
	/* 当前正在执行配置下发的任务数 */
	int m_configTaskCount;
	/* 当前正在执行APP控制任务总数 */
	int m_ctrlAppTaskCount;
	/* 当前正在执行实时查询的任务总数 */
	int m_realQueryTaskCount;
	vector<Task*> m_task;
	
private:
	TaskManager();
	~TaskManager();
	/* 任务管理实例 */
	static TaskManager* sm_taskManager;
	static Locker sm_lock;
};

#endif
