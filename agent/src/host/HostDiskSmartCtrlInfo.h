#ifndef _HOSTDISKSMARTCTRLINFO_H_
#define _HOSTDISKSMARTCTRLINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
using namespace com::fiberhome::fums::proto;

class HostDiskSmartCtrlInfo
{
public:
	void SendSystemInfo(RealQueryHostStatusData &data, Header::DataType type);
	RealSystemInfo GetSystemInfo();
};

#endif
