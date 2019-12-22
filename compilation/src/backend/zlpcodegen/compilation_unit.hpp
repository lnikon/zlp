#pragma once

#include "symboltable.hpp"
#include "translator_defs.hpp"

#include <future>

namespace ns_compilation_unit
{

struct CompilationUnitInfo
{
    CompilationUnitInfo() = default;

    CompilationUnitInfo(const CompilationUnitInfo&) = default;
    CompilationUnitInfo& operator=(const CompilationUnitInfo&) = default;

    CompilationUnitInfo(CompilationUnitInfo&&) noexcept = default;
    CompilationUnitInfo& operator=(CompilationUnitInfo&&) noexcept = default;

    std::string unitName_{};
    std::size_t entryPointIndex_{std::numeric_limits<uint32_t>::max()};
    std::size_t stackSize_{};
};

struct RelocationInfo
{
    RelocationInfo() = default;

    RelocationInfo(const RelocationInfo&) = default;
    RelocationInfo& operator=(const RelocationInfo&) = default;

    RelocationInfo(RelocationInfo&&) noexcept = default;
    RelocationInfo& operator=(RelocationInfo&&) noexcept = default;

    std::vector<std::size_t> relocations_{};
};

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
     * Getter for symbol table.
     * Returns shared pointer
     */
    symbol_ns::SymbolTableSPtr symbolTable() const;

    ns_translator::byte_vec_t vec_data_{};
    ns_translator::byte_vec_t vec_code_{};
    CompilationUnitInfo info_{};
    RelocationInfo reloc_{};

private:
    symbol_ns::SymbolTableSPtr ps_symbolTable_{symbol_ns::make_shared_symbol_table()};

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
