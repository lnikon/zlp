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
    /*
     * Create compilation unit which
     * will be filled by translator and returned
     */
    auto compUnit = ns_compilation_unit::make_shared();

    /*
     * Update translator to work with correct compilation unit
     */
    translator_->setCompilationUnit(compUnit);

    /*
     * Compile data section and setup symbol table for compilation unit
     */
    translator_->translate(dataSec_);

    /*
     * Compile code section and setup symbol table for compilation unit
     */
    translator_->translate(codeSec_, dataSec_);

    return compUnit;
}
