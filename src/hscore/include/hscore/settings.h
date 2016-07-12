#ifndef HSCORE_SETTINGS_H
#define HSCORE_SETTINGS_H

#include <string>
#include <map>

#include <hscore/pattern/singleton.h>
#include <hscore/cm.h>
#include <hscore/settings/settingsparameter.h>
#include <hscore/settings/settingsdescription.h>
#pragma once



namespace hscore
{
  class Settings : public Singleton<Settings>
  {
  public:
    template<typename T>
    static const T get(const SettingDescription<T>& sDesc);

    template<typename T>
    static const T get(const std::string& key);

    void reset();

    template <typename T>
    void registerSetting(const SettingDescription<T>& descrip);

    void logSettings() const;

    void updateValue(const std::string& key, const std::string& val);

  private:
    SETUP_SINGLETON(Settings);
    Settings();
    virtual ~Settings();
    class Parameter;

    void parseFile(std::string line);

    template <typename T>
    const T fetch(const SettingDescription<T>& sDesc) const;

    template <typename T>
    const T fetch(const std::string& sDesc) const;


    typedef std::map<std::string, ParameterS > SBuffer;
    bool m_changed;
    SBuffer m_buffer;
  };


}

#include "settings.inl"

#endif
