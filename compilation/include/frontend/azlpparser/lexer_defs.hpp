// For the Syntax Specification of Zpl see src/syntax_description.txt

#pragma once

#include <string>
#include <vector>

/*
 * All include's are the tokens those are lexer
 * should return to the parser.
 */
#include "variable.hpp"
#include "extension_defs.hpp"
#include "type_defs.hpp"
#include "instruction.hpp"
#include "operand.hpp"
#include "label.hpp"
#include "function.hpp"
#include "array.hpp"

// Section definition names
static const std::string STACK_SEC_NAME = ".STACK";
static const std::string DATA_SEC_NAME  = ".DATA";
static const std::string CODE_SEC_NAME  = ".CODE";
static const std::string MAIN_SEC_NAME  = ".MAIN";

// Keywords
static const std::string FUNCTION_KWRD = "Func";
static const std::string END_FUNCTION_KWRD = "EndF";
