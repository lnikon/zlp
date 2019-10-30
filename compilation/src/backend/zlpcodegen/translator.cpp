#include "translator.hpp"

ns_translator::Translator::Translator()
  : ps_codeTranslator_{ns_code_translator::make_shared()},
    pTransImpl_{std::make_unique<GenericTranslatorImpl>()}
{

}

void ns_translator::Translator::setTranslator(UniqueTransImplPtr&& transPtr)
{
    pTransImpl_ = std::move(transPtr);
}

void ns_translator::Translator::setCompilationUnit(ns_compilation_unit::CompilationUnitSPtr pCompilationUnit)
{
    ps_compilationUnit_ = pCompilationUnit;
}

ns_translator::TranslationResult ns_translator::Translator::translate(const CodeSection& codeSec)
{
  return ps_codeTranslator_->translate(codeSec);
}
