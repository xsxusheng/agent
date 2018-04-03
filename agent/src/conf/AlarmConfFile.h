#ifndef _ALARMCONFFILE_H_
#define _ALARMCONFFILE_H_
#include <iostream>
#include <string>
#include "../proto/Msg.pb.h"
#include "../proto/Config.pb.h"
using namespace com::fiberhome::fums::proto;
using namespace std;

class AlarmConfFile
{
public:
	AlarmConfFile();
	~AlarmConfFile();
	
	int Init();
	string GetAlarmConfFile(string &path);
	int Analyse(ConfigData &config, ConfigUpdateResponse &response);
};

#endif
