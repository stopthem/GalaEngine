#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <iostream>
#include <chrono>


std::vector<LogEntry> Logger::logEntries;

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