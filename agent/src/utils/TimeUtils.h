/**********************************************************
 * File: TimeUtils.h
 * Function: 
 *********************************************************/
#pragma once

#include <sys/time.h>
#include <string>

#include "MacroDefine.h"

using namespace std;



typedef enum {
    TIME_FMT_YYYYMMDDHHMMSS, /*yyyyMMddHHmmss*/
    TIME_FMT_YYYY_MM_DD_HH_MM_SS, /*yyyy-MM-dd HH:mm:ss*/
    TIME_FMT_YYYYMMDD, /*yyyyMMdd*/
    TIME_FMT_YYYY_MM_DD, /*yyyy-MM-dd*/
}ETIME_FMT_TYPE;




class CTime
{
public:
	CTime();
	~CTime();
    
	/** 以时间戳构造 */
	CTime(long stamp);


    /*重新获取时间*/
    int GetTimeNow();
    long GetTimeSec(){return _tv.tv_sec;}
    long GetTimeUsec(){return _tv.tv_usec;}



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

    static void GetTimeNowStr(string& timeNow);
    static string GetCurTimeStr(ETIME_FMT_TYPE type = TIME_FMT_YYYY_MM_DD_HH_MM_SS);


private:
	struct timeval _tv;
};



