

#ifndef INSTREAM_H__
#define INSTREAM_H__



#include <fstream>
#include <sstream>
#include <memory>

#pragma once
namespace hscore
{
  class InStream
  {
  public:
    explicit InStream(const std::string& path);
    explicit InStream(std::shared_ptr<std::istream> s);
    ~InStream();
    inline bool fail() const;
    inline std::string getLine();
    inline bool eof() const;
  private:
    std::shared_ptr<std::istream> m_stream;
    bool m_isFile;
  };

}

#include "instream.inl"
#endif // INSTREAM_H__
