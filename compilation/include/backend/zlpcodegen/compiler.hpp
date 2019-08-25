#pragma once

#include "translator_defs.hpp"
#include "translator.hpp"

struct Compiler final
{
  Compiler();

  Compiler(const Compiler&) = delete;
  Compiler operator=(const Compiler&) = delete;

  void setCodeSection(const CodeSection& codeSec);

  bool compile();

  private:
  // Holder for different chain model translators
  UniqueTransPtr translator_{nullptr};

  CodeSection codeSec_{};
};
