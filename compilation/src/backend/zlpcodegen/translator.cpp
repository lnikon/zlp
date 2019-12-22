#include "translator.hpp"

ns_translator::Translator::Translator()
  : ps_codeTranslator_{ns_code_translator::make_shared(symbolTbl_, varToSymblIndex_, funcToSymblIndex_)},
    ps_dataTranslator_{ns_data_translator::make_shared(symbolTbl_, varToSymblIndex_)}
{

}

void ns_translator::Translator::setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompilationUnit)
{
    ps_compilationUnit_ = pCompilationUnit;

    ps_codeTranslator_->setCompilationUnit(pCompilationUnit);
    ps_dataTranslator_->setCompilationUnit(pCompilationUnit);
}

void ns_translator::Translator::translate(const CodeSection& codeSec, const DataSection& crDataSec)
{
    ps_codeTranslator_->translate(codeSec, crDataSec);
}

void ns_translator::Translator::translate(const DataSection& crDataSec)
{
    ps_dataTranslator_->translate(crDataSec);
}
