#include "util.h"
#include <SDL.h>

void Util::Sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
}

bool Util::FileExists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string Util::OpenFile(std::string input, bool newLine)
{
	string temp;
	string content;
	ifstream file(input);
	if (file.is_open())
	{
		while (getline(file, temp))
		{
			if (newLine)
				content += temp + "\n";
			else
				content += temp;
		}
		file.close();
	}

	else cout << "Unable to open file\n";

	return content;
}

std::vector<std::string> Util::Split(const std::string &s, const std::string &delims)
{
	std::vector<std::string> result;
	std::string::size_type pos = 0;
	while (std::string::npos != (pos = s.find_first_not_of(delims, pos))) {
		auto pos2 = s.find_first_of(delims, pos);
		result.emplace_back(s.substr(pos, std::string::npos == pos2 ? pos2 : pos2 - pos));
		pos = pos2;
	}
	return result;
}