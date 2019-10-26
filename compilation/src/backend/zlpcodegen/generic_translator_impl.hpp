#pragma once

#include "interface_translator.hpp"

class GenericTranslatorImpl final : public ns_interface_translator::ITranslator
{
    using TranslationResult = ns_translator::TranslationResult;

    TranslationResult translate(const CodeSection& codeSec) override;

protected:
    TranslationResult translate(const Function& func) override;
    TranslationResult translate(const InstructionList& instrList) override;
    TranslationResult translate(const Instruction& instr) override;
};

