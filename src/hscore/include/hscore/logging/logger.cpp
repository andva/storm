#include "logger.h"

hscore::Logger::Logger()
{

}

hscore::Logger::~Logger()
{

}

std::string hscore::Logger::levelToString(Level l)
{
  switch (l)
  {
  case Logger::Info:
    return "INFO";
  case Logger::Debug:
    return "DEBUG";
  case Logger::Warning:
    return "WARNING";
  case Logger::Error:
    return "ERROR";
  case Logger::Fatal:
    return "FATAL";
  case Logger::None:
    return "NONE";
  default:
    return "UNDEFINED";
  }
}

