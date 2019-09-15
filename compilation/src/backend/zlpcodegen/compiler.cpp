#include "compiler.hpp"
#include "logger.hpp"

#include <fstream>

Compiler::Compiler()
  : translator_{ std::make_unique<Translator>() }
{ }

void Compiler::setDataSection(const DataSection& dataSec)
{
  dataSec_ = dataSec;
}

void Compiler::setCodeSection(const CodeSection& codeSec)
{
  codeSec_ = codeSec;
}

std::pair<bool, ByteVec> Compiler::compile()
{
  // @bytes will contain all the bytecode
  auto [ok, bytes] = translator_->translate(codeSec_);
  if (!ok)
  {
    Logger::printMessage("Compilation did not succeed", LogLevel::HIGH);
    return std::make_pair(ok, ByteVec{});
  }
}
