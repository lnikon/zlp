#include "translator.hpp"

Translator::Translator()
  : pTransImpl_{std::make_unique<GenericTranslatorImpl>()}
{

}

void Translator::setTranslator(UniqueTransImplPtr&& transPtr)
{
  pTransImpl_ = std::move(transPtr);
}

TranslationResult Translator::translate(const CodeSection& codeSec)
{
  return pTransImpl_->translate(codeSec);
}
