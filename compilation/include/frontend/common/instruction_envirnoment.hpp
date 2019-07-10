#pragma once

#include "instruction.hpp"

#include <set>
#include <tuple>

/* Instruction names */
const std::string NOP_INSTR_NAME      = "NOP";
const std::string BREAK_INSTR_NAME    = "BREAK";
const std::string END_INSTR_NAME      = "END";
const std::string JUMP_INSTR_NAME     = "JUMP";
const std::string CALL_INSTR_NAME     = "CALL";
const std::string RET_INSTR_NAME      = "RET";
const std::string GLFR_INSTR_NAME     = "GFLR";
const std::string SFLR_INSTR_NAME     = "SFLR";
const std::string LOAD_INSTR_NAME     = "LOAD";
const std::string STORE_INSTR_NAME    = "STORE";
const std::string LDREL_INSTR_NAME    = "LDREL";
const std::string STREL_INSTR_NAME    = "STREL";
const std::string PUSHSF_INSTR_NAME   = "PUSHSF";
const std::string POPSF_INSTR_NAME    = "POPSF";
const std::string PUSHA_INSTR_NAME    = "PUSHA";
const std::string POP_INSTR_NAME      = "POP";
const std::string PUSH_INSTR_NAME     = "PUSH";
const std::string ASSIGN_INSTR_NAME   = "ASSIGN";
const std::string SET_INSTR_NAME      = "SET";
const std::string MOVE_INSTR_NAME     = "MOVE";
const std::string SWAP_INSTR_NAME     = "SWAP";
const std::string INC_INSTR_NAME      = "INC";
const std::string DEC_INSTR_NAME      = "DEC";
const std::string TEST_INSTR_NAME     = "TEST";
const std::string CMP_INSTR_NAME      = "CMP";
const std::string IN_INSTR_NAME       = "IN";
const std::string OUT_INSTR_NAME      = "OUT";
const std::string AND_INSTR_NAME      = "AND"; 
const std::string OR_INSTR_NAME       = "OR";
const std::string XOR_INSTR_NAME      = "XOR";
const std::string NAND_INSTR_NAME     = "NAND";
const std::string NOR_INSTR_NAME      = "NOR";
const std::string NOT_INSTR_NAME      = "NOT";
const std::string SHL_INSTR_NAME      = "SHL";
const std::string SHR_INSTR_NAME      = "SHR";
const std::string ROL_INSTR_NAME      = "ROL";
const std::string ROR_INSTR_NAME      = "ROR";
const std::string SAL_INSTR_NAME      = "SAL";
const std::string SAR_INSTR_NAME      = "SAR";
const std::string RCL_INSTR_NAME      = "RCL";
const std::string RCR_INSTR_NAME      = "RCR";
const std::string ADD_INSTR_NAME      = "ADD";
const std::string ADC_INSTR_NAME      = "ADC";
const std::string SUB_INSTR_NAME      = "SUB";
const std::string SBB_INSTR_NAME      = "SBB";
const std::string MUL_INSTR_NAME      = "MUL";
const std::string IMUL_INSTR_NAME     = "IMUL";
const std::string DIV_INSTR_NAME      = "DIV";
const std::string IDIV_INSTR_NAME     = "IDIV";
const std::string NEG_INSTR_NAME      = "NEG";
const std::string CAST_INSTR_NAME     = "CAST";

struct InstructionEnvirnoment
{
  using ValueType   = std::pair<std::string, InstructionType>;
  using ResultType  = std::optional<std::pair<std::string, InstructionType>>;

  InstructionEnvirnoment() noexcept;
  ResultType  findInstructionName(const std::string& name);

  private:
  std::set<ValueType> supportedInstructionsNames_{};
};
