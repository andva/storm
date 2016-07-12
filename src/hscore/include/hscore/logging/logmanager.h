#ifndef LOGMANAGER_H__
#define LOGMANAGER_H__

#include <string>

#include <hscore/pattern/locator.h>
#include <hscore/logging/logger.h>

namespace hscore
{
  class LogManager : public Locator<Logger>
  {
  public:
    virtual void log(Logger::Level l, const std::string& c, const char* const file, int32_t line, const std::string& message);
  protected:
  };
}
#endif // LOGMANAGER_H__
