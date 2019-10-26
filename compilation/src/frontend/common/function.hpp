#pragma once

#include "common.hpp"
#include "instruction.hpp"
#include "label.hpp"

struct Function
{
    Function() = default;

    Function(const Function&) = default;
    Function& operator=(const Function&) = default;

    Function(Function&&) noexcept = default;
    Function& operator=(Function&&) noexcept = default;

    std::string		name_{};
    InstructionList	code_{};
    LabelList		labels_{};

    bool			isForwardDeclared{false};
};
using function_vec_t = std::vector<Function>;

