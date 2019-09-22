#include "code_generator.hpp"
#include "compilation_pipeline.hpp"
#include "logger.hpp"

CodeGenerator::CodeGenerator()
    : ps_printer_{std::make_shared<logger::Printer>()},
      ps_logger_{std::make_shared<logger::Logger>(ps_printer_, "Code Generator")}
{
}

void CodeGenerator::build()
{
    if (svec_inputFilenames_.empty())
    {
        ps_logger_->printMessage("Empty compilation filename list specified.\nNothing to do here", logger::LogLevel::HIGH);
        return;
    }

    // For now, use a single thread approach for compilation
    // But for the future, this process can be easly parallelized

    // A simple pipline for compilation
    // 1. Open the file
    // 2. Parse it
    // 3. Get internal representation
    // 4. Pass internal representation to the compiler
    // 5. Get binary code from compiler
    // 6. Write it to the output 'object file' using 'binary writer'
    // 7. Repeat starting from step @1 as there are files that are didn't compiled

    for (const auto &inputFilename : svec_inputFilenames_)
    {
        vec_pipelines_.emplace_back(std::thread(CompilationPipeline{inputFilename, ps_printer_}));
    }

    for (auto &piplineThread : vec_pipelines_)
    {
        if (piplineThread.joinable())
        {
            piplineThread.join();
        }
    }
}

void CodeGenerator::setInputFilenames(std::vector<std::string> &&inputFilenames)
{
    svec_inputFilenames_ = std::move(inputFilenames);
}

void CodeGenerator::setInputFilenames(const std::vector<std::string> &inputFilenames)
{
    svec_inputFilenames_ = inputFilenames;
}
