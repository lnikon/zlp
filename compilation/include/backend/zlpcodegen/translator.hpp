#pragma once

#include "translator_defs.hpp"
#include "interface_translator_impl.hpp"
#include "generic_translator_impl.hpp"

#include <memory>

struct Translator final
{
  Translator();

  Translator(const Translator&) = delete;
  Translator& operator=(const Translator&) = delete;

  void setTranslator(UniqueTransImplPtr&& transPtr);

  TranslationResult translate(const CodeSection& codeSec);

  private:
  UniqueTransImplPtr  pTransImpl_{nullptr};
};
