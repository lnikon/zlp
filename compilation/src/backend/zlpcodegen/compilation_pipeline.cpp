#include "compilation_pipeline.hpp"
#include "generic_binary_writer.hpp"
#include "parser.hpp"

CompilationPipeline::CompilationPipeline(const std::string &filename, logger::PrinterSPtr pPrinter)
    : pu_compiler_{std::make_unique<Compiler>()},
      pu_bin_writer_{std::make_unique<GenericBinaryWriter>(filename)},
      s_filename_{filename},
      ps_logger_{std::make_shared<logger::Logger>(pPrinter, filename)}
{
}

// Compilation pipelines goes here
std::optional<ByteVec> CompilationPipeline::operator()()
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

    const auto& bytevec = pu_compiler_->compile();
    if (!bytevec.has_value())
    {
        ps_logger_->printMessage(s_filename_ + ": Compilation did not succeed\n", logger::LogLevel::HIGH);
        return std::nullopt;
    }

    pu_bin_writer_->write(bytevec.value());

    ps_logger_->printMessage("Compilation of " + s_filename_ + " succeeded\n", logger::LogLevel::INFO);

    return std::nullopt;
}
