#ifdef _APPCONTROL_H_
#define _APPCONTROL_H_
#include <iostream>
#include <string>
using namespace std;

class AppControl
{
	string m_appType;
	string m_status;
public:
	AppControl(){}
	~AppControl(){}
	inline string GetAppType()
	{
		return m_appType;
	}

	inline void SetAppType(string &appType)
	{
		m_appType = appType;
	}

	inline string GetStatus()
	{
		return m_status;
	}

	inline void SetStatus(string &status)
	{
		m_status = status;
	}
};

#endif
