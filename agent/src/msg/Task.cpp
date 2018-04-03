
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
	if(m_processor != NULL)
	{
		delete m_processor;
		m_processor = NULL;
	}
	SV_LOG("~Task");
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
	SV_LOG("cost %ld, timeout %ld", costTime, m_mSecTimeout);
	if(costTime <= m_mSecTimeout)
	{
		return false;
	}
	SetState(TASK_TIMEOUT);
	SV_LOG("status %d,   %d", GetState(), TASK_TIMEOUT);

	return true;
}


void Task::SetMSecTimeout(long timeout)
{
	m_mSecTimeout = timeout;
}

void Task::SetState(State state)
{
	m_state = state;
}

int Task::GetState()
{
	return m_state;
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
