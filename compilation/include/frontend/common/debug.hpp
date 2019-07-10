#pragma once

#define DEBUG_MODE

#ifdef DEBUG_MODE
#include <iostream>
#include "logger.hpp"
#include "parser.hpp"
#include "parser_defs.hpp"
#include "array.hpp"
#include "utility.hpp"
#endif

inline void printStackSection(const StackSection& stackSec)
{
#ifdef DEBUG_MODE
  std::string stackInfo;
  stackInfo += "Stack Size: " + std::to_string(stackSec.size_) + "\n";

  Logger::printMessage(stackInfo, LogLevel::DEBUG);
  std::cout << std::endl;
#endif
}

// TODO: Pack into specilied function with multiple argument handling
inline void printArray(const Array& array)
{
#ifdef DEBUG_MODE
  const std::string prefix = "\n<ArrayInfo: ";

  std::string padding = std::string(prefix.size(), '-');
  padding += "> ";

  const std::string postfix = "\nEND ArrayInfo>";

  std::string arrayInfo;
  arrayInfo += prefix 
    + "\n" 
    + padding 
    + "name_ = " 
    + array.name_ 

    + "\n" 
    + padding 
    + "type_ = "
    + Parser::returnStringForType(array.type_)

    + "\n" 
    + padding 
    + "isSizeSpecified_ = " 
    + utility::convertBoolToString(array.isSizeSpecified_)

    + "\n" 
    + padding 
    + "size_ = " 
    + std::to_string(array.size_) 

    + "\n" 
    + padding 
    + "valueFromLexer_.size = "
    + std::to_string(array.valueFromLexer_.size())

    + "\n" 
    + padding 
    + "valueFromLexer_ = "
    + utility::convertVectorOfStringToString(array.valueFromLexer_)

    + postfix;

  Logger::printMessage(arrayInfo, LogLevel::DEBUG);
  std::cout << std::endl;
#endif
}

inline void printVariable(const Variable& variable)
{
#ifdef DEBUG_MODE
  const std::string prefix = "\n<VariableInfo: ";

  std::string padding = std::string(prefix.size(), '-');
  padding += "> ";

  const std::string postfix = "\nEND VariableInfo>";

  std::string variableInfo;
  variableInfo += prefix 
    + "\n" 
    + padding 
    + "name_ = " 
    + variable.name_ 

    + "\n" 
    + padding 
    + "type_ = "
    + Parser::returnStringForType(variable.type_)

    + "\n" 
    + padding 
    + "valueFromLexer_ = "
    + variable.valueFromLexer_
    
    + "\n" 
    + padding 
    + "value_ = "
    + std::to_string(variable.value_)
    
    + "\n" 
    + padding 
    + "charValue_ = "
    + std::string(1, variable.charValue_)

    + postfix;

  Logger::printMessage(variableInfo, LogLevel::DEBUG);
  std::cout << std::endl;
#endif
}
