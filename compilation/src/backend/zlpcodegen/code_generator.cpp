#include "code_generator.hpp"
#include "compilation_pipeline.hpp"
#include "logger.hpp"
#include "linker.h"
#include "generic_binary_writer.hpp"

CodeGenerator::CodeGenerator()
    : ps_printer_{std::make_shared<logger::Printer>()},
      ps_logger_{std::make_shared<logger::Logger>(ps_printer_, "Code Generator")}
{
}

void CodeGenerator::build()
{
    if (svec_inputFilenames_.empty())
    {
        ps_logger_->printMessage("Empty compilation filename list specified.\nNothing to do here",
                                 logger::LogLevel::HIGH);
        return;
    }

    std::for_each(std::begin(svec_inputFilenames_), std::end(svec_inputFilenames_),
                  [this](const auto& inputFilename)
    {
        ps_vec_compUnitsFutures_.emplace_back(std::async(CompilationPipeline{inputFilename, ps_printer_}));
    });

    auto compilationUnits = ns_compilation_unit::CompilationUnitSPtrVec{};
    for(auto& future : ps_vec_compUnitsFutures_)
    {
        auto compilationUnit = future.get();
        if(!compilationUnit)
        {
            ps_logger_->printMessage("Build process did not succeed on file " + compilationUnit->info_.unitName_,
                                     logger::LogLevel::HIGH);
            break;
        }

        compilationUnits.emplace_back(compilationUnit);
    }

    while (compilationUnits.size() != ps_vec_compUnitsFutures_.size())
    {

    }

    Linker linker;
    auto pCompUnit = linker.link(compilationUnits);

    GenericBinaryWriter writer(pCompUnit, "output.zexe");
    writer.write();
}

void CodeGenerator::setInputFilenames(std::vector<std::string> &&inputFilenames)
{
    svec_inputFilenames_ = std::move(inputFilenames);
}

void CodeGenerator::setInputFilenames(const std::vector<std::string> &inputFilenames)
{
    svec_inputFilenames_ = inputFilenames;
}
