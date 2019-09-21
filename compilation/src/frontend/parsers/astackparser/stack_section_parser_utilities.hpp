#pragma once

#include "parser_defs.hpp"
#include "logger.hpp"

namespace StackSectionParserUtilities
{

bool checkStackSection(const StackSection& stackSec, logger::LoggerSPtr pLogger);
bool checkStackSize(const std::size_t stackSize, logger::LoggerSPtr pLogger);

}
