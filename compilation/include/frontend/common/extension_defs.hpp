#pragma once
#include "common.hpp"

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

