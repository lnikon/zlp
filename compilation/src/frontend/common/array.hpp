#pragma once

#include "common.hpp"
#include "type_defs.hpp"

struct Array
{
  std::string               name_{};

  std::vector<std::string>  valueFromLexer_{};
  std::size_t               valueSizeFromLexer_{};

  std::vector<QWORD>        value_{};
  std::size_t               size_{};

  bool                      isSizeSpecified_{false};

  ValueType                 type_{};

  bool isInitialized_{false};
};

