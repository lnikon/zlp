#pragma once

#include "translator_defs.hpp"
#include "interface_translator.hpp"
#include "generic_translator_impl.hpp"

#include "compilation_unit.hpp"
#include "code_translator.hpp"
#include "datatranslator.h"

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
     * Setter for compilation unit
     */
    void setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompilationUnit);

    /*
     * Translates code section into byte_tcode
     */
    void translate(const CodeSection& codeSec, const DataSection& dataSec);
    void translate(const DataSection& dataSec);

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

    /*
     * Translator for data section
     */
    ns_data_translator::DataTranslatorSPtr ps_dataTranslator_{nullptr};

    /*
     * Mappings and symbol table
     */
    SimpleSymbolTable symbolTbl_{};
    std::vector<std::size_t> varToSymblIndex_{};
    std::vector<std::size_t> funcToSymblIndex_{};
};

} // namespace ns_translator
