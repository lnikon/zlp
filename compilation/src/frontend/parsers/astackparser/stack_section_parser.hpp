#pragma once

#include "parser_defs.hpp"
#include "logger.hpp"

#include <fstream>

class StackSectionParser
{
public:
    explicit StackSectionParser(logger::LoggerSPtr pLogger);
    ~StackSectionParser() = default;

    StackSectionParser(const StackSectionParser&) = delete;
    StackSectionParser& operator=(const StackSectionParser&) = delete;

    StackSectionParser(StackSectionParser&&) = delete;
    StackSectionParser& operator=(StackSectionParser&&) = delete;

    StackSection parse(std::fstream &inputStream);

    void setLineNumber(int lineNumber) { lineNumber_ = lineNumber; }
    int getLineNumber() const { return lineNumber_; }

private:
    /*
    * Synchronized logger
    */
    logger::LoggerSPtr ps_logger_{nullptr};
    
    std::size_t lineNumber_{0};

    bool parseStackSize(StackSection &rStackSec, std::string line);
    void setDefaultStackSize(StackSection &rStackSec);
};
