#pragma once

#include "interface_binary_writer.hpp"

IBinaryWriter::IBinaryWriter(const std::string &filename)
    : s_filename_{filename}
{
}