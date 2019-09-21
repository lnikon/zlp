#include "compilation_pipeline.hpp"
#include "parser.hpp"

CompilationPipeline::CompilationPipeline(const std::string &filename, logger::PrinterSPtr pPrinter)
    : pu_compiler_{std::make_unique<Compiler>()},
      s_filename_{filename},
      ps_logger_{std::make_shared<logger::Logger>(pPrinter, filename)}
{
}

// Compilation pipelines goes here
std::pair<bool, ByteVec> CompilationPipeline::operator()()
{
    // Input - Assembly
    // Output - IR
    auto parser = Parser{ps_logger_};
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
    if (!ok)
    {
        ps_logger_->printMessage(s_filename_ + ": Compilation did not succeed\n", logger::LogLevel::HIGH);
        return std::make_pair(false, ByteVec{});
    }

    ps_logger_->printMessage("Compilation of " + s_filename_+ " succeeded\n", logger::LogLevel::INFO);

    return std::make_pair(ok, bytevec);
}