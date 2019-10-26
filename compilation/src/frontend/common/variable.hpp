#pragma once
#include "common.hpp"
#include "type_defs.hpp"

struct Variable
{
    Variable() = default;

    Variable(const Variable&) = default;
    Variable& operator=(const Variable&) = default;

    Variable(Variable&&) noexcept = default;
    Variable& operator=(Variable&&) noexcept = default;

    std::string name_{};

    // TODO: Wrap into ZplValue
    std::string valueFromLexer_{};

    QWORD       value_{};
    CHAR        charValue_{};

    ValueType   type_{};

    bool        isInitialized_{false};

    static bool equal(const Variable& var1, const Variable& var2);
};



