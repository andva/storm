#include <hscore/debug/break.h>
#include <hscore/cmdparser.h>

template <typename T>
hscore::ValueEqBreak<T>::ValueEqBreak(T currentValue, T breakValue, const std::string& breakFunction, const int32_t breakLine)
  : Break(breakFunction, breakLine, false)
{
  if (currentValue == breakValue)
  {
    doBreak(breakFunction, breakLine);
  }
}

template <typename T>
hscore::ValueLessBreak<T>::ValueLessBreak(T currentValue, T lessValue, const std::string& breakFunction, const int32_t breakLine)
  : Break(breakFunction, breakLine, false)
{
  if (currentValue < lessValue)
  {
    doBreak(breakFunction, breakLine);
  }
}

template <typename T>
hscore::ValueLargerBreak<T>::ValueLargerBreak(T currentValue, T largerValue, const std::string& breakFunction, const int32_t breakLine)
{
  if (currentValue > largerValue)
  {
    doBreak(breakFunction, breakLine);
  }
}

void hscore::hsDebugBreak()
{
  if (CmdParser::instance().getValue<bool>('b'))
  {
    return;
  }
#ifdef WIN32
  __debugbreak();
#endif
}

hscore::ConditionalBreak::ConditionalBreak(bool condition, const std::string& breakFunction, const int32_t breakLine)
  : Break(breakFunction, breakLine, false)
{
  if (condition)
  {
    doBreak(breakFunction, breakLine);
  }
}

hscore::Break::Break(const std::string& breakFunction, const int32_t breakLine, bool alwaysBreak /*= true*/)
{
  if (alwaysBreak)
  {
#ifdef _DEBUG
    if (false)//CmdParser::disableDebugBreak())
    {
      return;
    }
#endif
    doBreak(breakFunction, breakLine);
  }
}

hscore::Break::~Break()
{}

void hscore::Break::doBreak(const std::string& breakFunction, const int32_t breakLine)
{
  LOG_INFO("Breakpoint hit (", breakFunction, ":", breakLine, ")");
#ifdef HS_BREAK_ON_CUSTOM_BREAKPOINTS
  hsDebugBreak();
#endif
}
/*
template hscore::ValueEqBreak<int32_t>;
template hscore::ValueEqBreak<float_t>;
template hscore::ValueLessBreak<float_t>;
template hscore::ValueLessBreak<int32_t>;*/
