#ifndef _HOSTDISKCFGINFO_H_
#define _HOSTDISKCFGINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../utils/ProtoBufPacker.h"
#include "../utils/base64.h"
using namespace com::fiberhome::fums::proto;

class HostDiskCfgInfo
{
public:
	static void SendDiskCfgInfo(RealQueryHostStatusData &data, Header::DataType type);
	static RealDiskCfgInfo GetDiskCfgInfo();
};

#endif
