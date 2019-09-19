#pragma once

#include "compilation_pipeline.hpp"

#include <vector>

struct CompilationPipelineController
{

    private:
    std::vector<CPipelineUPtr> pu_pipelines_{};
};