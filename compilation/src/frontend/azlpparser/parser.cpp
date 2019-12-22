#include "common.hpp"
#include "vm_config.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "stack_section_parser_utilities.hpp"
#include "data_section_parser_utilities.hpp"

#include <string>

Parser::Parser(logger::LoggerSPtr pLogger)
    : ps_logger_{pLogger}
{
  pLexer_ = std::make_unique<Lexer>(ps_logger_);
}

void Parser::parse(const std::string &inputFilename)
{
  std::fstream inputStream(inputFilename);
  if (!inputStream.is_open())
  {
    ps_logger_->printMessage("Unable to open file", logger::LogLevel::HIGH);
    exit(1);
  }
  else
  {
    ps_logger_->printMessage("Parsing input file", logger::LogLevel::INFO);
  }

  StackSection stackSec = pLexer_->parseStackSection(inputStream);
  const bool isStackSectionOk
          = StackSectionParserUtilities::checkStackSection(stackSec, ps_logger_);
  if (!isStackSectionOk)
  {
    ps_logger_->
            printMessage("StackSection is incorrect. Please review your code",
                         logger::LogLevel::HIGH);
    exit(1);
  }
  stackSec_ = stackSec;

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if (!inputStream.is_open())
  {
    ps_logger_->printMessage("Unable to open file", logger::LogLevel::HIGH);
    exit(1);
  }

  DataSection dataSec = pLexer_->parseDataSection(inputStream);
  const bool isDataSectionOk =
          DataSectionParserUtilities::checkDataSection(dataSec, ps_logger_);
  if (!isDataSectionOk)
  {
    ps_logger_->
            printMessage("DataSection is incorrect. Please, "
                         "review your code or &*() yourself",
                         logger::LogLevel::HIGH);
//    exit(1);
  }
  dataSec_ = dataSec;

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if (!inputStream.is_open())
  {
    ps_logger_->printMessage("Unable to open file", logger::LogLevel::HIGH);
    exit(1);
  }

  CodeSection codeSec = pLexer_->parseCodeSection(inputStream);
  codeSec_ = codeSec;

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if (!inputStream.is_open())
  {
    ps_logger_->printMessage("Unable to open file", logger::LogLevel::HIGH);
    exit(1);
  }

  inputStream.close();
  inputStream.clear();
  inputStream.seekg(0, std::ios::beg);
  inputStream.open(inputFilename);
  if (!inputStream.is_open())
  {
    ps_logger_->printMessage("Unable to open file", logger::LogLevel::HIGH);
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
