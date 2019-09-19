#pragma once

#include "parser_defs.hpp"

namespace DataSectionParserUtilities
{

bool checkDataSection(const DataSection& dataSec);
bool staticTypeCheck(const DataSection& dataSec);
bool isExpressionTypeSupported(ValueType type);

}
