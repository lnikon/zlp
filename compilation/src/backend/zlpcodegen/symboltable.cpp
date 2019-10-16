#include "symboltable.hpp"

#include <algorithm>
#include <iterator>

std::optional<symbol_ns::SymbolTable::symbol_index_t>
symbol_ns::SymbolTable::getSymbolIndex(symbol_ns::SymbolTable::symbol_name_cref_t name) const
{
    if(symbols_.empty())
    {
        return std::nullopt;
    }

    auto byName = [&name](const auto& symbol)
    {
        return symbol.name_ == name;
    };

    auto itSym = std::find_if(std::begin(symbols_), std::end(symbols_), byName);
    if(itSym == std::end(symbols_))
    {
        return std::nullopt;
    }

    return std::distance(std::begin(symbols_), itSym) - 1;
}
