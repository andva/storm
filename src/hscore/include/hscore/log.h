#ifndef HSCORE_LOG_H
#define HSCORE_LOG_H

#pragma once

#include <string>
#include <hscore/logging/logmanager.h>
#include <hscore/cm.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>

namespace hscore
{

template <typename T>
inline void doLogText(T&& t)
{
	std::cout << std::forward<T>(t);
};

template <typename T, typename... Args>
void doLogText(T&& t, Args&&... tail)
{
	std::cout << std::forward<T>(t);
	doLogText(std::forward<Args>(tail)...);
};

template <typename... Args>
inline void logText(Logger::Level logLevel, const char* const logCategory, const char* const logFunction, int32_t logLine, Args&&... text)
{

	LogManager::locate()->startLogging(logLevel, std::string(logCategory));
	doLogText(std::forward<Args>(text)...);
	LogManager::locate()->stopLogging(logFunction, logLine);
}

}

#endif

#define TEST_LOG(...) hscore::logText(##__VA_ARGS__)

#define LOG(__level__, __category__, ...) hscore::logText(__level__, __category__,  __FUNCTION__, __LINE__, ##__VA_ARGS__)

//hscore::logText(__level__, __category__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR_I(__category__, ...) LOG(hscore::Logger::Error, __category__, ##__VA_ARGS__)

#define LOG_WARNING_I(__category__, ...) LOG(hscore::Logger::Warning, __category__, ##__VA_ARGS__)

#define LOG_INFO_I(__category__, ...) LOG(hscore::Logger::Info, __category__, ##__VA_ARGS__)

#ifndef NDEBUG
#define LOG_DEBUG_I(__category__, ...) LOG(hscore::Logger::Debug, __category__, ##__VA_ARGS__)
#else
#define LOG_DEBUG_I(__category__, ...) HS_DO_NOTHING
#endif

#define LOG_CORE "CORE"

#define LOG_WARNING(...) LOG_WARNING_I(LOG_CORE, ##__VA_ARGS__)

#define LOG_DEBUG(...) LOG_DEBUG_I(LOG_CORE, ##__VA_ARGS__)

#define LOG_INFO(...) LOG_INFO_I(LOG_CORE, ##__VA_ARGS__)