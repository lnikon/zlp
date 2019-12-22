#pragma once

#include "translator_defs.hpp"
#include "parser_defs.hpp"
#include "function.hpp"
#include "instruction.hpp"
#include "compilation_unit.hpp"

namespace ns_code_translator {

constexpr const std::size_t cmdMinLen = 2;
constexpr const std::size_t cmdMaxLen = 12;

struct CodeTranslator final
{
    using TranslationResult = ns_translator::TranslationResult;


    /*
     * Translator for code section
     */

    CodeTranslator(SimpleSymbolTable& symblTbl,
                   std::vector<std::size_t>& varToSymblIndex,
                   std::vector<std::size_t>& funcToSymblIndex);

    CodeTranslator(const CodeTranslator&) = delete;
    CodeTranslator& operator=(const CodeTranslator&) = delete;

    CodeTranslator(CodeTranslator&&) noexcept = delete;
    CodeTranslator& operator=(CodeTranslator&&) noexcept = delete;

    void translate(const CodeSection& crCodeSec, const DataSection& crDataSec);

    /*
     * Setter for compilation unit
     */
    void setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompUnit);

    /*
     * Private data
     */
private:
    ns_compilation_unit::CompilationUnitSPtr ps_compUnit_{nullptr};
    SimpleSymbolTable& symblTbl_;
    std::vector<std::size_t>& varToSymblIndex_;
    std::vector<std::size_t>& funcToSymblIndex_;

    /*
     * Private methods
     */
private:
    std::size_t translate(const Function& func, const DataSection& crDataSec, std::size_t& rCodeSecOffset);
    TranslationResult translate(const InstructionList& instrList, const DataSection& crDataSec);
    TranslationResult translate(const Instruction& instr, const DataSection& crDataSec);
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
