/*************************************************************************
* File Name : RegisterAppTable.h
* Author : xus103
* Created Time : 2018年04月10日
* Description : app 注册表管理
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#ifndef _REGISTERAPPTABLE_H_
#define _REGISTERAPPTABLE_H_

#include <iostream>
#include <unordered_map>
#include <string>
#include "../proto/Msg.pb.h"
#include "../proto/App.pb.h"
#include "../msg/AmqpMessageSendProcessor.h"
#include "../utils/ProtoBufPacker.h"
#include "App.h"
using namespace com::fiberhome::fums::proto;
using namespace std;

class RegisterAppTable
{
public:
	RegisterAppTable(){}
	~RegisterAppTable(){}
	
	/* 获取APP注册表 */
	static unordered_map<string, App> GetAppTable();

	/* 注册一个APP */
	static void RegisterApp(App &app);

	/* 删除一个注册的App */
	static void DeleteRegisteredApp(App &app);

	/* 修改一个注册的App */
	static void ModifyRegisteredApp(App &app);

	/* 清除所有注册的APP记录 */
	static void ClearAllAppRecord();

	/* 判断注册表中是否有指定APP记录 */
	static bool AppExist(App &app);

	/* 根据APP及操作类型生成一个protobuf */
	static Major AppToProtoBuf(App &app, AppData::APP_OP_TYPE type);
	
private:

	static unordered_map<string, App> m_appTable;
};

#endif
