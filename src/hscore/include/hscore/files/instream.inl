namespace hscore
{
bool InStream::fail() const
{
	return m_stream->fail();
}

std::string InStream::getLine()
{
	std::string l;
	std::getline(*m_stream, l);
	return l;
}

bool InStream::eof() const
{
	return m_stream->eof()
		|| !m_stream->good();
}
}
