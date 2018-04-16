

#ifndef _APPCONTROLPROCESS_H_
#define _APPCONTROLPROCESS_H_
#include <iostream>
#include "../proto/Msg.pb.h"
#include "../proto/CtrlApp.pb.h"
#include "../proto/CommonDefine.pb.h"
using namespace com::fiberhome::fums::proto;


class AppControlProcess
{
public:
	AppControlProcess(){}
	~AppControlProcess(){}
	static int ControlProcess(CtrlAppData &ctrlApp);
};

#endif
