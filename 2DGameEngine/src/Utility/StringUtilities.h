#pragma once
#include <string>
#include <vector>

class StringUtilities
{
public:
	static std::vector<std::string> Split(const std::string& str, const std::string& delim);
};

