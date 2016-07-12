#include "instream.h"

#include <hscore/log.h>

hscore::InStream::InStream(const std::string& path)
	: m_stream(std::make_shared<std::ifstream>())
	, m_isFile(true)
{
	std::ifstream* s = static_cast<std::ifstream*>(m_stream.get());
	s->open(path, std::ios::in);
	if (fail())
	{
		LOG_DEBUG(LOG_CORE, (path + std::string(": File not found")));
	}
}

hscore::InStream::InStream(std::shared_ptr<std::istream> s)
	: m_stream(s)
	, m_isFile(false)
{

}

hscore::InStream::~InStream()
{
	if (!fail() && m_isFile)
	{
		std::ifstream* s = static_cast<std::ifstream*>(m_stream.get());
		s->close();
	}
}
