#pragma once

#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <optional>

#include "common.hpp"
#include "vm_config.hpp"
#include "extension_defs.hpp"
#include "type_defs.hpp"
#include "instruction.hpp"
#include "operand.hpp"
#include "label.hpp"
#include "function.hpp"
#include "array.hpp"
#include "variable.hpp"

using SimpleSymbolTable = std::unordered_map<std::string, std::size_t>;

struct StackSection
{
    std::size_t size_{};
};

/*
 * TODO: Pack into VariableEnvirnoment
 */
struct DataSection
{
    DataSection() = default;

    DataSection(const DataSection&) = default;
    DataSection& operator=(const DataSection&) = default;

    DataSection(DataSection&&) noexcept = default;
    DataSection& operator=(DataSection&&) noexcept = default;

    void insertVariable(const std::string& name, const Variable& var)
    {
        variableMap_.emplace(name, var);
    }

    std::optional<Variable> getVariable(const std::string& name)
    {
        auto it = variableMap_.find(name);
        if(it != std::end(variableMap_))
        {
            return it->second;
        }

        return std::nullopt;
    }

    bool variableExists(const std::string& name)
    {
        return variableMap_.find(name) != std::end(variableMap_);
    }

    void insertArray(const std::string& name, const Array& var)
    {
        arrayMap_.emplace(name, var);
    }

    std::optional<Array> getArray(const std::string& name)
    {
        auto it = arrayMap_.find(name);
        if(it != std::end(arrayMap_))
        {
            return it->second;
        }

        return std::nullopt;
    }

    bool arrayExists(const std::string& name)
    {
        return arrayMap_.find(name) != std::end(arrayMap_);
    }

    std::vector<Variable> getVariablesVector() const
    {
        std::vector<Variable> vars;

        for(const auto& var : variableMap_)
        {
            vars.push_back(var.second);
        }

        return vars;
    }

    std::vector<Array> getArraysVector() const
    {
        std::vector<Array> arrs;

        for(const auto& arr : arrayMap_)
        {
            arrs.push_back(arr.second);
        }

        return arrs;
    }

private:
    std::unordered_map<std::string, Variable>   variableMap_;
    std::unordered_map<std::string, Array>      arrayMap_;
};

/*
 * TODO: Pack into FunctionEnvirnoment
 */
struct CodeSection
{
    CodeSection() = default;

    CodeSection(const CodeSection&) = default;
    CodeSection& operator=(const CodeSection&) = default;

    CodeSection(CodeSection&&) noexcept = default;
    CodeSection& operator=(CodeSection&&) noexcept = default;

    function_vec_t code_{};

    void insertFunction(const Function& function)
    {
        code_.emplace_back(function);
    }

    void insertFunction(Function&& function)
    {
        code_.emplace_back(std::move(function));
    }

    bool isForwardDeclared(const std::string& name)
    {
        if(auto it = std::find_if(std::begin(code_), std::end(code_), [&name](const auto& fn) { return fn.name_ == name; } );
                it != std::end(code_))
        {
            return it->isForwardDeclared;
        }

        return false;
    }

    bool functionExists(const std::string& name)
    {
        return std::find_if(std::begin(code_), std::end(code_), [&name](const auto& fn)
        { return fn.name_ == name; }) != std::end(code_);
    }

    bool functionExists(const Function& fn)
    {
        return functionExists(fn.name_);
    }
};

struct MainSection
{
    std::string mainFunctionName_{};
};
