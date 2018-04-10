/*************************************************************************
* File Name : AgentConfFile.h
* Author : xus103
* Created Time : 2018年03月13日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#ifndef _AGENTCONFFILE_H_
#define _AGENTCONFFILE_H_
#include <iostream>
#include <string>
#include "../proto/Config.pb.h"
#include "../proto/CommonDefine.pb.h"
using namespace com::fiberhome::fums::proto;
using namespace std;


class AgentConfFile
{
public:
	AgentConfFile();
	~AgentConfFile();
	
	int Init();
	string GetAgentConfFile(string &path);
	int Analyse(ConfigData &config, ConfigUpdateResponse &response);
	
		
};

#endif
