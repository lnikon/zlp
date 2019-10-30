#pragma once

#include "translator_defs.hpp"
#include "parser_defs.hpp"
#include "function.hpp"
#include "instruction.hpp"

#include <utility>

namespace ns_interface_translator {

using namespace ns_translator;

/*
 * Generic interface for translators of different chain models.
 */
struct ITranslator
{
  virtual ~ITranslator() {}

  virtual TranslationResult translate(const CodeSection& codeSec) = 0;
};

} // namespace ns_interface_translator
