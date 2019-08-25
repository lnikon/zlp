#pragma once
#include "common.hpp"

namespace Extensions {
/* Instruction extensions */
enum class Extension 
{
  EXT_NULL = 0,
  EXT_CHAR,
  EXT_BYTE,
  EXT_WORD,
  EXT_DWORD,
  EXT_QWORD,
};

static std::string extensionToString(Extension ext)
{
  if(ext == Extension::EXT_BYTE)
  {
    return std::string{"EXT_BYTE"};
  }
  else if(ext == Extension::EXT_CHAR)
  {
    return std::string{"EXT_CHAR"};
  }
  else if(ext == Extension::EXT_WORD)
  {
    return std::string{"EXT_WORD"};
  }
  else if(ext == Extension::EXT_DWORD)
  {
    return std::string{"EXT_DWORD"};
  }
  else if(ext == Extension::EXT_QWORD)
  {
    return std::string{"EXT_QWORD"};
  }
  else
  {
    return std::string{"EXT_NULL"};
  }
}

static auto isExtension(const std::string& ext)
{
    if(ext == "B")
    {
        return std::make_pair(true, Extension::EXT_BYTE);
    }
    else if(ext == "W")
    {
        return std::make_pair(true, Extension::EXT_WORD);
    }
    else if(ext == "DW")
    {
        return std::make_pair(true, Extension::EXT_DWORD);
    }
    else if(ext == "QW")
    {
        return std::make_pair(true, Extension::EXT_QWORD);
    }
    else
    {
        return std::make_pair(false, Extension::EXT_NULL);
    }
}
}
