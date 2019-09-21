#pragma once

#include "parser_defs.hpp"
#include "logger.hpp"

namespace DataSectionParserUtilities
{

bool checkDataSection(const DataSection& dataSec, logger::LoggerSPtr pLogger);
bool staticTypeCheck(const DataSection& dataSec, logger::LoggerSPtr pLogger);
bool isExpressionTypeSupported(ValueType type, logger::LoggerSPtr pLogger);

}
