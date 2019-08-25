#include "main_utils.hpp"
#include "parser.hpp"
#include "compiler.hpp"

#include <iostream>
#include <string>

void printUsage()
{
    std::cout << "Usage: ./czpl <filename>.zpl\n";
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printUsage();
        exit(1);
    }

    const std::string& inputFilename = argv[1];

    // Input - Assembly
    // Output - IR
    Parser parser;
    parser.parse(inputFilename);

    // Get IR for stack section
    const auto& stackSec = parser.getStackSection();

    // Get IR for data section
    const auto& dataSec = parser.getDataSection();

    // Get IR for code section
    const auto& codeSec = parser.getCodeSection();

    // Start compilation of a single compilation unit
    // TODO:  Pack these into FinalCompilationPhases,
    //        make compilation of each unit multithreaded
    Compiler compiler;
    compiler.setCodeSection(codeSec);
    compiler.compile();

    return 0;
}
