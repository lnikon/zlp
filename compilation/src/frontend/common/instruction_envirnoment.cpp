#include "instruction_envirnoment.hpp"

#include <algorithm>
#include <iterator>
#include <optional>

InstructionEnvirnoment::InstructionEnvirnoment() noexcept
{
  supportedInstructionsNames_.insert({NOP_INSTR_NAME,     InstructionType::NOP});
  supportedInstructionsNames_.insert({BREAK_INSTR_NAME,   InstructionType::BREAK});
  supportedInstructionsNames_.insert({END_INSTR_NAME,     InstructionType::END});
  supportedInstructionsNames_.insert({JUMP_INSTR_NAME,    InstructionType::JUMP});
  supportedInstructionsNames_.insert({CALL_INSTR_NAME,    InstructionType::CALL});
  supportedInstructionsNames_.insert({RET_INSTR_NAME,     InstructionType::RET});
  supportedInstructionsNames_.insert({GLFR_INSTR_NAME,    InstructionType::GFLR});
  supportedInstructionsNames_.insert({SFLR_INSTR_NAME,    InstructionType::SFLR});
  supportedInstructionsNames_.insert({LOAD_INSTR_NAME,    InstructionType::LOAD});
  supportedInstructionsNames_.insert({STORE_INSTR_NAME,   InstructionType::STORE});
  supportedInstructionsNames_.insert({LDREL_INSTR_NAME,   InstructionType::LDREL});
  supportedInstructionsNames_.insert({STREL_INSTR_NAME,   InstructionType::STREL});
  supportedInstructionsNames_.insert({PUSHSF_INSTR_NAME,  InstructionType::PUSHSF});
  supportedInstructionsNames_.insert({POPSF_INSTR_NAME,   InstructionType::POPSF});
  supportedInstructionsNames_.insert({PUSHA_INSTR_NAME,   InstructionType::PUSHA});
  supportedInstructionsNames_.insert({POP_INSTR_NAME,     InstructionType::POP});
  supportedInstructionsNames_.insert({PUSH_INSTR_NAME,    InstructionType::PUSH});
  supportedInstructionsNames_.insert({ASSIGN_INSTR_NAME,  InstructionType::ASSIGN});
  supportedInstructionsNames_.insert({SET_INSTR_NAME,     InstructionType::SET});
  supportedInstructionsNames_.insert({MOVE_INSTR_NAME,    InstructionType::MOVE});
  supportedInstructionsNames_.insert({SWAP_INSTR_NAME,    InstructionType::SWAP});
  supportedInstructionsNames_.insert({INC_INSTR_NAME,     InstructionType::INC});
  supportedInstructionsNames_.insert({DEC_INSTR_NAME,     InstructionType::DEC});
  supportedInstructionsNames_.insert({TEST_INSTR_NAME,    InstructionType::TEST});
  supportedInstructionsNames_.insert({CMP_INSTR_NAME,     InstructionType::CMP});
  supportedInstructionsNames_.insert({IN_INSTR_NAME,      InstructionType::IN});
  supportedInstructionsNames_.insert({OUT_INSTR_NAME,     InstructionType::OUT});
  supportedInstructionsNames_.insert({AND_INSTR_NAME,     InstructionType::ADD});
  supportedInstructionsNames_.insert({OR_INSTR_NAME,      InstructionType::OR});
  supportedInstructionsNames_.insert({XOR_INSTR_NAME,     InstructionType::XOR});
  supportedInstructionsNames_.insert({NAND_INSTR_NAME,    InstructionType::NAND});
  supportedInstructionsNames_.insert({NOR_INSTR_NAME,     InstructionType::NOR});
  supportedInstructionsNames_.insert({NOT_INSTR_NAME,     InstructionType::NOT});
  supportedInstructionsNames_.insert({SHL_INSTR_NAME,     InstructionType::SHL});
  supportedInstructionsNames_.insert({SHR_INSTR_NAME,     InstructionType::SHR});
  supportedInstructionsNames_.insert({ROL_INSTR_NAME,     InstructionType::ROL});
  supportedInstructionsNames_.insert({ROR_INSTR_NAME,     InstructionType::ROR});
  supportedInstructionsNames_.insert({SAL_INSTR_NAME,     InstructionType::SAL});
  supportedInstructionsNames_.insert({SAR_INSTR_NAME,     InstructionType::SAR});
  supportedInstructionsNames_.insert({RCL_INSTR_NAME,     InstructionType::RCL});
  supportedInstructionsNames_.insert({RCR_INSTR_NAME,     InstructionType::RCR});
  supportedInstructionsNames_.insert({ADD_INSTR_NAME,     InstructionType::ADD});
  supportedInstructionsNames_.insert({ADC_INSTR_NAME,     InstructionType::ADC});
  supportedInstructionsNames_.insert({SUB_INSTR_NAME,     InstructionType::SUB});
  supportedInstructionsNames_.insert({SBB_INSTR_NAME,     InstructionType::SBB});
  supportedInstructionsNames_.insert({MUL_INSTR_NAME,     InstructionType::MUL});
  supportedInstructionsNames_.insert({IMUL_INSTR_NAME,    InstructionType::IMUL});
  supportedInstructionsNames_.insert({DIV_INSTR_NAME,     InstructionType::DIV});
  supportedInstructionsNames_.insert({IDIV_INSTR_NAME,    InstructionType::IDIV});
  supportedInstructionsNames_.insert({NEG_INSTR_NAME,     InstructionType::NEG});
  supportedInstructionsNames_.insert({CAST_INSTR_NAME,    InstructionType::CAST});
}

InstructionEnvirnoment::ResultType
InstructionEnvirnoment::findInstructionName(const std::string& name)
{
  auto findByName = [&name](const ValueType& value) {
    return !value.first.compare(name);
  };

  auto itToTuple = std::find_if(std::begin(supportedInstructionsNames_),
                                std::end(supportedInstructionsNames_),
                                findByName);

  ResultType result{std::nullopt};
  if(itToTuple != std::end(supportedInstructionsNames_))
  {
    result = *itToTuple;
  }

  return result;
}
