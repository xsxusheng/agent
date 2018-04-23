#ifndef _HOSTDISKRAIDINFO_H_
#define _HOSTDISKRAIDINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../utils/ProtoBufPacker.h"
#include "../utils/base64.h"
using namespace com::fiberhome::fums::proto;

class HostDiskRaidInfo
{
public:
	static void SendDiskRaidInfo(RealQueryHostStatusData &data, Header::DataType type);
	static RealDiskRaidCfgInfo GetDiskRaidCfgInfo();
};

#endif
