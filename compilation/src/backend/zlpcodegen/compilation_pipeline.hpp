#pragma once

#include "compiler.hpp"

#include <memory>
#include <fstream>

/*  Why do we need this class?
*   @CompilationPipeline takes responsibility for
*   1. Parsing file
*   2. Gathering Internal Representation(short IR)
*   3. Compilation of IR into bytecode for ZVM
*/

struct CompilationPipeline
{

    CompilationPipeline(const std::string &filename);

    /*
    * Compilation started via this operator
    */
    std::pair<bool, ByteVec> operator()();

private:
    /*
    * Each pipline shoud have exactly one compiler
    */
    CompilerUPtr pu_compiler_{nullptr};

    /*
    * Filename of Compilation Unit
    */
    std::string s_filename_{};

    /*
    * Stream associated with the Compilation Unit
    */
    std::fstream fs_file_;
};

using CPipelineUPtr = std::unique_ptr<CompilationPipeline>;
using CPipelineSPtr = std::shared_ptr<CompilationPipeline>;
using CPipelineWPtr = std::weak_ptr<CompilationPipeline>;