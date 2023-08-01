#pragma once
#include "spdlog/spdlog.h"//fix this
#include <string>
#include <memory>


namespace Log
{

class Logger
{
public:
	Logger() = default;

	~Logger() = default;

	Logger(const Logger&) = delete;

	Logger& operator=(const Logger&) = delete;

	static void Init(const std::string& name);

	static void ShutDown();

	static const std::string& GetName();

	static const std::shared_ptr<spdlog::logger>& GetLogger();

private:

	static std::shared_ptr<spdlog::logger> mConsoleLogger;
};
}

#ifdef _DEBUG

#define LOG_INFO(...)		Log::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...)		Log::Logger::GetLogger()->trace(__VA_ARGS__)
#define LOG_WARNING(...)	Log::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		Log::Logger::GetLogger()->error(__VA_ARGS__)

#elif NDEBUG

#define LOG_INFO(...)		
#define LOG_TRACE(...)	
#define LOG_WARN(...)		
#define LOG_ERROR(...)

#endif
