#pragma once
#include <mutex>
#include <stdio.h>

// Console logger

class Logger
{
public:
	template<typename... Args>
	static void Trace(const char* message, Args... args)
	{
		send("Trace", message, args...);
	}

	template<typename... Args>
	static void Debug(const char* message, Args... args)
	{
		send("Debug", message, args...);
	}

	template<typename... Args>
	static void Info(const char* message, Args... args)
	{
		send("Info", message, args...);
	}

	template<typename... Args>
	static void Warn(const char* message, Args... args)
	{
		send("Warn", message, args...);
	}

	template<typename... Args>
	static void Error(const char* message, Args... args)
	{
		send("Error", message, args...);
	}

	//Remember to clean before fatal
	template<typename... Args>
	static void Fatal(const char* message, Args... args)
	{
		send("Fatal", message, args...);
		exit(-1);
	}

private:
	template<typename... Args>
	static void send(const char* type, const char* message, Args... args)
	{
		std::lock_guard<std::mutex> lock(mLogMutex);
		printf("[%s]\t", type);
		printf(message, args...);
		printf("\n");
	}

private:
	static std::mutex mLogMutex;
};

inline std::mutex Logger::mLogMutex;