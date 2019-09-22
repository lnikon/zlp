#include "generic_binary_writer.hpp"

#include <algorithm>
#include <iterator>
#include <fstream>

GenericBinaryWriter::GenericBinaryWriter(const std::string &filename)
    : IBinaryWriter{filename}
{
}

void GenericBinaryWriter::write(const ByteVec& bytes)
{
    std::fstream binaryOut(s_filename_ + ".zobj", std::ios::out | std::ios::binary);
    if(!binaryOut.is_open())
    {
        // Print error message
        // Halt all threads
    }

    std::copy(std::begin(bytes), std::end(bytes), std::ostream_iterator<Byte>{binaryOut});
}

