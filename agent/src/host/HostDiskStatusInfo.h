#ifndef _HOSTDISKSTATUSINFO_H_
#define _HOSTDISKSTATUSINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
using namespace com::fiberhome::fums::proto;

class HostDiskStatusInfo
{
public:
	void SendSystemInfo(RealQueryHostStatusData &data, Header::DataType type);
	RealSystemInfo GetSystemInfo();
};

#endif
