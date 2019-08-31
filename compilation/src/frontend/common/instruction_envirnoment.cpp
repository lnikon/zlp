#include "instruction_envirnoment.hpp"

#include <algorithm>
#include <iterator>
#include <optional>
#include <utility>

InstructionEnvirnoment::InstructionEnvirnoment() noexcept
{
  // Control
  initControlInstructions();

  // Memory Access 
  initMemoryAccessInstructions();

  // Stack
  initStackInstructions();

  // Assignment
  initAssignmentInstructions();

  // Move Across Register
  initMoveInstructions();

  // Address Manipulation
  initAddressManipulationInstructions();

  // Comparison
  initComparisonInstructions();

  // Input & Output
  initComparisonInstructions();

  // Logical(bitwise)
  initLogicalInstructions();
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

  ResultType result{ std::nullopt };
  if (itToTuple != std::end(supportedInstructionsNames_))
  {
    result = *itToTuple;
  }

  return result;
}

void InstructionEnvirnoment::initControlInstructions() noexcept
{
  internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    NOP_INSTR_NAME,
    {
        InstructionType::IT_NOP
    })
  );
}

void InstructionEnvirnoment::initMemoryAccessInstructions() noexcept
{
  internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    LOAD_INSTR_NAME,
    {
        InstructionType::IT_LOAD,
        ConditionalCode::CC_NULL,
        {   // init @oplist_
            {OperandType::OT_REG_ARG, 0},
            {OperandType::OT_ARG, 0},
        },
        2,
        ImmediateValueType::IMV_NULL,    // immediate value type
        false   // no extension
    })
  );
}

void InstructionEnvirnoment::initStackInstructions() noexcept
{
  
}

void InstructionEnvirnoment::initAssignmentInstructions() noexcept
{
    internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    ASSIGN_INSTR_NAME,
    {
      InstructionType::IT_ASSIGN,
      ConditionalCode::CC_NULL,
      {
        {OperandType::OT_ARG, 0},
        {OperandType::OT_IMV, 1}
      },
      2,
      ImmediateValueType::IMV_NUM8,
      true,
      Extensions::MatchExtension::ME_DONT_CARE
    }
  ));

  internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    ASSIGN_INSTR_NAME,
    {
      InstructionType::IT_ASSIGN,
      ConditionalCode::CC_NULL,
      {
        {OperandType::OT_ARG, 0},
        {OperandType::OT_IMV, 1}
      },
      2,
      ImmediateValueType::IMV_NUM16,
      true,
      Extensions::MatchExtension::ME_DONT_CARE
    }
  ));

  internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    ASSIGN_INSTR_NAME,
    {
      InstructionType::IT_ASSIGN,
      ConditionalCode::CC_NULL,
      {
        {OperandType::OT_ARG, 0},
        {OperandType::OT_IMV, 1}
      },
      2,
      ImmediateValueType::IMV_NUM32,
      true,
      Extensions::MatchExtension::ME_DONT_CARE
    }
  ));

  internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    ASSIGN_INSTR_NAME,
    {
      InstructionType::IT_ASSIGN,
      ConditionalCode::CC_NULL,
      {
        {OperandType::OT_ARG, 0},
        {OperandType::OT_IMV, 1}
      },
      2,
      ImmediateValueType::IMV_NUM64,
      true,
      Extensions::MatchExtension::ME_DONT_CARE
    }
  ));
}

void InstructionEnvirnoment::initMoveInstructions() noexcept
{
    internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    "MOVE",
    {
      InstructionType::IT_MOVE,
      ConditionalCode::CC_NULL,
      {
          {OperandType::OT_REG, 0},
          {OperandType::OT_REG, 1}
      },
      2,
      ImmediateValueType::IMV_NULL,
      true
    }
  ));

  internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    "MOVE_EQ",
    {
      InstructionType::IT_MOVE,
      ConditionalCode::CC_EQUAL,
      {
          {OperandType::OT_REG_ARG, 0},
          {OperandType::OT_REG_ARG, 1}
      },
      2,
      ImmediateValueType::IMV_NULL,
      false
    }
  ));

  internalRepresentations_.emplace(std::pair<std::string, InstructionInfo>(
    "MOVE_NEQ",
    {
        InstructionType::IT_MOVE,
        ConditionalCode::CC_EQUAL,
        {
            {OperandType::OT_REG, 0},
            {OperandType::OT_REG, 1}
        },
        2,
        ImmediateValueType::IMV_NULL,
        true
    }
  ));
}

void InstructionEnvirnoment::initAddressManipulationInstructions() noexcept
{
  
}

void InstructionEnvirnoment::initComparisonInstructions() noexcept
{
  
}

void InstructionEnvirnoment::initInputOutputInstructions() noexcept
{

}

void InstructionEnvirnoment::initLogicalInstructions() noexcept
{

}