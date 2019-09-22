#pragma once

#include "translator_defs.hpp"

#include <memory>
#include <string>

struct IBinaryWriter
{
    explicit IBinaryWriter(const std::string& filename);
    
    virtual void write(const ByteVec&) = 0;

    protected:
    std::string s_filename_{};
};

using IBinWriterSPtr = std::shared_ptr<IBinaryWriter>;
using IBinWriterUPtr = std::unique_ptr<IBinaryWriter>;
using IBinWriterWPtr = std::weak_ptr<IBinaryWriter>;