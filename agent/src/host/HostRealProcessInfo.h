#ifndef _HOSTPROCESSINFO_H_
#define _HOSTPROCESSINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
using namespace com::fiberhome::fums::proto;

class HostProcessInfo
{
public:
	void SendSystemInfo(RealQueryHostStatusData &data, Header::DataType type);
	RealSystemInfo GetSystemInfo();
};

#endif
