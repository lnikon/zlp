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

    std::for_each(std::begin(svec_inputFilenames_), std::end(svec_inputFilenames_), [this](const auto& inputFilename)
    {
        ps_vec_compUnitsFutures_.emplace_back(std::async(std::launch::async, CompilationPipeline{inputFilename, ps_printer_}));
    });

//    std::for_each(std::begin(svec_inputFilenames_), std::end(svec_inputFilenames_), [this](auto&&)
//    {
//        ps_vec_compUnitsPromises_.emplace_back(ns_compilation_unit::SPtrCompilationUnitPromise{});
//    });

//    std::for_each(std::begin(ps_vec_compUnitsPromises_), std::end(ps_vec_compUnitsPromises_), [this](auto& promise)
//    {
//        ps_vec_compUnitsFutures_.emplace_back(promise.get_future());
//    });

//    for(auto idx = 0u; idx < ps_vec_compUnitsPromises_.size(); ++idx)
//    {
//        /*
//         * Compilation of a single unit starts here
//         */
//        vec_pipelines_.emplace_back(std::thread(CompilationPipeline{svec_inputFilenames_[idx], ps_printer_}, std::ref(ps_vec_compUnitsPromises_[idx])));
//    }

//    for (auto &piplineThread : vec_pipelines_)
//    {
//        if (piplineThread.joinable())
//        {
//            piplineThread.join();
//        }
//    }

    auto compilationUnits = ns_compilation_unit::CompilationUnitSPtrVec{};
    for(auto& future : ps_vec_compUnitsFutures_)
    {
        auto compilationUnit = future.get();
        if(!compilationUnit)
        {
            ps_logger_->printMessage("Build process did not succeed on file " + compilationUnit->getName(), logger::LogLevel::HIGH);
            break;
        }

        compilationUnits.emplace_back(compilationUnit);
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
