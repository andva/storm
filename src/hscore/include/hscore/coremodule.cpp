#include "coremodule.h"

#include <hscore/cmdparser.h>
#include <hscore/files/filesys.h>
#include <hscore/settings.h>

hscore::CoreModule::CoreModule()
	: HailStormModule()
	, m_showLogLine("SHOW_LOG_LINE", true)
	, m_showLogFunc("SHOW_LOG_FUNC", true)
{

}

hscore::CoreModule::~CoreModule()
{}

void hscore::CoreModule::addCmdArguments()
{
	hscore::CmdParser::instance().add('b', "break", "Disable debug breaks", true);
	hscore::CmdParser::instance().add('d', "data", "Custom data path", "C:/scrips/hscore");
}

void hscore::CoreModule::addSettings()
{
	Settings::instance().registerSetting(m_showLogFunc);
	Settings::instance().registerSetting(m_showLogLine);
}

void hscore::CoreModule::init()
{}

void hscore::CoreModule::bindUpdatePasses()
{}

void hscore::CoreModule::provideLocators()
{
	hscore::LogManager::provide(&m_log);
}

void hscore::CoreModule::registerKeys()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void hscore::CoreModule::registerFolders()
{
	std::string p = hscore::CmdParser::instance().getValue<std::string>('d');
	FileSys::instance().registerFolder("SETTINGS", p);
}

