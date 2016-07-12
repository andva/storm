#include "hailstormmodule.h"

#include <hscore/modulemanager.h>
#include <hscore/log.h>

const int32_t hscore::HailStormModule::c_numPasses = 3;

hscore::HailStormModule::HailStormModule()
{
	for (auto& f : m_updatePasses)
	{
		f = [&]() { HailStormModule::emptyUpdate(); };
	}
	ModuleManager::instance().addModule(this);
}

hscore::HailStormModule::~HailStormModule()
{

}

void hscore::HailStormModule::update(int32_t pass)
{
	this->m_updatePasses[pass]();
}

void hscore::HailStormModule::emptyUpdate()
{}
