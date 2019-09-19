#pragma once

#include "compiler.hpp"
#include <memory>

struct CompilationPipeline
{
    CompilationPipeline();
    void operator()(const std::string& filename);

    private:
    CompilerUPtr pu_Compiler_{nullptr};
};

using CPipelineUPtr = std::unique_ptr<CompilationPipeline>;
using CPipelineSPtr = std::shared_ptr<CompilationPipeline>;
using CPipelineWPtr = std::weak_ptr<CompilationPipeline>;