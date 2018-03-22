/*************************************************************************
* File Name : AppConfFile.cpp
* Author : xus103
* Created Time : 2018年03月13日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include "../utils/sv_log.h"
#include "AppConfFile.h"

AppConfFile::AppConfFile()
{

}

AppConfFile::~AppConfFile()
{

}

int AppConfFile::Init()
{
	return 0;
}

int AppConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
	SV_LOG("%s", config.configfilecontent().c_str());
	SV_LOG("\n");
	return 0;
}


