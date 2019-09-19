#pragma once

#include "common.hpp"
#include "instruction.hpp"

struct Label
{
  std::string       name_{};
  std::size_t       instrIndex_{}; 
};
using LabelList = std::vector<Label>;

