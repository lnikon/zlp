#pragma once

#include "translator_defs.hpp"
#include "parser_defs.hpp"
#include "function.hpp"
#include "instruction.hpp"
#include "compilation_unit.hpp"

namespace ns_instruction_translator {


struct InstructionTranslator final
{
    using TranslationResult = ns_translator::TranslationResult;

    /*
     * Translator for code section
     */

    InstructionTranslator(SimpleSymbolTable& symblTbl,
                   std::vector<std::size_t>& varToSymblIndex,
                   std::vector<std::size_t>& funcToSymblIndex,
                   std::vector<std::size_t>& lblReloc);

    InstructionTranslator(const InstructionTranslator&) = delete;
    InstructionTranslator& operator=(const InstructionTranslator&) = delete;

    InstructionTranslator(InstructionTranslator&&) noexcept = delete;
    InstructionTranslator& operator=(InstructionTranslator&&) noexcept = delete;

    /*
     * Setter for compilation unit
     */
    void setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompUnit);

    /*
     * Translator
     */
    std::size_t translate(const Instruction& instr, std::size_t codeSecOffset);

    /*
     * Private data
     */
private:
    ns_compilation_unit::CompilationUnitSPtr ps_compUnit_{nullptr};
    SimpleSymbolTable& symblTbl_;
    std::vector<std::size_t>& varToSymblIndex_;
    std::vector<std::size_t>& funcToSymblIndex_;
    std::vector<std::size_t>& lblReloc_;

    /*
     * Private methods
     */
private:
};

using InstructionTranslatorUPtr = std::unique_ptr<InstructionTranslator>;
using InstructionTranslatorSPtr = std::shared_ptr<InstructionTranslator>;
using InstructionTranslatorWPtr = std::weak_ptr<InstructionTranslator>;

template <typename... Args>
constexpr inline auto make_unique(Args&&... args)
{
    return std::make_unique<InstructionTranslator>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr inline auto make_shared(Args&&... args)
{
    return std::make_shared<InstructionTranslator>(std::forward<Args>(args)...);
}

} // namespace ns_code_translator
