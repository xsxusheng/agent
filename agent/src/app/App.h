/*************************************************************************
* File Name : App.h
* Author : xus103
* Created Time : 2018年03月13日
* Description : App
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#ifndef _APP_H_
#define _APP_H_
#include <iostream>
#include <string>
#include "../utils/Lock.h"
using namespace std;

class App
{
public:
	/* APP 状态 */
	enum AppStatus{
		STARTED = 0, 						/* 启动 */
		STOPED  = 1  						/* 停止 */
	};
	enum AppTryInstallingStatus
	{
		INSTALLED_SUCCESS = 0,				/* 安装成功 */
		INSTALLED_FAILED  = 1,				/* 安装失败 */
		DOWNLOAD_SUCC_NOT_INSTALL = 2,		/* 下载成功但未安装 */
		DOWNLOAD_FAILED = 3					/* 下载失败 */
	};

	App();
	App(string &appType, string &appVersion, int appStatus,
		string &appTryInstallingVersion, int &appTryInstallingStatus, string appTryInstallingFailedReason);
	~App();

	/* 获取APP类型 */
	string GetAppType();

	/* 设置APP类型 */
	void SetAppType(string &appType);

	/* 获取APP版本 */
	string GetAppVersion();

	/* 设置APP版本 */	
	void SetAppVersion(string &appVersion);

	/* 获取APP状态 */
	int GetAppStatus();

	/* 设置APP状态 */
	void SetAppStatus(int appStatus);

	/* 获取APP尝试安装版本 */
	string GetAppTryInstallingVersion();

	/* 设置APP尝试安装版本 */
	void SetAppTryInstallingVersion(string appTryInstallVersion);

	/* 获取APP尝试安装状态 */
	int GetAppTryInstallingStatus();
	
	/* 设置APP尝试安装状态 */
	void SetAppTryInstallingStatus(int appTryInstallingStatus);

	/* 获取APP尝试安装失败原因 */
	string GetAppTryInstallingFailedReason();

	/* 设置APP尝试安装失败原因 */
	void SetAppTryInstallingFailedReason(string appTryInstallingFailedReason);

	/* 设置启动 */
	void SetIsStart(bool start);
	
	/* 获取是否启动 */
	bool GetIsStart();

	/* 获取启动数 */
	int GetStartCount();

	/* 设置启动数 */
	void SetStartCount(int count);

	/* 获取APP daemon 状态 */
	int GetAppDaemonStatus();

	/* 设置APP daemon 状态 */
	void SetAppDaemonStatus(int appDaemonStatus);

private:
	/* APP 类型 */
	string m_appType;
	/* APP 版本 */
	string m_appVersion;
	/* APP 状态 */
	int m_appStatus;
	/* APP 尝试安装状态 */
	int m_appTryInstallingStatus;
	/* APP 尝试安装版本 */
	string m_appTryInstallingVersion;
	/* APP 尝试安装失败原因 */
	string m_appTryInstallingFailedReason;
	/* APP 是否启动 */
	bool m_isMayStart;
	/* APP 启动次数 */
	int m_startCount;
	/* APP daemon 状态 */
	int m_appDaemonStatus;
	CMutex m_appLock;
};

#endif
