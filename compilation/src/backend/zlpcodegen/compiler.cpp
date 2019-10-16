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

std::optional<ByteVec> Compiler::compile()
{
  // @bytes will contain all the bytecode
  const auto& bytes = translator_->translate(codeSec_);
  if (!bytes.has_value())
  {
    Logger::printMessage("Compilation did not succeed", LogLevel::HIGH);
    return std::nullopt;
  }

  return std::make_optional(bytes.value());
}
