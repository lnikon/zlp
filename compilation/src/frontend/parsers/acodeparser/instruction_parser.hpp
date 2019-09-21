#pragma once

#include "instruction.hpp"
#include "instruction_envirnoment.hpp"
#include "function.hpp"
#include "label.hpp"
#include "operand.hpp"
#include "lexer_defs.hpp"
#include "extension_defs.hpp"
#include "logger.hpp"

struct InstructionParser final
{

    explicit InstructionParser(logger::LoggerSPtr pLogger);
    ~InstructionParser() = default;

    InstructionParser(const InstructionParser &) = delete;
    InstructionParser &operator=(const InstructionParser &) = delete;

    InstructionParser(InstructionParser &&) = delete;
    InstructionParser &operator=(InstructionParser &&) = delete;

    std::pair<bool, Instruction> parse(std::string line);

    std::size_t lineNumber_{0};

private:
    /*
    * Synchronized logger
    */
    logger::LoggerSPtr ps_logger_{nullptr};

    InstructionEnvirnoment env_{};

    std::pair<bool, Instruction> isInstruction(const std::string &line);
    std::pair<bool, InstructionType> isInstructionType(const std::string &token);
    std::pair<bool, Extensions::Extension> isExtension(const std::string &token);
    std::pair<bool, OperandList> isOperandList(const std::string &token);
    std::pair<bool, Operand> isOperand(const std::string &token, Extensions::Extension ext);
    std::pair<bool, ImmediateValue> handleIMV(const std::string &token, Extensions::Extension ext);
};
