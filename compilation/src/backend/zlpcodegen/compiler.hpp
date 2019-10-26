#pragma once

#include "translator_defs.hpp"
#include "translator.hpp"
#include "compilation_unit.hpp"

#include <memory>

struct Compiler final
{
    Compiler();
    ~Compiler() = default;

    Compiler(const Compiler&) = delete;
    Compiler& operator=(const Compiler&) = delete;

    Compiler(Compiler&&) = delete;
    Compiler& operator=(Compiler&&) = delete;

    /*
    * Setter/Getter Methods
    */
    void setDataSection(const DataSection& codeSec);
    void setDataSection(DataSection&& codeSec);

    void setCodeSection(const CodeSection& codeSec);
    void setCodeSection(CodeSection&& codeSec);

    /*
    * Compilation Routines
    */
    ns_compilation_unit::CompilationUnitSPtr compile();

private:

    /*
     * Holder for different chain model translators
    */
    ns_translator::UniqueTransPtr translator_{nullptr};

    /*
    * Internal representations for input language
    */
    DataSection dataSec_{};
    CodeSection codeSec_{};
};

using CompilerUPtr = std::unique_ptr<Compiler>;
using CompilerSPtr = std::shared_ptr<Compiler>;
using CompilerWPtr = std::weak_ptr<Compiler>;
