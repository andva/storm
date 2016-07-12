#ifndef HSCORE_COREMODULE_H
#define HSCORE_COREMODULE_H

#include <hscore/hailstormmodule.h>
#include <hscore/logging/streamlog.h>
#include <hscore/settings/settingsdescription.h>
#pragma once

namespace hscore
{
  class CoreModule : public HailStormModule
  {
  public:
    CoreModule();

    virtual ~CoreModule();

    virtual void addCmdArguments() override;
    virtual void addSettings() override;
    virtual void registerFolders() override;
    
    virtual void init() override;

    virtual void bindUpdatePasses() override;

	virtual void provideLocators() override;

	virtual void registerKeys() override;

  private:
    SettingDescription<bool> m_showLogLine;
    SettingDescription<bool> m_showLogFunc;
    StreamLog m_log;
  };
}


#endif