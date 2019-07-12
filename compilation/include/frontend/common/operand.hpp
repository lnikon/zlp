#pragma once

#include <vector>

#include "common.hpp"
#include "type_defs.hpp"

/* Types of operands */
enum class OperandType
{
  REG = 0,  // Register index
  FUN,      // Function index
  LBL,      // Label index
  ZNULL,    // Default value
};

/* Instruction can have at most 3 arguments */
constexpr auto MAX_ARG_CNT = 3u;
enum ArgPos
{
    First = 0,
    Second,
    Third
};

/* Value and type for operand */
struct Operand
{
    OperandType type_{ OperandType::ZNULL };
    std::size_t index_{ 0 };
};

using OperandList = std::vector<Operand>;

