#pragma once
#include "../include/Logger.h"
#include "spdlog/sinks/msvc_sink.h"


namespace Log
{
std::shared_ptr<spdlog::logger> Logger::mConsoleLogger;

void Logger::Init(const std::string& name)
{
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
	mConsoleLogger = std::make_shared<spdlog::logger>(name, sink);
	mConsoleLogger->set_pattern("[%T][%l] %n: %v");
	mConsoleLogger->set_level(spdlog::level::trace);
	mConsoleLogger->flush_on(spdlog::level::trace);
	spdlog::register_logger(mConsoleLogger);
}

void Logger::ShutDown()
{
	spdlog::shutdown();
}
const std::string& Logger::GetName()
{
	return mConsoleLogger->name();
}
const std::shared_ptr<spdlog::logger>& Logger::GetLogger()
{
	return mConsoleLogger;
}

}// namespace Log