#ifndef HSCORE_MODULE_MANAGER_H
#define HSCORE_MODULE_MANAGER_H

#include <vector>

#include <hscore/pattern/singleton.h>
#include <hscore/hailstormmodule.h>

#pragma once
namespace hscore
{
  class ModuleManager : public Singleton<ModuleManager>
  {
  public:
    void init();

    void update();

  protected:
    friend HailStormModule;
    void addModule(HailStormModule* module);

  private:
    SETUP_SINGLETON(ModuleManager);
    ModuleManager();
    virtual ~ModuleManager();
    std::vector<HailStormModule*> m_moules;
  };

}

#endif