#include "compilation_pipeline.hpp"

CompilationPipeline::CompilationPipeline()
    : pu_Compiler_{std::make_unique<Compiler>()}
{

}

void CompilationPipeline::operator()(const std::string& filename)
{
    // Compilation pipelines goes here
}