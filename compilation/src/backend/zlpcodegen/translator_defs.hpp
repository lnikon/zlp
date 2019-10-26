#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <cstdint>

namespace ns_translator {
struct Translator;

using byte_t            = uint8_t;
using byte_vec_t        = std::vector<byte_t>;
using byte_vec_ref_t    = std::vector<byte_t>&;
using byte_vec_rref_t   = std::vector<byte_t>&&;
using byte_vec_cref_t   = const std::vector<byte_t>&;
using TranslationResult = std::optional<byte_vec_t>;

using UniqueTransPtr = std::unique_ptr<ns_translator::Translator>;
}

namespace ns_interface_translator {
struct ITranslator;

using UniqueTransImplPtr = std::unique_ptr<ns_interface_translator::ITranslator>;
}


