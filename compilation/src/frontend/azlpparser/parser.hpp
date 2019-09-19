#pragma once

#include <memory>

#include "common.hpp"
#include "lexer.hpp"
#include "parser_defs.hpp"

struct Parser
{
  Parser();
  void parse(const std::string& inputFilename);

  StackSection   getStackSection() const;
  DataSection    getDataSection()  const;
  CodeSection    getCodeSection()  const;
  MainSection    getMainSection()  const;

  static ValueType returnTypeForString(const std::string& type);
  static std::string returnStringForType(const ValueType type);

  private:
  using LexerPtr = std::unique_ptr<Lexer>;
  LexerPtr      pLexer_{nullptr};

  /*
   * Main Sections
   */
  StackSection  stackSec_{};
  DataSection   dataSec_{};
  CodeSection   codeSec_{};
  MainSection   mainSec_{};



  /*
   * Utilities for semantic checks
   */

  /*
   * Check DataSection semantics
   */
  bool checkDataSection(const DataSection& dataSec)       const;
  bool staticTypeCheck(const DataSection& dataSec)        const;
  bool isExpessionTypeSupported(ValueType type)           const;

};
