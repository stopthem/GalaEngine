#pragma once
#include <string>
#include <vector>

namespace gala
{
    class StringUtilities
    {
    public:
        static std::vector<std::string> Split(const std::string& str, const std::string& delim);
    };
}

