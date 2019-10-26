#include "generic_binary_writer.hpp"

#include <algorithm>
#include <iterator>
#include <fstream>

GenericBinaryWriter::GenericBinaryWriter(const std::string &filename)
    : IBinaryWriter{filename}
{
}

void GenericBinaryWriter::write(ns_translator::byte_vec_cref_t byte_ts)
{
    std::fstream binaryOut(s_filename_ + ".zobj", std::ios::out | std::ios::binary);
    if(!binaryOut.is_open())
    {
        // Print error message
        // Halt all threads
    }

    std::copy(std::begin(byte_ts), std::end(byte_ts), std::ostream_iterator<ns_translator::byte_t>{binaryOut});
}

