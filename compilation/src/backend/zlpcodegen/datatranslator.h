#pragma once

#include "translator_defs.hpp"
#include "parser_defs.hpp"
#include "function.hpp"
#include "instruction.hpp"
#include "compilation_unit.hpp"

namespace ns_data_translator {

struct DataTranslator final
{
    /*
     * Shortcuts
     */
    using TranslationResult = ns_translator::TranslationResult;

    /*
     * Translator for data section
     */
    DataTranslator(SimpleSymbolTable& symblTbl, std::vector<std::size_t>& varToSymblIndex);

    DataTranslator(const DataTranslator&) = delete;
    DataTranslator& operator=(const DataTranslator&) = delete;

    DataTranslator(DataTranslator&&) noexcept = delete;
    DataTranslator& operator=(DataTranslator&&) noexcept = delete;

    void translate(const DataSection& crDataSec);

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

    /*
     * Private methods
     */
private:
};

using DataTranslatorUPtr = std::unique_ptr<DataTranslator>;
using DataTranslatorSPtr = std::shared_ptr<DataTranslator>;
using DataTranslatorWPtr = std::weak_ptr<DataTranslator>;

template <typename... Args>
constexpr inline auto make_unique(Args&&... args)
{
    return std::make_unique<DataTranslator>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr inline auto make_shared(Args&&... args)
{
    return std::make_shared<DataTranslator>(std::forward<Args>(args)...);
}

} // namespace ns_code_translator
