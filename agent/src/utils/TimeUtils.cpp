/**********************************************************
 * File: TimeUtils.cpp
 * Function: 
 *********************************************************/
#include "TimeUtils.h"

#include <sys/time.h>





CTime::CTime()
{
    gettimeofday(&_tv, NULL);
}


CTime::CTime(time_t time)
{
    _tv.tv_sec = time;
    _tv.tv_usec = 0;
}


CTime::~CTime()
{
}


int CTime::GetTimeNow()
{
    return gettimeofday(&_tv, NULL);
}



long CTime::DiffSec(const CTime& time)
{
    long diff = 0;

    diff = _tv.tv_sec - time._tv.tv_sec;
    if (time._tv.tv_usec > _tv.tv_usec)
    {
        diff -= 1;
    }

    return diff;
}


long CTime::DiffMSec(const CTime& time)
{
    long diff = 0;
    diff = (_tv.tv_sec - time._tv.tv_sec) * 1000;
    if (_tv.tv_usec < time._tv.tv_usec)
    {
        diff += (1000 + _tv.tv_usec - time._tv.tv_usec) / 1000 - 1;
    }
    else
    {
        diff += (_tv.tv_usec - time._tv.tv_usec) / 1000;
    }
    return diff;
}


long CTime::DiffUSec(const CTime& time)
{
    long diff = 0;
    diff = (_tv.tv_sec - time._tv.tv_sec) * 1000000 + (_tv.tv_usec - time._tv.tv_usec);
    return diff;
}



CTime& CTime::operator = (const CTime& time)
{
    return *this;
}


CTime& CTime::operator + (const CTime& time)
{
    return *this;
}


CTime& CTime::operator - (const CTime& time)
{
    return *this;
}


CTime& CTime::operator += (const CTime& time)
{
    return *this;
}


CTime& CTime::operator -= (const CTime& time)
{
    return *this;
}


bool CTime::operator < (const CTime& time)
{
	if (_tv.tv_sec != time._tv.tv_sec)
	{
		return _tv.tv_sec < time._tv.tv_sec;
	}

	return _tv.tv_usec < time._tv.tv_usec;
}


bool CTime::operator > (const CTime& time)
{
	if (_tv.tv_sec != time._tv.tv_sec)
	{
		return _tv.tv_sec > time._tv.tv_sec;
	}

	return _tv.tv_usec > time._tv.tv_usec;
}


bool CTime::operator == (const CTime& time)
{
    return (_tv.tv_sec == time._tv.tv_sec) && (_tv.tv_usec == time._tv.tv_usec);
}





void CTime::secSleep(int sec)
{
    struct timeval	tv;
    tv.tv_sec = sec;
    tv.tv_usec = 0;
    select(0, NULL, NULL, NULL, &tv);
}


void CTime::msecSleep(int msec)
{
    struct timeval	tv;
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}


void CTime::usecSleep(int usec)
{
    struct timeval	tv;
    tv.tv_sec = usec / 1000000;
    tv.tv_usec = usec % 1000000;
    select(0, NULL, NULL, NULL, &tv);
}














