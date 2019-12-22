#include "data_section_parser.hpp"

#include "utility.hpp"
#include "lexer_defs.hpp"
#include "logger.hpp"
#include "utility.hpp"
#include "debug.hpp"
#include "generic_value.h"

DataSectionParser::DataSectionParser(logger::LoggerSPtr pLogger)
    : ps_logger_{pLogger}
{
}

DataSection DataSectionParser::parse(std::fstream &inputStream)
{
  DataSection dataSec;

  auto line = std::string{};
  bool isDataSectionOk = false;
  bool isDataSectionPresent = false;

  while (!isDataSectionPresent && std::getline(inputStream, line))
  {
    lineNumber_++;

    line = utility::trim_copy(line);

    if (line.empty())
    {
      continue;
    }

    // If .DATA doesn't section present,
    // then start processing of the .CODE section
    // else, read the next line
    const auto dataSectionPos = line.find(DATA_SEC_NAME);
    isDataSectionPresent = (dataSectionPos != std::string::npos);
  }

  if (isDataSectionPresent)
  {
    while (!isDataSectionOk && std::getline(inputStream, line))
    {
      lineNumber_++;

      line = utility::trim_copy(line);

      if (line.empty() || utility::starts_with(line, "#"))
      {
        continue;
      }

      const bool isCodeSegment = utility::starts_with(line, CODE_SEC_NAME);
      const bool isMainSegment = utility::starts_with(line, MAIN_SEC_NAME);
      if (isCodeSegment || isMainSegment)
      {
        break;
      }

      bool isArrayDecl = isArrayDeclaration(line);
      if (isArrayDecl)
      {
        parseArray(dataSec, line);
      }
      else
      {
        parseVariable(dataSec, line);
      }
    }
  }
  else
  {
    lineNumber_--;
  }

  std::cout << "hebhbsa\n";

  return dataSec;
}

void DataSectionParser::setLineNumber(int lineNumber) { lineNumber_ = lineNumber; }

int DataSectionParser::getLineNumber() const { return lineNumber_; }

void DataSectionParser::parseVariable(DataSection &rDataSec, std::string line)
{
  ValueType type = getSpecifiedType(line);

  std::string name = getVariableName(line);

  const bool isVariableUsedAsString = isStringDeclaration(line);
  if (isVariableUsedAsString)
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Type mismatch. Use CHAR array instead", logger::LogLevel::HIGH);
    exit(1);
  }

  // Depending on the type of the variable
  // one of branches should be active
  const auto typeStr = utility::returnStringForType(type);

  // This flag is for syntactical checks
  bool isAssignSignPresent{false};

  // If the variable is not char,
  // then parse its value as a string
  std::vector<std::string> valueFromLexer{};

  // If the variable type is CHAR,
  // then parse its value as char

  GenericValue value(type);
  if (!typeStr.compare("CHAR"))
  {
    char charValueFromLexer;
    std::tie(isAssignSignPresent, charValueFromLexer) = getCharValueForLexer(line);
    value = std::move(charValueFromLexer);
  }
  else
  {
    std::tie(isAssignSignPresent, valueFromLexer) = getArrayValueForLexer(line);

    if (valueFromLexer.size() > 1)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Too many values specified for variable", logger::LogLevel::HIGH);
      exit(1);
    }

    switch (value.type())
    {
    case Extensions::Extension::EXT_BYTE:
    {
        BYTE byte = utility::parserNumber<uint8_t, 0>(' ', &valueFromLexer[0]);
        value = std::move(byte);
        break;
    }
    case Extensions::Extension::EXT_WORD:
    {
        WORD byte = utility::parserNumber<uint16_t, 0>(' ', &valueFromLexer[0]);
        value = std::move(byte);
        break;
    }
    case Extensions::Extension::EXT_DWORD:
    {
        DWORD byte = utility::parserNumber<uint32_t, 0>(' ', &valueFromLexer[0]);
        value = std::move(byte);
        break;
    }
    case Extensions::Extension::EXT_QWORD:
    {
        QWORD byte = utility::parserNumber<uint64_t, 0>(' ', &valueFromLexer[0]);
        value = std::move(byte);
        break;
    }
    case Extensions::Extension::EXT_CHAR:
    {
      std::string str = valueFromLexer[0];
      value = std::move(str);
      break;
    }
    default:
        break;
    }
  }

  rDataSec.put(DataSectionItem{name, value});
}

