#pragma once

#include "instruction.hpp"

#include <set>
#include <tuple>
#include <optional>
#include <map>

/* Instruction names */
constexpr std::string_view NOP_INSTR_NAME      = "NOP";
constexpr std::string_view BREAK_INSTR_NAME    = "BREAK";
constexpr std::string_view END_INSTR_NAME      = "END";
constexpr std::string_view JUMP_INSTR_NAME     = "JUMP";
constexpr std::string_view CALL_INSTR_NAME     = "CALL";
constexpr std::string_view RET_INSTR_NAME      = "RET";
constexpr std::string_view GLFR_INSTR_NAME     = "GFLR";
constexpr std::string_view SFLR_INSTR_NAME     = "SFLR";
constexpr std::string_view LOAD_INSTR_NAME     = "LOAD";
constexpr std::string_view STORE_INSTR_NAME    = "STORE";
constexpr std::string_view LDREL_INSTR_NAME    = "LDREL";
constexpr std::string_view STREL_INSTR_NAME    = "STREL";
constexpr std::string_view PUSHSF_INSTR_NAME   = "PUSHSF";
constexpr std::string_view POPSF_INSTR_NAME    = "POPSF";
constexpr std::string_view PUSHA_INSTR_NAME    = "PUSHA";
constexpr std::string_view POP_INSTR_NAME      = "POP";
constexpr std::string_view PUSH_INSTR_NAME     = "PUSH";
constexpr std::string_view ASSIGN_INSTR_NAME   = "ASSIGN";
constexpr std::string_view SET_INSTR_NAME      = "SET";
constexpr std::string_view MOVE_INSTR_NAME     = "MOVE";
constexpr std::string_view SWAP_INSTR_NAME     = "SWAP";
constexpr std::string_view INC_INSTR_NAME      = "INC";
constexpr std::string_view DEC_INSTR_NAME      = "DEC";
constexpr std::string_view TEST_INSTR_NAME     = "TEST";
constexpr std::string_view CMP_INSTR_NAME      = "CMP";
constexpr std::string_view IN_INSTR_NAME       = "IN";
constexpr std::string_view OUT_INSTR_NAME      = "OUT";
constexpr std::string_view AND_INSTR_NAME      = "AND"; 
constexpr std::string_view OR_INSTR_NAME       = "OR";
constexpr std::string_view XOR_INSTR_NAME      = "XOR";
constexpr std::string_view NAND_INSTR_NAME     = "NAND";
constexpr std::string_view NOR_INSTR_NAME      = "NOR";
constexpr std::string_view NOT_INSTR_NAME      = "NOT";
constexpr std::string_view SHL_INSTR_NAME      = "SHL";
constexpr std::string_view SHR_INSTR_NAME      = "SHR";
constexpr std::string_view ROL_INSTR_NAME      = "ROL";
constexpr std::string_view ROR_INSTR_NAME      = "ROR";
constexpr std::string_view SAL_INSTR_NAME      = "SAL";
constexpr std::string_view SAR_INSTR_NAME      = "SAR";
constexpr std::string_view RCL_INSTR_NAME      = "RCL";
constexpr std::string_view RCR_INSTR_NAME      = "RCR";
constexpr std::string_view ADD_INSTR_NAME      = "ADD";
constexpr std::string_view ADC_INSTR_NAME      = "ADC";
constexpr std::string_view SUB_INSTR_NAME      = "SUB";
constexpr std::string_view SBB_INSTR_NAME      = "SBB";
constexpr std::string_view MUL_INSTR_NAME      = "MUL";
constexpr std::string_view IMUL_INSTR_NAME     = "IMUL";
constexpr std::string_view DIV_INSTR_NAME      = "DIV";
constexpr std::string_view IDIV_INSTR_NAME     = "IDIV";
constexpr std::string_view NEG_INSTR_NAME      = "NEG";
constexpr std::string_view CAST_INSTR_NAME     = "CAST";

struct InstructionEnvirnoment
{
  using ValueType   = std::pair<std::string, InstructionType>;
  using ResultType  = std::optional<std::pair<std::string, InstructionType>>;

  InstructionEnvirnoment() noexcept;
  ResultType  findInstructionName(const std::string& name);

  /* 
    Here we need smth like hash table with chaining, 
    to store different internal representations 
    of the same instruction.
  */
  std::multimap<std::string_view, InstructionInfo> internalRepresentations_{};

  private:
  std::set<ValueType> supportedInstructionsNames_{};
};
