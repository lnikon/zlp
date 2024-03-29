#include <utility>

#include "lexer.hpp"
#include "parser.hpp"
#include "lexer_defs.hpp"
#include "utility.hpp"
#include "logger.hpp"
#include "debug.hpp"

Lexer::Lexer(logger::LoggerSPtr pLogger)
  : ps_logger_{pLogger},
    stackSectionParser_{ps_logger_},
    dataSectionParser_{ps_logger_},
    codeSectionParser_{ps_logger_}
{

}

StackSection Lexer::parseStackSection(std::fstream& inputStream)
{
    stackSectionParser_.setLineNumber(lineNumber_);

    StackSection stackSection = stackSectionParser_.parse(inputStream);

    lineNumber_ = stackSectionParser_.getLineNumber();

    return stackSection;
}

DataSection Lexer::parseDataSection(std::fstream& inputStream)
{
    dataSectionParser_.setLineNumber(lineNumber_);

    DataSection dataSection = dataSectionParser_.parse(inputStream);

    lineNumber_ = dataSectionParser_.getLineNumber();

    return dataSection;
}

CodeSection Lexer::parseCodeSection(std::fstream& inputStream)
{
  codeSectionParser_.setLineNumber(lineNumber_);

  CodeSection codeSec = codeSectionParser_.parse(inputStream);

  lineNumber_ = codeSectionParser_.getLineNumber();

  return codeSec;
}

MainSection Lexer::parseMainSection(std::fstream& inputStream)
{
  MainSection mainSec;

  return mainSec;
}

void Lexer::parseMainFunction(MainSection& rMainSec)
{
}

