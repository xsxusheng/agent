#ifndef _HOSTDISKSTATUSINFO_H_
#define _HOSTDISKSTATUSINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../utils/ProtoBufPacker.h"
#include "../utils/base64.h"
using namespace com::fiberhome::fums::proto;

class HostDiskStatusInfo
{
public:
	static void SendDiskStatusInfo(RealQueryHostStatusData &data, Header::DataType type);
	static RealDiskStatusInfo GetDiskStatusInfo();
};

#endif
