#pragma once

#include "translator_defs.hpp"
#include "interface_translator.hpp"
#include "generic_translator_impl.hpp"

#include "compilation_unit.hpp"
#include "code_translator.hpp"

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
     * Setter for compilation unit
     */
    void setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompilationUnit);

    /*
     * Translates code section into byte_tcode
     */
    TranslationResult translate(const CodeSection& codeSec);
    TranslationResult translate(const DataSection& codeSec);

private:
    /*
     * Stores shared compilation unit.
     * Translators for different sections will modify
     * symbol table for current compilation unit
     * through this pointer
     */
    ns_compilation_unit::CompilationUnitSPtr ps_compilationUnit_{nullptr};

    /*
     * Translator for code section
     */
    ns_code_translator::CodeTranslatorSPtr ps_codeTranslator_{nullptr};

    UniqueTransImplPtr pTransImpl_{nullptr};
};

} // namespace ns_translator
