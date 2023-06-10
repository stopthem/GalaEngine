#pragma once

#include <string>
#include <vector>

/*
* LogType
*
* Enum for log types.
*/
enum LogType
{
	Log_Info,
	Log_Warning,
	Log_Error
};

/*
* LogEntry
*
* Struct that holds information about the log itself.
*/
struct LogEntry {
	LogType LogType = Log_Info;
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
};

