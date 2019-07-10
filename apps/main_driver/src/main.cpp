#include "main_utils.hpp"
#include "parser.hpp"

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

    const std::string inputFilename = argv[1];

    Parser parser;
    parser.parse(inputFilename);

    return 0;

}
