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
#include "generic_value.h"

using SimpleSymbolTable = std::unordered_map<std::string, std::size_t>;

struct StackSection
{
    std::size_t size_{};
};

/*
 * TODO: Pack into VariableEnvirnoment
 */

struct DataSectionItem
{
    std::string name_{};
    GenericValue value_{};
};

struct DataSection
{
    DataSection() = default;

    DataSection(const DataSection&) = default;
    DataSection& operator=(const DataSection&) = default;

    DataSection(DataSection&&) noexcept = default;
    DataSection& operator=(DataSection&&) noexcept = default;

    bool put(const DataSectionItem& item)
    {
        items_.emplace_back(item);
        itemsMap_[item.name_] = items_.size() - 1;

        return true;
    }

    auto find(const std::string& name) const
    {
        auto it = itemsMap_.find(name);
        auto found = (it != itemsMap_.end());

        return std::make_pair(found, it);
    }

    auto begin()
    {
        return std::begin(items_);
    }

    auto end()
    {
        return std::end(items_);
    }

    auto begin() const
    {
        return std::cbegin(items_);
    }

    auto end() const
    {
        return std::cend(items_);
    }

private:
    std::vector<DataSectionItem> items_;
    std::unordered_map<std::string, std::size_t> itemsMap_;
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
    std::size_t entryPointIndex_{std::numeric_limits<uint32_t>::max()};

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

    auto begin()
    {
        return std::begin(code_);
    }

    auto end()
    {
        return std::end(code_);
    }

    auto cbegin()
    {
        return std::cbegin(code_);
    }

    auto cend()
    {
        return std::cend(code_);
    }
};

struct MainSection
{
    std::string mainFunctionName_{};
};
