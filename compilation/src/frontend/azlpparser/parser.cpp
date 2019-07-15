#include "common.hpp"
#include "vm_config.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "stack_section_parser_utilities.hpp"
#include "data_section_parser_utilities.hpp"

Parser::Parser()
{
  pLexer_ = std::make_unique<Lexer>();
}

void Parser::parse(const std::string& inputFilename)
{
  std::fstream inputStream(inputFilename);
  if(!inputStream.is_open())
  {
    Logger::printMessage("Unable to open file " + inputFilename, LogLevel::HIGH);
    exit(1);
  }

  StackSection stackSec = pLexer_->parseStackSection(inputStream);
  const bool isStackSectionOk = StackSectionParserUtilities::checkStackSection(stackSec);
  if(!isStackSectionOk)
  {
    Logger::printMessage("StackSection is incorrect. Please review your code.\n", LogLevel::HIGH);
    exit(1);
  }
  stackSec_ = stackSec;

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if(!inputStream.is_open())
  {
    Logger::printMessage("Unable to open file " + inputFilename, LogLevel::HIGH);
    exit(1);
  }

  DataSection dataSec = pLexer_->parseDataSection(inputStream);
  const bool isDataSectionOk = DataSectionParserUtilities::checkDataSection(dataSec);
  if(!isDataSectionOk)
  {
    Logger::printMessage("DataSection is incorrect. Please review your code.\n", LogLevel::HIGH);
    exit(1);
  }
  dataSec_ = dataSec;

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if(!inputStream.is_open())
  {
    Logger::printMessage("Unable to open file " + inputFilename, LogLevel::HIGH);
    exit(1);
  }

  CodeSection codeSec = pLexer_->parseCodeSection(inputStream);
  codeSec_ = codeSec;

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if(!inputStream.is_open())
  {
    Logger::printMessage("Unable to open file " + inputFilename, LogLevel::HIGH);
    exit(1);
  }

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if(!inputStream.is_open())
  {
    Logger::printMessage("Unable to open file " + inputFilename, LogLevel::HIGH);
    exit(1);
  }

  MainSection mainSec = pLexer_->parseMainSection(inputStream);
  mainSec_ = mainSec;
}

StackSection Parser::getStackSection() const
{
  return stackSec_;
}

DataSection Parser::getDataSection() const
{
  return dataSec_;
}

CodeSection Parser::getCodeSection() const
{
  return codeSec_;
}

MainSection Parser::getMainSection() const
{
  return mainSec_;
}

ValueType Parser::returnTypeForString(const std::string& type)
{
  if(type == "CHAR")
  {
    return ValueType::EXT_CHAR;
  }
  else if(type == "BYTE") 
  {
    return ValueType::EXT_BYTE;
  }
  else if(type == "WORD")
  {
    return ValueType::EXT_WORD;
  }
  else if(type == "DWORD")
  {
    return ValueType::EXT_DWORD;
  }
  else if(type == "QWORD")
  {
    return ValueType::EXT_QWORD;
  }
  else
  {
    return ValueType::EXT_NULL;
  }
}

std::string Parser::returnStringForType(const ValueType type)
{
  switch(type)
  {
    case ValueType::EXT_CHAR:
      return std::string{"CHAR"};
    case ValueType::EXT_BYTE:
      return std::string{"BYTE"};
    case ValueType::EXT_WORD:
      return std::string{"WORD"};
    case ValueType::EXT_DWORD:
      return std::string{"DWORD"};
    case ValueType::EXT_QWORD:
      return std::string{"QWORD"};
    case ValueType::EXT_NULL:
    default:
      return std::string{"INVALID"};
  }
}
