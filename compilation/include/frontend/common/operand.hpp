#pragma once

#include <vector>

#include "common.hpp"
#include "type_defs.hpp"

/* Types of operands */
enum class OperandType
{
    OT_NULL = 0,    // Default value
    OT_REG,         // Register index
    OT_ARG,         // Address reg index
    OT_IMM,         // Immediate value, used only with 'assign' command
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

    // Tagged union trick... yeah I'm an old guy :)
    union 
    {
      // This filed will be used almost by all commands
      std::size_t index_{ 0 };

      /* These are for 'assign' command */
      int8_t i8;
      uint8_t ui8;

      int16_t i16;
      uint16_t ui16;

      // i32 can hold both 32 bit signed integers and addresses
      int32_t i32;
      uint32_t ui32;
    };

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
