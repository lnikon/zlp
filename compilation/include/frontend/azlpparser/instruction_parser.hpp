#pragma once

#include "instruction.hpp"
#include "instruction_envirnoment.hpp"
#include "function.hpp"
#include "label.hpp"
#include "operand.hpp"
#include "lexer_defs.hpp"
#include "extension_defs.hpp"

using namespace Extensions;

struct InstructionParser final
{

    InstructionParser() = default;
    ~InstructionParser() = default;

    InstructionParser(const InstructionParser&) = delete;
    InstructionParser(InstructionParser&&) = delete;
    const InstructionParser& operator=(const InstructionParser&) = delete;
    const InstructionParser& operator=(InstructionParser&&) = delete;

    std::pair<bool, Instruction> parse(std::string line);

    std::size_t lineNumber_{0};
private:
    InstructionEnvirnoment            env_{};

    std::pair<bool, Instruction>      isInstruction(const std::string& line);
    std::pair<bool, InstructionType>  isInstructionType(const std::string& token);
    std::pair<bool, Extension>        isExtension(const std::string& token);
    std::pair<bool, OperandList>      isOperandList(const std::string& token);
    std::pair<bool, Operand>          isOperand(const std::string& token);
};
