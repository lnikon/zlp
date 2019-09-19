#pragma once

#include <memory>

#include "translator_defs.hpp"
#include "translator.hpp"

struct Compiler final
{

  Compiler();
  ~Compiler() = default;

  Compiler(const Compiler&) = delete;
  Compiler& operator=(const Compiler&) = delete;

  Compiler(Compiler&&) = delete;
  Compiler& operator=(Compiler&&) = delete;

  /*
  * Setter/Getter Methods
  */
  void setDataSection(const DataSection& codeSec);
  void setCodeSection(const CodeSection& codeSec);

  /*
  * Compilation Routines
  */
  std::pair<bool, ByteVec> compile();

  private:

  /*
  * Holder for different chain model translators
  */
  UniqueTransPtr translator_{nullptr};

  /*
  * Internal representations for input language
  */
  DataSection dataSec_{};
  CodeSection codeSec_{};

};

using CompilerUPtr = std::unique_ptr<Compiler>;
using CompilerSPtr = std::shared_ptr<Compiler>;
using CompilerWPtr = std::weak_ptr<Compiler>;