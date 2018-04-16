/*************************************************************************
* File Name : TaskManager.cpp
* Author : xus103
* Created Time : 2018年03月01日
* Description : task manager, 
		every MQ message is regarded as a task, and a task is executed by one thread.
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "TaskManager.h"
#include "../utils/base64.h"
#include "../utils/sv_log.h"
#include "../utils/AgentUtils.h"
#include "../utils/ProtoBufPacker.h"
#include "AmqpMessageReceiveProcessor.h"
#include "AmqpMessageSendProcessor.h"


TaskManager* TaskManager::sm_taskManager = NULL;
Locker TaskManager::sm_lock;

TaskManager::TaskManager()
{
}

/* 需要将任务任务释放 */
TaskManager::~TaskManager()
{
	sm_lock.lock();
	for (vector<Task*>::const_iterator iter = m_task.begin(); iter != m_task.end(); iter++)
    	{
        	if(*iter != NULL)
        	{
			SV_LOG("delet task %d", (*iter)->GetState());
			delete *iter;
		}
	}
	m_task.clear();
	sm_lock.lock();
}

/*
 * 获取消息任务处理的单实例
 */
TaskManager* TaskManager::GetInstance()
{
    if(sm_taskManager == NULL)
    {
        sm_lock.lock();
        if(sm_taskManager == NULL)
        {
            sm_taskManager = new (std::nothrow) TaskManager();
        }
        sm_lock.unlock();
    }

    return sm_taskManager;
}


/* 判断任务是否为满，即达到该任务类型所能被处理的最大限制数 */
bool TaskManager::TaskIsFullByType(Header::DataType type)
{
	int count = 0;
	bool full = false;

	sm_lock.lock();
	for (vector<Task*>::const_iterator iter = m_task.begin(); iter != m_task.end(); iter++)
    	{
		if((*iter)->GetTaskType() == type)
		{
			//SV_LOG("status = %d   %d", (*iter)->GetState(), (*iter)->GetTaskThreadId());
			count++;
		}
	 
	}
	
	//SV_LOG("count %d---", count);
	switch(type)
	{
		case Header::CTRL_APP:
			full = count >= CTRL_APP_TASK_COUNT_LIMIT ? true : false;
			break;
		case Header::CONFIG:
			full = count >= CONFIG_TASK_COUNT_LIMIT ? true :false;
			break;
		case Header::SOFTWARE:
			SV_LOG("limit %d---", SOFTWARE_TASK_COUNT_LIMIT);
			full = count >= SOFTWARE_TASK_COUNT_LIMIT ? true : false;
			break;
		case Header::REALQUERYHOSTCFG:
			SV_LOG("limit %d---", REALQUERY_TASK_COUNT_LIMIT);
			full = count >= REALQUERY_TASK_COUNT_LIMIT ? true :false;
			break;
		default:
			SV_ERROR("unknown type");
	}

	sm_lock.unlock();
	
	return full;
}

bool TaskManager::TaskIsFull()
{
	bool full = false;
	
	sm_lock.lock();
	full = m_task.size() >= ALL_TASK_COUNT_LIMIT ? true : false;
	sm_lock.unlock();

	return full;	
}



Task* TaskManager::BuildCtrlAppTask(const string &message, const string &body, Header::DataType type)
{
	Task* task = NULL;
	bool full = false;

	if(message.empty() || body.empty())
	{
		return NULL;
	}

	/* 超出agent任务允许的处理任务数需要返回响应给fums */
	full = TaskIsFullByType(type); 
	if(full)
	{
		CtrlAppRstResponse ctrlResponse;
		ctrlResponse.set_uniqueid(AgentUtils::GetCurrentTimeMsec());
		ctrlResponse.mutable_res();

		CtrlAppData ctrlAppData;
		ctrlAppData.ParseFromString(base64_decode(body));
		
		CommonResponse response = ctrlResponse.res();
		response.set_responsecode(-1);
		response.set_responsemsg("task busy");
		response.set_status(CommonResponse::FAILED);
		
		string data = ProtoBufPacker::SerializeToArray<CtrlAppRstResponse>(ctrlResponse);
		Major major = ProtoBufPacker::PackResponseData(data,  Header::CTRL_APP, ctrlAppData.uniqueid());
		AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
		SV_WARN("app ctrl task too mutch");
		return NULL;
	}

	/* 新建一个任务 */
	task =  new (std::nothrow) Task();
	if(task == NULL)
	{
		SV_ERROR("new error");
		return NULL;
	}

	task->SetTaskType(type);
	task->SetMessage(message);
	task->SetMSecTimeout(60000);
	task->SetState(Task::TASK_IDLE);
	task->SetStartTime();

	return task;
}
	
	
Task* TaskManager::BuildConfigTask(const string &message, const string &body, Header::DataType type)
{
	Task* task = NULL;
	bool full = false;

	if(message.empty() || body.empty())
	{
		return NULL;
	}
	
	full = TaskIsFullByType(type); 
	if(full)
	{
		//todo 返回响应给fums
		SV_WARN("config task too mutch");
		return NULL;
	}
	
	/* 新建一个任务 */
	task =  new (std::nothrow) Task();
	if(task == NULL)
	{
		SV_ERROR("new error");
		return NULL;
	}

	task->SetTaskType(type);
	task->SetMessage(message);
	task->SetMSecTimeout(60000);
	task->SetState(Task::TASK_IDLE);
	task->SetStartTime();

	return task;
}

