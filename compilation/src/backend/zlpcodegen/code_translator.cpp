#include "code_translator.hpp"
#include "instructiontranslator.h"

#include <numeric>

void
ns_code_translator::CodeTranslator::setCompilationUnit(
        ns_compilation_unit::CompilationUnitSPtr pCompUnit)
{
    ps_compUnit_ = pCompUnit;
}

ns_code_translator::CodeTranslator::CodeTranslator(SimpleSymbolTable& symblTbl,
                                                   std::vector<std::size_t>& varToSymblIndex,
                                                   std::vector<std::size_t>& funcToSymblIndex)
    : symblTbl_(symblTbl),
      varToSymblIndex_(varToSymblIndex),
      funcToSymblIndex_(funcToSymblIndex)
{

}

void
ns_code_translator::CodeTranslator::translate(const CodeSection& crCodeSec,
                                              const DataSection& crDataSec)
{
    /*
     * Reference to units functions list
     */
    const auto& fnList = crCodeSec.code_;

    /*
     * Count of function, to reserve space for relocations
     */
    const auto fnCount = std::distance(std::begin(fnList), std::end(fnList));
    funcToSymblIndex_.reserve(static_cast<std::size_t>(fnCount));

    /*
     * Compilation unit level symbol table
     */
    auto symblTbl = ps_compUnit_->symbolTable();

    /*
     * Before the functions, variables were stored, so we should start counting after last variables index
     */
    std::size_t lastSym = symblTbl->last() + 1;

    /*
     * Offset from code section
     */
    std::size_t codeSecOffset = 0;
    for (const auto& fn : fnList)
    {
        symbol_ns::Symbol sym;
        sym.name_ = fn.name_;
        sym.type_ = symbol_ns::symbol_type_t::ST_CODE;
        sym.valueType_ = symbol_ns::symbol_value_type_t::EXT_NULL;
        sym.address_ = 0;
        sym.size_ = 0;

        symblTbl_.emplace(sym.name_, lastSym);
        funcToSymblIndex_.emplace_back(lastSym);

        if (funcToSymblIndex_.size() - 1 == crCodeSec.entryPointIndex_)
        {
            ps_compUnit_->info_.entryPointIndex_ = funcToSymblIndex_.size() - 1;
        }

        if (fn.sizeLines_ == 0)
        {
            continue;
        }

        sym.address_ = codeSecOffset;

        sym.size_ = sym.address_ - codeSecOffset;

        translate(fn, crDataSec, codeSecOffset);
    }
}

std::size_t
ns_code_translator::CodeTranslator::translate(const Function& crFunc,
                                              const DataSection& crDataSec,
                                              std::size_t& rCodeSecOffset)
{
    std::vector<std::size_t> lblReloc;

    std::size_t lblIdx = 0;
    std::vector<std::size_t> lblLoc;
    lblLoc.reserve(crFunc.labels_.size());

    constexpr const auto cmdAvgLen = (cmdMaxLen - cmdMinLen) / 2;
    ps_compUnit_->vec_code_.resize(rCodeSecOffset + crFunc.code_.size() * cmdAvgLen + cmdMaxLen);

    auto itr = ns_instruction_translator::make_shared(symblTbl_, varToSymblIndex_,
                                                      funcToSymblIndex_, lblReloc);
    itr->setCompilationUnit(ps_compUnit_);

    auto fnOffset = rCodeSecOffset;

    std::size_t cmdIdx = 0;
    const auto& cmds = crFunc.code_;
    for (const auto& cmd : cmds)
    {
        if (lblIdx < crFunc.labels_.size() && crFunc.labels_[lblIdx].index_ == cmdIdx)
        {
            lblLoc[lblIdx] = rCodeSecOffset - fnOffset;
        }

        if (ps_compUnit_->vec_code_.size() < rCodeSecOffset + cmdMaxLen)
        {
            ps_compUnit_->vec_code_.
                    resize(rCodeSecOffset + (crFunc.code_.size() - cmdIdx) * cmdAvgLen + cmdMaxLen);
        }

        rCodeSecOffset += itr->translate(cmd, rCodeSecOffset);
    }

    for (const auto codeOffset : lblReloc)
    {
        std::size_t lblIdx = reinterpret_cast<uint16_t&>(ps_compUnit_->vec_code_[codeOffset]);
        if (lblIdx >= lblLoc.size())
        {
            exit(1);
        }

        std::size_t lblOffset = lblLoc[lblIdx];
        int64_t relOffset =
                static_cast<int64_t>(lblOffset - (codeOffset - fnOffset + sizeof(uint16_t)));

        if (relOffset < std::numeric_limits<int16_t>::min() ||
            relOffset > std::numeric_limits<int16_t>::max())
        {
            exit(1);
        }

        reinterpret_cast<int16_t&>(ps_compUnit_->vec_data_[codeOffset])
                = static_cast<int16_t>(relOffset);
    }
}

