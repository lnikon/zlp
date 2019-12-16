#pragma once

#include <memory>

#include "common.hpp"
#include "lexer.hpp"
#include "parser_defs.hpp"
#include "logger.hpp"

struct Parser
{
  explicit Parser(logger::LoggerSPtr pLogger);
  ~Parser() = default;

  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;

  Parser(Parser &&) = delete;
  Parser &operator=(Parser &&) = delete;

  void parse(const std::string &inputFilename);

  StackSection getStackSection() const;
  DataSection getDataSection() const;
  CodeSection getCodeSection() const;
  MainSection getMainSection() const;

private:
  using LexerPtr = std::unique_ptr<Lexer>;
  LexerPtr pLexer_{nullptr};

  logger::LoggerSPtr ps_logger_{nullptr};

  /*
   * Main Sections
   */
  StackSection stackSec_{};
  DataSection dataSec_{};
  CodeSection codeSec_{};
  MainSection mainSec_{};

  /*
   * Utilities for semantic checks
   */

  /*
   * Check DataSection semantics
   */
  bool checkDataSection(const DataSection &dataSec) const;
  bool staticTypeCheck(const DataSection &dataSec) const;
  bool isExpessionTypeSupported(ValueType type) const;

  /*
  * Pointer to instace of shared logger.
  * Usually set by parent which is @CompilerPipelines
  */
};
