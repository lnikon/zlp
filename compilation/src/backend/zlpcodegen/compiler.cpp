#include "compiler.hpp"

Compiler::Compiler()
  : translator_{std::make_unique<Translator>()}
{ }

void Compiler::setCodeSection(const CodeSection& codeSec)
{
  codeSec_ = codeSec;
}

bool Compiler::compile()
{
  auto [ok, bytes] = translator_->translate(codeSec_);
  if(!ok)
  {
    return false;
  }
}
