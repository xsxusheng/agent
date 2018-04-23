/*************************************************************************
* File Name : AppConfFile.h
* Author : xus103
* Created Time : 2018年03月13日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#ifndef _APPCONFFILE_H_
#define _APPCONFFILE_H_
#include <iostream>
#include <string>
#include "../proto/Config.pb.h"
using namespace com::fiberhome::fums::proto;
using namespace std;

class AppConfFile
{
public:
	AppConfFile();
	~AppConfFile();

	/* 初始化 */
	int Init();

	/* 获取APP配置文件 */
	string GetAppConfFile(string &path, string &similarFile);

	/* 删除过去配置文件 */
	void DeleteExpiredConfFile(string &path, string &newFileName, string &usingFileName);

	/* 分析处理配置 */
	int Analyse(ConfigData &config, ConfigUpdateResponse &response);

	/* 分析处理配置 */
	int DownloadFile(ConfigData &config, ConfigUpdateResponse &response);
};

#endif

