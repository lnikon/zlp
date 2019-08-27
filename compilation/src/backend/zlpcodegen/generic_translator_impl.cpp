#include "generic_translator_impl.hpp"

TranslationResult GenericTranslatorImpl::translate(const CodeSection& codeSec)
{
  const auto& fnList = codeSec.code_;

  bool fnListDone = true;
  ByteVec bytevec;

  for (const auto& fn : fnList)
  {
    if (const auto & [ok, funcBytes] = translate(fn); ok)
    {
      bytevec.insert(std::end(bytevec), std::begin(funcBytes), std::end(funcBytes));
    }
    else
    {
      fnListDone = false;
      bytevec.clear();

      break;
    }
  }

  return TranslationResult{ fnListDone, bytevec };
}

TranslationResult GenericTranslatorImpl::translate(const Function& func)
{
  return translate(func.code_);
}

TranslationResult GenericTranslatorImpl::translate(const InstructionList& instrList)
{
  bool fnDone = true;
  ByteVec bytevec{};

  for (const auto& instr : instrList)
  {
    if (auto [ok, instrBytes] = translate(instr); ok)
    {
      bytevec.insert(std::end(bytevec), std::begin(instrBytes), std::end(instrBytes));
    }
    else
    {
      // Can't compile current instruction,
      // set fnDone to false, clear compilation result,
      // break out of the loop and stop compilation
      fnDone = false;
      bytevec.clear();
      break;
    }
  }

  return TranslationResult{ fnDone, bytevec };
}

TranslationResult GenericTranslatorImpl::translate(const Instruction& instr)
{
  using ubyte = std::uint8_t;

  bool ok = false;
  ByteVec bytevec;

  ubyte existsByte = 0;
  ubyte valueByte = 0;

  /***** Opcode Compilation *****/
  valueByte = static_cast<ubyte>(instr.type_);

  // Append opcode to chain
  bytevec.emplace_back(valueByte);
  /***** END Opcode Compilation *****/

  /***** Extension Compilation *****/
  existsByte = 0;
  valueByte = 0;
  if (instr.ex_ != Extensions::Extension::EXT_NULL)
  {
    existsByte = 1;
    valueByte = static_cast<ubyte>(instr.ex_);
  }

  // Append extension
  bytevec.emplace_back(existsByte);
  bytevec.emplace_back(valueByte);
  /***** END Extension compilation *****/

  /***** Conditional Code Compilation *****/
  existsByte = 0;
  valueByte = 0;
  if (instr.cnd_ != ConditionalCode::CC_NULL)
  {
    existsByte = 1;
    valueByte = static_cast<ubyte>(instr.cnd_);
  }

  // Append conditional code
  bytevec.emplace_back(existsByte);
  bytevec.emplace_back(valueByte);
  /***** END Conditional Code Compilation *****/

  /***** First Register Compilation *****/
  existsByte = 0;
  valueByte = 0;
  if (instr.oplst_.size() >= 1)
  {
    existsByte = 1;
    valueByte = static_cast<ubyte>(instr.oplst_[0].index_);

    // Append first register index
    bytevec.emplace_back(existsByte);
    bytevec.emplace_back(valueByte);
  }
  /***** First Register Compilation *****/

  /***** Second and Third Registers or Immediate Value Compilation *****/
  existsByte = 0;
  valueByte = 0;
  if (instr.oplst_[1].imv_.type_ != ImmediateValueType::IMV_NULL)
  {
    existsByte = 1;
    bytevec.emplace_back(existsByte);

    ImmediateValue imv = instr.oplst_[1].imv_;

    // TODO: Wrap into separate function
    // TODO: Convert integer into bytes
    if (imv.type_ == ImmediateValueType::IMV_NUM8)
    {
      bytevec.emplace_back(imv.byte_);
    }
    else if (imv.type_ == ImmediateValueType::IMV_NUM16)
    {
      bytevec.emplace_back(imv.word_);
    }
    else if (imv.type_ == ImmediateValueType::IMV_NUM32)
    {
      bytevec.emplace_back(imv.dword_);
    }
    else if (imv.type_ == ImmediateValueType::IMV_NUM64)
    {
      bytevec.emplace_back(imv.qword_);
    }
  }
  else
  {
    // Check for second register
    if (instr.oplst_.size() >= 2)
    {
      existsByte = 1;
      valueByte = static_cast<ubyte>(instr.oplst_[1].index_);

      // Append second register index
      bytevec.emplace_back(existsByte);
      bytevec.emplace_back(valueByte);

      // Check for third register
      if (instr.oplst_.size() > 2)
      {
        existsByte = 1;
        valueByte = static_cast<ubyte>(instr.oplst_[2].index_);
        
        // Append third register index
        bytevec.emplace_back(existsByte);
        bytevec.emplace_back(valueByte);
      }
    }
  }
  /***** End Immediate Value Compilation *****/

  ok = true;
  return TranslationResult{ ok, bytevec };
}













