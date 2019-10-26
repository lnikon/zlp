#pragma once

#include "common.hpp"
#include "type_defs.hpp"

struct Array
{
    Array() = default;

    Array(const Array&) = default;
    Array& operator=(const Array&) = default;

    Array(Array&&) noexcept = default;
    Array& operator=(Array&&) noexcept = default;

    std::string               name_{};

    std::vector<std::string>  valueFromLexer_{};
    std::size_t               valueSizeFromLexer_{};

    std::vector<QWORD>        value_{};
    std::size_t               size_{};

    bool                      isSizeSpecified_{false};

    ValueType                 type_{};

    bool isInitialized_{false};
};

