/*************************************************************************
* File Name : AppConfFile.h
* Author : xus103
* Created Time : 2018年03月13日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
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
	int Init();
	string GetAppRegisteredConfFile(string &path);
	int Analyse(ConfigData &config, ConfigUpdateResponse &response);
	int DownloadFile(ConfigData &config, ConfigUpdateResponse &response);
};



