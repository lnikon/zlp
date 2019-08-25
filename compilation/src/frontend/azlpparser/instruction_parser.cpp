#include "instruction_parser.hpp"
#include "utility.hpp"
#include "logger.hpp"

std::pair<bool, Instruction> InstructionParser::parse(std::string line)
{
  // instr_name [empty|extension|condition] operands(up to 3)
  auto result = isInstruction(line);

  return result;
}

std::pair<bool, Instruction> InstructionParser::isInstruction(const std::string& line)
{
  /* Instruction parsing starts here */
  bool isInstr = false;

  // Use index for token lookahead
  std::size_t nextToken = 0;

  StringVector tokens;
  utility::tokenize(line, tokens, " ,");

  if (tokens.empty())
  {
    return std::make_pair(false, Instruction{});
  }

  std::string instrName = tokens[nextToken++];
  utility::trim(instrName);

  // Use instruction info for internal representation matching
  InstructionInfo instrInfo;
  instrInfo.type_ = InstructionType::IT_NOP;

  // Actual instruction which will be returned
  Instruction instr;
  
  if(tokens.size() < 2)
  {
    return std::make_pair(isInstr, instr);
  }

  // Store externsion for operands
  std::string opSize = tokens[nextToken]; 

  // Holds true, if extension is present
  bool extOk = false;

  // Default extension should be DoubleWord
  Extensions::Extension ext = Extensions::Extension::EXT_DWORD;
  
  // Unpack result
  // If extensions is present, increment lookahead
  if(std::tie(extOk, ext) = isExtension(opSize); extOk)
  {
    instrInfo.ext_ = extOk;
    nextToken++;
  }

  // Parse argument
  for(std::size_t argIdx = 0; argIdx < MAX_ARG_CNT; ++argIdx)
  {
    if(nextToken == tokens.size())
    {
        break;
    }

    const auto arg = tokens[nextToken];
    if(auto[ok, operand] = isOperand(arg); ok)
    {
        instrInfo.oplst_[argIdx] = operand;
        instrInfo.opcnt_++;
        ++nextToken;
    }
  }
  /* Instruction parsing is done */

  /* Try to match parsed instruction by one of internal representations */
  bool isMatched = false;
  auto itInstrRange = env_.instructionRange(instrName);    
  for(auto itInstrRangeBegin = itInstrRange.first;
      itInstrRangeBegin != itInstrRange.second;
      ++itInstrRangeBegin)
  {
    // For now, skip matching by conditional code
 
    // Match by extension
    if(itInstrRangeBegin->second.ext_ != instrInfo.ext_)
    {
        continue;
    }

    // Match by operand count
    if(itInstrRangeBegin->second.opcnt_ != instrInfo.opcnt_)
    {
        continue;
    }

    // Match by types of operands
    for(std::size_t idx = 0; idx < instrInfo.opcnt_; ++idx)
    {
        if(itInstrRangeBegin->second.oplst_[idx] != instrInfo.oplst_[idx])
        {
            break;
        }
    }

    isMatched = true;
  } 

  if(!isMatched)
  {
    return std::make_pair(isInstr, instr);
  }

  // Create actual instruction from the information that we've actually got
  // Copy instruction type
  instr.type_ = instrInfo.type_;

  // Assign actual extension
  if(instrInfo.ext_)
  {
    instr.ex_ = ext;
  }

  // Handle conditional code
  instr.cnd_ = instrInfo.cnd_;

  // Handle arguments
  for(std::size_t opidx = 0; opidx < instrInfo.opcnt_; ++opidx)
  {
    instr.oplst_.emplace_back(instrInfo.oplst_[opidx]);
  }

  /* TODO: Add support for immediate values */

  isInstr = true;
  return std::make_pair(isInstr, instr);
}

std::pair<bool, InstructionType> InstructionParser::isInstructionType(const std::string& token)
{
  return std::pair<bool, InstructionType>();
}

std::pair<bool, Extensions::Extension> InstructionParser::isExtension(const std::string& token)
{
  return Extensions::isExtension(token);
}

std::pair<bool, OperandList> InstructionParser::isOperandList(const std::string& token)
{
    return std::pair<bool, OperandList>();
}

std::pair<bool, Operand> InstructionParser::isOperand(const std::string &token)
{
    auto result = std::make_pair(false, Operand{});

    auto tokentrmd = utility::trim_copy(token);

    if(token.empty())
    {
        return result;
    }

    // AR or GR
    if(token[0] == 'A' || token[0] == 'R')
    {
        // Check index
        bool isNumber = utility::is_number(token.substr(1, token.size() - 1));
        if(!isNumber)
        {
            Logger::printMessage("Syntax error on line "
                    + std::to_string(lineNumber_)
                    + ". Invalid index for Address\\Global Register\n", LogLevel::HIGH);
            exit(1);
        }

        if(token[0] == 'A')
        {
            result.second.type_ = OperandType::OT_ARG;
        }
        else if(token[0] == 'R')
        {
            result.second.type_ = OperandType::OT_REG;
        }
        else 
        {
            // TODO: Support for immediate values
            result.second.type_ = OperandType::OT_NULL;
        }

        result.second.index_ = utility::parse_int(token.substr(1, token.size() - 1));

        result.first = true;
    }

    return result;
}
