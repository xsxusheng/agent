#ifndef _HOSTDISKSMARTCTRLINFO_H_
#define _HOSTDISKSMARTCTRLINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../utils/ProtoBufPacker.h"
#include "../utils/base64.h"
using namespace com::fiberhome::fums::proto;

class HostDiskSmartCtrlInfo
{
public:
	static void SendDiskSmartCtlInfo(RealQueryHostStatusData &data, Header::DataType type);
	static RealDiskHealthInfo GetDiskHealthInfo();
};

#endif
