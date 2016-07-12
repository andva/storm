#ifndef HSCORE_BREAK_H
#define HSCORE_BREAK_H

#pragma once

#include <string>
#include <hscore/log.h>
#include <hscore/cm.h>

#define HS_ENABLE_BREAKPOINTS

#ifdef _DEBUG
#define HS_BREAK_ON_CUSTOM_BREAKPOINTS
#endif

namespace hscore
{

  void hsDebugBreak();

  class Break
  {
  public:
    Break(const std::string& breakFunction, const int32_t breakLine, bool alwaysBreak = true);
    virtual ~Break();
  protected:
    HS_DISSALLOW_ALL_DEFAULTS(Break);
    void doBreak(const std::string& breakFunction, const int32_t breakLine);
  private:

  };

  class ConditionalBreak : public Break
  {
  public:
    ConditionalBreak(bool condition, const std::string& breakFunction, const int32_t breakLine);
  private:
    HS_DISSALLOW_ALL_DEFAULTS(ConditionalBreak);
  };

  template <typename T>
  class ValueEqBreak : public Break
  {
  public:
    ValueEqBreak(T currentValue, T breakValue, const std::string& breakFunction, const int32_t breakLine);
  private:
    HS_DISSALLOW_ALL_DEFAULTS(ValueEqBreak);
  };

  template <typename T>
  class ValueLessBreak : public Break
  {
  public:
    ValueLessBreak(T currentValue, T lessValue, const std::string& breakFunction, const int32_t breakLine);
  private:
    HS_DISSALLOW_ALL_DEFAULTS(ValueLessBreak);
  };

  template <typename T>
  class ValueLargerBreak : public Break
  {
  public:
    ValueLargerBreak(T currentValue, T largerValue, const std::string& breakFunction, const int32_t breakLine);
  private:
    HS_DISSALLOW_ALL_DEFAULTS(ValueLargerBreak);
  };

}
#ifdef HS_ENABLE_BREAKPOINTS
#define HS_BREAK() hscore::Break(__FILE__, __LINE__);

#define HS_BREAK_VALUE_EQ(_type_, _val_, _break_val_) hscore::ValueEqBreak<_type_>(_val_, _break_val_, __FILE__, __LINE__);

#define HS_BREAK_VALUE_LARGER(_type_, _val_, _break_val_) hscore::ValueLargerBreak<_type_>(_val_, _break_val_, __FILE__, __LINE__);

#define HS_BREAK_VALUE_LESS(_type_, _val_, _break_val_) hscore::ValueLessBreak<_type_>(_val_, _break_val_, __FILE__, __LINE__);

#else
#define HS_BREAK() HS_DO_NOTHING
#define HS_BREAK_VALUE_EQ(_type_, _val_, _break_val_) HS_DO_NOTHING
#endif

#endif