Task* TaskManager::BuildSoftWareTask(const string &message, const string &body, Header::DataType type)
{
	Task* task = NULL;
	bool full = false;

	if(message.empty() || body.empty())
	{
		return NULL;
	}
	
	full = TaskIsFullByType(type); 
	if(full)
	{
		//todo 返回响应给fums
		SV_WARN("software upgrade task too mutch");
		return NULL;
	}

	/* 新建一个任务 */
	task =  new (std::nothrow) Task();
	if(task == NULL)
	{
		SV_ERROR("new error");
		return NULL;
	}

	task->SetTaskType(type);
	task->SetMessage(message);
	task->SetMSecTimeout(180000);
	task->SetState(Task::TASK_IDLE);
	task->SetStartTime();

	return task;
}

Task* TaskManager::BuildRealQueryTask(const string &message, const string &body, Header::DataType type)
{
	Task* task = NULL;
	bool full = false;

	if(message.empty() || body.empty())
	{
		return NULL;
	}
	
	full = TaskIsFullByType(type); 
	if(full)
	{
		//todo 返回响应给fums
		SV_WARN("real query task too mutch");
		return NULL;
	}
	
	/* 新建一个任务 */
	task =  new (std::nothrow) Task();
	if(task == NULL)
	{
		SV_ERROR("new error");
		return NULL;
	}

	task->SetTaskType(type);
	task->SetMessage(message);
	task->SetMSecTimeout(60000);
	task->SetState(Task::TASK_IDLE);
	task->SetStartTime();

	return task;
}



Task* TaskManager::BuildTask(const string &message)
{
	Task* task = NULL;
	
	if(message.empty())
	{
		SV_ERROR("parameter error");
		return NULL;
	}

	Major major;
	major.ParseFromString(base64_decode(message));
	if(!major.has_header())
	{
		SV_ERROR("parse message error");
		return NULL;
	}
	Header header = major.header();
	if(header.direction() != Header::FUMSTOAGEN)
	{		
		return NULL;
	}

	/* 根据任务类，构建任务对象 */
	Header::DataType type = header.type();
	switch(type)
	{
		case Header::CTRL_APP:
			task = BuildCtrlAppTask(message, major.body(), type);
			break;
		case Header::CONFIG:
			task = BuildConfigTask(message, major.body(), type);
			break;
		case Header::SOFTWARE:
			task = BuildSoftWareTask(message, major.body(), type);
			break;
		case Header::REALQUERYHOSTCFG:
			task = BuildRealQueryTask(message, major.body(), type);
			break;
		default:
			SV_ERROR("unknown type");
	}
	
	return task;
}


Task* TaskManager::GetTaskByThreadId(pthread_t id)
{
	Task* task = NULL;

	sm_lock.lock();
	for (vector<Task*>::const_reverse_iterator iter = m_task.rbegin(); iter != m_task.rend(); iter++)
    	{
		//SV_LOG("%d ---- %d", (*iter)->GetTaskThreadId(), id);
        	if((*iter)->GetTaskThreadId() == id)
        	{
			task = *iter;
			break;
		}
	}
	sm_lock.unlock();

	return task;
}


void TaskManager::CheckTask()
{
	sm_lock.lock();
	vector<Task*>::iterator iter = m_task.empty() ? m_task.end() : m_task.begin();
	while(iter != m_task.end())
    	{
		//SV_LOG("check %d", (*iter)->GetState());
		switch((*iter)->GetState())
		{
			case Task::TASK_IDLE:
			case Task::TASK_RUNNING:
				if((*iter)->IsTimeout())
				{
					continue;	
				}
				break;
			case Task::TASK_SUCCESS:
				SV_LOG("cost -------------------- %d", (*iter)->GetTaskCostMSecTime());
				delete *iter;
				iter = m_task.erase(iter);
				continue;
			case Task::TASK_FAILED:
				SV_ERROR("%s", (*iter)->GetErrMessage().c_str());
				delete *iter;
				iter = m_task.erase(iter);
				continue;
			case Task::TASK_TIMEOUT:
				SV_ERROR("timeout : %s", (*iter)->GetErrMessage().c_str());
				delete *iter;
				iter = m_task.erase(iter);
				continue;
			default:
				SV_ERROR("unkonw type");
				delete *iter;
				iter = m_task.erase(iter);
				continue;
		
		}
		iter++;	
	}
	sm_lock.unlock();
}




void TaskManager::MessageProcess(const string &message)
{
	if(message.empty())
	{
		return;
	}
	
	Task* task = BuildTask(message);
	if(task == NULL)
	{
		return;
	}
	SV_LOG("MessageProcess");
	/* 新建线程处理任务 */
	AmqpMessageReceiveProcessor* processor = new (std::nothrow) AmqpMessageReceiveProcessor();
	task->SetProcessor(processor);
	processor->Start();
	task->SetTaskThreadId(processor->GetThreadId());
	m_task.push_back(task);
}





