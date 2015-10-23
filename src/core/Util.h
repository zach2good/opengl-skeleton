#pragma once

#ifndef WIN32
#include <unistd.h>
#endif

#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_VALUE 0xFFFFFFFF

#include <vector>
#include <string>

namespace Util
{
	void Sleep(int milliseconds);
	std::vector<std::string> Split(const std::string &s, char delim);
};