void DataSectionParser::parseArray(DataSection &rDataSec, std::string line)
{
  DataSectionItem item;

  // Parse array type
  auto type = getSpecifiedType(line);
  GenericValue value(type);

  // TODO: Check for name redifinition
  auto name = getArrayName(line);
  item.name_ = name;

  const auto [isSizeSpecified, size] = getArraySize(line);

  const auto typeStr = utility::returnStringForType(type);
  bool isAssignSignPresent{false};
  std::vector<std::string> valueFromLexer{};
  if (!typeStr.compare("CHAR"))
  {
    std::tie(isAssignSignPresent, valueFromLexer) = getStringValueForLexer(line);
  }
  else
  {
    std::tie(isAssignSignPresent, valueFromLexer) = getArrayValueForLexer(line);
  }

  if (isSizeSpecified && !isAssignSignPresent)
  {
    if (valueFromLexer.size() > 0)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Missing assignment sign", logger::LogLevel::HIGH);
      exit(1);
    }
  }

  if (isSizeSpecified && valueFromLexer.empty())
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Neither array size nor initialization list specified. GO TO HELL!", logger::LogLevel::HIGH);
    exit(1);
  }

  switch (value.type())
  {
  case Extensions::Extension::EXT_BYTE:
  {
      BYTE_ARRAY values;
      for (auto value : valueFromLexer)
      {

          values.push_back(utility::parserNumber<uint8_t, 0>(' ', &value));
      }
      value = std::move(values);
      break;
  }
  case Extensions::Extension::EXT_WORD:
  {
      WORD_ARRAY values;
      for (auto value : valueFromLexer)
      {

          values.push_back(utility::parserNumber<uint16_t, 0>(' ', &value));
      }
      value = std::move(values);
      break;
  }
  case Extensions::Extension::EXT_DWORD:
  {
      DWORD_ARRAY values;
      for (auto value : valueFromLexer)
      {

          values.push_back(utility::parserNumber<uint32_t, 0>(' ', &value));
      }
      value = std::move(values);
      break;
  }
  case Extensions::Extension::EXT_QWORD:
  {
      QWORD_ARRAY values;
      for (auto value : valueFromLexer)
      {

          values.push_back(utility::parserNumber<uint64_t, 0>(' ', &value));
      }
      value = std::move(values);
      break;
  }
  case Extensions::Extension::EXT_CHAR:
  {
    std::string str = valueFromLexer[0];
    value = std::move(str);
    break;
  }
  default:
      break;
  }

  item.value_ = std::move(value);
  rDataSec.put(item);
}

bool DataSectionParser::isArrayDeclaration(const std::string &line) const
{
  return ((line.find("[") != std::string::npos) && (line.find("]") != std::string::npos));
}

bool DataSectionParser::isStringDeclaration(const std::string &line) const
{
  return ((line.find("\"") != std::string::npos) && (line.find("\"") != std::string::npos));
}

std::string DataSectionParser::isTypeSpecified(const std::string &line)
{
  const auto posOfSpaceBetweenTypeAndName = line.find_first_of(" ");
  std::string arrayType;

  if (posOfSpaceBetweenTypeAndName != std::string::npos)
  {
    arrayType = line.substr(0, posOfSpaceBetweenTypeAndName);
    arrayType = utility::trim_copy(arrayType);

    if (arrayType.empty())
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". No type specified for variable or array declaration", logger::LogLevel::HIGH);
      exit(1);
    }
  }

  return arrayType;
}

ValueType DataSectionParser::getSpecifiedType(const std::string &line)
{
  const auto type = isTypeSpecified(line);
  return utility::returnTypeForString(type);
}

std::string DataSectionParser::getArrayName(const std::string &line)
{
  const auto nameStart = line.find_first_of(" ") + 1;
  const auto nameEnd = line.find_first_of("[") - 1;

  auto arrayName = line.substr(nameStart, nameEnd - nameStart + 1);
  arrayName = utility::trim_copy(arrayName);

  if (arrayName.empty())
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Empty name specified for array", logger::LogLevel::HIGH);
    exit(1);
  }

  return arrayName;
}

std::string DataSectionParser::getVariableName(const std::string &line)
{
  const auto nameStart = line.find_first_of(" ") + 1;
  const auto nameEnd = line.find_first_of("=") - 1;

  auto variableName = line.substr(nameStart, nameEnd - nameStart + 1);
  variableName = utility::trim_copy(variableName);

  if (variableName.empty())
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Empty name specified for array", logger::LogLevel::HIGH);
    exit(1);
  }

  return variableName;
}

