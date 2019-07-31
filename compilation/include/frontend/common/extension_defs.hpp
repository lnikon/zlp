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
