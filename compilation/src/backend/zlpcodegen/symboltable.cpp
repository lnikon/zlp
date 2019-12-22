#include "symboltable.hpp"

#include <algorithm>
#include <iterator>

decltype(auto) symbol_ns::SymbolTable::findSymbolByName(symbol_ns::SymbolTable::symbol_name_cref_t name) const
{
    auto byName = [&name](const auto& symbol)
    {
        return symbol.name_ == name;
    };

    return std::find_if(std::begin(symbols_), std::end(symbols_), byName);
}

std::optional<symbol_ns::SymbolTable::symbol_index_t>
symbol_ns::SymbolTable::index(symbol_ns::SymbolTable::symbol_name_cref_t name) const
{
    if(symbols_.empty())
    {
        return std::nullopt;
    }

    auto itSym = findSymbolByName(name);
    if(itSym == std::end(symbols_))
    {
        return std::nullopt;
    }

    return std::distance(std::begin(symbols_), itSym) - 1;
}

std::optional<symbol_ns::Symbol>
symbol_ns::SymbolTable::get(symbol_ns::SymbolTable::symbol_name_cref_t name) const
{
    if(symbols_.empty())
    {
        return std::nullopt;
    }

    auto itSym = findSymbolByName(name);
    if(itSym == std::end(symbols_))
    {
        return std::nullopt;
    }

    return std::make_optional(*itSym);
}

std::optional<symbol_ns::Symbol>
symbol_ns::SymbolTable::get(symbol_ns::SymbolTable::symbol_index_t index) const
{
    if(index >= symbols_.size())
    {
        return std::nullopt;
    }

    return std::make_optional(symbols_[index]);
}

std::optional<symbol_ns::SymbolTable::symbol_index_t>
symbol_ns::SymbolTable::put(symbol_ns::symbol_cref_t symbol)
{
    symbols_.emplace_back(symbol);

    return symbols_.size() - 1;
}

std::optional<symbol_ns::SymbolTable::symbol_index_t>
symbol_ns::SymbolTable::put(symbol_ns::symbol_rref_t symbol)
{
    symbols_.emplace_back(std::move(symbol));

    return symbols_.size() - 1;
}

std::size_t
symbol_ns::SymbolTable::count() const noexcept
{
    return symbols_.size();
}

std::size_t
symbol_ns::SymbolTable::last() const noexcept
{
    return count() - 1;
}
