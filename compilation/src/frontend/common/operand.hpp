#pragma once

#include <vector>

#include "common.hpp"
#include "type_defs.hpp"
#include "immediate_value.hpp"

/* Types of operands */
enum class OperandType
{
    OT_NULL = 0,    // Default value
    OT_REG,         // Register index
    OT_ARG,         // Address reg index
    OT_IMV,         // Immediate value, used only with 'assign' command
    OT_REG_ARG,     // REG or ARG(for example AN/RN)
    //OT_FUN,       // Function index
    //OT_LBL,       // Label index
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
/* NOTE: Use words 'argument' and 'operand' interchangeably */
struct Operand
{
    OperandType type_{ OperandType::OT_NULL };
    std::size_t index_{ 0 };

    ImmediateValue imv_{};

    bool operator==(const Operand& other)
    {
        return type_ == other.type_;
    }

    bool operator!=(const Operand& other)
    {
        return !(*this == other);
    }
};
using OperandList = std::vector<Operand>;
