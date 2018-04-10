
#include "../utils/sv_log.h"
#include "Task.h"

Task::Task()
{
	m_processor = NULL;
}

Task::Task(const string &message)
{
	m_processor = NULL;
	m_message = message;
}


Task::~Task()
{
	//SV_LOG("~Task");
}

void Task::SetTaskType(Header::DataType type)
{
	m_taskType = type;
}

Header::DataType Task::GetTaskType()
{
	return m_taskType;
}

void Task::SetStartTime()
{
	m_startTime.GetTimeNow();
}

long Task::GetTaskCostMSecTime()
{
	CTime timeNow;
	long diff = m_startTime.DiffMSec(timeNow);
	return diff;
}

bool Task::IsTimeout()
{
	long costTime = -GetTaskCostMSecTime();
	//SV_LOG("cost %ld, timeout %ld", costTime, m_mSecTimeout);
	if(costTime <= m_mSecTimeout)
	{
		return false;
	}
	SetState(TASK_TIMEOUT);
	//SV_LOG("status %d,   %d", GetState(), TASK_TIMEOUT);

	return true;
}


void Task::SetMSecTimeout(long timeout)
{
	m_mSecTimeout = timeout;
}

void Task::SetState(State state)
{
	m_locker.lock();
	m_state = state;
	m_locker.unlock();
}

int Task::GetState()
{
	m_locker.lock();
	int state = m_state;
	m_locker.unlock();
	return state;
}

void Task::SetErrMessage(string &message)
{
	m_errMessage = message;
}

void Task::SetErrMessage(string message)
{
	m_errMessage = message;
}

string Task::GetErrMessage()
{
	return m_errMessage;
}

void Task::SetMessage(const string &message)
{
	m_message = message;
}

string Task::GetMessage()
{
	return m_message;
}

void Task::SetTaskThreadId(pthread_t id)
{
	m_taskThreadId = id;
}

pthread_t Task::GetTaskThreadId()
{
	return m_taskThreadId;
}

void Task::SetProcessor(AmqpMessageReceiveProcessor* processor)
{
	m_processor = processor;
}

AmqpMessageReceiveProcessor* Task::GetProcessor()
{
	return m_processor;
}
