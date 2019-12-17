#pragma once

#include "translator_defs.hpp"
#include "parser_defs.hpp"
#include "function.hpp"
#include "instruction.hpp"
#include "compilation_unit.hpp"

namespace ns_code_translator {

struct CodeTranslator final
{
    using TranslationResult = ns_translator::TranslationResult;

<<<<<<< HEAD
    /*
     * Translator for code section
     */
=======
    CodeTranslator() = default;

    CodeTranslator(const CodeTranslator&) = delete;
    CodeTranslator& operator=(const CodeTranslator&) = delete;

    CodeTranslator(CodeTranslator&&) noexcept = delete;
    CodeTranslator& operator=(CodeTranslator&&) noexcept = delete;

>>>>>>> 77b1e954693f5f816f54ca57563049e9cf9d4f04
    TranslationResult translate(const CodeSection& crCodeSec);

    /*
     * Setter for compilation unit
     */
    void setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompUnit);

    /*
     * Private data
     */
private:
    ns_compilation_unit::CompilationUnitSPtr ps_compUnit_{nullptr};

    /*
     * Private methods
     */
private:
    TranslationResult translate(const Function& func);
    TranslationResult translate(const InstructionList& instrList);
    TranslationResult translate(const Instruction& instr);
};

using CodeTranslatorUPtr = std::unique_ptr<CodeTranslator>;
using CodeTranslatorSPtr = std::shared_ptr<CodeTranslator>;
using CodeTranslatorWPtr = std::weak_ptr<CodeTranslator>;

template <typename... Args>
constexpr inline auto make_unique(Args&&... args)
{
    return std::make_unique<CodeTranslator>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr inline auto make_shared(Args&&... args)
{
    return std::make_shared<CodeTranslator>(std::forward<Args>(args)...);
}

} // namespace ns_code_translator
