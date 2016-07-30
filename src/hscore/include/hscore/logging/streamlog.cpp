#include "streamlog.h"

#include <hscore/settings.h>
#include <sstream>

#if defined(WIN32)
#pragma warning(push, 0)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#pragma warning(pop)

#include <hscore/logging/winguicon.h>
#endif
namespace
{

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

}
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
const int32_t LogColorRed = 12;
const int32_t LogColorYellow = 14;
const int32_t LogColorWhite = 7;
const int32_t LogColorGreen = 2;
#else
const int32_t LogColorRed = 31;
const int32_t LogColorYellow = 33;
const int32_t LogColorWhite = 39;
const int32_t LogColorGreen = 32;
#endif

#ifdef WIN32
#define kinSET_OUTPUT_CLR(strm, color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)
#else
#define kinSET_OUTPUT_CLR(color) fprintf(stdout, "\033["); fprintf(stdout, "%i", color); fprintf(stdout, "m");
#endif
hscore::StreamLog::StreamLog()
{
#ifdef WIN32
  RedirectIOToConsole();
#endif
}


hscore::StreamLog::~StreamLog()
{

}

hscore::Color hscore::StreamLog::levelToColor(Level l)
{
  switch (l)
  {
  case Logger::Info:
    return COLOR_WHITE;
  case Logger::Debug:
		return COLOR_GREEN;
  case Logger::Warning:
    return COLOR_YELLOW;
  case Logger::Error:
  case Logger::Fatal:
    return COLOR_RED;
  case Logger::None:
  default:
    return COLOR_WHITE;
  }
}

void hscore::StreamLog::setStreamColor(const Color c)
{
  int32_t colorId;
  if (c == COLOR_RED)
  {
    colorId = LogColorRed;
  }
  else if (c == COLOR_YELLOW)
  {
    colorId = LogColorYellow;
  }
  else if (c == COLOR_GREEN)
  {
    colorId = LogColorGreen;
  }
  else
  {
    colorId = LogColorWhite;
  }
  kinSET_OUTPUT_CLR(colorId);
}

void hscore::StreamLog::startLogging(Level l, const std::string& c)
{
	setStreamColor(levelToColor(l));
	std::cout << c << "\t";
}

void hscore::StreamLog::stopLogging(const char* const logFunction, int32_t logLine)
{
	bool showLine = Settings::instance().get<bool>("SHOW_LOG_LINE");
	bool showFunc = Settings::instance().get<bool>("SHOW_LOG_FUNC");
	if (showLine
		|| showFunc)
	{
		std::cout << "\t";
	}
	if (showFunc)
	{
		std::cout << logFunction << " ";
	}
	if (showLine && showFunc)
	{
		std::cout << ":";
	}
	if (showLine)
	{
		std::cout << logLine;
	}
	std::cout << std::endl;

	setStreamColor(COLOR_WHITE);
}
