#include "datatranslator.h"

#include <cstring>

ns_data_translator::DataTranslator::DataTranslator(SimpleSymbolTable& symblTbl,
                                                   std::vector<std::size_t>& varToSymblIndex)
    : symblTbl_(symblTbl),
      varToSymblIndex_(varToSymblIndex)
{

}

void
ns_data_translator::DataTranslator::translate(const DataSection& crDataSec)
{
    /*
     * Offset from data section
     */
    std::size_t dataSecOffset = 0;

    /*
     * Data items count
     */
    const auto count = std::distance(std::begin(crDataSec), std::end(crDataSec));

    /*
     * Reserve space for symbol indexes
     */
    varToSymblIndex_.reserve(static_cast<std::size_t>(count));

    /*
     * Store pointer to compilation unit symbol table
     */
    auto symblTbl = ps_compUnit_->symbolTable();

    /*
     * Last symbol index
     */
    std::size_t lastSym = 0;

    for (const auto& item : crDataSec)
    {
        symbol_ns::Symbol sym;

        sym.name_ = item.name_;
        sym.type_ = symbol_ns::symbol_type_t::ST_DATA;
        sym.valueType_ = item.value_.type();
        sym.size_ = 0;
        sym.address_ = 0;

        symblTbl_.emplace(sym.name_, lastSym);
        varToSymblIndex_.emplace_back(lastSym);

        if (item.value_.null())
        {
            continue;
        }

        const std::size_t reminder = dataSecOffset % item.value_.unitSize();
        if (reminder != 0)
        {
            dataSecOffset += item.value_.unitSize() - reminder;
        }

        const auto itemSize = item.value_.size();
        ps_compUnit_->vec_data_.reserve(dataSecOffset + itemSize);
        std::memcpy(&ps_compUnit_->vec_data_[dataSecOffset], item.value_, itemSize);

        sym.address_ = dataSecOffset;
        sym.size_ = item.value_.count();

        dataSecOffset += itemSize;

        /*
         * Add symbol to package level symbol table
         */
        symblTbl->put(std::move(sym));

        /*
         * Increment last symbol index
         */
        ++lastSym;
    }
}

void ns_data_translator::DataTranslator::setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompUnit)
{
    ps_compUnit_ = pCompUnit;
}
