#pragma once

#include "interface_binary_writer.hpp"

struct GenericBinaryWriter : IBinaryWriter
{
    explicit GenericBinaryWriter(const std::string& filename);

    virtual void write(const ByteVec&) override;
};

using GenericBinWriterSPtr = std::shared_ptr<GenericBinaryWriter>;
using GenericBinWriterUPtr = std::unique_ptr<GenericBinaryWriter>;
using GenericBinWriterWPtr = std::weak_ptr<GenericBinaryWriter>;