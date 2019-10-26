#pragma once

#include "translator_defs.hpp"
#include "interface_translator.hpp"
#include "generic_translator_impl.hpp"

#include <memory>

namespace ns_translator {
using namespace ns_interface_translator;

struct Translator final
{
    Translator();

    Translator(const Translator&) = delete;
    Translator& operator=(const Translator&) = delete;

    Translator(Translator&&) noexcept = delete;
    Translator& operator=(Translator&&) noexcept = delete;

    /*
     * Sets implementation for a translator
     */
    void setTranslator(UniqueTransImplPtr&& transPtr);

    /*
     * Translates code section into byte_tcode
     */
    TranslationResult translate(const CodeSection& codeSec);

private:
    UniqueTransImplPtr pTransImpl_{nullptr};
};

} // namespace ns_translator