std::pair<bool, std::vector<std::string>> DataSectionParser::getArrayValueForLexer(const std::string &line)
{
  std::vector<std::string> values;

  const auto posOfAssignSign = line.find_first_of("=");
  const bool isAssignSignPresent = (posOfAssignSign != std::string::npos);

  std::size_t offset = posOfAssignSign;
  if (!isAssignSignPresent)
  {
    offset = line.find_first_of("]");
  }
  const auto valueStart = offset + 1;

  std::string valueStr = line.substr(valueStart, line.size() - valueStart);
  valueStr = utility::trim_copy(valueStr);

  if (isAssignSignPresent && valueStr.empty())
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Wrong array declaration. Empty value specified after '=' sign", logger::LogLevel::HIGH);
    exit(1);
  }

  // TODO: Pack into trailingCharacterCheck(character) function
  if (valueStr.size() > 0 && valueStr.find_last_of(",") == valueStr.size() - 1)
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Trailing \',\' at the end of the line", logger::LogLevel::HIGH);
    exit(1);
  }

  utility::tokenize(valueStr, values);
  for (auto &value : values)
  {
    value = utility::trim_copy(value);
  }

  const std::size_t commaCount = std::count(valueStr.begin(), valueStr.end(), ',');

  if (values.size() - 1 != commaCount)
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Values should be separated by \',\'", logger::LogLevel::HIGH);
    exit(1);
  }

  return std::make_pair(isAssignSignPresent, values);
}

std::pair<bool, std::vector<std::string>>
DataSectionParser::getStringValueForLexer(const std::string &line)
{
  std::vector<std::string> result;

  const auto posOfAssignSign = line.find_first_of("=");
  const bool isAssignSignPresent = (posOfAssignSign != std::string::npos);

  std::size_t valueEnd{0};
  std::size_t offset = posOfAssignSign;
  if (!isAssignSignPresent)
  {
    offset = line.find_first_of("]");
  }
  else
  {
    offset = line.find_first_of("\"");
    if (offset == std::string::npos)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Missing opening \" in string value specification", logger::LogLevel::HIGH);
      exit(1);
    }

    valueEnd = line.find_last_of("\"");
    if (valueEnd == std::string::npos)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Missing closing \" in string value specification", logger::LogLevel::HIGH);
      exit(1);
    }
    valueEnd -= 1;
  }
  const auto valueStart = offset + 1;

  std::string valueStr = line.substr(valueStart, valueEnd - valueStart);
  valueStr = utility::trim_copy(valueStr);

  result.push_back(valueStr);

  return std::make_pair(isAssignSignPresent, result);
}

std::pair<bool, char> DataSectionParser::getCharValueForLexer(const std::string &line)
{
  char result;

  const auto posOfAssignSign = line.find_first_of("=");
  const bool isAssignSignPresent = (posOfAssignSign != std::string::npos);

  std::size_t valueEnd{0};
  std::size_t offset = posOfAssignSign;
  if (!isAssignSignPresent)
  {
    // WARNING: This is temporary solution
    std::size_t whitespacePos = line.find_first_of(" ");
    if (whitespacePos == std::string::npos)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Wrong declaration of variable", logger::LogLevel::HIGH);
      exit(1);
    }

    std::size_t nameStart = whitespacePos + 1;
    while (line[nameStart] == ' ')
    {
      nameStart++;
    }

    whitespacePos = line.find_first_of(' ', whitespacePos);
    offset = whitespacePos;
  }
  else
  {
    offset = line.find_first_of("\'");
    if (offset == std::string::npos)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Missing opening \' in character value specification", logger::LogLevel::HIGH);
      exit(1);
    }

    valueEnd = line.find_last_of("\'");
    if (valueEnd == std::string::npos)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Missing closing \' in character value specification", logger::LogLevel::HIGH);
      exit(1);
    }
    valueEnd -= 1;
  }
  const auto valueStart = offset + 1;

  std::string valueStr = line.substr(valueStart, valueEnd - valueStart + 1);

  if (isAssignSignPresent && valueStr.size() != 1)
  {
    ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Invalid value specified for char", logger::LogLevel::HIGH);
    exit(1);
  }

  result = valueStr[0];

  return std::make_pair(isAssignSignPresent, result);
}

std::pair<bool, std::size_t> DataSectionParser::getArraySize(const std::string &line)
{
  std::size_t size{0};
  bool isSizeSpecified{false};

  const std::size_t startOfSize = line.find_first_of("[") + 1;
  const std::size_t endOfSize = line.find_first_of("]") - 1;

  std::string sizeStr = line.substr(startOfSize, endOfSize - startOfSize + 1);
  sizeStr = utility::trim_copy(sizeStr);

  if (!sizeStr.empty())
  {
    if (!utility::is_number(sizeStr))
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Size of array should be non-negative integer", logger::LogLevel::HIGH);
      exit(1);
    }

    size = std::stoul(sizeStr);
    isSizeSpecified = true;
  }

  return std::make_pair(isSizeSpecified, size);
}
