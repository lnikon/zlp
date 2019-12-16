#include "code_translator.hpp"

void ns_code_translator::CodeTranslator::setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompUnit)
{
  ps_compUnit_ = pCompUnit;
}

ns_translator::TranslationResult ns_code_translator::CodeTranslator::translate(const CodeSection& crCodeSec)
{
  const auto& fnList = crCodeSec.code_;

  ns_translator::byte_vec_t byte_tvec;

  for (const auto& fn : fnList)
  {
    if (const auto fnbyte_ts = translate(fn); fnbyte_ts.has_value())
    {
      byte_tvec.insert(std::end(byte_tvec), std::begin(fnbyte_ts.value()), std::end(fnbyte_ts.value()));
    }
    else
    {
        return std::nullopt;
    }
  }

  return std::make_optional(byte_tvec);
}

ns_translator::TranslationResult ns_code_translator::CodeTranslator::translate(const Function& crFunc)
{
  return translate(crFunc.code_);
}

ns_translator::TranslationResult ns_code_translator::CodeTranslator::translate(const InstructionList& crInstrList)
{
  ns_translator::byte_vec_t byte_tvec{};

  for (const auto& instr : crInstrList)
  {
    if (const auto& instrbyte_ts = translate(instr); instrbyte_ts.has_value())
    {
      byte_tvec.insert(std::end(byte_tvec), std::begin(instrbyte_ts.value()), std::end(instrbyte_ts.value()));
    }
    else
    {
        return std::nullopt;
    }
  }

  return std::make_optional(byte_tvec);
}

ns_translator::TranslationResult ns_code_translator::CodeTranslator::translate(const Instruction& crInstr)
{
  using ubyte_t = std::uint8_t;

  ns_translator::byte_vec_t byte_tvec;

  ubyte_t existsbyte_t = 0;
  ubyte_t valuebyte_t = 0;

  /***** Opcode Compilation *****/
  valuebyte_t = static_cast<ubyte_t>(crInstr.type_);

  // Append opcode to chain
  byte_tvec.emplace_back(valuebyte_t);
  /***** END Opcode Compilation *****/

  /***** Extension Compilation *****/
  existsbyte_t = 0;
  valuebyte_t = 0;
  if (crInstr.ex_ != Extensions::Extension::EXT_NULL)
  {
    existsbyte_t = 1;
    valuebyte_t = static_cast<ubyte_t>(crInstr.ex_);
  }

  // Append extension
  byte_tvec.emplace_back(existsbyte_t);
  byte_tvec.emplace_back(valuebyte_t);
  /***** END Extension compilation *****/

  /***** Conditional Code Compilation *****/
  existsbyte_t = 0;
  valuebyte_t = 0;
  if (crInstr.cnd_ != ConditionalCode::CC_NULL)
  {
    existsbyte_t = 1;
    valuebyte_t = static_cast<ubyte_t>(crInstr.cnd_);
  }

  // Append conditional code
  byte_tvec.emplace_back(existsbyte_t);
  byte_tvec.emplace_back(valuebyte_t);
  /***** END Conditional Code Compilation *****/

  /***** First Register Compilation *****/
  existsbyte_t = 0;
  valuebyte_t = 0;
  if (crInstr.oplst_.size() >= 1)
  {
    existsbyte_t = 1;
    valuebyte_t = static_cast<ubyte_t>(crInstr.oplst_[0].index_);

    // Append first register index
    byte_tvec.emplace_back(existsbyte_t);
    byte_tvec.emplace_back(valuebyte_t);
  }
  /***** First Register Compilation *****/

  /***** Second and Third Registers or Immediate Value Compilation *****/
  existsbyte_t = 0;
  valuebyte_t = 0;
  if (crInstr.oplst_[1].imv_.type_ != ImmediateValueType::IMV_NULL)
  {
    existsbyte_t = 1;
    byte_tvec.emplace_back(existsbyte_t);

    ImmediateValue imv = crInstr.oplst_[1].imv_;

    // TODO: Wrap into separate function
    // TODO: Convert integer into byte_ts
    if (imv.type_ == ImmediateValueType::IMV_NUM8)
    {
      byte_tvec.emplace_back(imv.byte_t_);
    }
    else if (imv.type_ == ImmediateValueType::IMV_NUM16)
    {
      byte_tvec.emplace_back(imv.word_);
    }
    else if (imv.type_ == ImmediateValueType::IMV_NUM32)
    {
      byte_tvec.emplace_back(imv.dword_);
    }
    else if (imv.type_ == ImmediateValueType::IMV_NUM64)
    {
      byte_tvec.emplace_back(imv.qword_);
    }
  }
  else
  {
    // Check for second register
    if (crInstr.oplst_.size() >= 2)
    {
      existsbyte_t = 1;
      valuebyte_t = static_cast<ubyte_t>(crInstr.oplst_[1].index_);

      // Append second register index
      byte_tvec.emplace_back(existsbyte_t);
      byte_tvec.emplace_back(valuebyte_t);

      // Check for third register
      if (crInstr.oplst_.size() > 2)
      {
        existsbyte_t = 1;
        valuebyte_t = static_cast<ubyte_t>(crInstr.oplst_[2].index_);

        // Append third register index
        byte_tvec.emplace_back(existsbyte_t);
        byte_tvec.emplace_back(valuebyte_t);
      }
    }
  }
  /***** End Immediate Value Compilation *****/

  return std::make_optional(byte_tvec);
}
