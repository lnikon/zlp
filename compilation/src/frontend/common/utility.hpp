#pragma once

#include <algorithm>
#include <cctype>
#include <locale>

#include "common.hpp"
#include "type_defs.hpp"

namespace utility {
// trim from start (in place)
void ltrim(std::string &s);

// trim from end (in place)
void rtrim(std::string &s);

// trim from both ends (in place)
void trim(std::string &s);

// trim from start (copying)
std::string ltrim_copy(std::string s);

// trim from end (copying)
std::string rtrim_copy(std::string s);

// trim from both ends (copying)
std::string trim_copy(std::string s);

bool is_number(const std::string& s);

void find_and_replace(std::string& str,
                      const std::string& oldStr,
                      const std::string& newStr);

//! Tokenize the given string str with given delimiter. If no delimiter is given whitespace is used.
void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");

std::string convertBoolToString(const bool value);

std::string convertVectorOfStringToString(const std::vector<std::string>& strings);
bool starts_with(const std::string& line, const std::string& prefix);

bool checkCorrectKeyword(const std::string& line);

unsigned long parse_int(const std::string& str);
bool parse_uint(const std::string& str, std::size_t from);

ValueType returnTypeForString(const std::string &type);

std::string returnStringForType(const ValueType type);
} 
