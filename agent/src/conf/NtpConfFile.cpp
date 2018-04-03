/*************************************************************************
* File Name : NtpConfFile.cpp
* Author : xus103
* Created Time : 2018年04月2日
* Description : config NTP
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include "../utils/sv_log.h"
#include "../utils/Common.h"
#include "../utils/AgentUtils.h"
#include "NtpConfFile.h"



NtpConfFile::NtpConfFile()
{

}

NtpConfFile::~NtpConfFile()
{

}



int NtpConfFile::Init()
{
	return 0;
}
string NtpConfFile::GetNtpConfFile(string &path)
{
	string head("agent_ntp_");
	string tail(".xml");
	
	if(path.empty())
	{
		return "agent_ntp.xml";
	}
	vector<string> files = Common::GetAllFiles(path);
	string agentNtpConfFile = Common::GetLatestFile(files, head, tail);
	if(!agentNtpConfFile.empty())
	{
		return agentNtpConfFile;
	}

	return "agent_ntp.xml";
}

int NtpConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
	/* 文件保存路径 */
	string fileSavePath = config.filesavepath();
	/* 下发的新的配置文件 */
	string newFileName = config.configfilename();
	/* 当前正在使用的配置文件 */
	string usingFileName = GetNtpConfFile(fileSavePath);

	if(!newFileName.compare(usingFileName))
	{
		string errMsg = "the same file name, newFileName:" + newFileName + ", usingFileName:" + usingFileName;
		SV_ERROR("%s", errMsg.c_str());
		response.set_status(CommonResponse::FAILED);
		response.set_reason(errMsg);
		return -1;
	}

	string content = config.configfilecontent();
	string fileNameWithPath = Common::GetAbsolutePathFileName(fileSavePath, newFileName);
	if(!Common::SaveToFile(fileNameWithPath, content))
	{
		string errMsg = "fail to save file";
        	SV_ERROR("%s", errMsg.c_str());
       		response.set_status(CommonResponse::FAILED);
        	response.set_reason(errMsg);
        	return -1;
	}
	string usingFileNameWithPath = Common::GetAbsolutePathFileName(fileSavePath, usingFileName);
	cout<<usingFileNameWithPath<<endl;
	if(Common::DeleteFile(usingFileNameWithPath))
	{
		SV_WARN("delete file:%s error", usingFileName.c_str());
	}
	
	SV_LOG("%s", newFileName.c_str());
	SV_LOG("%s", config.configfilecontent().c_str());
	SV_LOG("\n");
	return 0;
}

