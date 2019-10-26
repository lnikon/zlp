#pragma once

#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <memory>

namespace symbol_ns {

enum class symbol_type_t : uint8_t
{
    ST_UNKOWN = 0,
    ST_DATA,
    ST_CODE,
    ST_ENUM_END
};

struct Symbol
{
    using symbol_name_t          = std::string;
    using symbol_name_ref_t      = std::string&;
    using symbol_name_cref_t     = const std::string&;

    using symbol_address_t       = std::size_t;
    using symbol_size_t          = std::size_t;
    using symbol_index_t         = std::size_t;

    Symbol() = default;

    Symbol(const Symbol&) = default;
    Symbol& operator=(const Symbol&) = default;

    Symbol(Symbol&&) noexcept = default;
    Symbol& operator=(Symbol&&) noexcept = default;

    symbol_type_t       type_{symbol_type_t::ST_UNKOWN};
    symbol_name_t       name_{};
    symbol_address_t    address_{};
    symbol_size_t       size_{};
};
using symbol_t              = Symbol;
using symbol_ref_t          = Symbol&;
using symbol_rref_t         = Symbol&;
using symbol_cref_t         = const Symbol&;
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

    /*
     * Return index of a symbol by a given name
     */
    std::optional<symbol_index_t>   index(symbol_name_cref_t name) const;

    /*
     * Return symbol by a given name
     */
    std::optional<Symbol>           get(symbol_name_cref_t name) const;

    /*
     * Return symbol by a given index
     */
    std::optional<Symbol>           get(symbol_index_t index) const;

    /*
     * Put lvalue symbol into table
     */
    std::optional<symbol_index_t>   put(symbol_cref_t symbol);

    /*
     * Put rvalue symbol into table
     */
    std::optional<symbol_index_t>   put(symbol_rref_t symbol);

private:
    /*
     * Actually, symbol table is simply a vector of symbols
     */
    symbol_vec_t symbols_{};

    /*
     * Utility functions
     */
    decltype(auto) findSymbolByName(symbol_name_cref_t name) const;
};

using SymbolTableUPtr = std::unique_ptr<SymbolTable>;
using SymbolTableSPtr = std::shared_ptr<SymbolTable>;
using SymbolTableWPtr = std::weak_ptr<SymbolTable>;

template <typename... Args>
constexpr inline auto make_unique_symbol(Args... args)
{
    return std::make_unique<Symbol>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr inline auto make_shared_symbol(Args... args)
{
    return std::make_shared<Symbol>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr inline auto make_unique_symbol_table(Args... args)
{
    return std::make_unique<SymbolTable>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr inline auto make_shared_symbol_table(Args... args)
{
    return std::make_shared<SymbolTable>(std::forward<Args>(args)...);
}


} // namespace symbol_ns
