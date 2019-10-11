#include "instruction_parser.hpp"
#include "utility.hpp"
#include "logger.hpp"

InstructionParser::InstructionParser(logger::LoggerSPtr pLogger)
    : ps_logger_{pLogger}
{
}

std::optional<Instruction> InstructionParser::parse(std::string line)
{
  /* Parsing algorithm */
  /*
  1. Parse instruction on line -> return @instructionInfo
  2. Try match @instructionInfo against internal representations
  3. If succeed, create and return insruction
  4. Otherwise return false
  */

  auto result = isInstruction(line);

  return result;
}

std::optional<Instruction> InstructionParser::isInstruction(const std::string &line)
{
  /* Instruction parsing starts here */
  bool isInstr = false;

  // Use index for token lookahead
  std::size_t nextToken = 0;

  StringVector tokens;
  utility::tokenize(line, tokens, " ,");

  if (tokens.empty())
  {
	  return std::nullopt;
  }

  std::string instrName = tokens[nextToken++];
  utility::trim(instrName);

  // Use instruction info for internal representation matching
  InstructionInfo instrInfo;
  instrInfo.type_ = InstructionType::IT_NOP;

  // Actual instruction which will be returned
  Instruction instr;

  if (tokens.size() < 2)
  {
	  return std::nullopt;
  }

  // Store externsion for operands
  std::string opSize = tokens[nextToken];

  // Default extension should be DoubleWord
  auto ext = std::optional<Extensions::Extension>(Extensions::Extension::EXT_DWORD);

  // Unpack result
  // If extensions is present, increment lookahead
  if (ext = isExtension(opSize); ext.has_value())
  {
    instrInfo.ext_ = true;

    // If empty extension string is given, then don't icrement lookahead
    if (!opSize.empty())
    {
      nextToken++;
    }
  }
  else
  {
	  ext = std::optional<Extensions::Extension>(Extensions::Extension::EXT_DWORD);
  }

  // Parse argument list
  for (std::size_t argIdx = 0; argIdx < MAX_ARG_CNT; ++argIdx)
  {
    if (nextToken == tokens.size())
    {
      break;
    }

    const auto arg = tokens[nextToken];
    if (auto operand = isOperand(arg, *ext); operand.has_value())
    {
      instrInfo.oplst_[argIdx] = *operand;
      instrInfo.opcnt_++;
      ++nextToken;
    }
  }
  /* Instruction parsing is done */

  /* Try to match parsed instruction by one of internal representations */
  bool isMatched = false;
  auto itInstrRange = env_.instructionRange(instrName);

  for (auto itInstrRangeBegin = itInstrRange.first;
       itInstrRangeBegin != itInstrRange.second;
       ++itInstrRangeBegin)
  {
    // For now, skip matching by conditional code

    // Match by extension
    // If internalRepresentation doesn't support extension
    // and extension is given in a source then skip
    const bool isDontCare = itInstrRangeBegin->second.mext_ == Extensions::MatchExtension::ME_DONT_CARE;
    const bool isExtNotMatch = itInstrRangeBegin->second.ext_ != instrInfo.ext_;
    if (isExtNotMatch)
    {
      if (!isDontCare)
      {
        continue;
      }
    }

    // Match by operand count
    if (itInstrRangeBegin->second.opcnt_ != instrInfo.opcnt_)
    {
      continue;
    }

    // Match by types of operands
    bool opListMatch = true;
    for (std::size_t idx = 0; idx < instrInfo.opcnt_; ++idx)
    {
      // Really, fuckin' really, a piece of SHIT!
      if (itInstrRangeBegin->second.oplst_[idx] != instrInfo.oplst_[idx])
      {
        if (itInstrRangeBegin->second.oplst_[idx].type_ == OperandType::OT_REG_ARG 
			&& instrInfo.oplst_[idx].type_ != OperandType::OT_REG 
			&& instrInfo.oplst_[idx].type_ != OperandType::OT_ARG)
        {
          opListMatch = false;
          break;
        }
      }
    }

    if (!opListMatch)
    {
      break;
    }

    // Get instruction type
    instrInfo.type_ = itInstrRangeBegin->second.type_;

    // Get conditional code
    instrInfo.cnd_ = itInstrRangeBegin->second.cnd_;

    isMatched = true;
    break;
  }

  if (!isMatched)
  {
	  return std::nullopt;
  }

  // Create actual instruction from the information that we've actually got
  // Copy instruction type
  instr.type_ = instrInfo.type_;

  // Assign actual extension
  if (instrInfo.ext_)
  {
    instr.ex_ = *ext;
  }

  // Handle conditional code
  instr.cnd_ = instrInfo.cnd_;

  // Handle arguments
  for (std::size_t opidx = 0; opidx < instrInfo.opcnt_; ++opidx)
  {
    instr.oplst_.emplace_back(instrInfo.oplst_[opidx]);
  }

  isInstr = true;
  return std::nullopt;
}

std::optional<InstructionType> InstructionParser::isInstructionType(const std::string &token)
{
  return std::nullopt;
}

std::optional<Extensions::Extension> InstructionParser::isExtension(const std::string &token)
{
  return Extensions::extension(token);
}

std::optional<OperandList> InstructionParser::isOperandList(const std::string &token)
{
  return std::nullopt;
}

std::optional<Operand> InstructionParser::isOperand(const std::string &token, Extensions::Extension ext)
{
  auto result = std::optional<Operand>{std::nullopt};

  auto tokentrmd = utility::trim_copy(token);

  if (token.empty())
  {
    return std::nullopt;
  }

  // AR or GR
  if (token[0] == 'A' || token[0] == 'R')
  {
    // Check index
    bool isNumber = utility::is_number(token.substr(1, token.size() - 1));
    if (!isNumber)
    {
      ps_logger_->printMessage("Syntax error on line " + std::to_string(lineNumber_) + ". Invalid index for Address\\Global Register\n", logger::LogLevel::HIGH);
      exit(1);
    }

    if (token[0] == 'A')
    {
      result->type_ = OperandType::OT_ARG;
      result->index_ = utility::parse_int(token.substr(1, token.size() - 1));
    }
    else if (token[0] == 'R')
    {
      result->type_ = OperandType::OT_REG;
      result->index_ = utility::parse_int(token.substr(1, token.size() - 1));
    }
  }
  else
  {
    if (auto imv = handleIMV(token, ext); imv.has_value())
    {
      result->type_ = OperandType::OT_IMV;
	  result->imv_ = std::move(imv.value());
    }
  }

  return result;
}

std::optional<ImmediateValue> InstructionParser::handleIMV(const std::string &token, Extensions::Extension ext)
{
	auto result = std::optional<ImmediateValue>{std::nullopt};

  long long value = utility::parse_int(token);

  // TODO: Handle numeric sign for immediate values

  if (ext == Extensions::Extension::EXT_BYTE || ext == Extensions::Extension::EXT_CHAR)
  {
    result->type_ = ImmediateValueType::IMV_NUM8;
    result->byte_ = value;
  }
  else if (ext == Extensions::Extension::EXT_WORD)
  {
    result->type_ = ImmediateValueType::IMV_NUM16;
    result->word_ = value;
  }
  else if (ext == Extensions::Extension::EXT_DWORD)
  {
    result->type_ = ImmediateValueType::IMV_NUM32;
    result->dword_ = value;
  }
  else if (ext == Extensions::Extension::EXT_QWORD)
  {
    result->type_ = ImmediateValueType::IMV_NUM64;
    result->qword_ = value;
  }

  return result;
}
