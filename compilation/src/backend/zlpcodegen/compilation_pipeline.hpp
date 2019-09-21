#pragma once

#include "compiler.hpp"
#include "logger.hpp"

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

    explicit CompilationPipeline(const std::string &filename, logger::PrinterSPtr pLogger);

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
    * This class spends time on synchronization of std::cout 
    * with other instances
    */
    logger::LoggerSPtr ps_logger_{nullptr};
};

using CPipelineUPtr = std::unique_ptr<CompilationPipeline>;
using CPipelineSPtr = std::shared_ptr<CompilationPipeline>;
using CPipelineWPtr = std::weak_ptr<CompilationPipeline>;