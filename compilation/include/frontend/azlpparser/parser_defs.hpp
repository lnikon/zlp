#pragma once

#include <unordered_map>

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

struct StackSection
{
  std::size_t size_{};
};

/*
 * TODO: Pack into VariableEnvirnoment
 */
struct DataSection
{
  void insertVariable(const std::string& name, const Variable& var) {}
  const Variable& getVariable(const std::string& name) { }
  bool variableExists(const std::string& name) {return false;}

  void insertArray(const std::string& name, const Array& var) {}
  const Array& getArray(const std::string& name) { }
  bool arrayExists(const std::string& name) { return false; }

  std::vector<Variable> getVariablesVector() const 
  {
    std::vector<Variable> vars;

    for(const auto var : variableMap_)
    {
      vars.push_back(var.second);
    }

    return vars;
  }

  std::vector<Array> getArraysVector() const 
  {
    std::vector<Array> arrs;

    for(const auto arr : arrayMap_)
    {
      arrs.push_back(arr.second);
    }

    return arrs;
  }

  private: std::unordered_map<std::string, Variable> variableMap_;  
  std::unordered_map<std::string, Array>    arrayMap_;  
};

/*
 * TODO: Pack into FunctionEnvirnoment
 */
struct CodeSection
{
  FunctionList code_{};

  void insertFunction(const Function& function) {}
  bool isForwardDeclared(const std::string& name) { return false; }
  bool functionExists(const std::string& name) { return false; }
  bool functionExists(const Function& name) { return false; }
};

struct MainSection
{
  std::string mainFunctionName_{};
};
