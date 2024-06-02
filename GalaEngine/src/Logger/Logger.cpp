#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <iostream>
#include <chrono>

#include "../Core/Editor/GalaConsole.h"


namespace gala
{
    std::vector<LogEntry> Logger::LogEntries;

    std::string Logger::CurrentTimeToString()
    {
        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        std::string str(buffer);

        return str;
    }

    void Logger::Log(const std::string& message)
    {
        LogEntry logEntry;
        logEntry.LogType = csys::ItemType::LOG;
        logEntry.Message = "LOG | [" + CurrentTimeToString() + "] : " + message;

        std::cout << "\x1B[32m" << logEntry.Message << "\033[0m" << '\n';

        AddToEntries(logEntry);
    }

    void Logger::Err(const std::string& message)
    {
        LogEntry logEntry;
        logEntry.LogType = csys::ItemType::ERROR;
        logEntry.Message = "ERROR | [" + CurrentTimeToString() + "] : " + message;

        std::cout << "\x1B[91m" << logEntry.Message << "\033[0m" << '\n';

        AddToEntries(logEntry);
    }

    void Logger::AddToEntries(const LogEntry& logEntry)
    {
        LogEntries.push_back(logEntry);


        GalaConsole::Get().GetConsole()->System().Log(logEntry.LogType) << logEntry.Message << csys::endl;
    }
}
