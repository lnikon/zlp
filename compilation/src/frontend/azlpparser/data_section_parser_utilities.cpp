#include "data_section_parser_utilities.hpp"

#include "logger.hpp"

bool DataSectionParserUtilities::checkDataSection(const DataSection& dataSec)
{
  bool isAllOk = true;

  const bool isStaticTypeCheckOk = staticTypeCheck(dataSec); 
  isAllOk = isStaticTypeCheckOk;

  return isAllOk;
}

bool DataSectionParserUtilities::staticTypeCheck(const DataSection& dataSec)
{
  bool isStaticTypeCheckOk = true;

  auto vars = dataSec.getVariablesVector();
  for(const auto& var : vars)
  {
    const bool isVarTypeSupported = isExpressionTypeSupported(var.type_);
    if(!isVarTypeSupported)
    {
      Logger::printMessage("Variable " + var.name_ + " has unsupported type.\n", LogLevel::HIGH);
      exit(1);
    }

    isStaticTypeCheckOk = isVarTypeSupported; // do AND with others
  }

  return isStaticTypeCheckOk;
}

bool DataSectionParserUtilities::isExpressionTypeSupported(ValueType type)
{
  switch(type)
  {
    case ValueType::CHAR:
    case ValueType::BYTE:
    case ValueType::WORD:
    case ValueType::DWORD:
    case ValueType::QWORD:
      return true;
    case ValueType::INVALID:
    default:
      return false;
  }

}
