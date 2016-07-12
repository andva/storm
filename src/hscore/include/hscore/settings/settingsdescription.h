
#ifndef HSCORE_SETTINGSDESCRIPTION_H
#define HSCORE_SETTINGSDESCRIPTION_H
#pragma once
namespace hscore
{
  class SettingDescriptionI
  {

  };


  template <typename T>
  class SettingDescription : public SettingDescriptionI
  {
  public:
    SettingDescription(const std::string& t, const T& def) : token(t), defaultValue(def) {}
    const std::string token;
    const T defaultValue;
  private:
  };
}

#endif // !HSCORE_SETTINGSDESCRIPTION_H