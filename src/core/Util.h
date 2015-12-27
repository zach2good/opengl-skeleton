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

#include <iostream>
#include <fstream>

using namespace std;

namespace Util
{
	void Sleep(int milliseconds);
	bool FileExists(const std::string& name);
	std::string OpenFile(std::string input, bool newLine = true);
	std::vector<std::string> Split(const std::string &s, const std::string &delims);
};
