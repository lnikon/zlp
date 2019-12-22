#ifndef LINKER_H
#define LINKER_H

#include "compilation_unit.hpp"

#include <unordered_map>
#include <string>

class Linker
{
public:
    Linker() = default;
    ~Linker() = default;

    Linker(const Linker&) = delete;
    Linker& operator=(const Linker&) = delete;

    Linker(Linker&&) = delete;
    Linker& operator=(Linker&&) = delete;

    ns_compilation_unit::CompilationUnitSPtr link(ns_compilation_unit::CompilationUnitSPtrVec units);

    /*
     * Private data
     */
private:
    std::unordered_map<std::string, std::size_t> symTbl_{};

    /*
     * Private methods
     */
private:
    void insertBinaryHeader(ns_compilation_unit::CompilationUnitSPtr);
    void merge(ns_compilation_unit::CompilationUnitSPtr result, ns_compilation_unit::CompilationUnitSPtrVec units);
    void resolve(ns_compilation_unit::CompilationUnitSPtr);

};

#endif // LINKER_H
