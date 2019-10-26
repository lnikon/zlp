#pragma once
#include "common.hpp"

namespace Extensions {

  enum class MatchExtension
  {
    ME_NULL = 0,
    ME_DONT_CARE
  };

  /* Instruction extensions */
  enum class Extension
  {
    EXT_NULL = 0,
    EXT_CHAR,
    EXT_byte_t,
    EXT_WORD,
    EXT_DWORD,
    EXT_QWORD,
  };

  static auto extensionToString(Extension ext)
  {
    if (ext == Extension::EXT_byte_t)
    {
      return std::string{ "EXT_byte_t" };
    }
    else if (ext == Extension::EXT_CHAR)
    {
      return std::string{ "EXT_CHAR" };
    }
    else if (ext == Extension::EXT_WORD)
    {
      return std::string{ "EXT_WORD" };
    }
    else if (ext == Extension::EXT_DWORD)
    {
      return std::string{ "EXT_DWORD" };
    }
    else if (ext == Extension::EXT_QWORD)
    {
      return std::string{ "EXT_QWORD" };
    }
    else
    {
      return std::string{ "EXT_NULL" };
    }
  }

  /*
  * If @ext is empty, then return default value for extension,
  * else if @ext is supported extension string, return that extension value,
  * otherwise, return Extension::EXT_NULL value
  */
  static auto extension(const std::string& ext)
  {
    // Default value
    if (ext.empty())
    {
      return Extension::EXT_DWORD;
    }

    if (ext == "B")
    {
      return Extension::EXT_byte_t;
    }
    else if (ext == "W")
    {
      return Extension::EXT_WORD;
    }
    else if (ext == "DW")
    {
      return Extension::EXT_DWORD;
    }
    else if (ext == "QW")
    {
      return Extension::EXT_QWORD;
    }
    else
    {
      return Extension::EXT_NULL;
    }
  }
}
