#include "instruction_parser.hpp"
#include "utility.hpp"

std::pair<bool, Instruction> InstructionParser::parse(std::string line)
{
    // instr_name [empty|extension|condition] operands(up to 3)
    auto result = isInstruction(line);

    return result;
}

std::pair<bool, Instruction> InstructionParser::isInstruction(const std::string& line)
{
    bool isInstr = false;
    Instruction instruction;

    StringVector tokens;
    utility::tokenize(line, tokens, " ,");

    if (tokens.empty())
    {
        return std::make_pair(false, Instruction{});
    }

    
    

    return std::make_pair(isInstr, instruction);
}

std::pair<bool, InstructionType> InstructionParser::isInstructionType(const std::string& token)
{
    return std::pair<bool, InstructionType>();
}

std::pair<bool, Extension> InstructionParser::isExtension(const std::string& token)
{
    return std::pair<bool, Extension>();
}

std::pair<bool, OperandList> InstructionParser::isOperandList(const std::string& token)
{
    return std::pair<bool, OperandList>();
}