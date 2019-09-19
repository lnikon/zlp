#pragma once

#include "parser_defs.hpp"
#include <fstream>

class DataSectionParser
{
  public:
    DataSection parse(std::fstream& inputStream);

    void setLineNumber(int lineNumber) { lineNumber_ = lineNumber; }
    int getLineNumber() const { return lineNumber_; }

  private:
    int lineNumber_{0};

    /*
     * Data section parsing routines 
     */
    void                          parseVariable(DataSection& rDataSec, std::string line);
    void                          parseArray(DataSection& rDataSec, std::string line);
    bool                          isArrayDeclaration(const std::string& line) const;
    bool                          isStringDeclaration(const std::string& line) const;
    std::string                   isTypeSpecified(const std::string& line);
    ValueType                     getSpecifiedType(const std::string& line);
    std::string                   getArrayName(const std::string& line);
    std::string                   getVariableName(const std::string& line);

    std::pair<bool, std::vector<std::string>>
        getArrayValueForLexer(const std::string& line);

    std::pair<bool, std::vector<std::string>>
        getStringValueForLexer(const std::string& line);

    std::pair<bool, char>         getCharValueForLexer(const std::string& line);

    std::pair<bool, std::size_t>  getArraySize(const std::string& line);


};