ns_translator::TranslationResult
ns_code_translator::CodeTranslator::translate(const InstructionList& crInstrList,
                                              const DataSection& crDataSec)
{
    ns_translator::byte_vec_t byte_tvec{};

    for (const auto& instr : crInstrList)
    {
        if (const auto& instrbyte_ts = translate(instr, crDataSec); instrbyte_ts.has_value())
        {
            byte_tvec.insert(std::end(byte_tvec), // Destination end
                             std::begin(instrbyte_ts.value()),  // Source begin
                             std::end(instrbyte_ts.value()));   // Source end
        }
        else
        {
            return std::nullopt;
        }
    }

    return std::make_optional(byte_tvec);
}

ns_translator::TranslationResult
ns_code_translator::CodeTranslator::translate(const Instruction& crInstr,
                                              const DataSection& crDataSec)
{
    using ubyte_t = std::uint8_t;

    ns_translator::byte_vec_t byte_tvec;


}

//ns_translator::TranslationResult
//ns_code_translator::CodeTranslator::translate(const Instruction& crInstr,
//                                              const DataSection& crDataSec)
//{
//  using ubyte_t = std::uint8_t;

//  ns_translator::byte_vec_t byte_tvec;

//  ubyte_t existsbyte_t = 0;
//  ubyte_t valuebyte_t = 0;

//  /***** Opcode Compilation *****/
//  valuebyte_t = static_cast<ubyte_t>(crInstr.type_);

//  // Append opcode to chain
//  byte_tvec.emplace_back(valuebyte_t);
//  /***** END Opcode Compilation *****/

//  /***** Extension Compilation *****/
//  existsbyte_t = 0;
//  valuebyte_t = 0;
//  if (crInstr.ex_ != Extensions::Extension::EXT_NULL)
//  {
//    existsbyte_t = 1;
//    valuebyte_t = static_cast<ubyte_t>(crInstr.ex_);
//  }

//  // Append extension
//  byte_tvec.emplace_back(existsbyte_t);
//  byte_tvec.emplace_back(valuebyte_t);
//  /***** END Extension compilation *****/

//  /***** Conditional Code Compilation *****/
//  existsbyte_t = 0;
//  valuebyte_t = 0;
//  if (crInstr.cnd_ != ConditionalCode::CC_NULL)
//  {
//    existsbyte_t = 1;
//    valuebyte_t = static_cast<ubyte_t>(crInstr.cnd_);
//  }

//  // Append conditional code
//  byte_tvec.emplace_back(existsbyte_t);
//  byte_tvec.emplace_back(valuebyte_t);
//  /***** END Conditional Code Compilation *****/

//  /***** First Register Compilation *****/
//  existsbyte_t = 0;
//  valuebyte_t = 0;
//  if (crInstr.oplst_.size() >= 1)
//  {
//    existsbyte_t = 1;
//    valuebyte_t = static_cast<ubyte_t>(crInstr.oplst_[0].index_);

//    // Append first register index
//    byte_tvec.emplace_back(existsbyte_t);
//    byte_tvec.emplace_back(valuebyte_t);
//  }
//  /***** First Register Compilation *****/

//  /***** Second and Third Registers or Immediate Value Compilation *****/
//  existsbyte_t = 0;
//  valuebyte_t = 0;
//  if (crInstr.oplst_[1].imv_.type_ != ImmediateValueType::IMV_NULL)
//  {
//    existsbyte_t = 1;
//    byte_tvec.emplace_back(existsbyte_t);

//    ImmediateValue imv = crInstr.oplst_[1].imv_;

//    // TODO: Wrap into separate function
//    // TODO: Convert integer into byte_ts
//    if (imv.type_ == ImmediateValueType::IMV_NUM8)
//    {
//      byte_tvec.emplace_back(imv.byte_t_);
//    }
//    else if (imv.type_ == ImmediateValueType::IMV_NUM16)
//    {
//      byte_tvec.emplace_back(imv.word_);
//    }
//    else if (imv.type_ == ImmediateValueType::IMV_NUM32)
//    {
//      byte_tvec.emplace_back(imv.dword_);
//    }
//    else if (imv.type_ == ImmediateValueType::IMV_NUM64)
//    {
//      byte_tvec.emplace_back(imv.qword_);
//    }
//  }
//  else
//  {
//    // Check for second register
//    if (crInstr.oplst_.size() >= 2)
//    {
//      existsbyte_t = 1;
//      valuebyte_t = static_cast<ubyte_t>(crInstr.oplst_[1].index_);

//      // Append second register index
//      byte_tvec.emplace_back(existsbyte_t);
//      byte_tvec.emplace_back(valuebyte_t);

//      // Check for third register
//      if (crInstr.oplst_.size() > 2)
//      {
//        existsbyte_t = 1;
//        valuebyte_t = static_cast<ubyte_t>(crInstr.oplst_[2].index_);

//        // Append third register index
//        byte_tvec.emplace_back(existsbyte_t);
//        byte_tvec.emplace_back(valuebyte_t);
//      }
//    }
//  }
//  /***** End Immediate Value Compilation *****/

//  return std::make_optional(byte_tvec);
//}
