#pragma once

#include "common.hpp"
#include "extension_defs.hpp"
#include "operand.hpp"

/* Supported instructions */
enum class InstructionType 
{
  NOP = 0x00000000,
  BREAK,
  END,
  JUMP,
  CALL,
  RET,
  GFLR,
  SFLR,
  LOAD,
  STORE,
  LDREL,
  STREL,
  PUSHSF,
  POPSF,
  PUSHA,
  POP,
  PUSH,
  ASSIGN,
  SET,
  MOVE,
  SWAP,
  INC,
  DEC,
  TEST,
  CMP,
  IN,
  OUT,
  AND, 
  OR,
  XOR,
  NAND,
  NOR,
  NOT,
  SHL,
  SHR,
  ROL,
  ROR,
  SAL,
  SAR,
  RCL,
  RCR,
  ADD,
  ADC,
  SUB,
  SBB,
  MUL,
  IMUL,
  DIV,
  IDIV,
  NEG,
  CAST
};

/* Conditional codes for instructions */
enum class ConditionalCode
{

};

struct Instruction
{
  std::string     name_{};
  InstructionType type_{InstructionType::NOP};
  Extension       ex_{Extension::DWORD};
  OperandList          opList_;
};
using InstructionList = std::vector<Instruction>;

