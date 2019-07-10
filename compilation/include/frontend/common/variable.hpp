#pragma once
#include "common.hpp"
#include "type_defs.hpp"

struct Variable
{
  std::string name_{};

  std::string valueFromLexer_{};

  QWORD       value_{};
  CHAR        charValue_{};
  
  ValueType   type_{};
  
  bool isInitialized_{false};

  //friend bool operator==(const Variable& var1, const Variable& var2);
  //friend bool operator!=(const Variable& var1, const Variable& var2);

  static bool areEqual(const Variable& var1, const Variable& var2);
};

//bool operator==(const Variable& var1, const Variable& var2)
//{
  //return Variable::areEqual(var1, var2);
//}

//bool operator!=(const Variable& var1, const Variable& var2)
//{
  //return !(var1 == var2);
//}


