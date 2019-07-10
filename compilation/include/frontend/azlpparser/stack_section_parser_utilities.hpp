#pragma once

#include "parser_defs.hpp"

namespace StackSectionParserUtilities
{

bool checkStackSection(const StackSection& stackSec);
bool checkStackSize(const std::size_t stackSize);

}
