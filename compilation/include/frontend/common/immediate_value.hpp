#pragma once

enum ImmediateValueType
{
    IMVNULL,
    IMVNUM8,
    IMVNUM16,
    IMVNUM32,
    IMVNUM64,
    IMVUNUM8,
    IMVUNUM16,
    IMVUNUM32,
    IMVUNUM64,
};

struct ImmediateValue
{
    ImmediateValueType type_{ ImmediateValueType::IMVNULL };

    union IMV {
        int8_t byte;
        int16_t word;
        int32_t dword;
        int64_t qword;

        uint8_t  ubyte;
        uint16_t uword;
        uint32_t udword;
        uint64_t uqword;
    };
};