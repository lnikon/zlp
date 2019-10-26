#include "translator.hpp"

ns_translator::Translator::Translator()
  : pTransImpl_{std::make_unique<GenericTranslatorImpl>()}
{

}

void ns_translator::Translator::setTranslator(UniqueTransImplPtr&& transPtr)
{
  pTransImpl_ = std::move(transPtr);
}

ns_translator::TranslationResult ns_translator::Translator::translate(const CodeSection& codeSec)
{
  return pTransImpl_->translate(codeSec);
}
