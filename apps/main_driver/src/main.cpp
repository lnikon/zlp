#include "main_utils.hpp"
#include "code_generator.hpp"

#include <iostream>
#include <string>
#include <set>

/*
* A temporary solution for input arguments parsing.
* Don't threat this shit serious...
*/
struct SimpleProgramArgumentParser
{
    std::vector<std::string> parseInputFilenames(int argc, char *argv[])
    {
        std::vector<std::string> inputFilenames;

        for(int c = 2; c < argc; ++c)
        {
            inputFilenames.emplace_back(std::string{argv[c]});
        }       

        return inputFilenames;
    }
};

void printUsage()
{
    std::cout << "Usage: ./czpl -input <filename1>.zpl <filename2>.zpl ...\n";
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printUsage();
        exit(1);
    }

    SimpleProgramArgumentParser simpleProgramArgumentParser;

    auto inputFilenames = simpleProgramArgumentParser.parseInputFilenames(argc, argv);

    CodeGenerator codeGen;
    codeGen.setInputFilenames(std::move(inputFilenames));
    codeGen.build();

    return 0;
}
