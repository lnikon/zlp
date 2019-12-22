#include "generic_binary_writer.hpp"

#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstring>

GenericBinaryWriter::GenericBinaryWriter(ns_compilation_unit::CompilationUnitSPtr pCompUnit,
                                         const std::string& crName)
    : pCompUnit_{pCompUnit},
      name_{crName}
{

}

void GenericBinaryWriter::write()
{
    ProgramInfoSection infoSec;
    infoSec.stackSize_ = pCompUnit_->info_.stackSize_;

    const std::size_t symbolTableSize = sizeof(SymbolTableSection);
    const std::size_t symbolSize = sizeof(Symbol);

    std::size_t bufferSize = symbolTableSize;
    bufferSize += symbolSize * pCompUnit_->symbolTable()->count();
    std::size_t bufferMarker = bufferSize;
    for (std::size_t i = 0; i < pCompUnit_->symbolTable()->count(); ++i)
    {
        bufferSize
                += sizeof(std::string::value_type)
                   * (pCompUnit_->symbolTable()->get(i)->name_.size() + 1);
    }

    if (bufferSize % 16 != 0)
    {
        bufferSize += 16 - bufferSize % 16;
    }

    std::vector<uint8_t> symbolBuff((std::size_t)bufferSize, (uint8_t)0);

//    uint8_t* symbolBuff = new uint8_t[bufferSize];
//    const std::size_t symBuffSize = bufferSize;

    uint8_t* pSymBuff = &symbolBuff[0];
    SymbolTableSection& rSymSec = reinterpret_cast<SymbolTableSection&>(*pSymBuff);
//    SymbolTableSection rSymSec;
    rSymSec.entryPoint_ = pCompUnit_->info_.entryPointIndex_;
    rSymSec.count_ = pCompUnit_->symbolTable()->count();
//    rSymSec.symbols_.resize(rSymSec.count_);
    for (std::size_t idx = 0; idx < pCompUnit_->symbolTable()->count(); ++idx)
    {
        auto symOpt = pCompUnit_->symbolTable()->get(idx);
        if (!symOpt.has_value())
        {
            continue;
        }

        auto& sym = symOpt.value();

        rSymSec.symbols_[idx].isFunc_ = (sym.type_ == symbol_ns::symbol_type_t::ST_CODE);
        rSymSec.symbols_[idx].valueType_ = sym.valueType_;
        rSymSec.symbols_[idx].base_ = sym.address_;
        rSymSec.symbols_[idx].size_ = sym.size_;
        rSymSec.symbols_[idx].namePos_ = bufferMarker;
        rSymSec.symbols_[idx].nameSize_ = sym.name_.size();

        std::size_t strSize = sizeof(std::string::value_type) * (sym.name_.size() + 1);
        std::memcpy(&symbolBuff[bufferMarker], sym.name_.data(), strSize);
        bufferMarker += strSize;
    }

    const std::size_t relocTblSize = sizeof(RelocationTableSection);

    bufferSize = relocTblSize;
    bufferSize += sizeof(std::size_t) * pCompUnit_->reloc_.relocations_.size();
    if (bufferSize % 16 != 0)
    {
        bufferSize += 16 - bufferSize % 16;
    }

    std::vector<uint8_t> relocTblBuff((size_t)bufferSize, (uint8_t)0);
    uint8_t* const pRelocTblBuff = &relocTblBuff[0];
    RelocationTableSection& relocTblSctn
            = reinterpret_cast<RelocationTableSection&>(*pRelocTblBuff);
    for (std::size_t idx = 0; idx < relocTblSctn.count_; ++idx)
    {
        relocTblSctn.relocs_[idx] = pCompUnit_->reloc_.relocations_[idx];
    }

    HeaderSection hdr;
    const std::size_t hdrSize = sizeof(HeaderSection);
    std::size_t outputMarker = hdrSize;

    std::size_t secIdx = 0;

    secIdx = static_cast<std::size_t>(SectionType::ST_INFO);
    const std::size_t progInfoSecSize = sizeof(ProgramInfoSection);
    hdr.sections_[secIdx].type_ = SectionType::ST_INFO;
    hdr.sections_[secIdx].addr_ = outputMarker;
    hdr.sections_[secIdx].size_ = progInfoSecSize;
    outputMarker += hdr.sections_[secIdx].size_;

    secIdx = static_cast<std::size_t>(SectionType::ST_CODE);
    hdr.sections_[secIdx].type_ = SectionType::ST_CODE;
    hdr.sections_[secIdx].addr_ = outputMarker;
    hdr.sections_[secIdx].size_ = pCompUnit_->vec_code_.size();
    outputMarker += hdr.sections_[secIdx].size_;

    secIdx = static_cast<std::size_t>(SectionType::ST_DATA);
    hdr.sections_[secIdx].type_ = SectionType::ST_DATA;
    hdr.sections_[secIdx].addr_ = outputMarker;
    hdr.sections_[secIdx].size_ = pCompUnit_->vec_data_.size();
    outputMarker += hdr.sections_[secIdx].size_;

    secIdx = static_cast<std::size_t>(SectionType::ST_SYMTBL);
    hdr.sections_[secIdx].type_ = SectionType::ST_SYMTBL;
    hdr.sections_[secIdx].addr_ = outputMarker;
    hdr.sections_[secIdx].size_ = symbolBuff.size();
    outputMarker += hdr.sections_[secIdx].size_;

    secIdx = static_cast<std::size_t>(SectionType::ST_RELOCTBL);
    hdr.sections_[secIdx].type_ = SectionType::ST_RELOCTBL;
    hdr.sections_[secIdx].addr_ = outputMarker;
    hdr.sections_[secIdx].size_ = relocTblBuff.size();
    outputMarker += hdr.sections_[secIdx].size_;

    std::fstream executable("/home/nikon/projects/zlp/build/apps/main_driver/src/output.zexe",
                            std::fstream::binary | std::fstream::in | std::fstream::out);
    if (!executable.is_open())
    {
        exit(1);
    }

    executable.write((char const*)&hdr, hdrSize);
    executable.write((char const*)&infoSec, progInfoSecSize);
    executable.write((char const*)pCompUnit_->vec_code_.data(), pCompUnit_->vec_code_.size());
    executable.write((char const*)pCompUnit_->vec_data_.data(), pCompUnit_->vec_data_.size());
    executable.write((char const*)symbolBuff.data(), symbolBuff.size());
    executable.write((char const*)relocTblBuff.data(), relocTblBuff.size());
}
