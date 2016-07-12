#ifndef STREAMLOG_H__
#define STREAMLOG_H__

#include <memory>
#include <hscore/cm.h>
#include <hscore/logging/logger.h>
#include <string>
#include <hscore/color.h>

#pragma once


namespace hscore
{

class StreamLog : public Logger
{
public:
	StreamLog();
	virtual ~StreamLog();
	virtual void startLogging(Level l, const std::string& c) override;

	virtual void stopLogging(const char* const logFunction, int32_t logLine) override;

private:
	HS_DISSALLOW_COPY_ASSIGN(StreamLog);
	static Color levelToColor(Level l);
	void setStreamColor(const Color c);
};
}


#endif // STREAMLOG_H__
