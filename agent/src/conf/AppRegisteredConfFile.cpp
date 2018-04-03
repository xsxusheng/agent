/*************************************************************************
* File Name : RegisteredAppConfFile.cpp
* Author : xus103
* Created Time : 2018年04月03日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include "../utils/sv_log.h"
#include "../utils/Common.h"
#include "../utils/AgentUtils.h"
#include "AppRegisteredConfFile.h"

AppRegisteredConfFile::AppRegisteredConfFile(){}
AppRegisteredConfFile::~AppRegisteredConfFile(){}

int AppRegisteredConfFile::Init()
{
        return 0;
}

string AppRegisteredConfFile::GetAppRegisteredConfFile(string &path)
{
        string head("agent_apps__");
        string tail(".xml");

        if(path.empty())
        {
                return "agent_apps.xml";
        }

        vector<string> files = Common::GetAllFiles(path);
        string alarmConfFile = Common::GetLatestFile(files, head, tail);
        if(!alarmConfFile.empty())
        {
                return alarmConfFile;
        }

        return "agent_apps.xml";
}

int AppRegisteredConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
        /* 文件保存路径 */
        string fileSavePath = config.filesavepath();
        /* 下发的新的配置文件 */
        string newFileName = config.configfilename();
        /* 当前正在使用的配置文件 */
        string usingFileName = GetAppRegisteredConfFile(fileSavePath);

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
        if(Common::DeleteFile(usingFileNameWithPath))
        {
                SV_WARN("delete file:%s error", usingFileName.c_str());
        }
        SV_LOG("%s", config.configfilecontent().c_str());
        SV_LOG("\n");

        return 0;
}
