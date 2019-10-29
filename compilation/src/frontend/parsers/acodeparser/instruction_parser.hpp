#pragma once

#include "instruction.hpp"
#include "instruction_envirnoment.hpp"
#include "function.hpp"
#include "label.hpp"
#include "operand.hpp"
#include "lexer_defs.hpp"
#include "extension_defs.hpp"
#include "logger.hpp"
#include "parser_defs.hpp"

struct InstructionParser final
{

    explicit InstructionParser(logger::LoggerSPtr pLogger, SimpleSymbolTable& varSymTbl, SimpleSymbolTable& funcSymTbl, SimpleSymbolTable& lblSymTbl);
    ~InstructionParser() = default;

    InstructionParser(const InstructionParser &) = delete;
    InstructionParser &operator=(const InstructionParser &) = delete;

    InstructionParser(InstructionParser &&) = delete;
    InstructionParser &operator=(InstructionParser &&) = delete;

    std::optional<Instruction> parse(std::string line);

    std::size_t lineNumber_{0};

private:
    /*
    * Synchronized logger
    */
    logger::LoggerSPtr ps_logger_{nullptr};

    InstructionEnvirnoment env_{};

	std::optional<Instruction>				isInstruction(const std::string &line);
	std::optional<InstructionType>			isInstructionType(const std::string &token);
	std::optional<Extensions::Extension>	isExtension(const std::string &token);
	std::optional<OperandList>				isOperandList(const std::string &token);
	std::optional<Operand>					isOperand(const std::string &token, Extensions::Extension ext);
	std::optional<ImmediateValue>			handleIMV(const std::string &token, Extensions::Extension ext);
};
