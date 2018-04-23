#ifndef _HOSTNICSTATUSINFO_H_
#define _HOSTNICSTATUSINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../utils/ProtoBufPacker.h"
#include "../utils/base64.h"
using namespace com::fiberhome::fums::proto;

class HostNicStatusInfo
{
public:
	static void SendNicStatusInfo(RealQueryHostStatusData &data, Header::DataType type);
	static RealNicStatusInfo GetNicStatusInfo();
};

#endif
