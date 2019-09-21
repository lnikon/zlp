#pragma once

#include "parser_defs.hpp"
#include <fstream>

struct MainSectionParser
{
    MainSection parse(std::fstream& inputStream);
};
