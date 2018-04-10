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

inline int App::GetAppStatus()
{
	return m_appStatus;
}

inline void App::SetAppStatus(int appStatus)
{
	m_appStatus = appStatus;
}

string App::GetAppTryInstallingVersion()
{
	return m_appTryInstallingVersion;
}

void App::SetAppTryInstallingVersion(string &appTryInstallingVersion)
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

void App::SetAppTryInstallingFailedReason(string &appTryInstallingFailedReason)
{
	m_appTryInstallingFailedReason = appTryInstallingFailedReason;
}

bool App::isStart()
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

bool App::operator==(const App &app)
{
	return m_appType == app.m_appType ? true : false;
}





























