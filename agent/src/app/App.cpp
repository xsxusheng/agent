/*************************************************************************
* File Name : App.cpp
* Author : xus103
* Created Time : 2018年03月13日
* Description : app operation
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "App.h"

App::App(){
	m_appVersion = "unknown";
	m_appStatus = STOPED;
	m_appTryInstallingVersion = "unknown";
	m_appTryInstallingStatus = INSTALLED_FAILED;
	m_appTryInstallingFailedReason = "unknown";
	m_isMayStart = false;
	m_startCount = 0;
	m_appDaemonStatus = STOPED;
};
App::App(string &appType, string &appVersion, int appStatus, string &appTryInstallingVersion,
                int &appTryInstallingStatus, string appTryInstallingFailedReason)
{
	m_appType                      = appType;
	m_appVersion                   = appVersion;
	m_appStatus                    = appStatus;
	m_appTryInstallingVersion      = appTryInstallingVersion;
	m_appTryInstallingStatus       = appTryInstallingStatus;
	m_appTryInstallingFailedReason = appTryInstallingFailedReason;
	m_isMayStart = false;
        m_startCount = 0;
	m_appDaemonStatus = STOPED;
}

App::~App(){};

string App::GetAppType()
{
	m_appLock.Lock();
	string appType = m_appType;
	m_appLock.UnLock();
	return appType;
}

void App::SetAppType(string &appType)
{
	m_appLock.Lock();
        m_appType = appType;
	m_appLock.UnLock();
}

string App::GetAppVersion()
{
	m_appLock.Lock();
	string appVersion = m_appVersion;
	m_appLock.UnLock();
	return appVersion;
}

void App::SetAppVersion(string &appVersion)
{
	m_appLock.Lock();
	m_appVersion = appVersion;
	m_appLock.UnLock();
}

int App::GetAppStatus()
{
	m_appLock.Lock();
	int appStatus = m_appStatus;
	m_appLock.UnLock();
	return appStatus;
}

void App::SetAppStatus(int appStatus)
{
	m_appLock.Lock();
	m_appStatus = appStatus;
	m_appLock.UnLock();
}

string App::GetAppTryInstallingVersion()
{
	m_appLock.Lock();
	string appTryInstallingVersion = m_appTryInstallingVersion;
	m_appLock.UnLock();
	return appTryInstallingVersion;
}

void App::SetAppTryInstallingVersion(string appTryInstallingVersion)
{
	m_appLock.Lock();
	m_appTryInstallingVersion = appTryInstallingVersion;
	m_appLock.UnLock();
}

int App::GetAppTryInstallingStatus()
{
	m_appLock.Lock();
	int appTryInstallingStatus = m_appTryInstallingStatus;
	m_appLock.UnLock();
	return appTryInstallingStatus;
}

void App::SetAppTryInstallingStatus(int appTryInstallingStatus)
{
	m_appLock.Lock();
	m_appTryInstallingStatus = appTryInstallingStatus;
	m_appLock.UnLock();
}

string App::GetAppTryInstallingFailedReason()
{
	m_appLock.Lock();
	string appTryInstallingFailedReason = m_appTryInstallingFailedReason;
	m_appLock.UnLock();
	return appTryInstallingFailedReason;
}

void App::SetAppTryInstallingFailedReason(string appTryInstallingFailedReason)
{
	m_appLock.Lock();
	m_appTryInstallingFailedReason = appTryInstallingFailedReason;
	m_appLock.UnLock();
}

/* 设置是否启动即fums是否启动了app */
void App::SetIsStart(bool start)
{
	m_appLock.Lock();
	m_isMayStart = start;
	m_appLock.UnLock();
}

/* 获取app是否启动 */
bool App::GetIsStart()
{
	m_appLock.Lock();
	bool isMayStart = m_isMayStart;
	m_appLock.UnLock();
	return isMayStart;
}



int App::GetStartCount()
{
	m_appLock.Lock();
	int startCount = m_startCount;
	m_appLock.UnLock();
	return startCount;
}

void App::SetStartCount(int count)
{
	m_appLock.Lock();
	m_startCount = count;
	m_appLock.UnLock();
}

int App::GetAppDaemonStatus()
{
	m_appLock.Lock();
	int appDaemonStatus = m_appDaemonStatus;
	m_appLock.UnLock();
	return appDaemonStatus;
}

void App::SetAppDaemonStatus(int appDaemonStatus)
{
	m_appLock.Lock();
	m_appDaemonStatus = appDaemonStatus;
	m_appLock.UnLock();
}
/*
bool App::operator == (const App& app1, const App& app2)
{
	return app1.GetAppType().compare(app2.GetAppType()) == 0 ? true : false;
}
*/
























