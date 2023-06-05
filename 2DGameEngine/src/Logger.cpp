#include "Logger.h"
#include <iostream>
#include <chrono>

std::vector<LogEntry> Logger::logEntries;

std::string Logger::CurrentTimeToString()
{
	char str[26];

	auto currentTimePoint = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

	return std::strerror(ctime_s(str, sizeof str, &currentTime));
}

void Logger::Log(const std::string& message)
{
	LogEntry logEntry;
	logEntry.logType = Log_Info;
	logEntry.message = "LOG | [" + CurrentTimeToString() + "] : " + message;

	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;

	logEntries.push_back(logEntry);
}

void Logger::Err(const std::string& message)
{
	LogEntry logEntry;
	logEntry.logType = Log_Error;
	logEntry.message = "ERROR | [" + CurrentTimeToString() + "] : " + message;

	std::cout << "\x1B[91m" << logEntry.message << "\033[0m" << std::endl;

	logEntries.push_back(logEntry);
}