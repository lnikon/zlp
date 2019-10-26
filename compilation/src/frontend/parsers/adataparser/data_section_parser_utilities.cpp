#include "data_section_parser_utilities.hpp"

#include "logger.hpp"

bool DataSectionParserUtilities::checkDataSection(const DataSection& dataSec, logger::LoggerSPtr pLogger)
{
  bool isAllOk = true;

  const bool isStaticTypeCheckOk = staticTypeCheck(dataSec, pLogger); 
  isAllOk = isStaticTypeCheckOk;

  return isAllOk;
}

bool DataSectionParserUtilities::staticTypeCheck(const DataSection& dataSec, logger::LoggerSPtr pLogger)
{
  bool isStaticTypeCheckOk = true;

  auto vars = dataSec.getVariablesVector();
  for(const auto& var : vars)
  {
    const bool isVarTypeSupported = isExpressionTypeSupported(var.type_, pLogger);
    if(!isVarTypeSupported)
    {
      pLogger->printMessage("Variable " + var.name_ + " has unsupported type.\n", logger::LogLevel::HIGH);
      exit(1);
    }

    isStaticTypeCheckOk = isVarTypeSupported; // do AND with others
  }

  return isStaticTypeCheckOk;
}

bool DataSectionParserUtilities::isExpressionTypeSupported(ValueType type, logger::LoggerSPtr)
{
  switch(type)
  {
    case ValueType::EXT_CHAR:
    case ValueType::EXT_byte_t:
    case ValueType::EXT_WORD:
    case ValueType::EXT_DWORD:
    case ValueType::EXT_QWORD:
      return true;
    case ValueType::EXT_NULL:
    default:
      return false;
  }
}
