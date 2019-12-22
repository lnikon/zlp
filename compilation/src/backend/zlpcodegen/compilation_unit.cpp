#include "compilation_unit.hpp"

ns_compilation_unit::CompilationUnit::CompilationUnit(ns_translator::byte_vec_cref_t vec_data, ns_translator::byte_vec_cref_t vec_code)
    : vec_data_{vec_data},
      vec_code_{vec_code} { }

ns_compilation_unit::CompilationUnit::CompilationUnit(ns_translator::byte_vec_rref_t vec_data, ns_translator::byte_vec_rref_t vec_code) noexcept
    : vec_data_{std::move(vec_data)},
      vec_code_{std::move(vec_code)} { }

symbol_ns::SymbolTableSPtr ns_compilation_unit::CompilationUnit::symbolTable() const
{
  return ps_symbolTable_;
}
