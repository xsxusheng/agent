#include "Thread.h"
#include <iostream>
using namespace std;


Thread::Thread() : m_autoDelete(true)//构造函数
{
	//SV_LOG("Thread ...");
}

Thread::~Thread() //析构函数
{
	//SV_LOG("~Thread ...");
}

void Thread::Start()//启动线程
{
	pthread_create(&m_threadId, NULL, __ThreadRoutine, this);
	//第三个参数这里并不能直接放上执行函数run
	//因为run函数式普通的成员函数，隐含的第一个参数是Thread*(就是this)
	//调用的时候是thiscall约定，也就是说他不能做为入口函数
}

void Thread::Join() //等待线程执行结束并且收回被等待线程的资源
{
	pthread_join(m_threadId, NULL);
}

void* Thread::__ThreadRoutine(void* arg)//
{
	Thread* thread = static_cast<Thread*>(arg);//派生类指针转换成基类指针
	thread->__DoRun();
	if (thread->m_autoDelete)
		delete thread;
	exit(1);
	return NULL;
}

void Thread::SetAutoDelete(bool autoDelete)
{
	m_autoDelete = autoDelete;
}
