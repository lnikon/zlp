#include <algorithm>
#include <cctype>
#include <locale>
#include <type_traits>

#include "common.hpp"
#include "utility.hpp"

// Copied from StackOverflow
// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

// trim from start (in place)
void utility::ltrim(std::string &s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
          }));
}

// trim from end (in place)
void utility::rtrim(std::string &s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
          }).base(),
          s.end());
}

// trim from both ends (in place)
void utility::trim(std::string &s)
{
  utility::ltrim(s);
  utility::rtrim(s);
}

// trim from start (copying)
std::string utility::ltrim_copy(std::string s)
{
  utility::ltrim(s);
  return s;
}

// trim from end (copying)
std::string utility::rtrim_copy(std::string s)
{
  utility::rtrim(s);
  return s;
}

// trim from both ends (copying)
std::string utility::trim_copy(std::string s)
{
  utility::trim(s);
  return s;
}

bool utility::is_number(const std::string &s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void utility::find_and_replace(std::string &str,
                               const std::string &oldStr,
                               const std::string &newStr)
{
  std::string::size_type pos = 0u;
  while ((pos = str.find(oldStr, pos)) != std::string::npos)
  {
    str.replace(pos, oldStr.length(), newStr);
    pos += newStr.length();
  }
}

//! Tokenize the given string str with given delimiter. If no delimiter is given whitespace is used.
void utility::tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters)
{
  tokens.clear();
  // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of(delimiters, lastPos);
  }
}

std::string utility::convertBoolToString(const bool value)
{
  return (value) ? std::string{"true"} : std::string{"false"};
}

std::string utility::convertVectorOfStringToString(const std::vector<std::string> &strings)
{
  std::string result;
  result += "[";
  for (const auto &str : strings)
  {
    result += str + " ";
  }

  if (result.size() > 1)
  {
    result[result.size() - 1] = ']';
  }
  else
  {
    result += ']';
  }

  return result;
}

bool utility::starts_with(const std::string &line, const std::string &prefix)
{
  return (line.rfind(prefix, 0) == 0);
}

bool utility::checkCorrectKeyword(const std::string &line)
{
  if (line.empty())
  {
    return false;
  }

  if (!std::isalpha(line[0]))
  {
    return false;
  }

  for (std::size_t i = 0; i < line.size(); i++)
  {
    const unsigned char ch = static_cast<unsigned char>(line[i]);
    if (!std::isalnum(ch) && ch != '_')
    {
      return false;
    }
  }

  return true;
}

unsigned long utility::parse_int(const std::string &str)
{
  return std::stoi(str, nullptr, 10);
}

bool utility::parse_uint(const std::string &, std::size_t )
{
  return false;
}

ValueType utility::returnTypeForString(const std::string &type)
{
  if (type == "CHAR")
  {
    return ValueType::EXT_CHAR;
  }
  else if (type == "BYTE")
  {
    return ValueType::EXT_BYTE;
  }
  else if (type == "WORD")
  {
    return ValueType::EXT_WORD;
  }
  else if (type == "DWORD")
  {
    return ValueType::EXT_DWORD;
  }
  else if (type == "QWORD")
  {
    return ValueType::EXT_QWORD;
  }
  else
  {
    return ValueType::EXT_NULL;
  }
}

std::string utility::returnStringForType(const ValueType type)
{
  switch (type)
  {
  case ValueType::EXT_CHAR:
    return std::string{"CHAR"};
  case ValueType::EXT_BYTE:
    return std::string{"BYTE"};
  case ValueType::EXT_WORD:
    return std::string{"WORD"};
  case ValueType::EXT_DWORD:
    return std::string{"DWORD"};
  case ValueType::EXT_QWORD:
    return std::string{"QWORD"};
  case ValueType::EXT_NULL:
  default:
    return std::string{"INVALID"};
  }
}

//template<typename ValueType, int Radix>
//ValueType utility::parserNumber(const char delim, std::string *str)
//{
//    if ((*str)[0] == '-')
//    {
//        return parserNumberHelper<Signess<ValueType>::signed_type>(delim, str, Radix);
//    }
//    else
//    {
//        return parserNumberHelper<Signess<ValueType>::unsigned_type>(delim, str, Radix);
//    }
//}

//template<typename ValueType>
//ValueType utility::parserNumberHelper(const char delim, std::string *str, int radix)
//{
//    ValueType number = ValueType();

//    char* lastPos = nullptr;
//    if (std::is_signed<ValueType>::value)
//    {
//        int64_t signedNum = std::strtoll(str->c_str(), &lastPos, radix);
//        number = static_cast<ValueType>(signedNum);
//    }
//    else
//    {
//        uint64_t unsignedNum = std::strtoull(str->c_str(), &lastPos, radix);
//        number = static_cast<ValueType>(unsignedNum);
//    }

//    return number;
//}









