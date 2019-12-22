#include "linker.h"
#include "symboltable.hpp"

#include <cstring>
#include <algorithm>
#include <numeric>

ns_compilation_unit::CompilationUnitSPtr
Linker::link(ns_compilation_unit::CompilationUnitSPtrVec units)
{
    auto pCompUnit = ns_compilation_unit::make_shared();
    insertBinaryHeader(pCompUnit);
    merge(pCompUnit, units);
    resolve(pCompUnit);

    return pCompUnit;
}

void
Linker::insertBinaryHeader(ns_compilation_unit::CompilationUnitSPtr)
{

}

void
Linker::merge(ns_compilation_unit::CompilationUnitSPtr result,
              ns_compilation_unit::CompilationUnitSPtrVec units)
{
    for (auto unit : units)
    {
        result->info_.stackSize_ = std::max(result->info_.stackSize_, unit->info_.stackSize_);

        std::size_t lastDataSize = result->vec_data_.size();
        std::size_t currDataSize = unit->vec_data_.size();
        std::size_t reminder = currDataSize % 16;
        std::size_t finaDatalSize
                = lastDataSize + currDataSize + (reminder == 0 ? 0 : 16 - reminder);

        result->vec_data_.resize(finaDatalSize);
        std::memcpy(&result->vec_data_[lastDataSize], &unit->vec_data_[0], currDataSize);
        if (reminder)
        {
            std::memset(&result->vec_data_[lastDataSize + currDataSize], 0, 16 - reminder);
        }

        std::size_t lastCodeSize = result->vec_code_.size();
        std::size_t currCodeSize = unit->vec_code_.size();
        std::size_t codeReminder = currCodeSize % 16;
        std::size_t finalCodeSize
                = lastCodeSize + currCodeSize + (codeReminder == 0 ? 0 : 16 - codeReminder);

        result->vec_code_.resize(finalCodeSize);
        std::memcpy(&result->vec_code_[lastCodeSize], &unit->vec_code_[0], currCodeSize);
        if (codeReminder)
        {
            std::memset(&result->vec_code_[lastCodeSize + currCodeSize], 0, 16 - codeReminder);
        }

        std::vector<std::size_t> symblIdxRemap(unit->symbolTable()->count());

        for (std::size_t symIdx = 0; symIdx < symblIdxRemap.size(); ++symIdx)
        {
            auto sym = unit->symbolTable()->get(symIdx);
            if (!sym.has_value())
            {
                exit(1);
            }

            const auto& symValue = sym.value();
            std::size_t shiftSize
                    = (symValue.type_ == symbol_ns::symbol_type_t::ST_CODE ?
                           lastCodeSize : lastDataSize);

            auto symIt = symTbl_.find(symValue.name_);
            if (symIt == symTbl_.end())
            {
                symbol_ns::symbol_t finalSym = symValue;
                finalSym.address_ += shiftSize;
                symblIdxRemap[symIdx] = result->symbolTable()->count();
                result->symbolTable()->put(finalSym);
                symTbl_.emplace(finalSym.name_, symblIdxRemap[symIdx]);
            }
            else
            {
                auto finalSym = result->symbolTable()->get(symIt->second);
                if (!finalSym.has_value())
                {
                    exit(1);
                }

                auto& finalSymValue = finalSym.value();
                if (symValue.address_ != std::numeric_limits<uint32_t>::max())
                {
                    finalSymValue.address_ = symValue.address_ + shiftSize;
                    finalSymValue.size_ = symValue.size_;
                }
                symblIdxRemap[symIdx] = symIt->second;
            }
        }

        auto relocMerge = [lastCodeSize, &result, &symblIdxRemap](
                          std::vector<std::size_t>& finalTbl,
                          const std::vector<std::size_t>& tbl)
        {
            std::size_t relocBase = finalTbl.size();
            finalTbl.reserve(relocBase + tbl.size());
            finalTbl.insert(finalTbl.end(), tbl.begin(), tbl.end());

            for (std::size_t i = relocBase; i < finalTbl.size(); ++i)
            {
                finalTbl[i] += lastCodeSize;
                std::size_t relAddr = finalTbl[i];
                std::size_t& symIdx = reinterpret_cast<std::size_t&>(result->vec_code_[relAddr]);
                symIdx = symblIdxRemap[symIdx];
            }
        };

        relocMerge(result->reloc_.relocations_, unit->reloc_.relocations_);

        if (unit->info_.entryPointIndex_ != std::numeric_limits<uint32_t>::max())
        {
            std::size_t entryPoint = symblIdxRemap[unit->info_.entryPointIndex_];
            if (result->info_.entryPointIndex_ != std::numeric_limits<uint32_t>::max() &&
                result->info_.entryPointIndex_ != entryPoint)
            {
                exit(1);
            }
            result->info_.entryPointIndex_ = entryPoint;
        }
    }
}

void
Linker::resolve(ns_compilation_unit::CompilationUnitSPtr pCompUnit)
{
    std::vector<std::size_t>& rReloc = pCompUnit->reloc_.relocations_;
    for (std::size_t offset : rReloc)
    {
        std::size_t* pAddr = reinterpret_cast<std::size_t*>(&pCompUnit->vec_code_[offset]);
        std::size_t symIdx = 0;
        std::memcpy(&symIdx, pAddr, sizeof(std::size_t));
        auto sym = pCompUnit->symbolTable()->get(symIdx);
        if (!sym.has_value())
        {
            exit(1);
        }

        auto& rSymValue = sym.value();
        if (rSymValue.address_ == std::numeric_limits<uint32_t>::max())
        {
            exit(1);
        }

        std::size_t symAddr = rSymValue.address_;
        if (rSymValue.type_ != symbol_ns::symbol_type_t::ST_CODE)
        {
            symAddr += pCompUnit->vec_code_.size();
        }
        std::memcpy(pAddr, &symAddr, sizeof(std::size_t));
    }
}
