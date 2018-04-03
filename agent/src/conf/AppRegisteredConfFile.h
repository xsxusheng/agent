/*************************************************************************
* File Name : AppRegisteredConfFile.h
* Author : xus103
* Created Time : 2018年03月13日
* Description : app register process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#ifndef _APPREGISTEREDCONFFILE_H_
#define _APPREGISTEREDCONFFILE_H_
#include <iostream>
#include <string>
#include "../proto/Config.pb.h"
using namespace com::fiberhome::fums::proto;
using namespace std;

class AppRegisteredConfFile
{
public:
        AppRegisteredConfFile();
        ~AppRegisteredConfFile();
        int Init();
        string GetAppRegisteredConfFile(string &path);
        int Analyse(ConfigData &config, ConfigUpdateResponse &response);
};

#endif
