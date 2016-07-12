#ifndef LOGGER_H__
#define LOGGER_H__

#pragma once

#include <string>
#include <stdint.h>
#include <iostream>

namespace hscore
{
class Logger
{
public:
	Logger();
	virtual ~Logger();
	enum Level
	{
		Info = 0x0000,
		Debug = 0x0001,
		Warning = 0x0002,
		Error = 0x0003,
		Fatal = 0x0004,
		None = 0x0005,
	};
	virtual void startLogging(Level l, const std::string& c) = 0;

	template<typename T>
	void log(const T& message);

	virtual void stopLogging(const char* const logFunction, int32_t logLine) = 0;

protected:
	static std::string levelToString(Level l);
};

template<typename T>
void hscore::Logger::log(const T& message)
{
	std::cout << message;
}

}
#endif // LOG_H__
