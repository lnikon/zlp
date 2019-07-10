#include "variable.hpp"

bool Variable::areEqual(const Variable& var1, const Variable& var2)
{
  const bool sameName       = (var1.name_ == var2.name_);
  const bool sameValue      = (var1.value_ == var2.value_);
  const bool sameCharValue  = (var1.charValue_ == var2.charValue_);
  const bool sameType       = (var1.type_ == var2.type_);

  return sameName && sameValue && sameCharValue && sameType; 
}
