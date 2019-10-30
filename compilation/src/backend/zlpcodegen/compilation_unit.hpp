#pragma once

#include "symboltable.hpp"
#include "translator_defs.hpp"

#include <future>

namespace ns_compilation_unit
{

/*
 * Represents a code generation result of a single compilation pipeline.
 * Should be considered as a input to linker along with other
 * compilations units to do relocations and after produce a suitable,
 * well formed executable for our virtual machine.
 */
struct CompilationUnit
{
    CompilationUnit() = default;

    CompilationUnit(const CompilationUnit&) = default;
    CompilationUnit& operator=(const CompilationUnit&) = default;

    CompilationUnit(CompilationUnit&&) noexcept = default;
    CompilationUnit& operator=(CompilationUnit&&) noexcept = default;

    CompilationUnit(ns_translator::byte_vec_cref_t vec_data, ns_translator::byte_vec_cref_t vec_code);
    CompilationUnit(ns_translator::byte_vec_rref_t vec_data, ns_translator::byte_vec_rref_t vec_code) noexcept;

    /*
     * Setter/Getter pair for @name
     */
    std::string name() const;
    void setName(std::string_view name);

    /*
     * Getter for symbol table.
     * Returns shared pointer
     */
    symbol_ns::SymbolTableSPtr symbolTable() const;

    /*
     * Getter for compiled data
     */
    ns_translator::byte_vec_t data() const;

    /*
     * Getter for compiler code
     */
    ns_translator::byte_vec_t code() const;

private:
    std::string s_name_{};

    symbol_ns::SymbolTableSPtr ps_symbolTable_{symbol_ns::make_shared_symbol_table()};

    ns_translator::byte_vec_t vec_data_{};
    ns_translator::byte_vec_t vec_code_{};
};

using CompilationUnitUPtr    = std::unique_ptr<CompilationUnit>;
using CompilationUnitSPtr    = std::shared_ptr<CompilationUnit>;
using CompilationUnitSPtrVec = std::vector<CompilationUnitSPtr>;
using CompilationUnitWPtr    = std::weak_ptr<CompilationUnit>;

using SPtrCompilationUnitPromise     = std::promise<CompilationUnitSPtr>;
using SPtrCompilationUnitPromiseVec  = std::vector<SPtrCompilationUnitPromise>;

using SPtrCompilationUnitFuture      = std::future<CompilationUnitSPtr>;
using SPtrCompilationUnitFutureVec   = std::vector<SPtrCompilationUnitFuture>;

template <typename... Args>
constexpr inline auto make_unique(Args&&... args)
{
    return std::make_unique<CompilationUnit>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr inline auto make_shared(Args&&... args)
{
    return std::make_shared<CompilationUnit>(std::forward<Args>(args)...);
}

} // namespace ns_compilation_unit
