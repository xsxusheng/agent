/*************************************************************************
	> File Name: ProtoBufPacker.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月05日 星期一 14时04分40秒
 ************************************************************************/

#ifndef _PROTOBUFPACKER_H
#define _PROTOBUFPACKER_H
#include <string>
#include "../proto/Msg.pb.h"
#include "../proto/App.pb.h"
#include "../proto/Perf.pb.h"
#include "../proto/Config.pb.h"
#include "../proto/Response.pb.h"
#include "../proto/CommonDefine.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../proto/AcsEvent.pb.h"
#include "../proto/Alarm.pb.h"
#include "../proto/CtrlApp.pb.h"
#include "../proto/Event.pb.h"
#include "../proto/HaSwitch.pb.h"
#include "../proto/HostConfig.pb.h"
#include "../proto/SoftwareInstall.pb.h"
#include "../proto/StbInspect.pb.h"
#include <google/protobuf/stubs/common.h>
using namespace com::fiberhome::fums::proto;
using namespace std;
class ProtoBufPacker
{
public:
    static Major PackMsgMajor(string &body, Header::DataType type, Header::DIRECTION direction);
    static Major PackResponseData(string body, Header::DataType type, ::google::protobuf::int64 uniqueId);
    static Major PackPerfEntity(string data, PerfData::PERFDATATYPE type);
    static Major PackHeartBeatData(string data);
    static Major PackAppEntity(string body);
    static Major PackAlarmEntity(string body);
    static Major PackEventEntity(string body);
    static Major PackAcsEventEntity(string body);
    static Major PackStbInspectEntity(string body);

    static string PrintPerf(string &body);
    static string PrintCfgStr(RealQueryHostStatusData::HostCfgTypeEnum type, string data);
    static string PrintResponse(string &body);
    static void ProtoToString(Major major);
    template <typename T>
    static string SerializeToArray(T t);
};

template <typename T>
string ProtoBufPacker::SerializeToArray(T t)
{
        int size = t.ByteSizeLong();
        if(size < 1)
        {
                return "";
        }

        char data[size + 1];
        memset(data, 0, size +1);
        t.SerializeToArray((void *)data, size);
        string message(data);

        return message;
}

#endif
