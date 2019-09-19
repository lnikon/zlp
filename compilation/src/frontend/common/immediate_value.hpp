#pragma once

#include <cstdint>

enum class ImmediateValueType  : uint8_t
{
    IMV_NULL,
    IMV_NUM8,
    IMV_NUM16,
    IMV_NUM32,
    IMV_NUM64,
    IMV_UNUM8,
    IMV_UNUM16,
    IMV_UNUM32,
    IMV_UNUM64,
};

struct ImmediateValue
{
    ImmediateValueType type_{ ImmediateValueType::IMV_NULL };

    union {
        int8_t byte_;
        int16_t word_;
        int32_t dword_;
        int64_t qword_;

        uint8_t  ubyte_;
        uint16_t uword_;
        uint32_t udword_;
        uint64_t uqword_;
    };
};
