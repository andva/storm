#ifndef HSCORE_HSMODULE_H
#define HSCORE_HSMODULE_H
#pragma once
#include <hscore/cm.h>
#include <array>
#include <functional>

namespace hscore
{
  class HailStormModule
  {
  public:
    static const int32_t c_numPasses;
    HailStormModule();
    virtual ~HailStormModule();
    virtual void registerFolders() = 0;
    virtual void addCmdArguments() = 0;
    virtual void addSettings() = 0;
    virtual void bindUpdatePasses() = 0;
	virtual void provideLocators() = 0;
	virtual void registerKeys() = 0;
    virtual void init() = 0;
    virtual void update(int32_t pass) final;

  protected:
    typedef void(HailStormModule::*FunctionPointer)();
    std::array<std::function<void()>, 3> m_updatePasses;

  private:
    void emptyUpdate();
  };
}


#endif