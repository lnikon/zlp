#include "compilation_pipeline.hpp"
#include "logger.hpp"
#include "parser.hpp"

CompilationPipeline::CompilationPipeline(const std::string &filename)
    : pu_compiler_{std::make_unique<Compiler>()},
      s_filename_{filename}
//   fs_file_{s_filename_}
{
    // if(!fs_file_.is_open())
    // {
    // Logger::printMessage("Unable to open following Compilat Unit: " + filename, LogLevel::HIGH);
    // return;
    // }
}

// Compilation pipelines goes here
std::pair<bool, ByteVec> CompilationPipeline::operator()()
{
    // Input - Assembly
    // Output - IR
    Parser parser;
    parser.parse(s_filename_);

    // Get IR for stack section
    const auto &stackSec = parser.getStackSection();

    // Get IR for data section
    const auto &dataSec = parser.getDataSection();

    // Get IR for code section
    const auto &codeSec = parser.getCodeSection();

    pu_compiler_->setDataSection(dataSec);
    pu_compiler_->setCodeSection(codeSec);

    const auto [ok, bytevec] = pu_compiler_->compile();
    if(!ok)
    {
        Logger::printMessage("Compilation did not succeed\n", LogLevel::HIGH);
        return std::make_pair(false, ByteVec{});
    }

    return std::make_pair(ok, bytevec);
}