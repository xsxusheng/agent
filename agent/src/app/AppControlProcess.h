/*************************************************************************
* File Name : AppControlProcess.h
* Author : xus103
* Created Time : 2018年03月13日
* Description : app cmd process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/


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
