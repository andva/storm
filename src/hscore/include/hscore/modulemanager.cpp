#include "modulemanager.h"
#include <hscore/settings.h>
#include <hscore/cmdparser.h>

hscore::ModuleManager::ModuleManager()
{

}

hscore::ModuleManager::~ModuleManager()
{

}

void hscore::ModuleManager::init()
{
	for (HailStormModule* m : m_moules)
	{
		m->provideLocators();
	}
	for (HailStormModule* m : m_moules)
	{
		m->addSettings();
	}
	for (HailStormModule* m : m_moules)
	{
		m->addCmdArguments();
	}
	for (HailStormModule* m : m_moules)
	{
		m->registerFolders();
	}


	hscore::Settings::instance().reset();
	char* v[1];
	hscore::CmdParser::instance().parse(0, v);
	for (HailStormModule* m : m_moules)
	{
		m->init();
	}
	for (HailStormModule* m : m_moules)
	{
		m->bindUpdatePasses();
	}
	hscore::Settings::instance().logSettings();
}

void hscore::ModuleManager::update()
{
	for (HailStormModule* m : m_moules)
	{
		for (int32_t i = 0; i < HailStormModule::c_numPasses; ++i)
		{
			m->update(i);
		}
	}
}

void hscore::ModuleManager::addModule(HailStormModule* module)
{
	m_moules.push_back(module);
}
