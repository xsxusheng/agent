/*************************************************************************
* File Name : NtpConfFile.h
* Author : xus103
* Created Time : 2018年04月2日
* Description : config NTP
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include <iostream>
#include <string>
#include "../proto/Config.pb.h"
#include "../proto/CommonDefine.pb.h"
using namespace com::fiberhome::fums::proto;
using namespace std;


class NtpConfFile
{
public:
	NtpConfFile();
	~NtpConfFile();
	
	int Init();
	string GetNtpConfFile(string &path);
	int Analyse(ConfigData &config, ConfigUpdateResponse &response);
	
		
};
