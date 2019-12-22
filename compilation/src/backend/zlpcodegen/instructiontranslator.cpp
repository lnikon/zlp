#include "instructiontranslator.h"

#include <cstring>

ns_instruction_translator::InstructionTranslator::InstructionTranslator(SimpleSymbolTable& symblTbl,
                                                                        std::vector<std::size_t>& varToSymblIndex,
                                                                        std::vector<std::size_t>& funcToSymblIndex,
                                                                        std::vector<std::size_t>& lblReloc)
    : symblTbl_(symblTbl),
      varToSymblIndex_(varToSymblIndex),
      funcToSymblIndex_(funcToSymblIndex),
      lblReloc_(lblReloc)
{

}

void
ns_instruction_translator::InstructionTranslator::setCompilationUnit(
        ns_compilation_unit::CompilationUnitSPtr pCompUnit)
{
    ps_compUnit_ = pCompUnit;
}

std::size_t
ns_instruction_translator::InstructionTranslator::translate(const Instruction& instr,
                                                            std::size_t codeSecOffset)
{
    uint8_t* pCodeStart = &ps_compUnit_->vec_code_[codeSecOffset];
    uint8_t* pCodeNow = pCodeStart;

    *pCodeNow = static_cast<uint8_t>(instr.type_);
    pCodeNow++;

    if (instr.cnd_ != ConditionalCode::CC_NULL)
    {
        *pCodeNow = static_cast<uint8_t>(instr.type_);

    }

    for (const auto& arg : instr.oplst_)
    {
        auto type = arg.type_;

        switch (type)
        {
            case OperandType::OT_ARG:
                *pCodeNow = static_cast<uint8_t>(arg.index_);
                break;
            case OperandType::OT_REG:
                *pCodeNow = static_cast<uint8_t>(arg.index_);
                break;
            case OperandType::OT_VAR: {
                std::size_t symIdx = varToSymblIndex_[arg.index_];
                std::memcpy(pCodeNow, &symIdx, sizeof(uint32_t));
                ps_compUnit_->reloc_.relocations_.push_back(codeSecOffset + (pCodeNow - pCodeStart));
                pCodeNow += sizeof(uint32_t);
                break;
            }
            case OperandType::OT_FUN: {
                std::size_t symIdx = funcToSymblIndex_[arg.index_];
                std::memcpy(pCodeNow, &symIdx, sizeof(uint32_t));
                ps_compUnit_->reloc_.relocations_.push_back(codeSecOffset + (pCodeNow - pCodeStart));
                pCodeNow += sizeof(uint32_t);
                break;
            }
            case OperandType::OT_LBL: {
                *reinterpret_cast<uint16_t*>(pCodeNow) = static_cast<uint16_t>(arg.index_);
                lblReloc_.push_back(codeSecOffset + (pCodeNow - pCodeStart));
                pCodeNow += sizeof(uint16_t);
                break;
            }
            case OperandType::OT_IMV:
                switch (arg.imv_.type_)
                {
                    case ImmediateValueType::IMV_UNUM8:
                        *reinterpret_cast<uint8_t*>(pCodeNow) = arg.imv_.ubyte_t_;
                        pCodeNow += sizeof(uint8_t);
                        break;
                    case ImmediateValueType::IMV_NUM8:
                        *reinterpret_cast<int8_t*>(pCodeNow) = arg.imv_.byte_t_;
                        pCodeNow += sizeof(int8_t);
                        break;
                    case ImmediateValueType::IMV_UNUM16:
                        *reinterpret_cast<uint16_t*>(pCodeNow) = arg.imv_.uword_;
                        pCodeNow += sizeof(uint16_t);
                        break;
                    case ImmediateValueType::IMV_NUM16:
                        *reinterpret_cast<int16_t*>(pCodeNow) = arg.imv_.word_;
                        pCodeNow += sizeof(int16_t);
                        break;
                    case ImmediateValueType::IMV_UNUM32:
                        *reinterpret_cast<uint32_t*>(pCodeNow) = arg.imv_.udword_;
                        pCodeNow += sizeof(uint32_t);
                        break;
                    case ImmediateValueType::IMV_NUM32:
                        *reinterpret_cast<int32_t*>(pCodeNow) = arg.imv_.dword_;
                        pCodeNow += sizeof(int32_t);
                        break;
                    case ImmediateValueType::IMV_UNUM64:
                        *reinterpret_cast<uint64_t*>(pCodeNow) = arg.imv_.uqword_;
                        pCodeNow += sizeof(uint64_t);
                        break;
                    case ImmediateValueType::IMV_NUM64:
                        *reinterpret_cast<int64_t*>(pCodeNow) = arg.imv_.qword_;
                        pCodeNow += sizeof(int64_t);
                        break;
                    default:
                        exit(1);
//                        break;
                }
                break;

            default:
                exit(1);
//                break;
        }
    }

    return pCodeNow - pCodeStart;
}
