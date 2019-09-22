#pragma once

#include <fstream>

#include "common.hpp"
#include "parser_defs.hpp"
#include "stack_section_parser.hpp"
#include "data_section_parser.hpp"
#include "code_section_parser.hpp"

struct Lexer final
{
  explicit Lexer(logger::LoggerSPtr pLogger);
  ~Lexer() = default;

  Lexer(const Lexer &) = delete;
  Lexer &operator=(const Lexer &) = delete;

  Lexer(Lexer &&) = delete;
  Lexer &operator=(Lexer &&) = delete;

  StackSection parseStackSection(std::fstream &inputStream);
  DataSection parseDataSection(std::fstream &inputStream);
  CodeSection parseCodeSection(std::fstream &inputStream);
  MainSection parseMainSection(std::fstream &inputStream);

  std::size_t lineNumber() const
  {
    return lineNumber_;
  }

private:
  /*
  * Synchronized logger
  */
  logger::LoggerSPtr ps_logger_{nullptr};

  /*
  * Parsers for general sections
  */
  StackSectionParser stackSectionParser_;
  DataSectionParser dataSectionParser_;
  CodeSectionParser codeSectionParser_;

  std::size_t lineNumber_{0};
  std::size_t functionCount_{0};

  /*
  * Stack section parsing routines
  */
  bool parseStackSize(StackSection &rStackSec, std::string line);
  void setDefaultStackSize(StackSection &rStackSec);

  /*
  * Main section parsing routines
  */
  void parseMainFunction(MainSection &rMainSec);
};
