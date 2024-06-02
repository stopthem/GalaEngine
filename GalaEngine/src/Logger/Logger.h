#pragma once

#include <string>
#include <vector>

#include "csys/csys.h"

namespace gala
{
    /*
* LogEntry
*
* Struct that holds information about the log itself.
*/
    struct LogEntry {
        csys::ItemType LogType = csys::ItemType::LOG;
        std::string Message;
    };

    /*
* Logger
*
* A logging class using std::cout for now.
*/
    class Logger
    {
    public:
        static std::string CurrentTimeToString();

        static void Log(const std::string& message);

        static void Err(const std::string& message);

    public:
        static std::vector<LogEntry> LogEntries;

    private:
        static void AddToEntries(const LogEntry& logEntry);
    };
}

