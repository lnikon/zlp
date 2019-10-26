#pragma once

#include "interface_binary_writer.hpp"

struct GenericBinaryWriter : IBinaryWriter
{
    explicit GenericBinaryWriter(const std::string& filename);

    virtual void write(ns_translator::byte_vec_cref_t) override;
};

using GenericBinWriterSPtr = std::shared_ptr<GenericBinaryWriter>;
using GenericBinWriterUPtr = std::unique_ptr<GenericBinaryWriter>;
using GenericBinWriterWPtr = std::weak_ptr<GenericBinaryWriter>;
