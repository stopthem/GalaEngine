#include "StringUtilities.h"
#include <vector>
#include <string>

namespace gala
{
    std::vector<std::string> StringUtilities::Split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos;
        do
        {
            pos = str.find(delim, prev);

            if (pos == std::string::npos) pos = str.length();

            std::string token = str.substr(prev, pos - prev);

            if (!token.empty()) tokens.push_back(token);

            prev = pos + delim.length();
        }
        while (pos < str.length() && prev < str.length());

        return tokens;
    }
}
