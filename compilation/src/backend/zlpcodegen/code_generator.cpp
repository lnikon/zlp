#include "code_generator.hpp"
#include "logger.hpp"

void CodeGenerator::build()
{
    if(inputFilenames_.empty())
    {
        Logger::printMessage("\nEmpty compilation filename list specified.\nNothing to do here...\n", LogLevel::HIGH);
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

    for(const auto& inputFilename : inputFilenames_)
    {
        
    }
}

void CodeGenerator::setInputFilenames(std::vector<std::string>&& inputFilenames)
{
    inputFilenames_ = std::move(inputFilenames);
}

void CodeGenerator::setInputFilenames(const std::vector<std::string>& inputFilenames)
{
    inputFilenames_ = inputFilenames;
}
