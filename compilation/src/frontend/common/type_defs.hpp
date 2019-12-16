#pragma once
#include <cstdint>

#include "extension_defs.hpp"

/* Variable types */
using BYTE  = uint8_t;
using CHAR  = char;
using WORD  = uint16_t;
using DWORD = uint32_t;
using QWORD = uint64_t;

using BYTE_ARRAY  = std::vector<BYTE>;
using CHAR_ARRAY  = std::vector<CHAR>;
using WORD_ARRAY  = std::vector<WORD>;
using DWORD_ARRAY = std::vector<DWORD>;
using QWORD_ARRAY = std::vector<QWORD>;

/* Type of operands value */
using ValueType = Extensions::Extension;

