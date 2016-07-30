#include "settings.h"
#include <regex>
#include <hscore/files/filesys.h>
#include <hscore/files/workingdir.h>

hscore::Settings::Settings()
{
}

hscore::Settings::~Settings()
{

}

void hscore::Settings::reset()
{
	std::string path = WorkingDir::instance().getFilePath("settings.txt");

	std::shared_ptr<InStream> stream = FileSys::instance().getInFileStream(path);

	if (!stream->fail())
	{
		std::string fileString;
		while (!stream->eof())
		{
			parseFile(stream->getLine());
		}
	}
}

void hscore::Settings::logSettings() const
{
	LOG_INFO("-- Log settings --");
	for (auto& s : m_buffer)
	{
		LOG_INFO(s.second.getValue(), "\t", s.first);
	}
	LOG_INFO("-- --");
}

void hscore::Settings::updateValue(const std::string& key, const std::string& val)
{
	m_buffer[key].setValue(val);
}

void hscore::Settings::parseFile(std::string line)
{
	std::smatch value_match;
	std::regex regex("(\\w{1,}).(\\d{1,}).*");
	if (line.size() == 0)
		return;
	if (std::regex_match(line, value_match, regex)
		&& value_match.size() == 3)
	{
			std::string identifier = value_match[1].str();
			std::string value = value_match[2].str();
			updateValue(identifier, value);
	}
	else
	{
		LOG_WARNING("Entry ", line, " has no assigned value.");
	}
}
