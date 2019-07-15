#pragma once

#include "common.hpp"
#include "extension_defs.hpp"
#include "operand.hpp"
#include "immediate_value.hpp"

/* Supported instructions */
enum class InstructionType 
{
  IT_NULL = 0x00000000,
  IT_NOP,
  IT_BREAK,
  IT_END,
  IT_JUMP,
  IT_CALL,
  IT_RET,
  IT_GFLR,
  IT_SFLR,
  IT_LOAD,
  IT_STORE,
  IT_LDREL,
  IT_STREL,
  IT_PUSHSF,
  IT_POPSF,
  IT_PUSHA,
  IT_POP,
  IT_PUSH,
  IT_ASSIGN,
  IT_SET,
  IT_MOVE,
  IT_SWAP,
  IT_INC,
  IT_DEC,
  IT_TEST,
  IT_CMP,
  IT_IN,
  IT_OUT,
  IT_AND, 
  IT_OR,
  IT_XOR,
  IT_NAND,
  IT_NOR,
  IT_NOT,
  IT_SHL,
  IT_SHR,
  IT_ROL,
  IT_ROR,
  IT_SAL,
  IT_SAR,
  IT_RCL,
  IT_RCR,
  IT_ADD,
  IT_ADC,
  IT_SUB,
  IT_SBB,
  IT_MUL,
  IT_IMUL,
  IT_DIV,
  IT_IDIV,
  IT_NEG,
  IT_CAST
};

/* Conditional codes for instructions */
enum class ConditionalCode
{
    CC_NULL,
};

/* Instruction structure description
  Instruction is consist of its type: NOP, NEG, IDIV...,
  the point is, instruction with same type can have many different internal representations,
  for example the operand of @assign can be either @AddressRegister or @Register and depending on that
  different internal representations will be created.
  
  Instruction can have extension, which specified how operands will be treated.

  It has an @ConditionCode. It also changes the internal representation. 
  Instructions with same types but different @ConditionCode's are not the same.

  Also, it can have @OperandList.
*/

struct Instruction
{
  InstructionType       type_{InstructionType::IT_NULL};
  Extension             ex_{Extension::EXT_DWORD};
  ConditionalCode       cnd_{ ConditionalCode::CC_NULL };
  OperandList           oplst_;
  ImmediateValueType    immtype_{};
};
using InstructionList = std::vector<Instruction>;

struct InstructionInfo
{
    InstructionType         type_{ InstructionType::IT_NULL};
    ConditionalCode         cnd_{ ConditionalCode::CC_NULL };
    OperandType             oplst_[MAX_ARG_CNT]{ OperandType::OT_NULL };
    ImmediateValueType      immtype_{ImmediateValueType::IMVNULL};
};