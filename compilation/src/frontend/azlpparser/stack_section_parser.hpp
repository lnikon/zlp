#pragma once

#include "parser_defs.hpp"
#include <fstream>

class StackSectionParser
{
    public:
        StackSection parse(std::fstream& inputStream);

        void setLineNumber(int lineNumber) { lineNumber_ = lineNumber; }
        int getLineNumber() const { return lineNumber_; }

    private:
        std::size_t lineNumber_{0};

        bool parseStackSize(StackSection& rStackSec, std::string line);
        void setDefaultStackSize(StackSection& rStackSec);
};
