#pragma once

#include "instruction.hpp"
#include "function.hpp"
#include "label.hpp"
#include "operand.hpp"
#include "lexer_defs.hpp"

struct InstructionParser final
{
    InstructionParser() = default;
    ~InstructionParser() = default;

    InstructionParser(const InstructionParser&) = delete;
    InstructionParser(InstructionParser&&) = delete;
    const InstructionParser& operator=(const InstructionParser&) = delete;
    const InstructionParser& operator=(InstructionParser&&) = delete;

    std::pair<bool, Instruction> parse(std::string line);

private:
    std::pair<bool, Instruction>      isInstruction(const std::string& line);
    std::pair<bool, InstructionType>  isInstructionType(const std::string& token);
    std::pair<bool, Extension>        isExtension(const std::string& token);
    std::pair<bool, OperandList>      isOperandList(const std::string& token);
};