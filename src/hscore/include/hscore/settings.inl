//#ifndef SETTINGS_INL__
//#define SETTINGS_INL__

#include <hscore/ato.h>
#include <hscore/assert.h>

//#pragma once

template<typename T>
const T hscore::Settings::get(const SettingDescription<T>& sDesc)
{
  return instance().fetch<T>(sDesc);
}

template<typename T>
const T hscore::Settings::get(const std::string& key)
{
  return instance().fetch<T>(key);
}

template<typename T>
const T hscore::Settings::fetch(const SettingDescription<T>& sDesc) const
{
  SBuffer::const_iterator it = m_buffer.find(sDesc);
  if (it != m_buffer.end())
  {
    return ato<T>(it->second.getValue().c_str());
  }
  else
  {
    return sDesc.defaultValue;
  }
}

template <typename T>
const T hscore::Settings::fetch(const std::string& sDesc) const
{
  SBuffer::const_iterator it = m_buffer.find(sDesc);
  HS_ASSERT(it != m_buffer.end() && "Setting not found");
  return ato<T>(it->second.getValue());
}

template <typename T>
void hscore::Settings::registerSetting(const SettingDescription<T>& desc)
{
  SBuffer::iterator it = m_buffer.find(desc.token);
  if (it == m_buffer.end())
  {
    std::string sv = toa<T>(desc.defaultValue);
    m_buffer[desc.token].setValue(sv);
  }
}

//#endif // SETTINGS_INL__