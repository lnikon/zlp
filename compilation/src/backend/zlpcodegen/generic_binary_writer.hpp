#pragma once

#include "compilation_unit.hpp"
#include "symboltable.hpp"

#include <memory>

enum class SectionType : std::size_t
{
    ST_INFO = 0,
    ST_CODE,
    ST_DATA,
    ST_SYMTBL,
    ST_RELOCTBL,

    ST_END_OF_ENUM
};

struct SectionInfo
{
    SectionType	type_;
    std::size_t	addr_;
    std::size_t size_;
};

struct HeaderSection
{
    static constexpr const int sectionsCount = static_cast<int>(SectionType::ST_END_OF_ENUM);
    SectionInfo sections_[sectionsCount];
};

struct Symbol
{
    bool        isFunc_{0};
    symbol_ns::symbol_value_type_t valueType_{symbol_ns::symbol_value_type_t::EXT_NULL};
    symbol_ns::symbol_type_t type_{symbol_ns::symbol_type_t::ST_UNKOWN};
    std::size_t base_{0};
    std::size_t size_{0};
    std::size_t namePos_{0};
    std::size_t nameSize_{0};
};

struct SymbolTableSection
{
    static constexpr const std::size_t type = static_cast<std::size_t>(SectionType::ST_SYMTBL);
    std::size_t entryPoint_{std::numeric_limits<uint32_t>::max()};
    std::size_t count_{0};
    Symbol symbols_[];
};

struct ProgramInfoSection
{
    static constexpr const std::size_t type = static_cast<std::size_t>(SectionType::ST_INFO);
    std::size_t codeBase_{0};
    std::size_t dataBase_{0};
    std::size_t stackSize_{0};
    std::size_t programStart_{0};
};

struct RelocationTableSection
{
    static constexpr const std::size_t type = static_cast<std::size_t>(SectionType::ST_RELOCTBL);
    std::size_t count_{0};
    std::size_t relocs_[];
};

struct GenericBinaryWriter
{
    GenericBinaryWriter(ns_compilation_unit::CompilationUnitSPtr pCompUnit,
                        const std::string& crName);

    GenericBinaryWriter(const GenericBinaryWriter&) = default;
    GenericBinaryWriter(GenericBinaryWriter&&) noexcept = default;

    GenericBinaryWriter& operator=(const GenericBinaryWriter&) = default;
    GenericBinaryWriter& operator=(GenericBinaryWriter&&) noexcept = default;

    void write();

private:
    ns_compilation_unit::CompilationUnitSPtr pCompUnit_{nullptr};
    std::string name_{};
};

using GenericBinWriterSPtr = std::shared_ptr<GenericBinaryWriter>;
using GenericBinWriterUPtr = std::unique_ptr<GenericBinaryWriter>;
using GenericBinWriterWPtr = std::weak_ptr<GenericBinaryWriter>;
