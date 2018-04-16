#include "App.h"

App::App(){};
App::App(string &appType, string &appVersion, int appStatus, string &appTryInstallingVersion,
                int &appTryInstallingStatus, string appTryInstallingFailedReason)
{
	m_appType                      = appType;
	m_appVersion                   = appVersion;
	m_appStatus                    = appStatus;
	m_appTryInstallingVersion      = appTryInstallingVersion;
	m_appTryInstallingStatus       = appTryInstallingStatus;
	m_appTryInstallingFailedReason = appTryInstallingFailedReason;
}

App::~App(){};

string App::GetAppType()
{
	return m_appType;
}

void App::SetAppType(string &appType)
{
        m_appType = appType;
}

string App::GetAppVersion()
{
	return m_appVersion;
}

void App::SetAppVersion(string &appVersion)
{
	m_appVersion = appVersion;
}

int App::GetAppStatus()
{
	return m_appStatus;
}

void App::SetAppStatus(int appStatus)
{
	m_appStatus = appStatus;
}

string App::GetAppTryInstallingVersion()
{
	return m_appTryInstallingVersion;
}

void App::SetAppTryInstallingVersion(string appTryInstallingVersion)
{
	m_appTryInstallingVersion = appTryInstallingVersion;
}

int App::GetAppTryInstallingStatus()
{
	return m_appTryInstallingStatus;
}

void App::SetAppTryInstallingStatus(int appTryInstallingStatus)
{
	m_appTryInstallingStatus = appTryInstallingStatus;
}

string App::GetAppTryInstallingFailedReason()
{
	return m_appTryInstallingFailedReason;
}

void App::SetAppTryInstallingFailedReason(string appTryInstallingFailedReason)
{
	m_appTryInstallingFailedReason = appTryInstallingFailedReason;
}

/* 设置是否启动即fums是否启动了app */
void App::SetIsStart(bool start)
{
	m_isMayStart = start;
}

/* 获取app是否启动 */
bool App::GetIsStart()
{
	return m_isMayStart;
}



int App::GetStartCount()
{
	return m_startCount;
}

void App::SetStartCount(int count)
{
	m_startCount = count;
}

int App::GetAppDaemonStatus()
{
	return m_startCount;
}

void App::SetAppDaemonStatus(int appDaemonStatus)
{
	m_appDaemonStatus = appDaemonStatus;
}
/*
bool App::operator == (const App& app1, const App& app2)
{
	return app1.GetAppType().compare(app2.GetAppType()) == 0 ? true : false;
}
*/
























