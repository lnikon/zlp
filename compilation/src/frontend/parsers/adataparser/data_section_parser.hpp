#pragma once

#include "parser_defs.hpp"
#include "logger.hpp"

#include <fstream>

class DataSectionParser final
{
public:
    explicit DataSectionParser(logger::LoggerSPtr pLogger);
    ~DataSectionParser() = default;

    DataSectionParser(const DataSectionParser &) = delete;
    DataSectionParser &operator=(const DataSectionParser &) = delete;

    DataSectionParser(DataSectionParser &&) = delete;
    DataSectionParser &operator=(DataSectionParser &&) = delete;

    DataSection parse(std::fstream &inputStream);

    void setLineNumber(int lineNumber) { lineNumber_ = lineNumber; }
    int getLineNumber() const { return lineNumber_; }

private:
    /*
     * Synchronized logger
     */
    logger::LoggerSPtr ps_logger_{nullptr};

    /*
     * Symbol table for data section
     */
    SimpleSymbolTable dataTable_{};

    int lineNumber_{0};

    /*
     * Data section parsing routines
     */
    void parseVariable(DataSection &rDataSec, std::string line);
    void parseArray(DataSection &rDataSec, std::string line);
    bool isArrayDeclaration(const std::string &line) const;
    bool isStringDeclaration(const std::string &line) const;
    std::string isTypeSpecified(const std::string &line);
    ValueType getSpecifiedType(const std::string &line);
    std::string getArrayName(const std::string &line);
    std::string getVariableName(const std::string &line);

    std::pair<bool, std::vector<std::string>>
    getArrayValueForLexer(const std::string &line);

    std::pair<bool, std::vector<std::string>>
    getStringValueForLexer(const std::string &line);

    std::pair<bool, char> getCharValueForLexer(const std::string &line);

    std::pair<bool, std::size_t> getArraySize(const std::string &line);
};
