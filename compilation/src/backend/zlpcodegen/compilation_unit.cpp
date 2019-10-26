#include "compilation_unit.hpp"

ns_compilation_unit::CompilationUnit::CompilationUnit(ns_translator::byte_vec_cref_t vec_data, ns_translator::byte_vec_cref_t vec_code)
    : vec_data_{vec_data},
      vec_code_{vec_code} { }

ns_compilation_unit::CompilationUnit::CompilationUnit(ns_translator::byte_vec_rref_t vec_data, ns_translator::byte_vec_rref_t vec_code) noexcept
    : vec_data_{std::move(vec_data)},
      vec_code_{std::move(vec_code)} { }

std::string ns_compilation_unit::CompilationUnit::getName() const
{
    return s_name_;
}
