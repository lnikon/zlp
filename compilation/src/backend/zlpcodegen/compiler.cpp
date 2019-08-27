#include "compiler.hpp"

#include <fstream>

Compiler::Compiler()
  : translator_{ std::make_unique<Translator>() }
{ }

void Compiler::setCodeSection(const CodeSection& codeSec)
{
  codeSec_ = codeSec;
}

bool Compiler::compile()
{
  // @bytes will contain all the bytecode
  auto [ok, bytes] = translator_->translate(codeSec_);
  if (!ok)
  {
    return false;
  }

  // TEMP: Write bytes into file
  std::fstream bytecodeOut("translation_out.zexe", std::ios::out | std::ios::binary);
  if (!bytecodeOut.is_open())
  {
    return false;
  }

  for (const auto byte : bytes)
  {
    bytecodeOut << byte;
  }

  bytecodeOut.close();
}
