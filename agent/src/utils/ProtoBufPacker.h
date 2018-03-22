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
using namespace com::fiberhome::fums::proto;
using namespace std;
class ProtoBufPacker
{
public:
    static Major PackMsgMajor(string &body, Header::DataType type, Header::DIRECTION direction);
    static Major PackResponseData(string &body, Header::DataType type, long uniqueId);
    static Major PackPerfEntity(string data, PerfData::PERFDATATYPE type);
    static Major PackPerfEntity(string &data, PerfData::PERFDATATYPE type);
    static Major PackHeartBeatData(string data);
    static Major PackHeartBeatData(string &data);
    static Major PackAppEntity(string &body);
    static Major PackAlarmEntity(string &body);
    static Major PackEventEntity(string &body);
    static Major PackAcsEventEntity(string &body);
    static Major PackStbInspectEntity(string &body);
	
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
