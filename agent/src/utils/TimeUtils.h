/**********************************************************
 * File: TimeUtils.h
 * Function: 
 *********************************************************/
#pragma once

#include <sys/time.h>

#include "MacroDefine.h"

using namespace std;






class CTime
{
public:
	CTime();
	~CTime();
    
	/** 以时间戳构造 */
	CTime(time_t stamp);


    /*重新获取时间*/
    int GetTimeNow();


	/** 比较两时间之间的差异 */
	long DiffSec(const CTime & time);

	/** 比较两时间之间的差异 */
	long DiffMSec(const CTime & time);

	/** 比较两时间之间的差异 */
	long DiffUSec(const CTime & time);

    CTime& operator = (const CTime& time);
	CTime& operator + (const CTime& time);
	CTime& operator - (const CTime& time);
	CTime& operator += (const CTime& time);
	CTime& operator -= (const CTime& time);
    
	bool operator < (const CTime& time);
	bool operator > (const CTime& time);
	bool operator == (const CTime& time);



    static void secSleep(int sec);
    static void msecSleep(int msec);
    static void usecSleep(int usec);


private:
	struct timeval _tv;
};


