#ifndef _HOSTREALPROCESSINFO_H_
#define _HOSTREALPROCESSINFO_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/RealQueryHostStatus.pb.h"
#include "../utils/ProtoBufPacker.h"
#include "../utils/base64.h"
using namespace com::fiberhome::fums::proto;

class HostRealProcessInfo
{
public:
	static void SendRealProcessInfo(RealQueryHostStatusData &data, Header::DataType type);
	static RealProcessStatusInfo GetRealProcessInfo();
};

#endif
