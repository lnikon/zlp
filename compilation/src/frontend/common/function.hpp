#pragma once

#include "common.hpp"
#include "instruction.hpp"
#include "label.hpp"

struct Function
{
  std::string     name_{};
  InstructionList code_{};
  LabelList       labels_{};
  
  bool isForwardDeclared{false};
};
using FunctionList = std::vector<Function>;

