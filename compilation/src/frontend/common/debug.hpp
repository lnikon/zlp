#pragma once

#define DEBUG_MODE

#ifdef DEBUG_MODE
#include <iostream>

#include "logger.hpp"
#include "parser_defs.hpp"
#include "array.hpp"
#include "utility.hpp"
#include "instruction.hpp"
#endif

namespace debug
{

inline void print(const StackSection &stackSec, logger::LoggerSPtr pLogger)
{
#ifdef DEBUG_MODE

  std::string stackInfo;
  stackInfo += "Stack Size: " + std::to_string(stackSec.size_) + "\n";

  pLogger->printMessage(stackInfo, logger::LogLevel::DEBUG);

#endif
}

// TODO: Pack into specilied function with multiple argument handling
inline void print(const Array &array, logger::LoggerSPtr pLogger)
{
#ifdef DEBUG_MODE

  const std::string prefix = "\n<ArrayInfo: ";

  std::string padding = std::string(prefix.size(), '-');
  padding += "> ";

  const std::string postfix = "\nEND ArrayInfo>";

  std::string arrayInfo;
  arrayInfo += prefix + "\n" + padding + "name_ = " + array.name_

               + "\n" + padding + "type_ = " + utility::returnStringForType(array.type_)

               + "\n" + padding + "isSizeSpecified_ = " + utility::convertBoolToString(array.isSizeSpecified_)

               + "\n" + padding + "size_ = " + std::to_string(array.size_)

               + "\n" + padding + "valueFromLexer_.size = " + std::to_string(array.valueFromLexer_.size())

               + "\n" + padding + "valueFromLexer_ = " + utility::convertVectorOfStringToString(array.valueFromLexer_)

               + postfix;

  pLogger->printMessage(arrayInfo, logger::LogLevel::DEBUG);
  
#endif
}

inline void print(const Variable &variable, logger::LoggerSPtr pLogger)
{
#ifdef DEBUG_MODE
  const std::string prefix = "\n<VariableInfo: ";

  std::string padding = std::string(prefix.size(), '-');
  padding += "> ";

  const std::string postfix = "\nEND VariableInfo>";

  std::string variableInfo;
  variableInfo += prefix + "\n" + padding + "name_ = " + variable.name_

                  + "\n" + padding + "type_ = " + utility::returnStringForType(variable.type_)

                  + "\n" + padding + "valueFromLexer_ = " + variable.valueFromLexer_

                  + "\n" + padding + "value_ = " + std::to_string(variable.value_)

                  + "\n" + padding + "charValue_ = " + std::string(1, variable.charValue_)

                  + postfix;

  pLogger->printMessage(variableInfo, logger::LogLevel::DEBUG);

#endif
}

inline void printInstruction(const Instruction &instr, logger::LoggerSPtr pLogger)
{
#ifdef DEBUG_MODE

  const std::string prefix = "\n<InstructionInfo: ";

  std::string padding = std::string(prefix.size(), '-');
  padding += "> ";

  const std::string postfix = "\nEND InstructionInfo>";

  std::string variableInfo;
  variableInfo += prefix;

#endif
}

} // namespace debug
