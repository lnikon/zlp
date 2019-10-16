#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <vector>
#include <optional>
#include <functional>

namespace symbol_ns {

enum class symbol_type_t
{
    ST_UNKOWN = 0,
    ST_VAR,
    ST_ARR,
    ST_FUN,
    ST_LBL
};

struct Symbol
{
    using symbol_name_t          = std::string;
    using symbol_name_ref_t      = std::string&;
    using symbol_name_cref_t     = const std::string&;

    using symbol_address_t       = std::size_t;
    using symbol_size_t          = std::size_t;
    using symbol_index_t         = std::size_t;

    symbol_type_t       type_{symbol_type_t::ST_UNKOWN};
    symbol_name_t       name_{};
    symbol_address_t    address_{};
    symbol_size_t       size_{};
};
using symbol_vec_t          = std::vector<Symbol>;
using symbol_vec_ref_t      = std::vector<Symbol>&;
using symbol_vec_cref_t     = const std::vector<Symbol>&;

struct SymbolTable
{
    using symbol_name_t          = Symbol::symbol_name_t;
    using symbol_name_ref_t      = Symbol::symbol_name_ref_t;
    using symbol_name_cref_t     = Symbol::symbol_name_cref_t;
    using symbol_index_t         = Symbol::symbol_index_t;

    SymbolTable() = default;

    SymbolTable(const SymbolTable&) = default;
    SymbolTable& operator=(const SymbolTable&) = default;

    SymbolTable(SymbolTable&&) = default;
    SymbolTable& operator=(SymbolTable&&) = default;

    std::optional<symbol_index_t> getSymbolIndex(symbol_name_cref_t name) const;

private:
    /*
     * Actually, symbol table is simply a vector of symbols
     */
    symbol_vec_t symbols_{};

};

} // namespace symbol_ns

#endif // SYMBOLTABLE_H
