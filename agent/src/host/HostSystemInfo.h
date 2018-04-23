#ifndef _HOSTSYSTEMINFO_H_
#define _HOSTSYSTEMINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../utils/ProtoBufPacker.h"
#include "../utils/base64.h"
using namespace com::fiberhome::fums::proto;

class HostSystemInfo
{
public:
	static void SendSystemInfo(RealQueryHostStatusData &data, Header::DataType type);
	static RealSystemInfo GetSystemInfo();
};

#endif
