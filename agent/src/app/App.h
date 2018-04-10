#ifndef _APP_H_
#define _APP_H_
#include <iostream>
#include <string>
using namespace std;

class App
{
public:
	App();
	App(string &appType, string &appVersion, int appStatus,
		string &appTryInstallingVersion, int &appTryInstallingStatus, string appTryInstallingFailedReason);
	~App();

	string GetAppType();
	void SetAppType(string &appType);
	string GetAppVersion();
	void SetAppVersion(string &appVersion);
	int GetAppStatus();
	void SetAppStatus(int appStatus);
	string GetAppTryInstallingVersion();
	void SetAppTryInstallingVersion(string &appTryInstallVersion);
	int GetAppTryInstallingStatus();
	void SetAppTryInstallingStatus(int appTryInstallingStatus);
	string GetAppTryInstallingFailedReason();
	void SetAppTryInstallingFailedReason(string &appTryInstallingFailedReason);
	bool isStart();
	int GetStartCount();
	void SetStartCount(int count);
	int GetAppDaemonStatus();
	void SetAppDaemonStatus(int appDaemonStatus);
	
	bool operator==(const App &app);

private:
	string m_appType;
	string m_appVersion;
	int m_appStatus;
	int m_appTryInstallingStatus;
	string m_appTryInstallingVersion;
	string m_appTryInstallingFailedReason;
	bool m_isMayStart;
	int m_startCount;
	int m_appDaemonStatus;
};

#endif
