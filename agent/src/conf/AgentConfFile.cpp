/*************************************************************************
* File Name : AgentConfFile.cpp
* Author : xus103
* Created Time : 2018年03月13日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include "../utils/sv_log.h"
#include "../utils/Common.h"
#include "../utils/AgentUtils.h"
#include "ConfManager.h"
#include "AgentConfFile.h"



AgentConfFile::AgentConfFile()
{

}

AgentConfFile::~AgentConfFile()
{

}



int AgentConfFile::Init()
{
	return 0;
}
string AgentConfFile::GetAgentConfFile(string &path)
{
	string head("agent_conf_");
	string tail(".xml");
	
	if(path.empty())
	{
		return "agent_conf.xml";
	}

	vector<string> files = Common::GetAllFiles(path);
	string agentConfFile = Common::GetLatestFile(files, head, tail);
	if(!agentConfFile.empty())
	{
		return agentConfFile;
	}

	return "agent_conf.xml";
}

int AgentConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
	int ret = ConfManager::agentConfFileRWLock.TimeWrLock(20);
	if(0 == ret)
	{
		SV_ERROR("get lock error");
                return -1;
	}
	
	/* 文件保存路径 */
	string fileSavePath = config.filesavepath();
	/* 下发的新的配置文件 */
	string newFileName = config.configfilename();
	/* 当前正在使用的配置文件 */
	string usingFileName = GetAgentConfFile(fileSavePath);

	if(!newFileName.compare(usingFileName))
	{
		string errMsg = "the same file name, newFileName:" + newFileName + ", usingFileName:" + usingFileName;
		SV_ERROR("%s", errMsg.c_str());
		response.set_status(CommonResponse::FAILED);
		response.set_reason(errMsg);
		ConfManager::agentConfFileRWLock.UnLock();
		return -1;
	}

	string content = config.configfilecontent();
	string fileNameWithPath = Common::GetAbsolutePathFileName(fileSavePath, newFileName);
	SV_LOG("ppp %s", fileNameWithPath.c_str());
	if(!Common::SaveToFile(fileNameWithPath, content))
	{
		string errMsg = "fail to save file";
        	SV_ERROR("%s", errMsg.c_str());
        	response.set_status(CommonResponse::FAILED);
        	response.set_reason(errMsg);
		ConfManager::agentConfFileRWLock.UnLock();
        	return -1;
	}
	string etc("/opt/fonsview/NE/agent/");
	string usingFileNameWithPath = Common::GetAbsolutePathFileName(etc, usingFileName);
	if(Common::DeleteFile(usingFileNameWithPath))
	{
		SV_WARN("delete file:%s error", usingFileName.c_str());
	}
	
	ConfManager::agentConfFileRWLock.UnLock();
	return 0;
}

