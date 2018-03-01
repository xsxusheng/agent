/*************************************************************************
	> File Name: base.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月22日 星期四 08时59分13秒
 ************************************************************************/

#ifndef _BASE_H
#define _BASE_H
#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
#endif
