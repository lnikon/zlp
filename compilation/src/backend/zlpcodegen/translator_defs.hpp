#pragma once

#include <vector>
#include <memory>
#include <cstdint>

struct Translator;
struct ITranslator;

using ByteVec = std::vector<uint8_t>;
using TranslationResult = std::pair<bool, ByteVec>;
using UniqueTransPtr = std::unique_ptr<Translator>;
using UniqueTransImplPtr = std::unique_ptr<ITranslator>;

