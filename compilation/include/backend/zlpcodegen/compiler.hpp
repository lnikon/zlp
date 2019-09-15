#pragma once

#include "translator_defs.hpp"
#include "translator.hpp"

struct Compiler final
{
  Compiler();

  Compiler(const Compiler&) = delete;
  Compiler operator=(const Compiler&) = delete;

  void setDataSection(const DataSection& codeSec);
  void setCodeSection(const CodeSection& codeSec);

  std::pair<bool, ByteVec> compile();

  private:
  // Holder for different chain model translators
  UniqueTransPtr translator_{nullptr};

  DataSection dataSec_{};
  CodeSection codeSec_{};
  
};
