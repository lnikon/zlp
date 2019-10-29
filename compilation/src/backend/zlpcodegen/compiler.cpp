#include "compiler.hpp"
#include "logger.hpp"

#include <fstream>

Compiler::Compiler()
    : translator_{ std::make_unique<ns_translator::Translator>() }
{ }

void Compiler::setDataSection(const DataSection& dataSec)
{
    dataSec_ = dataSec;
}

void Compiler::setDataSection(DataSection&& dataSec)
{
    dataSec_ = std::move(dataSec);
}

void Compiler::setCodeSection(const CodeSection& codeSec)
{
    codeSec_ = codeSec;
}

void Compiler::setCodeSection(CodeSection&& codeSec)
{
    codeSec_ = std::move(codeSec);
}

ns_compilation_unit::CompilationUnitSPtr Compiler::compile()
{
    auto dataBytesOpt = std::make_optional(ns_translator::byte_vec_t{});
    if (!dataBytesOpt.has_value())
    {
        Logger::printMessage("Error during compilation of data section", LogLevel::HIGH);
        return nullptr;
    }

    auto codeBytesOpt = translator_->translate(codeSec_);
    if (!codeBytesOpt.has_value())
    {
        Logger::printMessage("Error during compilation of code section", LogLevel::HIGH);
        return nullptr;
    }

    auto codeBytesValue = codeBytesOpt.value();
    auto dataBytesValue = dataBytesOpt.value();

    return ns_compilation_unit::make_shared(std::move(dataBytesValue), std::move(codeBytesValue));
}
